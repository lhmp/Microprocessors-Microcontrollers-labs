/*
 * fsm_automatic.h
 *
 *  Created on: Dec 4, 2024
 *      Author: maiph
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

#include "main.h"
#include "button.h"
#include "timer.h"
#include "global.h"
#include "lcd.h"

void turnonTrafficLight1(int led);
void turnonTrafficLight2(int led);
void fsm_LED();
void fsm_simple_buttons_run();
void fsm_traffic();
void fsm_clock_counter();
void fsm_auto_traffic();
void fsm_auto_traffic_1();

extern int clock_counter;

#endif /* INC_FSM_AUTOMATIC_H_ */
