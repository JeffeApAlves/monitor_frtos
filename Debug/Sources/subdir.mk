################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/RingBuffer.c \
../Sources/application.c \
../Sources/frtos_tasks.c \
../Sources/main.c \
../Sources/protocol.c \
../Sources/utils.c 

OBJS += \
./Sources/Events.o \
./Sources/RingBuffer.o \
./Sources/application.o \
./Sources/frtos_tasks.o \
./Sources/main.o \
./Sources/protocol.o \
./Sources/utils.o 

C_DEPS += \
./Sources/Events.d \
./Sources/RingBuffer.d \
./Sources/application.d \
./Sources/frtos_tasks.d \
./Sources/main.d \
./Sources/protocol.d \
./Sources/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:/workspace.kds/monitor_frtos/Static_Code/PDD" -I"D:/workspace.kds/monitor_frtos/Static_Code/IO_Map" -I"D:/workspace.kds/monitor_frtos/Sources" -I"D:/workspace.kds/monitor_frtos/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


