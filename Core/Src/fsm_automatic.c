/*
 * fsm_automatic.c
 *
 *  Created on: Dec 4, 2024
 *      Author: maiph
 */

#include "fsm_automatic.h"
#include "lcd.h"

int auto_status = 0;
int auto_status_1 = 0;
int clock_counter = 3;
int clock_counter_1 = 5;
int manual_status = 0;

int BUFFER_RED = 5;
int BUFFER_YELLOW = 2;
int BUFFER_GREEN = 3;

int MAX_RED = 5;
int MAX_YELLOW = 2;
int MAX_GREEN = 3;

void fsm_clock_counter()
{

	if(timer_flag[0] == 1)
	{
		setTimer(100, 0);
	}
	if(timer_flag[1] == 1 && (manual_status == 0))
	{
		clock_counter--;
		clock_counter_1--;
		setTimer(100, 1);
	}
	HAL_GPIO_TogglePin(PA5_GPIO_Port, PA5_Pin);
}

//FIRST 7SEG OUT0->OUT2 & SEG0->SEG6
void fsm_auto_traffic(){
	switch(auto_status){
	case 0:
		//GREEN
				lcd_goto_XY(0, 6);
				lcd_send_num(clock_counter);
				HAL_GPIO_WritePin(Traffic_light_1_1_GPIO_Port, Traffic_light_1_1_Pin, SET);
				HAL_GPIO_WritePin(Traffic_light_1_2_GPIO_Port, Traffic_light_1_2_Pin, RESET);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_YELLOW;
					  auto_status = 1;
				  }
		break;
	case 1:
		//YELLOW
				lcd_goto_XY(0, 6);
				lcd_send_num(clock_counter);
				HAL_GPIO_WritePin(Traffic_light_1_1_GPIO_Port, Traffic_light_1_1_Pin, RESET);
				HAL_GPIO_WritePin(Traffic_light_1_2_GPIO_Port, Traffic_light_1_2_Pin, SET);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_RED;
					  auto_status = 2;
				  }


		break;
	case 2:
		//RED
				lcd_goto_XY(0, 6);
				lcd_send_num(clock_counter);
				HAL_GPIO_WritePin(Traffic_light_1_1_GPIO_Port, Traffic_light_1_1_Pin, SET);
				HAL_GPIO_WritePin(Traffic_light_1_2_GPIO_Port, Traffic_light_1_2_Pin, SET);
				  if(clock_counter == 0)
				  {
					  clock_counter = MAX_GREEN;
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
				lcd_goto_XY(0, 14);
				lcd_send_num(clock_counter_1);
				HAL_GPIO_WritePin(Traffic_light_2_1_GPIO_Port, Traffic_light_2_1_Pin, SET);
				HAL_GPIO_WritePin(Traffic_light_2_2_GPIO_Port, Traffic_light_2_2_Pin, SET);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_GREEN;
					  auto_status_1 = 2;
				  }
		break;
	case 1:
		//YELLOW
				lcd_goto_XY(0, 14);
				lcd_send_num(clock_counter_1);
				HAL_GPIO_WritePin(Traffic_light_2_1_GPIO_Port, Traffic_light_2_1_Pin, RESET);
				HAL_GPIO_WritePin(Traffic_light_2_2_GPIO_Port, Traffic_light_2_2_Pin, SET);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_RED;
					  auto_status_1 = 0;
				  }

		break;
	case 2:
		//GREEN
				lcd_goto_XY(0, 14);
				lcd_send_num(clock_counter_1);
				HAL_GPIO_WritePin(Traffic_light_2_1_GPIO_Port, Traffic_light_2_1_Pin, SET);
				HAL_GPIO_WritePin(Traffic_light_2_2_GPIO_Port, Traffic_light_2_2_Pin, RESET);
				  if(clock_counter_1 == 0)
				  {
					  clock_counter_1 = MAX_YELLOW;
					  auto_status_1 = 1;
				  }
		break;
	}
}

void blink_red()
{
	if(timer_flag[2] == 1)
	{
		HAL_GPIO_WritePin(Traffic_light_1_1_GPIO_Port, Traffic_light_1_1_Pin, SET);
		HAL_GPIO_WritePin(Traffic_light_1_2_GPIO_Port, Traffic_light_1_2_Pin, SET);
		HAL_GPIO_WritePin(Traffic_light_2_1_GPIO_Port, Traffic_light_2_1_Pin, SET);
		HAL_GPIO_WritePin(Traffic_light_2_2_GPIO_Port, Traffic_light_2_2_Pin, SET);
		setTimer(25, 2);
	}
}

