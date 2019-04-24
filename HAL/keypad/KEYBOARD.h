#ifndef KEYBOARD_h_
#define KEYBOARD_h_

#include <avr/io.h>
#ifndef F_CPU
# define F_CPU 16000000UL
#endif
#include <util/delay.h>

#define keyboardDDR 	DDRD
#define KeyboardPORT 	PORTD
#define keyboardPIN 	PIND

void keyboardIntiat();
uint8_t keyboardScan();




#endif
