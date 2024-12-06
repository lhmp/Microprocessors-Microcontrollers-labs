/*
 * button.c
 *
 *  Created on: Nov 11, 2024
 *      Author: maiph
 */

#include "button.h"
#include "lcd.h"

int KeyReg0[BUTTON_COUNT] = {NORMAL_STATE};
int KeyReg1[BUTTON_COUNT] = {NORMAL_STATE};
int KeyReg2[BUTTON_COUNT] = {NORMAL_STATE};
int KeyReg3[BUTTON_COUNT] = {NORMAL_STATE};
int counter[BUTTON_COUNT] = {0};
int button[] = {button_mode_Pin, button_time_Pin, button_set_Pin};
int TimeOutForKeyPress[BUTTON_COUNT] = {KEY_TIMED_OUT};
int button_flag[BUTTON_COUNT] = {0}; //Init button flag to 0
int button_long_flag[BUTTON_COUNT] = {0};

void subKeyProcess(int index) //Used to set button at index flag
{
	button_flag[index] = 1;
}

void subKeyLongProcess(int index)
{
	button_long_flag[index] = 1;
}

int isButtonPressed(int index) //Check button at index is pressed or not
{
	if(button_flag[index] == 1){
		button_flag[index] = 0; //Reset flag
		return 1;
	}
	else return 0;
}

int isButtonLongPressed(int index){
	if(button_long_flag[index] == 1){
		button_long_flag[index] = 0; //Reset flag
		return 1;
	}
	else return 0;
}

GPIO_TypeDef* buttonPorts[] = {GPIOA, GPIOA, GPIOC};
uint16_t buttonPins[] = {GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_7};
void getKeyInput()
{
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[i] = HAL_GPIO_ReadPin(buttonPorts[i], buttonPins[i]);
		//Debouncing
		if((KeyReg1[i] == KeyReg0[i])
		&&(KeyReg1[i] == KeyReg2[i])) //If all 3 registers have the same values
		{
			if(KeyReg3[i] != KeyReg2[i])
			{
				KeyReg3[i] = KeyReg2[i];

				if(KeyReg2[i] == PRESSED_STATE)
				{
					subKeyProcess(i);
					TimeOutForKeyPress[i] = KEY_TIMED_OUT;
				}
			}
			else
			{
				TimeOutForKeyPress[i]--;
				if (TimeOutForKeyPress[i] == 0){
					if(KeyReg2[i] == PRESSED_STATE)
					{
						subKeyProcess(i);
					}
					TimeOutForKeyPress[i] = KEY_TIMED_OUT;
				}
			}
		}
	}
}
