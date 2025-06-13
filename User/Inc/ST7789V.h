#ifndef __ST77789V_H__
#define __ST77789V_H__

#include "main.h"
#include "Font.h"

#define      ST7789V_ADDRESS_CMD             ((uint32_t)0X6C000000)              //屏幕命令指令地址
#define      ST7789V_ADDRESS_DAT             ((uint32_t)0X6D000000)              //屏幕数据指令地址

#define      ST7789V_LESS_PIXEL              240                                 //屏幕短边像素数量
#define      ST7789V_MORE_PIXEL              320                                 //屏幕长边像素数量

#define      ST7789V_DISWINDOW_STAR_X        0                                   //显示起始点像素X方向
#define      ST7789V_DISWINDOW_STAR_Y        0                                   //显示起始点像素Y方向

#define      LCDID_UNKNOWN                   0                                   //未知屏幕控制器ID
#define      LCDID_ILI9341                   0x9341
#define      LCDID_ST7789V                   0x8552                              //ST7789V屏幕ID

#define      CMD_SetCoordinateX		 	     0x2A                                //设置X方向窗体范围指令
#define      CMD_SetCoordinateY		 	     0x2B                                //设置Y方向窗体范围指令
#define      CMD_SetPixel		 		     0x2C

#define      BACKGROUND		                 GBLUE                              //默认窗体背景

#define      WHITE		 		             0xFFFF	                            //白色
#define      BLACK                           0x0000	                            //黑色
#define      GREY                            0xF7DE	                            //灰色
#define      BLUE                            0x001F	                            //蓝色
#define      BLUE2                           0x051F	                            //浅蓝色
#define      RED                             0xF800	                            //红色
#define      MAGENTA                         0xF81F	                            //洋红色
#define      GREEN                           0x07E0	                            //绿色
#define      CYAN                            0x7FFF	                            //蓝绿色，青色
#define      YELLOW                          0xFFE0	                            //黄色
#define      BRED                            0xF81F                             //紫色
#define      GRED                            0xFFE0                             //
#define      GBLUE                           0x07FF                             //天蓝色

extern uint8_t LCD_SCAN_MODE;
extern uint16_t LCD_X_LENGTH;
extern uint16_t LCD_Y_LENGTH;

void                        ST7789V_WriteCmd              (uint16_t cmd);
void                        ST7789V_WriteData             (uint16_t data);
uint16_t                    ST7789V_ReadData              (void);
static void                 ST7789V_delay_ms              (uint16_t ms);
void                        ST7789V_Init                  (void);
void                        ST7789V_BackLed_Control       (FunctionalState State);
void                        ST7789V_RST                   (void);
static void                 ST7789V_REG_Config            (void);
uint16_t                    ST7789V_ReadID                (void);
void                        ST7789V_GramScan              (uint8_t ucOption);
void                        ST7789V_OpenWindow            (uint16_t px, uint16_t py, uint16_t width, uint16_t height);
static __inline void        ST7789V_FillColor             (uint32_t ulAmout_Point,uint16_t pColor);
void                        ST7789V_ClearScreen           ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight);
void                        ST7789V_SetPointPixel         (uint16_t px, uint16_t py);
void                        ST7789v_DrawLine              (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void                        ST7789V_SetColor              (const uint16_t fontcolor, const uint16_t backcolor);
void                        ST7789V_GetColor              (uint16_t *fontcolor, uint16_t *backcolor);
void                        ST7789V_SetFontColor          (const uint16_t fontcolor);
void                        ST7789V_SetBackColor          (const uint16_t backcolor);
void                        ST7789V_SetFont               (sFONT *font);
sFONT                       *ST7789V_GetFont              (void);
void                        ST7789V_DispChar_EN           (const uint16_t usX, const uint16_t usY, const char chChar);
void                        ST7789V_DispString_EN         (uint16_t line,  char *pStr );
void                        ST7789V_ClearLine             (const uint16_t Line);




#endif

