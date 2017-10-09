################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/dog.c \
../src/human.c \
../src/linlist.c \
../src/linlist_elem.c \
../src/mamal.c 

OBJS += \
./src/dog.o \
./src/human.o \
./src/linlist.o \
./src/linlist_elem.o \
./src/mamal.o 

C_DEPS += \
./src/dog.d \
./src/human.d \
./src/linlist.d \
./src/linlist_elem.d \
./src/mamal.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/matze/shk/linux-toolchain/PLT_MRT_Eclipse_RPi_Installer_Lin/workspace/ObjectOrientation/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


