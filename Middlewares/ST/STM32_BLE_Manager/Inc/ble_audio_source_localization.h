/**
  ******************************************************************************
  * @file    ble_audio_source_localization.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   E-BLE_AudioSourceLocalization info service APIs.
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
#ifndef _BLE_AUDIO_SOURCE_LOCALIZATION_H_
#define _BLE_AUDIO_SOURCE_LOCALIZATION_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Init Audio Source Localization service
  * @retval *ble_char_pointer: Data structure pointer for Audio Source Localization service
  */
extern ble_char_object_t *ble_init_audio_source_localization_service(void);

#ifndef BLE_MANAGER_SDKV2
/**
  * @brief  Setting Audio Source Localization Advertise Data
  * @param  *manuf_data: Advertise Data
  */
extern void ble_set_audio_source_localization_advertise_data(uint8_t *manuf_data);
#endif /* BLE_MANAGER_SDKV2 */

/**
  * @brief  Update Audio Source Localization characteristic
  * @param  angle Audio Source Localization evaluated angle
  * @retval status
  */
extern ble_status_t ble_audio_source_localization_update(uint16_t angle);

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
extern void notify_event_audio_source_localization(ble_notify_event_t event);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_AUDIO_SOURCE_LOCALIZATION_H_ */

