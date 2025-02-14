/**
  ******************************************************************************
  * @file    ble_status.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.0.0
  * @date    25-September-2024
  * @brief   Header file which contains definition of Bluetooth status and error codes.
  * @note    Error Codes are defined according to Bluetooth Specifications
  *              Vol.2 Part D.
  *           - HCI/Controller standard codes range is [0x00 : 0x3F].
  *             Their name is prefixed by "BLE_ERROR_"
  *           - Host specific (and proprietary) error codes range is [0x80 : 0xFF].
  *             Their name is prefixed by "BLE_STATUS_" and they're grouped by Layer
  *           - BLE_STATUS_SUCCESS value is 0x00 and is the unique error code
  *             used by both Controller and Host layers.
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

#ifndef __BLE_STATUS_H__
#define __BLE_STATUS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* @brief Standard Error Codes as specified by the Bluetooth Specifications
 * Vol.2, Part D ("Error Codes").
 * According to the spec the error codes range is from 0x00 to 0x3F.
 */
#define BLE_STATUS_SUCCESS                          ((ble_status_t)(0x00))

#define BLE_ERROR_UNKNOWN_HCI_COMMAND               ((ble_status_t)(0x01))
#define BLE_ERROR_UNKNOWN_CONNECTION_ID             ((ble_status_t)(0x02))

#define BLE_ERROR_HARDWARE_FAILURE                  ((ble_status_t)(0x03))

#define BLE_ERROR_AUTHENTICATION_FAILURE            ((ble_status_t)(0x05))
#define BLE_ERROR_KEY_MISSING                       ((ble_status_t)(0x06))
#define BLE_ERROR_MEMORY_CAPACITY_EXCEEDED          ((ble_status_t)(0x07))
#define BLE_ERROR_CONNECTION_TIMEOUT                ((ble_status_t)(0x08))

#define BLE_ERROR_CONNECTION_ALREADY_EXISTS         ((ble_status_t)(0x0B))
#define BLE_ERROR_COMMAND_DISALLOWED                ((ble_status_t)(0x0C))

#define BLE_ERROR_UNSUPPORTED_FEATURE               ((ble_status_t)(0x11))

#define BLE_ERROR_INVALID_HCI_CMD_PARAMS            ((ble_status_t)(0x12))

#define BLE_ERROR_TERMINATED_REMOTE_USER            ((ble_status_t)(0x13))

#define BLE_ERROR_TERMINATED_LOCAL_HOST             ((ble_status_t)(0x16))

#define BLE_ERROR_UNSUPP_RMT_FEATURE                ((ble_status_t)(0x1A))

#define BLE_ERROR_INVALID_LMP_LL_PARAMS             ((ble_status_t)(0x1E))

#define BLE_ERROR_UNSPECIFIED                       ((ble_status_t)(0x1F))

#define BLE_ERROR_UNSUPP_LMP_LL_PARAM_VALUE         ((ble_status_t)(0x20))

#define BLE_ERROR_PROCEDURE_TIMEOUT                 ((ble_status_t)(0x22))

#define BLE_ERROR_LL_PROCEDURE_COLLISION            ((ble_status_t)(0x23))

#define BLE_ERROR_LMP_PDU_NOT_ALLOWED               ((ble_status_t)(0x24))

#define BLE_ERROR_INSTANT_PASSED                    ((ble_status_t)(0x28))

#define BLE_ERROR_DIFFERENT_TRANSACTION_COLLISION   ((ble_status_t)(0x2A))

#define BLE_ERROR_PARAMETER_OUT_OF_RANGE            ((ble_status_t)(0x30))

#define BLE_ERROR_HOST_BUSY_PAIRING                 ((ble_status_t)(0x38))

#define BLE_ERROR_CONTROLLER_BUSY                   ((ble_status_t)(0x3A))

#define BLE_ERROR_DIRECTED_ADVERTISING_TIMEOUT      ((ble_status_t)(0x3C))

#define BLE_ERROR_CONNECTION_END_WITH_MIC_FAILURE   ((ble_status_t)(0x3D))

#define BLE_ERROR_CONNECTION_FAILED_TO_ESTABLISH    ((ble_status_t)(0x3E))

#define BLE_ERROR_COARSE_CLOCK_ADJ_REJECTED         ((ble_status_t)(0x40))

#define BLE_ERROR_TYPE0_SUBMAP_NOT_DEFINED          ((ble_status_t)(0x41))

#define BLE_ERROR_UNKNOWN_ADVERTISING_IDENTIFIER    ((ble_status_t)(0x42))

#define BLE_ERROR_LIMIT_REACHED                     ((ble_status_t)(0x43))

#define BLE_ERROR_OPERATION_CANCELLED_BY_HOST       ((ble_status_t)(0x44))

#define BLE_ERROR_PACKET_TOO_LONG                   ((ble_status_t)(0x45))




/**
  * @name Generic/System error codes
  * @brief The error codes as reported by the different Protocol layers.
  *        They start with 0x80
  * @{
  */

/**
  * @brief The Connection Identifier does not exist.
  * Temporary remapped to corresponding Controller Error.
  */
#define BLE_STATUS_UNKNOWN_CONNECTION_ID    ((ble_status_t)(0x80))

/**
  * @brief The Host failed while performing the requested operation.
  */
#define BLE_STATUS_FAILED                   ((ble_status_t)(0x81))

/**
  * @brief Invalid parameters passed at Host layer.
  */
#define BLE_STATUS_INVALID_PARAMS           ((ble_status_t)(0x82))

/**
  * @brief The Host is already processing another request received in advance.
  */
#define BLE_STATUS_BUSY                     ((ble_status_t)(0x83))

