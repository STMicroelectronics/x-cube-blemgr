/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_blemgr.h
  * @author  System Research & Applications Team - Catania Lab.
  * @brief   Header file for app_blemgr.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_BLEMGR_H
#define APP_BLEMGR_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_exti.h"
#include "stm32l4xx_nucleo.h"

#include "SensorDataTransmit_config.h"

/* Exported macro ------------------------------------------------------------*/
#define MCR_BLUEMS_F2I_1D(in, out_int, out_dec) {out_int = (int32_t)in; out_dec= (int32_t)((in-out_int)*10);};
#define MCR_BLUEMS_F2I_2D(in, out_int, out_dec) {out_int = (int32_t)in; out_dec= (int32_t)((in-out_int)*100);};

/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported Variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported Functions --------------------------------------------------------*/
void MX_BLEMGR_Init(void);
void MX_BLEMGR_Process(void);

extern void SetRandomEnvironmentalValues(int32_t *PressToSend,uint16_t *HumToSend,int16_t *TempToSend);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* APP_BLEMGR_H */
