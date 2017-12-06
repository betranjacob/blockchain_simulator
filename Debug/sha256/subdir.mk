################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sha256/sha256.cpp 

OBJS += \
./sha256/sha256.o 

CPP_DEPS += \
./sha256/sha256.d 


# Each subdirectory must supply rules for building sources it contributes
sha256/%.o: ../sha256/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -std=c++1y -I"/home/betran/workspace/block_chain_simulator/sha256" -I"/home/betran/workspace/block_chain_simulator/chilkat" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


