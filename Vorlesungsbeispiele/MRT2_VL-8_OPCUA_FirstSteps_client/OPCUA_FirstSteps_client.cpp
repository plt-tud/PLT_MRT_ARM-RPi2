/*
	Copyright (c) 2019 Chris Iatrou <chris_paul.iatrou@tu-dresdden.de>

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
 */
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include "open62541.h"

bool runClient = true;

static void stopHandler(int sig) {
    runClient = false;
}

int main(void) {
    signal(SIGINT,  stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Client *client    = UA_Client_new(UA_ClientConfig_default);


    /* Verbindung mit einem lokal laufenden Ampel Server: */
    //UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://127.0.0.1:4840");

    /* Verbindung mit einem Ampel Server auf dem Raspberry Pi: */
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.0.240:4840");

    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return (int)retval;
    }

    /* Hier mit dem Server interagieren */
    while (runClient) {
        UA_Client_manuallyRenewSecureChannel(client);
        std::cout << "Client Renewing Session" << std::endl;
        sleep(1);
    }

    UA_Client_delete(client);
    return UA_STATUSCODE_GOOD;
}
