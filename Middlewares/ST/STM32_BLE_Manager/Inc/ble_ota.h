/**
  ******************************************************************************
  * @file    ble_ota.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   Ota characteristic APIs.
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
#ifndef _BLE_OTA_H_
#define _BLE_OTA_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BLUE_WB
#error "This Feature is only for WB BLE Chip"
#endif /* BLUE_WB */

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Init OTA characteristic
  * @retval *ble_char_pointer: Data structure pointer for OTA characteristic
  */
extern ble_char_object_t *ble_init_ota_service(void);

/******************************************************************
  * Callback function prototype to manage the write request events *
  *****************************************************************/
extern void write_request_ota_function(uint8_t *att_data, uint8_t data_length);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_GNSS_H_ */

