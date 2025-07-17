/**
  ******************************************************************************
  * @file    stm32wb_conf.h
  * @author  SRA Application Team
  * @brief   BLE configuration file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WB_CONF_H
#define STM32WB_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32u5xx_hal.h"
#include <string.h>

/*---------- Print messages from BLE3 files at user level -----------*/
#define BLE3_DEBUG      0
/*---------- Print messages from BLE3 files at middleware level -----------*/
#define STM32WB05N_DEBUG      0
/*---------- Number of Bytes reserved for HCI Read Packet -----------*/
#define HCI_READ_PACKET_SIZE      200
/*---------- Number of Bytes reserved for HCI Max Payload -----------*/
#define HCI_MAX_PAYLOAD_SIZE      200
/*---------- Scan Interval: time interval from when the Controller started its last scan until it begins the subsequent scan (for a number N, Time = N x 0.625 msec) -----------*/
#define SCAN_P      16384
/*---------- Scan Window: amount of time for the duration of the LE scan (for a number N, Time = N x 0.625 msec) -----------*/
#define SCAN_L      16384
/*---------- Supervision Timeout for the LE Link (for a number N, Time = N x 10 msec) -----------*/
#define SUPERV_TIMEOUT      60
/*---------- Minimum Connection Period (for a number N, Time = N x 1.25 msec) -----------*/
#define CONN_P1      40
/*---------- Maximum Connection Period (for a number N, Time = N x 1.25 msec) -----------*/
#define CONN_P2      40
/*---------- Minimum Connection Length (for a number N, Time = N x 0.625 msec) -----------*/
#define CONN_L1      2000
/*---------- Maximum Connection Length (for a number N, Time = N x 0.625 msec) -----------*/
#define CONN_L2      2000
/*---------- Advertising Type -----------*/
#define ADV_DATA_TYPE      HCI_ADV_EVENT_PROP_CONNECTABLE | HCI_ADV_EVENT_PROP_SCANNABLE | HCI_ADV_EVENT_PROP_LEGACY
/*---------- Minimum Advertising Interval (for a number N, Time = N x 0.625 msec) -----------*/
#define ADV_INTERV_MIN      1600
/*---------- Maximum Advertising Interval (for a number N, Time = N x 0.625 msec) -----------*/
#define ADV_INTERV_MAX      1920
/*---------- Minimum Connection Event Interval (for a number N, Time = N x 1.25 msec) -----------*/
#define L2CAP_INTERV_MIN      9
/*---------- Maximum Connection Event Interval (for a number N, Time = N x 1.25 msec) -----------*/
#define L2CAP_INTERV_MAX      20
/*---------- Timeout Multiplier (for a number N, Time = N x 10 msec) -----------*/
#define L2CAP_TIMEOUT_MULTIPLIER      600
/*---------- HCI Default Timeout -----------*/
#define HCI_DEFAULT_TIMEOUT_MS        1000

#define STM32WB_memcpy                memcpy
#define STM32WB_memset                memset
#define STM32WB_memcmp                memcmp

#if (BLE3_DEBUG == 1)
  #include <stdio.h>
  #define PRINT_DBG(...)              printf(__VA_ARGS__)
#else
  #define PRINT_DBG(...)
#endif

#if PRINT_CSV_FORMAT
  #include <stdio.h>
  #define PRINT_CSV(...)              printf(__VA_ARGS__)
  void print_csv_time(void);
#else
  #define PRINT_CSV(...)
#endif

#if STM32WB05N_DEBUG
  /**
   * User can change here printf with a custom implementation.
   * For example:
   * #define STM32WB_PRINTF(...)   STBOX1_PRINTF(__VA_ARGS__)
   */
  #include <stdio.h>
  #define STM32WB_PRINTF(...)         printf(__VA_ARGS__)
#else
  #define STM32WB_PRINTF(...)
#endif

#ifdef __cplusplus
}
#endif
#endif /* STM32WB_CONF_H */
