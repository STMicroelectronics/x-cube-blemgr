/**
  ******************************************************************************
  * @file    link_layer.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version V1.3.0
  * @date    20-July-2023
  * @brief   Header file for BLE link layer constants.
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

#ifndef _LINK_LAYER_H
#define _LINK_LAYER_H

#include "ble_types.h"
#include <stdint.h>

/**
 * @defgroup Link_Layer Link Layer constants and types
 * @brief Constants and types related to Link Layer functions
 * @{
 */
   
/* Macros for Enable parameters in HCI commands. */   
#define HCI_DISABLE                                    0x00
#define HCI_ENABLE                                     0x01
   

/**
 * Bluetooth 48 bit address (in little-endian order).
 */
typedef uint8_t tBDAddr[6];

#define BD_ADDR_SIZE                                   0x06U

/* Address types */   
#define HCI_ADDR_PUBLIC                                0x00U
#define HCI_ADDR_RANDOM_ADDR                           0x01U
#define HCI_ADDR_STATIC_RANDOM_ADDR                    0x01U
#define HCI_ADDR_RESOLVABLE_PRIVATE_ADDR               0x02U
#define HCI_ADDR_NON_RESOLVABLE_PRIVATE_ADDR           0x03U
   
/* HCI_LE_Set_Advertising_Parameters: Advertising_Type */
#define HCI_ADV_TYPE_ADV_IND                           0x00U
#define HCI_ADV_TYPE_ADV_DIRECT_IND_HDC                0x01U
#define HCI_ADV_TYPE_ADV_SCAN_IND                      0x02U
#define HCI_ADV_TYPE_ADV_NONCONN_IND                   0x03U
#define HCI_ADV_TYPE_ADV_DIRECT_IND_LDC                0x04U

/* HCI_LE_Set_Advertising_Parameters: Advertising_Filter_Policy */
#define HCI_ADV_FILTER_NONE                            0x00U
#define HCI_ADV_FILTER_ACCEPT_LIST_SCAN                0x01U
#define HCI_ADV_FILTER_ACCEPT_LIST_CONNECT             0x02U
#define HCI_ADV_FILTER_ACCEPT_LIST_SCAN_CONNECT        0x03U
   
#define HCI_ADV_CH_37                                  0x01U
#define HCI_ADV_CH_38                                  0x02U
#define HCI_ADV_CH_39                                  0x04U
#define HCI_ADV_CH_ALL                                 0x07U

/* HCI_LE_Set_[Advertising/Scan]_Parameters: Own_Address_Type */
#define HCI_OWN_ADDR_TYPE_PUBLIC                       0x00U
#define HCI_OWN_ADDR_TYPE_RANDOM                       0x01U
#define HCI_OWN_ADDR_TYPE_RP_OR_PUBLIC                 0x02U
#define HCI_OWN_ADDR_TYPE_RP_OR_RANDOM                 0x03U

/* HCI_LE_Set_Scan_Parameters: LE_Scan_Type */
#define HCI_SCAN_TYPE_PASSIVE                          0x00U
#define HCI_SCAN_TYPE_ACTIVE                           0x01U

/* HCI_LE_Set_Scan_Parameters: Scanning_Filter_Policy */
#define HCI_SCAN_FILTER_BASIC_UNFILTERED               0x00U
#define HCI_SCAN_FILTER_BASIC_FILTERED                 0x01U
#define HCI_SCAN_FILTER_EXTENDED_UNFILTERED            0x02U
#define HCI_SCAN_FILTER_EXTENDED_FILTERED              0x03U

/* HCI_LE_Create_Connection: Initiator_Filter_Policy */
#define HCI_INIT_FILTER_ACCEPT_LIST_NONE               0x00U
#define HCI_INIT_FILTER_ACCEPT_LIST                    0x01U

/* HCI_LE_Read_PHY: TX_PHY */
#define HCI_TX_PHY_LE_1M                               0x01U
#define HCI_TX_PHY_LE_2M                               0x02U
#define HCI_TX_PHY_LE_CODED                            0x03U

/* HCI_LE_Read_PHY: RX_PHY */
#define HCI_RX_PHY_LE_1M                               0x01U
#define HCI_RX_PHY_LE_2M                               0x02U
#define HCI_RX_PHY_LE_CODED                            0x03U