/**
  * @brief The operation requested cannot be completed immediately by the Host
  * (usually because of lack of resources).
  * The operation is generally put on hold by the caller and it's usually
  * retried on later time.
  */
#define BLE_STATUS_PENDING                  ((ble_status_t)(0x84))

/**
  * @brief The requested operation cannot be performed by the Host in the current status.
  */
#define BLE_STATUS_NOT_ALLOWED              ((ble_status_t)(0x85))

/**
  * @brief The requested operation violates the logic of the called layer/function or
  * the format of the data to be processed during the operation.
  */
#define BLE_STATUS_ERROR                    ((ble_status_t)(0x86))

/**
  * @brief The requested operation failed because of lack of memory.
  * Out of memory shall be returned for situations where memory will never
  * become available again
  */
#define BLE_STATUS_OUT_OF_MEMORY            ((ble_status_t)(0x87))

/**
  * @brief The requested operation failed for a temporary lack of resources
  * (e.g. packet pool or timers), but it may be retried later when resources may
  * become available (packets or timers may have been released by other consumers).
  */
#define BLE_STATUS_INSUFFICIENT_RESOURCES   ((ble_status_t)(0x88))

/**
  * @brief A NULL pointer was passed as function parameter
  */
#define BLE_STATUS_NULL_PARAM               ((ble_status_t)(0x89))

/**
  *@}
  */


/**
  * @name L2CAP error codes, start with 0xA0
  *  @brief Error codes returned by the L2CAP, start at 0xA0
  * @{
  */

/**
  * @brief An invalid L2CAP CID/channel has been selected to send data over.
  */
#define BLE_STATUS_INVALID_CID              ((ble_status_t)(0xA0))

/**
  *@}
  */


/**
  * @name  Security Manager error codes
  * @brief Error codes returned by the Security Manager Protocol (SMP), start at
  *        0xB0
  * @{
  */

/**
  * @brief The remote device in in the Blacklist and the pairing operation it requested
  * cannot be performed.
  */
#define BLE_STATUS_DEV_IN_BLACKLIST         ((ble_status_t)(0xB0))

/**
  * @brief CSRK not found during validation of an incoming signed packet
  */
#define BLE_STATUS_CSRK_NOT_FOUND           ((ble_status_t)(0xB1))

/**
  * @brief Currently not used!
  */
#define BLE_STATUS_IRK_NOT_FOUND            ((ble_status_t)(0xB2))

/**
  * @brief A search for a specific remote device was unsuccessful because no entry exists
  * either into Security/GATT Database (flash-based) or in volatile database.
  */
#define BLE_STATUS_DEV_NOT_FOUND            ((ble_status_t)(0xB3))

/**
  * @brief The security database is full and no more records can be added.
  */
#define BLE_STATUS_SEC_DB_FULL              ((ble_status_t)(0xB4))

/**
  * @brief The remote device is not bonded, and no operations related to bonded devices
  * may be performed (e.g. writing Gatt Client data).
  */
#define BLE_STATUS_DEV_NOT_BONDED           ((ble_status_t)(0xB5))

/**
  * @brief The encryption key size used for encrypting the link is insufficient\n
  */
#define BLE_INSUFFICIENT_ENC_KEYSIZE        ((ble_status_t)(0xB6))

/**
  *@}
  */


/**
  * @name Gatt layer Error Codes
  * @brief Error codes returned by the Gatt layer, start at 0xC0
  * @{
  */

/**
  * @brief Notification/Indication can't be sent to the requested remote device because
  * it doesn't satisfy the needed security permission.
  */
#define BLE_STATUS_SEC_PERMISSION_ERROR     ((ble_status_t)(0xC0))

/**
  *@}
  */


/**
  * @name GAP layer Error Codes
  * @brief Error codes returned by the GAP layer. start at 0xD0
  * @{
  */

/**
  *  @brief The address of the device could not be resolved using the IRK stored
  */
#define BLE_STATUS_ADDRESS_NOT_RESOLVED          ((ble_status_t)(0xD0))

/**
  *  @brief The configuration set by the aci_gap_set_scan_configuration command
  *         is not coherent with the GAP procedure that is requested to be started
  */
#define BLE_STATUS_INVALID_SCAN_CONFIGURATION    ((ble_status_t)(0xD1))

/**
  *  @brief The configuration set by the aci_gap_set_connect_configuration command
  *         is not coherent with the GAP procedure that is requested to be started
  */
#define BLE_STATUS_INVALID_CONNECT_CONFIGURATION ((ble_status_t)(0xD2))

/**
  *  @brief The configuration set by the aci_gap_set_advertising_configuration command
  *         is not valid
  */
#define BLE_STATUS_INVALID_ADV_CONFIGURATION     ((ble_status_t)(0xD3))

/**
  *  @brief The discoverability flags in the advertising data are not coherent
  *         with the discoverability mode set in the advertising configuration
  */
#define BLE_STATUS_INVALID_ADV_FLAGS             ((ble_status_t)(0xD4))
/**
  *@}
  */


/**
  * @name flash error codes
  * @brief Flash sector read write error codes, start at 0xF0
  *        and are currently remapped from 0xFA to 0xFC
  * @{
  */
#define NVM_READ_FAILED                   ((ble_status_t)(0xF0))
#define NVM_WRITE_FAILED                  ((ble_status_t)(0xF1))
#define NVM_ERASE_FAILED                  ((ble_status_t)(0xF2))

/**
  * @name Profiles Library Error Codes
  * @{
  */
#define BLE_STATUS_TIMEOUT                          (0xFF)
#define BLE_STATUS_PROFILE_ALREADY_INITIALIZED      (0xF0)

/**
  *@}
  */

#ifdef __cplusplus
}
#endif

#endif /* __BLE_STATUS_H__ */
