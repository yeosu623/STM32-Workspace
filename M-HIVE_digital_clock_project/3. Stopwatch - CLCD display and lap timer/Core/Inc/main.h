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

typedef struct _CLCD {
	uint8_t str1[16];
	uint8_t str2[16];
} CLCD;

typedef enum _Clock_mode {
	STOPWATCH
} Clock_mode;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define OFF 0
#define ON 1
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
