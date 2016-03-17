#include "ua_namespace.h"
#include "bcm2835.h"
#include <stdio.h>
#include <stdlib.h>
#include "sys/utsname.h"
#include "ua_types.h"
#include <dirent.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/**
 * @brief Get an ADC Value (as Voltage) from a SPI connected MCP2008 ADC
 * 
 * @param handle Channel number of the ADC
 * @param nodeid NodeId on which this datasource was requested
 * @param sourceTimeStamp Timestamp on which the SPI communications where initialized
 * @param range Ignored for this function
 * @param dataValue Will contain a floating point value as a voltage equivalent ADC sample
 * @return UA_StatusCode Returns GOOD or -1 if an error occurs
 */
static UA_StatusCode getADC(void *handle, const UA_NodeId nodeid, UA_Boolean sourceTimeStamp, const UA_NumericRange *range, UA_DataValue *dataValue) {
  //note that this is only possible if the identifier is a string - but we are sure to have one here
  bcm2835_spi_begin();
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, 0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);
  
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  
  //Transfer many bytes
  char data_buffer[3];
  data_buffer[0] = 1;
  data_buffer[2] = 0;
  
  int channel = *((int *) handle);
  data_buffer[1] = (8+channel) << 4;
  bcm2835_spi_transfern(&data_buffer[0], 3);     //data_buffer used for tx and rx
  
  /* TMP36 Analog devices sensor: 750mV@25C, 10mV/C
  float t;*
  t = data_buffer[2];
  t = t/1024 * 5.0 - 0.75;
  t = 25 + t/0.1;
  */
  dataValue->hasValue = UA_TRUE;
  
  unsigned int h = ((data_buffer[1] && 0x0F) << 8 ) + data_buffer[2];
  UA_Variant_setScalarCopy(&dataValue->value, &h, &UA_TYPES[UA_TYPES_INT32]);
  
  return UA_STATUSCODE_GOOD;
}

static UA_StatusCode writeGPIOValue(void *handle, const UA_NodeId nodeid, const UA_Variant *data, const UA_NumericRange *range) {
  UA_UInt32 gpioValue = 0;
  UA_UInt32 gpioNo = 0;
  
  if (handle == NULL)
    return UA_STATUSCODE_BADINTERNALERROR;
  gpioNo = (int) *((int *) handle);
  
  UA_NodeId cmp_int32 = UA_NODEID_NUMERIC(0, UA_NS0ID_INT32);
  if (data->data == NULL)
    return UA_STATUSCODE_BADARGUMENTSMISSING;
  if (!UA_NodeId_equal(&cmp_int32, &data->type->typeId))
    return UA_STATUSCODE_BADARGUMENTSMISSING;
  
  gpioValue = (UA_Int32) *((UA_Int32 *) (data->data));
  if (gpioValue > 1 || gpioValue < 0)
    return UA_STATUSCODE_BADOUTOFRANGE;
  if (gpioValue == 0)
    bcm2835_gpio_clr(gpioNo);
  else
    bcm2835_gpio_set(gpioNo);
  
  return UA_STATUSCODE_GOOD;
}

static UA_StatusCode readGPIOValue(void *handle, const UA_NodeId nodeid, UA_Boolean sourceTimeStamp, const UA_NumericRange *range, UA_DataValue *dataValue) {
  UA_UInt32 gpioValue = 0;
  
  if (handle == NULL)
    return UA_STATUSCODE_BADINTERNALERROR;
  
  if (bcm2835_gpio_lev((int) *((int *) handle)) != 0)
    gpioValue = 1;
  
  UA_Variant_setScalarCopy(&dataValue->value, &gpioValue, &UA_TYPES[UA_TYPES_INT32]);
  dataValue->hasValue = UA_TRUE;
  dataValue->hasServerTimestamp = UA_TRUE;
  dataValue->serverTimestamp = UA_DateTime_now();
  
  return UA_STATUSCODE_GOOD;
}

