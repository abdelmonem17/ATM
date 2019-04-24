#******************************************************************************
# Copyright (C) 2019 Abdelmonem Mostafa
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. 
#
#*****************************************************************************

SRCS =		./APP/main.c\
			./APP/customer/customer.c\
			./HAL/LCD/LCD.c\
			./HAL/keypad/KEYBOARD.c\
			./HAL/EEPROM/EEPROM.c\
			./LIB/string/STRING.c\
			./MCAL/TWI/TWI.c
			

INCLUDES =	\
			-I./APP/customer\
			-I./HAL/LCD\
			-I./HAL/keypad\
			-I./HAL/EEPROM\
			-I./LIB/string\
			-I./MCAL/TWI



GENERATED=	\
			./*.map \
			./*.elf\
			APP/*.d \
			APP/customer/*.d\
			HAL/LCD/*.d \
			HAL/keypad/*.d\
			HAL/EEPROM/*.d \
			LIB/string/*.d\
			MCAL/TWI*/.d\
			\
			APP/*.asm \
			APP/customer/*.asm\
			HAL/LCD/*.asm\
			HAL/keypad/*.asm\
			HAL/EEPROM/*.asm \
			LIB/string/*.asm\
			MCAL/TWI/*.asm\
			\
			APP/*.o \
			APP/customer/*.o\
			HAL/LCD/*.o \
			HAL/keypad/*.o\
			HAL/EEPROM/*.o \
			LIB/string/*.o\
			MCAL/TWI/*.o\
			\
			APP/*.i \
			APP/customer/*.i\
			HAL/LCD/*.i \
			HAL/keypad/*.i\
			HAL/EEPROM/*.i \
			LIB/string/*.i\
			MCAL/TWI/*.i
