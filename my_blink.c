#include "ch32fun.h"

#define PIN_ME PA1

int main()
{
	SystemInit();

	funGpioInitAll(); // Enable GPIOs
	
	funPinMode( PIN_ME,     GPIO_Speed_10MHz | GPIO_CNF_OUT_PP ); // Set PIN_1 to output

	while(1)
	{
		funDigitalWrite( PIN_ME, FUN_HIGH );
		Delay_Ms( 500 );
		funDigitalWrite( PIN_ME, FUN_LOW );
		Delay_Ms( 500 );
	}
}
