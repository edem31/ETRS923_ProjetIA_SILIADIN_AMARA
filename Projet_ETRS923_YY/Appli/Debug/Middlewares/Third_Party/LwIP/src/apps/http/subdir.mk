################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/apps/http/altcp_proxyconnect.c \
../Middlewares/Third_Party/LwIP/src/apps/http/fs.c \
../Middlewares/Third_Party/LwIP/src/apps/http/fsdata.c \
../Middlewares/Third_Party/LwIP/src/apps/http/http_client.c \
../Middlewares/Third_Party/LwIP/src/apps/http/httpd.c 

OBJS += \
./Middlewares/Third_Party/LwIP/src/apps/http/altcp_proxyconnect.o \
./Middlewares/Third_Party/LwIP/src/apps/http/fs.o \
./Middlewares/Third_Party/LwIP/src/apps/http/fsdata.o \
./Middlewares/Third_Party/LwIP/src/apps/http/http_client.o \
./Middlewares/Third_Party/LwIP/src/apps/http/httpd.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/apps/http/altcp_proxyconnect.d \
./Middlewares/Third_Party/LwIP/src/apps/http/fs.d \
./Middlewares/Third_Party/LwIP/src/apps/http/fsdata.d \
./Middlewares/Third_Party/LwIP/src/apps/http/http_client.d \
./Middlewares/Third_Party/LwIP/src/apps/http/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/apps/http/%.o Middlewares/Third_Party/LwIP/src/apps/http/%.su Middlewares/Third_Party/LwIP/src/apps/http/%.cyclo: ../Middlewares/Third_Party/LwIP/src/apps/http/%.c Middlewares/Third_Party/LwIP/src/apps/http/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -c -I../Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include -I../../LWIP/App -I../../LWIP/Target -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system/arch -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/lan8742 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-apps-2f-http

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-apps-2f-http:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/apps/http/altcp_proxyconnect.cyclo ./Middlewares/Third_Party/LwIP/src/apps/http/altcp_proxyconnect.d ./Middlewares/Third_Party/LwIP/src/apps/http/altcp_proxyconnect.o ./Middlewares/Third_Party/LwIP/src/apps/http/altcp_proxyconnect.su ./Middlewares/Third_Party/LwIP/src/apps/http/fs.cyclo ./Middlewares/Third_Party/LwIP/src/apps/http/fs.d ./Middlewares/Third_Party/LwIP/src/apps/http/fs.o ./Middlewares/Third_Party/LwIP/src/apps/http/fs.su ./Middlewares/Third_Party/LwIP/src/apps/http/fsdata.cyclo ./Middlewares/Third_Party/LwIP/src/apps/http/fsdata.d ./Middlewares/Third_Party/LwIP/src/apps/http/fsdata.o ./Middlewares/Third_Party/LwIP/src/apps/http/fsdata.su ./Middlewares/Third_Party/LwIP/src/apps/http/http_client.cyclo ./Middlewares/Third_Party/LwIP/src/apps/http/http_client.d ./Middlewares/Third_Party/LwIP/src/apps/http/http_client.o ./Middlewares/Third_Party/LwIP/src/apps/http/http_client.su ./Middlewares/Third_Party/LwIP/src/apps/http/httpd.cyclo ./Middlewares/Third_Party/LwIP/src/apps/http/httpd.d ./Middlewares/Third_Party/LwIP/src/apps/http/httpd.o ./Middlewares/Third_Party/LwIP/src/apps/http/httpd.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-apps-2f-http

