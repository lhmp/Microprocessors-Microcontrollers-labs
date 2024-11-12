/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lab2.h"
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int led_index = 0;
int timer0_counter = 0;
int timer0_flag = 0;
int timer1_flag = 0;
int timer2_flag = 0;
int TIMER_CYCLE = 10;
void setTimer0(int duration){
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
	timer1_flag = 0;
}
void timer_run(){
	if (timer0_counter>0){
		timer0_counter--;
		if (timer0_counter == 0) timer0_flag = 1;
		if (timer0_counter % 25 == 0) timer1_flag = 1;
		if (timer0_counter % 50 == 0) timer2_flag = 1;
	}
}
//////
int clk_hour =15, clk_minute = 5, clk_second = 50;
int led_buffer[4] = {1,2,3,4};
void updateClockBuffer(){
	if (clk_hour<9) led_buffer[0] = 0;
	else led_buffer[0] = clk_hour/10;
	if (clk_minute<9) led_buffer[2] = 0;
	else led_buffer[2] = clk_minute/10;

	led_buffer[1] = clk_hour%10;
	led_buffer[3] = clk_minute%10;
}
/////
void update7SEG (int index){
	switch (index){
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		display7SEG(led_buffer[0]);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		display7SEG(led_buffer[1]);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		break;
	case 2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
		display7SEG(led_buffer[2]);
		break;
	case 3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
		display7SEG(led_buffer[3]);
		HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		break;

	default:
		break;
	}
}
//////
int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {0x01, 0x06, 0x38, 0xC8, 0xC8, 0x38, 0x06, 0x01};
uint16_t row_pin[8] = {ROW0_Pin,ROW1_Pin,ROW2_Pin,ROW3_Pin,ROW4_Pin,ROW5_Pin,ROW6_Pin,ROW7_Pin};
uint16_t col_pin[8] = {ENM0_Pin,ENM1_Pin,ENM2_Pin,ENM3_Pin,ENM4_Pin,ENM5_Pin,ENM6_Pin,ENM7_Pin};
uint8_t charA[8] = {0x01, 0x06, 0x38, 0xC8, 0xC8, 0x38, 0x06, 0x01};

void updateLEDMatrix(int index){
	for (int i = 0; i < 8; i++){
		HAL_GPIO_WritePin(GPIOA, col_pin[i], 0);
		HAL_GPIO_WritePin(GPIOB, row_pin[i], 0);
	}
    switch (index){
        case 0:
			HAL_GPIO_WritePin(GPIOA, col_pin[0], 1);
			for (int i = 0; i < 8; i++){
				if (matrix_buffer[index] & (0x80 >> i)){
					HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
				}
			}
            break;
        case 1:
        	HAL_GPIO_WritePin(GPIOA, col_pin[1], 1);
        	for (int i = 0; i < 8; i++){
        		if (matrix_buffer[index] & (0x80 >> i)){
        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
        		}
        	}
            break;
        case 2:
        	HAL_GPIO_WritePin(GPIOA, col_pin[2], 1);
        	for (int i = 0; i < 8; i++){
        		if (matrix_buffer[index] & (0x80 >> i)){
        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
        		}
        	}
            break;
        case 3:
        	HAL_GPIO_WritePin(GPIOA, col_pin[3], 1);
        	for (int i = 0; i < 8; i++){
        		if (matrix_buffer[index] & (0x80 >> i)){
        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
        		}
        	}
            break;
        case 4:
        	HAL_GPIO_WritePin(GPIOA, col_pin[4], 1);
        	for (int i = 0; i < 8; i++){
        		if (matrix_buffer[index] & (0x80 >> i)){
        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
        		}
        	}
            break;
        case 5:
        	HAL_GPIO_WritePin(GPIOA, col_pin[5], 1);
        	for (int i = 0; i < 8; i++){
        		if (matrix_buffer[index] & (0x80 >> i)){
        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
        		}
        	}
            break;
        case 6:
        	HAL_GPIO_WritePin(GPIOA, col_pin[6], 1);
        	for (int i = 0; i < 8; i++){
        		if (matrix_buffer[index] & (0x80 >> i)){
        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
        		}
        	}
            break;
        case 7:
        	HAL_GPIO_WritePin(GPIOA, col_pin[7], 1);
        	for (int i = 0; i < 8; i++){
        		if (matrix_buffer[index] & (0x80 >> i)){
        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
        		}
        	}
            break;
        default:
            break;
    }
}

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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	int index_led_matrix = 0;
//	resetMatrix();
	setTimer0(1000);
	HAL_GPIO_WritePin(DOT_GPIO_Port, DOT_Pin, 0);
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
  while (1)
  {

	  if (timer0_flag == 1){
	  		  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	  		  clk_second++;
	  		  if (clk_second >=60 ){
	  			  clk_second = 0;
	  			  clk_minute++;
	  		  }
	  		  if (clk_minute >=60 ){
	  			  clk_minute = 0;
	  			  clk_hour++;
	  		  }
	  		  if (clk_hour >= 24){
	  			  clk_hour = 0;
	  		  }

	  		  updateClockBuffer();
	  		  setTimer0(1000);
	  	  }
	  	  if (timer1_flag == 1 ){
	  		  	update7SEG(led_index++);
	  			led_index = (led_index == 4)?0:led_index;
	  			timer1_flag = 0;
	  	  }
	  	  if (timer2_flag == 1){
			if(index_led_matrix >=8){index_led_matrix=0;}
			updateLEDMatrix(index_led_matrix++);
	  		timer2_flag = 0;
	  	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin PB3 PB4 PB5
                           PB6 ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	timer_run();
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
