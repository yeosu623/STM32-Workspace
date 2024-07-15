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
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "easyMacros.h"
#include "7SEG.h"
#include "CLCD.h"
#include "lap.h"
#include "stopwatch.h"
#include "button_event.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
CLCD clcd = {"", ""};
Clock_mode clock_mode = BUTTON1;
Lap lap = {0, 0, {}, READY};
Stopwatch stopwatch = {OFF, {0, 0, 0, 0}, STOPPED};
Button button1 = {0, NONE};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
void convert_stopwatch_time_format();
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
  MX_TIM6_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  L_RED_LED_OFF();
  L_GREEN_LED_OFF();
  L_BLUE_LED_OFF();
  R_RED_LED_OFF();
  R_GREEN_LED_OFF();
  R_BLUE_LED_OFF();

  HAL_TIM_Base_Start_IT(&htim6);
  _7SEG_GPIO_Init();
  CLCD_GPIO_Init();
  CLCD_Init();
  CLCD_Clear();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  switch(clock_mode)
	  {
	    case STOPWATCH :
	    	stopwatch_show_time();

			switch(lap.state)
			{
			case MEASURE : lap_measure(); break;
			case DISPLAY_RECORD : lap_display_record(); break;
			case CLEAR : lap_clear(); break;
			}

			break;

		case BUTTON1 :
			switch(button1.state)
			{
			case NONE          : break;
			case PRESS         : button1_show_press_time(); break;
			case SHORT_RELEASE : button1_short_release(); break;
			case MID_RELEASE   : button1_mid_release(); break;
			case LONG_RELEASE  : button1_long_release(); break;
			}

			break;
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

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* TIM6_DAC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		if(stopwatch.state == RUNNING)
		{
			stopwatch.time.milisecond++;
			stopwatch_convert_time_format();
		}

		if(button1.state == PRESS)
		{
			if(button1.milisecond <= MID_LONG_BOUNDARY_TIME)
				button1.milisecond++;
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	// SW1 press
	if(GPIO_Pin == SW1 && CHECK_SW1_PRESSING())
	{
		L_RED_LED_TOGGLE();

		switch(clock_mode)
		{
		case BUTTON1 :
			button1_start();
			break;
		}
	}

	// SW1 release
	if(GPIO_Pin == SW1 && !CHECK_SW1_PRESSING())
	{
		switch(clock_mode)
		{
		case BUTTON1 :
			button1_measure_release();
			break;
		}
	}

	// SW2
	if(GPIO_Pin == SW2 && CHECK_SW2_PRESSING())
	{
		L_GREEN_LED_TOGGLE();

		switch(clock_mode)
		{
		case STOPWATCH :
			stopwatch_run_and_pause();
			break;
		}
	}

	// SW3
	if(GPIO_Pin == SW3 && CHECK_SW3_PRESSING())
	{
		L_BLUE_LED_TOGGLE();

		switch(clock_mode)
		{
		case STOPWATCH :
			stopwatch_measure_lap_or_stop();
			break;
		}
	}

	// SW4
	if(GPIO_Pin == SW4 && CHECK_SW4_PRESSING())
	{
		R_RED_LED_TOGGLE();

		switch(clock_mode)
		{
		case STOPWATCH :
			stopwatch_dlsplay_record();
		}
	}
}
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
