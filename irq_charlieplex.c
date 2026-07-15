// Could be defined here, or in the processor defines.
#define SYSTEM_CORE_CLOCK 48000000

#include "ch32fun.h"
#include <stdio.h>

#define APB_CLOCK SYSTEM_CORE_CLOCK

#include "irq_charlieplex.h"

volatile uint32_t brightness[100];
volatile uint8_t lednum[100];
volatile uint32_t led_index;
uint8_t set_led[CHARLIE_LEDS];
uint8_t reset_led[CHARLIE_LEDS];

uint32_t get_led_set( uint32_t led ){
  return(led % (CHARLIE_PINS_N));
}
uint32_t get_led_reset( uint32_t led ){
  return((CHARLIE_PINS_N - (led/(CHARLIE_PINS_N-1))) - 1);
}

void SysTick_Handler(void) __attribute__((interrupt));
void SysTick_Handler(void)
{
  uint32_t set_pin, reset_pin;

	// Turn off the LED quickly
//	GPIOC->CFGLR = CHARLIE_CFGLRC_IN;
//	GPIOD->CFGLR = CHARLIE_CFGLRD_IN;
 	// Clear the output values for our pins
 	GPIOC->BSHR = CHARLIE_BSHRC_PINS;
 	GPIOD->BSHR = CHARLIE_BSHRD_PINS;
	// And drive them all low to prevent ghosting
	GPIOC->CFGLR = CHARLIE_CFGLRC_OUT;
//	GPIOC->CFGLR = CHARLIE_CFGLRC_IN;
	GPIOD->CFGLR = CHARLIE_CFGLRD_OUT;
//	GPIOD->CFGLR = CHARLIE_CFGLRD_IN;

	// If the current led_index points to an invalid LED, don't display anything
	if(lednum[led_index] < CHARLIE_LEDS){
		// calculate next values to set
//		reset_pin = get_led_reset( lednum[led_index] );
//  	set_pin = get_led_set( lednum[led_index] );
		reset_pin = reset_led[ lednum[led_index] ];
  	set_pin = set_led[ lednum[led_index] ];

  	// Configure the pins for input/output
  	GPIOC->CFGLR = charlie_pin_data[set_pin].cfglrc | charlie_pin_data[reset_pin].cfglrc;
  	GPIOD->CFGLR = charlie_pin_data[set_pin].cfglrd | charlie_pin_data[reset_pin].cfglrd;

  	// Set the set pin
		GPIOC->BSHR = charlie_pin_data[set_pin].bshrc;
  	GPIOD->BSHR = charlie_pin_data[set_pin].bshrd;
	}

  // Clear the trigger state for the next IRQ
  SysTick->SR = 0x00000000;
	// Set time to wait for brightness time
  SysTick->CMP += brightness[led_index];

	if (lednum[++led_index] == 255)
		led_index=0;
}

int main()
{
	SystemInit();

	for(int i = 0; i < CHARLIE_LEDS; i++){
		set_led[i] = get_led_set(i);
		reset_led[i] = get_led_reset(i);
	}

	Delay_Ms(1500);

	// Enable GPIOs
	RCC->APB2PCENR |= RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_AFIOEN;
	// Convert PD1 from SWIO to GPIO
	AFIO->PCFR1 &= ~(AFIO_PCFR1_SWCFG);
	AFIO->PCFR1 |= AFIO_PCFR1_SWCFG_DISABLE;

	int index = 0, total_brightness = 0;
	// Setup display list
	// reserve two slots for the 'second' LEDs
	lednum[index] = 0;
	brightness[index] = 200;
	total_brightness += 200;
	index++;
	lednum[index] = 0;
	brightness[index] = 200;
	total_brightness += 200;
	index++;

	// Make the hour ticks
	for(int i = 0; i < CHARLIE_LEDS; i+=20){
		lednum[index] = i;
		brightness[index] = 175;
		total_brightness += 175;
		index++;
	}

	// Set the end 'no led' entry to be the remaining frame time
//	lednum[index] = CHARLIE_LEDS;
//	brightness[index++] = DELAY_MS_TIME - total_brightness;
	// Put all the leftover brightness in the second hand
//	brightness[0] = DELAY_MS_TIME - total_brightness;
	// Set the 'end of list' flag
	lednum[index] = 255;

	// Setup the systick IRQ and set it to fire in one MS
	SysTick->CTLR = 0;
  SysTick->CMP = 1000;
  SysTick->CNT = 0;
  SysTick->CTLR |= SYSTICK_CTLR_STE | SYSTICK_CTLR_STIE | SYSTICK_CTLR_STCLK ; 
  NVIC_EnableIRQ(SysTick_IRQn);

	// spin the second hand
	int counter = 0;
	while(1) {
		int bright;
		lednum[0] = counter/100;
		lednum[1] = ((counter/100) + 1) % CHARLIE_LEDS;
		bright = ((100 - (counter%100)) * (DELAY_MS_TIME - total_brightness)) / 100;
		brightness[0] = (bright > 200)?bright:200;
		bright = ((counter%100) * (DELAY_MS_TIME - total_brightness)) / 100;
		brightness[1] = (bright > 200)?bright:200;
		if(++counter == (CHARLIE_LEDS * 100))
			counter=0;
		Delay_Ms(600/240);
		}
}

