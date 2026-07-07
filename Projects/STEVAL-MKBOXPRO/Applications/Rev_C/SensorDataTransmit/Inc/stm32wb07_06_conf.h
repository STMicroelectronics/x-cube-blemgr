/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32wb07_06_conf.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @brief   STM32WB07_06 configuration file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  ******************************************************************************
  */

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WB07_06_CONF_H
#define STM32WB07_06_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32u5xx_hal.h"
#include <string.h>

/*---------- Maximum Advertising Interval (for a number N, Time = N x 0.625 msec) -----------*/
#define ADV_INTERV_MAX      1920
/*---------- Number of Bytes reserved for HCI Max Payload -----------*/
#define HCI_MAX_PAYLOAD_SIZE      255
/*---------- Number of incoming packets added to the list of packets to read -----------*/
#define HCI_READ_PACKET_NUM_MAX      10
/*---------- Minimum Advertising Interval (for a number N, Time = N x 0.625 msec) -----------*/
#define ADV_INTERV_MIN      1600
/*---------- Print messages from BLueNRG-LP files at middleware level -----------*/
#define STM32WB07_06_DEBUG      0
/*---------- Number of Bytes reserved for HCI Read Packet -----------*/
#define HCI_READ_PACKET_SIZE      255
/*---------- HCI Default Timeout -----------*/
#define HCI_DEFAULT_TIMEOUT_MS        1000

#define STM32WB07_06_MEMCPY                memcpy
#define STM32WB07_06_MEMSET                memset
#define STM32WB07_06_MEMCMP                memcmp

#if STM32WB07_06_DEBUG
/**
  * User can change here printf with a custom implementation.
  * For example:
  * #define STM32WB07_06_PRINTF(...)   STBOX1_PRINTF(__VA_ARGS__)
  */
#include <stdio.h>
#define STM32WB07_06_PRINTF(...)         printf(__VA_ARGS__)
#else /* STM32WB07_06_DEBUG */
#define STM32WB07_06_PRINTF(...)
#endif /* STM32WB07_06_DEBUG */

#ifdef __cplusplus
}
#endif
#endif /* STM32WB07_06_CONF_H */
