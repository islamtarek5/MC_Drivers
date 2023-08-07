/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-06-27 12:07:12                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-08 00:22:32                              *
 * @FilePath              : MC_driver.h                                      *
 ****************************************************************************/

#ifndef MC_DRIVERS_MC_DRIVER_H_
#define MC_DRIVERS_MC_DRIVER_H_

/**
 * @section Includes
 */

#include <stdint.h>

/**
 * @section Definitions
 */

/**
 * @brief Bit Values
 */

#define CLEAR_VALUE 0U
#define SET_VALUE 1U

/**
 * @brief Global Interrupt
 */

#define GLOBAL_INTERRUPT_DISABLE 0U
#define GLOBAL_INTERRUPT_ENABLE 1U

/**
 * @section Typedefs
 */

/**
 * @brief Driver Errors
 */

typedef enum
{
    DRIVER_IS_OK = (uint8_t)0,
    VALUE_IS_NOT_EXISTED,
    PTR_USED_IS_NULL_PTR,

    /* EEPROM Status */
    EEPROM_ADDRESS_NOT_AVAILABLE,
    EEPROM_DATA_IS_WRITTEN,
    EEPROM_DATA_IS_NOT_COMPLETELY_WRITTEN,
    EEPROM_DATA_IS_READ,
    EEPROM_DATA_IS_NOT_COMPLETELY_READ,

    DRIVER_MAX_STATUS
} driver_status_t;

#endif