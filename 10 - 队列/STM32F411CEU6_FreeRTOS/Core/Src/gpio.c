/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, led_red_Pin|led_blue_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(led_green_GPIO_Port, led_green_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_DC_Pin|LCD_RST_Pin|LCD_PWR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = key_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(key_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = led_red_Pin|led_green_Pin|led_blue_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = key_s1_Pin|key_s2_Pin|key_s3_Pin|key_s4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = LCD_DC_Pin|LCD_RST_Pin|LCD_PWR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
uint8_t Get_key(uint8_t mode)
{
	/* 保存uwtick的值 */
	static uint32_t tick;
	/* 按键标志位 */
	static uint8_t flag = 0;
	uint8_t key_s1_status,key_s2_status,key_s3_status,key_s4_status;
	
	key_s1_status = HAL_GPIO_ReadPin(key_s1_GPIO_Port, key_s1_Pin);
	key_s2_status = HAL_GPIO_ReadPin(key_s2_GPIO_Port, key_s2_Pin);
	key_s3_status = HAL_GPIO_ReadPin(key_s3_GPIO_Port, key_s3_Pin);
	key_s4_status = HAL_GPIO_ReadPin(key_s4_GPIO_Port, key_s4_Pin);
	
	/* 如果有案件按下 进入 if 保持当前 uwtick的值 */
	if(flag == 0 && (key_s1_status != 1 || key_s2_status != 1 || key_s3_status != 1 || key_s4_status != 1))
	{
		flag = 1;
		tick = uwTick;
	}
	/* 上一步有按键按下后 等待 100ms 如果还是满足if里面的案件检测, 说明确实有按键按下返回标号 */
	if(flag == 1 &&  (uwTick - tick ) > 100)
	{
		if(flag == 1 && key_s1_status == 0 && key_s2_status == 1 && key_s3_status == 1 && key_s4_status == 1)
		{
			flag = 2;
			return s1_down;
		}
		else if(flag == 1 && key_s1_status == 1 && key_s2_status == 0 && key_s3_status == 1 && key_s4_status == 1)
		{
			flag = 2;
			return s2_down;
		}
		else if(flag == 1 && key_s1_status == 1 && key_s2_status == 1 && key_s3_status == 0 && key_s4_status == 1)
		{
			flag = 2;
			return s3_down;
		}
		else if(flag == 1 && key_s1_status == 1 && key_s2_status == 1 && key_s3_status == 1 && key_s4_status == 0)
		{
			flag = 2;
			return s4_down;
		}
	}
	
	/* 在没有案件按下时令flag =0 等待按键按下 */
	if(key_s1_status == 1 && key_s2_status == 1 && key_s3_status == 1 && key_s4_status == 1)
	{
		flag = 0;
	}
	return key_null;
}
/* USER CODE END 2 */
