################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GraphicsHw2.cpp \
../src/World.cpp 

OBJS += \
./src/GraphicsHw2.o \
./src/World.o 

CPP_DEPS += \
./src/GraphicsHw2.d \
./src/World.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -o  "$@" "$<" -std=c++0x -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0  -lGLU -lGL -lglut -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"
	@echo 'Finished building: $<'
	@echo ' '