static UA_StatusCode writeGPIOfsel(void *handle, const UA_NodeId nodeid, const UA_Variant *data, const UA_NumericRange *range) {
  
  if (handle == NULL)
    return UA_STATUSCODE_BADINTERNALERROR;
  UA_UInt32 gpioNo = (int) *((int *) handle);
  
  UA_NodeId cmp_int32 = UA_NODEID_NUMERIC(0, UA_NS0ID_INT32);
  if (data->data == NULL)
    return UA_STATUSCODE_BADARGUMENTSMISSING;
  if (!UA_NodeId_equal(&cmp_int32, &data->type->typeId))
    return UA_STATUSCODE_BADARGUMENTSMISSING;
  
  UA_UInt32 gpioFSEL = (UA_Int32) *((UA_Int32 *) (data->data));
  
  if (gpioFSEL > 7 || gpioFSEL < 0)
    return UA_STATUSCODE_BADOUTOFRANGE;
  
  bcm2835_gpio_fsel(gpioNo, gpioFSEL);
  
  return UA_STATUSCODE_GOOD;
}

static UA_StatusCode readGPIOfsel(void *handle, const UA_NodeId nodeid, UA_Boolean sourceTimeStamp, const UA_NumericRange *range, UA_DataValue *dataValue) {
  UA_UInt32 gpioFSEL = 0;
  
  if (handle == NULL)
    return UA_STATUSCODE_BADINTERNALERROR;
  
  /*there is no read_fsel in the library... perform this using peri_read*/
  UA_UInt32 gpioNo = (int) *((int *) handle);
  // Warn: this is a pointer to a 32 bit word... do not use ((gpioNo/10)) << 2 --> *4byte is implicit
  volatile uint32_t* fseladdr = (uint32_t*) (bcm2835_regbase(BCM2835_REGBASE_GPIO) + BCM2835_GPFSEL0 + (gpioNo/10)); // << 2) );
  gpioFSEL = bcm2835_peri_read(fseladdr);
  gpioFSEL = (gpioFSEL >> ((int) *((int *) handle))%10) && 0x07;
  
  UA_Variant_setScalarCopy(&dataValue->value, &gpioFSEL, &UA_TYPES[UA_TYPES_INT32]);
  dataValue->hasValue = UA_TRUE;
  dataValue->hasServerTimestamp = UA_TRUE;
  dataValue->serverTimestamp = UA_DateTime_now();
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode setGPIO(const UA_NodeId objectId, const UA_Variant *input, UA_Variant *output, void *handle) {
  int gpiono = (int) *((int *) handle);
  printf("Setting %d\n", gpiono);
  if (handle != NULL)
    bcm2835_gpio_set(gpiono);
  
  return UA_STATUSCODE_GOOD;
}

UA_StatusCode clrGPIO(const UA_NodeId objectId, const UA_Variant *input, UA_Variant *output, void *handle) {
  int gpiono = (int) *((int *) handle);
  if (handle != NULL)
    bcm2835_gpio_clr(gpiono);
  
  return UA_STATUSCODE_GOOD;
}

static int readline(int file, char **buffer, unsigned int maxlength) { 
  *buffer = (char *) malloc(maxlength);
  memset(*buffer, 0, maxlength);
  char buf = 0;
  unsigned int pos = 0;
  int r;
  while (pos<maxlength && (r = read(file, &buf, 1))) {
    (*buffer)[pos++] = buf;
    if(buf == '\n') break;;
  }
  if (pos != maxlength && pos > 0) {
    (*buffer)[--pos] = 0; // remove the newline
  }
  realloc(*buffer, pos);
  
  // return -1 at EOF, 0 if we really have a zero length string
  return (r==0) ? -1 : pos;
}

static UA_String *getMACofDevice(char *deviceName) {
  int addressFile;
  char *addressFileName = (char *) malloc(strlen(deviceName) + 14 + 10);
  UA_String *address = UA_String_new();
  strcpy(addressFileName, "/sys/class/net/");
  strcpy(&addressFileName[15], deviceName);
  strcpy(&addressFileName[15+strlen(deviceName)], "/address");
  
  if((addressFile = open(addressFileName, O_RDONLY))) { // Read MAC address from file
    address->length = readline(addressFile, (char **) &address->data, 126);
    close(addressFile);
  }
  realloc(address->data, address->length);
  free(addressFileName );
  
  return address;
}

UA_StatusCode UA_Servernamespace_init_device(UA_Server *server, UA_NodeId *virtualRootNodeId) {
  UA_StatusCode retval = UA_STATUSCODE_GOOD;
  
  struct utsname sysinfo;
  if(!uname(&sysinfo)) {
    UA_VariableAttributes attr;
    UA_VariableAttributes_init(&attr);
    UA_QualifiedName browsename;
    UA_String  varContent;
    
    for(int i = 0; i<6; i++) {
      switch(i) {
        case 0: 
          attr.displayName = UA_LOCALIZEDTEXT("en_US", "nodename");
          attr.description = UA_LOCALIZEDTEXT("en_US", "nodename");
          browsename = UA_QUALIFIEDNAME(1, "nodename");
          varContent = UA_String_fromChars((char*) &sysinfo.nodename);
          break;
        case 1: 
          attr.displayName = UA_LOCALIZEDTEXT("en_US", "release");
          attr.description = UA_LOCALIZEDTEXT("en_US", "release");
          browsename = UA_QUALIFIEDNAME(1, "release");
          varContent = UA_String_fromChars((char*) &sysinfo.release);
          break;
        break;
        case 2: 
          attr.displayName = UA_LOCALIZEDTEXT("en_US", "sysname");
          attr.description = UA_LOCALIZEDTEXT("en_US", "sysname");
          browsename = UA_QUALIFIEDNAME(1, "sysname");
          varContent = UA_String_fromChars((char*) &sysinfo.sysname);
          break;
        break;
        case 3: 
          attr.displayName = UA_LOCALIZEDTEXT("en_US", "domainname");
          attr.description = UA_LOCALIZEDTEXT("en_US", "domainname");
          browsename = UA_QUALIFIEDNAME(1, "domainname");
          # ifdef __USE_GNU
            varContent = UA_String_fromChars((char*) &sysinfo.domainname);
          #else
            varContent = UA_String_fromChars("");
          #endif
          break;
        break;
        case 4: 
          attr.displayName = UA_LOCALIZEDTEXT("en_US", "machine");
          attr.description = UA_LOCALIZEDTEXT("en_US", "machine");
          browsename = UA_QUALIFIEDNAME(1, "machine");
          varContent = UA_String_fromChars((char*) &sysinfo.machine);
          break;
        break;
        case 5: 
          attr.displayName = UA_LOCALIZEDTEXT("en_US", "version");
          attr.description = UA_LOCALIZEDTEXT("en_US", "version");
          browsename = UA_QUALIFIEDNAME(1, "version");
          varContent = UA_String_fromChars((char*) &sysinfo.version);
          break;
        default:
          attr.displayName = UA_LOCALIZEDTEXT("en_US", "");
          attr.description = UA_LOCALIZEDTEXT("en_US", "");
          browsename = UA_QUALIFIEDNAME(1, "");
          varContent = UA_String_fromChars("");
          break;
      }
      UA_Variant_setScalarCopy(&attr.value, &varContent, &UA_TYPES[UA_TYPES_STRING]);
      retval |= UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1,0),
                                          *virtualRootNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                          browsename, UA_NODEID_NULL,
                                          attr, NULL);
      UA_String_deleteMembers(&varContent);
    }
  }
  
  // Create a network adapter node
  UA_ObjectAttributes   oAttributes;
  UA_VariableAttributes vAttributes;
  UA_ObjectAttributes_init(&oAttributes);
  UA_VariableAttributes_init(&vAttributes);
  
  UA_NodeId *netNode = UA_NodeId_new();
  oAttributes.description = UA_LOCALIZEDTEXT("en_US", "Networking adapters and cards information");
  oAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "Networking");
  retval = UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1,0),
                                    *virtualRootNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                    UA_QUALIFIEDNAME(1, "NetDevices"), UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),
                                    oAttributes, netNode);
  UA_NodeId *netDevNode = UA_NodeId_new();
  if (retval == UA_STATUSCODE_GOOD) {
    DIR *classNetDir;
    struct dirent *classNetDirEnt;
    classNetDir = opendir("/sys/class/net");
    if (classNetDir) {
      // For each adapter listed
      while ((classNetDirEnt = readdir(classNetDir)) != NULL) {
        if(strncmp(classNetDirEnt->d_name, ".", 1)) { // Filter "." and ".." directories
          oAttributes.description = UA_LOCALIZEDTEXT("en_US", classNetDirEnt->d_name);
          oAttributes.displayName = UA_LOCALIZEDTEXT("en_US", classNetDirEnt->d_name);
          retval = UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1,0),
                                           *netNode, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                           UA_QUALIFIEDNAME(1, classNetDirEnt->d_name), UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),
                                           oAttributes, netDevNode);
          // Read this devices MAC address
          vAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "MAC");
          vAttributes.description = UA_LOCALIZEDTEXT("en_US", "Media Access Controller address of this device.");
          
          // We need to read /sys/class/net/<deviceName>/address
          UA_String *address = getMACofDevice(classNetDirEnt->d_name);
          UA_Variant_setScalarCopy(&vAttributes.value, address, &UA_TYPES[UA_TYPES_STRING]);
          retval = UA_Server_addVariableNode( server, UA_NODEID_NUMERIC(1,0),
                                              *netDevNode, UA_NODEID_NUMERIC(0, UA_NS0ID_HASPROPERTY),
                                              UA_QUALIFIEDNAME(1, "MAC Address"), UA_NODEID_NULL,
                                              vAttributes, NULL);
          
          UA_String_delete(address);
        }
      }
      closedir(classNetDir);
    }
  }
  UA_NodeId_delete(netDevNode);
  UA_NodeId_delete(netNode);
  
  // Create a cpu info node
  UA_NodeId *cpuNode = UA_NodeId_new();
  oAttributes.description = UA_LOCALIZEDTEXT("en_US", "CPU information");
  oAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "CPU");
  retval = UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1,0),
                                   *virtualRootNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                   UA_QUALIFIEDNAME(1, "CPU"), UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),
                                   oAttributes, cpuNode);
  char *cpuInfoLine = NULL;
  int  cpuInfoFile;
  vAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "CPU Serial");
  vAttributes.description = UA_LOCALIZEDTEXT("en_US", "Serial number of the processor/SoC");
  if((cpuInfoFile = open("/proc/cpuinfo", O_RDONLY))) {
    while(readline(cpuInfoFile, &cpuInfoLine, 255) >= 0) {
      if (cpuInfoLine == NULL) continue;
      if(!strncmp(cpuInfoLine, "Serial", 6)) {
        int pos=7;
        while ((cpuInfoLine[pos] == ' ' || cpuInfoLine[pos] == '\t' || cpuInfoLine[pos] == ':') && pos < strlen(cpuInfoLine)) pos++;
        
        UA_String tmp = UA_String_fromChars((char *) &cpuInfoLine[pos]);
        UA_Variant_setScalarCopy(&vAttributes.value, &tmp, &UA_TYPES[UA_TYPES_STRING]);
        retval |= UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1,0),
                                            *cpuNode, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                            UA_QUALIFIEDNAME(1, "CPUSerial"), UA_NODEID_NULL,
                                            vAttributes, NULL);
        break;
      }
    }
    close(cpuInfoFile);
  }
  UA_NodeId_delete(cpuNode);
  return retval;
}

