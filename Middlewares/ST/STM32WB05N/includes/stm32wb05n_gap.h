/**
  ******************************************************************************
  * @file    stm32wb05n_gap.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version V1.3.0
  * @date    20-July-2023
  * @brief   Header file for BLE GAP layer constants
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

#ifndef __GAP_H__
#define __GAP_H__

#include <link_layer.h>

/**
 *@addtogroup GAP GAP
 *@brief Generic Access Profile
 *@{
 */

/**
 *@addtogroup GAP_constants GAP Constants
 *@brief Constants for GAP layer
 *@{
 */

/**
 * @name Characteristic value lengths
 * @{
 */
#define APPEARANCE_CHAR_LEN                         (2)
#define PERIPHERAL_PREFERRED_CONN_PARAMS_CHAR_LEN   (8)
#define CENTRAL_ADDRESS_RESOLUTION_CHAR_LEN         (1)
/**
 * @}
 */

/**
 * @name AD Types
 * @brief AD types for adv data and scan response data
 * @{
 */

#define AD_TYPE_FLAGS                           (0x01)

#define AD_TYPE_16_BIT_SERV_UUID                (0x02)
#define AD_TYPE_16_BIT_SERV_UUID_CMPLT_LIST     (0x03)
#define AD_TYPE_32_BIT_SERV_UUID                (0x04)
#define AD_TYPE_32_BIT_SERV_UUID_CMPLT_LIST     (0x05)
#define AD_TYPE_128_BIT_SERV_UUID               (0x06)
#define AD_TYPE_128_BIT_SERV_UUID_CMPLT_LIST    (0x07)

#define AD_TYPE_SHORTENED_LOCAL_NAME            (0x08)
#define AD_TYPE_COMPLETE_LOCAL_NAME             (0x09)

/** TX power level AD type*/
#define AD_TYPE_TX_POWER_LEVEL                  (0x0A)

/** Class of device */
#define AD_TYPE_CLASS_OF_DEVICE                 (0x0D)

/** Security manager TK value AD type */
#define AD_TYPE_SEC_MGR_TK_VALUE                (0x10)

/** Security manager OOB flags */
#define AD_TYPE_SEC_MGR_OOB_FLAGS               (0x11)

/** Slave connection interval AD type */
#define AD_TYPE_SLAVE_CONN_INTERVAL             (0x12)

#define AD_TYPE_SERV_SOLICIT_16_BIT_UUID_LIST   (0x14)
#define AD_TYPE_SERV_SOLICIT_32_BIT_UUID_LIST   (0x1F)
#define AD_TYPE_SERV_SOLICIT_128_BIT_UUID_LIST  (0x15)

#define AD_TYPE_16_BIT_UUID_SERVICE_DATA        (0x16)
#define AD_TYPE_32_BIT_UUID_SERVICE_DATA        (0x20)
#define AD_TYPE_128_BIT_UUID_SERVICE_DATA       (0x21)

/** Manufaturer specific data AD type */
#define AD_TYPE_MANUFACTURER_SPECIFIC_DATA      (0xFF)

/**
 * @}
 */

/**
 * @name Flags AD Type bits
 * @brief Bits for Flags AD Type
 * @{
 */
#define FLAG_BIT_LE_LIMITED_DISCOVERABLE_MODE   (0x01)
#define FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE   (0x02)
#define FLAG_BIT_BR_EDR_NOT_SUPPORTED           (0x04)
#define FLAG_BIT_LE_BR_EDR_CONTROLLER           (0x08)
#define FLAG_BIT_LE_BR_EDR_HOST                 (0x10)
/**
 * @}
 */


/**
 * @name GAP modes
 * @{
 */
#define GAP_MODE_NON_DISCOVERABLE             0
#define GAP_MODE_LIMITED_DISCOVERABLE         1
#define GAP_MODE_GENERAL_DISCOVERABLE         2
#define GAP_MODE_BROADCAST                    3
/**
 * @}
 */

/**
 * @name Privacy type
 * @{
 */
#define PRIVACY_DISABLED                        (0x00)
#define PRIVACY_HOST_ENABLED                    (0x01)
#define PRIVACY_CONTROLLER_ENABLED              (0x02)
/**
 * @}
 */
   
/**
 * @name Operation
 * Values for Operation parameter (see aci_gap_set_advertising_data()).
 * @{
 */   
#define ADV_COMPLETE_DATA             (0x03)
#define ADV_UNCHANGED_DATA            (0x04)   
/**
 * @}
 */

/**
 * @name Recommended advertising intervals
 * Intervals in terms of 625 micro seconds
 * @{
 */
#define GAP_ADV_INT_MIN_USER_INITIATED_CONN          (48)   /* 30 ms  */
#define GAP_ADV_INT_MAX_USER_INITIATED_CONN          (96)   /* 60 ms  */
#define GAP_ADV_INT_MIN_USER_INITIATED_NONCONN       (160)  /* 100 ms */
#define GAP_ADV_INT_MAX_USER_INITIATED_NONCONN       (240)  /* 150 ms */
#define GAP_ADV_INT_MIN_BACKGROUND                   (1600) /* 1 s    */
#define GAP_ADV_INT_MAX_BACKGROUND                   (1920) /* 1.2 s  */   
/**
 * @}
 */

/**
 * @anchor gap_roles
 * @name GAP Roles
 * @{
*/
#define GAP_PERIPHERAL_ROLE                     (0x01)
#define GAP_BROADCASTER_ROLE                    (0x02)
#define GAP_CENTRAL_ROLE                        (0x04)
#define GAP_OBSERVER_ROLE                       (0x08)
/**
 * @}
 */

