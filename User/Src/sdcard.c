#include "sdcard.h"
#include "sdio.h"


void SD_WriteBlocks_DMA(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
	HAL_Delay(4);
	while(HAL_SD_CARD_TRANSFER != HAL_SD_GetCardState(hsd));
	SD_DMA_WriteConfig(hsd, hdma);
	if(HAL_SD_WriteBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks) != HAL_OK)
	{
	  	Error_Handler();
	}
}

void SD_ReadBlocks_DMA(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks)
{
	HAL_Delay(4);
	while(HAL_SD_CARD_TRANSFER != HAL_SD_GetCardState(hsd));
	SD_DMA_ReadConfig(hsd, hdma);
	if(HAL_SD_ReadBlocks_DMA(hsd, pData, BlockAdd, NumberOfBlocks) != HAL_OK)
	{
		Error_Handler();
	}
}

void SD_DMA_WriteConfig(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma)
{
	hdma->Init.Direction = DMA_MEMORY_TO_PERIPH;
    HAL_DMA_DeInit(hdma);
    HAL_DMA_Init(hdma);
    __HAL_LINKDMA(hsd, hdmatx, *hdma);
}


void SD_DMA_ReadConfig(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma)
{
	hdma->Init.Direction = DMA_PERIPH_TO_MEMORY;
    HAL_DMA_DeInit(hdma);
    HAL_DMA_Init(hdma);
    __HAL_LINKDMA(hsd, hdmarx, *hdma);
}

