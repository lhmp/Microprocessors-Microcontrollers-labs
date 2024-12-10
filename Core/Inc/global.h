/*
 * global.h
 *
 *  Created on: Dec 9, 2024
 *      Author: maiph
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"
#include <stdio.h>

#define TIMER_COUNT 1

extern int timer_counter[TIMER_COUNT];
extern int timer_flag[TIMER_COUNT];
extern int timer_delay[TIMER_COUNT];

void main_fsm();
void command_parser_fsm(int);
void uart_communication_fsm();

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart);
extern UART_HandleTypeDef huart2;
extern uint8_t temp;

extern ADC_HandleTypeDef hadc1;
extern char str[50];
extern uint32_t ADC_value;

#endif /* INC_GLOBAL_H_ */
