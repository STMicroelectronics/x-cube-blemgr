/**
  ******************************************************************************
  * @file    bluenrg_lp_driver_hal.h
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @version 2.0.0
  * @date    25-September-2024
  * @brief   Header file with HAL define for BlueNRG-LP
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

#ifndef __BLUENRG_HAL_H__
#define __BLUENRG_HAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @defgroup Config_vals Offsets and lengths for configuration values.
  * @brief Offsets and lengths for configuration values.
  *      See aci_hal_write_config_data().
  * @{
  */

/**
  * @name Configuration values.
  * See @ref aci_hal_write_config_data().
  * @{
  */
#define CONFIG_DATA_PUBADDR_OFFSET          (0x00) /**< Bluetooth public address */
#define CONFIG_DATA_DIV_OFFSET              (0x06) /**< DIV used to derive CSRK */
#define CONFIG_DATA_ER_OFFSET               (0x08) /**< Encryption root key used to derive LTK and CSRK */
#define CONFIG_DATA_IR_OFFSET               (0x18) /**< Identity root key used to derive LTK and CSRK */
#define CONFIG_DATA_LL_WITHOUT_HOST         (0x2C) /**< Switch on/off Link Layer only mode. Set to 1 to disable Host.
                           It can be written only if aci_hal_write_config_data() is the first command
                           after reset. */

/**
  * Select the BlueNRG roles and mode configurations.\n
  * @li Mode 1: slave or master, 1 connection, RAM1 only (small GATT DB)
  * @li Mode 2: slave or master, 1 connection, RAM1 and RAM2 (large GATT DB)
  * @li Mode 3: master only, 8 connections, RAM1 and RAM2.
  */
#define CONFIG_DATA_ROLE          (0x2D)
/**
  * @}
  */

/**
  * @name Length for configuration values.
  * See @ref aci_hal_write_config_data().
  * @{
  */
#define CONFIG_DATA_PUBADDR_LEN             (6)
#define CONFIG_DATA_DIV_LEN                 (2)
#define CONFIG_DATA_ER_LEN                  (16)
#define CONFIG_DATA_IR_LEN                  (16)
#define CONFIG_DATA_LL_WITHOUT_HOST_LEN     (1)
#define CONFIG_DATA_ROLE_LEN                (1)
/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __BLUENRG_HAL_ACI_H__ */
