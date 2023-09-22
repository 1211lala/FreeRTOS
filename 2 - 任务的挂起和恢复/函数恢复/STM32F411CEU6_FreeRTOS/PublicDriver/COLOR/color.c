#include ".\COLOR\color.h"


static float min(float a, float b, float c)
{
  float m;
  
  m = a < b ? a : b;
  return (m < c ? m : c); 
}

static float max(float a, float b, float c)
{
  float m;
  
  m = a > b ? a : b;
  return (m > c ? m : c); 
}
  
/*RGB -> HSV*/
void rgb2hsv(uint8_t r, uint8_t g, uint8_t b, float *h, float *s, float *v)
{
  float red, green ,blue;
  float cmax, cmin, delta;
  
  red = (float)r / 255;
  green = (float)g / 255;
  blue = (float)b / 255;
  
  cmax = max(red, green, blue);
  cmin = min(red, green, blue);
  delta = cmax - cmin;

  /* H */
  if(delta == 0)
  {
    *h = 0;
  }
  else
  {
    if(cmax == red)
    {
      if(green >= blue)
      {
        *h = 60 * ((green - blue) / delta);
      }
      else
      {
        *h = 60 * ((green - blue) / delta) + 360;
      }
    }
    else if(cmax == green)
    {
      *h = 60 * ((blue - red) / delta + 2);
    }
    else if(cmax == blue) 
    {
      *h = 60 * ((red - green) / delta + 4);
    }
  }
  
  /* S */
  if(cmax == 0)
  {
    *s = 0;
  }
  else
  {
    *s = delta / cmax;
  }
  
  /* V */
  *v = cmax;
}
  

/*HSV -> RGB*/
void hsv2rgb(float h, float s, float v, uint8_t *r, uint8_t *g, uint8_t *b)
{
    int hi = ((int)h / 60) % 6;
    float f = h * 1/ 60 - hi;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1- (1 - f) * s);
    switch (hi)
		{
        case 0:
            *r = 255 * v;
            *g = 255 * t;
            *b = 255 * p;
            break;
        case 1:
            *r = 255 * q;
            *g = 255 * v;
            *b = 255 * p;
            break;
        case 2:
            *r = 255 * p;
            *g = 255 * v;
            *b = 255 * t;
            break;
        case 3:
            *r = 255 * p;
            *g = 255 * q;
            *b = 255 * v;
            break;
        case 4:
            *r = 255 * t;
            *g = 255 * p;
            *b = 255 * v;
            break;
        case 5:
            *r = 255 * v;
            *g = 255 * p;
            *b = 255 * q;
            break;
    }
}



unsigned short RGBToRGB565(uint8_t r, uint8_t g, uint8_t b)
{
	return ( r << 16 | g << 8 | b);
}
 
unsigned short RGB888ToRGB565(unsigned int Color888)
{
	unsigned short Color565 = 0;
 
	/* 获取RGB单色，并截取高位 */
	unsigned char Red   = (Color888 & RGB888_RED)   >> 19;
	unsigned char Green = (Color888 & RGB888_GREEN) >> 10;
	unsigned char Blue  = (Color888 & RGB888_BLUE)  >> 3;
 
	Color565 = (Red << 11) + (Green << 5) + (Blue << 0);
	return Color565;
}
 
unsigned int RGB565ToRGB888(unsigned short Color565)
{
	unsigned int Color888 = 0;
 
	/* 获取RGB单色，并填充低位 */
	unsigned char Red   = (Color565 & RGB565_RED)    >> 8;
	unsigned char Green = (Color565 & RGB565_GREEN)  >> 3;
	unsigned char Blue  = (Color565 & RGB565_BLUE)   << 3;
 
	Color888 = (Red << 16) + (Green << 8) + (Blue << 0);
	return Color888;
}

/*获取随机数*/
uint32_t RNG_GetRandomNumber(uint32_t min,uint32_t max)
{
	return rand()%(max - min + 1) + min;    
}
