/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-07 22:36:20                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-07 23:05:59                              *
 * @FilePath              : MM_int.h                                         *
 ****************************************************************************/

#ifndef MM_MM_INT_H_
#define MM_MM_INT_H_

/**
 * @section Includes
 */

#include "../../MC_driver.h"

/**
 * @section Typedefs
 */

/**
 * @brief Atmega32 Sleep Modes
 */
typedef enum
{
    IDLE_MODE = (uint8_t)0      , /* That mode halts CPU_CLK and FLASH CLK                                                  */
    ADC_NOISE_REDUCTION_MODE    , /* That mode halts CPU_CLK, FLAH_CLK and IO_CLK                                           */
    PWR_DOWN_MODE               , /* That mode halts all generated clocks                                                   */
    PWR_SAVE_MODE               , /* That mode halts all generated clocks except ASY_CLK                                    */
    STANDBY_MODE = (uint8_t)6   , /* That mode halts all generated clocks and keeps main oscillator working                 */
    EXTENDED_STANDBY_MODE       , /* That mode halts all generated clocks except ASY_CLK and keeps main oscillator working  */
    NORMAL_MODE                 , /* That mode allows all clocks to work                                                    */
    LAST_MODE
}mode_t;

/**
 * @section APIs
 */

driver_status_t MM_set_mode   (mode_t mode);
driver_status_t MM_get_mode   (mode_t * mode);

#endif