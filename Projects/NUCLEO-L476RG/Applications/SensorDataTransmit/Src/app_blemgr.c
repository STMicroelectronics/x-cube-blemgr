/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_blemgr.c
  * @author  System Research & Applications Team - Catania Lab.
  * @brief   This file provides code for blemgr application.
  *
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

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_blemgr.h"
#include "BLE_Manager.h"

#define PRESSURE_MIDDLE_VALUE 1000.0

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private macro ------------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* Imported Variables --------------------------------------------------------*/

/* USER CODE BEGIN IV */

/* USER CODE END IV */

/* Exported Variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private Variables ---------------------------------------------------------*/
static uint8_t BlinkLed                         = 0;
static uint8_t RandomEnvEnabled                 = 0;
static uint8_t RandomSensorFusionEnabled        = 0;
static uint8_t LedEnabled                       = 0;
static uint8_t LedStatus                        = 0;

static volatile uint32_t FeatureMask;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void User_Init(void);
static void User_Process(void);
static void ComputeRandomQuaternions(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

void MX_BLEMGR_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* USER CODE BEGIN BLEMGR_Init_PreTreatment */

  /* USER CODE END BLEMGR_Init_PreTreatment */

  /* Initialize BLEMGR application */

  User_Init();
  /* Initialize the BlueNRG stack and services */

  BluetoothInit();

  /* USER CODE BEGIN BLEMGR_Init_PostTreatment */

  /* USER CODE END BLEMGR_Init_PostTreatment */
}

/*
 * BLEMGR background task
 */
void MX_BLEMGR_Process(void)
{
  /* USER CODE BEGIN BLEMGR_Process_PreTreatment */

  /* USER CODE END BLEMGR_Process_PreTreatment */

  /* Process of the BLEMGR application */

  User_Process();

  /* USER CODE BEGIN BLEMGR_Process_PostTreatment */

  /* USER CODE END BLEMGR_Process_PostTreatment */
}

/**
  * @brief  Initialize User process.
  *
  * @param  None
  * @retval None
  */
static void User_Init(void)
{
  BSP_LED_Init(LED_GREEN);

  /* Initialize button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

#ifdef SENSOR_DT_ENABLE_PRINTF
  /* UART Initialization */
  if (BSP_COM_Init(COM1) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }
  else
  {
    HAL_Delay(20);
    SENSOR_DT_PRINTF("\033[2J\033[1;1f");
    SENSOR_DT_PRINTF("UART Initialized\r\n");
  }
#endif /* SENSOR_DT_ENABLE_PRINTF */

  SENSOR_DT_PRINTF("\r\nSTMicroelectronics %s:\r\n"
                   "\tVersion %c.%c.%c\r\n"
                   "\tSTM32L476RG-Nucleo board"
                   "\r\n",
                   FW_PACKAGENAME,
                   FW_VERSION_MAJOR, FW_VERSION_MINOR, FW_VERSION_PATCH);

  SENSOR_DT_PRINTF("\n\t(HAL %ld.%ld.%ld_%ld)\r\n"
                   "\tCompiled %s %s"
#if defined (__IAR_SYSTEMS_ICC__)
                   " (IAR)\r\n"
#elif defined (__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) /* For ARM Compiler 5 and 6 */
                   " (KEIL)\r\n"
#elif defined (__GNUC__)
                   " (STM32CubeIDE)\r\n"
#endif /* IDE */
                   ,
                   HAL_GetHalVersion() >> 24,
                   (HAL_GetHalVersion() >> 16) & 0xFF,
                   (HAL_GetHalVersion() >> 8) & 0xFF,
                   HAL_GetHalVersion()      & 0xFF,
                   __DATE__, __TIME__);

  SENSOR_DT_PRINTF("\r\n");

#ifdef SENSOR_DT_DEBUG_CONNECTION
  SENSOR_DT_PRINTF("Debug Connection         Enabled\r\n");
#endif /* SENSOR_DT_DEBUG_CONNECTION */

#ifdef SENSOR_DT_NOTIFY_TRAMISSION
  SENSOR_DT_PRINTF("Debug Notify Transmission Enabled\r\n\n");
#endif /* SENSOR_DT_NOTIFY_TRAMISSION */
}

/**
  * @brief  Configure the device as Client or Server and manage the communication
  *         between a client and a server.
  *
  * @param  None
  * @retval None
  */
