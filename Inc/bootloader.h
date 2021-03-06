/**
  ******************************************************************************
  * STM32L4 Bootloader
  ******************************************************************************
  * @author Akos Pasztor
  * @file   bootloader.h
  * @brief  Bootloader header
  *	        This file contains the bootloader configuration parameters,
  *	        function prototypes and other required macros and definitions.
  * @see    Please refer to README for detailed information.
  ******************************************************************************
  * Copyright (c) 2017 Akos Pasztor.                    https://akospasztor.com
  ******************************************************************************
**/

#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

/*** Bootloader configuration *************************************************/
#define USE_SWO_TRACE           1       /* For development/debugging: stdout/stderr via SWO trace */
#define USE_CHECKSUM            1       /* Check application checksum on startup */
#define USE_WRITE_PROTECTION    0       /* Enable write protection after performing in-app-programming */
#define SET_VECTOR_TABLE        1       /* Automatically set vector table location before launching application */

#define APP_FILENAME    "image.bin"             /* File name of application located on SD card */
#define APP_ADDRESS     (uint32_t)0x08008000    /* Start address of application space in flash */
#define END_ADDRESS     (uint32_t)0x080FFFFB    /* End address of application space (addr. of last byte) */
#define CRC_ADDRESS     (uint32_t)0x080FFFFC    /* Start address of application checksum in flash */

#define SYSMEM_ADDRESS  (uint32_t)0x1FFF0000    /* Address of System Memory (ST Bootloader) */
/*** End of configuration *****************************************************/

/* Defines -------------------------------------------------------------------*/
#define FLASH_PAGE_NBPERBANK    256             /* Number of pages per bank in flash */
#define APP_SIZE        (uint32_t)(((END_ADDRESS - APP_ADDRESS) + 3) / 4) /* Size of application in DWORD (32bits or 4bytes) */

/* Bootloader Error Codes */
enum
{
    BL_OK = 0,
    BL_NO_APP,
    BL_SIZE_ERROR,
    BL_CHKS_ERROR,
    BL_ERASE_ERROR,
    BL_WRITE_ERROR,
    BL_OBP_ERROR
};

/* Flash Protection Types */
enum
{
    BL_PROTECTION_NONE  = 0,
    BL_PROTECTION_WRP   = 0x1,
    BL_PROTECTION_RDP   = 0x2,
    BL_PROTECTION_PCROP = 0x4,
};

/* Functions -----------------------------------------------------------------*/
void    Bootloader_Init(void);
uint8_t Bootloader_Erase(void);

void    Bootloader_FlashBegin(void);
uint8_t Bootloader_FlashNext(uint64_t data);
void    Bootloader_FlashEnd(void);

uint8_t Bootloader_GetProtectionStatus(void); 
uint8_t Bootloader_ConfigProtection(uint32_t protection);

uint8_t Bootloader_CheckSize(uint32_t appsize);
uint8_t Bootloader_VerifyChecksum(void);
uint8_t Bootloader_CheckForApplication(void);
void    Bootloader_JumpToApplication(void);
void    Bootloader_JumpToSysMem(void);

#endif /* __BOOTLOADER_H */