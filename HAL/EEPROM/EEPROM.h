#ifndef _EEPROM_H_
#define _EEPROM_H_
#ifndef F_CPU
# define F_CPU 16000000UL
#endif
#include "../../MCAL/TWI/TWI.h"
#include "util/delay.h"

#define START_ADDRESS 0x00

void EEPROM_init();
uint8_t EEPROM_read(uint8_t address, uint16_t location);
void EEPROM_write(uint8_t address,uint16_t location,char data);
void EEPROM_read_array(uint8_t address,uint16_t location,char *arr,uint16_t arr_size);
void EEPROM_write_array(uint8_t address,uint16_t location,char *arr,uint16_t arr_size);

#endif
