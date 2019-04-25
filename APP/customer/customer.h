/******************************************************************************
 * Copyright (C) 2019 by Abdelmonem Mostafa
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software.
 *
 *****************************************************************************/


/****************************************************************************
 * @file  customer.h
 * @brief this file includes some functions protype to manipulate customer data
 *
 * @author Abdelmonem Mostafa
 * @date 23th April 2019
 *
 ****************************************************************************/


#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include <stdlib.h>
#include <stdint.h>

#ifndef NULL
#define NULL	( (void*)0 )
#endif

#include "../../LIB/string/STRING.h"
#include "../../HAL/EEPROM/EEPROM.h"
#include "../../HAL/LCD/LCD.h"
#include "../../HAL/EEPROM/EEPROM.h"
#include "../../HAL/LCD/LCD.h"
#include "../../HAL/keypad/KEYBOARD.h"



#define DEBUG_STOP(string)   	  LCDClearScreen();\
							  	  LCDPrint(string);\
							  	  while(1)


#define CUSTOMER_DATA_SIZE 	80
#define USERNAME_SIZE 		32
#define ID_SIZE				16
#define PASSWORD_SIZE		16
#define CREDIT_SIZE			16
#define INDEX_SIZE			1

#define  WELCOME_WINDOW 	0
#define  LOG_WINDOW   		1
#define  LOGIN_WINDOW		12
#define  REGISTERATION_WINDOW    11
#define  CREDIT_WINDOW 		2
#define  DASHBOARD_WINDOW	3
#define  TRASNFER_WINDOW	4

#define IS_INIATED 			0
#define CHECKING_ADDRESS	(0x1FE0)

typedef struct
{
    char username[USERNAME_SIZE];
    char ID[ID_SIZE];
    char password[PASSWORD_SIZE];
    uint16_t credit;
}new_customer;
typedef struct Entity
{
    new_customer customer;
    struct Entity *next_customer;
    struct Entity *previous_customer;
    uint8_t index;

}new_entity;
typedef enum
{
    no_error,
    not_enough_memory_error,
    not_enough_money_error,
	not_enough_eeprom_memory,
	much_money_error,
    username_used_error,
    ID_used_error,
    username_length_error,
    ID_length_error,
    username_and_ID_error,
    logging_error,
    username_or_ID_error,

}customer_entity_error;






/****************************************************************************
*
*   @brief function log in customer account
*   this function takes username and password of the user and try to log in the database
*   @params 2 strings (username , password)
*   @return enum  (customer_entity_error)
****************************************************************************/
customer_entity_error customer_login(char *username,char *password);

/****************************************************************************
*
*   @brief function log from customer account
*   this function takes void and log out from the account and return nothing
*   @params void
*   @return void
****************************************************************************/

void customer_logout();
/****************************************************************************
*
*   @brief function makes customer to get money from his account
*   this function takes the quantity of money that customer want and print the money on LCD and return error type if there
*   @params uint16  (quantity)
*   @return enum  (customer_entity_error)
****************************************************************************/
customer_entity_error customer_take_money(uint16_t quantity);

//customer_entity_error customer_put_money(uint16_t quantity)
//customer_entity_error customer_database_index(uint8_t *pIndex);

/****************************************************************************
*
*   @brief function apply and validates customer info and save in database ,considering the bank accepted the application
*   this function takes customer info , 3 strings (username,password,ID)  and uint16t (credit) and return error if there is
*   @params  3 strings (username,password,ID)  and uint16t (credit)
*   @return enum  (customer_entity_error)
****************************************************************************/
customer_entity_error customer_new(char *username,char *password,char *ID,uint16_t _credit);

/****************************************************************************
*
*   @brief function initiates customers' database
*   this function takes void and init database
*   @params void
*   @return void
****************************************************************************/

void customer_init();
/****************************************************************************
*
*   @brief function prints welcome massage
*   this function takes void and init database
*   @params void
*   @return void
****************************************************************************/

/****************************************************************************
*
*   @brief function prints welcome massage
*   this function takes void and init database
*   @params void
*   @return void
****************************************************************************/
void customer_welcome();

/****************************************************************************
*
*   @brief function scan the keyboard for customer info to to in his account
*   this function takes void and try to log in customer account
*   @params void
*   @return void
****************************************************************************/
void customer_log();

/****************************************************************************
*
*   @brief function scans the keyboard for customer option
*   this function takes void and return customer option
*   @params void
*   @return char  (option)
****************************************************************************/
char customer_readOption();


/****************************************************************************
*
*   @brief function validate customer info to manage him to log his account
*   this function takes void and validates customer info and return uint8_t according the validation
*   @params void
*   @return uint8_t
****************************************************************************/
uint8_t customer_validate_login();

/****************************************************************************
*
*   @brief function scans the keyboard for customer info and validate it to apply for a new card
*   this function takes void and validates entered customer info
*   @params void
*   @return void
****************************************************************************/
uint8_t customer_card_apply();
/****************************************************************************
*
*   @brief function shows dashboard control and scans the keyboard for option
*   this function takes void and show the dashboard
*   @params void
*   @return void
****************************************************************************/
uint8_t customer_dashboard();
#endif // _CUSTOMER_H_
