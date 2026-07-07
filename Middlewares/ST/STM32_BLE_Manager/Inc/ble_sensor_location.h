/**
  ******************************************************************************
  * @file    ble_sensor_location.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Body Sensor Location characteristic APIs.
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
#ifndef _BLE_SENSOR_LOCATION_H_
#define _BLE_SENSOR_LOCATION_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Exported defines ----------------------------------------------------------*/
#ifndef DEFAULT_MAX_SENSOR_LOCATION_CHAR_LEN
#define DEFAULT_MAX_SENSOR_LOCATION_CHAR_LEN    1U
#endif /* DEFAULT_MAX_SENSOR_LOCATION_CHAR_LEN */

/* Keep the same service key used by the old Heart Monitor integration. */
#ifndef HEART_MONITOR_SRV_KEY
#define HEART_MONITOR_SRV_KEY                   (0x4321)
#endif /* HEART_MONITOR_SRV_KEY */

/* Exported typedef ----------------------------------------------------------*/
typedef enum
{
  BLE_SENSOR_LOCATION_OTHER = 0,
  BLE_SENSOR_LOCATION_CHEST,
  BLE_SENSOR_LOCATION_WRIST,
  BLE_SENSOR_LOCATION_FINGER,
  BLE_SENSOR_LOCATION_HAND,
  BLE_SENSOR_LOCATION_EAR_LOBE,
  BLE_SENSOR_LOCATION_FOOT
} ble_sensor_location_t;

/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Init Body Sensor Location characteristic
  * @param  max_length Maximum characteristic length
  * @param  default_sensor_location Default value exposed by this characteristic.
  *         Use one value from ble_sensor_location_t
  * @retval ble_char_object_t* Characteristic object pointer
  */
extern ble_char_object_t *ble_init_sensor_location_service(uint16_t max_length,
                                                           uint8_t default_sensor_location);

/**
  * @brief  Update Body Sensor Location characteristic
  * @param  sensor_location Body sensor location enum value
  * @retval ble_status_t Status
  */
extern ble_status_t ble_sensor_location_update(uint8_t sensor_location);

/**
  * @brief  Body Sensor Location Get Max Char Length
  * @param  None
  * @retval uint16_t max_char_length
  */
extern uint16_t ble_sensor_location_get_max_char_length(void);

/**
  * @brief  Body Sensor Location Set Max Char Length
  * @param  max_char_length max char length
  * @retval none
  */
extern void ble_sensor_location_set_max_char_length(uint16_t max_char_length);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_SENSOR_LOCATION_H_ */
