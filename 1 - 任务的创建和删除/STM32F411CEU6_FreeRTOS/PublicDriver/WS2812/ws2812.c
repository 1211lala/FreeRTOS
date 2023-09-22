#include ".\WS2812\ws2812.h"
 
uint32_t Pixel_Buf[Pixel_NUM+1][24];   	        /*���ݴ洢����*/


void WWS2812_SendArray(void)
{
	HAL_TIM_PWM_Start_DMA(WS2812_TIM, WS2812_CHANNEL, (uint32_t *)Pixel_Buf, (Pixel_NUM+1)*24);
}


 /*����:���һ��װ��24��0,���24������ռ�ձ�Ϊ0��PWM��,��Ϊ���reset��ʱ,������ʱ��Ϊ24*1.2=30us > 24us(Ҫ�����24us)*/
void WS2812_Reset(void)
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		Pixel_Buf[Pixel_NUM][i] = 0;
	}
}

/*����:LedIdΪLED���,Color:�������ɫ�ṹ��*/
void WS2812_SetColor(uint8_t LedId,RGB_Color_TypeDef Color)
{
	uint8_t i; 
	if(LedId > Pixel_NUM)return; 
	
	for(i=0;i<8;i++)   Pixel_Buf[LedId][i] = ( (Color.G & (1 << (7 -i)))? (CODE_1):CODE_0 );        /*����ĳһ��0~7ת�����G*/
	for(i=8;i<16;i++)  Pixel_Buf[LedId][i] = ( (Color.R & (1 << (15-i)))? (CODE_1):CODE_0 );        /*����ĳһ��8~15ת�����R*/
	for(i=16;i<24;i++) Pixel_Buf[LedId][i] = ( (Color.B & (1 << (23-i)))? (CODE_1):CODE_0 );        /*����ĳһ��16~23ת�����B*/
}
 

 
/*���ù̶������������ɫ*/
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


/*��������һ��WS2812����ɫ*/
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
