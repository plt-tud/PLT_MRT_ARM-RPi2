################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ua_mapped_class/ua_mapped_class.cpp \
../src/ua_mapped_class/ua_proxies.cpp \
../src/ua_mapped_class/ua_remoteobject.cpp 

OBJS += \
./src/ua_mapped_class/ua_mapped_class.o \
./src/ua_mapped_class/ua_proxies.o \
./src/ua_mapped_class/ua_remoteobject.o 

CPP_DEPS += \
./src/ua_mapped_class/ua_mapped_class.d \
./src/ua_mapped_class/ua_proxies.d \
./src/ua_mapped_class/ua_remoteobject.d 


# Each subdirectory must supply rules for building sources it contributes
src/ua_mapped_class/%.o: ../src/ua_mapped_class/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -DBUILD_RPI -DUA_NO_AMALGAMATION -I"/home/mrt/workspace/UA_Lights/include" -I"/home/mrt/workspace/UA_Lights/include/open62541/deps" -I"/home/mrt/workspace/UA_Lights/include/open62541/src" -I"/home/mrt/workspace/UA_Lights/include/open62541/src/server" -I"/home/mrt/workspace/UA_Lights/include/Automaton" -I"/home/mrt/workspace/UA_Lights/include/model_pregenerated" -I"/home/mrt/workspace/UA_Lights/include/open62541" -I"/home/mrt/workspace/UA_Lights/include/TrafficLight" -I"/home/mrt/workspace/UA_Lights/include/ua_mapped_class" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


