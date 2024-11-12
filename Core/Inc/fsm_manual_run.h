/*
 * fsm_manual_run.h
 *
 *  Created on: Nov 11, 2024
 *      Author: maiph
 */

#ifndef INC_FSM_MANUAL_RUN_H_
#define INC_FSM_MANUAL_RUN_H_

#include "main.h"
#include "button.h"
#include "timer.h"
#include "global.h"
#include "7seg.h"

void fsm_LED();
void fsm_simple_buttons_run();
void fsm_traffic();
void fsm_clock_counter();
void fsm_auto_traffic();

extern int clock_counter;

#endif /* INC_FSM_MANUAL_RUN_H_ */
