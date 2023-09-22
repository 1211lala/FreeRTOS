#ifndef __WS2812_H__
#define __WS2812_H__

#include "main.h"
#include "tim.h"
#include ".\COLOR\color.h"

#define 	Pixel_NUM             8                  /*LED�����궨��*/
#define 	CODE_1               (87)                /*1�붨ʱ����������*/
#define 	CODE_0               (35)                /*0�붨ʱ����������*/
#define 	WS2812_TIM           &htim3          
#define   WS2812_CHANNEL       TIM_CHANNEL_1


/*LED��ԭɫֵ��С�Ľṹ��*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;



void WS2812_SetColor(uint8_t LedId,RGB_Color_TypeDef Color);                      /*��һ��LEDװ��24����ɫ������*/
void WS2812_Reset(void);                                                          /*�ú������ڽ��������24�����ݱ�Ϊ0 ����RESET_code*/
void WWS2812_SendArray(void);                                                     /*DMA�������ݺ���*/

void WS2812_SetLine(uint16_t Pixel_Len, RGB_Color_TypeDef Color);
void WS2812_SetAlone(uint16_t ID, RGB_Color_TypeDef Color);

RGB_Color_TypeDef WS2812_SetBrightness(float num, RGB_Color_TypeDef rgb);

#endif
