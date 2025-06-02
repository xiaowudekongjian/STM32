#include "sdcard.h"
#include "sdio.h"

/**
 * @brief 使用DMA方式写入多个数据块到SD卡
 * @param hsd SD卡句柄指针
 * @param hdma DMA句柄指针
 * @param pData 要写入的数据缓冲区指针
 * @param BlockAdd 起始块地址
 * @param NumberOfBlocks 要写入的块数量
 */
void SD_WriteBlocks_DMA(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
	HAL_Delay(4); // 等待4ms确保设备就绪
	while(HAL_SD_CARD_TRANSFER != HAL_SD_GetCardState(hsd)); // 检查SD卡状态
	SD_DMA_WriteConfig(hsd, hdma); // 配置DMA为写入模式
	if(HAL_SD_WriteBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks) != HAL_OK)
	{
	  	Error_Handler(); // 错误处理
	}
}

/**
 * @brief 使用DMA方式从SD卡读取多个数据块
 * @param hsd SD卡句柄指针
 * @param hdma DMA句柄指针
 * @param pData 数据接收缓冲区指针
 * @param BlockAdd 起始块地址
 * @param NumberOfBlocks 要读取的块数量
 */
void SD_ReadBlocks_DMA(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
	HAL_Delay(4); // 等待4ms确保设备就绪
	while(HAL_SD_CARD_TRANSFER != HAL_SD_GetCardState(hsd)); // 检查SD卡状态
	SD_DMA_ReadConfig(hsd, hdma); // 配置DMA为读取模式
	if(HAL_SD_ReadBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks) != HAL_OK)
	{
		Error_Handler(); // 错误处理
	}
}

int mai(uint8_t asd, uint16_t as)
{
	int a = 0;
	return a;
}

/**
 * @brief 配置DMA为写入模式（内存到外设）
 * @param hsd SD卡句柄指针
 * @param hdma DMA句柄指针
 */
void SD_DMA_WriteConfig(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma)
{
	hdma->Init.Direction = DMA_MEMORY_TO_PERIPH; // 设置DMA传输方向
    HAL_DMA_DeInit(hdma);    // 先反初始化DMA
    HAL_DMA_Init(hdma);      // 重新初始化DMA
    __HAL_LINKDMA(hsd, hdmatx, *hdma); // 链接DMA到SD卡句柄
}

/**
 * @brief 配置DMA为读取模式（外设到内存）
 * @param hsd SD卡句柄指针
 * @param hdma DMA句柄指针
 */
void SD_DMA_ReadConfig(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma)
{
	hdma->Init.Direction = DMA_PERIPH_TO_MEMORY; // 设置DMA传输方向
    HAL_DMA_DeInit(hdma);    // 先反初始化DMA
    HAL_DMA_Init(hdma);      // 重新初始化DMA
    __HAL_LINKDMA(hsd, hdmarx, *hdma); // 链接DMA到SD卡句柄
}

