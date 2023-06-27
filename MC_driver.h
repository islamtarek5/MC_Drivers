/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 12:07:12                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-27 16:23:34                              *
 * @FilePath              : MC_driver.h                                      *
 ****************************************************************************/

#ifndef MC_DRIVERS_MC_DRIVER_H_
#define MC_DRIVERS_MC_DRIVER_H_

/**
 * @section Definitions
*/

/**
 * @brief Bit Values
 */

#define CLEAR_VALUE                 0U
#define SET_VALUE                   1U

/**
 * @brief Global Interrupt
 */

#define GLOBAL_INTERRUPT_DISABLE    0U
#define GLOBAL_INTERRUPT_ENABLE     1U

/**
 * @section Typedefs
 */

/**
 * @brief Driver Errors
 */

typedef enum
{
    DRIVER_WITHOUT_ERRORS = (uint8_t)0,
    DRIVER_ERROR_ADDRESS_NOT_AVAILABLE,

    DRIVER_MAX_ERROR
}driver_err_t;

#endif 