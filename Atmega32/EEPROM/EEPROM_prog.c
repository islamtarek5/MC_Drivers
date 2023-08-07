/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-06-27 10:24:09                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-07 23:42:17                              *
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
 * @section Implementation
 */

/**
 * @brief This API is used to Initialize EEPROM with given Configurations (Address, Interrupt state).
 * @return The status of EEPROM (DRIVER_IS_OK or EEPROM_ADDRESS_NOT_AVAILABLE).
 */
driver_status_t EEPROM_init(void)
{
    driver_status_t EEPROM_status = DRIVER_IS_OK;

    /* Check if location is available or not */
    if (EEPROM_INITIAL_ADDRESS <= EEPROM_LAST_LOCATION)
    {
        /* Set EEPROM Initial Address */
        ((EEPROM->EEARL).reg) = ((uint8_t)(EEPROM_INITIAL_ADDRESS >> EEPROM_ADDRESS_LEAST_BYTE));
        ((EEPROM->EEARH).reg) = ((uint8_t)(EEPROM_INITIAL_ADDRESS >> EEPROM_ADDRESS_MOST_BYTE));
    }
    else
    {
        /* EEPROM Address is not available */
        EEPROM_status = EEPROM_ADDRESS_NOT_AVAILABLE;
    }
    /* Set EEPROM Ready Interrupt State */
    (((EEPROM->EECR).bits).EERIE) = EEPROM_INTERRUPT;

    /* Return EEPROM status */
    return EEPROM_status;
}

/**
 * @brief This API is used to write byte of data in specific address in EEPROM.
 * @param address The Address indicates the location of EEPROM at which data will be written (must be >= 0 and <= 1023).
 * @param byte Ths Byte of data that will be written in the given address.
 * @return The status of EEPROM (EEPROM_ADDRESS_NOT_AVAILABLE or EEPROM_DATA_IS_WRITTEN).
 */
driver_status_t EEPROM_write_byte(uint16_t address, uint8_t byte)
{
    driver_status_t EEPROM_status = DRIVER_IS_OK;
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
#endif
    /* Disable Interrupts */
    ((SREG->bits).I) = GLOBAL_INTERRUPT_DISABLE;

    /* Check if the address in available EEPROM Space */
    if (address <= EEPROM_LAST_LOCATION)
    {
        /* Set the EEPROM Address at which data will be written */
        ((EEPROM->EEARL).reg) = ((uint8_t)(address >> EEPROM_ADDRESS_LEAST_BYTE));
        ((EEPROM->EEARH).reg) = ((uint8_t)(address >> EEPROM_ADDRESS_MOST_BYTE));

        /* Set the EEPROM Data */
        ((EEPROM->EEDR).reg) = byte;

        /* Set EEPROM Master Write Enable */
        (((EEPROM->EECR).bits).EEMWE) = SET_VALUE;

        /* Set EEPROM Write Enable */
        ((EEPROM->EECR).reg) = EEPROM_WRITE_ENABLE_CONDITION;

        /* Enable Interrupts */
        ((SREG->bits).I) = GLOBAL_INTERRUPT_ENABLE;

        /* Data is written */
        EEPROM_status = EEPROM_DATA_IS_WRITTEN;
    }
    else
    {
        /* Update Driver Error value */
        EEPROM_status = EEPROM_ADDRESS_NOT_AVAILABLE;
    }
#if OS == TIME_TRIGGER_OS
}
#endif

/* Return EEPROM status */
return EEPROM_status;
}

/**
 * @brief This API is used to write more than byte of data in successive addresses in EEPROM.
 * @param base_address The start Address at which data will be written.
 * @param data A pointer to data that will be written in the given addresses in EEPROM.
 * @param length The length of data that wanted to be written in EEPROM.
 * @param actual_length A pointer to length of data that has been actually written in EEPROM.
 * @return The Actual length of data that has been written in EEPROM and
 * the status of EEPROM (EEPROM_DATA_IS_WRITTEN, EEPROM_ADDRESS_NOT_AVAILABLE, EEPROM_DATA_IS_NOT_COMPLETELY_WRITTEN or PTR_USED_IS_NULL_PTR).
 */
driver_status_t EEPROM_write_data(uint16_t base_address, uint8_t *data, uint16_t length, uint16_t *actual_length)
{
    driver_status_t EEPROM_status = DRIVER_IS_OK;
    static uint16_t next_location = EEPROM_NO_ADDRESS;

    /* Check if the pointers are null */
    if ((data == NULL) || (actual_length == NULL))
    {
        /* Set EEPROM status to NULL Pointer */
        EEPROM_status = PTR_USED_IS_NULL_PTR;
    }
    else
    {
        /* Check if the Base Address is available or not */
        if (base_address <= EEPROM_LAST_LOCATION)
        {
/* Check which OS is used */
#if OS == SUPER_LOOP_OS
            while
#elif OS == TIME_TRIGGER_OS
                if
#endif
                /* Check if there is still data need to be written */
                ((*actual_length < length) && (next_location <= EEPROM_LAST_LOCATION))
            {
                /* Check if that is a new data block */
                if (*actual_length == EEPROM_NO_DATA)
                {
                    /* Set next location by base address */
                    next_location = base_address;
                }
                else
                {
                    /* Do Nothing */
                }
                /* Write data of the given index */
                EEPROM_status = EEPROM_write_byte(next_location, data[*actual_length]);

                /* Check if the Data is written or not */
                if (EEPROM_status == EEPROM_DATA_IS_WRITTEN)
                {
                    /* Update next Location */
                    next_location++;
                    /* Update the actual length */
                    (*actual_length)++;
                }
                else
                {
                    /* Do Nothing */
                }
            }
#if OS == TIME_TRIGGER_OS
            else
#endif
                if (*actual_length >= length)
            {
                /* All Data has been written */
                EEPROM_status = EEPROM_DATA_IS_WRITTEN;
            }
            else
            {
                /* Not All Data has been written */
                EEPROM_status = EEPROM_DATA_IS_NOT_COMPLETELY_WRITTEN;
            }
        }
        else
        {
            /* EEPROM Base Address is not available */
            EEPROM_status = EEPROM_ADDRESS_NOT_AVAILABLE;
        }
    }

    /* Return EEPROM status */
    return EEPROM_status;
}

