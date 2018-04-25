################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Ampel.cpp \
../src/Ampel_Behaviors.cpp \
../src/Automaton.cpp \
../src/AutomatonElement.cpp \
../src/Behavior.cpp \
../src/State.cpp \
../src/Transition.cpp \
../src/ampel_capabilities.cpp \
../src/ampel_peripheral_rPi.cpp \
../src/ampel_peripheral_x86.cpp \
../src/rPi_accessor.cpp \
../src/task.cpp 

OBJS += \
./src/Ampel.o \
./src/Ampel_Behaviors.o \
./src/Automaton.o \
./src/AutomatonElement.o \
./src/Behavior.o \
./src/State.o \
./src/Transition.o \
./src/ampel_capabilities.o \
./src/ampel_peripheral_rPi.o \
./src/ampel_peripheral_x86.o \
./src/rPi_accessor.o \
./src/task.o 

CPP_DEPS += \
./src/Ampel.d \
./src/Ampel_Behaviors.d \
./src/Automaton.d \
./src/AutomatonElement.d \
./src/Behavior.d \
./src/State.d \
./src/Transition.d \
./src/ampel_capabilities.d \
./src/ampel_peripheral_rPi.d \
./src/ampel_peripheral_x86.d \
./src/rPi_accessor.d \
./src/task.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/mrt/workspace/Ampel_ohne_IoT/include" -I"/home/mrt/workspace/Ampel_ohne_IoT/src" -I"/home/mrt/workspace/Ampel_ohne_IoT/include/Automaton" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


