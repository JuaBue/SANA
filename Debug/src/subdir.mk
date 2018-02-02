################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/logging.c \
../src/qmain.c 

OBJS += \
./src/logging.o \
./src/qmain.o 

C_DEPS += \
./src/logging.d \
./src/qmain.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -I"C:\Users\juan.bueno\Desktop\SIEMENS\SANA\src\Includes" -I"C:\Users\juan.bueno\Desktop\SIEMENS\SANA\src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


