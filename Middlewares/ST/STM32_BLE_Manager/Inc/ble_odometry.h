/**
  ******************************************************************************
  * @file    ble_odometry.h
  * @author  System Research & Applications Team - Noida/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Odometry services APIs.
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
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BLE_ODOMETRY_H_
#define _BLE_ODOMETRY_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ble_manager.h"

/* Exported Defines ----------------------------------------------------------*/

#ifndef DEFAULT_MAX_NOTIFICATION_CHAR_LEN
#define DEFAULT_MAX_NOTIFICATION_CHAR_LEN  20
#endif /* DEFAULT_MAX_PNPL_NOTIFICATION_CHAR_LEN */

/* Update frequency Command Codes */
#define ONE_HZ                      0x1
#define TWO_HZ                      0x2
#define THREE_HZ                    0x3

/* Command Codes for Control parameter*/
#define EN                      0x01
#define DIS                     0x00

/* Error Codes */
#define ERROR_GENERAL               0xF0
#define ERROR_CMD_NOT_SUPPORTED     0xF1
#define ERROR_CMD_NOT_EXPECTED      0xF2
#define ERROR_CMD_NOT_ALLOWED       0xF3
#define ERROR_PARAMS_NOT_CORRECT    0xF4
#define ERROR_PARAMS_OUT_OF_RANGE   0xF5
#define ERROR_INTERNAL              0xF6
#define ERROR_SUBSYSTEM             0xF7
#define ERROR_SUBSYSTEM_COMM_FAILED 0xF8
#define ERROR_AUTH_REQUIRED         0xF9

/* Exported typedef --------------------------------------------------------- */

/* Exported Variables ------------------------------------------------------- */

/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Init Odometry service
  * @retval ble_char_object_t* ble_char_pointer: Data structure pointer for Odometry service
  */
extern ble_char_object_t *ble_init_odometry_service(void);

/**
  * @brief  Odometry Set Max Char Length
  * @param  uint16_t max_char_length
  */
extern void ble_odometry_set_max_char_length(uint16_t max_char_length);

/**
  * @brief  Odometry Get Max Char Length
  * @retval uint16_t max_char_length
  */
extern uint16_t ble_odometry_get_max_char_length(void);

/**
  * @brief  Update Odometry characteristic value
  * @param  x_axis
  * @param  y_axis
  * @param  theta
  * @param  heading
  * @retval Status
  */
extern ble_status_t ble_odometry_update(float x_axis, float y_axis, float theta, float heading);

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
extern void notify_event_odometry(ble_notify_event_t Event);

/******************************************************************
  * Callback function prototype to manage the write request events *
  *****************************************************************/
extern void write_request_odometry_function(uint8_t *received_msg, uint32_t msg_length);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_ROBOT_MOVEMENT_H_ */

