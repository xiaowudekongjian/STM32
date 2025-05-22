#ifndef _WS2812B_H_
#define _WS2812B_H_

#include "main.h"
#include "tim.h"
#include "dma.h"

#define WS2812B_PIN    GPIO_Pin_1
#define WS2812B_PORT   GPIOA
#define WS2812B_HIGH   GPIO_SetBits(WS2812B_PORT,WS2812B_PIN)
#define WS2812B_LOW	   GPIO_ResetBits(WS2812B_PORT,WS2812B_PIN)


// RGB 颜色结构体 (0-255)
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBColor;

// HSV 颜色结构体
typedef struct {
    float h; // 色相 (0-360 度)
    float s; // 饱和度 (0.0-1.0)
    float v; // 明度 (0.0-1.0)
} HSVColor;

/*	根据DataSheet定义0/1编码对应的高电平比较值，因为高电平在前，定义高电平的即可
**	高低电平的比例约为2:1
*/
#define WS2812B_ARR 90		//TIM2的自动重装载值
#define T0H 30						//0编码高电平时间占1/3
#define T1H 60						//1编码高电平时间占2/3

/* 灯珠亮的个数 */
#define LED_NUM  60
#define RESET_NUM 1
#define DATA_SIZE  24 	    //WS2812B一个编码的bit数，3*8


void PWM_WS2812B_Init();
void WS2812B_Reset(void);
void WS2812B_Buf_Clear();
void PWM_WS2812B_Write_24Bits(uint16_t index,uint32_t RGB_Data);
void WS2812B_Set_Color(uint16_t head, uint16_t num ,uint32_t RGB_Data);
void PWM_WS2812B_Refresh();
void PWM_WS2812B_Red(uint16_t num);
void PWM_WS2812B_Green(uint16_t num);
void PWM_WS2812B_Blue(uint16_t num);
void PWM_WS2812B_Gradual(HSVColor* HSV);
void PWM_WS2812B_Rainbow(HSVColor* HSV);
void RGB_Show_64(void);
HSVColor rgb_to_hsv(RGBColor rgb);
RGBColor hsv_to_rgb(HSVColor hsv);
void Color_Gradual(HSVColor* Color, float step);
uint32_t rgb_to_int(RGBColor rgb);

#endif
