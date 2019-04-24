/****************************************************************************
 * @file  customer.h
 * @brief this file includes some functions protype to manipulate customer data
 *
 * @author Abdelmonem Mostafa
 * @date 23th April 2019
 *
 ****************************************************************************/
#include "customer.h"




/****************************************************************************
*
*   @brief function applys and validates customer info and save in database and in linkedlist data structure
*   this function takes customer info , 3 strings (username,password,ID)  and uint16t (credit) and return error if there is
*   @params  3 strings (username,password,ID)  and uint16t (credit)
*   @return enum  (customer_entity_error)
****************************************************************************/
static customer_entity_error customer_registeration(char *username,char *password,char *ID,uint16_t money);

/****************************************************************************
*
*   @brief function validates customer info and save in database and in linkedlist data structure
*   this function takes customer info , 3 strings (username,password,ID)  return error if there is
*   @params  3 strings (username,password,ID)
*   @return enum  (customer_entity_error)
****************************************************************************/
static customer_entity_error customer_info_error(char *username,char *password,char *ID);

/****************************************************************************
*
*   @brief function creat customer structure and save it in linkedlist data structure
*   this function takes customer info , 3 strings (username,password,ID) and pointer to enum (PError)  return customer structure if no error
*   @params  3 strings (username,password,ID)
*   @return enum  (customer_entity_error)
****************************************************************************/
static new_entity * create_customer_entity(char *username,char *password,char *ID,uint16_t money,customer_entity_error *pError);

/****************************************************************************
*
*   @brief function return current customer name and credit
*   this function takes string (username) and pointer to uint16_t (pCredit) to change their values
*   @params  string (username) and pointer to uint16_t (pCredit)
*   @return enum  (customer_entity_error)
****************************************************************************/
static customer_entity_error  customer_info(char *username,uint16_t *pCredit);


/****************************************************************************
*
*   @brief function format the entered money and print in in LCD
*   this function takes money as uint16_t (quantity) to format it
*   @params  uint16_t (quantity)
*   @return void
****************************************************************************/
static void money_format(uint16_t quantity);

/****************************************************************************
*
*   @brief function load database from EEPROM to the RAM to make it faster to manipulate the data
*   this function takes void and cashing the data from external ROM
*   @params  void
*   @return  void
****************************************************************************/
static void customer_cashing();


static new_entity * PFirst_customer_entity=NULL;
static new_entity * PLast_customer_entity=NULL;
static new_entity * PCurrent_customer_entity=NULL;
static uint8_t Index=0;
static char _customer_number=0;

static new_entity *create_customer_entity(char *username,char *password,char *ID,uint16_t money,customer_entity_error *pError)
{
    new_entity *pCustomer_entity=(new_entity*) malloc(sizeof(new_entity));
    *pError=customer_info_error(username,password,ID);
    if( *pError )
    {
        //printf("\n\"error id is %d\"",*pError);
        return 0;
    }
    else {


        if(pCustomer_entity  )
        {
            str_copy(pCustomer_entity->customer.username , username);
            str_copy(pCustomer_entity->customer.ID , ID );
            str_copy(pCustomer_entity->customer.password,password);
            pCustomer_entity->customer.credit=money;
            pCustomer_entity->index=Index++;
            pCustomer_entity->next_customer=pCustomer_entity->previous_customer=NULL;
            return pCustomer_entity;
        }
        else
        {
           *pError=not_enough_memory_error;
            return 0;
        }
    }

}
static customer_entity_error customer_info_error(char *username,char *password,char*ID)
{   new_entity *pCustmer_entity=PFirst_customer_entity;

    if(str_len(username) > 19 || str_len(username)<8 || str_len(password) !=8  || str_len(ID)!=14)
    {
    	LCDClearScreen();
        LCDPrint("please type username with 8 char as min length and id 14 char and PW must be 8 char");
        _delay_ms(2000);
        LCDClearScreen();
        return username_or_ID_error;
    }
    else
    {

    while(pCustmer_entity)
    {
        if( str_equal(pCustmer_entity->customer.username , username)  )
        {
        	LCDClearScreen();
            LCDPrint("\nfail to register please type different username");
            _delay_ms(2000);
            LCDClearScreen();
            return username_used_error;
        }
        if( str_equal(pCustmer_entity->customer.ID , ID)  )
        {
        	LCDClearScreen();
            LCDPrint("\nfail to register please type different ID");
            _delay_ms(2000);
            LCDClearScreen();
            return ID_used_error;
         }

        pCustmer_entity=pCustmer_entity->next_customer;

    }

    return no_error;
    }
}
static customer_entity_error customer_registeration(char *username,char *password,char *ID,uint16_t money)
{
    customer_entity_error customer_error;
    new_entity *pCustomer_entity=create_customer_entity(username,password,ID,money,&customer_error);
    if(!customer_error)
    {

       if(PFirst_customer_entity==NULL)
       {
           PFirst_customer_entity=PLast_customer_entity=pCustomer_entity;
       }
       else
       {
           pCustomer_entity->previous_customer=PLast_customer_entity;
           PLast_customer_entity->next_customer=pCustomer_entity;
           PLast_customer_entity=pCustomer_entity;
       }
    }
    else
    {
        //nothing
    }
    return customer_error;
}

