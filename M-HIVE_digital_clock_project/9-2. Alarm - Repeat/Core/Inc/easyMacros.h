#include "gpio.h"

/*
 * easyMacros.h
 *
 *  Created on: Mar 15, 2024
 *      Author: yeosu
 *
 *  Description : Macros for using functions easier.
 */

/* Define Variables */
#define TRUE 1
#define FALSE 0
#define SW1 GPIO_PIN_3
#define SW2 GPIO_PIN_15
#define SW3 GPIO_PIN_4
#define SW4 GPIO_PIN_10

/* Condition Check Macros */
#define	CHECK_SW1_PRESSING() 		(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == GPIO_PIN_SET)
#define CHECK_SW2_PRESSING() 		(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_SET)
#define CHECK_SW3_PRESSING() 		(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == GPIO_PIN_SET)
#define CHECK_SW4_PRESSING() 		(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10) == GPIO_PIN_SET)
#define CHECK_L_RED_LED_ON()		(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12) == GPIO_PIN_RESET)
#define CHECK_L_RED_LED_OFF()		(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12) == GPIO_PIN_SET)
#define CHECK_L_GREEN_LED_ON()		(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13) == GPIO_PIN_RESET)
#define CHECK_L_GREEN_LED_OFF()		(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13) == GPIO_PIN_SET)
#define CHECK_L_BLUE_LED_ON() 		(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14) == GPIO_PIN_RESET)
#define CHECK_L_BLUE_LED_OFF() 		(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14) == GPIO_PIN_SET)
#define CHECK_R_RED_LED_ON()		(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == GPIO_PIN_RESET)
#define CHECK_R_RED_LED_OFF() 		(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == GPIO_PIN_SET)
#define CHECK_R_GREEN_LED_ON()		(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET)
#define CHECK_R_GREEN_LED_OFF() 	(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_SET)
#define CHECK_R_BLUE_LED_ON() 		(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
#define CHECK_R_BLUE_LED_OFF() 		(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)

/* Set and Reset LED Macros */
#define L_RED_LED_ON()      		(HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET))
#define L_RED_LED_OFF()      		(HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET))
#define L_GREEN_LED_ON()    		(HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET))
#define L_GREEN_LED_OFF()    		(HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET))
#define L_BLUE_LED_ON()     		(HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET))
#define L_BLUE_LED_OFF()       		(HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET))
#define R_RED_LED_ON()     			(HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET))
#define R_RED_LED_OFF()     		(HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET))
#define R_GREEN_LED_ON()   			(HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET))
#define R_GREEN_LED_OFF()   		(HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET))
#define R_BLUE_LED_ON()    			(HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET))
#define R_BLUE_LED_OFF()   	 		(HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET))

#define L_RED_LED_TOGGLE()			(CHECK_L_RED_LED_OFF()   ? L_RED_LED_ON()   : L_RED_LED_OFF())
#define L_GREEN_LED_TOGGLE()		(CHECK_L_GREEN_LED_OFF() ? L_GREEN_LED_ON() : L_GREEN_LED_OFF())
#define L_BLUE_LED_TOGGLE()			(CHECK_L_BLUE_LED_OFF()  ? L_BLUE_LED_ON()  : L_BLUE_LED_OFF())
#define R_RED_LED_TOGGLE()			(CHECK_R_RED_LED_OFF()   ? R_RED_LED_ON()   : R_RED_LED_OFF())
#define R_GREEN_LED_TOGGLE()		(CHECK_R_GREEN_LED_OFF() ? R_GREEN_LED_ON() : R_GREEN_LED_OFF())
#define R_BLUE_LED_TOGGLE()			(CHECK_R_BLUE_LED_OFF()  ? R_BLUE_LED_ON()  : R_BLUE_LED_OFF())

#define ALL_LED_ON()                {\
									L_RED_LED_ON();\
									L_GREEN_LED_ON();\
									L_BLUE_LED_ON();\
									R_RED_LED_ON();\
									R_GREEN_LED_ON();\
									R_BLUE_LED_ON();\
									}
#define ALL_LED_OFF()               {\
									L_RED_LED_OFF();\
									L_GREEN_LED_OFF();\
									L_BLUE_LED_OFF();\
									R_RED_LED_OFF();\
									R_GREEN_LED_OFF();\
									R_BLUE_LED_OFF();\
									}
