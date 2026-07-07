/**
  ******************************************************************************
  * @file    ble_robot_movement.c
  * @author  System Research & Applications Team - Noida/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Add Robot Movement services.
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
#include "ble_robot_movement.h"

/* Private define ------------------------------------------------------------*/
#define COPY_ROBOT_MOVEMENT_CHAR_UUID(uuid_struct) COPY_UUID_128(uuid_struct,0x00,0x00,0x00,0x28,0x00,0x02,0x11,\
                                                                 0xe1,0xac,0x36,0x00,0x02,0xa5,0xd5,0xc5,0x1b)

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
__weak void notify_event_robot_movement(ble_notify_event_t event);

/******************************************************************
  * Callback function prototype to manage the write request events *
  *****************************************************************/
__weak void write_request_robot_movement_function(uint8_t *received_msg, uint32_t msg_length);

/* Private variables ---------------------------------------------------------*/
/* Data structure pointer for Robot Movement service */
static ble_char_object_t ble_char_robot_movement;

/* Private functions ---------------------------------------------------------*/
static void attr_mod_request_robot_movement(void *ble_char_pointer, uint16_t attr_handle, uint16_t offset,
                                            uint8_t data_length,
                                            uint8_t *att_data);

static void write_request_robot_movement(void *ble_char_pointer, uint16_t handle, uint16_t offset, uint8_t data_length,
                                         uint8_t *att_data);

static uint16_t robot_movement_max_char_length = DEFAULT_MAX_NOTIFICATION_CHAR_LEN;

/**
  * @brief  Init Robot Movement service
  * @retval ble_char_object_t *ble_char_pointer: Data structure pointer for Robot Movement service
  */
ble_char_object_t *ble_init_robot_movement_service(void)
{
  /* Data structure pointer for BLE service */
  ble_char_object_t *ble_char_pointer;

  /* Init data structure pointer for Robot Movement service */
  ble_char_pointer = &ble_char_robot_movement;
  memset(ble_char_pointer, 0, sizeof(ble_char_object_t));
  ble_char_pointer->attr_mod_request_cb = attr_mod_request_robot_movement;
  ble_char_pointer->write_request_cb = write_request_robot_movement;
  COPY_ROBOT_MOVEMENT_CHAR_UUID((ble_char_pointer->uuid));
  ble_char_pointer->char_uuid_type = UUID_TYPE_128;
  ble_char_pointer->char_value_length = robot_movement_max_char_length;
  ble_char_pointer->char_properties = ((uint8_t)CHAR_PROP_NOTIFY) | ((uint8_t)CHAR_PROP_WRITE);
  ble_char_pointer->security_permissions = ATTR_PERMISSION_NONE;
  ble_char_pointer->gatt_evt_mask = ((uint8_t)GATT_NOTIFY_ATTRIBUTE_WRITE) |
                                    ((uint8_t)GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP);
  ble_char_pointer->enc_key_size = 20;
  ble_char_pointer->is_variable = 1;

  BLE_MANAGER_PRINTF("BLE Robot Movement features ok\r\n");

  return ble_char_pointer;
}


/**
  * @brief  Update Robot Movement characteristic value
  * @param  robot_movement_status: Robot Movement packet
  * @retval Status
  */
ble_status_t ble_robot_movement_update(uint8_t robot_movement_status)
{
  ble_status_t ret;
  uint8_t buff[2 + 1];

  STORE_LE_16(buff, (HAL_GetTick() / 10U));
  buff[2] = robot_movement_status;

  ret = ACI_GATT_UPDATE_CHAR_VALUE(&ble_char_robot_movement, 0, 2 + 1, buff);

  if (ret != (ble_status_t)BLE_STATUS_SUCCESS)
  {
    if (ble_std_err_service == BLE_SERV_ENABLE)
    {
      bytes_to_write = (uint8_t)sprintf((char *)buffer_to_write, "Error Updating Robot Movement Char\n");
      std_err_update(buffer_to_write, bytes_to_write);
    }
    else
    {
      BLE_MANAGER_PRINTF("Error Updating Robot Movement Char\r\n");
    }
  }
  return ret;

}

/**
  * @brief  This function is called when there is a change on the GATT attribute
  *         With this function it's possible to understand if Robot Movement is subscribed or not to the one service
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
static void attr_mod_request_robot_movement(void *void_char_pointer, uint16_t attr_handle, uint16_t offset,
                                            uint8_t data_length,
                                            uint8_t *att_data)
{
  if (att_data[0] == 01U)
  {
    notify_event_robot_movement(BLE_NOTIFY_SUB);
  }
  else if (att_data[0] == 0U)
  {
    notify_event_robot_movement(BLE_NOTIFY_UNSUB);
  }

#if (BLE_DEBUG_LEVEL>1)
  if (ble_std_term_service == BLE_SERV_ENABLE)
  {
    bytes_to_write = (uint8_t)sprintf((char *)buffer_to_write,
                                      "--->RobotMovement=%s\n",
                                      (att_data[0] == BLE_NOTIFY_SUB) ? " ON" : " OFF");
    term_update(buffer_to_write, bytes_to_write);
  }
  else
  {
    BLE_MANAGER_PRINTF("--->RobotMovement=%s", (att_data[0] == BLE_NOTIFY_SUB) ? " ON\r\n" : " OFF\r\n");
  }
#endif /* (BLE_DEBUG_LEVEL>1) */
}

/**
  * @brief  This event is given when a write request is received by the server from the client.
  * @param  void *ble_char_pointer
  * @param  uint16_t handle Handle of the attribute
  */
static void write_request_robot_movement(void *ble_char_pointer, uint16_t handle, uint16_t offset, uint8_t data_length,
                                         uint8_t *att_data)
{
  BLE_MANAGER_PRINTF("%x %x %x %x %x %x\r\n", att_data[0], att_data[1], att_data[2], att_data[3], att_data[4],
                     att_data[5]);
  write_request_robot_movement_function(att_data, data_length);
}
/**
  * @brief  Robot Movement Set Max Char Length
  * @param  uint16_t max_char_length
  */
void ble_robot_movement_set_max_char_length(uint16_t max_char_length)
{
  robot_movement_max_char_length = max_char_length;
}

/**
  * @brief  Robot Movement Get Max Char Length
  * @retval uint16_t max_char_length
  */
uint16_t ble_robot_movement_get_max_char_length(void)
{
  return robot_movement_max_char_length;
}

/**************************************************
  * Callback function to manage the notify events *
  *************************************************/
/**
  * @brief  Callback Function for Un/Subscription Feature
  * @param  event Sub/Unsub
  */
__weak void notify_event_robot_movement(ble_notify_event_t event)
{
  /* Prevent unused argument(s) compilation warning */
  BLE_UNUSED(event);

  if (event == BLE_NOTIFY_SUB)
  {
    BLE_MANAGER_PRINTF("\r\nNotify robot movement event function not defined (It is a weak function)\r\n");
  }

  /* NOTE: This function Should not be modified, when the callback is needed,
           the notify_event_robot_movement could be implemented in the user file
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
__weak void write_request_robot_movement_function(uint8_t *received_msg, uint32_t msg_length)
{
  /* Prevent unused argument(s) compilation warning */
  BLE_UNUSED(received_msg);
  BLE_UNUSED(msg_length);

  BLE_MANAGER_PRINTF("\r\nWrite Robot Movement detection function not defined (It is a weak function)\r\n");

  /* NOTE: This function Should not be modified, when the callback is needed,
           the write_request_robot_movement_function could be implemented in the user file
   */
}