customer_entity_error customer_new(char *username,char *password,char *ID,uint16_t _credit)
{
	char credit[4]={0};
	credit[0]=_credit>>8;
	credit[1]=_credit;
	char arr[2];
	arr[0]=IS_INIATED;
	customer_entity_error error;

	if(_customer_number==200)
	{
		error=not_enough_eeprom_memory;
		LCDClearScreen();
		LCDPrint("sorry you can't apply for new card at this time");
		_delay_ms(5000);
		  LCDClearScreen();
	}
	else
	{
			error=customer_registeration(username ,password,ID,6675);

		if(error==no_error)
		{
			EEPROM_write_array(0xA0,(Index-1)*CUSTOMER_DATA_SIZE+ START_ADDRESS, username,USERNAME_SIZE);
			EEPROM_write_array(0xA0,(Index-1)*CUSTOMER_DATA_SIZE+START_ADDRESS+USERNAME_SIZE, password,PASSWORD_SIZE);
			EEPROM_write_array(0xA0,(Index-1)*CUSTOMER_DATA_SIZE+START_ADDRESS+USERNAME_SIZE+PASSWORD_SIZE,ID,ID_SIZE);
			EEPROM_write_array(0xA0,(Index-1)*CUSTOMER_DATA_SIZE+START_ADDRESS+USERNAME_SIZE+PASSWORD_SIZE+ID_SIZE,credit, CREDIT_SIZE);
			arr[1]=++_customer_number;
			EEPROM_write_array(0xA0,0x1FE0,arr,16);
		}
		else
		{
			LCDClearScreen();
			LCDPrint("error in registeration try again");
			_delay_ms(2000);
			  LCDClearScreen();

		}
	}
	return error;
}


