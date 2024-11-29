## <b>SensorDataTransmit Application Description</b>

Application for STEVAL-MKBOXPRO board.

Example Description:

The SensorDataTransmit is a sample application to help the user to set and configure bluetooth connectivity from board
to mobile application (such as ST BLE Sensor) according to STM32_BLE_Manager middleware.

The Example application initizializes all the Components and Library creating 3 Custom Bluetooth services:

 - The first service exposes:
   - the HW characteristics related to randomly Temperature, Humidity,
     Pressure values and LED status.
   - the SW characteristic: the quaternions randomly generated 
 - The second Service exposes the console services where we have stdin/stdout and stderr capabilities
 - The last Service is used for configuration purpose
The example application allows the user to control the initialization phase via UART.
Launch a terminal application and set the UART port to 115200 bps, 8 bit, No Parity, 1 stop bit.
 
This example must be used with the related ST BLE Sensor Android or iOS application available on Play/itune store,
in order to read the sent information by Bluetooth Low Energy protocol

### <b>Required IDE settings</b>

For Keil IDE:

 - set the "Micro LIB" option from within the "Project/Option for Target" menu (Target tab).
 - set the "Misc Controls" option with the "-Wno-format" string, from within the "Project/Option for Target" menu (C/C++ (AC6) tab).
 
### <b>Keywords</b>

BLE, BLE_Manager, BlueNRG-LP, SPI, UART

### <b>Hardware and Software environment</b>

- This example runs on STEVAL-MKBOXPRO (SensorTile.box-Pro) evaluation board and it can be easily tailored to any other supported device and development board.
- This example must be used with the related ST BLE Sensor Android/iOS application (Version 5.0.0 or higher) available on the Google Play or Apple App Store, in order to read the sent information by Bluetooth Low Energy protocol

ADDITIONAL_COMP : BlueNRG-LP https://www.st.com/en/wireless-connectivity/bluenrg-lp.html

### <b>Dependencies</b>

STM32Cube packages:

  - STM32U5xx drivers from STM32CubeU5 V1.6.0
  
### <b>How to use it?</b>

This package contains projects for 3 IDEs viz. IAR, Keil µVision 5 and Integrated Development Environment for STM32. 
In order to make the  program work, you must do the following:

 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.

For IAR:

 - Open IAR toolchain (this firmware has been successfully tested with Embedded Workbench V9.20.1).
 - Open the IAR project file EWARM\Project.eww
 - Rebuild all files 

For Keil µVision 5:

 - Open Keil µVision 5 toolchain (this firmware has been successfully tested with MDK-ARM Professional Version: 5.38.0).
 - Open the µVision project file MDK-ARM\SensorDataTransmit.uvprojx
 - Rebuild all files
 
For Integrated Development Environment for STM32:

 - Open STM32CubeIDE (this firmware has been successfully tested with Version 1.16.1).
 - Set the default workspace proposed by the IDE (please be sure that there are not spaces in the workspace path).
 - Press "File" -> "Import" -> "Existing Projects into Workspace"; press "Browse" in the "Select root directory" and choose the path where the System
   Workbench project is located (it should be STM32CubeIDE). 
 - Rebuild all files

### <b>Author</b>

SRA Application Team

### <b>License</b>

Copyright (c) 2024 STMicroelectronics.
All rights reserved.

This software is licensed under terms that can be found in the LICENSE file
in the root directory of this software component.
If no LICENSE file comes with this software, it is provided AS-IS.