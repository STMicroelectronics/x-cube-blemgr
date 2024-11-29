/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    SensorDataTransmit_config.h
  * @author  System Research & Applications Team - Catania Lab.
  * @version 4.0.0
  * @date    11-October-2024
  * @brief   X-CUBE-BLEMGR configuration
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __SENSOR_DT_CONFIG_H
#define __SENSOR_DT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported define ------------------------------------------------------------*/
/* Define The transmission interval in Multiple of 10ms for quaternions*/
#define QUAT_UPDATE_MUL_10MS 3

/* Define How Many quaternions you want to transmit (from 1 to 3) */
#define SEND_N_QUATERNIONS 1

/* Define The transmission interval in Multiple of 100ms for CO concentration Values */

/* IMPORTANT
The Sensors fusion runs at 100Hz so like MAXIMUM it possible to send:
1 quaternion every 10ms
2 quaternions every 20ms
3 quaternions every 30ms

if QUAT_UPDATE_MUL_10MS!=3, then SEND_N_QUATERNIONS must be ==1
*/

/*************** Debug Defines ******************/
#define SENSOR_DT_ENABLE_PRINTF

/* For enabling connection and notification subscriptions debug */
#define SENSOR_DT_DEBUG_CONNECTION

/* For enabling transmission for notified services (except for quaternions) */
#define SENSOR_DT_NOTIFY_TRAMISSION

/*************** Don't Change the following defines *************/

/* Package Version only numbers 0->9 */
#define FW_VERSION_MAJOR '4'
#define FW_VERSION_MINOR '0'
#define FW_VERSION_PATCH '0'

/* Package Name */
#define FW_PACKAGENAME "X-CUBE-BLEMGR"

/* STM32 board type*/
#define STM32_BOARD "STM32L476RGTX-NUCLEO"

#ifdef SENSOR_DT_ENABLE_PRINTF
#define SENSOR_DT_PRINTF(...) printf(__VA_ARGS__)
#else /* SENSOR_DT_ENABLE_PRINTF */
#define SENSOR_DT_PRINTF(...)
#endif /* SENSOR_DT_ENABLE_PRINTF */

/* STM32 MCU_ID */
#define STM32_MCU_ID ((uint32_t *)0xE0042000)

/* Control Section */

#if ((SEND_N_QUATERNIONS<1) || (SEND_N_QUATERNIONS>3))
#error "SEND_N_QUATERNIONS could be only 1,2 or 3"
#endif /* ((SEND_N_QUATERNIONS<1) || (SEND_N_QUATERNIONS>3)) */

#if ((QUAT_UPDATE_MUL_10MS!=3) && (SEND_N_QUATERNIONS!=1))
#error "If QUAT_UPDATE_MUL_10MS!=3 then SEND_N_QUATERNIONS must be = 1"
#endif /* ((QUAT_UPDATE_MUL_10MS!=3) && (SEND_N_QUATERNIONS!=1)) */

#ifdef __cplusplus
}
#endif

#endif /* __SENSOR_DT_CONFIG_H */

