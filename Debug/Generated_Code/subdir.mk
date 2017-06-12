################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AD1.c \
../Generated_Code/AS1.c \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/AdcLdd1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/BitIoLdd4.c \
../Generated_Code/BitIoLdd5.c \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/FRTOS1.c \
../Generated_Code/GI2C1.c \
../Generated_Code/I2C1.c \
../Generated_Code/LED_B.c \
../Generated_Code/LED_G.c \
../Generated_Code/LED_R.c \
../Generated_Code/LEDpin1.c \
../Generated_Code/LEDpin2.c \
../Generated_Code/LEDpin3.c \
../Generated_Code/MCUC1.c \
../Generated_Code/MMA1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/SCL1.c \
../Generated_Code/SDA1.c \
../Generated_Code/TI1.c \
../Generated_Code/TSK1.c \
../Generated_Code/TU1.c \
../Generated_Code/TimerIntLdd1.c \
../Generated_Code/UTIL1.c \
../Generated_Code/Vectors.c \
../Generated_Code/WAIT1.c \
../Generated_Code/croutine.c \
../Generated_Code/event_groups.c \
../Generated_Code/heap_1.c \
../Generated_Code/heap_2.c \
../Generated_Code/heap_3.c \
../Generated_Code/heap_4.c \
../Generated_Code/heap_5.c \
../Generated_Code/list.c \
../Generated_Code/mpu_wrappers.c \
../Generated_Code/port.c \
../Generated_Code/queue.c \
../Generated_Code/tasks.c \
../Generated_Code/timers.c 

OBJS += \
./Generated_Code/AD1.o \
./Generated_Code/AS1.o \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/AdcLdd1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/BitIoLdd4.o \
./Generated_Code/BitIoLdd5.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/FRTOS1.o \
./Generated_Code/GI2C1.o \
./Generated_Code/I2C1.o \
./Generated_Code/LED_B.o \
./Generated_Code/LED_G.o \
./Generated_Code/LED_R.o \
./Generated_Code/LEDpin1.o \
./Generated_Code/LEDpin2.o \
./Generated_Code/LEDpin3.o \
./Generated_Code/MCUC1.o \
./Generated_Code/MMA1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/SCL1.o \
./Generated_Code/SDA1.o \
./Generated_Code/TI1.o \
./Generated_Code/TSK1.o \
./Generated_Code/TU1.o \
./Generated_Code/TimerIntLdd1.o \
./Generated_Code/UTIL1.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \
./Generated_Code/croutine.o \
./Generated_Code/event_groups.o \
./Generated_Code/heap_1.o \
./Generated_Code/heap_2.o \
./Generated_Code/heap_3.o \
./Generated_Code/heap_4.o \
./Generated_Code/heap_5.o \
./Generated_Code/list.o \
./Generated_Code/mpu_wrappers.o \
./Generated_Code/port.o \
./Generated_Code/queue.o \
./Generated_Code/tasks.o \
./Generated_Code/timers.o 

C_DEPS += \
./Generated_Code/AD1.d \
./Generated_Code/AS1.d \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/AdcLdd1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/BitIoLdd4.d \
./Generated_Code/BitIoLdd5.d \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/FRTOS1.d \
./Generated_Code/GI2C1.d \
./Generated_Code/I2C1.d \
./Generated_Code/LED_B.d \
./Generated_Code/LED_G.d \
./Generated_Code/LED_R.d \
./Generated_Code/LEDpin1.d \
./Generated_Code/LEDpin2.d \
./Generated_Code/LEDpin3.d \
./Generated_Code/MCUC1.d \
./Generated_Code/MMA1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/SCL1.d \
./Generated_Code/SDA1.d \
./Generated_Code/TI1.d \
./Generated_Code/TSK1.d \
./Generated_Code/TU1.d \
./Generated_Code/TimerIntLdd1.d \
./Generated_Code/UTIL1.d \
./Generated_Code/Vectors.d \
./Generated_Code/WAIT1.d \
./Generated_Code/croutine.d \
./Generated_Code/event_groups.d \
./Generated_Code/heap_1.d \
./Generated_Code/heap_2.d \
./Generated_Code/heap_3.d \
./Generated_Code/heap_4.d \
./Generated_Code/heap_5.d \
./Generated_Code/list.d \
./Generated_Code/mpu_wrappers.d \
./Generated_Code/port.d \
./Generated_Code/queue.d \
./Generated_Code/tasks.d \
./Generated_Code/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"D:/workspace.kds/monitor_frtos/Static_Code/PDD" -I"D:/workspace.kds/monitor_frtos/Static_Code/IO_Map" -I"D:/workspace.kds/monitor_frtos/Sources" -I"D:/workspace.kds/monitor_frtos/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