static void User_Process(void)
{
  if (set_connectable)
  {
    set_connectable = 0;
    setConnectable();
    BlinkLed = 1;
  }

  /* handle BLE event */
  hci_user_evt_proc();

  /* Blinking the Led */
  if (BlinkLed)
  {
    BSP_LED_Toggle(LED_GREEN);
    LedStatus = !LedStatus;

    /* wait 1 sec before Led Status changes */
    HAL_Delay(1000);
  }

  /* Environmental Data */
  if (RandomEnvEnabled)
  {
    int32_t PressToSend;
    uint16_t HumToSend;
    int16_t TempToSend;

    /* Read all the Environmental Sensors */
    SetRandomEnvironmentalValues(&PressToSend, &HumToSend, &TempToSend);

    /* Send the Data with BLE */
    BLE_EnvironmentalUpdate(PressToSend, HumToSend, TempToSend, 0);

    /* wait 1 sec before sending new data */
    HAL_Delay(1000);
  }

  /* MotionFX */
  if (RandomSensorFusionEnabled)
  {
    ComputeRandomQuaternions();

    /* wait 100 ms before sending new data */
    HAL_Delay(100);
  }

  /* Wait next event */
  __WFI();
}

/**
  * @brief  Compute Random Quaternions
  * @param  None
  * @retval None
  */
static void ComputeRandomQuaternions(void)
{
  static BLE_MOTION_SENSOR_Axes_t quat_axes_send[1] = {{0, 0, 0}};

  static uint32_t counter = 0;

  /* Update Acceleration, Gyroscope and Sensor Fusion data */
  if (counter < 25)
  {
    quat_axes_send[0].Axis_x -= (100  + ((uint64_t)rand() * 3 * counter) / RAND_MAX);
    quat_axes_send[0].Axis_y += (100  + ((uint64_t)rand() * 5 * counter) / RAND_MAX);
    quat_axes_send[0].Axis_z -= (100  + ((uint64_t)rand() * 7 * counter) / RAND_MAX);
  }
  else
  {
    quat_axes_send[0].Axis_x += (200 + ((uint64_t)rand() * 7 * counter) / RAND_MAX);
    quat_axes_send[0].Axis_y -= (150 + ((uint64_t)rand() * 3 * counter) / RAND_MAX);
    quat_axes_send[0].Axis_z += (10  + ((uint64_t)rand() * 5 * counter) / RAND_MAX);
  }

  BLE_SensorFusionUpdate(quat_axes_send, 1);

  counter ++;
  if (counter == 50)
  {
    counter = 0;
    quat_axes_send[0].Axis_x = -quat_axes_send[0].Axis_x;
    quat_axes_send[0].Axis_y = -quat_axes_send[0].Axis_y;
    quat_axes_send[0].Axis_z = -quat_axes_send[0].Axis_z;
  }
}

/**
  * @brief  Random Environmental Data (Temperature/Pressure/Humidity)
  * @param  int32_t *PressToSend pointer to Press Value
  * @param  uint16_t *HumToSend  pointer to Humidity Value
  * @param  int16_t *TempToSend pointer to Temperature Value
  * @retval None
  */
void SetRandomEnvironmentalValues(int32_t *PressToSend, uint16_t *HumToSend, int16_t *TempToSend)
{
  float RandomValue;
  int32_t decPart, intPart;

  *PressToSend = 0;
  *HumToSend = 0;
  *TempToSend = 0;

  /* P sensor emulation */
  RandomValue = PRESSURE_MIDDLE_VALUE + ((uint64_t)rand() * 80) / RAND_MAX;
  MCR_BLUEMS_F2I_2D(RandomValue, intPart, decPart);
  *PressToSend = intPart * 100 + decPart;

  /* H sensor emulation */
  RandomValue = 60.0 + ((uint64_t)rand() * 20) / RAND_MAX;
  MCR_BLUEMS_F2I_1D(RandomValue, intPart, decPart);
  *HumToSend = intPart * 10 + decPart;

  /* T sensor emulation */
  RandomValue = 27.0 + ((uint64_t)rand() * 5) / RAND_MAX;
  MCR_BLUEMS_F2I_1D(RandomValue, intPart, decPart);
  *TempToSend = intPart * 10 + decPart;
}

/**
  * @brief  This function is called when there is a LE Connection Complete event.
  * @param  uint16_t ConnectionHandle
  * @param  uint8_t Address_Type
  * @param  uint8_t addr[6]
  * @retval None
  */
void ConnectionCompletedFunction(uint16_t ConnectionHandle, uint8_t Address_Type, uint8_t addr[6])
{
  BlinkLed = 0;

  BSP_LED_Off(LED_GREEN);
  LedStatus = 0;

  /* USER CODE BEGIN */

  /* USER CODE END */

  SENSOR_DT_PRINTF("Call to ConnectionCompletedFunction\r\n");
  HAL_Delay(100);
}

