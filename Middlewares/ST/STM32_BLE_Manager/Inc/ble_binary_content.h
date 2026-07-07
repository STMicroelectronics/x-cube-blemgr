/**
  ******************************************************************************
  * @file    ble_binary_content.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   BLE_BinaryContent info services APIs.
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
#ifndef _BLE_BINARY_CONTENT_H_
#define _BLE_BINARY_CONTENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Exported Defines ----------------------------------------------------------*/
#ifndef DEFAULT_MAX_BINARY_CONTENT_CHAR_LEN
#define DEFAULT_MAX_BINARY_CONTENT_CHAR_LEN  20
#endif /* DEFAULT_MAX_BINARY_CONTENT_CHAR_LEN */

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Init BinaryContent info service
  * @retval *ble_char_pointer: Data structure pointer for BinaryContent info service
  */
extern ble_char_object_t *ble_init_binary_content_service(void);

/**
  * @brief  BinaryContent Send Buffer
  * @param  *buffer
  * @param  len
  * @retval status
  */
extern ble_status_t ble_binary_content_update(uint8_t *buffer, uint8_t len);

/**
  * @brief  BinaryContent Set Max Char Length
  * @param  max_char_length
  */
extern void ble_binary_content_set_max_char_length(uint16_t max_char_length);

/**
  * @brief  BinaryContent Get Max Char Length
  * @retval max_char_length
  */
extern uint16_t ble_binary_content_get_max_char_length(void);

/**
  * @brief  BinaryContent Reset Status
  */
extern void ble_binary_content_reset(void);

/**
  * @brief  This event is given when a write request is received by the server from the client.
  * @param  *ble_char_pointer
  * @param  handle Handle of the attribute
  * @param  offset
  * @param  data_length
  * @param  *att_data
  */
extern void write_request_binary_content(void *ble_char_pointer, uint16_t handle, uint16_t offset,
                                         uint8_t data_length,
                                         uint8_t *att_data);

/**
  * @brief  This function is called to parse a Binary Content packet.
  * @param  buffer_out: pointer to the output buffer.
  * @param  buffer_in: pointer to the input data.
  * @param  len: buffer in length
  * @retval Buffer out length.
  */
extern uint32_t ble_binary_content_parse(uint8_t **buffer_out, uint8_t *buffer_in, uint32_t len);

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
extern void notify_event_binary_content(ble_notify_event_t event);

/******************************************************************
  * Callback function prototype to manage the write request events *
  *****************************************************************/
extern void write_request_binary_content_function(uint8_t *received_msg, uint32_t msg_length);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_BINARY_CONTENT_H_ */