UA_StatusCode UA_Servernamespace_init_GPIOs(UA_Server *server, UA_NodeId *virtualRootNodeId) {
  UA_StatusCode retval = UA_STATUSCODE_GOOD;
  UA_ObjectAttributes oAttributes;
  UA_ObjectAttributes_init(&oAttributes);
  
  UA_MethodAttributes mAttributes;
  UA_MethodAttributes_init(&mAttributes);
  
  UA_VariableAttributes vAttributes;
  UA_VariableAttributes_init(&vAttributes);
  
  UA_NodeId *NewNodeId = UA_NodeId_new();
  char gpioName[255];
  UA_DataSource dateDataSource;
  
  UA_Int32 *GPIOHandle; 
  for (int gpiono=0; gpiono < 64 && retval == UA_STATUSCODE_GOOD; gpiono++) {
      GPIOHandle = (UA_Int32 *) malloc(sizeof(UA_Int32));
      *GPIOHandle = gpiono;
      
      sprintf((char *) &gpioName, "GPIO Pin %d", gpiono);
      oAttributes.description = UA_LOCALIZEDTEXT("en_US", (char *) &gpioName);
      oAttributes.displayName = UA_LOCALIZEDTEXT("en_US", (char *) &gpioName);
      retval |= UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1,0),
					*virtualRootNodeId,
					UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
					UA_QUALIFIEDNAME(1, "Device"),
					UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),
					oAttributes,
					NewNodeId);
      if (retval) {
	break;
      }
 
      // Create a Read/Write datasource for the pins logical value
      sprintf((char *) &gpioName, "GPIO Pin %d Value", gpiono);
      dateDataSource = (UA_DataSource) {.handle = GPIOHandle, .read = readGPIOValue, .write = writeGPIOValue};
      vAttributes.displayName = UA_LOCALIZEDTEXT("en_US", (char *) &gpioName);
      vAttributes.description = UA_LOCALIZEDTEXT("en_US","Logical level value of GPIO (0=Low, 1=High)");
      retval |= UA_Server_addDataSourceVariableNode(server, UA_NODEID_NUMERIC(1,0),
					  *NewNodeId,
					  UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
					  UA_QUALIFIEDNAME(1, (char *) &gpioName), UA_NODEID_NULL, vAttributes, dateDataSource, NULL);
      
      // Create a Read/Write datasource for the pins function select register
      sprintf((char *) &gpioName, "GPIO Pin %d FSEL", gpiono);
      dateDataSource = (UA_DataSource) {.handle = GPIOHandle, .read = readGPIOfsel, .write = writeGPIOfsel};
      vAttributes.displayName = UA_LOCALIZEDTEXT("en_US", (char *) &gpioName);
      vAttributes.description = UA_LOCALIZEDTEXT("en_US","Function select register for this pin");
      retval |= UA_Server_addDataSourceVariableNode(server, UA_NODEID_NUMERIC(1,0),
                                                    *NewNodeId,
                                                    UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                                                    UA_QUALIFIEDNAME(1, (char *) &gpioName), UA_NODEID_NULL, vAttributes, dateDataSource, NULL);
      
      // Create a SET Function
      sprintf((char *) &gpioName, "Set_GPIO%d", gpiono);
      mAttributes.executable = UA_TRUE;
      mAttributes.userExecutable = UA_TRUE;
      mAttributes.description = UA_LOCALIZEDTEXT("en_US", "Set GPIO Pin level to high");
      mAttributes.displayName = UA_LOCALIZEDTEXT("en_US", (char *) &gpioName);
      retval |= UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(0, 0),
			      *NewNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
			      UA_QUALIFIEDNAME(1, (char *) &gpioName), mAttributes,
			      setGPIO, GPIOHandle,
			      0, NULL, 0, NULL,
			      NULL
 			    );
      
      // Create a CLR Function
      sprintf((char *) &gpioName, "Clr_GPIO%d", gpiono);
      mAttributes.description = UA_LOCALIZEDTEXT("en_US", "Set GPIO Pin level to low");
      mAttributes.displayName = UA_LOCALIZEDTEXT("en_US", (char *) &gpioName);
      retval |= UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(0, 0),
			      *NewNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
			      UA_QUALIFIEDNAME(1, (char *) &gpioName), mAttributes,
			      clrGPIO, GPIOHandle, 0, NULL, 0, NULL, NULL
 			    );
  }
  
  return retval;
}

