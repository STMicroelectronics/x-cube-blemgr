/**
  ******************************************************************************
  * @file    ble_hr_measurement.c
  * @author  MEMS Sensor Application Team.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Add Heart Rate Measurement characteristic using standard HR Monitor profile.
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
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ble_manager.h"
#include "ble_manager_common.h"
#include "ble_hr_measurement.h"

/* Private define ------------------------------------------------------------*/
#define HEART_RATE_MEASURMENT_UUID                                     (0x2A37)

typedef union
{
  struct
  {
    uint8_t heart_rate_value_format : 1;
    uint8_t sensor_contact_status : 2;
    uint8_t energy_expended_status : 1;
    uint8_t rr_interval : 1;
    uint8_t reserved : 3;
  } bits;
  uint8_t byte;
} heart_rate_measurement_flags_t;

/* Private variables ---------------------------------------------------------*/
static ble_char_object_t ble_hr_measurement;
static uint16_t hr_measurement_max_char_length = DEFAULT_MAX_HR_MEASUREMENT_CHAR_LEN;
static heart_rate_measurement_flags_t hr_meas_flags;

/* Private functions ---------------------------------------------------------*/
static void attr_mod_request_hr_measurement(void *void_char_pointer, uint16_t attr_handle, uint16_t offset,
                                            uint8_t data_length, uint8_t *att_data);

/**
  * @brief  Init Heart Rate Measurement characteristic
  * @param  max_length Maximum characteristic length
  * @param  heart_rate_value_format Heart Rate Value Format bit (0: uint8, 1: uint16)
  * @param  sensor_contact_status Sensor Contact Status bits value (2-bit field)
  * @param  energy_expended_status Energy Expended Status bit
  * @param  rr_interval RR-Interval bit
  * @param  reserved Reserved bits value (3-bit field)
  * @retval ble_char_object_t* Characteristic pointer
  */
ble_char_object_t *ble_init_hr_measurement_service(uint16_t max_length,
                                                   uint8_t heart_rate_value_format,
                                                   uint8_t sensor_contact_status,
                                                   uint8_t energy_expended_status,
                                                   uint8_t rr_interval,
                                                   uint8_t reserved)
{
  ble_char_object_t *ble_char_pointer = &ble_hr_measurement;

  memset(ble_char_pointer, 0, sizeof(ble_char_object_t));
  ble_char_pointer->attr_mod_request_cb = attr_mod_request_hr_measurement;
  *(uint16_t *)&ble_char_pointer->uuid[0] = HEART_RATE_MEASURMENT_UUID;
  ble_char_pointer->char_uuid_type = UUID_TYPE_16;
  ble_char_pointer->char_value_length = max_length;
  ble_char_pointer->char_properties = (uint8_t)CHAR_PROP_NOTIFY;
  ble_char_pointer->security_permissions = ATTR_PERMISSION_NONE;
  ble_char_pointer->gatt_evt_mask = GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP;
  ble_char_pointer->enc_key_size = 16;
  ble_char_pointer->is_variable = 1;
  ble_char_pointer->service_handle = HEART_MONITOR_SRV_KEY;

  hr_meas_flags.byte = 0U;
  hr_meas_flags.bits.heart_rate_value_format = heart_rate_value_format;
  hr_meas_flags.bits.sensor_contact_status = sensor_contact_status;
  hr_meas_flags.bits.energy_expended_status = energy_expended_status;
  hr_meas_flags.bits.rr_interval = rr_interval;
  hr_meas_flags.bits.reserved = reserved;

  hr_measurement_max_char_length = max_length;

  BLE_MANAGER_PRINTF("BLE HR Measurement feature ok\r\n");

  return ble_char_pointer;
}

/**
  * @brief  Backward-compatible alias for old misspelled API
  * @param  max_lenght Maximum characteristic length
  * @retval ble_char_object_t* Characteristic pointer
  */
ble_char_object_t *ble_init_hr_meassurement_service(uint16_t max_lenght)
{
  return ble_init_hr_measurement_service(max_lenght,
                                         BLE_HR_VALUE_FORMAT_UINT8,
                                         BLE_HR_SENSOR_CONTACT_SUPPORTED_DETECTED_FIELD,
                                         BLE_HR_ENERGY_EXPENDED_NOT_PRESENT,
                                         BLE_HR_RR_INTERVAL_PRESENT,
                                         BLE_HR_RESERVED_DEFAULT);
}

