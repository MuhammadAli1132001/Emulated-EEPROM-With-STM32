# Emulated EEPROM Library for STM32

This library provides an easy-to-use interface for emulating EEPROM functionality on STM32 microcontrollers using internal flash memory. It allows you to store and retrieve integer and string data in non-volatile memory, which persists even after power cycles.

## Features
- **Page-based Flash Memory Access**: Write and read data to/from specific pages in flash memory.
- **Data Integrity**: Ensures that data is written and retrieved with a null terminator for strings.
- **Simple API**: Provides an easy-to-use set of functions for interacting with flash memory.
- **Supports Both Integer and String Data**: Write integers and strings (in 64-bit chunks) to flash memory.

## Why This Library is Important
Embedded systems often require non-volatile storage for saving configuration parameters, calibration data, or user settings. The STM32 microcontrollers do not have built-in EEPROMs, so internal flash memory can be used as a replacement. This library makes the process of storing and retrieving data from flash memory straightforward, while also providing a robust interface for reading and writing data in a way that is both reliable and efficient.

## Supported STM32 Models
This library is designed to work with STM32 microcontrollers that use the HAL (Hardware Abstraction Layer) library, specifically the STM32G0 series. Other STM32 microcontrollers may also work with minor adjustments.

## Installation
1. **Download or Clone the Repository**:
   ```bash
   git clone https://github.com/MuhammadAli1132001/Emulated-EEPROM-With-STM32.git

2. Add the Files to Your Project: Copy the emulated_eeprom.c and emulated_eeprom.h files into your STM32 project directory. Include emulated_eeprom.h in your source files where needed.

3. Link HAL Library: Ensure you have the STM32 HAL library linked to your project as this library uses the HAL_FLASH_Unlock, HAL_FLASH_Program, and related functions.
