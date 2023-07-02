/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 12:07:12                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-07-02 12:43:00                              *
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

    /* EEPROM Status */
    EEPROM_ADDRESS_NOT_AVAILABLE,
    EEPROM_DATA_IS_WRITTEN,
    EEPROM_DATA_IS_NOT_COMPLETELY_WRITTEN,
    EEPROM_DATA_IS_READ,
    EEPROM_DATA_IS_NOT_COMPLETELY_READ,

    DRIVER_MAX_STATUS
} driver_status_t;

#endif