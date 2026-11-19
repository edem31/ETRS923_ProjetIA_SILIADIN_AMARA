################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Workspace/Projet_ETRS923_YY/Middlewares/Third_Party/LwIP/contrib/apps/chargen/chargen.c 

OBJS += \
./Middlewares/LwIP/contrib/apps/chargen/chargen.o 

C_DEPS += \
./Middlewares/LwIP/contrib/apps/chargen/chargen.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/LwIP/contrib/apps/chargen/chargen.o: C:/Workspace/Projet_ETRS923_YY/Middlewares/Third_Party/LwIP/contrib/apps/chargen/chargen.c Middlewares/LwIP/contrib/apps/chargen/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -c -I../Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include -I../../Drivers/BSP/Components/lan8742 -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system -I../../Middlewares/Third_Party/LwIP/system/arch -I../LWIP/App -I../LWIP/Target -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-LwIP-2f-contrib-2f-apps-2f-chargen

clean-Middlewares-2f-LwIP-2f-contrib-2f-apps-2f-chargen:
	-$(RM) ./Middlewares/LwIP/contrib/apps/chargen/chargen.cyclo ./Middlewares/LwIP/contrib/apps/chargen/chargen.d ./Middlewares/LwIP/contrib/apps/chargen/chargen.o ./Middlewares/LwIP/contrib/apps/chargen/chargen.su

.PHONY: clean-Middlewares-2f-LwIP-2f-contrib-2f-apps-2f-chargen