/* HCI_LE_Set_PHY: ALL_PHYS */
#define HCI_ALL_PHYS_TX_NO_PREF                        0x01U
#define HCI_ALL_PHYS_RX_NO_PREF                        0x02U

/* HCI_LE_Set_PHY: TX_PHYS */
#define HCI_TX_PHYS_LE_1M_PREF                         0x01U
#define HCI_TX_PHYS_LE_2M_PREF                         0x02U
#define HCI_TX_PHYS_LE_CODED_PREF                      0x04U

/* HCI_LE_Set_PHY: RX_PHYS */
#define HCI_RX_PHYS_LE_1M_PREF                         0x01U
#define HCI_RX_PHYS_LE_2M_PREF                         0x02U
#define HCI_RX_PHYS_LE_CODED_PREF                      0x04U

/* HCI_LE_Set_Extended_Advertising_Parameters: Advertising_Event_Properties */
#define HCI_ADV_EVENT_PROP_NONE                        0x0000U
#define HCI_ADV_EVENT_PROP_CONNECTABLE                 0x0001U
#define HCI_ADV_EVENT_PROP_SCANNABLE                   0x0002U
#define HCI_ADV_EVENT_PROP_DIRECTED                    0x0004U
#define HCI_ADV_EVENT_PROP_HDC_DIRECTED                0x0008U
#define HCI_ADV_EVENT_PROP_LEGACY                      0x0010U
#define HCI_ADV_EVENT_PROP_ANONYMOUS                   0x0020U
#define HCI_ADV_EVENT_PROP_TXPOWER_INC                 0x0040U

/* HCI_LE_Set_Extended_Advertising_Parameters: Primary_Advertising_PHY and Secondary_Advertising_PHY */
#define HCI_ADV_PHY_LE_1M                      0x01U
#define HCI_ADV_PHY_LE_2M                      0x02U
#define HCI_ADV_PHY_LE_CODED                   0x03U

/* HCI_LE_Set_Extended_Advertising_Data: Operation */
#define HCI_SET_ADV_DATA_OPERATION_INTERMEDIATE        0x00U
#define HCI_SET_ADV_DATA_OPERATION_FIRST               0x01U
#define HCI_SET_ADV_DATA_OPERATION_LAST                0x02U
#define HCI_SET_ADV_DATA_OPERATION_COMPLETE            0x03U
#define HCI_SET_ADV_DATA_OPERATION_UNCHANGED           0x04U

/* HCI_LE_Advertising_Report: Event_Type */
#define HCI_ADV_EVT_TYPE_ADV_IND                       0x00U
#define HCI_ADV_EVT_TYPE_ADV_DIRECT_IND                0x01U
#define HCI_ADV_EVT_TYPE_ADV_SCAN_IND                  0x02U
#define HCI_ADV_EVT_TYPE_ADV_NONCONN_IND               0x03U
#define HCI_ADV_EVT_TYPE_SCAN_RSP                      0x04U

/* HCI_LE_Extended_Advertising_Report: Event_Type */
#define HCI_EXT_ADV_EVT_TYPE_CONNECTABLE               0x0001U
#define HCI_EXT_ADV_EVT_TYPE_SCANNABLE                 0x0002U
#define HCI_EXT_ADV_EVT_TYPE_DIRECTED                  0x0004U
#define HCI_EXT_ADV_EVT_TYPE_SCAN_RESP                 0x0008U
#define HCI_EXT_ADV_EVT_TYPE_LEGACY                    0x0010U
#define HCI_EXT_ADV_EVT_TYPE_DATA_STATUS_MASK          0x0060U
#define HCI_EXT_ADV_EVT_TYPE_DATA_STATUS_COMPLETE      0x0000U
#define HCI_EXT_ADV_EVT_TYPE_DATA_STATUS_MORE_DATA     0x0020U
#define HCI_EXT_ADV_EVT_TYPE_DATA_STATUS_TRUNCATED     0x0040U

/* HCI_LE_Set_Extended_Scan_Parameters: Scanning_PHYs */
#define HCI_SCANNING_PHYS_LE_1M                        0x01U
#define HCI_SCANNING_PHYS_LE_CODED                     0x04U

/* HCI_LE_Extended_Create_Connection: Initiating_PHYs */
#define HCI_INIT_PHYS_SCAN_CONN_LE_1M                  0x01U
#define HCI_INIT_PHYS_CONN_LE_2M                       0x02U
#define HCI_INIT_PHYS_SCAN_CONN_LE_CODED               0x04U

