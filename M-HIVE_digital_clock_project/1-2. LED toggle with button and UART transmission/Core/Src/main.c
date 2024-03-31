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
#include "usart.h"
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
int SW4_pressed = FALSE;
int select_left_LED = TRUE;
uint8_t uart3_rx_data = 0;
uint8_t uart3_rx_flag = 0;
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
  MX_USART3_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart3, &uart3_rx_data, sizeof(uart3_rx_data));

  L_RED_LED_OFF();
  L_GREEN_LED_OFF();
  L_BLUE_LED_OFF();
  R_RED_LED_OFF();
  R_GREEN_LED_OFF();
  R_BLUE_LED_OFF();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /*
     * BUTTON 방식
     * red, green, blue LED 전부 같은 방식으로 동작한다.
     */
	if(SW1_pressed != CHECK_SW1_PRESSING()) // Rising Edge, Falling Edge를 검출
	{
		SW1_pressed = !SW1_pressed; // 버튼의 현재 상태 검출
		if(SW1_pressed) // 버튼이 눌러져있는 것으로 Rising Edge만 검출
		{
			if(select_left_LED) L_RED_LED_TOGGLE(); // 왼쪽 LED가 선택되어 있으면 왼쪽 LED를 토글
			else R_RED_LED_TOGGLE(); // 반대의 경우 오른쪽 LED를 토글
		}
	}

	if(SW2_pressed != CHECK_SW2_PRESSING())
	{
		SW2_pressed = !SW2_pressed;
		if(SW2_pressed)
		{
			if(select_left_LED) L_GREEN_LED_TOGGLE();
			else R_GREEN_LED_TOGGLE();
		}
	}

	if(SW3_pressed != CHECK_SW3_PRESSING())
	{
		SW3_pressed = !SW3_pressed;
		if(SW3_pressed)
		{
			if(select_left_LED) L_BLUE_LED_TOGGLE();
			else R_BLUE_LED_TOGGLE();
		}
	}

	if(SW4_pressed != CHECK_SW4_PRESSING()) // Rising Edge, Falling Edge 검출
	{
		SW4_pressed = !SW4_pressed; // 버튼의 현재 상태 검출
		if(SW4_pressed) select_left_LED = !select_left_LED; // 버튼의 현재 상태로 Rising Edge만 검출. LED 선택 방태를 바꾼다.
	}


	/*
	 * UART Interrupt 방식
	 * red, green, blue LED 전부 같은 방식으로 동작한다.
	 */
	if(uart3_rx_flag) // UART3으로 데이터를 받아서 flag가 1이 되면
	{
		uart3_rx_flag = 0; // flag를 0으로 해준 후
		switch(uart3_rx_data) { // 받아온 데이터로 각각의 동작을 수행한다. 1~3은 red, green, blue LED toggle이고, 4는 LED 선택이다.
			case '1':
				if(select_left_LED) L_RED_LED_TOGGLE();
				else R_RED_LED_TOGGLE();
				break;
			case '2':
				if(select_left_LED) L_GREEN_LED_TOGGLE();
				else R_GREEN_LED_TOGGLE();
				break;
			case '3':
				if(select_left_LED) L_BLUE_LED_TOGGLE();
				else R_BLUE_LED_TOGGLE();
				break;
			case '4':
				select_left_LED = !select_left_LED;
		}
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
  /* USART3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{
		HAL_UART_Receive_IT(&huart3, &uart3_rx_data, sizeof(uart3_rx_data));
		uart3_rx_flag = 1;
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
