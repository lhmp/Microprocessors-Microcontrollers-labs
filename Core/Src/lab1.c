#include "lab1.h"

void ex_1(){
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
	while (1)
	{
	  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	  HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
	  HAL_Delay(2000);
	}
}

void ex_2(){
	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, RESET);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);
	HAL_Delay(5000);

	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, RESET);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, SET);
	HAL_Delay(2000);

	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, SET);
	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, SET);
	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, RESET);
	HAL_Delay(3000);
}

void display7SEG(int num){
	char led7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
	for (int i = 0; i <= 7; i++){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, (led7[num] >> i) & 1);
	}
}

int counter = 0;
void ex_4(){
	if (counter >= 10) counter = 0;
	display7SEG(counter++);
	HAL_Delay(1000);

}

//PA8 - > 13 (R-Y-G)
int counter_led = 9;
void ex_5(){
	switch (counter_led){
	case 9:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET);
		display7SEG(4);
		counter_led--;
		break;
	case 8:
		display7SEG(3);
		counter_led--;
		break;
	case 7:
		display7SEG(2);
		counter_led--;
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_SET);
		display7SEG(1);
		counter_led--;
		break;
	case 5:
		display7SEG(0);
		counter_led--;
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_SET);
		display7SEG(2);
		counter_led--;
		break;
	case 3:
		display7SEG(1);
		counter_led--;
	case 2:
		display7SEG(0);
		counter_led--;
	case 1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		display7SEG(1);
		counter_led--;
		break;
	case 0:
		display7SEG(0);
		counter_led+=9;
		break;
	}
	HAL_Delay(1000);
}

uint16_t LEDpin [12] = {GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12};

void test_LED (int num){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LEDpin [num], GPIO_PIN_RESET);
}

void ex_6(){
	for (int i = 0; i < 12; i++){
		test_LED(i);
		HAL_Delay(1000);
	}
}

void clearAllClock(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_SET);
}

void setNumberOnClock(int num){
	HAL_GPIO_WritePin(GPIOB, LEDpin [num], GPIO_PIN_RESET);
}

void clearNumberOnClock(int num){
	HAL_GPIO_WritePin(GPIOB, LEDpin [num], GPIO_PIN_SET);
}

void ex_10(){
	clearAllClock();
	for (int i = 0; i < 12; i++){
		setNumberOnClock(i);
		HAL_Delay(100);
		for (int j = 0; j < 12; j++){
			setNumberOnClock(i);
			setNumberOnClock(j);
			HAL_Delay(100);
			for (int n = 0; n < 5; n++){
				for (int k = 0; k < 12; k++){
					setNumberOnClock(i);
					setNumberOnClock(j);
					setNumberOnClock(k);
					HAL_Delay(100);
					clearNumberOnClock(i);
					clearNumberOnClock(j);
					clearNumberOnClock(k);
				}
			}
			clearNumberOnClock(i);
			clearNumberOnClock(j);
		}
		clearNumberOnClock(i);
	}
	clearAllClock();
}

