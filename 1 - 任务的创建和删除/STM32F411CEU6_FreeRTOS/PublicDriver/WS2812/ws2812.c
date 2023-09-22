#include ".\WS2812\ws2812.h"
 
uint32_t Pixel_Buf[Pixel_NUM+1][24];   	        /*数据存储数组*/


void WWS2812_SendArray(void)
{
	HAL_TIM_PWM_Start_DMA(WS2812_TIM, WS2812_CHANNEL, (uint32_t *)Pixel_Buf, (Pixel_NUM+1)*24);
}


 /*功能:最后一行装在24个0,输出24个周期占空比为0的PWM波,作为最后reset延时,这里总时长为24*1.2=30us > 24us(要求大于24us)*/
void WS2812_Reset(void)
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		Pixel_Buf[Pixel_NUM][i] = 0;
	}
}

/*参数:LedId为LED序号,Color:定义的颜色结构体*/
void WS2812_SetColor(uint8_t LedId,RGB_Color_TypeDef Color)
{
	uint8_t i; 
	if(LedId > Pixel_NUM)return; 
	
	for(i=0;i<8;i++)   Pixel_Buf[LedId][i] = ( (Color.G & (1 << (7 -i)))? (CODE_1):CODE_0 );        /*数组某一行0~7转化存放G*/
	for(i=8;i<16;i++)  Pixel_Buf[LedId][i] = ( (Color.R & (1 << (15-i)))? (CODE_1):CODE_0 );        /*数组某一行8~15转化存放R*/
	for(i=16;i<24;i++) Pixel_Buf[LedId][i] = ( (Color.B & (1 << (23-i)))? (CODE_1):CODE_0 );        /*数组某一行16~23转化存放B*/
}
 

 
/*设置固定数量灯珠的颜色*/
void WS2812_SetLine(uint16_t Pixel_Len, RGB_Color_TypeDef Color)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)
	{
		WS2812_SetColor(i,Color);
	}
	WS2812_Reset();
	WWS2812_SendArray();
}


/*单独设置一个WS2812的颜色*/
void WS2812_SetAlone(uint16_t ID, RGB_Color_TypeDef Color)
{
	WS2812_SetColor(ID,Color);
	WS2812_Reset();
	WWS2812_SendArray();
}
 

RGB_Color_TypeDef WS2812_SetBrightness(float num, RGB_Color_TypeDef rgb)
{
  float h, s,v;
  rgb2hsv(rgb.R, rgb.G, rgb.B, &h, &s, &v);
  v=num;
  hsv2rgb(h, s, v, &rgb.R, &rgb.G, &rgb.B);
  return rgb;
}
