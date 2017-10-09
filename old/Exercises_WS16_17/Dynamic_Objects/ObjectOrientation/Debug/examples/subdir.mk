################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../examples/example_00.c 

OBJS += \
./examples/example_00.o 

C_DEPS += \
./examples/example_00.d 


# Each subdirectory must supply rules for building sources it contributes
examples/%.o: ../examples/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/matze/shk/linux-toolchain/PLT_MRT_Eclipse_RPi_Installer_Lin/workspace/ObjectOrientation/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