customer_entity_error customer_login(char *username,char *password)
{
    new_entity *pCustomer_entity=PFirst_customer_entity;
    while(pCustomer_entity)
    {
        if( str_equal(pCustomer_entity->customer.password , password) && str_equal(pCustomer_entity->customer.username , username) )
        {
            PCurrent_customer_entity=pCustomer_entity;
            return no_error;
        }
        pCustomer_entity=pCustomer_entity->next_customer;
    }
    LCDClearScreen();
    LCDPrint("fail to login please try again");
    _delay_ms(2000);
    LCDClearScreen();
    return username_or_ID_error;
}
void customer_logout()
{
    PCurrent_customer_entity=NULL;
}
customer_entity_error customer_take_money(uint16_t quantity)
{
	char credit[3];

    if(PCurrent_customer_entity)
    {
    	if(quantity < 1990)
    	{

			if(PCurrent_customer_entity->customer.credit >= quantity)
			{


				money_format(quantity);
				PCurrent_customer_entity->customer.credit-=quantity;	//update cashed database
																		//update eeprom database
				credit[0]=PCurrent_customer_entity->customer.credit >> 8;
				credit[1]=PCurrent_customer_entity->customer.credit;
				EEPROM_write_array(0xA0, (PCurrent_customer_entity->index) * CUSTOMER_DATA_SIZE+START_ADDRESS+USERNAME_SIZE+PASSWORD_SIZE+ID_SIZE ,credit,16);

				return no_error;
			}
			else
			{
				
				LCDClearScreen();
				LCDPrint("sorry you don't have enought money so please enter number less than :");
				_delay_ms(3000);
				LCDClearScreen();
				
				return not_enough_money_error;
			}
    	}
    	else
    	{
			LCDClearScreen();
			LCDPrint("sorry you cat't take money more 1989");
			_delay_ms(3000);
			LCDClearScreen();
			return much_money_error;
    	}
    }
    else
    {
        //printf("\nplease log in first");
    	LCDClearScreen();
    	LCDPrint("please log in first");
    	_delay_ms(3000);
    	LCDClearScreen();
        return logging_error;
    }

}
static void money_format(uint16_t quantity)
{
    uint8_t money_class[7]={1,5,10,20,50,100,200};

    int8_t start=0,size=0;
    char money_save[7];






    	for(int8_t i =6; i >= 0 ;i--)
    	{

    		if(quantity >= money_class[i])
    		{
    			money_save[i]=quantity/money_class[i] +0x30;
    			quantity%=money_class[i];
    			start= start  > i ? start :i;
    			size=size > (start-i+1) ? size : (start-i+1);
    		}
    		else
    			money_save[i]='0';

    	}



    	LCDClearScreen();
    	LCDPrint("your money :");
    	LCDRowColumn(2,1);

    	while( size -- )
    	{
    		LCDSendChar(money_save[start]);
    		LCDSendChar('X');
    		LCDPrint(  intToString(money_class[start--]) );
    		LCDPrint("LE,");


    	}
    	_delay_ms(10000);
    	_delay_ms(10000);
    	LCDClearScreen();


}
/*
inline customer_entity_error customer_put_money(uint16_t quantity)
{
    if(PCurrent_customer_entity)
    {
        PCurrent_customer_entity->customer.credit+=quantity;
        return no_error;
    }
    else
    {
        //printf("\nlog in first");
        return logging_error;
    }
}*/
inline void customer_init()
{
	LCDIntiat();
	keyboardIntiat();
	EEPROM_init();

	if(EEPROM_read(0xA0,0x1FE0) !=IS_INIATED)
	{

																				//iniat the database

		customer_new("Abdelmonem Mostafa0" ,"12345678","01234567811120",0x3132);
		customer_new("Abdelmonem Mostafa1" ,"12345678","01234567811121",0x3132);
		customer_new("Abdelmonem Mostafa2" ,"12345678","01234567811122",0x3132);
		customer_new("Abdelmonem Mostafa3" ,"12345678","01234567811123",0x3132);
		customer_new("Abdelmonem Mostafa4" ,"12345678","01234567811124",0x3132);
		customer_new("Abdelmonem Mostafa5" ,"12345678","01234567811125",0x3132);
		customer_new("ABC0123456780" ,"12345678","01234567811130",0x3132);
		customer_new("ABC0123456781" ,"12345678","01234567811131",0x3132);

		customer_new("12345678" ,"12345678","01234567811166",0x3132);
		
	}
	else
	{
		customer_cashing();
	}
}
inline static  void customer_cashing()
{
	    char customer_number;
	    char username[20];
	    char password[9];
	    char ID[15];
	    char credit[3];
	    customer_number=_customer_number=EEPROM_read(0xA0,0x1FE1);
		for(uint8_t i=0;i<customer_number;++i)
		{
			EEPROM_read_array(0xA0,i*CUSTOMER_DATA_SIZE+START_ADDRESS,username,20);
			EEPROM_read_array(0xA0,i*CUSTOMER_DATA_SIZE+START_ADDRESS+USERNAME_SIZE,					   password,9);
			EEPROM_read_array(0xA0,i*CUSTOMER_DATA_SIZE+START_ADDRESS+USERNAME_SIZE+PASSWORD_SIZE, 			ID,15);
			EEPROM_read_array(0xA0,i*CUSTOMER_DATA_SIZE+START_ADDRESS+USERNAME_SIZE+PASSWORD_SIZE+ID_SIZE ,credit,2);
			customer_registeration(username,password,ID, ( (credit[0]<<8) +credit[1] )   );
		}


}

/*
customer_entity_error customer_database_index(uint8_t *pIndex)
{
    if(PCurrent_customer_entity)
    {
       *pIndex=PCurrent_customer_entity->index;
       return no_error;
    }
    else
    {
    	LCDClearScreen();
          LCDPrint("log in first");
        return logging_error;
    }
}*/

