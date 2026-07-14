// Could be defined here, or in the processor defines.
#define SYSTEM_CORE_CLOCK 48000000

#include "ch32fun.h"
#include <stdio.h>

#define APB_CLOCK SYSTEM_CORE_CLOCK

#include "irq_charlieplex.h"

volatile uint32_t brightness[100];
volatile uint8_t lednum[100];
volatile uint32_t led_index;

uint32_t get_led_reset( uint32_t led ){
  return(led % (CHARLIE_PINS_N));
}
uint32_t get_led_set( uint32_t led ){
  return((CHARLIE_PINS_N - (led/(CHARLIE_PINS_N-1))) - 1);
}

void SysTick_Handler(void) __attribute__((interrupt));
void SysTick_Handler(void)
{
  uint32_t set_pin, reset_pin;

	// Turn off the LED quickly
	GPIOC->CFGLR = (CHARLIE_CFGLRC_IN & CHARLIE_CFGLRC_MASK);
	GPIOD->CFGLR = (CHARLIE_CFGLRD_IN & CHARLIE_CFGLRD_MASK);
 	// Clear the output values for our pins
 	GPIOC->BSHR = CHARLIE_BSHRC_PINS;
 	GPIOD->BSHR = CHARLIE_BSHRD_PINS;

	// If the current led_index points to an invalid LED, don't display anything
	if(lednum[led_index] < CHARLIE_LEDS){
		// calculate next values to set
		reset_pin = get_led_set( lednum[led_index] );
  	set_pin = get_led_reset( lednum[led_index] );

  	// Configure the pins for input/output
  	GPIOC->CFGLR |= charlie_pin_data[set_pin].cfglrc | charlie_pin_data[reset_pin].cfglrc;
  	GPIOD->CFGLR |= charlie_pin_data[set_pin].cfglrd | charlie_pin_data[reset_pin].cfglrd;

  	// Set the set pin
  	GPIOC->BSHR = charlie_pin_data[set_pin].bshrc;
  	GPIOD->BSHR = charlie_pin_data[set_pin].bshrd;
	}

  SysTick->CMP += brightness[led_index];
  // Clear the trigger state for the next IRQ
  SysTick->SR = 0x00000000;

	if (lednum[++led_index] == 255)
		led_index=0;
}

int main()
{
	SystemInit();

	Delay_Ms(1500);

	// Enable GPIOs
	RCC->APB2PCENR |= RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_AFIOEN;
	// Convert PD1 from SWIO to GPIO
	AFIO->PCFR1 &= ~(AFIO_PCFR1_SWCFG);
	AFIO->PCFR1 |= AFIO_PCFR1_SWCFG_DISABLE;

	int index = 0, total_brightness = 0;
	// Setup display list
	// reserve the 'second' LED
	lednum[index] = 0;
	brightness[index] = DELAY_MS_TIME/10;
	total_brightness += DELAY_MS_TIME/10;
	index++;

	// Make the hour ticks
	for(int i = 0; i < CHARLIE_LEDS; i+=20){
		lednum[index] = i;
		brightness[index] = DELAY_MS_TIME/150;
		total_brightness += DELAY_MS_TIME/150;
		index++;
	}

	// Set the end 'no led' entry to be the remaining frame time
	lednum[index] = CHARLIE_LEDS;
	brightness[index++] = DELAY_MS_TIME - total_brightness;
	// Set the 'end of list' flag
	lednum[index] = 255;

	// Setup the systick IRQ and set it to fire in one MS
	SysTick->CTLR = 0x0000;
  SysTick->CMP = DELAY_MS_TIME - 1;
  SysTick->CNT = 0x00000000;
  SysTick->CTLR |= SYSTICK_CTLR_STE | SYSTICK_CTLR_STIE | SYSTICK_CTLR_STCLK ; 
  NVIC_EnableIRQ(SysTick_IRQn);

	// spin the second hand
	int counter = 0;
	while(1) {
		lednum[0] = counter;
		if(counter++ == CHARLIE_LEDS)
			counter=0;
		Delay_Ms(60000/240);
		}
}

