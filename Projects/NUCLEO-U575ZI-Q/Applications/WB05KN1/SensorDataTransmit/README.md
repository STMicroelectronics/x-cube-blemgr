## <b>SensorDataTransmit Application Description</b>

Application for NUCLEO-U575ZI-Q with X-NUCLEO-WB05KN1 expansion board.

Example Description:

The SensorDataTransmit is a sample application to help the user to set and configure Bluetooth connectivity from the board
to a mobile application (such as ST BLE Sensor) according to STM32_BLE_Manager middleware.

The Example application initializes all the Components and Library creating 2 Custom Bluetooth services:

 - The three service exposes:
   - the HW characteristics related to randomly generated Temperature, Humidity,
     Pressure values and LED status.
   - the SW characteristic: the randomly generated quaternions
 - The second service is used for configuration purpose
 
The example application allows the user to control the initialization phase via UART.
Launch a terminal application and set the UART port to 115200 bps, 8 bit, No Parity, 1 stop bit.
 
This example must be used with the related ST BLE Sensor Android or iOS application available on Play/iTune Store,
in order to read the information sent over Bluetooth Low Energy protocol

### <b>Important Hardware Additional Information</b>

The firmware of X-NUCLEO-WB05KN1 to be upgrade with latest BLE_Transparent_Mode_STM32WB05_location_essential binary images present in X-CUBE-WB05N_V2.1.0 package on to Utilities folder.
Please refer UM3406/section 3.3 for steps to upgrade the X-NUCLEO-WB05KN1 firmware.
Depending on the use case user can select between UART/SPI image:

 - For SPI select BLE_TransparentMode_SPI_with_Updater.hex image
 - For UART select BLE_TransparentMode_UART_with_Updater.hex image

### <b>Required STM32CubeMX settings</b>

Before code generation in Project Manager:

 - for toolchain/IDE MKD-ARM set Min Version to 5.32 (default is 5.39).
 
Without this setting the code will be building but the flashing on board will fail.

### <b>Required IDE settings</b>

For Keil IDE:

 - set the "Micro LIB" option from within the "Project/Option for Target" menu (Target tab).
 - set the "Misc Controls" option with the "-Wno-format" string, from within the "Project/Option for Target" menu (C/C++ (AC6) tab).
 
### <b>Keywords</b>

BLE, BLE_Manager, WB05N, SPI, UART

### <b>Hardware and Software environment</b>

  - This example runs on STM32 Nucleo devices with BlueNRG-2 STM32 expansion board
    (X-NUCLEO-WB05KN1)
  - This example has been tested with STMicroelectronics:
    - NUCLEO-U575ZI-Q board
  - This example must be used with the related ST BLE Sensor Android/iOS application (Version 5.0.0 or higher) available on the Google Play or Apple App Store, in order to read the sent information by Bluetooth Low Energy protocol

	
ADDITIONAL_BOARD : X-NUCLEO-WB05KN1 https://www.st.com/en/evaluation-tools/x-nucleo-wb05kn1.html
ADDITIONAL_COMP : STM32WB05KN https://www.st.com/en/microcontrollers-microprocessors/stm32wb05kn.html

### <b>Dependencies</b>

STM32Cube packages:

  - STM32U5xx drivers from STM32CubeU5 V1.8.0
  
X-CUBE packages:

  - X-CUBE-WB05N V2.1.0
  
### <b>How to use it?</b>

This package contains projects for 3 IDEs IAR, Keil µVision 5 and Integrated Development Environment for STM32. 
In order to make the  program work, you must do the following:

 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.

For IAR:

 - Open IAR toolchain (this firmware has been successfully tested with Embedded Workbench V9.60.3).
 - Open the IAR project file EWARM\Project.eww
 - Rebuild all files 

For Keil µVision 5:

 - Open Keil µVision 5 toolchain (this firmware has been successfully tested with MDK-ARM Professional Version: 5.38.0).
 - Open the µVision project file MDK-ARM\SensorDataTransmit.uvprojx
 - Rebuild all files
 
For Integrated Development Environment for STM32:

 - Open STM32CubeIDE (this firmware has been successfully tested with Version 2.1.1).
 - Set the default workspace proposed by the IDE (please be sure that there are not spaces in the workspace path).
 - Press "File" -> "Import" -> "Existing Projects into Workspace"; press "Browse" in the "Select root directory" and choose the path where the System
   Workbench project is located (it should be STM32CubeIDE). 
 - Rebuild all files

### <b>Author</b>

SRA Application Team

### <b>License</b>

Copyright (c) 2026 STMicroelectronics.
All rights reserved.

This software is licensed under terms that can be found in the LICENSE file
in the root directory of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.