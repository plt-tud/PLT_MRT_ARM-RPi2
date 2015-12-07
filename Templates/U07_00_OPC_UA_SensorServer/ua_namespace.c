#include "ua_namespace.h"
#include "bcm2835.h"
#include <stdio.h>
#include <stdlib.h>

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
  volatile uint32_t* fseladdr = (uint32_t*) (bcm2835_regbase(BCM2835_REGBASE_PADS) + BCM2835_GPFSEL0 + ((gpioNo/10) << 2) );
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

  
  UA_VariableAttributes vAttributes;
  UA_VariableAttributes_init(&vAttributes);    
  
  // Create a human readable device description
  UA_LocalizedText tmpLoclizedText = UA_LOCALIZEDTEXT("en_US", "Raspberry Pi 2 B");
  UA_Variant_setScalarCopy(&vAttributes.value, &tmpLoclizedText, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
  vAttributes.description = UA_LOCALIZEDTEXT("en_US", "Device type");
  vAttributes.displayName = UA_LOCALIZEDTEXT("en_US", "DeviceType");
  retval |= UA_Server_addVariableNode(server, UA_NODEID_NUMERIC(1,0),
			    *deviceRootNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
			    UA_QUALIFIEDNAME(1, "DeviceType"), UA_NODEID_NULL,
			    vAttributes, NULL);
  
  // Create a series of nodes for GPIOs
  UA_NodeId *NewNodeId = UA_NodeId_new();
  
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