/**
  * @brief  Update Heart Rate Measurement characteristic
  * @param  heart_rate_bpm Heart Rate in bpm
  * @param  rr_interval_s RR interval in seconds
  * @retval ble_status_t   Status
  */
ble_status_t ble_hr_measurement_update(uint8_t heart_rate_bpm, uint16_t rr_interval_s)
{
  ble_status_t ret;
  uint8_t buff[DEFAULT_MAX_HR_MEASUREMENT_CHAR_LEN];

  if (hr_measurement_max_char_length < sizeof(buff))
  {
    BLE_MANAGER_PRINTF("BLE HR Measurement Error ... Max Len too small %d<%d\r\n",
                       hr_measurement_max_char_length,
                       (uint16_t)sizeof(buff));
    return (ble_status_t)BLE_ERROR_LIMIT_REACHED;
  }

  buff[0] = hr_meas_flags.byte;
  buff[1] = heart_rate_bpm;
  buff[2] = (uint8_t)(rr_interval_s & 0xFFU);
  buff[3] = (uint8_t)((rr_interval_s >> 8) & 0xFFU);
  buff[4] = 0U;
  buff[5] = 0U;

  ret = ACI_GATT_UPDATE_CHAR_VALUE(&ble_hr_measurement, 0, (uint8_t)(sizeof(buff)), buff);

  if (ret != (ble_status_t)BLE_STATUS_SUCCESS)
  {
    if (ble_std_err_service == BLE_SERV_ENABLE)
    {
      bytes_to_write = (uint8_t)sprintf((char *)buffer_to_write, "Error Updating HR Measurement Char\n");
      std_err_update(buffer_to_write, bytes_to_write);
    }
    else
    {
      BLE_MANAGER_PRINTF("Error Updating HR Measurement Char ret=%x\r\n", ret);
    }
  }

  return ret;
}

/**
  * @brief  Heart Rate Measurement Get Max Char Length
  * @param  None
  * @retval uint16_t max_char_length
  */
uint16_t ble_hr_measurement_get_max_char_length(void)
{
  return hr_measurement_max_char_length;
}

/**
  * @brief  Heart Rate Measurement Set Max Char Length
  * @param  max_char_length max char length
  * @retval none
  */
void ble_hr_measurement_set_max_char_length(uint16_t max_char_length)
{
  hr_measurement_max_char_length = max_char_length;
}

/**
  * @brief  This function is called when there is a change on the gatt attribute
  * @param  void_char_pointer Characteristic pointer
  * @param  attr_handle Handle of the attribute
  * @param  offset attribute offset
  * @param  data_length length of the data
  * @param  att_data attribute data
  * @retval None
  */
static void attr_mod_request_hr_measurement(void *void_char_pointer, uint16_t attr_handle, uint16_t offset,
                                            uint8_t data_length, uint8_t *att_data)
{
  BLE_UNUSED(void_char_pointer);
  BLE_UNUSED(attr_handle);
  BLE_UNUSED(offset);
  BLE_UNUSED(data_length);

  if (att_data[0] == 01U)
  {
    notify_event_hr_measurement(BLE_NOTIFY_SUB);
  }
  else if (att_data[0] == 0U)
  {
    notify_event_hr_measurement(BLE_NOTIFY_UNSUB);
  }

#if (BLE_DEBUG_LEVEL > 1)
  if (ble_std_term_service == BLE_SERV_ENABLE)
  {
    bytes_to_write = (uint8_t)sprintf((char *)buffer_to_write,
                                      "--->HRMeasurement=%s\n",
                                      (att_data[0] == 01U) ? " ON" : " OFF");
    term_update(buffer_to_write, bytes_to_write);
  }
  else
  {
    BLE_MANAGER_PRINTF("--->HRMeasurement=%s", (att_data[0] == 01U) ? " ON\r\n" : " OFF\r\n");
  }
#endif /* (BLE_DEBUG_LEVEL > 1) */
}

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
/**
  * @brief  Callback Function for Un/Subscription Feature
  * @param  event Sub/Unsub event
  * @retval None
  */
__weak void notify_event_hr_measurement(ble_notify_event_t event)
{
  BLE_UNUSED(event);

  BLE_MANAGER_PRINTF("\r\nNotify hr measurement function not defined (It is a weak function)\r\n");
}