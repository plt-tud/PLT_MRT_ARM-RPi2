################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Automaton.cpp \
../src/AutomatonElement.cpp \
../src/Behavior.cpp \
../src/State.cpp \
../src/Transition.cpp \
../src/example.cpp 

OBJS += \
./src/Automaton.o \
./src/AutomatonElement.o \
./src/Behavior.o \
./src/State.o \
./src/Transition.o \
./src/example.o 

CPP_DEPS += \
./src/Automaton.d \
./src/AutomatonElement.d \
./src/Behavior.d \
./src/State.d \
./src/Transition.d \
./src/example.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/mrt/workspace/Automaton_Example/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


