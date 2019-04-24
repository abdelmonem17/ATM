#ifndef LCD_h_
#define LCD_h_
#ifndef F_CPU
# define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#define _4bitMode
//data ports
#define LCD_DDDR DDRC
#define LCD_DPORT PORTC
#define LCD_DPIN PINC
//command ports
#define LCD_CDDR DDRC
#define LCD_CPORT PORTC
#define LCD_CPIN PINC
#define EN 3
#define RS 2
#define COLUMN_SIZE 20









void LCDIntiat();
void LCDSendCmd(uint8_t cmd);
void LCDSendChar(char data);
void LCDRowColumn(uint8_t row,uint8_t column);
void LCDPrint(char str[]);
void LCDClearScreen();


#endif
