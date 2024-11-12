/*
 * button.h
 *
 *  Created on: Nov 11, 2024
 *      Author: maiph
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#include "global.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define KEY_TIMED_OUT 100
extern int button_flag[BUTTON_COUNT];

void getKeyInput();
int isButtonPressed(int);
int isButtonLongPressed(int);

#endif /* INC_BUTTON_H_ */
