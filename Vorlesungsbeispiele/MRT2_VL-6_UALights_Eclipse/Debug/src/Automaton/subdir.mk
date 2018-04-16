################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Automaton/Automaton.cpp \
../src/Automaton/AutomatonElement.cpp \
../src/Automaton/Behavior.cpp \
../src/Automaton/State.cpp \
../src/Automaton/Transition.cpp 

OBJS += \
./src/Automaton/Automaton.o \
./src/Automaton/AutomatonElement.o \
./src/Automaton/Behavior.o \
./src/Automaton/State.o \
./src/Automaton/Transition.o 

CPP_DEPS += \
./src/Automaton/Automaton.d \
./src/Automaton/AutomatonElement.d \
./src/Automaton/Behavior.d \
./src/Automaton/State.d \
./src/Automaton/Transition.d 


# Each subdirectory must supply rules for building sources it contributes
src/Automaton/%.o: ../src/Automaton/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-linux-gnueabihf-g++ -std=c++0x -DBUILD_RPI -DUA_NO_AMALGAMATION -I"/home/mrt/workspace/UA_Lights/include" -I"/home/mrt/workspace/UA_Lights/include/open62541/deps" -I"/home/mrt/workspace/UA_Lights/include/open62541/src" -I"/home/mrt/workspace/UA_Lights/include/open62541/src/server" -I"/home/mrt/workspace/UA_Lights/include/Automaton" -I"/home/mrt/workspace/UA_Lights/include/model_pregenerated" -I"/home/mrt/workspace/UA_Lights/include/open62541" -I"/home/mrt/workspace/UA_Lights/include/TrafficLight" -I"/home/mrt/workspace/UA_Lights/include/ua_mapped_class" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