/**
  * @brief  This function is called when the peer device get disconnected.
  * @param  None
  * @retval None
  */
void DisconnectionCompletedFunction(void)
{
  LedEnabled = 0;
  RandomEnvEnabled = 0;
  RandomSensorFusionEnabled = 0;

  /* USER CODE BEGIN */

  /* USER CODE END */

  SENSOR_DT_PRINTF("Call to DisconnectionCompletedFunction\r\n");
  HAL_Delay(100);
}

/**
  * @brief  This function makes the parsing of the Debug Console
  * @param  uint8_t *att_data attribute data
  * @param  uint8_t data_length length of the data
  * @retval uint32_t SendBackData true/false
  */
uint32_t DebugConsoleParsing(uint8_t *att_data, uint8_t data_length)
{
  uint32_t SendBackData = 1;

  /* Help Command */
  if (!strncmp("help", (char *)(att_data), 4))
  {
    /* Print Legend */
    SendBackData = 0;

    BytesToWrite = sprintf((char *)BufferToWrite, "Command:\r\n"
                           "info-> System Info\r\n"
                           "versionBle-> Ble Version\r\n"
                           "uid-> STM32 UID value\r\n");
    Term_Update(BufferToWrite, BytesToWrite);
  }
  else if (!strncmp("info", (char *)(att_data), 4))
  {
    SendBackData = 0;

    BytesToWrite = sprintf((char *)BufferToWrite, "\r\nSTMicroelectronics %s:\r\n"
                           "\tVersion %c.%c.%c\r\n"
                           "\tSTM32L476RG-Nucleo board"
                           "\r\n",
                           BLE_FW_PACKAGENAME,
                           BLE_VERSION_FW_MAJOR, BLE_VERSION_FW_MINOR, BLE_VERSION_FW_PATCH);

    Term_Update(BufferToWrite, BytesToWrite);

    BytesToWrite = sprintf((char *)BufferToWrite, "\t(HAL %ld.%ld.%ld_%ld)\r\n"
                           "\tCompiled %s %s"
#if defined (__IAR_SYSTEMS_ICC__)
                           " (IAR)\r\n",
#elif defined (__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) /* For ARM Compiler 5 and 6 */
                           " (KEIL)\r\n",
#elif defined (__GNUC__)
                           " (STM32CubeIDE)\r\n",
#endif /* IDE */
                           HAL_GetHalVersion() >> 24,
                           (HAL_GetHalVersion() >> 16) & 0xFF,
                           (HAL_GetHalVersion() >> 8) & 0xFF,
                           HAL_GetHalVersion()      & 0xFF,
                           __DATE__, __TIME__);

    Term_Update(BufferToWrite, BytesToWrite);
  }
  else if (!strncmp("versionBle", (char *)(att_data), 10))
  {
    uint8_t  hwVersion;
    uint16_t fwVersion;
    /* get the BlueNRG HW and FW versions */
    getBlueNRGVersion(&hwVersion, &fwVersion);
    BytesToWrite = sprintf((char *)BufferToWrite, "%s_%d.%d.%c\r\n",
                           "BlueNRG2",
                           (fwVersion >> 8) & 0xF,
                           (fwVersion >> 4) & 0xF,
                           ('a' + (fwVersion & 0xF)));
    Term_Update(BufferToWrite, BytesToWrite);
    SendBackData = 0;
  }
  else if ((att_data[0] == 'u') & (att_data[1] == 'i') & (att_data[2] == 'd'))
  {
    /* Write back the STM32 UID */
    uint8_t *uid = (uint8_t *)BLE_STM32_UUID;
    uint32_t MCU_ID = BLE_STM32_MCU_ID[0] & 0xFFF;
    BytesToWrite = sprintf((char *)BufferToWrite, "%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X_%.3lX\r\n",
                           uid[ 3], uid[ 2], uid[ 1], uid[ 0],
                           uid[ 7], uid[ 6], uid[ 5], uid[ 4],
                           uid[11], uid[ 10], uid[9], uid[8],
                           MCU_ID);
    Term_Update(BufferToWrite, BytesToWrite);
    SendBackData = 0;
  }

  return SendBackData;
}

/**
  * @brief  Callback Function for Config write request.
  * @param uint8_t *att_data attribute data
  * @param uint8_t data_length length of the data
  * @retval None
  */
