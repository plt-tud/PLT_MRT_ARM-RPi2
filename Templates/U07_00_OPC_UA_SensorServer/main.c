//This file contains source-code that is discussed in a tutorial located here:
// http://open62541.org/doc/sphinx/tutorial_firstStepsServer.html

#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <dlfcn.h>

#include "ua_types.h"
#include "ua_server.h"
#include "logger_stdout.h"
#include "networklayer_tcp.h"
#include "bcm2835.h"

#include "ua_namespace.h"

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define OPCUA_SERVER_PORT 16664

UA_Boolean running;
UA_Logger logger = Logger_Stdout;

static void stopHandler(int signal) {
  running = UA_FALSE;
}

/**
 * @brief Stars an OPC UA Server on 0.0.0.0:OPCUA_SERVER_PORT (16664 per default)
 * 
 * @param args Takes no arguments (call is remnant of pthread)
 * @return void* Returns NULL
 */
void *ua_server_thread(void *args) {
  UA_Server *server = UA_Server_new(UA_ServerConfig_standard);
  UA_Server_setLogger(server, logger);
  UA_Server_addNetworkLayer(server, ServerNetworkLayerTCP_new(UA_ConnectionConfig_standard, OPCUA_SERVER_PORT));
  
  UA_Servernamespace_init(server);
  bcm2835_init();
  UA_Server_run(server, 1, &running);
  UA_Server_delete(server);
  bcm2835_spi_end();
  
  printf("Terminated\n");
  return NULL;
}

/**
 * @brief The beacon thread periodically sends an UDP broadcast to allow clients in the same subnet to locate this server. The thread will keep on running until a SIGINT is received.
 * 
 * @param args Takes no arguments (call is remnant of pthread)
 * @return void* Returns NULL
 */
void *udp_beacon_thread(void *args) {
  char *err, *buf = "UA Server Beacon";
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    printf("Beacon Error: Could not create socket\n");
    return NULL;
  }
  int res;
  struct sockaddr_in dst;
  
  // Enable broadcast (will return "Permission denied" on sendto otherwise)
  int broadcastEnable=1;
  res=setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
    
  memset(&dst, '\0', sizeof(struct sockaddr_in));
  dst.sin_family = AF_INET;
  dst.sin_port   = htons(16666);
  dst.sin_addr.s_addr = htonl(INADDR_BROADCAST);;
  
  // Send periodic beacons so clients can locate us
  while (running != UA_FALSE) {
    sleep(1);
    printf("beacon\n");
    res = sendto(sock, buf, strlen(buf), 0, (const struct sockaddr *) &dst, sizeof(struct sockaddr_in));
    if (res < 0) {
      err = strerror(errno);
      printf("Beacon Error: %s\n", err);
      break;
    }
  }
  
  return NULL;
}

int main(void) {
  pthread_t opcua_server_thread, beacon_thread;
  void *opcua_server_thread_result;
  
  // Register for Interrupt and Terminate signals (CTRL-C and KILL)
  signal(SIGINT,  stopHandler);
  signal(SIGTERM, stopHandler);
  running = UA_TRUE;
  
  // Start 2 Threads: UA Server, UDP beacon
  int res = pthread_create(&opcua_server_thread, NULL, ua_server_thread, NULL);
  res = pthread_create(&beacon_thread, NULL, udp_beacon_thread, NULL);
  
  // Wait for threads to rejoin
  res = pthread_join(opcua_server_thread, &opcua_server_thread_result);
  if (res) {
    printf("Threads could not be joined");
  }
  
  return 0;
}
