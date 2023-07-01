/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 12:07:12                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-07-01 20:01:50                              *
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
    DRIVER_STATUS_IS_NORMAL = (uint8_t)0,

    DRIVER_MAX_STATUS
} driver_status_t;

#endif