void WriteRequestConfigFunction(uint8_t *att_data, uint8_t data_length)
{
  uint32_t FeatureMask = (att_data[3]) | (att_data[2] << 8) | (att_data[1] << 16) | (att_data[0] << 24);
  uint8_t Command = att_data[4];
  uint8_t Data    = att_data[5];

  switch (FeatureMask)
  {
    case FEATURE_MASK_LED:
      /* Led events */
#ifdef SENSOR_DT_DEBUG_CONNECTION
      if (BLE_StdTerm_Service == BLE_SERV_ENABLE)
      {
        BytesToWrite = sprintf((char *)BufferToWrite, "Conf Sig F=%lx C=%2x\n\r", FeatureMask, Command);
        Term_Update(BufferToWrite, BytesToWrite);
      }
      else
      {
        SENSOR_DT_PRINTF("Conf Sig F=%lx C=%2x\r\n", FeatureMask, Command);
      }
#endif /* SENSOR_DT_DEBUG_CONNECTION */
      switch (Command)
      {
        case 1:
          BSP_LED_On(LED_GREEN);
          LedStatus = 1;
          Config_Update(FEATURE_MASK_LED, Command, Data);
          break;
        case 0:
          BSP_LED_Off(LED_GREEN);
          LedStatus = 0;
          Config_Update(FEATURE_MASK_LED, Command, Data);
          break;
      }
      /* Update the LED feature */
      if (LedEnabled)
      {
        BLE_LedStatusUpdate(LedStatus);
      }
      break;
  }
}

/***************************************************
  * Callback functions to manage the notify events *
  **************************************************/

/**
  * @brief  Callback Function for Un/Subscription Feature
  * @param  BLE_NotifyEvent_t Event Sub/Unsub
  * @retval None
  */
void NotifyEventEnv(BLE_NotifyEvent_t Event)
{
  /* Environmental Features */
  if (Event == BLE_NOTIFY_SUB)
  {
    RandomEnvEnabled = 1;
  }

  if (Event == BLE_NOTIFY_UNSUB)
  {
    RandomEnvEnabled = 0;
  }

  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
  * @brief  Callback Function for Un/Subscription Feature
  * @param  BLE_NotifyEvent_t Event Sub/Unsub
  * @retval None
  */
void NotifyEventLed(BLE_NotifyEvent_t Event)
{
  /* Led Features */
  if (Event == BLE_NOTIFY_SUB)
  {
    LedEnabled = 1;
    BLE_LedStatusUpdate(LedStatus);
  }

  if (Event == BLE_NOTIFY_UNSUB)
  {
    LedEnabled = 0;
  }

  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
  * @brief  Callback Function for Un/Subscription Feature
  * @param  BLE_NotifyEvent_t Event Sub/Unsub
  * @retval None
  */
void NotifyEventSensorFusion(BLE_NotifyEvent_t Event)
{
  /* Sensor Fusion Features */
  if (Event == BLE_NOTIFY_SUB)
  {
    RandomSensorFusionEnabled = 1;
  }

  if (Event == BLE_NOTIFY_UNSUB)
  {
    RandomSensorFusionEnabled = 0;
  }

  /* USER CODE BEGIN */

  /* USER CODE END */
}

/**
  * @brief  Callback Function for answering to Info command
  * @param  uint8_t *Answer Return String
  * @retval None
  */
void ExtConfigInfoCommandCallback(uint8_t *Answer)
{
  uint8_t  hwVersion;
  uint16_t fwVersion;

  /* get the BlueNRG HW and FW versions */
  getBlueNRGVersion(&hwVersion, &fwVersion);

  sprintf((char *)Answer, "STMicroelectronics %s:\n"
          "Version %c.%c.%c\n"
          "%s board\n"
          "BlueNRG-2 HW ver%d.%d\n"
          "BlueNRG-2 FW ver%d.%d.%c\n"
          "(HAL %ld.%ld.%ld_%ld)\n"
          "Compiled %s %s"
#if defined (__IAR_SYSTEMS_ICC__)
          " (IAR)",
#elif defined (__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) /* For ARM Compiler 5 and 6 */
          " (KEIL)",
#elif defined (__GNUC__)
          " (STM32CubeIDE)",
#endif /* IDE */
          FW_PACKAGENAME,
          FW_VERSION_MAJOR,
          FW_VERSION_MINOR,
          FW_VERSION_PATCH,
          STM32_BOARD,
          ((hwVersion >> 4) & 0x0F),
          (hwVersion & 0x0F),
          (fwVersion >> 8) & 0xF,
          (fwVersion >> 4) & 0xF,
          ('a' + (fwVersion & 0xF)),
          HAL_GetHalVersion() >> 24,
          (HAL_GetHalVersion() >> 16) & 0xFF,
          (HAL_GetHalVersion() >> 8) & 0xFF,
          HAL_GetHalVersion()      & 0xFF,
          __DATE__, __TIME__);
}

