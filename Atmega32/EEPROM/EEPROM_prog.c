/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 10:24:09                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-27 15:34:18                              *
 * @FilePath              : EEPROM_prog.c                                    *
 ****************************************************************************/

/**
 * @section Includes
 */

#include "../atmega32_reg.h"
#include "EEPROM_int.h"
#include "EEPROM_priv.h"
#include "EEPROM_cfg.h"

/**
 * @section Global Variables
 */

extern driver_err_t DRIVER_ERROR = DRIVER_WITHOUT_ERRORS;
static uint8_t EEPROM_WRITE_FLAG = EEPROM_NOT_WRITTEN;

/**
 * @section Implementation
 */

/**
 * @brief This API is used to Initialize EEPROM with given Configurations (Address, Interrupt state).
 */
void EEPROM_init(void)
{
    /* Set EEPROM Initial Address */
    ((EEPROM->EEARL).reg) = ((uint8_t)(EEPROM_INITIAL_ADDRESS << ADDRESS_LEAST));
    ((EEPROM->EEARH).reg) = ((uint8_t)(EEPROM_INITIAL_ADDRESS << ADDRESS_MOST));

    /* Set EEPROM Ready Interrupt State */
    (((EEPROM->EECR).bits).EERIE) = EEPROM_INTERRUPT;
}

/**
 * @brief This API is used to write byte of data in specific address in EEPROM.
 * @param address The Address indicates the location of EEPROM at which data will be written (must be >= 0 and <= 1023).
 * @param byte Ths Byte of data that will be written in the given address.
 */
void EEPROM_write_byte(uint16_t address, uint8_t byte)
{
/* Check which OS is used */
#if OS == SUPER_LOOP_OS
    /* Wait until EEPROM is ready to be written */
    while (((((EEPROM->EECR).bits).EEWE) != EEPROM_WRITE_CONDITION))
    {
#if BOOT_LOADER_USAGE == BOOT_LOADER_IS_USED
        /* Wait until CPU finished programming the Flash */
        while (((SPMCR->bits).SPMEN) != EEPROM_WRITE_CONDITION)
            ;
#endif
    }
    /* Disable Interrupts */
    ((SREG->bits).I) = GLOBAL_INTERRUPT_DISABLE;

    /* Check if the address in available EEPROM Space */
    if (address >= EEPROM_FIRST_LOCATION && address <= EEPROM_LAST_LOCATION)
    {
        /* Set the EEPROM Address at which data will be written */
        ((EEPROM->EEARL).reg) = ((uint8_t)(address << ADDRESS_LEAST));
        ((EEPROM->EEARH).reg) = ((uint8_t)(address << ADDRESS_MOST));

        /* Set the EEPROM Data */
        ((EEPROM->EEDR).reg) = byte;

        /* Set EEPROM Master Write Enable */
        (((EEPROM->EECR).bits).EEMWE) = SET_VALUE;

        /* Set EEPROM Write Enable */
        (((EEPROM->EECR).bits).EEMWE) = SET_VALUE;

        /* Enable Interrupts */
        ((SREG->bits).I) = GLOBAL_INTERRUPT_ENABLE;
    }
    else
    {
        DRIVER_ERROR = DRIVER_ADDRESS_NOT_AVAILABLE;
    }

#elif OS == TIME_TRIGGER_OS
    /* Check if EEPROM is ready to be written */
    if (
        ((((EEPROM->EECR).bits).EEWE) == EEPROM_WRITE_CONDITION)
#if BOOT_LOADER_USAGE == BOOT_LOADER_IS_USED
        /* Check if CPU finished programming the Flash */
        && (((SPMCR->bits).SPMEN) == EEPROM_WRITE_CONDITION)
#endif
    )
    {
        /* Disable Interrupts */
        ((SREG->bits).I) = GLOBAL_INTERRUPT_DISABLE;

        /* Check if the address in available EEPROM Space */
        if (address >= EEPROM_FIRST_LOCATION && address <= EEPROM_LAST_LOCATION)
        {
            /* Set the EEPROM Address at which data will be written */
            ((EEPROM->EEARL).reg) = ((uint8_t)(address << ADDRESS_LEAST));
            ((EEPROM->EEARH).reg) = ((uint8_t)(address << ADDRESS_MOST));

            /* Set the EEPROM Data */
            ((EEPROM->EEDR).reg) = byte;

            /* Set EEPROM Master Write Enable */
            (((EEPROM->EECR).bits).EEMWE) = SET_VALUE;

            /* Set EEPROM Write Enable */
            (((EEPROM->EECR).bits).EEMWE) = SET_VALUE;

            /* Enable Interrupts */
            ((SREG->bits).I) = GLOBAL_INTERRUPT_ENABLE;

            /* Update Write complere flag */
            EEPROM_WRITE_FLAG = EEPROM_IS_WRITTEN;
        }
        else
        {
            DRIVER_ERROR = DRIVER_ADDRESS_NOT_AVAILABLE;
        }
    }
#else
    /* DO Nothing */
#endif
}

uint16_t EEPROM_write_data(uint16_t base_address, uint8_t *data, uint16_t length)
{
}

uint16_t EEPROM_read_data(uint16_t base_address, uint8_t *data, uint16_t length)
{
}

void EEPROM_enable_interrupt(void)
{
}

void EEPROM_disable_interrupt(void)
{
}
