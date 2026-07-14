#ifndef _FUNCONFIG_H
#define _FUNCONFIG_H

// This file is C code, so single line comments start with a double slash.
/* Multi line comments can use the slash-star-body-star-slash syntax
 * but it's sometimes harder on version control systems and when editing
 * comments as the first and last lines are special.  Most people prefer
 * multiple single line comments instead of a multi-line comment.
*/

// This file configures the many options supported by the ch32fun system.
// Many of them won't make sense unless you know more about the ch32fun
// system.  You can learn more by reading the examples it contains.  Just
// search for the values you find in these #define commands to find relevant
// examples
// Some of these values configure how the chip runs--clocks speed, etc. and
// are improtant to the functioning of your code.  Some control how debugging
// works.  If your project is meant to run on many different chips and 
// different chips need different options, you can put conditionals in
// here to only #define values for particular chip or chip variants.  You
// should *not* define the chip you're working with here, that is done in
// the Makefile.  You can use the defines from the make system here.
// #if defined(CH32V10x)
// This would include the following block only if the build system is set
// to build for a CH32V10x series processor.  Normal C preprocessor syntax
// applies.
//
// The follwing is just a sample of the various values set in some of the
// ch32fun examples:
// #define FUNCONF_USE_DEBUGPRINTF 				0
// #define FUNCONF_USE_DEBUGPRINTF 				1
// #define FUNCONF_UART_PRINTF_BAUD    		115200
// #define FUNCONF_USE_USBPRINTF       		0
// #define FUNCONF_USE_USBPRINTF       		1
// #define CLK_SOURCE_CH5XX          			CLK_SOURCE_HSE_PLL_62_4MHz
// #define CLK_SOURCE_CH5XX            		CLK_SOURCE_HSE_PLL_78MHz // default so not really needed
// #define CLK_SOURCE_CH5XX            		CLK_SOURCE_PLL_100MHz // default so not really needed
// #define CLK_SOURCE_CH5XX            		CLK_SOURCE_PLL_60MHz // default so not really needed
// #define CLK_SOURCE_CH5XX          			CLK_SOURCE_PLL_60MHz // default so not really needed
// #define DEBUG
// #define FUNCONF_5V_OPERATION 					1
// #define FUNCONF_DEBUG_HARDFAULT   			0
// #define FUNCONF_DEBUG_HARDFAULT   			1
// #define FUNCONF_DEBUGPRINTF_TIMEOUT 		(1<<31) // Wait for a very very long time.
// #define FUNCONF_ENABLE_HPE 						1
// #define FUNCONF_H41x_V5F_EN 						1
// #define FUNCONF_HSE_BYPASS 						0 		// bypass the HSE when using an external clock source
// #define FUNCONF_INIT_ANALOG       			0 // ADC is not implemented yet
// #define FUNCONF_ISR_IN_RAM        			1
// #define FUNCONF_NULL_PRINTF 						1
// #define FUNCONF_PLL_MULTIPLIER 				14
// #define FUNCONF_PLL_MULTIPLIER 				15
// #define FUNCONF_PLL_MULTIPLIER 				16
// #define FUNCONF_PLL_MULTIPLIER 				2
// #define FUNCONF_PLL_MULTIPLIER      		9
// #define FUNCONF_POWERED_BY_V5PIN  			0 // Set this to 1 if you use CH570/2 and use 5V to power it.
// #define FUNCONF_SUPPORT_CONSTRUCTORS 	1
// #define FUNCONF_SYSTEM_CORE_CLOCK   		100 * 1000 * 1000     // keep in line with CLK_SOURCE_CH5XX
// #define FUNCONF_SYSTEM_CORE_CLOCK 			120000000
// #define FUNCONF_SYSTEM_CORE_CLOCK 			60 * 1000 * 1000     // keep in line with CLK_SOURCE_CH5XX
// #define FUNCONF_SYSTEM_CORE_CLOCK 			624 * 100 * 1000     // keep in line with CLK_SOURCE_CH5XX
// #define FUNCONF_SYSTEM_CORE_CLOCK   		72000000
// #define FUNCONF_SYSTEM_CORE_CLOCK   		78 * 1000 * 1000     // keep in line with CLK_SOURCE_CH5XX
// #define FUNCONF_SYSTEM_CORE_CLOCK 			8 * 1000 * 1000
// #define FUNCONF_SYSTICK_USE_HCLCK 			1
// #define FUNCONF_SYSTICK_USE_HCLK 			1
// #define FUNCONF_TINYVECTOR 						1
// #define FUNCONF_USE_5V_VDD       			1
// #define FUNCONF_USE_CLK_SEC 						0
// #define FUNCONF_USE_CLK_SEC						1
// #define FUNCONF_USE_HSE 								0
// #define FUNCONF_USE_HSE 								1
// #define FUNCONF_USE_HSI 								0
// #define FUNCONF_USE_HSI 								1
// #define FUNCONF_USE_PLL 								0
// #define FUNCONF_USE_PLL 								1	
// #define INTERRUPT_IN_RAM 							0
// #define MINICHLINK         						1
// #define NAKED_TEST 										1
// #define OVERCLOCK 											0
// #define RANDOM_STRENGTH    						2
// #define SYSTICK_USE_HCLK 							1
// #define USE_VTF    										1

#endif

