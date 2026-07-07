/**
  ******************************************************************************
  * @file    ble_hr_measurement.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Heart Rate Measurement characteristic APIs.
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
#ifndef _BLE_HR_MEASUREMENT_H_
#define _BLE_HR_MEASUREMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Exported defines ----------------------------------------------------------*/
#ifndef DEFAULT_MAX_HR_MEASUREMENT_CHAR_LEN
#define DEFAULT_MAX_HR_MEASUREMENT_CHAR_LEN    6U
#endif /* DEFAULT_MAX_HR_MEASUREMENT_CHAR_LEN */

/* Backward compatibility with previous typo used in local draft code. */
#ifndef DEFAULT_MAX_HR_MEASURENENT_CHAR_LEN
#define DEFAULT_MAX_HR_MEASURENENT_CHAR_LEN DEFAULT_MAX_HR_MEASUREMENT_CHAR_LEN
#endif /* DEFAULT_MAX_HR_MEASURENENT_CHAR_LEN */

/* Keep the same service key used by the old Heart Monitor integration. */
#ifndef HEART_MONITOR_SRV_KEY
#define HEART_MONITOR_SRV_KEY                   (0x4321)
#endif /* HEART_MONITOR_SRV_KEY */

/*
 * Heart Rate Measurement Flags (BLE UUID 0x2A37) field values.
 *
 * Bit 0: heart_rate_value_format
 * 0: UINT8, 1: UINT16
 *
 * Bits 1-2: sensor_contact_status
 * 0: not supported, 1: supported but not detected, 3: supported and detected
 *
 * Bit 3: energy_expended_status
 * 0: not present, 1: present
 *
 * Bit 4: rr_interval
 * 0: not present, 1: present
 *
 * Bits 5-7: reserved
 * should be 0
 */
#define BLE_HR_VALUE_FORMAT_UINT8                           (0U)
#define BLE_HR_VALUE_FORMAT_UINT16                          (1U)

#define BLE_HR_SENSOR_CONTACT_NOT_SUPPORTED_FIELD           (0U)
#define BLE_HR_SENSOR_CONTACT_SUPPORTED_NOT_DETECTED_FIELD  (1U)
#define BLE_HR_SENSOR_CONTACT_SUPPORTED_DETECTED_FIELD      (3U)

#define BLE_HR_ENERGY_EXPENDED_NOT_PRESENT                  (0U)
#define BLE_HR_ENERGY_EXPENDED_PRESENT                      (1U)

#define BLE_HR_RR_INTERVAL_NOT_PRESENT                      (0U)
#define BLE_HR_RR_INTERVAL_PRESENT                          (1U)

#define BLE_HR_RESERVED_DEFAULT                             (0U)

/* Exported typedef ----------------------------------------------------------*/
typedef enum
{
  BLE_HR_SENSOR_CONTACT_NOT_SUPPORTED    = 0x00,
  BLE_HR_SENSOR_CONTACT_SUPPORTED_NOT_DETECTED = 0x02,
  BLE_HR_SENSOR_CONTACT_SUPPORTED_DETECTED = 0x06
} ble_hr_sensor_contact_t;

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Init Heart Rate Measurement characteristic
  * @param  max_length Maximum characteristic length
  * @param  heart_rate_value_format Heart Rate Value Format bit (0: uint8, 1: uint16)
  * @param  sensor_contact_status Sensor Contact Status bits value (2-bit field)
  * @param  energy_expended_status Energy Expended Status bit
  * @param  rr_interval RR-Interval bit
  * @param  reserved Reserved bits value (3-bit field)
  * @retval ble_char_object_t* Characteristic object pointer
  */
extern ble_char_object_t *ble_init_hr_measurement_service(uint16_t max_length,
                                                          uint8_t heart_rate_value_format,
                                                          uint8_t sensor_contact_status,
                                                          uint8_t energy_expended_status,
                                                          uint8_t rr_interval,
                                                          uint8_t reserved);

/**
  * @brief  Update Heart Rate Measurement characteristic
  * @param  heart_rate_bpm Heart Rate in bpm
  * @param  rr_interval_s  RR interval in seconds
  * @retval ble_status_t Status
  */
extern ble_status_t ble_hr_measurement_update(uint8_t heart_rate_bpm, uint16_t rr_interval_s);

/**
  * @brief  Heart Rate Measurement Get Max Char Length
  * @param  None
  * @retval uint16_t max_char_length
  */
extern uint16_t ble_hr_measurement_get_max_char_length(void);

/**
  * @brief  Heart Rate Measurement Set Max Char Length
  * @param  max_char_length max char length
  * @retval none
  */
extern void ble_hr_measurement_set_max_char_length(uint16_t max_char_length);

/* Backward compatibility alias for legacy misspelled name. */
extern ble_char_object_t *ble_init_hr_meassurement_service(uint16_t max_lenght);

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
extern void notify_event_hr_measurement(ble_notify_event_t event);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_HR_MEASUREMENT_H_ */

