################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/model_pregenerated/ua_light_namespaceinit_generated.c 

OBJS += \
./include/model_pregenerated/ua_light_namespaceinit_generated.o 

C_DEPS += \
./include/model_pregenerated/ua_light_namespaceinit_generated.d 


# Each subdirectory must supply rules for building sources it contributes
include/model_pregenerated/%.o: ../include/model_pregenerated/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -DUA_NO_AMALGAMATION -I"/home/mrt/workspace/UA_Lights/include/Automaton" -I"/home/mrt/workspace/UA_Lights/include" -I"/home/mrt/workspace/UA_Lights/include/open62541/deps" -I"/home/mrt/workspace/UA_Lights/include/open62541/src" -I"/home/mrt/workspace/UA_Lights/include/open62541/src/server" -I"/home/mrt/workspace/UA_Lights/include/Automaton" -I"/home/mrt/workspace/UA_Lights/include/model_pregenerated" -I"/home/mrt/workspace/UA_Lights/include/open62541" -I"/home/mrt/workspace/UA_Lights/include/TrafficLight" -I"/home/mrt/workspace/UA_Lights/include/ua_mapped_class" -I"/home/mrt/workspace/UA_Lights/include/model_pregenerated" -I"/home/mrt/workspace/UA_Lights/include/open62541" -I"/home/mrt/workspace/UA_Lights/include/TrafficLight" -I"/home/mrt/workspace/UA_Lights/include/ua_mapped_class" -I"/home/mrt/workspace/UA_Lights/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


