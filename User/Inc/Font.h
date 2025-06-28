#ifndef __FONT_H__
#define __FONT_H__

#include "main.h"


/**
 * CODE_FORMAT 为1表示UTF-8,0表示GBK2312
 */
#define CODE_FORMAT 1


#define FONT_CH_HEIGHT 16
#define FONT_CH_WIDTH 16


#define LINE(x)                ((x)*((sFONT*)ST7789V_GetFont())->height)
#define LINEY(x)               ((x)*FONT_CH_WIDTH)


typedef struct _tfont {
    const uint8_t *bitmap;
    uint8_t width;
    uint8_t height;
}sFONT;

//0表示使用SD卡字模，非零表示FLASH字模,由于SD卡字模有文件系统，速度慢很多。

#define GBKCODE_FLASH 						0

#if GBKCODE_FLASH
/*使用FLASH字模*/
/*中文字库存储在FLASH的起始地址*/
/*FLASH*/
#define GBKCODE_START_ADDRESS   512*4096


/*获取字库的函数*/
//定义获取中文字符字模数组的函数名，ucBuffer为存放字模数组名，usChar为中文字符（国标码）
#define      GetGBKCode( ucBuffer, usChar )  GetGBKCode_from_EXFlash( ucBuffer, usChar )
int GetGBKCode_from_EXFlash( uint8_t * pBuffer, uint16_t c);

#else
/*使用SD字模*/


/*SD卡字模路径*/
#define GBKCODE_FILE_NAME			"0:/srcdata/GB2312_H1616.FON"


/*获取字库的函数*/
//定义获取中文字符字模数组的函数名，ucBuffer为存放字模数组名，usChar为中文字符（国标码）

#define GetGBKCode( ucBuffer, usChar )  GetGBKCode_from_sd( ucBuffer, usChar )
int GetGBKCode_from_sd ( uint8_t * pBuffer, uint16_t c);

#endif

extern sFONT Font8x16;
extern sFONT Font16x24;
extern sFONT Font24x32;

extern const uint8_t ASCII8x16_Table[];
extern const uint8_t ASCII16x24_Table[];
extern const uint8_t ASCII24x32_Table[];
#endif

