#include "WS2812B.h"
#include "stdlib.h"
#include <math.h>

uint32_t WS2812B_BUFF[LED_NUM + RESET_NUM * 2][24];




// RGB转HSV函数
HSVColor rgb_to_hsv(RGBColor rgb) {
    HSVColor hsv;
    float r = rgb.r / 255.0f;
    float g = rgb.g / 255.0f;
    float b = rgb.b / 255.0f;

    float max = fmaxf(r, fmaxf(g, b));
    float min = fminf(r, fminf(g, b));
    float delta = max - min;

    // 计算明度 (Value)
    hsv.v = max;

    // 处理灰度色（无颜色）
    if (delta < 0.00001f) {
        hsv.h = 0.0f;
        hsv.s = 0.0f;
        return hsv;
    }

    // 计算饱和度 (Saturation)
    hsv.s = delta / max;

    // 计算色相 (Hue)
    if (r >= max) {
        hsv.h = (g - b) / delta;         // 黄色到品红之间
    } else if (g >= max) {
        hsv.h = 2.0f + (b - r) / delta;  // 青色到黄色之间
    } else {
        hsv.h = 4.0f + (r - g) / delta;  // 品红到青色之间
    }

    hsv.h *= 60.0f; // 转换为度数
    if (hsv.h < 0.0f) hsv.h += 360.0f; // 确保角度非负

    return hsv;
}

// HSV转RGB函数
RGBColor hsv_to_rgb(HSVColor hsv) {
    RGBColor rgb;
    float c = hsv.v * hsv.s; // 色度
    float x = c * (1.0f - fabsf(fmodf(hsv.h / 60.0f, 2.0f) - 1.0f));
    float m = hsv.v - c;

    float r, g, b;

    // 根据色相区间计算
    if (hsv.h < 60.0f) {
        r = c; g = x; b = 0;
    } else if (hsv.h < 120.0f) {
        r = x; g = c; b = 0;
    } else if (hsv.h < 180.0f) {
        r = 0; g = c; b = x;
    } else if (hsv.h < 240.0f) {
        r = 0; g = x; b = c;
    } else if (hsv.h < 300.0f) {
        r = x; g = 0; b = c;
    } else {
        r = c; g = 0; b = x;
    }

    // 添加明度偏移并转换为0-255
    rgb.r = (unsigned char)((r + m) * 255.0f);
    rgb.g = (unsigned char)((g + m) * 255.0f);
    rgb.b = (unsigned char)((b + m) * 255.0f);

    return rgb;
}

uint32_t rgb_to_int(RGBColor rgb)
{
	uint32_t color = 0;
	color = (rgb.r << 16) | (rgb.g << 8) | (rgb.b);
	return color;
}
void PWM_WS2812B_Init()
{
	WS2812B_Buf_Clear();
}
void WS2812B_Buf_Clear()
{
	int i = 0,j = 0;
	int a = LED_NUM + RESET_NUM * 2;
	for (i = 0; i < a; i++)
	{
		for (j = 0; j < 24; j++)
		{
			WS2812B_BUFF[i][j] = 0;
		}
	}
}
void WS2812B_Reset(void)
{
	int i = 0, j = 0;
	for (j = 0; j < RESET_NUM; j++)
	{
		for (i = 0; i < 24; i++)
		{
			WS2812B_BUFF[j][i] = 0;
			WS2812B_BUFF[j+RESET_NUM+LED_NUM][i] = 0;
		}
	}
}
void PWM_WS2812B_Write_24Bits(uint16_t index,uint32_t RGB_Data)
{
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		WS2812B_BUFF[index+RESET_NUM][i] = (((RGB_Data << (8+i)) & 0x00800000))? (T1H):(T0H); 	//G
		WS2812B_BUFF[index+RESET_NUM][i+8] = (((RGB_Data << (i)) & 0x00800000))? (T1H):(T0H);		//R
		WS2812B_BUFF[index+RESET_NUM][i+16] = (((RGB_Data << (16+i)) & 0x00800000))? (T1H):(T0H);	//B
	}
}
void WS2812B_Set_Color(uint16_t head, uint16_t num ,uint32_t RGB_Data)
{
	uint16_t i = 0;
	for (i = 0; i < num; i++)
	{
		PWM_WS2812B_Write_24Bits(head+i ,RGB_Data);
	}
}
void PWM_WS2812B_Refresh()
{
	WS2812B_Reset();
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)WS2812B_BUFF, (LED_NUM+RESET_NUM*2)*24);
}
void PWM_WS2812B_Red(uint16_t num)
{

}
void PWM_WS2812B_Green(uint16_t num)
{

}
void PWM_WS2812B_Blue(uint16_t num)
{

}
void PWM_WS2812B_Gradual(HSVColor* HSV)
{
	  Color_Gradual(HSV,0.3);
	  WS2812B_Buf_Clear();
	  WS2812B_Set_Color(0,LED_NUM,rgb_to_int(hsv_to_rgb(*HSV)));
	  PWM_WS2812B_Refresh();
//	  RGB_Show_64();
	  HAL_Delay(20);
}
void PWM_WS2812B_Rainbow(HSVColor* HSV)
{
	uint16_t i = 0,j = 0;
	for (i = LED_NUM; i > 0; i--)
	{
	  for (j = 0; j < 24; j++)
	  	{
	  		WS2812B_BUFF[i+RESET_NUM][j] = WS2812B_BUFF[i-1+RESET_NUM][j];
	  	}
	}

	  Color_Gradual(HSV,7);
	  WS2812B_Set_Color(0,1,rgb_to_int(hsv_to_rgb(*HSV)));
	  PWM_WS2812B_Refresh();
//	  RGB_Show_64();
	  HAL_Delay(40);
}



void Color_Gradual(HSVColor* Color,float step)
{
	if(Color->h < 360)
	{
		Color->h += step;
	}
	else
	{
		Color->h = fmod(Color->h, 360);
	}

}





