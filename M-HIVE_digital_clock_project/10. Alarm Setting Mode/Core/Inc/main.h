/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

// Stopwatch
typedef enum _Stopwatch_state {
	RUNNING,
	PAUSED,
	STOPPED
} Stopwatch_state;

typedef struct _Stopwatch_time {
	uint32_t hour;
	uint32_t minute;
	uint32_t second;
	uint32_t milisecond;
} Stopwatch_time;

typedef struct _Stopwatch {
	int point;
	Stopwatch_time time;
	Stopwatch_state state;
} Stopwatch;

// Lap
typedef enum _Lap_state {
	READY,
	MEASURE,
	DISPLAY_RECORD,
	CLEAR
} Lap_state;

typedef struct _Lap {
	int count;
	int show_num;
	Stopwatch_time record[9];
	Lap_state state;
} Lap;

// CLCD
typedef struct _CLCD {
	uint8_t str1[16];
	uint8_t str2[16];
} CLCD;

// Button Events
typedef enum _Button_state {
	NONE,

	MEASURE_HOLD,
	SHORT_HOLD,
	SHORT_MID_THRESHOLD,
	MID_HOLD,
	MID_LONG_THRESHOLD,
	LONG_HOLD,

	MEASURE_RELEASE,
	SHORT_RELEASE,
	MID_RELEASE,
	LONG_RELEASE
} Button_state;

typedef struct _Button {
	int value;
	int hold_milisecond;
	int repeating_milisecond;
	Button_state state;
} Button;

// Buzzer
typedef enum _Buzzer_State {
	STOP,
	BEEP
} Buzzer_State;

typedef enum _Tone {
	// PSC value for buzzer tone.
	LOW = 15000,
	MID = 10000,
	HIGH = 7500
} Tone;

typedef struct _Buzzer {
	int running_milisecond;
	int beep_milisecond;
	int config; // OFF = 0, ON = 1
	Buzzer_State state;
	Tone tone;
} Buzzer;

// Clock
typedef struct _Clock_Time {
	int year;
	int month;
	int day;
	int hour; // 24h standard.
	int minute;
	int second;
	int milisecond;
} Clock_Time;

typedef struct _Clock {
	int point; // OFF = 0, ON = 1
	int leap_year; // TRUE = 1, FALSE = 0
	int mode_24h; // TRUE = 1, FALSE = 0
	Clock_Time time;
} Clock;

// Clock_Config
typedef enum _Clock_Time_Element {
	YEAR, MONTH, DAY, HOUR, MINUTE, SECOND
} Clock_Time_Element;

typedef struct _Clock_Config {
	Clock_Time_Element choose;
} Clock_Config;

// Alarm
typedef struct _Alarm {
	int select;
	int hour[5];
	int minute[5];
	int activate[5]; // ON = 1, OFF = 0
	int repeat[5]; // ON = 1, OFF = 0

	int closing; // TRUE = 1, FALSE = 0
} Alarm;

// Alarm_Config
typedef enum _Alarm_Time_Element {
	SELECT, ALARM_MINUTE, ALARM_HOUR, REPEAT, ACTIVATE
} Alarm_Time_Element;

typedef struct _Alarm_Config {
	Alarm_Time_Element choose;
} Alarm_Config;

// System
typedef enum _System_Mode {
	STOPWATCH,
	CLOCK,
	CLOCK_CONFIG,
	ALARM,
	ALARM_CONFIG,
	ALARM_TRIGGER
} System_Mode;

typedef struct _System {
	int wait_milisecond;
	System_Mode mode;
} System;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define OFF 0
#define ON 1

#define TRUE 1
#define FALSE 0

#define SHORT_MID_BOUNDARY_TIME 700
#define MID_LONG_BOUNDARY_TIME 2500

#define MID_HOLD_CYCLE_TIME 150
#define LONG_HOLD_CYCLE_TIME 20
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void change_system_mode(System_Mode);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
