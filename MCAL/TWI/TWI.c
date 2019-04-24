#include "TWI.h"
void TWI_master_initait()
{
	TWSR=0;
	TWBR=0x47;            //SCL =50Khz
	TWCR=(1<<TWEN);
	

}

void TWI_start_condition()
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while( !( TWCR & ( 1<<TWINT ) ) );    //polling for monitor that start condition is sent
}

void TWI_sending(uint8_t data)
{
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);     //to start sending data
	while( !( TWCR & (1<<TWINT) ) ); //waiting until data sent
	
}

uint8_t TWI_receive(uint8_t IsLast)
{
	
	if(IsLast)                   //read only one byte
		TWCR=(1<<TWINT)|(1<<TWEN);
	else                         //read more than one byte
	{			        //start receiving and after that send ACK
	TWCR=(1<<TWEA)|(TWINT);
	TWCR|=(1<<TWINT);		
	}
	while( !( TWCR & (1<<TWINT) ) );           //wait for complete
    			
	return TWDR;
	
}
void TWI_stop_condition()
{
	TWCR=TWCR=(1<<TWINT)|(1<<TWEN)| (1<<TWSTO);     //start send stop condition
	
}

void TWI_slave_initiat(uint8_t slaveAdress)
{
	slaveAdress&=~(1<<0);
	TWCR=1<<TWEN;
	TWAR=slaveAdress|isGeneralCalling ;
	
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	
}
void TWI_slave_listen()
{
	while( !( TWCR & (1<<TWINT) ) );
	
}
