/**
  ******************************************************************************
  * @file    bluenrg_utils.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.0.0
  * @date    25-September-2024
  * @brief   Header file for BlueNRG-1,2 utility functions
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BLUENRG_UTILS_H
#define __BLUENRG_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "compiler.h"
#include "ble_types.h"

/* Exported types ------------------------------------------------------------*/

/**
  * Structure inside IFR for configuration options.
  */
typedef  PACKED(struct) dev_config_s
{
  uint8_t  swxo_tune;
  uint8_t  ls_source;
  uint8_t  smps_management;
  uint8_t  reserved;
  uint16_t hs_startup_time;
  uint16_t sca;
  uint8_t  reserved_2;
  uint32_t max_conn_event_length;
  uint8_t  test_mode;
} dev_config_t;

/* Exported constants --------------------------------------------------------*/

#define BASE_ADDRESS    (0x10040000)
#define SECTOR_SIZE     (2*1024)  /* 2 KB */

/* Exported macros -----------------------------------------------------------*/
#define FROM_US_TO_SYS_TIME(us)      ((uint32_t)(us/2.4414)+1)
#define FROM_SYS_TIME_TO_US(sys)     ((uint32_t)(sys*2.4414))

/* Convert 2 digit BCD number to an integer */
#define BCD_TO_INT(bcd) ((bcd & 0xF) + ((bcd & 0xF0) >> 4)*10)

/* Convert 2 digit number to a BCD number */
#define INT_TO_BCD(n) ((((uint8_t)n/10)<<4) + (uint8_t)n%10)

/**
  * Return values
  */
#define BLE_UTIL_SUCCESS                 0
#define BLE_UTIL_UNSUPPORTED_VERSION     1
#define BLE_UTIL_WRONG_IMAGE_SIZE        2
#define BLE_UTIL_ACI_ERROR               3
#define BLE_UTIL_CRC_ERROR               4
#define BLE_UTIL_PARSE_ERROR             5
#define BLE_UTIL_WRONG_VERIFY            6

/* Exported functions ------------------------------------------------------- */
/**
  * @brief  Flash a new firmware using internal bootloader.
  * @param  fw_image     Pointer to the firmware image (raw binary data,
  *                      little-endian).
  * @param  fw_size      Size of the firmware image. The firmware image size shall
  *                      be multiple of 4 bytes.
  * @retval int32_t      It returns 0 if successful, or a number not equal to 0 in
  *                      case of error (ACI_ERROR, UNSUPPORTED_VERSION,
  *                      WRONG_IMAGE_SIZE, CRC_ERROR)
  */
int32_t program_device(const uint8_t *fw_image, uint32_t fw_size);


/**
  * @brief  Verify raw data from Device Configuration block.
  * @param  ifr_data Pointer to the buffer that will contain the data to verify.
  * @retval int      It returns 0 if successful, or a number not equal to 0 in
                     case of error (ACI_ERROR, BLE_UTIL_WRONG_VERIFY)
  */
uint8_t verify_dev_config(const dev_config_t *ifr_data);

/**
  * @brief  Program raw data to Device Configuration block
  * @param  ifr_image     Pointer to the buffer that will contain the data to program.
  * @retval int      It returns 0 if successful
  */
int program_dev_config(const dev_config_t *ifr_image);

/**
  * @brief  Get BlueNRG hardware and firmware version
  * @param  hw_version Pointer to the Hardware Version (e.g. CUT 3.0 = 0x30,
  *                    CUT 3.1 = 0x31).
  * @param  fw_version Pointer to the Firmware Version in the format 0xJJMN
  *                    where JJ = Major Version number, M = Minor Version
  *                    number and N = Patch Version number.
  * @retval int        It returns 0 if successful
  */
uint8_t get_blue_nrg_version(uint8_t *hw_version, uint16_t *fw_version);

#ifdef __cplusplus
}
#endif

#endif /*__BLUENRG_UTILS_H */

