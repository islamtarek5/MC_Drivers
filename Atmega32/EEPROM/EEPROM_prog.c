/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 10:24:09                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-27 12:31:28                              *
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

void EEPROM_write_byte(uint16_t address, uint8_t byte)
{

}

void EEPROM_write_data(uint16_t base_address, uint8_t * data, uint16_t length)
{

}

void EEPROM_read_data(uint16_t base_address, uint8_t * data, uint16_t length)
{

}

void EEPROM_enable_interrupt(void)
{

}

void EEPROM_disable_interrupt(void)
{
    
}
