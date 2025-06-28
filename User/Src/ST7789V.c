#include "ST7789V.h"
#include "Unicode_gbk.h"


uint16_t lcd_id = LCDID_UNKNOWN;                                //屏幕ID
uint8_t LCD_SCAN_MODE = 6;                                      //屏幕刷新模式
uint16_t LCD_X_LENGTH = 0;                                      //屏幕X轴方向长度
uint16_t LCD_Y_LENGTH = 0;                                      //屏幕Y轴方向长度
static uint16_t CurrentTextColor   = BLACK;                     //文字颜色
static uint16_t CurrentBackColor   = BACKGROUND;                //背景颜色
static sFONT *CurrentFont = &Font8x16;
/**
 * 向屏幕写指令
 * @param cmd 指令
 */
void ST7789V_WriteCmd(const uint16_t cmd)
{
    *(__IO uint16_t*) (ST7789V_ADDRESS_CMD) = cmd;
}

/**
 * 向屏幕写数据
 * @param data 数据
 */
void ST7789V_WriteData(const uint16_t data)
{
    *(__IO uint16_t*) (ST7789V_ADDRESS_DAT) = data;
}

/**
 * 读取屏幕返回数据
 * @return 读取的数据
 */
uint16_t ST7789V_ReadData(void)
{
    return *(__IO uint16_t*) (ST7789V_ADDRESS_DAT);;
}

/**
 * 简单延时
 * @param ms 延时毫秒数
 */
static void ST7789V_delay_ms(uint16_t ms)
{
    for (; ms != 0; --ms);
}

/**
 * ST7789初始化操作
 */
void ST7789V_Init(void)
{
    ST7789V_BackLed_Control(ENABLE);
    ST7789V_RST();
    ST7789V_REG_Config();
    HAL_Delay(100);
}


/**
 * 背光控制
 * @param State 背光是否开启
 * ENABLE:开启背光
 * DISABLE:关闭背光
 */
