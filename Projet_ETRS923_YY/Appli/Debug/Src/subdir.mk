################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/app_freertos.c \
../Src/ia_pluie.c \
../Src/lps22df_reg.c \
../Src/main.c \
../Src/secure_nsc.c \
../Src/sht40.c \
../Src/stm32n6xx_hal_msp.c \
../Src/stm32n6xx_hal_timebase_tim.c \
../Src/stm32n6xx_it.c \
../Src/stts22h_reg.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32n6xx_s.c 

OBJS += \
./Src/app_freertos.o \
./Src/ia_pluie.o \
./Src/lps22df_reg.o \
./Src/main.o \
./Src/secure_nsc.o \
./Src/sht40.o \
./Src/stm32n6xx_hal_msp.o \
./Src/stm32n6xx_hal_timebase_tim.o \
./Src/stm32n6xx_it.o \
./Src/stts22h_reg.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32n6xx_s.o 

C_DEPS += \
./Src/app_freertos.d \
./Src/ia_pluie.d \
./Src/lps22df_reg.d \
./Src/main.d \
./Src/secure_nsc.d \
./Src/sht40.d \
./Src/stm32n6xx_hal_msp.d \
./Src/stm32n6xx_hal_timebase_tim.d \
./Src/stm32n6xx_it.d \
./Src/stts22h_reg.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32n6xx_s.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N657xx -c -I../Inc -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include -I../../Drivers/BSP/Components/lan8742 -I../LWIP/App -I../LWIP/Target -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system -I../../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/app_freertos.cyclo ./Src/app_freertos.d ./Src/app_freertos.o ./Src/app_freertos.su ./Src/ia_pluie.cyclo ./Src/ia_pluie.d ./Src/ia_pluie.o ./Src/ia_pluie.su ./Src/lps22df_reg.cyclo ./Src/lps22df_reg.d ./Src/lps22df_reg.o ./Src/lps22df_reg.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/secure_nsc.cyclo ./Src/secure_nsc.d ./Src/secure_nsc.o ./Src/secure_nsc.su ./Src/sht40.cyclo ./Src/sht40.d ./Src/sht40.o ./Src/sht40.su ./Src/stm32n6xx_hal_msp.cyclo ./Src/stm32n6xx_hal_msp.d ./Src/stm32n6xx_hal_msp.o ./Src/stm32n6xx_hal_msp.su ./Src/stm32n6xx_hal_timebase_tim.cyclo ./Src/stm32n6xx_hal_timebase_tim.d ./Src/stm32n6xx_hal_timebase_tim.o ./Src/stm32n6xx_hal_timebase_tim.su ./Src/stm32n6xx_it.cyclo ./Src/stm32n6xx_it.d ./Src/stm32n6xx_it.o ./Src/stm32n6xx_it.su ./Src/stts22h_reg.cyclo ./Src/stts22h_reg.d ./Src/stts22h_reg.o ./Src/stts22h_reg.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32n6xx_s.cyclo ./Src/system_stm32n6xx_s.d ./Src/system_stm32n6xx_s.o ./Src/system_stm32n6xx_s.su

.PHONY: clean-Src

