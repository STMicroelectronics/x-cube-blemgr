/**
  ******************************************************************************
  * @file    ble_scene_description.c
  * @author  System Research & Applications Team - Noida/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Add Scene Description services.
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "ble_manager.h"
#include "ble_manager_common.h"
#include "ble_scene_description.h"

/* Private define ------------------------------------------------------------*/
#define COPY_SCENE_DESCRIPTION_CHAR_UUID(uuid_struct) COPY_UUID_128(uuid_struct,0x00,0x00,0x00,0x29,0x00,0x02,0x11,\
                                                                    0xe1,0xac,0x36,0x00,0x02,0xa5,0xd5,0xc5,0x1b)

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
__weak void notify_event_scene_description(ble_notify_event_t event);

/******************************************************************
  * Callback function prototype to manage the write request events *
  *****************************************************************/
__weak void write_request_scene_description_function(uint8_t *received_msg, uint32_t msg_length);

/******************************************************************
  * Callback function prototype to manage the read request events *
  *****************************************************************/
__weak void read_request_scene_description_function(uint8_t *status);

/* Private variables ---------------------------------------------------------*/
/* Data structure pointer for Scene Description service */
static ble_char_object_t ble_char_scene_description;

/* Private functions ---------------------------------------------------------*/
static void attr_mod_request_scene_description(void *ble_char_pointer, uint16_t attr_handle, uint16_t offset,
                                               uint8_t data_length,
                                               uint8_t *att_data);

static void write_request_scene_description(void *ble_char_pointer, uint16_t handle, uint16_t offset,
                                            uint8_t data_length,
                                            uint8_t *att_data);

#if ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N))
static void read_request_scene_description(void *ble_char_pointer, uint16_t handle);
#else /* ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N)) */
static void read_request_scene_description(void *ble_char_pointer,
                                           uint16_t handle,
                                           uint16_t connection_handle,
                                           uint8_t operation_type,
                                           uint16_t attr_val_offset,
                                           uint8_t data_length,
                                           uint8_t data[]);
#endif /* ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N)) */

static uint16_t scene_description_content_max_char_length = DEFAULT_NOTIFICATION_CHAR_LEN;

/**
  * @brief  Init Scene Description service
  * @retval ble_char_object_t* ble_char_pointer:  Data structure pointer for Scene Description service
  */
ble_char_object_t *ble_init_scene_description_service(void)
{
  /* Data structure pointer for BLE service */
  ble_char_object_t *ble_char_pointer;

  /* Init data structure pointer for Robot Movement service */
  ble_char_pointer = &ble_char_scene_description;
  memset(ble_char_pointer, 0, sizeof(ble_char_object_t));
  ble_char_pointer->attr_mod_request_cb = attr_mod_request_scene_description;
  ble_char_pointer->write_request_cb = write_request_scene_description;
  ble_char_pointer->read_request_cb = read_request_scene_description;
  COPY_SCENE_DESCRIPTION_CHAR_UUID((ble_char_pointer->uuid));
  ble_char_pointer->char_uuid_type = UUID_TYPE_128;
  ble_char_pointer->char_value_length = scene_description_content_max_char_length;
  ble_char_pointer->char_properties = ((uint8_t)(CHAR_PROP_NOTIFY)) | ((uint8_t)(CHAR_PROP_WRITE_WITHOUT_RESP)) |
                                      ((uint8_t)(CHAR_PROP_WRITE)) | ((uint8_t)(CHAR_PROP_READ));
  ble_char_pointer->security_permissions = ATTR_PERMISSION_NONE;
  ble_char_pointer->gatt_evt_mask = ((uint8_t)GATT_NOTIFY_ATTRIBUTE_WRITE) |
                                    ((uint8_t)GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP);
  ble_char_pointer->enc_key_size = 16;
  ble_char_pointer->is_variable = 1;

  BLE_MANAGER_PRINTF("BLE Scene Description features ok\r\n");
  return ble_char_pointer;
}

/**
  * @brief  Update the Scene Description Characteristic with the provided buffer.
  * @param  buffer: Pointer to the data buffer containing the scene description.
  * @param  len: Length of the data buffer.
  * @retval Status of the characteristic update operation.
  */
ble_status_t ble_scene_description_update(uint8_t *update_data, uint32_t len)
{
  ble_status_t ret;
  ret = ACI_GATT_UPDATE_CHAR_VALUE(&ble_char_scene_description, 0, (uint8_t)len, update_data);

  if (ret != (ble_status_t)BLE_STATUS_SUCCESS)
  {
    if (ble_std_err_service == BLE_SERV_ENABLE)
    {
      bytes_to_write = (uint8_t)sprintf((char *)buffer_to_write,
                                        "Error Updating Scene Description Char with JSON data\n");
    }
    else
    {
      BLE_MANAGER_PRINTF("Error Updating Scene Description Char with JSON data\r\n");
    }
  }
  BLE_MANAGER_DELAY(20);
  return ret;
}

