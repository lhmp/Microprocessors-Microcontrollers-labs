/*
 * fsm_manual_run.c
 *
 *  Created on: Nov 11, 2024
 *      Author: maiph
 */

#include "fsm_manual_run.h"

/*
 * status = 0 NORMAL
 * status = 1 Modify
 *
 * */

///*
// * BUTTON[0] = RESET
// * BUTTON[1] = INC
// * BUTTON[2] = DEC
// * */
///*
// * TIMER_FLAG[0]: 7SEG
// * TIMER_FLAG[1]: LED_DEBUG
// * */
//
/*
 * OUT0: GREEN
 * OUT1: YELLOW
 * OUT2: RED
 *
 * OUT3: GREEN1
 * OUT4: YELLOW1
 * OUT5: RED1
 */
int auto_status = 0;
int auto_status_1 = 0;
int clock_counter = 3;
int clock_counter_1 = 5;
int manual_status = 0;

int MAX_RED = 5;
int MAX_YELLOW = 2;
int MAX_GREEN = 3;

int BUFFER_RED = 5;
int BUFFER_YELLOW = 2;
int BUFFER_GREEN = 3;


void fsm_clock_counter()
{
	if(timer_flag[0] == 1)
	{
		HAL_GPIO_TogglePin(GPIOA, OUT7_Pin);
		setTimer(100, 0);
	}
	if(timer_flag[1] == 1 && (manual_status == 0))
	{
		clock_counter--;
		clock_counter_1--;
		display7SEG(clock_counter);
		display7SEG_1(clock_counter_1);
		setTimer(100, 1);
	}
}

//FIRST 7SEG OUT0->OUT2 & SEG0->SEG6
void fsm_auto_traffic(){
	switch(auto_status){
	case 0:
		//GREEN
				  HAL_GPIO_WritePin(GPIOA, OUT0_Pin, 0);
				  HAL_GPIO_WritePin(GPIOA, OUT1_Pin|OUT2_Pin, 1);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_YELLOW;
					  display7SEG(clock_counter);
					  auto_status = 1;
				  }
		break;
	case 1:
		//YELLOW
				  HAL_GPIO_WritePin(GPIOA, OUT1_Pin, 0);
				  HAL_GPIO_WritePin(GPIOA, OUT0_Pin|OUT2_Pin, 1);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_RED;
					  display7SEG(clock_counter);
					  auto_status = 2;
				  }


		break;
	case 2:
		//RED
				  HAL_GPIO_WritePin(GPIOA, OUT2_Pin, 0);
				  HAL_GPIO_WritePin(GPIOA, OUT0_Pin|OUT1_Pin, 1);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_GREEN;
					  display7SEG(clock_counter);
					  auto_status = 0;
				  }
		break;
	}
}

//SECOND 7SEG OUT3->OUT5 & SEG0_1->SEG6_1
void fsm_auto_traffic_1(){
	switch(auto_status_1){
	case 0:
		//RED
				  HAL_GPIO_WritePin(GPIOA, OUT5_Pin, 0);
				  HAL_GPIO_WritePin(GPIOA, OUT4_Pin|OUT3_Pin, 1);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_GREEN;
					  display7SEG_1(clock_counter_1);
					  auto_status_1 = 2;
				  }
		break;
	case 1:
		//YELLOW
				  HAL_GPIO_WritePin(GPIOA, OUT4_Pin, 0);
				  HAL_GPIO_WritePin(GPIOA, OUT5_Pin|OUT3_Pin, 1);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_RED;
					  display7SEG_1(clock_counter_1);
					  auto_status_1 = 0;
				  }

		break;
	case 2:
		//GREEN
				  HAL_GPIO_WritePin(GPIOA, OUT3_Pin, 0);
				  HAL_GPIO_WritePin(GPIOA, OUT4_Pin|OUT5_Pin, 1);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_YELLOW;
					  display7SEG_1(clock_counter_1);
					  auto_status_1 = 1;
				  }
		break;
	}
}

