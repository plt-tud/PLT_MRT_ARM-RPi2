################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TrafficLight/BinarySensor.cpp \
../src/TrafficLight/TrafficLight.cpp \
../src/TrafficLight/TrafficLightBehavior.cpp \
../src/TrafficLight/TrafficLightOutputFacility.cpp 

OBJS += \
./src/TrafficLight/BinarySensor.o \
./src/TrafficLight/TrafficLight.o \
./src/TrafficLight/TrafficLightBehavior.o \
./src/TrafficLight/TrafficLightOutputFacility.o 

CPP_DEPS += \
./src/TrafficLight/BinarySensor.d \
./src/TrafficLight/TrafficLight.d \
./src/TrafficLight/TrafficLightBehavior.d \
./src/TrafficLight/TrafficLightOutputFacility.d 


# Each subdirectory must supply rules for building sources it contributes
src/TrafficLight/%.o: ../src/TrafficLight/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -DBUILD_RPI -DUA_NO_AMALGAMATION -I"/home/mrt/workspace/UA_Lights/include" -I"/home/mrt/workspace/UA_Lights/include/open62541/deps" -I"/home/mrt/workspace/UA_Lights/include/open62541/src" -I"/home/mrt/workspace/UA_Lights/include/open62541/src/server" -I"/home/mrt/workspace/UA_Lights/include/Automaton" -I"/home/mrt/workspace/UA_Lights/include/model_pregenerated" -I"/home/mrt/workspace/UA_Lights/include/open62541" -I"/home/mrt/workspace/UA_Lights/include/TrafficLight" -I"/home/mrt/workspace/UA_Lights/include/ua_mapped_class" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


