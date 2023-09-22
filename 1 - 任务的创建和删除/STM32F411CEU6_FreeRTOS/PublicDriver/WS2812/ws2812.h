#ifndef __WS2812_H__
#define __WS2812_H__

#include "main.h"
#include "tim.h"
#include ".\COLOR\color.h"

#define 	Pixel_NUM             8                  /*LED数量宏定义*/
#define 	CODE_1               (87)                /*1码定时器计数次数*/
#define 	CODE_0               (35)                /*0码定时器计数次数*/
#define 	WS2812_TIM           &htim3          
#define   WS2812_CHANNEL       TIM_CHANNEL_1


/*LED三原色值大小的结构体*/
typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}RGB_Color_TypeDef;



void WS2812_SetColor(uint8_t LedId,RGB_Color_TypeDef Color);                      /*给一个LED装载24个颜色数据码*/
void WS2812_Reset(void);                                                          /*该函数用于将数组最后24个数据变为0 代表RESET_code*/
void WWS2812_SendArray(void);                                                     /*DMA发送数据函数*/

void WS2812_SetLine(uint16_t Pixel_Len, RGB_Color_TypeDef Color);
void WS2812_SetAlone(uint16_t ID, RGB_Color_TypeDef Color);

RGB_Color_TypeDef WS2812_SetBrightness(float num, RGB_Color_TypeDef rgb);

#endif