//MODE 2
void blink_red()
{
	if(timer_flag[2] == 1)
	{
		HAL_GPIO_TogglePin(GPIOA, OUT2_Pin|OUT5_Pin);
		setTimer(25, 2);
	}
}

//MODE 3
void blink_yellow()
{
	if(timer_flag[2] == 1)
	{
		HAL_GPIO_TogglePin(GPIOA, OUT1_Pin|OUT4_Pin);
		setTimer(25, 2);
	}
}

//MODE 4
void blink_green()
{
	if(timer_flag[2] == 1)
	{
		HAL_GPIO_TogglePin(GPIOA, OUT0_Pin|OUT3_Pin);
		setTimer(25, 2);
	}
}

void fsm_traffic(){
	switch(manual_status)
	{
	case 0:
		fsm_auto_traffic();
		fsm_auto_traffic_1();
		if(isButtonPressed(0) == 1){
			manual_status = 1;
			display7SEG(2);
			display7SEG_1(BUFFER_RED);
			HAL_GPIO_WritePin(GPIOA, OUT0_Pin|OUT1_Pin|OUT2_Pin|OUT3_Pin|OUT4_Pin|OUT5_Pin, 1);
		}
		break;
	case 1:
		blink_red();
		if(isButtonPressed(0) == 1){
			manual_status = 2;
			display7SEG(3);
			display7SEG_1(BUFFER_YELLOW);
			HAL_GPIO_WritePin(GPIOA, OUT0_Pin|OUT1_Pin|OUT2_Pin|OUT3_Pin|OUT4_Pin|OUT5_Pin, 1);
		}
		if(isButtonPressed(1) == 1){
			BUFFER_RED++;
			if(BUFFER_RED == 10){BUFFER_RED = 0;}
			display7SEG_1(BUFFER_RED);
		}
		if(isButtonPressed(2) == 1){
			MAX_RED = BUFFER_RED;
		}
		break;
	case 2:
		blink_yellow();
		if(isButtonPressed(0) == 1){
			manual_status = 3;
			display7SEG(4);
			display7SEG_1(BUFFER_GREEN);
			HAL_GPIO_WritePin(GPIOA, OUT0_Pin|OUT1_Pin|OUT2_Pin|OUT3_Pin|OUT4_Pin|OUT5_Pin, 1);
		}
		if(isButtonPressed(1) == 1){
			BUFFER_YELLOW++;
			if(BUFFER_YELLOW == 10){BUFFER_YELLOW = 0;}
			display7SEG_1(BUFFER_YELLOW);
		}
		if(isButtonPressed(2) == 1){
			MAX_YELLOW = BUFFER_YELLOW;
		}
		break;
	case 3:
		blink_green();
		if(isButtonPressed(0) == 1){
			manual_status = 0;
			//CHECK CONDITIONS HERE
			if(BUFFER_RED != BUFFER_GREEN + BUFFER_YELLOW)
			{
				HAL_GPIO_TogglePin(GPIOA, OUT6_Pin);
				MAX_RED = 5;
				MAX_YELLOW = 2;
				MAX_GREEN = 3;
			}

			//RESET TRAFFIC
			auto_status = 0;
			auto_status_1 = 0;
			clock_counter = MAX_GREEN;
			clock_counter_1 = MAX_RED;
			setTimer(100, 1);
			display7SEG(clock_counter);
			display7SEG_1(clock_counter_1);

			//
			HAL_GPIO_WritePin(GPIOA, OUT0_Pin|OUT1_Pin|OUT2_Pin|OUT3_Pin|OUT4_Pin|OUT5_Pin, 1);
		}
		if(isButtonPressed(1) == 1){
			BUFFER_GREEN++;
			if(BUFFER_GREEN == 10){BUFFER_GREEN = 0;}
			display7SEG_1(BUFFER_GREEN);
		}
		if(isButtonPressed(2) == 1){
			MAX_GREEN = BUFFER_GREEN;
		}
		break;
	}
}
