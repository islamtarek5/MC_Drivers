/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-06-27 12:07:12                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2024-01-11 11:09:44                              *
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
#define SET_VALUE   1U

/**
 * @brief Global Interrupt
 */
#define GLOBAL_INTERRUPT_DISABLE 0U
#define GLOBAL_INTERRUPT_ENABLE  1U

/**
 * @brief NULL Pointer
 */
#define NULL_PTR ((void*)0)

/**
 * @brief Bits Manipulation. 
 */
#define GET_BIT(var, bit)  (((var) >> bit) & SET_VALUE)

/**
 * @brief Bits Positions.
*/
#define BIT0        0U
#define BIT1        1U
#define BIT2        2U
#define BIT3        3U
#define BIT4        4U
#define BIT5        5U
#define BIT6        6U
#define BIT7        7U

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
    VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER,
    VALUE_IS_NOT_COMPATIBLE_WITH_OTHER_CONFIGURATIONS,
    VALUE_IS_RESERVED,

    /* EEPROM Status */
    EEPROM_ADDRESS_NOT_AVAILABLE,
    EEPROM_DATA_IS_WRITTEN,
    EEPROM_DATA_IS_NOT_COMPLETELY_WRITTEN,
    EEPROM_DATA_IS_READ,
    EEPROM_DATA_IS_NOT_COMPLETELY_READ,

    DRIVER_MAX_STATUS
} driver_status_t;

#endif
