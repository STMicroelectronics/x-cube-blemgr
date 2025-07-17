/**
  ******************************************************************************
  * @file    stm32wb05n_driver_hal.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version V1.3.0
  * @date    20-July-2023
  * @brief   Header file with HAL define for STM32WB05N
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

#ifndef __STM32WB05N_HAL_H__
#define __STM32WB05N_HAL_H__

/**
 *@addtogroup HAL_LL HAL/LL
 *@{
 */
/**
 *@addtogroup HAL_constants HAL/LL Constants
 *@brief Constants for Hardware abstraction Layer and Link Layer.
 *@{
 */

/**
 * @name Configuration values.
 * See @ref aci_hal_write_config_data() and @ref aci_hal_read_config_data().
 * @{
 */
#define CONFIG_DATA_PUBADDR_OFFSET                  (0x00) /**< Bluetooth public address */
#define CONFIG_DATA_ER_OFFSET                       (0x08) /**< Encryption root key used to derive LTK and CSRK */
#define CONFIG_DATA_IR_OFFSET                       (0x18) /**< Identity root key used to derive LTK and CSRK */
#define CONFIG_DATA_LL_WITHOUT_HOST                 (0x2C) /**< Switch on/off Link Layer only mode. Set to 1 to disable Host.
                           It can be written only if aci_hal_write_config_data() is the first command
                           after reset. */
#define CONFIG_DATA_STATIC_RANDOM_ADDRESS           (0x2E) /**< To set the static random address used by the stack, instead of the one stored in NVM. */
#define CONFIG_DATA_SCAN_CH_MAP                     (0x2F) /**< To set the channel map for scanning. */
#define CONFIG_DATA_STORED_STATIC_RANDOM_ADDRESS    (0x80) /**< The static random address stored in NVM. */
#define CONFIG_DATA_DEBUG_KEY                       (0xD0) /**< Use debug key for secure connections. */
#define CONFIG_DATA_DLE                             (0xD1) /**< To set the maximum allowed parameter values for Data Length Extension */
/**
 * @}
 */

/**
 * @name Length for configuration values.
 * See @ref aci_hal_write_config_data() and @ref aci_hal_read_config_data().
 * @{
 */
#define CONFIG_DATA_PUBADDR_LEN                 (6)
#define CONFIG_DATA_ER_LEN                      (16)
#define CONFIG_DATA_IR_LEN                      (16)
#define CONFIG_DATA_LL_WITHOUT_HOST_LEN         (1)
#define CONFIG_DATA_STATIC_RANDOM_ADDRESS_LEN   (6)
#define CONFIG_DATA_SCAN_CH_MAP_LEN             (1)
#define CONFIG_DATA_DEBUG_KEY_LEN               (1)
#define CONFIG_DATA_DLE_LEN                     (1)
/**
 * @}
 */


/**
 * @name Types for fw error event
 * @brief See aci_hal_fw_error_event().
 * @{
 */

#define HAL_FW_L2CAP_RECOMBINATION_ERROR            0x01 /**< L2CAP layer failed recombining a PDU */
#define HAL_FW_GATT_UNEXPECTED_RESPONSE_ERROR       0x02 /**< GATT layer received an unexpteced response. Peer probably violated the ATT protocol. */
#define HAL_FW_GATT_SEQUENTIAL_PROTOCOL_ERROR       0x03 /**< GATT layer received an unexpteced request. Peer probably violated the sequentiality of ATT protocol. */
#define HAL_FW_BONDING_DB_FULL_GATTSERVICE_ERROR    0x04 /**< No space to store info GATT database info in NVM. Database needs to be cleaned up (remove invalidated records) or some bonding entries need to be removed. */
#define HAL_FW_BONDING_DB_FULL_PAIRING_ERROR        0x05 /**< No space to store bonding info in NVM. Database needs to be cleaned up (remove invalidated records) or some bonding entries need to be removed. */
#define HAL_FW_SCHEDULER_OVERRUN_ERROR              0x06 /**< Link Layer scheduler failed to reschedule slots for too many times. This may indicate an unrecoverable situation. A system reset is recommended. */ 
#define HAL_FW_MEMBUF_NOT_AVAILABLE                 0x07 /**< Out of memory resources for isochronous channels. */
#define HAL_FW_CTE_TIMER_PROGRAM_ERROR              0x08 /**< Error in programming timer for CTE reception functionality. */
#define HAL_FW_MBM_RESOURCE_MISS                    0x09 /**< Requested resources are not available. */

/**
 * @}
 */
 
 /**
 * @name Types for aci_hal_pawr_data_free_event()
 * @brief See aci_hal_pawr_data_free_event().
 * @{
 */

#define HAL_PAWR_DATA_TYPE_SUBEVENT                 0x00 /**< PAwR subevevent data */
#define HAL_PAWR_DATA_TYPE_RESPONSE                 0x01 /**< PAwR response data */

/**
 * @}
 */

/**
 * @}
 */
/**
 * @}
 */

#endif /* __STM32WB05N_HAL_ACI_H__ */
