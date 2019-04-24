#include <avr/io.h>
#include "customer/customer.h"



int main()
{





uint8_t window=WELCOME_WINDOW;

customer_init();
customer_welcome();
window=LOG_WINDOW;








while(1)
{
	if(window==LOG_WINDOW)
	{
		customer_log();


		window= customer_readOption() == '1' ? REGISTERATION_WINDOW : LOGIN_WINDOW;
	}
	else if(window==LOGIN_WINDOW)
	{
		window=customer_validate_login();

	}
	else if (window==REGISTERATION_WINDOW)
	{
      window= customer_card_apply();

	}
	else if(window ==DASHBOARD_WINDOW)
	{
		window=customer_dashboard();

	}

}

return 0;
}

