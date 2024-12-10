/*
 * global.c
 *
 *  Created on: Dec 9, 2024
 *      Author: maiph
 */

#include "global.h"
#include "timer.h"

int timer_counter[TIMER_COUNT] = {0};
int timer_flag[TIMER_COUNT] = {0};
int timer_delay[TIMER_COUNT] = {300};

uint8_t temp = 0;
#define MAX_BUFFER_SIZE 30
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;
char str[50];
uint32_t ADC_value = 0;
uint32_t ADC_buffer = 0;
int state = 0;
int ok_flag = 0;
int rst_flag = 0;

uint32_t get_sensor()
{
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	ADC_value =  HAL_ADC_GetValue(&hadc1);
	HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!ADC=%lu#\r\n", ADC_value), 1000);
	return ADC_value;
}

//A FUNCTION TO CHECK IF 3S THE OK FLAG IS SET OR NOT
void check_ok()
{
	if(timer_flag[0] == 1 && ok_flag == 0 && rst_flag == 1){
		HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!ADC=%lu#\r\n", ADC_buffer), 1000);
		setTimer(300, 0);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart)
{
	if(huart->Instance == USART2)
	{
		if(temp == 33){index_buffer = 0;}
		buffer[index_buffer++] = temp;
		if(index_buffer == MAX_BUFFER_SIZE) index_buffer = 0;
		buffer_flag = 1;
		HAL_UART_Transmit(&huart2, &temp, 1, 50);
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}

void command_parser_fsm(int value)
{
	/*
	 * CASE ! (33) state 1
	 * CASE # (35) state 2
	 * CASE O (79) state 3
	 * CASE K (75) state 4
	 * CASE R (82) state 5
	 * CASE S (83) state 6
	 * CASE T (84) state 7
	 * */
	//CHECK ! AND RST BUFFER, IF # AND BACKTRACK
	switch(state)
	{
	case 0: //!
		if(value == 33){
			state = 1;
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\n"), 1000);
		}
		else{}
		break;
	case 1: //O/R
		if(value == 79){state = 3;}
		else if(value == 82){state = 5;}
		else{state = 0;}
		break;
	case 2:
		//PROCESS
		break;
	case 3: //K
		if(value == 75){state = 4;}
		else{state = 0;}
		break;
	case 4: //#
		if(value == 35){
			ok_flag = 1;
			//PROCESS OK
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\n"), 1000);
			state = 0;
		}
		else{state = 0;}
		break;
	case 5: //S
		if(value == 83){state = 6;}
		else{state = 0;}
		break;
	case 6: //T
		if(value == 84){state = 7;}
		else{state = 0;}
		break;
	case 7: //#
		if(value == 35){
			rst_flag = 1;
			ok_flag = 0;
			//PROCESS RST
			ADC_buffer = get_sensor();
			setTimer(300, 0);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\n"), 1000);
			state = 0;
		}
		else{state = 0;}
		break;
	default:
		break;
	}
}

void main_command_parser()
{
	for(int i = 0; i < index_buffer; i++)
	{
		command_parser_fsm(buffer[i]);
	}
}

void uart_communication_fsm()
{

}

void main_fsm()
{
	if(buffer_flag == 1)
	{
		main_command_parser();
		buffer_flag = 0;
	}

	check_ok();
	uart_communication_fsm();
}
