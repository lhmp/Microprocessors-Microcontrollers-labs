/*
 * 7seg.c
 *
 *  Created on: Nov 11, 2024
 *      Author: maiph
 */

#include "7seg.h"

void display7SEG(int c)
{
	HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, 1);
	switch(c){
	case 0:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin,0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB,SEG0_Pin|SEG1_Pin|SEG3_Pin|SEG4_Pin|SEG6_Pin,0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin |SEG6_Pin, 0);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin|SEG5_Pin|SEG6_Pin, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin | SEG5_Pin | SEG6_Pin, 0);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, 0);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin, 0);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin, 0);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|SEG3_Pin|SEG5_Pin|SEG6_Pin, 0);
		break;
	}
}
void display7SEG_1(int c)
{
	HAL_GPIO_WritePin(GPIOA, S0_Pin|S1_Pin|S2_Pin|S3_Pin|S4_Pin|S5_Pin|S6_Pin, 1);
	switch(c){
	case 0:
		HAL_GPIO_WritePin(GPIOA, S0_Pin|S1_Pin|S2_Pin|S3_Pin|S4_Pin|S5_Pin, 0);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOA, S1_Pin|S2_Pin,0);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOA,S0_Pin|S1_Pin|S3_Pin|S4_Pin|S6_Pin,0);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOA, S0_Pin|S1_Pin|S2_Pin|S3_Pin|S6_Pin, 0);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOA, S1_Pin|S2_Pin|S5_Pin|S6_Pin, 0);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOA, S0_Pin|S2_Pin|S3_Pin|S5_Pin|S6_Pin, 0);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOA, S0_Pin|S2_Pin|S3_Pin|S4_Pin|S5_Pin|S6_Pin, 0);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOA, S0_Pin|S1_Pin|S2_Pin, 0);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOA, S0_Pin|S1_Pin|S2_Pin|S3_Pin|S4_Pin|S5_Pin|S6_Pin, 0);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOA, S0_Pin|S1_Pin|S2_Pin|S3_Pin|S5_Pin|S6_Pin, 0);
		break;
	}
}
