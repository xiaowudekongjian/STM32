#include "WS2812B.h"
#include "stdlib.h"
uint32_t WS2812B_BUFF[LED_NUM+1][24];



void PWM_WS2812B_Init()
{
	WS2812B_Buf_Clear();
}
void WS2812B_Buf_Clear()
{
	int i = 0,j = 0;
	for (i = 0; i < LED_NUM+1; i++)
	{
		for (j = 0; j < 24; j++)
		{
			WS2812B_BUFF[i][j] = 0;
		}
	}
}
void WS2812B_Reset(void)
{
	int i = 0;
	for (i = 0; i < 24; i++)
	{
		WS2812B_BUFF[LED_NUM][i] = 0;
	}

}
void PWM_WS2812B_Write_24Bits(uint16_t index,uint32_t RGB_Data)
{
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		WS2812B_BUFF[index][i] = (((RGB_Data << (8+i)) & 0x00800000))? (T1H):(T0H); 	//G
		WS2812B_BUFF[index][i+8] = (((RGB_Data << (i)) & 0x00800000))? (T1H):(T0H);		//R
		WS2812B_BUFF[index][i+16] = (((RGB_Data << (16+i)) & 0x00800000))? (T1H):(T0H);	//B
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
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_2, (uint32_t*)WS2812B_BUFF, (LED_NUM+1)*24);
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

void RGB_Show_64(void)
{
	WS2812B_Buf_Clear();
	WS2812B_Set_Color(0,60,rand()%0x1000000);
//	WS2812B_Set_Color(0,60,0xffffff);
//	WS2812B_Set_Color(30,15,0x00ff00);
//	WS2812B_Set_Color(45,15,0x0000ff);

	PWM_WS2812B_Refresh();
}


