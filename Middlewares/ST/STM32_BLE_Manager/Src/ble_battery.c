/**
  ******************************************************************************
  * @file    ble_battery.c
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.0.0
  * @date    25-September-2024
  * @brief   Add battery info services using vendor specific profiles.
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

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "ble_manager.h"
#include "ble_manager_common.h"

/* Private define ------------------------------------------------------------*/
#define COPY_BATTERY_CHAR_UUID(uuid_struct) COPY_UUID_128(uuid_struct,0x00,0x02,0x00,0x00,\
                                                          0x00,0x01,0x11,0xe1,0xac,0x36,0x00,0x02,0xa5,0xd5,0xc5,0x1b)

#define BATTERY_ADVERTISE_DATA_POSITION  16

/* Private variables ---------------------------------------------------------*/
/* Data structure pointer for battery info service */
static ble_char_object_t ble_char_battery;

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
__weak void notify_event_battery(ble_notify_event_t event);

/* Private functions prototypes ----------------------------------------------*/
static void attr_mod_request_battery(void *ble_char_pointer, uint16_t attr_handle, uint16_t offset, uint8_t data_length,
                                     uint8_t *att_data);

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Init battery info service
  * @param  None
  * @retval ble_char_object_t* ble_char_pointer: Data structure pointer for battery info service
  */
ble_char_object_t *ble_init_battery_service(void)
{
  /* Data structure pointer for BLE service */
  ble_char_object_t *ble_char_pointer;

  /* Init data structure pointer for battery info service */
  ble_char_pointer = &ble_char_battery;
  memset(ble_char_pointer, 0, sizeof(ble_char_object_t));
  ble_char_pointer->attr_mod_request_cb = attr_mod_request_battery;
  COPY_BATTERY_CHAR_UUID((ble_char_pointer->uuid));
  ble_char_pointer->char_uuid_type = UUID_TYPE_128;
  ble_char_pointer->char_value_length = 2 + 2 + 2 + 2 + 1;
  ble_char_pointer->char_properties = CHAR_PROP_NOTIFY;
  ble_char_pointer->security_permissions = ATTR_PERMISSION_NONE;
  ble_char_pointer->gatt_evt_mask = GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP;
  ble_char_pointer->enc_key_size = 16;
  ble_char_pointer->is_variable = 0;

  BLE_MANAGER_PRINTF("BLE Battery features ok\r\n");

  return ble_char_pointer;
}

#ifndef BLE_MANAGER_SDKV2
/**
  * @brief  Setting Battery Advertise Data
  * @param  uint8_t *manuf_data: Advertise Data
  * @retval None
  */
void ble_set_battery_advertise_data(uint8_t *manuf_data)
{
  /* Setting Battery Advertise Data */
  manuf_data[BATTERY_ADVERTISE_DATA_POSITION] |= 0x02U;
}
#endif /* BLE_MANAGER_SDKV2 */

/**
  * @brief  Update Battery characteristic
  * @param  int32_t battery_level %Charge level
  * @param  uint32_t voltage Battery voltage
  * @param  uint32_t current Battery current (0x8000 if not available)
  * @param  uint32_t status Charging/Discharging
  * @retval ble_status_t   Status
  */
ble_status_t ble_battery_update(uint32_t battery_level, uint32_t voltage, uint32_t current, uint32_t status)
{
  ble_status_t ret;

  uint8_t buff[2 + 2 + 2 + 2 + 1];

  STORE_LE_16(buff, (HAL_GetTick() / 10U));
  STORE_LE_16(buff + 2, (battery_level * 10U));
  STORE_LE_16(buff + 4, (voltage));
  STORE_LE_16(buff + 6, (current));
  buff[8] = (uint8_t)status;

  ret = ACI_GATT_UPDATE_CHAR_VALUE(&ble_char_battery, 0, 2 + 2 + 2 + 2 + 1, buff);

  if (ret != (ble_status_t)BLE_STATUS_SUCCESS)
  {
    if (ble_std_err_service == BLE_SERV_ENABLE)
    {
      bytes_to_write = (uint8_t)sprintf((char *)buffer_to_write, "Error Updating Bat Char\n");
      std_err_update(buffer_to_write, bytes_to_write);
    }
    else
    {
      BLE_MANAGER_PRINTF("Error Updating Bat Char\r\n");
    }
  }
  return ret;
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  This function is called when there is a change on the gatt attribute
  *         With this function it's possible to understand if battery is subscribed or not to the one service
  * @param  void *void_char_pointer
  * @param  uint16_t attr_handle Handle of the attribute
  * @param  uint16_t offset: (SoC mode) the offset is never used and it is always 0. Network coprocessor mode:
  *                          - Bits 0-14: offset of the reported value inside the attribute.
  *                          - Bit 15: if the entire value of the attribute does not fit inside a single
  *                            ACI_GATT_ATTRIBUTE_MODIFIED_EVENT event, this bit is set to 1 to notify that other
  *                            ACI_GATT_ATTRIBUTE_MODIFIED_EVENT events will follow to report the remaining value.
  * @param  uint8_t data_length length of the data
  * @param  uint8_t *att_data attribute data
  * @retval None
  */
static void attr_mod_request_battery(void *void_char_pointer, uint16_t attr_handle, uint16_t offset,
                                     uint8_t data_length,
                                     uint8_t *att_data)
{
  if (att_data[0] == 01U)
  {
    notify_event_battery(BLE_NOTIFY_SUB);
  }
  else if (att_data[0] == 0U)
  {
    notify_event_battery(BLE_NOTIFY_UNSUB);
  }

#if (BLE_DEBUG_LEVEL>1)
  if (ble_std_term_service == BLE_SERV_ENABLE)
  {
    bytes_to_write = (uint8_t) sprintf((char *)buffer_to_write, "--->Bat=%s\n", (att_data[0] == 01U) ? " ON" : " OFF");
    term_update(buffer_to_write, bytes_to_write);
  }
  else
  {
    BLE_MANAGER_PRINTF("--->Bat=%s", (att_data[0] == 01U) ? " ON\r\n" : " OFF\r\n");
  }
#endif /* BLE_DEBUG_LEVEL>1 */
}

/**************************************************
  * Callback function to manage the notify events *
  *************************************************/
/**
  * @brief  Callback Function for Un/Subscription Feature
  * @param  ble_notify_event_t event Sub/Unsub
  * @retval None
  */
__weak void notify_event_battery(ble_notify_event_t event)
{
  /* Prevent unused argument(s) compilation warning */
  BLE_UNUSED(event);

  if (event == BLE_NOTIFY_SUB)
  {
    BLE_MANAGER_PRINTF("\r\nNotify battery function not defined (It is a weak function)\r\n");
  }

  /* NOTE: This function Should not be modified, when the callback is needed,
           the notify_event_battery could be implemented in the user file
   */
}
