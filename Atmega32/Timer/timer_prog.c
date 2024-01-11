/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2024-01-09 17:07:55                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2024-01-11 13:13:44                              *
 * @FilePath              : timer_prog.c                                     *
 ****************************************************************************/

/**
 * @section Includes
 */

#include "../atmega32_reg.h"
#include "timer_int.h"
#include "timer_priv.h"
#include "Timer_cfg.h"
#include "../GPIO/GPIO_int.h"

/**
 * @section Global Variables
 */

/**
 * @brief Callback pointers to functions.
 */
timer_P2VCbFunc_t TIMER0_OVF_CB = NULL_PTR;
timer_P2VCbFunc_t TIMER0_CM_CB = NULL_PTR;

/**
 * @section APIs Implementation.
 */

/**
 * @brief This function is used to set Timer Configurations.
 * @param timer_config Is pointer to timer configuration strtucture.
 * @note Configurations of Timer are {Timer_ID, Timer_Mode, Timer_PinFunction, Timer_Technique}.
 * @return The Status of API (DRIVER_IS_OK, VALUE_IS_RESERVED, VALUE_IS_NOT_COMPATIBLE_WITH_OTHER_CONFIGURATIONS, VALUE_IS_NOT_EXISTED, VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER, PTR_USED_IS_NULL_PTR).
 * @example of Timer Configurations (TIMER_0, TIMER_NORMAL_MODE, TIMER_PIN_NOT_USED, TIMER_BUSY_WAIT_TECH).
 */
driver_status_t timer_init(timer_cfg_S *timer_config)
{
    driver_status_t Timer_status = DRIVER_IS_OK;

    /* Check if the Pointer is null pointer */
    if (timer_config != NULL_PTR)
    {
        /* Disable All Interrupts */
        TIMSK->reg = CLEAR_VALUE;
        
        /* Check if Timer ID is existing or not */
        if ((timer_config->id) < TIMER_MAX_ID)
        {
            if (timer_config->id == TIMER_0)
            {
                /* Check if Timer Mode is existing for Timer 0 or not */
                if (timer_config->mode == TIMER_NORMAL_MODE || timer_config->mode == TIMER_PWM_PPHASE_CORRECT_MODE || timer_config->mode == TIMER_COMPARE_MATCH_MODE || timer_config->mode == TIMER_FAST_PWM_MODE)
                {
                    /* Set the Selected Mode */
                    TCCR0->bits.WGM0 = GET_BIT((timer_config->mode), BIT0);
                    TCCR0->bits.WGM1 = GET_BIT((timer_config->mode), BIT3);

                    /* Check if the Timer Pin function is existing or not */
                    if (timer_config->pinFunc < TIMER_MAX_PIN_FUNC)
                    {
                        /* Check if the Pin Function value is the reserved value or not */
                        if (((timer_config->mode == TIMER_FAST_PWM_MODE) || (timer_config->mode == TIMER_PWM_PPHASE_CORRECT_MODE)) && (timer_config->pinFunc == TIMER_RESERVED_PIN_FUNC_VALUE))
                        {
                            /* Timer Pin function Value is reserved*/
                            Timer_status = VALUE_IS_RESERVED;
                        }
                        /* Check if The Pin function Value is compatible with the selected mode or not */
                        else if (((timer_config->mode == TIMER_NORMAL_MODE) && (timer_config->pinFunc != TIMER_PIN_NOT_USED)) || ((timer_config->mode == TIMER_COMPARE_MATCH_MODE) && (timer_config->pinFunc > TIMER_SET_PIN)) || (((timer_config->mode == TIMER_FAST_PWM_MODE) || (timer_config->mode == TIMER_PWM_PPHASE_CORRECT_MODE)) && ((timer_config->pinFunc >= TIMER_TOGGLE_PIN) && (timer_config->pinFunc <= TIMER_SET_PIN))))
                        {
                            /* Pin Function Value isn't compatible with selected mode */
                            Timer_status = VALUE_IS_NOT_COMPATIBLE_WITH_OTHER_CONFIGURATIONS;
                        }
                        /* Pin Function is not reserved and is compatible with the selected mode */
                        else
                        {
                            /* Check if Pin Function Value will be within more than 2 bits */
                            if (timer_config->pinFunc > MAX_PIN_FUNCTION_ACCEPTED_VALUE)
                            {
                                /* Update Pin Function Value to be within 2 bits */
                                timer_config->pinFunc -= MAX_PIN_FUNCTION_ACCEPTED_VALUE;
                            }
                            else
                            {
                                /* Do Nothing */
                            }
                            /* Check if the Time Pin is used or not */
                            if (timer_config->pinFunc != TIMER_PIN_NOT_USED)
                            {
                                /* Set Timer Pin direction to output */
                                GPIO_set_pin_mode(PORT_B, PIN_3, PIN_OUTPUT);
                            }
                            else
                            {
                                /* Do Nothing */
                            }

                            /* Set the selected Pin Function*/
                            TCCR0->bits.COM0 = GET_BIT((timer_config->pinFunc), BIT0);
                            TCCR0->bits.COM1 = GET_BIT((timer_config->pinFunc), BIT1);
                        }
                    }
                    else
                    {
                        /* Timer Pin Function is Not Existing */
                        Timer_status = VALUE_IS_NOT_EXISTED;
                    }
                }
                else
                {
                    /* Mode is not available for timer 0 */
                    Timer_status = VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER;
                }
            }
        }
        else
        {
            /* Timer ID is not existing */
            Timer_status = VALUE_IS_NOT_EXISTED;
        }
    }
    else
    {
        /* Pointer to Timer configuration structure is Null Pointer */
        Timer_status = PTR_USED_IS_NULL_PTR;
    }

    /* Return Timer Status Value */
    return Timer_status;
}

driver_status_t timer_set_inerrupt_status(timer_id_t, timer_interrupt_status_t);
driver_status_t timer_set_callback_function(timer_id_t, timer_P2VCbFunc_t);
driver_status_t timer_start(timer_id_t);
driver_status_t timer_stop(timer_id_t);