/**
  * @brief  This function is called when there is a change on the GATT attribute
  *         With this function it's possible to understand if Robot Scene Description is subscribed
  *         or not to the one service.
  * @param  void *void_char_pointer
  * @param  uint16_t attr_handle Handle of the attribute
  * @param  uint16_t offset: (SoC mode) the offset is never used and it is always 0. Network coprocessor mode:
  *                          - Bits 0-14: offset of the reported value inside the attribute.
  *                          - Bit 15: if the entire value of the attribute does not fit inside a single
  *                            ACI_GATT_ATTRIBUTE_MODIFIED_EVENT event, this bit is set to 1 to notify that other
  *                            ACI_GATT_ATTRIBUTE_MODIFIED_EVENT events will follow to report the remaining value.
  * @param  uint8_t data_length length of the data
  * @param  uint8_t *att_data attribute data
  */
static void attr_mod_request_scene_description(void *void_char_pointer, uint16_t attr_handle, uint16_t offset,
                                               uint8_t data_length,
                                               uint8_t *att_data)
{
  if (att_data[0] == 01U)
  {
    notify_event_scene_description(BLE_NOTIFY_SUB);
  }
  else if (att_data[0] == 0U)
  {
    notify_event_scene_description(BLE_NOTIFY_UNSUB);
  }

#if (BLE_DEBUG_LEVEL>1)
  if (ble_std_term_service == BLE_SERV_ENABLE)
  {
    bytes_to_write = (uint8_t)sprintf((char *)buffer_to_write,
                                      "--->SceneDescription=%s\n",
                                      (att_data[0] == BLE_NOTIFY_SUB) ? " ON" : " OFF");
    term_update(buffer_to_write, bytes_to_write);
  }
  else
  {
    BLE_MANAGER_PRINTF("--->SceneDescription=%s", (att_data[0] == BLE_NOTIFY_SUB) ? " ON\r\n" : " OFF\r\n");
  }
#endif /* (BLE_DEBUG_LEVEL>1) */
}

/**
  * @brief  This event is given when a write request is received by the server from the client.
  * @param  void *ble_char_pointer
  * @param  uint16_t handle Handle of the attribute
  */
static void write_request_scene_description(void *ble_char_pointer, uint16_t handle, uint16_t offset,
                                            uint8_t data_length, uint8_t *att_data)
{
  write_request_scene_description_function(att_data, data_length);
}

#if ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N))
/**
  * @brief  This event is given when a read request is received by the server from the client.
  * @param  void *ble_char_pointer Pointer to the characteristic object
  * @param  uint16_t handle Handle of the attribute
  */
static void read_request_scene_description(void *ble_char_pointer, uint16_t handle)
#else /* ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N)) */
/**
  * @brief  This event is given when a read request is received by the server from the client.
  * @param  void *ble_char_pointer Pointer to the characteristic object
  * @param  uint16_t handle Handle of the attribute
  * @param  connection_handle Connection handle
  * @param  operation_type see aci_gatt_srv_authorize_nwk_event
  * @param  attr_val_offset ffset from which the value needs to be read or write
  * @param  data_length Length of Data field
  * @param  data[] The data that the client has requested to write
  */
static void read_request_scene_description(void *ble_char_pointer,
                                           uint16_t handle,
                                           uint16_t connection_handle,
                                           uint8_t operation_type,
                                           uint16_t attr_val_offset,
                                           uint8_t data_length,
                                           uint8_t data[])
#endif /* ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N)) */
{
  read_request_scene_description_function(NULL);
}

/********************************************************
  * Callback function to manage the notification events *
  *******************************************************/
/**
  * @brief  Callback function to manage notification subscription events.
  * @param  ble_notify_event_t event Notification subscribe/unsubscribe event
  */
__weak void notify_event_scene_description(ble_notify_event_t event)
{
  /* Prevent unused argument(s) compilation warning */
  BLE_UNUSED(event);

  if (event == BLE_NOTIFY_SUB)
  {
    BLE_MANAGER_PRINTF("\r\nNotify scene description event function not defined (It is a weak function)\r\n");
  }

  /* NOTE: This function Should not be modified, when the callback is needed,
           the notify_event_scene_description could be implemented in the user file
   */
}

/********************************************************
  * Callback function to manage the write request events *
  *******************************************************/
/**
  * @brief  Callback Function for Scene description write request.
  * @param  uint8_t *received_msg
  * @param  uint8_t msg_length
  */
__weak void write_request_scene_description_function(uint8_t *received_msg, uint32_t msg_length)
{
  /* Prevent unused argument(s) compilation warning */
  BLE_UNUSED(received_msg);
  BLE_UNUSED(msg_length);

  BLE_MANAGER_PRINTF("\r\nWrite Scene Description detection function not defined (It is a weak function)\r\n");

  /* NOTE: This function Should not be modified, when the callback is needed,
           the write_request_scene_description_function could be implemented in the user file
   */
}
/********************************************************
  * Callback function to manage the read request events *
  *******************************************************/
/**
  * @brief  Callback Function for scene description read request.
  * @param  uint8_t *status of the feature
  */
__weak void read_request_scene_description_function(uint8_t *status)
{
  BLE_UNUSED(status);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the read_request_sceneDescription_Function could be implemented in the user file (BLE_Implementation.c)
   */
}