inline void customer_welcome()
{

	LCDClearScreen();
	LCDRowColumn(1,1);
	LCDPrint("Welcome @ ATM system = : go , on : back  ");
	LCDPrint("please press any   button to continue..");
	keyboardScan();
	LCDClearScreen();
}
inline void customer_log()
{
	LCDClearScreen();
	LCDRowColumn(1,1);
	LCDPrint("options press 1 or 2");
	LCDRowColumn(2,1);
	LCDPrint("1-apply for card");
	LCDRowColumn(3,1);
	LCDPrint("2-log in");

}
inline char customer_readOption()
{
	char option;
	do
	{
		option= keyboardScan();
	}
	while(option !='1' && option !='2');
	LCDClearScreen();
	return  option ;
}
inline uint8_t customer_validate_login()
{
	char username[20];
	char password[10];
	customer_entity_error error;
	uint8_t i=0;
    LCDRowColumn(1,6);
	LCDPrint("username");
	LCDRowColumn(3,6);
	LCDPrint("password");

	LCDRowColumn(2,1);
	while( ( username[i]=keyboardScan() ) !='>' )
	{
		if(username[i] !='<')
			LCDSendChar(username[i++]);
		else
			return LOG_WINDOW;

	}
	username[i]='\0';

	i=0;
	LCDRowColumn(4,1);
	while( ( password[i]=keyboardScan() ) !='>' )
	{
		if(username[i++] !='<')
			LCDSendChar('*');
		else
			return LOG_WINDOW;

	}

	password[i]='\0';
	/*LCDClearScreen();
	LCDPrint(username);
	LCDRowColumn(2,1);
	LCDPrint(password);
	while(1);*/
	error= customer_login(username,password);
	if(error == no_error)
	{
		return DASHBOARD_WINDOW ;
	}
	else
	{
		//try again
		return LOGIN_WINDOW;
	}
}
inline uint8_t customer_card_apply()
{

	char username[20] ;char password[10] ;char ID[16] ;uint16_t credit=0;
	customer_entity_error error;
	uint8_t i=0;
	char ch;
    LCDRowColumn(1,1);
	LCDPrint("username");
	LCDRowColumn(3,1);
	LCDPrint("password");
	LCDRowColumn(2,1);
	while( ( username[i]=keyboardScan() ) !='>' )
	{
		if(username[i] !='<')
			LCDSendChar(username[i++]);
		else
			return LOG_WINDOW;


	}
	username[i]='\0';

	i=0;
	LCDRowColumn(4,1);
	while( ( password[i]=keyboardScan() ) !='>' )
	{

		if(password[i++] !='<')
			LCDSendChar('*');
		else
			return LOG_WINDOW;


	}

	password[i]='\0';
	LCDClearScreen();


    LCDRowColumn(1,1);
	LCDPrint("ID");
	LCDRowColumn(3,1);
	LCDPrint("credit");
	LCDRowColumn(2,1);

	i=0;
	while( ( ID[i]=keyboardScan() ) !='>' )
	{
		if(ID[i] !='<')
			LCDSendChar(ID[i++]);
		else
			return LOG_WINDOW;

	}
	ID[i]='\0';

	i=0;
	LCDRowColumn(4,1);
	while( ( (ch=keyboardScan() ) !='>' ) && (i < 5) )
	{

		if(ch !='<')
			credit=(ch-0x30)+(credit*10);
		else
			return LOG_WINDOW;

		i++;
		LCDSendChar(ch);
	}



	error= customer_new(username,password,ID,credit);
	if(error == no_error)
	{

		LCDClearScreen();
		LCDPrint("successful app...");
		_delay_ms(3000);
		return LOG_WINDOW ;
	}
	else
	{
		//try again
		return REGISTERATION_WINDOW;
	}
}
static inline customer_entity_error  customer_info(char *username,uint16_t *pCredit)
{
	if(PCurrent_customer_entity)
	{
		*pCredit= PCurrent_customer_entity->customer.credit;
		 str_copy(username, PCurrent_customer_entity->customer.username);
		 return no_error;
	}
	else
	{
		LCDClearScreen();
		LCDPrint("please log in first");
		return logging_error;
	}

}
inline uint8_t customer_dashboard()
{
	char username[20];
	char *str;
	uint16_t money_amount;
	//uint16_t money=0;
	uint8_t i=0;
	customer_entity_error error;
	char key;

	error=customer_info(username,&money_amount);
	if(error==no_error)
	{
		str=intToString(money_amount);
		LCDClearScreen();
		LCDPrint(username);
		LCDRowColumn(2,1);
		LCDPrint( str );
		LCDPrint(" LE");
        LCDRowColumn(3,1);
		LCDPrint("3- to get money");
		LCDRowColumn(4,1);
        LCDPrint("0- logout");
        do
        {
        	key=keyboardScan();
        }while(key !='3' && key !='0');

        if(key=='3')
        {
        	LCDClearScreen();
        	LCDPrint("Enter the amount:");
        	LCDRowColumn(2,1);
        	money_amount=0;
        	while( ( (key=keyboardScan() ) !='>' ) && (i < 4)  )
        	{

        		if(key !='<')
        			money_amount=(key-0x30)+(money_amount*10);
        		else
        			return DASHBOARD_WINDOW;

        		LCDSendChar(key);
        		i++;
        	}
        	customer_take_money(money_amount);
        	return DASHBOARD_WINDOW;

        }
        else
        {
        	customer_logout();
        	return LOG_WINDOW;
        }

	}

	return LOGIN_WINDOW;

}

