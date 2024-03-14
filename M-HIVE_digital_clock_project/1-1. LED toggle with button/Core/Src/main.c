/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "easyMacros.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TRUE 1
#define FALSE 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
int SW1_pressed = FALSE;
int SW2_pressed = FALSE;
int SW3_pressed = FALSE;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();

  /* USER CODE BEGIN 2 */
  LEFT_LED_RED_SET();
  LEFT_LED_GREEN_SET();
  LEFT_LED_BLUE_SET();
  RIGHT_LED_RED_SET();
  RIGHT_LED_GREEN_SET();
  RIGHT_LED_BLUE_SET();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	// LED - RED
	// 빨강색 LED, 초록색 LED, 파랑색 LED 전부 동작원리가 같다.
	if(SW1_pressed == FALSE && IS_SW1_PRESSING() == TRUE) // SW1을 누르고 있지 않다가 누르기 시작하는 그 시점부터
	{
		SW1_pressed = TRUE; // SW1을 누르고 있는 상태라고 인식한다.

		if(IS_LEFT_LED_RED_RESET()) LEFT_LED_RED_SET(); // 만약 왼쪽 빨강색 LED가 꺼져있으면 켜주고,
		else if(IS_LEFT_LED_RED_SET()) LEFT_LED_RED_RESET(); // 켜져있으면 꺼준다.
	}
	if(SW1_pressed == TRUE && IS_SW1_PRESSING() == FALSE) // SW1을 누르고 있다가 때기 시작하는 그 시점부터
	{
		SW1_pressed = FALSE; // SW1을 때고 있는 상태라고 인식한다.

		if(IS_RIGHT_LED_RED_RESET()) RIGHT_LED_RED_SET(); // 만약 오른쪽 빨강색 LED가 꺼져있으면 켜주고,
		else if(IS_RIGHT_LED_RED_SET())	RIGHT_LED_RED_RESET(); // 켜저있으면 꺼준다.
	}


	// LED - GREEN
	if(SW2_pressed == FALSE && IS_SW2_PRESSING() == TRUE)
	{
		SW2_pressed = TRUE;

		if(IS_LEFT_LED_GREEN_RESET()) LEFT_LED_GREEN_SET();
		else if(IS_LEFT_LED_GREEN_SET()) LEFT_LED_GREEN_RESET();
	}
	if(SW2_pressed == TRUE && IS_SW2_PRESSING() == FALSE)
	{
		SW2_pressed = FALSE;

		if(IS_RIGHT_LED_GREEN_RESET()) RIGHT_LED_GREEN_SET();
		else if(IS_RIGHT_LED_GREEN_SET()) RIGHT_LED_GREEN_RESET();
	}


	// LED - BLUE
	if(SW3_pressed == FALSE && IS_SW3_PRESSING() == TRUE)
	{
		SW3_pressed = TRUE;

		if(IS_LEFT_LED_BLUE_RESET()) LEFT_LED_BLUE_SET();
		else if(IS_LEFT_LED_BLUE_SET()) LEFT_LED_BLUE_RESET();
	}
	if(SW3_pressed == TRUE && IS_SW3_PRESSING() == FALSE)
	{
		SW3_pressed = FALSE;

		if(IS_RIGHT_LED_BLUE_RESET()) RIGHT_LED_BLUE_SET();
		else if(IS_RIGHT_LED_BLUE_SET()) RIGHT_LED_BLUE_RESET();
	}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
