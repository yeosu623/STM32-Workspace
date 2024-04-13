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
int show_7seg_point = FALSE; // 0.5초마다 7-Seg의 점을 깜박거리기 위해서 있는 변수이다.
int stopwatch_start = FALSE; // SW2를 누르면 이 변수가 TRUE가 되어서, Stopwatch가 시작된다.
int stopwatch_reset = FALSE; // SW3을 누르면 이 변수가 TRUE가 되어서, Stopwatch가 초기화된다.
static unsigned int stopwatch_time_1h = 0; // Stopwatch의 1시간 단위의 데이터
static unsigned int stopwatch_time_1m = 0; // Stopwatch의 1분 단위의 데이터
static unsigned int stopwatch_time_1s = 0; // Stopwatch의 1초 단위의 데이터
static unsigned int stopwatch_time_1ms = 0; // Stopwatch의 1밀리초 단위의 데이터

typedef enum _Mode { // 디지털 알람 시계의 모드 정의. 현재는 Stopwatch만 있다.
	Stopwatch = 0,
	Other
} Mode;
Mode mode = Stopwatch;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
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
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  switch(mode) // 디지털 알람시계의 모드를 Swtich-Case로 구분하였다.
	  {
	  /*
	   * Stopwatch 모드일 경우. 여기서는 7-Seg에 시간을 표시해주는 일만 한다.
	   * 밑의 코드에서 버튼의 외부 인터럽트를 통하여 Stopwatch 시작과 리셋을 조작한다.
	   */
	  case Stopwatch :
		    // 0.5초마다 점을 토글시키는 코드
			if(stopwatch_time_1ms < 500) show_7seg_point = ON;
			else show_7seg_point = OFF;

			// 첫째 자리는 1초 단위로, 둘째 자리는 0.1초 단위로 7-Seg에 표시한다.
			_7SEG_SetNumber(DGT1, stopwatch_time_1s % 10, show_7seg_point);
			_7SEG_SetNumber(DGT2, stopwatch_time_1ms / 100, OFF);
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) // 1ms 주기의 Timer 6
{
	if(htim->Instance == TIM6)
	{
		// Stopwatch 시작할시, 1ms 단위로 시간을 누적하여 측정한다.
		if(stopwatch_start)
		{
			stopwatch_time_1ms++;
			convert_stopwatch_time_format(); // Stopwatch의 1ms를 1s, 1m, 1h로 변환하는 함수
		}

		// Stopwatch를 리셋할시, 누적된 시간을 0으로 초기화 한다.
		if(stopwatch_reset)
		{
			stopwatch_time_1ms = 0;
			stopwatch_time_1s = 0;
			stopwatch_time_1m = 0;
			stopwatch_time_1h = 0;
			stopwatch_reset = FALSE;
		}
	}
}

void convert_stopwatch_time_format()
{
	if(stopwatch_time_1ms == 1000)
	{
		stopwatch_time_1ms = 0;
		stopwatch_time_1s++;
	}
	if(stopwatch_time_1s == 60)
	{
		stopwatch_time_1s = 0;
		stopwatch_time_1m++;
	}
	if(stopwatch_time_1m == 60)
	{
		stopwatch_time_1m = 0;
		stopwatch_time_1h++;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) // 외부 인터럽트를 통하여 SW1~4를 조작하는 함수
{
	// SW1
	if(GPIO_Pin == SW1 && CHECK_SW1_PRESSING())
	{
		L_RED_LED_TOGGLE();
	}

	// SW2
	if(GPIO_Pin == SW2 && CHECK_SW2_PRESSING())
	{
		L_GREEN_LED_TOGGLE();

		switch(mode)
		{
		case Stopwatch :
			stopwatch_start = !stopwatch_start; // Stopwatch의 Start/Pause를 토글한다.
			break;
		}
	}

	// SW3
	if(GPIO_Pin == SW3 && CHECK_SW3_PRESSING())
	{
		L_BLUE_LED_TOGGLE();

		switch(mode)
		{
		case Stopwatch :
			if(!stopwatch_start) stopwatch_reset = TRUE; // Stopwatch가 Pause일 경우, Stopwatch를 Reset한다.
			break;
		}
	}

	// SW4
	if(GPIO_Pin == SW4 && CHECK_SW4_PRESSING())
	{
		R_RED_LED_TOGGLE();
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
