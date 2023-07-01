/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 10:24:09                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-07-01 19:31:46                              *
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

extern driver_status_t DRIVER_STATUS = DRIVER_STATUS_IS_NORMAL;
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
    if (EEPROM_INITIAL_ADDRESS <= EEPROM_LAST_LOCATION)
    {
        ((EEPROM->EEARL).reg) = ((uint8_t)(EEPROM_INITIAL_ADDRESS << EEPROM_ADDRESS_LEAST_BYTE));
        ((EEPROM->EEARH).reg) = ((uint8_t)(EEPROM_INITIAL_ADDRESS << EEPROM_ADDRESS_MOST_BYTE));
    }
    else
    {
        /* Update Driver Error value */
        DRIVER_STATUS = EEPROM_ADDRESS_NOT_AVAILABLE;
    }
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
    while (((((EEPROM->EECR).bits).EEWE) != EEPROM_DATA_REG_IS_AVAILABLE))
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
    if (address <= EEPROM_LAST_LOCATION)
    {
        /* Set the EEPROM Address at which data will be written */
        ((EEPROM->EEARL).reg) = ((uint8_t)(address << EEPROM_ADDRESS_LEAST_BYTE));
        ((EEPROM->EEARH).reg) = ((uint8_t)(address << EEPROM_ADDRESS_MOST_BYTE));

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
        /* Update Driver Error value */
        DRIVER_STATUS = EEPROM_ADDRESS_NOT_AVAILABLE;
    }

#elif OS == TIME_TRIGGER_OS
    /* Check if EEPROM is ready to be written */
    if (
        ((((EEPROM->EECR).bits).EEWE) == EEPROM_DATA_REG_IS_AVAILABLE)
#if BOOT_LOADER_USAGE == BOOT_LOADER_IS_USED
        /* Check if CPU finished programming the Flash */
        && (((SPMCR->bits).SPMEN) == EEPROM_WRITE_CONDITION)
#endif
    )
    {
        /* Disable Interrupts */
        ((SREG->bits).I) = GLOBAL_INTERRUPT_DISABLE;

        /* Check if the address in available EEPROM Space */
        if (address <= EEPROM_LAST_LOCATION)
        {
            /* Set the EEPROM Address at which data will be written */
            ((EEPROM->EEARL).reg) = ((uint8_t)(address << EEPROM_ADDRESS_LEAST_BYTE));
            ((EEPROM->EEARH).reg) = ((uint8_t)(address << EEPROM_ADDRESS_MOST_BYTE));

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
            /* Update Driver Error value */
            DRIVER_STATUS = EEPROM_ADDRESS_NOT_AVAILABLE;
        }
    }
#else
    /* DO Nothing */
#endif
}

/**
 * @brief This API is used to write more than byte of data in successive addresses in EEPROM.
 * @param base_address The start Address at which data will be written.
 * @param data A pointer to data that will be written in the given addresses in EEPROM.
 * @param length The length of data that wanted to be written in EEPROM.
 * @return The Actual size of data that has been written in EEPROM.
 */
uint16_t EEPROM_write_data(uint16_t base_address, uint8_t *data, uint16_t length)
{
    static uint16_t actual_length = EEPROM_NO_DATA;
    static uint16_t next_location = EEPROM_NO_ADDRESS;

/* Check which OS is used */
#if OS == SUPER_LOOP_OS

    /* Check if the location is available or not */
    while ((next_location <= EEPROM_LAST_LOCATION) && (base_address <= EEPROM_LAST_LOCATION))
    {
        /* Check if that is a new call */
        if (next_location == EEPROM_NO_ADDRESS)
        {
            /* Set next location by base address */
            next_location = base_address;

            /* Reset the actual length */
            actual_length = EEPROM_NO_DATA;
        }
        else
        {
            /* Do Nothing */
        }

        /* check if there is still  data not written yet */
        if (actual_length < length)
        {
            /* Write data of the given index */
            EEPROM_write_byte(next_location, data[actual_length]);

            /* Update next Location */
            next_location++;
            /* Update the actual length */
            actual_length++;
        }
        else
        {
            /* Reset the next location */
            next_location = EEPROM_NO_ADDRESS;

            /* Leave the loop */
            break;
        }
    }

    /* Check if the EEPROM reaches the end or not */
    if ((next_location > EEPROM_LAST_LOCATION) || (base_address > EEPROM_LAST_LOCATION))
    {
        /* Update Driver Error value */
        DRIVER_STATUS = EEPROM_ADDRESS_NOT_AVAILABLE;
    }
    else
    {
        /* All data is written */
        DRIVER_STATUS = EEPROM_IS_TOTALLY_WRITTEN;
    }

#elif OS == TIME_TRIGGER_OS
    /* Check if the location is available or not */
    if ((next_location <= EEPROM_LAST_LOCATION) && (base_address <= EEPROM_LAST_LOCATION) && (DRIVER_STATUS == DRIVER_STATUS_IS_NORMAL))
    {
        /* Check if that is a new call */
        if (next_location == EEPROM_NO_ADDRESS)
        {
            /* Set next location by base address */
            next_location = base_address;

            /* Reset the actual length */
            actual_length = EEPROM_NO_DATA;
        }
        else
        {
            /* Do Nothing */
        }

        /* check if there is still  data not written yet */
        if (actual_length < length)
        {

            /* Reset EEPROM Write Flag */
            EEPROM_WRITE_FLAG = EEPROM_NOT_WRITTEN;

            /* Write data of the given index */
            EEPROM_write_byte(next_location, data[actual_length]);

            if (EEPROM_WRITE_FLAG == EEPROM_IS_WRITTEN)
            {
                /* Update next Location */
                next_location++;
                /* Update the actual length */
                actual_length++;
            }
            else
            {
                /* Do Nothing */
            }
        }
        else
        {
            /* All data has been written */
            DRIVER_STATUS = EEPROM_IS_TOTALLY_WRITTEN;

            /* Reset the next location */
            next_location = EEPROM_NO_ADDRESS;
        }
    }
    else if ((next_location > EEPROM_LAST_LOCATION) || (base_address > EEPROM_LAST_LOCATION))
    {
        /* Update Driver Error value */
        DRIVER_STATUS = EEPROM_ADDRESS_NOT_AVAILABLE;
    }
    else
    {
        /* Do Nothing */
    }

#else
    /* Do Nothing */
#endif

    return actual_length;
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
