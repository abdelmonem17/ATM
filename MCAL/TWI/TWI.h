/*
 * TWI.h
 *
 * Created: 1/7/2019 7:43:24 PM
 *  Author: Eng Abdo
 */ 
#ifndef TWI_H_
#define TWI_H_
#include <avr/io.h>


#define isGeneralCalling 1
#define osc 16000000
void TWI_master_initait();
void TWI_start_condition();
void TWI_stop_condition();
void TWI_slave_listen();
void TWI_slave_initiat(uint8_t slaveAdress);

void TWI_sending(uint8_t data); 
uint8_t TWI_receive(uint8_t IsLast);

#endif