/* HCI_LE_Receiver_Test/HCI_LE_Transmitter_Test [v2]: PHY */
#define HCI_TEST_PHY_LE_1M                             0x01U
#define HCI_TEST_PHY_LE_2M                             0x02U

/* HCI_LE_Connection_Complete/HCI_LE_Enhanced_Connection_Complete: Role */
#define HCI_ROLE_CENTRAL                               0x00U
#define HCI_ROLE_PERIPHERAL                            0x01U

/* HCI_LE_Set_Privacy_Mode: Privacy_Mode */
#define HCI_PRIV_MODE_NETWORK                          0x00U
#define HCI_PRIV_MODE_DEVICE                           0x01U

/* HCI_LE_Periodic_Advertising_Report: Data_Status */
#define HCI_PADV_DATA_STATUS_COMPLETE                  0x00U
#define HCI_PADV_DATA_STATUS_MORE_DATA                 0x01U
#define HCI_PADV_DATA_STATUS_TRUNCATED                 0x02U
#define HCI_PADV_DATA_STATUS_FAILED                    0xFFU


/**
 * @name Duplicate filtering
 * @{
 */
#define DUPLICATE_FILTER_DISABLED                   0
#define DUPLICATE_FILTER_ENABLED                    1
#define DUPLICATE_FILTER_ENABLED_FOR_SCAN_PERIOD    2
/**
 * @}
 */

/**
 * @name Bitmasks for Link Layer PHYs
 * @{
 */
#define LE_1M_PHY_BIT       0x01
#define LE_2M_PHY_BIT       0x02
#define LE_CODED_PHY_BIT    0x04

/**
 * @}
 */
   
/**
 * @name Values for Link Layer PHYs
 * @{
 */
#define HCI_PHY_LE_1M                   0x01
#define HCI_PHY_LE_2M                   0x02
#define HCI_PHY_LE_CODED                0x03
#define HCI_PHY_LE_CODED_S8             0x03
#define HCI_PHY_LE_CODED_S2             0x04

/**
 * @}
 */

/**
 * @name Link Layer State
 * @{
 */   
#define LL_IDLE         0x00
#define LL_ADV          0x01
#define LL_CONN_SLAVE   0x02
#define LL_SCAN         0x03
#define LL_CONN_REQ     0x04
#define LL_CONN_MASTER  0x05
#define LL_TX_TEST      0x06
#define LL_RX_TEST      0x07
/**
 * @}
 */

/**
 * @name CTE Type
 * @{
 */   
#define CTE_AOA         0x00
#define CTE_AOD_1us     0x01
#define CTE_AOD_2us     0x02
/**
 * @}
 */

/**
 * @name CTE Type bitmask
 * @{
 */   
#define CTE_AOA_BIT         0x01
#define CTE_AOD_1us_BIT     0x02
#define CTE_AOD_2us_BIT     0x04
/**
 * @}
 */
   
/**
 * @name CTE Slot Duration
 * @{
 */   
#define CTE_SLOT_1us        0x01
#define CTE_SLOT_2us        0x02
/**
 * @}
 */

/**
 * @name Reason for hci_le_transmit_power_reporting_event()
 * @{
 */
#define LOCAL_TX_POWER_CHANGE               0x00
#define REMOTE_TX_POWER_CHANGE              0x01
#define READ_REMOTE_TX_POWER_COMPLETE       0x02
/**
 * @}
 */

/**
 * @name Transmit_Power_Level value
 * @{
 */
#define POWER_NOT_MANAGED                   0x7E
#define POWER_NA                            0x7F
/**
 * @}
 */

/**
 * @name Transmit_Power_Level_Flag values
 * @{
 */
#define MIN_TX_POWER_BIT                    0x01
#define MAX_TX_POWER_BIT                    0x02
/**
 * @}
 */
   
/**
 * @name LE Event Mask
 * @see hci_le_set_event_mask()
 * @{
 */
