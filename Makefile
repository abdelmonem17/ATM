#******************************************************************************
# Copyright (C) 2019 by Abdelmonem Mostafa
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Makefile for host or ATMEGA32 embedded system platform.
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      <FILE>.i - Builds <FILE>.i preprocessed output file
#      <FILE>.asm - Builds <FILE>.asm assembly output file and final executable
#      <FILE>.o - Builds <FILE>.o object file
#      compile-all - Compile all object files, but does not link
#      build - Builds and links all source files
#      clean - Removes all generated files
#
# Platform Overrides:
#      PLATFORM - Target platform (HOST or ATMEGA32)
#
#------------------------------------------------------------------------------


include sources.mk

PLATFORM=ATMEGA32
TARGET=ATM

ifeq ($(PLATFORM),ATMEGA32)
	# Arcitectures spacific flags
	
	CPU=atmega32
	GNU=avr
	# Compiler flags
	CC=$(GNU)-gcc
	CFLAGS=-Wall -Werror -g -O3 -std=c99 \
			-mmcu=$(CPU)
	#Linker flags
	LD=$(GNU)-ld
	LDFLAGS=-Wl,-Map=$(TARGET).map
	
	CPPFLAGS=$(INCLUDES) -DVERBOSE
	

else
	GNU=
	CC=$(GNU)-gcc
	CFLAGS=-Wall -Werror -g -O0 -std=c99 
	LDFLAGS=-Wl,-Map=$(TARGET).map
	ifeq ($(PLATFORM),HOST)
		CPPFLAGS=-DHOST -DVERBOSE 
	endif
endif


size_info=$(GNU)-size

OBJS=$(SRCS:.c=.o)


%.i:%.c
	$(CC) -E $(CPPFLAGS) $(CFLAGS) $< -o $@

%.asm:%.c
	$(CC) -S $(CPPFLAGS) $(CFLAGS) $< -o $@

%.o:%.c
	$(CC) -c $(CPPFLAGS)  $(CFLAGS)  $< -o $@  
%.d:%.c
	$(CC) -MM $(CPPFLAGS) $(CFLAGS)  $*.c -o $*.d

.PHONEY:build
build:all
.PHONEY:all
all:$(TARGET).elf
$(TARGET).elf:$(OBJS)
	$(CC) $(OBJS) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) $(LDFLAGS) -o $@
	$(size_info) -Atd $(TARGET).elf
	$(size_info) -Btd $(TARGET).elf
	$(size_info) -Btd $(OBJS)



.PHONEY:clean
clean:
	rm -f   $(GENERATED)
