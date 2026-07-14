// This example shows how to flexibly drive arbitrary charlieplexed displays
// It uses two layers of lookup to determine the port data for each LED.  
// The first layer converts the LED# to two virtual pin#.
// The second layer converts the virtual pin# to the GPIO register values.
#define FLOAT (GPIO_Speed_In   |  GPIO_CNF_IN_ANALOG)
#define OUT   (GPIO_Speed_2MHz |  GPIO_CNF_OUT_PP)
#define CHARLIE_PINS_N 16
#define CHARLIE_LEDS (CHARLIE_PINS_N * (CHARLIE_PINS_N - 1))
// Create masks for the GPIO configuration registers to show which bits we control
// We use all of port C
#define CHARLIE_CFGLRC_MASK 	(~(GPIO_CFGLR_MODE0 | \
				   GPIO_CFGLR_MODE1 | \
				   GPIO_CFGLR_MODE2 | \
				   GPIO_CFGLR_MODE3 | \
				   GPIO_CFGLR_MODE4 | \
				   GPIO_CFGLR_MODE5 | \
				   GPIO_CFGLR_MODE6 | \
				   GPIO_CFGLR_MODE7 | \
				   GPIO_CFGLR_CNF0 | \
				   GPIO_CFGLR_CNF1 | \
				   GPIO_CFGLR_CNF2 | \
				   GPIO_CFGLR_CNF3 | \
				   GPIO_CFGLR_CNF4 | \
				   GPIO_CFGLR_CNF5 | \
				   GPIO_CFGLR_CNF6 | \
				   GPIO_CFGLR_CNF7))
// We use all of port D
#define CHARLIE_CFGLRD_MASK 	(~(GPIO_CFGLR_MODE0 | \
				   GPIO_CFGLR_MODE1 | \
				   GPIO_CFGLR_MODE2 | \
				   GPIO_CFGLR_MODE3 | \
				   GPIO_CFGLR_MODE4 | \
				   GPIO_CFGLR_MODE5 | \
				   GPIO_CFGLR_MODE6 | \
				   GPIO_CFGLR_MODE7 | \
				   GPIO_CFGLR_CNF0 | \
				   GPIO_CFGLR_CNF1 | \
				   GPIO_CFGLR_CNF2 | \
				   GPIO_CFGLR_CNF3 | \
				   GPIO_CFGLR_CNF4 | \
				   GPIO_CFGLR_CNF5 | \
				   GPIO_CFGLR_CNF6 | \
				   GPIO_CFGLR_CNF7))
// We also need a value to set all of the pins to input
#define CHARLIE_CFGLRC_IN 	((FLOAT) << (4*0) | \
			 	 (FLOAT) << (4*1) | \
				 (FLOAT) << (4*2) | \
				 (FLOAT) << (4*3) | \
				 (FLOAT) << (4*4) | \
				 (FLOAT) << (4*5) | \
				 (FLOAT) << (4*6) | \
				 (FLOAT) << (4*7))
#define CHARLIE_CFGLRD_IN 	((FLOAT) << (4*0) | \
				 (FLOAT) << (4*1) | \
				 (FLOAT) << (4*2) | \
				 (FLOAT) << (4*3) | \
				 (FLOAT) << (4*4) | \
				 (FLOAT) << (4*5) | \
				 (FLOAT) << (4*6) | \
				 (FLOAT) << (4*7))
// And a value to use to reset all the pins
#define CHARLIE_BSHRC_PINS 	(GPIO_BSHR_BR0 | GPIO_BSHR_BR1 | GPIO_BSHR_BR2 | GPIO_BSHR_BR3 | \
				GPIO_BSHR_BR4 | GPIO_BSHR_BR5 | GPIO_BSHR_BR6 | GPIO_BSHR_BR7)
#define CHARLIE_BSHRD_PINS 	(GPIO_BSHR_BR0 | GPIO_BSHR_BR1 | GPIO_BSHR_BR2 | GPIO_BSHR_BR3 | \
				GPIO_BSHR_BR4 | GPIO_BSHR_BR5 | GPIO_BSHR_BR6 | GPIO_BSHR_BR7)
// Define an array of structures containing the values for the port C and D
// configuration and bit set/reset registers to drive a physical pin--indexed
// by virtual pin number.  
// Virtual pin 0 is PC0 though pin 7 being PC7
// Then 8 is PD0 through 15 being PD7
const struct {
	uint32_t cfglrc;
	uint32_t cfglrd;
	uint16_t bshrc;
	uint16_t bshrd;
} charlie_pin_data[CHARLIE_PINS_N] = {
	{((OUT) << (4*0)   | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 GPIO_BSHR_BS0,
	 0x0},

	{((FLOAT) << (4*0) | (OUT) << (4*1)   | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 GPIO_BSHR_BS1,
	 0x0},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (OUT) << (4*2)   | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 GPIO_BSHR_BS2,
	 0x0},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (OUT) << (4*3)   | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 GPIO_BSHR_BS3,
	 0x0},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (OUT) << (4*4)   | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 GPIO_BSHR_BS4,
	 0x0},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (OUT) << (4*5)   | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 GPIO_BSHR_BS5,
	 0x0},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (OUT) << (4*6)   | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 GPIO_BSHR_BS6,
	 0x0},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (OUT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 GPIO_BSHR_BS7,
	 0x0},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((OUT) << (4*0)   | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 0x0,
	 GPIO_BSHR_BS0},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (OUT) << (4*1)   | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 0x0,
	 GPIO_BSHR_BS1},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (OUT) << (4*2)   | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 0x0,
	 GPIO_BSHR_BS2},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (OUT) << (4*3)   | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 0x0,
	 GPIO_BSHR_BS3},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (OUT) << (4*4)   | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 0x0,
	 GPIO_BSHR_BS4},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (OUT) << (4*5)   | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 0x0,
	 GPIO_BSHR_BS5},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (OUT) << (4*6)   | (FLOAT) << (4*7)),
	 0x0,
	 GPIO_BSHR_BS6},

	{((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (FLOAT) << (4*7)),
	 ((FLOAT) << (4*0) | (FLOAT) << (4*1) | (FLOAT) << (4*2) | (FLOAT) << (4*3) | (FLOAT) << (4*4) | (FLOAT) << (4*5) | (FLOAT) << (4*6) | (OUT) << (4*7)),
	 0x0,
	 GPIO_BSHR_BS7}
};
