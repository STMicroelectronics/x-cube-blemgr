/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    hci_tl_interface_template.c
  * @author  System Research & Applications Team - Agrate/Catania Lab.
  * @brief   This file provides the implementation for all functions prototypes
  *          for the STM32 BlueNRG HCI Transport Layer interface
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

/* Includes ------------------------------------------------------------------*/
#include "RTE_Components.h"

#include "hci_tl.h"

/* Defines -------------------------------------------------------------------*/
#define HEADER_SIZE       5U
#define MAX_BUFFER_SIZE   255U
#define TIMEOUT_DURATION  15U
#define TIMEOUT_IRQ_HIGH  1000U

/* Exported variables --------------------------------------------------------*/
volatile uint32_t hci_event = 0;

/* Private variables ---------------------------------------------------------*/
EXTI_HandleTypeDef hexti11;

/* Private function prototypes -----------------------------------------------*/
static void hci_tl_spi_enable_irq(void);
static void hci_tl_spi_disable_irq(void);
static int32_t is_data_available(void);

/******************** IO Operation and BUS services ***************************/
/**
  * @brief  Enable SPI IRQ.
  * @param  None
  * @retval None
  */
static void hci_tl_spi_enable_irq(void)
{
  HAL_NVIC_EnableIRQ(HCI_TL_SPI_EXTI_IRQn);
}

/**
  * @brief  Disable SPI IRQ.
  * @param  None
  * @retval None
  */
static void hci_tl_spi_disable_irq(void)
{
  HAL_NVIC_DisableIRQ(HCI_TL_SPI_EXTI_IRQn);
}

/**
  * @brief  Initializes the peripherals communication with the BlueNRG
  *         Expansion Board (via SPI, I2C, USART, ...)
  *
  * @param  void* Pointer to configuration struct
  * @retval int32_t Status
  */
int32_t hci_tl_spi_init(void *pConf)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  BUS_EXTI_GPIO_CLK_ENABLE();
  BUS_CS_GPIO_CLK_ENABLE();
  BUS_RST_GPIO_CLK_ENABLE();

  /* Configure EXTI Line */
  GPIO_InitStruct.Pin = HCI_TL_SPI_EXTI_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(HCI_TL_SPI_EXTI_PORT, &GPIO_InitStruct);

  /* Configure RESET Line */
  GPIO_InitStruct.Pin =  HCI_TL_RST_PIN ;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HCI_TL_RST_PORT, &GPIO_InitStruct);

  /* Configure CS */
  GPIO_InitStruct.Pin = HCI_TL_SPI_CS_PIN ;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HCI_TL_SPI_CS_PORT, &GPIO_InitStruct);
  /* Deselect CS PIN for BlueNRG at startup to avoid spurious commands */
  HAL_GPIO_WritePin(HCI_TL_SPI_CS_PORT, HCI_TL_SPI_CS_PIN, GPIO_PIN_SET);

  return BSP_SPI1_Init();
}

/**
  * @brief  DeInitializes the peripherals communication with the BlueNRG
  *         Expansion Board (via SPI, I2C, USART, ...)
  *
  * @param  None
  * @retval int32_t 0
  */
int32_t hci_tl_spi_de_init(void)
{
  HAL_GPIO_DeInit(HCI_TL_SPI_EXTI_PORT, HCI_TL_SPI_EXTI_PIN);
  HAL_GPIO_DeInit(HCI_TL_SPI_CS_PORT, HCI_TL_SPI_CS_PIN);
  HAL_GPIO_DeInit(HCI_TL_RST_PORT, HCI_TL_RST_PIN);
  return 0;
}

/**
  * @brief Reset BlueNRG module.
  *
  * @param  None
  * @retval int32_t 0
  */
int32_t hci_tl_spi_reset(void)
{
  /* Deselect CS PIN for BlueNRG to avoid spurious commands */
  HAL_GPIO_WritePin(HCI_TL_SPI_CS_PORT, HCI_TL_SPI_CS_PIN, GPIO_PIN_SET);

  HAL_GPIO_WritePin(HCI_TL_RST_PORT, HCI_TL_RST_PIN, GPIO_PIN_RESET);
  HAL_Delay(5);
  HAL_GPIO_WritePin(HCI_TL_RST_PORT, HCI_TL_RST_PIN, GPIO_PIN_SET);
  HAL_Delay(150);
  return 0;
}

/**
  * @brief  Reads from BlueNRG SPI buffer and store data into local buffer.
  *
  * @param  buffer : Buffer where data from SPI are stored
  * @param  size   : Buffer size
  * @retval int32_t: Number of read bytes
  */
