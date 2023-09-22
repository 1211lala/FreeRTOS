#ifndef __COLOR_H__
#define __COLOR_H__


#include "main.h"
#include "stdlib.h"

#define RGB888_RED      0x00ff0000
#define RGB888_GREEN    0x0000ff00
#define RGB888_BLUE     0x000000ff
 
#define RGB565_RED      0xf800
#define RGB565_GREEN    0x07e0
#define RGB565_BLUE     0x001f


void rgb2hsv(uint8_t r, uint8_t g, uint8_t b, float *h, float *s, float *v);  /*颜色算法 RGB-> hsv*/
void hsv2rgb(float h, float s, float v, uint8_t *r, uint8_t *g, uint8_t *b);  /*颜色算法 hsv-> RGB*/
unsigned short RGBToRGB565(uint8_t r, uint8_t g, uint8_t b);                  /*颜色算法rgb -> RGB565*/
unsigned short RGB888ToRGB565(unsigned int Color888);                         /*颜色算法RGB888 -> RGB565*/  
unsigned int RGB565ToRGB888(unsigned short Color565);                         /*颜色算法RGB565 -> RGB888*/

uint32_t RNG_GetRandomNumber(uint32_t min,uint32_t max);                        /*获取随机数*/
#endif
