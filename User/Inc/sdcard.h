#ifndef __CD_CARD_H_
#define __CD_CARD_H_

#include "main.h"

void SD_WriteBlocks_DMA(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks);
void SD_ReadBlocks_DMA(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma, uint8_t *pData, uint32_t BlockAdd, uint32_t NumberOfBlocks);
void SD_DMA_WriteConfig(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma);
void SD_DMA_ReadConfig(SD_HandleTypeDef *hsd, DMA_HandleTypeDef *hdma);
#endif
