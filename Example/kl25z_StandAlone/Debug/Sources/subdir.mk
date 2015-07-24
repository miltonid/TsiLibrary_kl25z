################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/main.c \
../Sources/tsi_kl25z.c 

OBJS += \
./Sources/main.o \
./Sources/tsi_kl25z.o 

C_DEPS += \
./Sources/main.d \
./Sources/tsi_kl25z.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -DDEBUG -DCPU_MKL25Z128VLK4 -DFRDM_KL25Z -DFREEDOM -I/home/milton/KSDK_1.2.0/platform/osa/inc -I/home/milton/KSDK_1.2.0/platform/utilities/inc -I/home/milton/KSDK_1.2.0/platform/CMSIS/Include -I/home/milton/KSDK_1.2.0/platform/devices -I/home/milton/KSDK_1.2.0/platform/devices/MKL25Z4/include -I/home/milton/KSDK_1.2.0/platform/devices/MKL25Z4/startup -I/home/milton/KSDK_1.2.0/platform/hal/inc -I/home/milton/KSDK_1.2.0/platform/drivers/inc -I/home/milton/KSDK_1.2.0/platform/system/inc -I../board -I"../Sources" -I/home/milton/KSDK_1.2.0/platform/drivers/src/adc16 -I/home/milton/KSDK_1.2.0/platform/drivers/src/cmp -I/home/milton/KSDK_1.2.0/platform/drivers/src/dac -I/home/milton/KSDK_1.2.0/platform/drivers/src/dma -I/home/milton/KSDK_1.2.0/platform/drivers/src/gpio -I/home/milton/KSDK_1.2.0/platform/drivers/src/i2c -I/home/milton/KSDK_1.2.0/platform/drivers/src/lpsci -I/home/milton/KSDK_1.2.0/platform/drivers/src/lptmr -I/home/milton/KSDK_1.2.0/platform/drivers/src/pit -I/home/milton/KSDK_1.2.0/platform/drivers/src/rtc -I/home/milton/KSDK_1.2.0/platform/drivers/src/spi -I/home/milton/KSDK_1.2.0/platform/drivers/src/tpm -I/home/milton/KSDK_1.2.0/platform/drivers/src/tsi -I/home/milton/KSDK_1.2.0/platform/drivers/src/uart -I/home/milton/KSDK_1.2.0/platform/drivers/src/cop -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


