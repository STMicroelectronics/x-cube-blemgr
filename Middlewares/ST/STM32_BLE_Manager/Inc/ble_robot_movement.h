/**
  ******************************************************************************
  * @file    ble_robot_movement.h
  * @author  System Research & Applications Team - Noida/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Robot Movement services APIs.
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
#ifndef _BLE_ROBOT_MOVEMENT_H_
#define _BLE_ROBOT_MOVEMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ble_manager.h"

/* Exported Defines ----------------------------------------------------------*/

#ifndef DEFAULT_MAX_NOTIFICATION_CHAR_LEN
#define DEFAULT_MAX_NOTIFICATION_CHAR_LEN  20
#endif /* DEFAULT_MAX_PNPL_NOTIFICATION_CHAR_LEN */

/* Command Codes */
#define CMD_GET_ROBOT_TOPOLOGY      0x10
#define CMD_SET_NAVIGATION_MODE     0x21
#define CMD_MOVE_COMMAND_SIMPLE_MOV 0x25
#define CMD_MOVE_COMMAND_ARTICULATE 0x26
#define CMD_MOVE_COMMAND_PWM_SPEED  0x24

/* Command Codes for armed status*/
#define CMD_ROBOT_ARMED             0x01
#define CMD_ROBOT_DISARMED          0x00

/* Action Codes */
#define ACTION_WRITE                0x10
#define ACTION_READ                 0x20
#define ACTION_WRITE_ACK            0x30
#define ACTION_READ_PERIODIC        0x60
#define ACTION_ACK_STATUS           0x80

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
  * @brief  Init Robot Movement service
  * @retval ble_char_object_t* ble_char_pointer: Data structure pointer for Robot Movement service
  */
extern ble_char_object_t *ble_init_robot_movement_service(void);

/**
  * @brief  RobotMovement Set Max Char Length
  * @param  uint16_t max_char_length
  */
extern void ble_robot_movement_set_max_char_length(uint16_t max_char_length);

/**
  * @brief  RobotMovement Get Max Char Length
  * @retval uint16_t max_char_length
  */
extern uint16_t ble_robot_movement_get_max_char_length(void);

/**
  * @brief  Update Robot Movement characteristic value
  * @param  robot_movement_status: Robot Movement packet
  * @retval Status
  */
extern ble_status_t ble_robot_movement_update(uint8_t robot_movement_status);

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
extern void notify_event_robot_movement(ble_notify_event_t event);

/******************************************************************
  * Callback function prototype to manage the write request events *
  *****************************************************************/
extern void write_request_robot_movement_function(uint8_t *received_msg, uint32_t msg_length);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_ROBOT_MOVEMENT_H_ */

