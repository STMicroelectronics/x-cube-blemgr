/**
  ******************************************************************************
  * @file    ble_scene_description.h
  * @author  System Research & Applications Team - Noida/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Robot Scene Description service APIs.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 20245 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BLE_SCENE_DESCRIPTION_H_
#define _BLE_SCENE_DESCRIPTION_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ble_manager.h"

/* Exported Defines ----------------------------------------------------------*/
#ifndef DEFAULT_NOTIFICATION_CHAR_LEN
#define DEFAULT_NOTIFICATION_CHAR_LEN  220U
#define DEFAULT_SD_NOTIFY_CHAR_LEN  210U
#endif /* DEFAULT_NOTIFICATION_CHAR_LEN */

/* Scene description commands codes*/
/*CMD TYPE*/
#define SCENE_DESCRIPTION_CMD_GET                               (uint8_t)(0x10)
#define SCENE_DESCRIPTION_CMD_GET_CMD_SET                       (uint8_t)(0x20)
#define SCENE_DESCRIPTION_CMD_GET_CMD_UPDATE_DEVICE             (uint8_t)(0x21)
#define SCENE_DESCRIPTION_CMD_GET_CMD_COMMAND                   (uint8_t)(0x30)
#define SCENE_DESCRIPTION_CMD_GET_CMD_SYSTEM_CONFIG             (uint8_t)(0x40)
#define SCENE_DESCRIPTION_CMD_GET_CMD_SYSTEM_INFO               (uint8_t)(0x50)
#define SCENE_DESCRIPTION_CMD_GET_CMD_COMPUTE_STREAM_IDS        (uint8_t)(0x60)
#define SCENE_DESCRIPTION_CMD_GET_CMD_ERROR                     (uint8_t)(0x70)

/* Exported typedef --------------------------------------------------------- */

/* Exported Variables ------------------------------------------------------- */

/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Init Scene Description service
  * @retval ble_char_object_t* ble_char_pointer: Data structure pointer for Scene Description service
  */
extern ble_char_object_t *ble_init_scene_description_service(void);

/**
  * @brief  Update the Scene Description Characteristic with the provided buffer.
  * @param  buffer: Pointer to the data buffer containing the scene description.
  * @param  len: Length of the data buffer.
  * @retval Status of the characteristic update operation.
  */
extern ble_status_t ble_scene_description_update(uint8_t *buffer, uint32_t len);

/**
  * @brief  SceneDescription Set Max Char Length
  * @param  uint16_t max_char_length
  */
extern void ble_scene_description_set_max_char_length(uint16_t max_char_length);

/**
  * @brief  SceneDescription Get Max Char Length
  * @retval uint16_t max_char_length
  */
extern uint16_t ble_scene_description_get_max_char_length(void);

/**
  * @brief  SceneDescription Reset Status
  */
extern void ble_scene_description_reset(void);

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
extern void notify_event_scene_description(ble_notify_event_t event);

/******************************************************************
  * Callback function prototype to manage the write request events *
  *****************************************************************/
extern void write_request_scene_description_function(uint8_t *received_msg, uint32_t msg_length);

/******************************************************************
  * Callback function prototype to manage the read request events *
  *****************************************************************/
extern void read_request_scene_description_function(uint8_t *status);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_SCENE_DESCRIPTION_H_ */

