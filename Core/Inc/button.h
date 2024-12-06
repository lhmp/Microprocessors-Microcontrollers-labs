/*
 * button.h
 *
 *  Created on: Oct 5, 2023
 *      Author: KAI
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "global.h"
#include "lcd.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define KEY_TIMED_OUT 100
extern int button_flag[BUTTON_COUNT];

void getKeyInput();
int isButtonPressed(int);
int isButtonLongPressed(int);

#endif /* INC_BUTTON_H_ */

