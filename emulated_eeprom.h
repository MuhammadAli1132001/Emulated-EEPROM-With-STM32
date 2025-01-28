/*
 * emulated_eeprom.h
 *
 * Created on: Nov 13, 2024
 * Author: Muhammad Ali
 */

#ifndef EMULATED_EEPROM_H
#define EMULATED_EEPROM_H

#include "main.h"
#include "stm32g0xx_hal_flash.h"

// Flash memory configuration
#define FLASH_BASE_ADDRESS 0x08000000 // Base address of flash memory
#define DATA_SPACING       8          // Space between consecutive data entries (bytes)
#define PAGE_SIZE          2048       // Flash memory page size (bytes)
#define DATA_PAGE          50         // Page number used for storing data

// Function prototypes
uint32_t Flash_GetPageAddress(int pageNumber); // Get the flash address of a page
void Flash_ErasePage(uint32_t pageAddress);    // Erase a flash memory page
void Flash_WriteData(uint32_t pageAddress, int intData, const char *strData); // Write integer and string data to flash
uint32_t Flash_ReadInt(uint32_t address);      // Read an integer from flash
void Flash_ReadString(uint32_t address, char *buffer, size_t maxLength); // Read a string from flash

#endif // EMULATED_EEPROM_H
