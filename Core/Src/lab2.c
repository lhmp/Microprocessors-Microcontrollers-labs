/*
 * lab2.c
 *
 *  Created on: Oct 1, 2024
 *      Author: maiph
 */

#include "main.h"
#include "lab2.h"

void display7SEG(int num){
	char led7[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
	for (int i = 0; i <= 7; i++){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 << i, (led7[num] >> i) & 1);
	}
}

//int hour = 15, minute = 8, second = 50;
////void updateClockBuffer(){
////	led_buffer[0] = hour/10;
////	led_buffer[1] = hour%10;
////	led_buffer[2] = minute/10;
////	led_buffer[3] = minute%10;
////}
//
//void updateClockBuffer(){
//	if (hour<9) led_buffer[0] = 0;
//	else led_buffer[0] = hour/10;
//	if (minute<9) led_buffer[2] = 0;
//	else led_buffer[2] = minute/10;
//
//	led_buffer[1] = hour%10;
//	led_buffer[3] = minute%10;
//}

//int led_buffer[4] = {1,5,0,8};
//
//void update7SEG (int index){
//	switch (index){
//	case 0:
//		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
//		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
//		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
//		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
//		display7SEG(led_buffer[0]);
//		break;
//	case 1:
//		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
//		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
//		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
//		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
//		display7SEG(led_buffer[1]);
//		break;
//	case 2:
//		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
//		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
//		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
//		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
//		display7SEG(led_buffer[2]);
//		break;
//	case 3:
//		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
//		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
//		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
//		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
//		display7SEG(led_buffer[3]);
//		break;
//
//	default:
//		break;
//	}
//}

//void updateMatrixBuffer(){
//	for (int i=0; i<8; i++){
//		uint8_t shift_left = matrix_buffer[i]<<1;
//		uint8_t shift_right = matrix_buffer[i]>>7;
//		matrix_buffer[i] = shift_left | shift_right;
//	}
//}

//const int MAX_LED_MATRIX = 8;
//int index_led_matrix = 0;
//uint8_t matrix_buffer[8] = {0x01, 0x06, 0x38, 0xC8, 0xC8, 0x38, 0x06, 0x01};
//uint16_t row_pin[8] = {ROW0_Pin,ROW1_Pin,ROW2_Pin,ROW3_Pin,ROW4_Pin,ROW5_Pin,ROW6_Pin,ROW7_Pin};
//uint16_t col_pin[8] = {ENM0_Pin,ENM1_Pin,ENM2_Pin,ENM3_Pin,ENM4_Pin,ENM5_Pin,ENM6_Pin,ENM7_Pin};
//uint8_t charA[8] = {0x01, 0x06, 0x38, 0xC8, 0xC8, 0x38, 0x06, 0x01};
//
//void updateLEDMatrix(int index){
//	for (int i = 0; i < 8; i++){
//		HAL_GPIO_WritePin(GPIOA, col_pin[i], 0);
//		HAL_GPIO_WritePin(GPIOB, row_pin[i], 0);
//	}
//    switch (index){
//        case 0:
//			HAL_GPIO_WritePin(GPIOA, col_pin[i], 1);
//			for (int i = 0; i < 8; i++){
//				if (matrix_buffer[index] & (0x80 >> i)){
//					HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
//				}
//			}
//            break;
//        case 1:
//        	HAL_GPIO_WritePin(GPIOA, col_pin[1], 1);
//        	for (int i = 0; i < 8; i++){
//        		if (matrix_buffer[index] & (0x80 >> i)){
//        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
//        		}
//        	}
//            break;
//        case 2:
//        	HAL_GPIO_WritePin(GPIOA, col_pin[2], 1);
//        	for (int i = 0; i < 8; i++){
//        		if (matrix_buffer[index] & (0x80 >> i)){
//        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
//        		}
//        	}
//            break;
//        case 3:
//        	HAL_GPIO_WritePin(GPIOA, col_pin[3], 1);
//        	for (int i = 0; i < 8; i++){
//        		if (matrix_buffer[index] & (0x80 >> i)){
//        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
//        		}
//        	}
//            break;
//        case 4:
//        	HAL_GPIO_WritePin(GPIOA, col_pin[4], 1);
//        	for (int i = 0; i < 8; i++){
//        		if (matrix_buffer[index] & (0x80 >> i)){
//        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
//        		}
//        	}
//            break;
//        case 5:
//        	HAL_GPIO_WritePin(GPIOA, col_pin[5], 1);
//        	for (int i = 0; i < 8; i++){
//        		if (matrix_buffer[index] & (0x80 >> i)){
//        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
//        		}
//        	}
//            break;
//        case 6:
//        	HAL_GPIO_WritePin(GPIOA, col_pin[6], 1);
//        	for (int i = 0; i < 8; i++){
//        		if (matrix_buffer[index] & (0x80 >> i)){
//        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
//        		}
//        	}
//            break;
//        case 7:
//        	HAL_GPIO_WritePin(GPIOA, col_pin[7], 1);
//        	for (int i = 0; i < 8; i++){
//        		if (matrix_buffer[index] & (0x80 >> i)){
//        			HAL_GPIO_WritePin(GPIOB, row_pin[i], 1);
//        		}
//        	}
//            break;
//        default:
//            break;
//    }
//}

//uint8_t matrix_buffer[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
//int matrix_index = 0;
//void updateMatrixBuffer(){
//	for (int i=0; i<8; i++){
//		uint8_t shift_left = matrix_buffer[i]<<1;
//		uint8_t shift_right = matrix_buffer[i]>>7;
//		matrix_buffer[i] = shift_left | shift_right;
//	}
//}
//void displayMatrixLedCol(int number, int state){
//	if (number == 0) HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, state);
//	if (number == 1) HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, state);
//	if (number == 2) HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, state);
//	if (number == 3) HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, state);
//	if (number == 4) HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, state);
//	if (number == 5) HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, state);
//	if (number == 6) HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, state);
//	if (number == 7) HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, state);
//}
//void displayMatrixLedRow(int number){
//	if (number == 0) HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, 0);
//	if (number == 1) HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, 0);
//	if (number == 2) HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, 0);
//	if (number == 3) HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, 0);
//	if (number == 4) HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, 0);
//	if (number == 5) HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, 0);
//	if (number == 6) HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, 0);
//	if (number == 7) HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, 0);
//}
//void resetMatrix(){
//  HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);
//  HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
//  HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
//  HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
//  HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
//  HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
//  HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
//  HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
//
//  HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, 1);
//  HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, 1);
//  HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, 1);
//  HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, 1);
//  HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, 1);
//  HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, 1);
//  HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, 1);
//  HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, 1);
//}
//
//void displayMatrixLed(){
//	int bitStatus;
//	displayMatrixLedRow(matrix_index);
//	for (int nth = 0; nth<8; nth++){
//		bitStatus = (matrix_buffer[matrix_index]>>nth)&1;
//		displayMatrixLedCol(nth, bitStatus);
//	}
//}