UA_StatusCode UA_Servernamespace_init_ADC(UA_Server *server, UA_NodeId *virtualRootNodeId) {
  UA_StatusCode retval = UA_STATUSCODE_GOOD;
  
  UA_VariableAttributes vAttributes;
  UA_VariableAttributes_init(&vAttributes);    
  
  UA_NodeId *NewNodeId = UA_NodeId_new();
  char channelName[255];
  UA_DataSource dateDataSource;
  
  // Create an 8 ADC read values
  UA_Int32 *ADCHandle;
  for(int channelID = 0; channelID < 8; channelID ++) {
    ADCHandle = UA_Int32_new();
    *ADCHandle = channelID;
    sprintf((char*) &channelName, "ADC Channel %d", channelID);
    dateDataSource = (UA_DataSource) {.handle = ADCHandle, .read = getADC, .write = NULL};
    vAttributes.description = UA_LOCALIZEDTEXT("en_US","Voltage on MCP3008 Sensor Channel");
    vAttributes.displayName = UA_LOCALIZEDTEXT("en_US",(char *) channelName);
    UA_Server_addDataSourceVariableNode(server, UA_NODEID_NUMERIC(1,0),
					*virtualRootNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
					UA_QUALIFIEDNAME(1, (char *) channelName), UA_NODEID_NULL, 
					vAttributes, dateDataSource, NewNodeId);
  }
  
  return retval;
}