//MODE 3
void blink_yellow()
{
	if(timer_flag[2] == 1)
	{
		HAL_GPIO_WritePin(Traffic_light_1_1_GPIO_Port, Traffic_light_1_1_Pin, RESET);
		HAL_GPIO_WritePin(Traffic_light_1_2_GPIO_Port, Traffic_light_1_2_Pin, SET);
		HAL_GPIO_WritePin(Traffic_light_2_1_GPIO_Port, Traffic_light_2_1_Pin, RESET);
		HAL_GPIO_WritePin(Traffic_light_2_2_GPIO_Port, Traffic_light_2_2_Pin, SET);
		setTimer(25, 2);
	}
}

//MODE 4
void blink_green()
{
	if(timer_flag[2] == 1)
	{
		HAL_GPIO_WritePin(Traffic_light_1_1_GPIO_Port, Traffic_light_1_1_Pin, SET);
		HAL_GPIO_WritePin(Traffic_light_1_2_GPIO_Port, Traffic_light_1_2_Pin, RESET);
		HAL_GPIO_WritePin(Traffic_light_2_1_GPIO_Port, Traffic_light_2_1_Pin, SET);
		HAL_GPIO_WritePin(Traffic_light_2_2_GPIO_Port, Traffic_light_2_2_Pin, RESET);
		setTimer(25, 2);
	}
}

int mode = 0;
void fsm_traffic(){
	switch(manual_status)
	{
	case 0:
		fsm_auto_traffic();
		fsm_auto_traffic_1();
		if(isButtonPressed(0) == 1){
			manual_status = 1;
		}

		break;
	case 1:
		blink_red();
		if(isButtonPressed(0) == 1){
			manual_status = 2;
		}
		lcd_goto_XY(0, 5);
		lcd_send_num(BUFFER_RED);
		if(isButtonPressed(1) == 1){
			BUFFER_RED++;
			if(BUFFER_RED == 10){BUFFER_RED = 0;}
		}
		if(isButtonPressed(2) == 1){
			MAX_RED = BUFFER_RED;
		}
		break;
	case 2:
		blink_yellow();
		if(isButtonPressed(0) == 1){
			manual_status = 3;
		}
		lcd_goto_XY(0, 8);
		lcd_send_num(BUFFER_YELLOW);
		if(isButtonPressed(1) == 1){
			BUFFER_YELLOW++;
			if(BUFFER_YELLOW == 10){
				BUFFER_YELLOW = 0;
			}
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
		}
		lcd_goto_XY(0, 7);
		lcd_send_num(BUFFER_GREEN);
		if(isButtonPressed(1) == 1){
			BUFFER_GREEN++;
			if(BUFFER_GREEN == 10){BUFFER_GREEN = 0;}
		}
		if(isButtonPressed(2) == 1){
			MAX_GREEN = BUFFER_GREEN;
		}
		break;
	}


	switch (manual_status){
	case 0:
		if (manual_status == mode){
			lcd_clear_display();
		}
		lcd_goto_XY(1, 0);
		lcd_send_string("MODE 1");
		lcd_goto_XY(0, 0);
		lcd_send_string("ROAD1:");
		lcd_goto_XY(0, 8);
		lcd_send_string("ROAD2:");
		mode = 1;
		break;
	case 1:
		if (manual_status == mode){
			lcd_clear_display();
		}
		lcd_goto_XY(1, 0);
		lcd_send_string("MODE 2");
		lcd_goto_XY(0, 0);
		lcd_send_string("RED:");
		mode = 2;
		break;
	case 2:
		if (manual_status == mode){
			lcd_clear_display();
		}
		lcd_goto_XY(1, 0);
		lcd_send_string("MODE 3");
		lcd_goto_XY(0, 0);
		lcd_send_string("YELLOW:");
		mode = 3;
		break;
	case 3:
		if (manual_status == mode){
			lcd_clear_display();
		}
		lcd_goto_XY(1, 0);
		lcd_send_string("MODE 4");
		lcd_goto_XY(0, 0);
		lcd_send_string("GREEN:");
		mode = 0;
		break;
	}
}


