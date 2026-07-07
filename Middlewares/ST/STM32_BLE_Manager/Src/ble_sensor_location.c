/**
  ******************************************************************************
  * @file    ble_sensor_location.c
  * @author  MEMS Sensor Application Team.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Add Body Sensor Location characteristic using standard HR Monitor profile.
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
#include <string.h>
#include "ble_manager.h"
#include "ble_manager_common.h"
#include "ble_sensor_location.h"

/* Private define ------------------------------------------------------------*/
#define SENSOR_LOCATION_UUID                                          (0x2A38)

/* Private variables ---------------------------------------------------------*/
static ble_char_object_t ble_sensor_location;
static uint16_t sensor_location_max_char_length = DEFAULT_MAX_SENSOR_LOCATION_CHAR_LEN;
static uint8_t current_sensor_location = (uint8_t)BLE_SENSOR_LOCATION_FINGER;

/* Private functions ---------------------------------------------------------*/
#if ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N))
static void read_request_sensor_location(void *ble_char_pointer, uint16_t handle);
#else /* ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N)) */
static void read_request_sensor_location(void *ble_char_pointer,
                                         uint16_t handle,
                                         uint16_t connection_handle,
                                         uint8_t operation_type,
                                         uint16_t attr_val_offset,
                                         uint8_t data_length,
                                         uint8_t data[]);
#endif /* ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N)) */

/**
  * @brief  Init Body Sensor Location characteristic
  * @param  max_length Maximum characteristic length
  * @param  default_sensor_location Default body sensor location value
  * @retval ble_char_object_t* Characteristic pointer
  */
ble_char_object_t *ble_init_sensor_location_service(uint16_t max_length,
                                                    uint8_t default_sensor_location)
{
  ble_char_object_t *ble_char_pointer = &ble_sensor_location;

  memset(ble_char_pointer, 0, sizeof(ble_char_object_t));
  ble_char_pointer->read_request_cb = read_request_sensor_location;
  *(uint16_t *)&ble_char_pointer->uuid[0] = SENSOR_LOCATION_UUID;
  ble_char_pointer->char_uuid_type = UUID_TYPE_16;
  ble_char_pointer->char_value_length = max_length;
  ble_char_pointer->char_properties = (uint8_t)CHAR_PROP_READ;
  ble_char_pointer->security_permissions = ATTR_PERMISSION_NONE;
  ble_char_pointer->gatt_evt_mask = GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP;
  ble_char_pointer->enc_key_size = 16;
  ble_char_pointer->is_variable = 0;
  ble_char_pointer->service_handle = HEART_MONITOR_SRV_KEY;

  sensor_location_max_char_length = max_length;
  current_sensor_location = default_sensor_location;

  BLE_MANAGER_PRINTF("BLE Sensor Location feature ok\r\n");

  return ble_char_pointer;
}

/**
  * @brief  Update Body Sensor Location characteristic
  * @param  sensor_location Body sensor location enum value
  * @retval ble_status_t   Status
  */
ble_status_t ble_sensor_location_update(uint8_t sensor_location)
{
  ble_status_t ret;
  uint8_t buff[DEFAULT_MAX_SENSOR_LOCATION_CHAR_LEN];

  if (sensor_location_max_char_length < sizeof(buff))
  {
    BLE_MANAGER_PRINTF("BLE Sensor Location Error ... Max Len too small %d<%d\r\n",
                       sensor_location_max_char_length,
                       (uint16_t)sizeof(buff));
    return (ble_status_t)BLE_ERROR_LIMIT_REACHED;
  }

  current_sensor_location = sensor_location;
  buff[0] = current_sensor_location;

  ret = ACI_GATT_UPDATE_CHAR_VALUE(&ble_sensor_location, 0, (uint8_t)(sizeof(buff)), buff);

  if (ret != (ble_status_t)BLE_STATUS_SUCCESS)
  {
    if (ble_std_err_service == BLE_SERV_ENABLE)
    {
      bytes_to_write = (uint8_t)sprintf((char *)buffer_to_write, "Error Updating Sensor Location Char\n");
      std_err_update(buffer_to_write, bytes_to_write);
    }
    else
    {
      BLE_MANAGER_PRINTF("Error Updating Sensor Location Char ret=%x\r\n", ret);
    }
  }

  return ret;
}

/**
  * @brief  Body Sensor Location Get Max Char Length
  * @param  None
  * @retval uint16_t max_char_length
  */
uint16_t ble_sensor_location_get_max_char_length(void)
{
  return sensor_location_max_char_length;
}

/**
  * @brief  Body Sensor Location Set Max Char Length
  * @param  max_char_length max char length
  * @retval none
  */
void ble_sensor_location_set_max_char_length(uint16_t max_char_length)
{
  sensor_location_max_char_length = max_char_length;
}

/**
  * @brief  This function is called when there is a read request
  * @param  ble_char_pointer Characteristic pointer
  * @param  handle Handle of the attribute
  * @retval None
  */
#if ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N))
static void read_request_sensor_location(void *ble_char_pointer, uint16_t handle)
{
  BLE_UNUSED(ble_char_pointer);
  BLE_UNUSED(handle);

  (void)ble_sensor_location_update(current_sensor_location);
}
#else /* ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N)) */
static void read_request_sensor_location(void *ble_char_pointer,
                                         uint16_t handle,
                                         uint16_t connection_handle,
                                         uint8_t operation_type,
                                         uint16_t attr_val_offset,
                                         uint8_t data_length,
                                         uint8_t data[])
{
  ble_status_t ret;
  uint8_t buff[DEFAULT_MAX_SENSOR_LOCATION_CHAR_LEN];

  BLE_UNUSED(ble_char_pointer);

  buff[0] = current_sensor_location;

  ret = aci_gatt_srv_write_handle_value_nwk(handle,
                                            0,
                                            (uint8_t)sizeof(buff),
                                            buff);
  if (ret != (ble_status_t)BLE_STATUS_SUCCESS)
  {
    BLE_MANAGER_PRINTF("Error: read_request_sensor_location write value\r\n");
  }

  ret = aci_gatt_srv_authorize_resp_nwk(connection_handle,
                                        handle,
                                        operation_type,
                                        0,
                                        attr_val_offset,
                                        data_length,
                                        data);
  if (ret != BLE_STATUS_SUCCESS)
  {
    BLE_MANAGER_PRINTF("aci_gatt_srv_authorize_resp_nwk() failed: 0x%02x\r\n", ret);
  }
}
#endif /* ((BLUE_CORE != BLUENRG_LP) && (BLUE_CORE != STM32WB07_06) && (BLUE_CORE != STM32WB05N)) */
