/**
  ******************************************************************************
  * @file    BLE_NeaiNClassClassification.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 1.6.0
  * @date    15-September-2022
  * @brief   NEAI N-Class Classification info services APIs.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/**
  *  How NEAI NCC characteristic works
  *
  *  Byte    |    0    |    1    |    2    |    3    |    4    |    5    |        6         |       7       |     8 - 12
  *  Field   |      ********  NOT USED  ********     |  PHASE  |  STATE  | CLASS_NUMBER_NCC |  MAJOR CLASS  | PROBABILITIES
  *
  *  NEAI NCC characteristic length depends on the number of class defined in the NEAI NCC library,
  *  its length is equals to --> 8 + CLASS_NUMBER_NCC
  *
  */

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BLE_NEAI_N_CLASS_CLASSIFICATION_H_
#define _BLE_NEAI_N_CLASS_CLASSIFICATION_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported Defines ---------------------------------------------------------*/
#ifndef CLASS_NUMBER_NCC
#define CLASS_NUMBER_NCC 2
#endif

#define NEAI_NCC_ESCAPE  0xFF

typedef enum
{
  NEAI_NCC_PHASE_IDLE            = 0x00,
  NEAI_NCC_PHASE_CLASSIFICATION  = 0x01,
  NEAI_NCC_PHASE_NULL            = 0xFF
} BLE_NCC_phase_t;

typedef enum
{
  NEAI_NCC_STATE_OK                         = 0x00,
  NEAI_NCC_STATE_NOINIT                     = 0x7B,
  NEAI_NCC_STATE_BOARD_ERROR                = 0x7C,
  NEAI_NCC_STATE_BUFFER_ERROR               = 0x7D,
  NEAI_NCC_STATE_ENOUGH_CALL                = 0x7E,
  NEAI_NCC_STATE_RECOMMENDED_LEARNING_DONE  = 0x7F,
  NEAI_NCC_STATE_UNKNOWN                    = 0x80,
  NEAI_NCC_STATE_NULL                       = 0xFF
} BLE_NCC_state_t;

typedef struct
{
  BLE_NCC_phase_t phase;
  BLE_NCC_state_t state;
  uint8_t major_class;
  float *probabilities;
} BLE_NCC_output_t;

typedef enum
{
  NEAI_NCC_COMMAND_STOP      = 0x00,
  NEAI_NCC_COMMAND_CLASSIFY  = 0x01
} BLE_NCC_command_t;


typedef void (*CustomNotifyEventNeaiNClassClassification_t)(BLE_NotifyEvent_t Event);
typedef void (*CustomWriteRequestNClassClassification_t)(uint8_t * att_data, uint8_t data_length);

/* Exported Variables ------------------------------------------------------- */
extern CustomNotifyEventNeaiNClassClassification_t CustomNotifyEventNCC;
extern CustomWriteRequestNClassClassification_t CustomWriteRequestNCC;

/* Exported functions ------------------------------------------------------- */

/**
 * @brief  Init N-Class Classification info service
 * @retval BleCharTypeDef* BleCharPointer: Data structure pointer for N-Class Classification info service
 */
extern BleCharTypeDef* BLE_InitNCCService(void);

/**
 * @brief  Update N-Class Classification characteristic value
 * @param  BLE_NCC_output_t    output:
 * @retval tBleStatus:         Status
 */
extern tBleStatus BLE_NeaiNClassClassificationUpdate(BLE_NCC_output_t output);

#ifdef __cplusplus
}
#endif

#endif /* _BLE_NEAI_N_CLASS_CLASSIFICATION_H_ */