UA_StatusCode UA_Servernamespace_init(UA_Server *server) {
  UA_StatusCode retval = UA_STATUSCODE_GOOD;
  UA_ObjectAttributes oAttributes;
  UA_ObjectAttributes_init(&oAttributes);
  
  oAttributes.description = UA_LOCALIZEDTEXT("en_US", "Raspberry Pi device components");
  oAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "Device");
  // Create a new root node in OBJECTS to store RPi data structures
  UA_NodeId *deviceRootNodeId = UA_NodeId_new();
  retval |= UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1,0),
			  UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                          UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                          UA_QUALIFIEDNAME(1, "Device"),
			  UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),
			  oAttributes,
			  deviceRootNodeId);
  if (retval != UA_STATUSCODE_GOOD) {
      UA_NodeId_delete(deviceRootNodeId);
      return -1;
  }
  UA_NodeId *NewNodeId = UA_NodeId_new();
  
  UA_VariableAttributes vAttributes;
  UA_VariableAttributes_init(&vAttributes);    
  
  // Create a human readable device description
  UA_LocalizedText tmpLoclizedText = UA_LOCALIZEDTEXT("en_US", "Raspberry Pi 2 B");
  UA_Variant_setScalarCopy(&vAttributes.value, &tmpLoclizedText, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
  vAttributes.description = UA_LOCALIZEDTEXT("en_US", "OS System and host information");
  vAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "System");
  retval |= UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1,0),
			    *deviceRootNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
			    UA_QUALIFIEDNAME(1, "DeviceType"), UA_NODEID_NULL,
                            vAttributes, NewNodeId);
  UA_Servernamespace_init_device(server, NewNodeId);
  
  // Create a new root node for GPIOs
  oAttributes.description = UA_LOCALIZEDTEXT("en_US", "General Purpose input/output pins");
  oAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "GPIOs");
  retval |= UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1,0),
			  *deviceRootNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                          UA_QUALIFIEDNAME(1, "GPIOs"), UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),
			  oAttributes, NewNodeId);
  // Create GPIOs under this node
  UA_Servernamespace_init_GPIOs(server, NewNodeId);
  
  // Create a new root node for ADC data
  oAttributes.description = UA_LOCALIZEDTEXT("en_US", "MCP3008 ADC Sensor");
  oAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "ADC Values");
  retval |= UA_Server_addObjectNode(server, UA_NODEID_NUMERIC(1,0),
			  *deviceRootNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                          UA_QUALIFIEDNAME(1, "ADC Values"), UA_NODEID_NUMERIC(0, UA_NS0ID_FOLDERTYPE),
			  oAttributes, NewNodeId);
  UA_Servernamespace_init_ADC(server, NewNodeId);
  
  UA_NodeId_delete(NewNodeId);
  UA_NodeId_delete(deviceRootNodeId);
  return retval;
}