/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-07 22:37:53                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-08 00:20:00                              *
 * @FilePath              : MM_prog.c                                        *
 ****************************************************************************/

/**
 * @section Includes
 */

#include "../atmega32_reg.h"
#include "MM_int.h"

/**
 * @section Implementation
 */

/**
 * @brief This API is used to set MCU mode.
 * @param mode The mode which is set to MCU (NORMAL_MODE, IDLE_MODE, ADC_NOISE_REDUCTION_MODE,
 * PWR_DOWN_MODE, PWR_SAVE_MODE, STANDBY_MODE or EXTENDED_STANDBY_MODE)
 * @return The status of Mode Manager (DRIVER_IS_OK or VALUE_IS_NOT_EXISTED). 
 */
driver_status_t MM_set_mode(mode_t mode)
{
    driver_status_t MM_status = DRIVER_IS_OK;

    /* Check if the mode is existed or not */
    if(mode >= LAST_MODE)
    {
        MM_status = VALUE_IS_NOT_EXISTED;
    }
    /* Check if the mode is normal mode or not */
    else if(mode == NORMAL_MODE)
    {
        /* Disable Sleep Mode */
        ((MCUCR -> bits).SE) = (uint8_t)CLEAR_VALUE;
    }
    else
    {
        /* Set Selected Sleep Mode */
        ((MCUCR ->bits).SM) = (uint8_t)mode;

        /* Enable Sleep Mode */
        ((MCUCR -> bits).SE) = (uint8_t)SET_VALUE;

        /* Run Sleep Instruction */
        _SLEEP();

        /* Disable Sleep Mode */
        ((MCUCR -> bits).SE) = (uint8_t)CLEAR_VALUE;
    }

    /* Return Mode Manager status */
    return MM_status;
}

/**
 * @brief This API is used to get MCU mode.
 * @param mode A pointer to the MCU mode (NORMAL_MODE, IDLE_MODE, ADC_NOISE_REDUCTION_MODE,
 * PWR_DOWN_MODE, PWR_SAVE_MODE, STANDBY_MODE or EXTENDED_STANDBY_MODE)
 * @return the mode of MCU and
 * the status of Mode Manager (DRIVER_IS_OK or PTR_USED_IS_NULL_PTR).  
 */
driver_status_t MM_get_mode(mode_t * mode)
{
    driver_status_t MM_status = DRIVER_IS_OK;

    /* Check if the pointer is null */
    if(mode == NULL)
    {
        MM_status = PTR_USED_IS_NULL_PTR;
    }
    else
    {
        /* Check if the mode is normal */
        if(((MCUCR -> bits).SE) == (uint8_t)CLEAR_VALUE)
        {
            /* Set Mode to Normal Mode */
            *mode = NORMAL_MODE;
        }
        else
        {
            /* Update mode Value */
            *mode = (mode_t)((MCUCR ->bits).SM);
        }
    }

    /* Return Mode Manager status */
    return MM_status;
}