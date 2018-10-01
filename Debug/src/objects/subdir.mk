################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/objects/Character.cpp \
../src/objects/Cube.cpp \
../src/objects/LightObject.cpp \
../src/objects/Object.cpp \
../src/objects/Sun.cpp \
../src/objects/Token.cpp 

OBJS += \
./src/objects/Character.o \
./src/objects/Cube.o \
./src/objects/LightObject.o \
./src/objects/Object.o \
./src/objects/Sun.o \
./src/objects/Token.o 

CPP_DEPS += \
./src/objects/Character.d \
./src/objects/Cube.d \
./src/objects/LightObject.d \
./src/objects/Object.d \
./src/objects/Sun.d \
./src/objects/Token.d 


# Each subdirectory must supply rules for building sources it contributes
src/objects/%.o: ../src/objects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -o  "$@" "$<" -std=c++0x -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0  -lGLU -lGL -lglut -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"
	@echo 'Finished building: $<'
	@echo ' '


