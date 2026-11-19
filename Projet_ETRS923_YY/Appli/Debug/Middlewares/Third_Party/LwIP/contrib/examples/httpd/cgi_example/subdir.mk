################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/cgi_example.c 

OBJS += \
./Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/cgi_example.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/cgi_example.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/%.o Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/%.su Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/%.cyclo: ../Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/%.c Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -c -I../Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include -I../../LWIP/App -I../../LWIP/Target -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system/arch -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/lan8742 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-contrib-2f-examples-2f-httpd-2f-cgi_example

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-contrib-2f-examples-2f-httpd-2f-cgi_example:
	-$(RM) ./Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/cgi_example.cyclo ./Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/cgi_example.d ./Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/cgi_example.o ./Middlewares/Third_Party/LwIP/contrib/examples/httpd/cgi_example/cgi_example.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-contrib-2f-examples-2f-httpd-2f-cgi_example