/**
 * @brief This API is used to read 1 byte or more successive bytes from EEPROM.
 * @param base_address The start Address from which data will be read.
 * @param data A pointer to data that will be read from the given addresses in EEPROM.
 * @param length The length of data that wanted to be read from EEPROM.
 * @param actual_length A pointer to length of data that has been actually read from EEPROM.
 * @return The Actual length of data that has been read in EEPROM and
 * the status of EEPROM (EEPROM_DATA_IS_READ, EEPROM_ADDRESS_NOT_AVAILABLE, EEPROM_DATA_IS_NOT_COMPLETELY_READ or PTR_USED_IS_NULL_PTR).
 */
driver_status_t EEPROM_read_data(uint16_t base_address, uint8_t *data, uint16_t length, uint16_t *actual_length)
{
    driver_status_t EEPROM_status = DRIVER_IS_OK;
    static uint16_t next_location = EEPROM_NO_ADDRESS;

    /* Check if the pointers are null */
    if ((data == NULL) || (actual_length == NULL))
    {
        /* Set EEPROM status to NULL Pointer */
        EEPROM_status = PTR_USED_IS_NULL_PTR;
    }
    else
    {
        /* Check if the Base Address is available or not */
        if (base_address <= EEPROM_LAST_LOCATION)
        {
/* Check which OS is used */
#if OS == SUPER_LOOP_OS
            while
#elif OS == TIME_TRIGGER_OS
            if
#endif
                /* Check if there is still data need to be read and
                there is still locations available in EEPROM */
                ((*actual_length < length) && (next_location <= EEPROM_LAST_LOCATION))
            {
                /* Check if that is a new data block */
                if (*actual_length == EEPROM_NO_DATA)
                {
                    /* Set next location by base address */
                    next_location = base_address;
                }
                else
                {
                    /* Do Nothing */
                }

                /* Make sure that there is no wirting process is going on */
#if OS == SUPER_LOOP_OS
                while (((((EEPROM->EECR).bits).EEWE) != EEPROM_DATA_REG_IS_AVAILABLE))
                    ;
#elif OS == TIME_TRIGGER_OS
                if (((((EEPROM->EECR).bits).EEWE) == EEPROM_DATA_REG_IS_AVAILABLE))
                {
#endif
                /* Set the Address from which data will be read */
                ((EEPROM->EEARL).reg) = ((uint8_t)(next_location >> EEPROM_ADDRESS_LEAST_BYTE));
                ((EEPROM->EEARH).reg) = ((uint8_t)(next_location >> EEPROM_ADDRESS_MOST_BYTE));

                /* Enable EEPROM Read */
                (((EEPROM->EECR).bits).EERE) = SET_VALUE;

                /* Store the data */
                data[*actual_length] = ((EEPROM->EEDR).reg);

                /* Update next Location */
                next_location++;

                /* Update the actual length */
                (*actual_length)++;
#if OS == TIME_TRIGGER_OS
                }
                else
                {
                    /* Do Nothing */
                }
#endif
            }
#if OS == TIME_TRIGGER_OS
            else
#endif
            if (*actual_length >= length)
            {
                /* All Data has been read */
                EEPROM_status = EEPROM_DATA_IS_READ;
            }
            else
            {
                /* Not All Data has been read */
                EEPROM_status = EEPROM_DATA_IS_NOT_COMPLETELY_READ;
            }
        }
        else
        {
            /* EEPROM Base Address is not available */
            EEPROM_status = EEPROM_ADDRESS_NOT_AVAILABLE;
        }
    }

    /* Return EEPROM status */
    return EEPROM_status;
}

/**
 * @brief This API is used to Enable EEPROM Interrupt.
 */
void EEPROM_enable_interrupt(void)
{
    /* Enable Global Interrupt */
    ((SREG->bits).I) = GLOBAL_INTERRUPT_ENABLE;

    /* Enable EEPROM Interrupt */
    (((EEPROM->EECR).bits).EERIE) = EERPOM_INTERRUPT_ENABLE;
}

/**
 * @brief This API is used to disable EEPROM Interrupt.
 */
void EEPROM_disable_interrupt(void)
{
    /* Disable EEPROM interrupt */
    (((EEPROM->EECR).bits).EERIE) = EEPROM_INTERRUPT_DISABLE;
}