#define HCI_LE_EVT_MASK_BYTE0_CONNECTION_COMPLETE                                         (0x01U)
#define HCI_LE_EVT_MASK_BYTE0_ADVERTISING_REPORT                                          (0x02U)
#define HCI_LE_EVT_MASK_BYTE0_CONNECTION_UPDATE_COMPLETE                                  (0x04U)
#define HCI_LE_EVT_MASK_BYTE0_READ_REMOTE_FEATURES_COMPLETE                               (0x08U)
#define HCI_LE_EVT_MASK_BYTE0_LTK_REQUEST                                                 (0x10U)
#define HCI_LE_EVT_MASK_BYTE0_REMOTE_CONNECTION_PARAMETER_REQUEST                         (0x20U)
#define HCI_LE_EVT_MASK_BYTE0_DATA_LEN_CHANGE                                             (0x40U)
#define HCI_LE_EVT_MASK_BYTE0_READ_LOCAL_P256_COMPLETE                                    (0x80U)
#define HCI_LE_EVT_MASK_BYTE1_GENERATE_DHKEY_COMPLETE                                     (0x01U)
#define HCI_LE_EVT_MASK_BYTE1_ENHANCED_CONNECTION_COMPLETE                                (0x02U)
#define HCI_LE_EVT_MASK_BYTE1_DIRECTED_ADVERTISING_REPORT                                 (0x04U)
#define HCI_LE_EVT_MASK_BYTE1_PHY_UPDATE_COMPLETE                                         (0x08U)
#define HCI_LE_EVT_MASK_BYTE1_EXTENDED_ADVERTISING_REPORT                                 (0x10U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_SYNC_ESTABLISHED                       (0x20U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_REPORT                                 (0x40U)
#define HCI_LE_EVT_MASK_BYTE1_PERIODIC_ADVERTISING_SYNC_LOST                              (0x80U)
#define HCI_LE_EVT_MASK_BYTE2_SCAN_TIMEOUT                                                (0x01U)
#define HCI_LE_EVT_MASK_BYTE2_ADVERTISING_SET_TERMINATED                                  (0x02U)
#define HCI_LE_EVT_MASK_BYTE2_SCAN_REQUEST_RECEIVED                                       (0x04U)
#define HCI_LE_EVT_MASK_BYTE2_CHANNEL_SELECTION_ALGORITHM                                 (0x08U)
#define HCI_LE_EVT_MASK_BYTE2_CONNECTIONLESS_IQ_REPORT                                    (0x10U)
#define HCI_LE_EVT_MASK_BYTE2_CONNECTION_IQ_REPORT                                        (0x20U)
#define HCI_LE_EVT_MASK_BYTE2_CTE_REQUEST_FAILED                                          (0x40U)
#define HCI_LE_EVT_MASK_BYTE2_PERIODIC_ADVERTISING_SYNC_TRANSFER                          (0x80U)
#define HCI_LE_EVT_MASK_BYTE3_CIS_ESTABLISHED                                             (0x01U)
#define HCI_LE_EVT_MASK_BYTE3_CIS_REQUEST                                                 (0x02U)
#define HCI_LE_EVT_MASK_BYTE3_CREATE_BIG_COMPLETE                                         (0x04U)
#define HCI_LE_EVT_MASK_BYTE3_TERMINATE_BIG_COMPLETE                                      (0x08U)
#define HCI_LE_EVT_MASK_BYTE3_BIG_SYNC_ESTABLISHED                                        (0x10U)
#define HCI_LE_EVT_MASK_BYTE3_BIG_SYNC_LOST                                               (0x20U)
#define HCI_LE_EVT_MASK_BYTE3_REQUEST_PEER_SCA_COMPLETE                                   (0x40U)
#define HCI_LE_EVT_MASK_BYTE3_PATH_LOSS_THRESHOLD                                         (0x80U)
#define HCI_LE_EVT_MASK_BYTE4_TRANSMIT_POWER_REPORTING                                    (0x01U)
#define HCI_LE_EVT_MASK_BYTE4_BIG_INFO_ADVERTISING_REPORT                                 (0x02U)
#define HCI_LE_EVT_MASK_BYTE4_SUBRATE_CHANGE                                              (0x04U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_SYNC_ESTABLISHED_V2                    (0x08U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_REPORT_V2                              (0x10U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_SYNC_TRANSFER_V2                       (0x20U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_SUBEVENT_DATA_REQ                      (0x40U)
#define HCI_LE_EVT_MASK_BYTE4_PERIODIC_ADVERTISING_RESPONSE_REPORT                        (0x80U)
#define HCI_LE_EVT_MASK_BYTE5_ENHANCED_CONNECTION_COMPLETE_V2                             (0x01U)

/**
 * @}
 */
 
#endif /* _LINK_LAYER_H */
