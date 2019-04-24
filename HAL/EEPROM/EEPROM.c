/*
 * EEPROM.c
 *
 *  Created on: Apr 19, 2019
 *      Author: Eng Abdo
 */
#include "EEPROM.h"

//static int _written_data=0;

inline void EEPROM_init()
{
	TWI_master_initait();

}
void EEPROM_write(uint8_t address,uint16_t location,char data)
{

		TWI_start_condition();
		TWI_sending( (address & 0xFE)  );
		TWI_sending( (location>>8) );
		TWI_sending( location );

	    TWI_sending(data);
        TWI_stop_condition();
        _delay_ms(10);

}

uint8_t EEPROM_read(uint8_t address, uint16_t location)
{

		 TWI_start_condition();
		 TWI_sending( (address & 0xFE)  );
		 TWI_sending( (location>>8) );
		 TWI_sending( location );
		 TWI_start_condition();
		 TWI_sending( (address | 0x01)  );
	     return TWI_receive(1);
}
void EEPROM_write_array(uint8_t address,uint16_t location,char *arr,uint16_t arr_size)
{
	    uint16_t written_data=16;
		TWI_start_condition();
		TWI_sending( (address & 0xFE)  );
		TWI_sending( (location>>8) );
		TWI_sending( location );

		for(uint16_t i=0;i<arr_size;i++)
		{

			if(i < written_data  )
				TWI_sending(arr[i]);
			else
			{

				TWI_stop_condition();
				_delay_ms(15);
				written_data+=16;
				location+=16;
				TWI_start_condition();
				TWI_sending( (address & 0xFE)  );
				TWI_sending( (location>>8) );
				TWI_sending( location );
				TWI_sending(arr[i]);

			}
		}
		TWI_stop_condition();
		_delay_ms(15);

}
void EEPROM_read_array(uint8_t address,uint16_t location,char *arr,uint16_t arr_size)
{

		TWI_start_condition();
        TWI_sending( (address & 0xFE)  );
		TWI_sending( (location>>8) );
		TWI_sending( location );
		TWI_start_condition();
		TWI_sending( (address | 0x01)  );

		for(uint16_t i=0;i<arr_size;i++)
		{


				arr[i]=TWI_receive(i+1==arr_size);


		}

}