void ST7789V_BackLed_Control(const FunctionalState State)
{
    switch(State)
    {
        case DISABLE:
            HAL_GPIO_WritePin(BackLed_GPIO_Port, BackLed_Pin, GPIO_PIN_SET);
            break;
        case ENABLE:
            HAL_GPIO_WritePin(BackLed_GPIO_Port, BackLed_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

/**
 * 屏幕重启
 */
void ST7789V_RST(void)
{
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(300);
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(300);
}

/**
 * 屏幕初始化指令
 */
static void ST7789V_REG_Config(void)
{

    lcd_id = ST7789V_ReadID();
    if(lcd_id == LCDID_ST7789V)
    {
        /*  Power control B (CFh)  */
        ST7789V_WriteCmd ( 0xCF  );
        ST7789V_WriteData ( 0x00  );
        ST7789V_WriteData ( 0xC1  );
        ST7789V_WriteData ( 0x30  );
    
    /*  Power on sequence control (EDh) */
    
        ST7789V_WriteCmd ( 0xED );
        ST7789V_WriteData ( 0x64 );
        ST7789V_WriteData ( 0x03 );
        ST7789V_WriteData ( 0x12 );
        ST7789V_WriteData ( 0x81 );
    
    /*  Driver timing control A (E8h) */
    
        ST7789V_WriteCmd ( 0xE8 );
        ST7789V_WriteData ( 0x85 );
        ST7789V_WriteData ( 0x10 );
        ST7789V_WriteData ( 0x78 );
    
    /*  Power control A (CBh) */
    
        ST7789V_WriteCmd ( 0xCB );
        ST7789V_WriteData ( 0x39 );
        ST7789V_WriteData ( 0x2C );
        ST7789V_WriteData ( 0x00 );
        ST7789V_WriteData ( 0x34 );
        ST7789V_WriteData ( 0x02 );

    /* Pump ratio control (F7h) */
    
        ST7789V_WriteCmd ( 0xF7 );
        ST7789V_WriteData ( 0x20 );

    /* Driver timing control B */
    
        ST7789V_WriteCmd ( 0xEA );
        ST7789V_WriteData ( 0x00 );
        ST7789V_WriteData ( 0x00 );
    
    
    /* Power Control 1 (C0h) */
    
        ST7789V_WriteCmd ( 0xC0 );   //Power control
        ST7789V_WriteData ( 0x21 );  //VRH[5:0]
    
    /* Power Control 2 (C1h) */
    
        ST7789V_WriteCmd ( 0xC1 );   //Power control
        ST7789V_WriteData ( 0x11 );  //SAP[2:0];BT[3:0]
    
    /* VCOM Control 1 (C5h) */
        ST7789V_WriteCmd ( 0xC5 );
        ST7789V_WriteData ( 0x2D );
        ST7789V_WriteData ( 0x33 );

    /*  VCOM Control 2 (C7h)  */
//	ST7789V_WriteCmd ( 0xC7 );
//	ST7789V_WriteData ( 0XC0 );
    
    /* memory access control set */
    
        ST7789V_WriteCmd ( 0x36 );   //Memory Access Control
        ST7789V_WriteData ( 0x00 );  /*ÊúÆÁ  ×óÉÏ½Çµ½ (Æðµã)µ½ÓÒÏÂ½Ç (ÖÕµã)É¨Ãè·½Ê½*/


        ST7789V_WriteCmd(0x3A);
        ST7789V_WriteData(0x55);
    
      /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    
        ST7789V_WriteCmd ( 0xB1 );
        ST7789V_WriteData ( 0x00 );
        ST7789V_WriteData ( 0x17 );
    
    /*  Display Function Control (B6h) */
    
        ST7789V_WriteCmd ( 0xB6 );
        ST7789V_WriteData ( 0x0A );
        ST7789V_WriteData ( 0xA2 );

        ST7789V_WriteCmd(0xF6);
        ST7789V_WriteData(0x01);
        ST7789V_WriteData(0x30);
    
    /* Enable 3G (F2h) */
        ST7789V_WriteCmd ( 0xF2 );
        ST7789V_WriteData ( 0x00 );
    
    /* Gamma Set (26h) */
        ST7789V_WriteCmd ( 0x26 );
        ST7789V_WriteData ( 0x01 );
    
    
    /* Positive Gamma Correction */
        ST7789V_WriteCmd(0xe0); //Positive gamma
        ST7789V_WriteData(0xd0);
        ST7789V_WriteData(0x00);
        ST7789V_WriteData(0x02);
        ST7789V_WriteData(0x07);
        ST7789V_WriteData(0x0b);
        ST7789V_WriteData(0x1a);
        ST7789V_WriteData(0x31);
        ST7789V_WriteData(0x54);
        ST7789V_WriteData(0x40);
        ST7789V_WriteData(0x29);
        ST7789V_WriteData(0x12);
        ST7789V_WriteData(0x12);
        ST7789V_WriteData(0x12);
        ST7789V_WriteData(0x17);

    /* Negative Gamma Correction (E1h) */
        ST7789V_WriteCmd(0xe1); //Negative gamma
        ST7789V_WriteData(0xd0);
        ST7789V_WriteData(0x00);
        ST7789V_WriteData(0x02);
        ST7789V_WriteData(0x07);
        ST7789V_WriteData(0x05);
        ST7789V_WriteData(0x25);
        ST7789V_WriteData(0x2d);
        ST7789V_WriteData(0x44);
        ST7789V_WriteData(0x45);
        ST7789V_WriteData(0x1c);
        ST7789V_WriteData(0x18);
        ST7789V_WriteData(0x16);
        ST7789V_WriteData(0x1c);
        ST7789V_WriteData(0x1d);
  
	
    //	/* column address control set */
    //	ST7789V_WriteCmd ( CMD_SetCoordinateX );
    //	ST7789V_WriteData ( 0x00 );
    //	ST7789V_WriteData ( 0x00 );
    //	ST7789V_WriteData ( 0x00 );
    //	ST7789V_WriteData ( 0xEF );
    //
    //	/* page address control set */
    //
    //	ST7789V_WriteCmd ( CMD_SetCoordinateY );
    //	ST7789V_WriteData ( 0x00 );
    //	ST7789V_WriteData ( 0x00 );
    //	ST7789V_WriteData ( 0x01 );
    //	ST7789V_WriteData ( 0x3F );


    /* Sleep Out (11h)  */
    ST7789V_WriteCmd ( 0x11 );	  //Exit Sleep
    ST7789V_delay_ms ( 0xAFFf<<2 );
    
    /* Display ON (29h) */
    ST7789V_WriteCmd ( 0x29 );   //Display on
    
    ST7789V_WriteCmd(0x2c);
  }

}

/**
 * 获取屏幕ID
 * @return 屏幕ID
 */
uint16_t ST7789V_ReadID(void)
{
    uint16_t id = 0;

    ST7789V_WriteCmd(0X04);
    ST7789V_ReadData();
    ST7789V_ReadData();
    id = ST7789V_ReadData();
    id = id << 8;
    id |= ST7789V_ReadData();
    if (id == LCDID_ST7789V)
    {
        return id;
    }
    else
    {
        return LCDID_UNKNOWN;
    }
}

/**
 * 屏幕刷新方式设定
 * @param ucOption 屏幕刷新方向模式
 */
void ST7789V_GramScan(uint8_t ucOption)
{
    if (ucOption > 7)
        return;
    LCD_SCAN_MODE = ucOption;
    if (LCD_SCAN_MODE % 2 == 0)
    {
        LCD_X_LENGTH = ST7789V_LESS_PIXEL;
        LCD_Y_LENGTH = ST7789V_MORE_PIXEL;
    }
    else
    {
        LCD_X_LENGTH = ST7789V_MORE_PIXEL;
        LCD_Y_LENGTH = ST7789V_LESS_PIXEL;
    }
    ST7789V_WriteCmd(0X36);
    if (lcd_id == LCDID_ST7789V)
    {
        ST7789V_WriteCmd(ucOption << 5);
    }
    ST7789V_WriteCmd(CMD_SetCoordinateX);
    ST7789V_WriteData(0X00);
    ST7789V_WriteData(0X00);
    ST7789V_WriteData(((LCD_X_LENGTH -1) >> 8) & 0XFF);
    ST7789V_WriteData((LCD_X_LENGTH - 1) & 0XFF);

    ST7789V_WriteCmd(CMD_SetCoordinateY);
    ST7789V_WriteData(0X00);
    ST7789V_WriteData(0X00);
    ST7789V_WriteData(((LCD_Y_LENGTH -1) >> 8) & 0XFF);
    ST7789V_WriteData((LCD_Y_LENGTH - 1) & 0XFF);
}

/**
 * 开启一个新窗体
 * @param px X方向起始点像素
 * @param py Y方向起始点像素
 * @param width 窗体宽度
 * @param height 窗体高度
 */
void ST7789V_OpenWindow(uint16_t px, uint16_t py, uint16_t width, uint16_t height)
{
    ST7789V_WriteCmd(CMD_SetCoordinateX);
    ST7789V_WriteData(px >> 8);
    ST7789V_WriteData(px & 0xff);
    ST7789V_WriteData((px + width - 1) >> 8);
    ST7789V_WriteData((px + width - 1) & 0xff);

    ST7789V_WriteCmd(CMD_SetCoordinateY);
    ST7789V_WriteData(py >> 8);
    ST7789V_WriteData(py & 0xff);
    ST7789V_WriteData((py + height - 1) >> 8);
    ST7789V_WriteData((py + height - 1) & 0xff);
}

/* 填充颜色
 * @param ulAmout_Point 填充点数
 * @param pColor 填充颜色
 */
static __inline void ST7789V_FillColor(uint32_t ulAmout_Point,uint16_t pColor)
{
    uint32_t i = 0;
    ST7789V_WriteCmd(CMD_SetPixel);
    for(i = 0 ; i < ulAmout_Point ; i++)
    {
        ST7789V_WriteData(pColor);
    }
}

/**
 * 画点
 * @param px x轴像素点坐标
 * @param py y轴像素点坐标
 */
void ST7789V_SetPointPixel(uint16_t px, uint16_t py)
{
    if (px <= LCD_X_LENGTH && py <= LCD_Y_LENGTH)
    {
        ST7789V_OpenWindow(px,py,1,1);
        ST7789V_FillColor(1,CurrentTextColor);
    }
}

void ST7789v_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint16_t us;
    uint16_t usX_Current,usY_Current;

    int32_t lError_x = 0, lError_y = 0,lDelta_x, lDelta_y,lDistance;
    int32_t lIncrease_x, lIncrease_y;

    lDelta_x = x2 - x1;
    lDelta_y = y2 - y1;

    usX_Current = x1;
    usY_Current = y1;

    if (lDelta_x > 0)
        lIncrease_x = 1;
    else if (lDelta_x == 0)
        lIncrease_x = 0;
    else
    {
        lIncrease_x = -1;
        lDelta_x = -lDelta_x;
    }

    if (lDelta_y > 0)
        lIncrease_y = 1;
    else if (lDelta_y == 0)
        lIncrease_y = 0;
    else
    {
        lIncrease_y = -1;
        lDelta_y = -lDelta_y;
    }

    if (lDelta_x > lDelta_y)
        lDistance = lDelta_x;
    else
        lDistance = lDelta_y;

    for (us = 0; us <= lDistance; us++)
    {
        ST7789V_SetPointPixel(usX_Current,usY_Current);

        lError_x += lDelta_x;
        lError_y += lDelta_y;

        if (lError_x > lDistance)
        {
            lError_x -= lDistance;
            usX_Current += lIncrease_x;
        }

        if (lError_y > lDistance)
        {
            lError_y -= lDistance;
            usY_Current += lIncrease_y;
        }
    }

}



void ST7789V_DrawRectangle(uint16_t usX_Start, uint16_t usY_Start, uint16_t usWidth, uint16_t usHeight, uint8_t ucFilled)
{
    if (ucFilled)
    {
        ST7789V_OpenWindow(usX_Start, usY_Start, usWidth, usHeight);
        ST7789V_FillColor(usWidth*usHeight, CurrentTextColor);
    }
    else
    {
        ST7789v_DrawLine(usX_Start, usY_Start, usX_Start + usWidth, usY_Start);
        ST7789v_DrawLine(usX_Start, usY_Start, usX_Start, usY_Start + usHeight);
        ST7789v_DrawLine(usX_Start + usWidth, usY_Start, usX_Start + usWidth, usY_Start + usHeight);
        ST7789v_DrawLine(usX_Start, usY_Start + usHeight, usX_Start + usWidth, usY_Start + usHeight);
    }

}

void ST7789V_DrawCircle(uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled)
{
    int16_t sCurrentX = 0, sCurrentY = (int16_t)usRadius;
    int16_t sError;
    sError = 3 - (usRadius << 1);
    while (sCurrentX <= sCurrentY)
    {
        int16_t sCountY;


        if ( ucFilled )
            for ( sCountY = sCurrentX; sCountY <= sCurrentY; sCountY ++ )
            {
                ST7789V_SetPointPixel ( usX_Center + sCurrentX, usY_Center + sCountY );           //1研究对象
                ST7789V_SetPointPixel ( usX_Center - sCurrentX, usY_Center + sCountY );           //2
                ST7789V_SetPointPixel ( usX_Center - sCountY,   usY_Center + sCurrentX );           //3
                ST7789V_SetPointPixel ( usX_Center - sCountY,   usY_Center - sCurrentX );           //4
                ST7789V_SetPointPixel ( usX_Center - sCurrentX, usY_Center - sCountY );           //5
                ST7789V_SetPointPixel ( usX_Center + sCurrentX, usY_Center - sCountY );           //6
                ST7789V_SetPointPixel ( usX_Center + sCountY,   usY_Center - sCurrentX );           //7
                ST7789V_SetPointPixel ( usX_Center + sCountY,   usY_Center + sCurrentX );           //0
            }

        else
        {
            ST7789V_SetPointPixel ( usX_Center + sCurrentX, usY_Center + sCurrentY );             //1
            ST7789V_SetPointPixel ( usX_Center - sCurrentX, usY_Center + sCurrentY );             //2
            ST7789V_SetPointPixel ( usX_Center - sCurrentY, usY_Center + sCurrentX );             //3
            ST7789V_SetPointPixel ( usX_Center - sCurrentY, usY_Center - sCurrentX );             //4
            ST7789V_SetPointPixel ( usX_Center - sCurrentX, usY_Center - sCurrentY );             //5
            ST7789V_SetPointPixel ( usX_Center + sCurrentX, usY_Center - sCurrentY );             //6
            ST7789V_SetPointPixel ( usX_Center + sCurrentY, usY_Center - sCurrentX );             //7
            ST7789V_SetPointPixel ( usX_Center + sCurrentY, usY_Center + sCurrentX );             //0
        }
        sCurrentX++;
        if ( sError < 0 )
        {
            sError += 4 * sCurrentX + 6;
        }
        else
        {
            sError += 10 + 4 * ( sCurrentX - sCurrentY );
            sCurrentY --;
        }

    }
}

/**
 * 区块颜色清除
 * @param usX X方向起始点像素
 * @param usY Y方向起始点像素
 * @param usWidth 窗体宽度
 * @param usHeight 窗体高度
 */
void ST7789V_ClearScreen( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight)
{
    ST7789V_OpenWindow(usX, usY, usWidth, usHeight);
    ST7789V_FillColor(usWidth*usHeight, CurrentBackColor);
}

/**
 * 设置颜色
 * @param fontcolor 前景颜色
 * @param backcolor 背景颜色
 */
void ST7789V_SetColor(const uint16_t fontcolor, const uint16_t backcolor)
{
    CurrentTextColor = fontcolor;
    CurrentBackColor = backcolor;
}

/**
 * 获取颜色
 * @param fontcolor 前景颜色
 * @param backcolor 背景颜色
 */
void ST7789V_GetColor(uint16_t *fontcolor, uint16_t *backcolor)
{
    *fontcolor = CurrentTextColor;
    *backcolor = CurrentBackColor;
}
/**
 * 设置前景颜色
 * @param fontcolor 前景颜色
 */
void ST7789V_SetFontColor(const uint16_t fontcolor)
{
    CurrentTextColor = fontcolor;
}
/**
 * 设置背景颜色
 * @param backcolor 背景颜色
 */
void ST7789V_SetBackColor(const uint16_t backcolor)
{
    CurrentBackColor = backcolor;
}

/**
 * 设置字体
 * @param font 字体指针
 */
void ST7789V_SetFont(sFONT *font)
{
    CurrentFont = font;
}

/**
 * 获取当前字体状态
 * @return 字体指针地址
 */
sFONT *ST7789V_GetFont(void)
{
    return CurrentFont;
}

/**
 * 显示单个英文字符
 * @param usX 行坐标
 * @param usY 列坐标
 * @param chChar 显示字符
 */
void ST7789V_DispChar_EN(const uint16_t usX, const uint16_t usY, const char chChar)
{
    const uint16_t ucRealativePosation = chChar -  ' ';
    uint8_t  byteCount, bitCount;
    const uint8_t fontLength = ((CurrentFont->height) * (CurrentFont->width)) / 8;
    uint8_t *pFontBuff = (uint8_t*)&(CurrentFont->bitmap[ucRealativePosation*fontLength]);
    ST7789V_OpenWindow(usX, usY, CurrentFont->width, CurrentFont->height);
    ST7789V_WriteCmd(CMD_SetPixel);
    for (byteCount = 0; byteCount < fontLength; byteCount++)
    {
        for (bitCount = 0; bitCount < 8; bitCount++)
        {
            if (pFontBuff[byteCount] & (0x80>>bitCount))
            {
                ST7789V_WriteData(CurrentTextColor);
            }
            else
            {
                ST7789V_WriteData(CurrentBackColor);
            }
        }
    }
}

void ST7789V_DispChar_ZH(uint16_t usX, uint16_t usY, uint16_t usChar)
{
    uint8_t rowCount,bitCount;
    uint8_t ucBuffer[FONT_CH_HEIGHT*FONT_CH_WIDTH/8];
    uint16_t usTemp;

    ST7789V_OpenWindow(usX,usY,FONT_CH_WIDTH,FONT_CH_HEIGHT);
    ST7789V_WriteCmd(CMD_SetPixel);
    GetGBKCode(ucBuffer,usChar);
    for ( rowCount = 0; rowCount < FONT_CH_HEIGHT; rowCount++ )
    {
        /* 取出两个字节的数据，在lcd上即是一个汉字的一行 */
        usTemp = ucBuffer [ rowCount * 2 ];
        usTemp = ( usTemp << 8 );
        usTemp |= ucBuffer [ rowCount * 2 + 1 ];

        for ( bitCount = 0; bitCount < FONT_CH_WIDTH; bitCount ++ )
        {
            if ( usTemp & ( 0x8000 >> bitCount ) )  //高位在前
                ST7789V_WriteData ( CurrentTextColor );
            else
                ST7789V_WriteData ( CurrentBackColor );
        }
    }
}



/**
 * 显示英文字符串
 * @param line 行号
 * @param pStr 字符串指针
 */
void ST7789V_DispString_EN(  uint16_t line,  char *pStr )
{
    uint16_t usX = 0;

    while ( * pStr != '\0' )
    {
        if ( ( usX - ST7789V_DISWINDOW_STAR_X + CurrentFont->width ) > LCD_X_LENGTH )
        {
            usX = ST7789V_DISWINDOW_STAR_X;
            line += CurrentFont->height;
        }

        if ( ( line - ST7789V_DISWINDOW_STAR_Y + CurrentFont->height ) > LCD_Y_LENGTH )
        {
            usX = ST7789V_DISWINDOW_STAR_X;
            line = ST7789V_DISWINDOW_STAR_Y;
        }
        if (*pStr >= ' ')
        {
            ST7789V_DispChar_EN ( usX, line, * pStr);
            usX += CurrentFont->width;
        }
        else if (*pStr == 0x0A)
        {
            usX = ST7789V_DISWINDOW_STAR_X;
            line += CurrentFont->height;
        }
        pStr ++;



    }

}


void ST7789V_DispString_CH (uint16_t usX , uint16_t usY, char * pStr )
{
    uint16_t usCh;
    uint32_t uc;
    uint16_t unicide;
    while( * pStr != '\0' )
    {
        if ( ( usX - ST7789V_DISWINDOW_STAR_X + FONT_CH_WIDTH ) > LCD_X_LENGTH )
        {
            usX = ST7789V_DISWINDOW_STAR_X;
            usY += FONT_CH_HEIGHT;
        }

        if ( ( usY - ST7789V_DISWINDOW_STAR_Y + FONT_CH_HEIGHT ) > LCD_Y_LENGTH )
        {
            usX = ST7789V_DISWINDOW_STAR_X;
            usY = ST7789V_DISWINDOW_STAR_Y;
        }
#ifdef CODE_FORMAT
        uc = (*(uint8_t *)pStr<<16) | (*(uint8_t *)(pStr+1)<<8)  |(*(uint8_t *)(pStr+2));
        unicide = (uc & 0x0F0000)>>4 | (uc & 0x003F00)>>2 |(uc & 0x00003F);
        usCh = UnicodeToGBK(unicide);
#else

         usCh = * ( uint16_t * ) pStr;
         usCh = ( usCh << 8 ) + ( usCh >> 8 );
#endif
        ST7789V_DispChar_ZH ( usX, usY, usCh );

        usX += FONT_CH_WIDTH;

        pStr += 3;           //一个汉字两个字节

    }

}

void ST7789V_ClearLine(const uint16_t Line)
{
    ST7789V_ClearScreen(0,Line, LCD_X_LENGTH, ST7789V_GetFont()->height);
}

// 将Unicode码点转换为GBK编码
uint16_t UnicodeToGBK(uint16_t unicode)
{
    uint16_t gbkcode = 0;
    uint16_t i = 0;


    for ( i = 0 ; i < MAX_UNI_INDEX ; i++ )
    {
        if (GB_TO_UNI[i][0] == unicode)
        {
            gbkcode = GB_TO_UNI[i][1];
            return  gbkcode;
        }
    }

    return  0XA0A1;
}

