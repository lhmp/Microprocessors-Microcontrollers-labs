/*
 * timer.c
 *
 *  Created on: Dec 9, 2024
 *      Author: maiph
 */

#include"timer.h"

void HAL_TIM_PeriodElapsedCallback (TIM_HandleTypeDef * htim)
{
	timerRun();
}

void setAllTimer(int duration)
{
	for(int i = 0; i < TIMER_COUNT; i++) setTimer(duration, i);
}

void setTimer(int duration, int index)
{
	timer_flag[index] = 0;
	timer_counter[index] = duration;
}

void timerRun()
{
	for(int i = 0; i < TIMER_COUNT; i++){
	if(timer_counter[i] > 0)
	{
		timer_counter[i]--;
		if(timer_counter[i] <= 0)
		{
			timer_flag[i] = 1;
		}
	}
	}
}

