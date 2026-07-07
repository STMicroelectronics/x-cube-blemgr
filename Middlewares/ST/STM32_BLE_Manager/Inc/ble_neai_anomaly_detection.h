/**
  ******************************************************************************
  * @file    ble_neai_anomaly_detection.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.2.0
  * @date    20-April-2026
  * @brief   NEAI(Cartesiam) Anomaly Detection info services APIs.
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
#ifndef _BLE_NEAI_ANOMALY_DETECTION_H_
#define _BLE_NEAI_ANOMALY_DETECTION_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Exported Defines ---------------------------------------------------------*/
#define NEAI_AD_ESCAPE 0xFF

typedef enum
{
  NEAI_AD_STATUS_NORMAL  = 0x00,
  NEAI_AD_STATUS_ANOMALY = 0x01,
  NEAI_AD_STATUS_NULL    = 0xFF
} ble_ad_status_t;

typedef enum
{
  NEAI_AD_PHASE_IDLE          = 0x00,
  NEAI_AD_PHASE_LEARNING      = 0x01,
  NEAI_AD_PHASE_DETECTING     = 0x02,
  NEAI_AD_PHASE_IDLE_TRAINED  = 0x03,
  NEAI_AD_PHASE_BUSY          = 0x04,
  NEAI_AD_PHASE_NULL          = 0xFF
} ble_ad_phase_t;

typedef enum
{
  NEAI_AD_STATE_OK              = 0x00,
  NEAI_AD_STATE_NOINIT          = 0x7B,
  NEAI_AD_STATE_BOARD_ERROR     = 0x7C,
  NEAI_AD_STATE_BUFFER_ERROR    = 0x7D,
  NEAI_NOT_STATE_ENOUGH_CALL    = 0x7E,
  NEAI_AD_STATE_LEARNING_DONE   = 0x7F,
  NEAI_AD_STATE_UNKNOWN         = 0x80,
  NEAI_AD_STATE_NULL            = 0xFF
} ble_ad_state_t;

typedef struct
{
  ble_ad_phase_t phase;
  ble_ad_state_t state;
  uint8_t progress;
  uint8_t status;
  uint8_t similarity;
} ble_ad_output_t;

typedef enum
{
  NEAI_AD_STOP    = 0x00,
  NEAI_AD_LEARN   = 0x01,
  NEAI_AD_DETECT  = 0x02,
  NEAI_AD_RESET   = 0xFF
} ble_ad_command_t;

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Init NeaiAnomalyDetection info service
  * @retval *ble_char_pointer: Data structure pointer for environmental info service
  */
extern ble_char_object_t *ble_init_ad_service(void);

/**
  * @brief  Update NEAI AD characteristic value
  * @param  output contains info about:
  * - phase = (idle=0x00) | (learning=0x01) | (detecting=0x02)
  * - state = (NEAI_OK=0x00) | .....
  * - progress = from 0x00 to 0x64 (completion percentage)
  * - status = (normal=0x00) | (anomaly=0x01)
  * - similarity = from 0x00 to 0x64 (inference probability)
  *
  * ONLY THE PHASE FIELD IS MANDATORY
  * if you don't want use one of the others info, you can put NEAI_AD_ESCAPE
  *
  * @retval status
  */
extern ble_status_t ble_neai_anomaly_detection_update(ble_ad_output_t output);

/************************************************************
  * Callback function prototype to manage the notify events *
  ***********************************************************/
extern void notify_event_neai_anomaly_detection(ble_notify_event_t event);

/******************************************************************
  * Callback function prototype to manage the write request events *
  *****************************************************************/
extern void write_request_neai_anomaly_detection_function(uint8_t *att_data, uint8_t data_length);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_NEAI_ANOMALY_DETECTION_H_ */
