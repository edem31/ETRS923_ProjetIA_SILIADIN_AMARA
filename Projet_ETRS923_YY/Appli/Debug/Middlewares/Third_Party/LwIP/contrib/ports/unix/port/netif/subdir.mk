################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/fifo.c \
../Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/list.c \
../Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/pcapif.c \
../Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/sio.c \
../Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/tapif.c \
../Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/vdeif.c 

OBJS += \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/fifo.o \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/list.o \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/pcapif.o \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/sio.o \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/tapif.o \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/vdeif.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/fifo.d \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/list.d \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/pcapif.d \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/sio.d \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/tapif.d \
./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/vdeif.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/%.o Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/%.su Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/%.cyclo: ../Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/%.c Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -c -I../Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include -I../../LWIP/App -I../../LWIP/Target -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system/arch -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/BSP/lan8742 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-contrib-2f-ports-2f-unix-2f-port-2f-netif

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-contrib-2f-ports-2f-unix-2f-port-2f-netif:
	-$(RM) ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/fifo.cyclo ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/fifo.d ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/fifo.o ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/fifo.su ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/list.cyclo ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/list.d ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/list.o ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/list.su ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/pcapif.cyclo ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/pcapif.d ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/pcapif.o ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/pcapif.su ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/sio.cyclo ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/sio.d ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/sio.o ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/sio.su ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/tapif.cyclo ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/tapif.d ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/tapif.o ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/tapif.su ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/vdeif.cyclo ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/vdeif.d ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/vdeif.o ./Middlewares/Third_Party/LwIP/contrib/ports/unix/port/netif/vdeif.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-contrib-2f-ports-2f-unix-2f-port-2f-netif

