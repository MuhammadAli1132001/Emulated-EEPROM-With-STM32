/*
 * emulated_eeprom.c
 *
 *  Created on: Nov 13, 2024
 *      Author: Muhammad Ali
 */

#include "emulated_eeprom.h"

uint32_t EE_GetPageHexAddress(int pageNumber) {
    uint32_t offset = PAGE_SIZE * pageNumber;
    uint32_t hexAddress = FLASH_BASE_ADDRESS + offset;
    return hexAddress;
}

void EE_ErasePage(uint32_t pageAddress) {
    HAL_StatusTypeDef status;

    status = HAL_FLASH_Unlock();
    if (status != HAL_OK) return;

    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT);
    if (status != HAL_OK) return;

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR);
    FLASH_PageErase(FLASH_BANK_1, pageAddress);

    status = FLASH_WaitForLastOperation(FLASH_TIMEOUT);
    if (status != HAL_OK) return;

    CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
    HAL_FLASH_Lock();
}

void EE_WriteDataIntString(uint32_t pageAddress, int integerData, char *stringData) {
    EE_ErasePage(DATA_PAGE);
    HAL_FLASH_Unlock();

    // Write integer data
    HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, pageAddress, integerData);

    // Write string data in 64-bit chunks
    uint32_t address = pageAddress + DATA_SPACING * 2;
    size_t len = strlen(stringData);
    for (size_t i = 0; i < len; i += 8) {
        uint64_t chunk = 0;
        memcpy(&chunk, &stringData[i], (len - i >= 8) ? 8 : len - i);
        HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, address, chunk);
        address += 8;
    }

    // Write null terminator
    uint64_t nullTerminator = 0;
    HAL_FLASH_Program(TYPEPROGRAM_DOUBLEWORD, address, nullTerminator);

    HAL_FLASH_Lock();
}

uint32_t EE_ReadInteger(uint32_t address) {
    return *(uint32_t *)address;
}

void EE_ReadString(uint32_t address, char *buffer, size_t maxLength) {
    size_t i = 0;
    while (i < maxLength - 1) { // Reserve space for null terminator
        char c = *(char *)(address + i);
        buffer[i] = c;
        if (c == '\0') break;
        i++;
    }
    buffer[maxLength - 1] = '\0'; // Ensure null termination
}
