/**
  ******************************************************************************
  * @file    ble_environmental.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Environmental info services APIs.
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
#ifndef _BLE_ENVIRONMENTAL_H_
#define _BLE_ENVIRONMENTAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Exported Defines ----------------------------------------------------------*/
/* Feature mask for Temperature1 */
#define FEATURE_MASK_TEMP1 0x00040000
/* Feature mask for Temperature2 */
#define FEATURE_MASK_TEMP2 0x00010000
/* Feature mask for Pressure */
#define FEATURE_MASK_PRESS 0x00100000
/* Feature mask for Humidity */
#define FEATURE_MASK_HUM   0x00080000

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Init environmental info service
  * @param  press_enable:    1 for enabling the BLE pressure feature, 0 otherwise.
  * @param  hum_enable:      1 for enabling the BLE humidity feature, 0 otherwise.
  * @param  num_temp_enabled: 0 for disabling BLE temperature feature
  *                                 1 for enabling only one BLE temperature feature
  *                                 2 for enabling two BLE temperatures feature
  * @retval *ble_char_pointer: Data structure pointer for environmental info service
  */
extern ble_char_object_t *ble_init_env_service(uint8_t press_enable, uint8_t hum_enable, uint8_t num_temp_enabled);

#ifndef BLE_MANAGER_SDKV2
/**
  * @brief  Setting Environmental Advertise Data
  * @param  *manuf_data: Advertise Data
  */
extern void ble_set_env_advertise_data(uint8_t *manuf_data);
#endif /* BLE_MANAGER_SDKV2 */

/**
  * @brief  Update Environmental characteristic value
  * @param  press:  Pressure in mbar (Set 0 if not used)
  * @param  hum:    humidity RH (Relative Humidity) in thenths of % (Set 0 if not used)
  * @param  temp1:  Temperature in tenths of degree (Set 0 if not used)
  * @param  temp2:  Temperature in tenths of degree (Set 0 if not used)
  * @retval status
  */
extern ble_status_t ble_environmental_update(int32_t press, uint16_t hum, int16_t temp1, int16_t temp2);

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
extern void notify_event_env(ble_notify_event_t event);

/******************************************************************
  * Callback function prototype to manage the read request events *
  *****************************************************************/
extern void read_request_env_function(int32_t *press, uint16_t *hum, int16_t *temp1, int16_t *temp2);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_ENVIRONMENTAL_H_ */