int32_t hci_tl_spi_receive(uint8_t *buffer, uint16_t size)
{
  uint16_t byte_count;
  uint16_t len = 0;
  uint8_t char_00 = 0x00;
  volatile uint8_t read_char;

  uint8_t header_master[HEADER_SIZE] = {0x0b, 0x00, 0x00, 0x00, 0x00};
  uint8_t header_slave[HEADER_SIZE];

  if (HAL_GPIO_ReadPin(HCI_TL_SPI_IRQ_PORT, HCI_TL_SPI_IRQ_PIN) != GPIO_PIN_SET)
  {
    return 0;
  }

  hci_tl_spi_disable_irq();

  /* CS reset */
  HAL_GPIO_WritePin(HCI_TL_SPI_CS_PORT, HCI_TL_SPI_CS_PIN, GPIO_PIN_RESET);

  /* Read the header */
  BSP_SPI1_SendRecv(header_master, header_slave, HEADER_SIZE);

  /* device is ready */
  byte_count = (header_slave[4] << 8) | header_slave[3];

  if (byte_count > 0)
  {
    /* avoid to read more data than the size of the buffer */
    if (byte_count > size)
    {
      byte_count = size;
    }

    for (len = 0; len < byte_count; len++)
    {
      BSP_SPI1_SendRecv(&char_00, (uint8_t *)&read_char, 1);
      buffer[len] = read_char;
    }
  }

  /**
    * To be aligned to the SPI protocol.
    * Can bring to a delay inside the frame, due to the BlueNRG that needs
    * to check if the header is received or not.
    */
  uint32_t tickstart = HAL_GetTick();
  while ((HAL_GetTick() - tickstart) < TIMEOUT_IRQ_HIGH)
  {
    if (HAL_GPIO_ReadPin(HCI_TL_SPI_IRQ_PORT, HCI_TL_SPI_IRQ_PIN)==GPIO_PIN_RESET)
    {
      break;
    }
  }

  hci_tl_spi_enable_irq();

  /* Release CS line */
  HAL_GPIO_WritePin(HCI_TL_SPI_CS_PORT, HCI_TL_SPI_CS_PIN, GPIO_PIN_SET);

  return len;
}

/**
  * @brief  Writes data from local buffer to SPI.
  *
  * @param  buffer : data buffer to be written
  * @param  size   : size of first data buffer to be written
  * @retval int32_t: Number of read bytes
  */
int32_t hci_tl_spi_send(uint8_t *buffer, uint16_t size)
{
  int32_t result;
  uint16_t rx_bytes;

  uint8_t header_master[HEADER_SIZE] = {0x0a, 0x00, 0x00, 0x00, 0x00};
  uint8_t header_slave[HEADER_SIZE];

  static uint8_t read_char_buf[MAX_BUFFER_SIZE];
  uint32_t tickstart = HAL_GetTick();

  hci_tl_spi_disable_irq();

  do
  {
    uint32_t tickstart_data_available = HAL_GetTick();

    result = 0;

    /* CS reset */
    HAL_GPIO_WritePin(HCI_TL_SPI_CS_PORT, HCI_TL_SPI_CS_PIN, GPIO_PIN_RESET);

    /*
     * Wait until BlueNRG-LP is ready.
     * When ready it will raise the IRQ pin.
     */
    while (!is_data_available())
    {
      if ((HAL_GetTick() - tickstart_data_available) > TIMEOUT_DURATION)
      {
        result = -3;
        break;
      }
    }
    if (result == -3)
    {
      /* The break causes the exiting from the "while", so the CS line must be released */
      HAL_GPIO_WritePin(HCI_TL_SPI_CS_PORT, HCI_TL_SPI_CS_PIN, GPIO_PIN_SET);
      break;
    }

    /* Read header */
    BSP_SPI1_SendRecv(header_master, header_slave, HEADER_SIZE);

    rx_bytes = (((uint16_t)header_slave[2]) << 8) | ((uint16_t)header_slave[1]);

    if (rx_bytes >= size)
    {
      /* Buffer is big enough */
      BSP_SPI1_SendRecv(buffer, read_char_buf, size);
    }
    else
    {
      /* Buffer is too small */
      result = -2;
    }

    /* Release CS line */
    HAL_GPIO_WritePin(HCI_TL_SPI_CS_PORT, HCI_TL_SPI_CS_PIN, GPIO_PIN_SET);

    if ((HAL_GetTick() - tickstart) > TIMEOUT_DURATION)
    {
      result = -3;
      break;
    }
  } while (result < 0);

  /**
    * To be aligned to the SPI protocol.
    * Can bring to a delay inside the frame, due to the BlueNRG that needs
    * to check if the header is received or not.
    */
  tickstart = HAL_GetTick();
  while ((HAL_GetTick() - tickstart) < TIMEOUT_IRQ_HIGH)
  {
    if (HAL_GPIO_ReadPin(HCI_TL_SPI_IRQ_PORT, HCI_TL_SPI_IRQ_PIN)==GPIO_PIN_RESET)
	{
      break;
    }
  }

  hci_tl_spi_enable_irq();

  return result;
}

/**
  * @brief  Reports if the BlueNRG has data for the host micro.
  *
  * @param  None
  * @retval int32_t: 1 if data are present, 0 otherwise
  */
static int32_t is_data_available(void)
{
  return (HAL_GPIO_ReadPin(HCI_TL_SPI_EXTI_PORT, HCI_TL_SPI_EXTI_PIN) == GPIO_PIN_SET);
}

/***************************** hci_tl_interface main functions *****************************/
/**
  * @brief  Register hci_tl_interface IO bus services
  *
  * @param  None
  * @retval None
  */
void hci_tl_lowlevel_init(void)
{
  /* USER CODE BEGIN hci_tl_lowlevel_init 1 */

  /* USER CODE END hci_tl_lowlevel_init 1 */

  /* USER CODE BEGIN hci_tl_lowlevel_init 2 */

  /* USER CODE END hci_tl_lowlevel_init 2 */

  /* USER CODE BEGIN hci_tl_lowlevel_init 3 */

  /* USER CODE END hci_tl_lowlevel_init 3 */
}

/**
  * @brief HCI Transport Layer Low Level Interrupt Service Routine
  *
  * @param  None
  * @retval None
  */
void hci_tl_lowlevel_isr(void)
{
  /* Call hci_notify_asynch_evt() */
  while (is_data_available())
  {
    if (hci_notify_asynch_evt(NULL))
    {
      return;
    }
  }

  hci_event = 1;

  /* USER CODE BEGIN hci_tl_lowlevel_isr */

  /* USER CODE END hci_tl_lowlevel_isr */
}

