/*
 * timer.h
 *
 *  Created on: Dec 4, 2024
 *      Author: maiph
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "global.h"
#include "main.h"
#include "button.h"

//#include "scheduler.h"
extern int timer_delay[TIMER_COUNT];
extern int timer_counter[TIMER_COUNT];
extern int timer_flag[TIMER_COUNT];

void timerRun();
void setAllTimer(int duration);
void setTimer(int duration, int index);

#endif /* INC_TIMER_H_ */
