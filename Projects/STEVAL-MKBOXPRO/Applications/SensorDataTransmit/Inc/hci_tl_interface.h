/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hci_tl_interface.h
  * @author  SRA Application Team
  * @brief   Header file for hci_tl_interface.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HCI_TL_INTERFACE_H
#define HCI_TL_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @addtogroup LOW_LEVEL_INTERFACE LOW_LEVEL_INTERFACE
  * @{
  */

/**
  * @defgroup LL_HCI_TL_INTERFACE HCI_TL_INTERFACE
  * @{
  */

/**
  * @defgroup LL_HCI_TL_INTERFACE_TEMPLATE TEMPLATE
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "steval_mkboxpro_bus.h"

/* Exported Defines ----------------------------------------------------------*/
#define HCI_TL_SPI_EXTI_PORT  GPIOB
#define HCI_TL_SPI_EXTI_PIN   GPIO_PIN_11
#define HCI_TL_SPI_EXTI_IRQn  EXTI11_IRQn

#define HCI_TL_SPI_IRQ_PORT   GPIOB
#define HCI_TL_SPI_IRQ_PIN    GPIO_PIN_11

#define BUS_EXTI_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE();

#define HCI_TL_SPI_CS_PORT    GPIOA
#define HCI_TL_SPI_CS_PIN     GPIO_PIN_2

#define BUS_CS_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE();

#define HCI_TL_RST_PORT       GPIOD
#define HCI_TL_RST_PIN        GPIO_PIN_4

#define BUS_RST_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE();

#define HCI_TL_SPI_MOSI_PORT  BUS_SPI1_MOSI_GPIO_PORT
#define HCI_TL_SPI_MOSI_PIN   BUS_SPI1_MOSI_GPIO_PIN
#define HCI_TL_SPI_MISO_PORT  BUS_SPI1_MISO_GPIO_PORT
#define HCI_TL_SPI_MISO_PIN   BUS_SPI1_MISO_GPIO_PIN
#ifdef IS_GPIO_AF
#define HCI_TL_SPI_MOSI_AF    BUS_SPI1_MOSI_GPIO_AF
#define HCI_TL_SPI_MISO_AF    BUS_SPI1_MISO_GPIO_AF
#endif /* IS_GPIO_AF */

/* Exported variables --------------------------------------------------------*/
extern volatile uint32_t hci_event;

extern EXTI_HandleTypeDef hexti11;
#define H_EXTI_11 hexti11
#define H_EXTI hexti11
#define EXTI_LINE EXTI_LINE_11

/* Exported Functions --------------------------------------------------------*/

/**
  * @defgroup LL_HCI_TL_INTERFACE_TEMPLATE_Functions Exported Functions
  * @{
  */
int32_t hci_tl_spi_init(void *pConf);
int32_t hci_tl_spi_de_init(void);

/**
  * @brief  Register hci_tl_interface IO bus services and the IRQ handlers.
  * @param  None
  * @retval None
  */
void hci_tl_lowlevel_init(void);

/**
  * @brief HCI Transport Layer Low Level Interrupt Service Routine
  * @param  None
  * @retval None
  */
void hci_tl_lowlevel_isr(void);

/**
  * @}
  */

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
#endif /* HCI_TL_INTERFACE_H */