/**
 * @anchor gap_procedure_codes
 * @name GAP procedure codes
 * Procedure codes for aci_gap_start_procedure()
 * and aci_gap_terminate_proc() commands.
 * @{
 */    
#define GAP_LIMITED_DISCOVERY_PROC                  (0x00)
#define GAP_GENERAL_DISCOVERY_PROC                  (0x01)
#define GAP_AUTO_CONNECTION_ESTABLISHMENT_PROC      (0x02)
#define GAP_GENERAL_CONNECTION_ESTABLISHMENT_PROC   (0x03)
#define GAP_SELECTIVE_CONNECTION_ESTABLISHMENT_PROC (0x04)
#define GAP_OBSERVATION_PROC                        (0x05)
#define GAP_DIRECT_CONNECTION_ESTABLISHMENT_PROC    (0x06)
#define GAP_NAME_DISCOVERY_PROC                     (0x07)

/**
 * @}
 */

/**
 * @anchor gap_appearance_values
 * @name GAP Appearance values
 * Values for GAP Appearance characteristic.
 * @{
 */ 
#define GAP_APPEARANCE_UNKNOWN                                 0x0000
#define GAP_APPEARANCE_GENERIC_PHONE                           0x0040
#define GAP_APPEARANCE_GENERIC_COMPUTER                        0x0080
#define GAP_APPEARANCE_GENERIC_WATCH                           0x00C0
#define GAP_APPEARANCE_WATCH_SPORT_WATCH                       0x00C1
#define GAP_APPEARANCE_GENERIC_CLOCK                           0x0100
#define GAP_APPEARANCE_GENERIC_DISPLAY                         0x0140
#define GAP_APPEARANCE_GENERIC_REMOTE_CONTROL                  0x0180
#define GAP_APPEARANCE_GENERIC_EYE_GLASSES                     0x01C0
#define GAP_APPEARANCE_GENERIC_TAG                             0x0200
#define GAP_APPEARANCE_GENERIC_KEYRING                         0x0240
#define GAP_APPEARANCE_GENERIC_MEDIA_PLAYER                    0x0280
#define GAP_APPEARANCE_GENERIC_BARCODE_SCANNER                 0x02C0
#define GAP_APPEARANCE_GENERIC_THERMOMETER                     0x0300
#define GAP_APPEARANCE_THERMOMETER_EAR                         0x0301
#define GAP_APPEARANCE_GENERIC_HEART_RATE_SENSOR               0x0340
#define GAP_APPEARANCE_HEART_RATE_SENSOR_HEART_RATE_BELT       0x0341
#define GAP_APPEARANCE_GENERIC_BLOOD_PRESSURE                  0x0380
#define GAP_APPEARANCE_BLOOD_PRESSURE_ARM                      0x0381
#define GAP_APPEARANCE_BLOOD_PRESSURE_WRIST                    0x0382
#define GAP_APPEARANCE_HUMAN_INTERFACE_DEVICE                  0x03C0
#define GAP_APPEARANCE_KEYBOARD                                0x03C1
#define GAP_APPEARANCE_MOUSE                                   0x03C2
#define GAP_APPEARANCE_JOYSTICK                                0x03C3
#define GAP_APPEARANCE_GAMEPAD                                 0x03C4
#define GAP_APPEARANCE_DIGITIZER_TABLET                        0x03C5
#define GAP_APPEARANCE_CARD_READER                             0x03C6
#define GAP_APPEARANCE_DIGITAL_PEN                             0x03C7
#define GAP_APPEARANCE_BARCODE_SCANNER                         0x03C8
#define GAP_APPEARANCE_GENERIC_GLUCOSE_METER                   0x0400
#define GAP_APPEARANCE_GENERIC_RUNNING_WALKING_SENSOR          0x0440
#define GAP_APPEARANCE_RUNNING_WALKING_IN_SHOE                 0x0441
#define GAP_APPEARANCE_RUNNING_WALKING_ON_SHOE                 0x0442
#define GAP_APPEARANCE_RUNNING_WALKING_ON_HIP                  0x0443
#define GAP_APPEARANCE_GENERIC_CYCLING                         0x0480
#define GAP_APPEARANCE_CYCLING_CYCLING_COMPUTER                0x0481
#define GAP_APPEARANCE_CYCLING_SPEED_SENSOR                    0x0482
#define GAP_APPEARANCE_CYCLING_CADENCE_SENSOR                  0x0483
#define GAP_APPEARANCE_CYCLING_POWER_SENSOR                    0x0484
#define GAP_APPEARANCE_CYCLING_SPEED_AND_CADENCE_SENSOR        0x0485
#define GAP_APPEARANCE_GENERIC_PULSE_OXYMETER                  0x0C40
#define GAP_APPEARANCE_FINGERTIP                               0x0C41
#define GAP_APPEARANCE_WRIST_WORN                              0x0C42
#define GAP_APPEARANCE_GENERIC_WEIGHT_SCALE                    0x0C80
#define GAP_APPEARANCE_GENERIC_OUTDOOR_SPORT_ACTIVITY          0x1440
#define GAP_APPEARANCE_LOCATION_DISPLAY_DEVICE                 0x1441
#define GAP_APPEARANCE_LOCATION_AND_NAVIGATION_DISPLAY_DEVICE  0x1442
#define GAP_APPEARANCE_LOCATION_POD                            0x1443
#define GAP_APPEARANCE_LOCATION_AND_NAVIGATION_POD             0x1444
#define GAP_APPEARANCE_GENERIC_ENVIRONMENTAL_SENSOR            0x1640

/**
 * @}
 */

/**
 * @}
 */

#endif /* __GAP_H__ */
