/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2024-01-09 17:07:55                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2024-01-18 13:39:25                              *
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
 * @section Macros.
 */

/**
 * @brief Values For Busy Wait Code style.
 */
#define TIMER_BUSY_WAIT_0 0U
#define TIMER_BUSY_WAIT_1 1U

/**
 * @brief
 * Configuration for Busy Wait Code Style.
 */
#define TIMER_BUSY_WAIT_METHOD TIMER_BUSY_WAIT_0

/**
 * @section Private Data types.
 */

/**
 * @brief Timer Info.
 */
typedef struct
{
    timer_cfg_S timer_cfg;
    timer_interrupt_status_t interrupt_status;
} timer_info_S;

/**
 * @section Global Variables
 */

/**
 * @brief Callback pointers to functions.
 */
static timer_P2VCbFunc_t TIMER_OVF_CB_ARR[TIMER_MAX_ID] = {NULL_PTR, NULL_PTR, NULL_PTR};
static timer_P2VCbFunc_t TIMER_CM_CB_ARR[TIMER_MAX_ID] = {NULL_PTR, NULL_PTR, NULL_PTR};

/**
 * @brief Number of OVFs.
 */
static uint32_t TIMER_COUNTs[TIMER_MAX_ID];

/**
 * @brief Timer initial Value
 */
static uint16_t TIMER_INITIAL_VALUE[TIMER_MAX_ID];

/**
 * @brief Timer Number of required OVFs.
 */
static uint8_t TIMER_REQUIRED_OVFs[TIMER_MAX_ID];

/**
 * @brief Maximum Timer Counts.
 */
static const uint16_t TIMER_MAX_COUNT_VALUE[TIMER_MAX_ID] =
    {
        TIMER_0_MAX_COUNT_VALUE,
        TIMER_1_MAX_COUNT_VALUE,
        TIMER_2_MAX_COUNT_VALUE};

/**
 * @brief Timers'Configurations Array.
 */
static timer_info_S TIMER_INFO_ARR[TIMER_MAX_ID] =
    {
        {{TIMER_MAX_ID, TIMER_MAX_MODE, TIMER_MAX_PIN_FUNC, TIMER_MAX_TECH}, TIMER_MAX_INTERRRUPT_STATE},
        {{TIMER_MAX_ID, TIMER_MAX_MODE, TIMER_MAX_PIN_FUNC, TIMER_MAX_TECH}, TIMER_MAX_INTERRRUPT_STATE},
        {{TIMER_MAX_ID, TIMER_MAX_MODE, TIMER_MAX_PIN_FUNC, TIMER_MAX_TECH}, TIMER_MAX_INTERRRUPT_STATE}};

/**
 * @section Static Functions Prototypes
 */

static void timer_calculations(timer_id_t);
static driver_status_t timer_busy_wait(timer_id_t);

/**
 * @section APIs Implementation.
 */

/**
 * @brief This function is used to set Timer Configurations.
 * @param timer_config Is pointer to timer configuration strtucture.
 * @note Configurations of Timer are {Timer_ID, Timer_Mode, Timer_PinFunction, Timer_Technique}.
 * @return The status of API (DRIVER_IS_OK, VALUE_IS_RESERVED, VALUE_IS_NOT_COMPATIBLE_WITH_OTHER_CONFIGURATIONS, VALUE_IS_NOT_EXISTED, VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER, PTR_USED_IS_NULL_PTR).
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
            /* Check if the timer used is Timer0 or  Timer2 */
            if ((timer_config->id == TIMER_0) || (timer_config->id == TIMER_2))
            {
                /* Check if Timer Mode is existing for Timers 0,2 or not */
                if (timer_config->mode == TIMER_NORMAL_MODE || timer_config->mode == TIMER_PWM_PPHASE_CORRECT_MODE || timer_config->mode == TIMER_COMPARE_MATCH_MODE || timer_config->mode == TIMER_FAST_PWM_MODE)
                {
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

                            /* Update Timer Info */
                            ((TIMER_INFO_ARR[timer_config->id]).timer_cfg).id = timer_config->id;
                            ((TIMER_INFO_ARR[timer_config->id]).timer_cfg).mode = timer_config->mode;
                            ((TIMER_INFO_ARR[timer_config->id]).timer_cfg).pinFunc = timer_config->pinFunc;
                            ((TIMER_INFO_ARR[timer_config->id]).timer_cfg).tech = timer_config->tech;
                        }
                        /* Check which Timer is used (Timer0 or Timer2) */
                        if (timer_config->id == TIMER_0)
                        {
                            /* Set the Selected Mode */
                            TCCR0->bits.WGM0 = GET_BIT((timer_config->mode), BIT0);
                            TCCR0->bits.WGM1 = GET_BIT((timer_config->mode), BIT3);

                            /* Set the selected Pin Function*/
                            TCCR0->bits.COM0 = GET_BIT((timer_config->pinFunc), BIT0);
                            TCCR0->bits.COM1 = GET_BIT((timer_config->pinFunc), BIT1);

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
                        }
                        else
                        {
                            // TODO: This section will be added with Timer2 Implementation.
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
            else
            {
                // TODO: This section will be added with Timer1 Implementation.
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

/**
 * @brief This API is used to set the Interrupt Status (Enable, Disable).
 * @param ID is the ID of the Timer whose Interrupt status will be set.
 * @param INT_status is the Interrupt Status which will be used (TIMER_DISABLE_ALL_INTERRUPTS, TIMER_ENABLE_OVERFLOW_INERRUPT, TIMER_ENABLE_COMPARE_MATCH_INTERRUPT, TIMER_ENABLE_ALL_INTERRUPTS).
 * @return The status of API (DRIVER_IS_OK, VALUE_IS_NOT_COMPATIBLE_WITH_OTHER_CONFIGURATIONS, VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER, VALUE_IS_NOT_EXISTED).
 */
driver_status_t timer_set_inerrupt_status(timer_id_t ID, timer_interrupt_status_t INT_status)
{
    driver_status_t timer_status = DRIVER_IS_OK;

    /* Check if the Timer ID is existing or not */
    if (ID < TIMER_MAX_ID)
    {
        if (ID == TIMER_0 || ID == TIMER_2)
        {
            /* Check if the Interrupt status is existing for Timers 0, 2 or not */
            if ((INT_status <= TIMER_ENABLE_BOTH_OVF_AND_CM_INTERRUPTS) && ((TIMER_INFO_ARR[ID].timer_cfg).tech == TIMER_INTERRUPT_TECH))
            {
                /* Update Timer Info */
                TIMER_INFO_ARR[ID].interrupt_status = INT_status;

                /* Check which Timer is used (Timer0 or Timer2) */
                if (ID == TIMER_0)
                {
                    /* Set The selected interrupt status */
                    TIMSK->bits.TOIE0 = GET_BIT(INT_status, BIT0);
                    TIMSK->bits.OCIE0 = GET_BIT(INT_status, BIT1);
                }
                else
                {
                    // TODO: This section will be added with Timer2 Implementation.
                }
            }
            /* Check if the Configurations are Compatible or not */
            else if (((TIMER_INFO_ARR[ID].timer_cfg).tech == TIMER_BUSY_WAIT_TECH) && (INT_status != TIMER_DISABLE_ALL_INTERRUPTS))
            {
                /* Timer Interrupts can't be used with busy wait technique */
                timer_status = VALUE_IS_NOT_COMPATIBLE_WITH_OTHER_CONFIGURATIONS;
            }
            /* Check if the Technique selected is existing or not */
            else if ((TIMER_INFO_ARR[ID].timer_cfg).tech >= TIMER_MAX_TECH)
            {
                /* Timer Technique which is chosed isn't existing */
                timer_status = VALUE_IS_NOT_EXISTED;
            }
            else
            {
                /* This Value is not accepted for Timers 0, 2*/
                timer_status = VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER;
            }
        }
        else
        {
            // TODO: This section will be added with Timer1 Implementation.
        }
    }
    else
    {
        /* Timer ID isn't Existing */
        timer_status = VALUE_IS_NOT_EXISTED;
    }

    /* Return Timer Status Value */
    return timer_status;
}

/**
 * @brief This API is used to set Callback function.
 * @param ID is the ID of Timer whose callback function will be set. 
 * @param cb_type is the Type of callback function (TIMER_OVF_CB, TIMER_CM_CB).
 * @param P2callback is function pointer to callback function.
 * @return The status of the API (DRIVER_IS_OK, PTR_USED_IS_NULL_PTR or VALUE_IS_NOT_EXISTED)
 */
driver_status_t timer_set_callback_function(timer_id_t ID, timer_cb_t cb_type, timer_P2VCbFunc_t P2callback)
{
    driver_status_t timer_status = DRIVER_IS_OK;

    /* Check if Timer ID is existing or not */
    if (ID < TIMER_MAX_ID)
    {
        /* Check if the Pointer to callback function is null pointer */
        if (P2callback != NULL_PTR)
        {
            /* Check if the Callback is OverFlow callback */
            if (cb_type == TIMER_OVF_CB)
            {
                /* Set OVF Callback function */
                TIMER_OVF_CB_ARR[ID] = P2callback;
            }
            /* Check if the Callback is compare match callback */
            else if (cb_type == TIMER_CM_CB)
            {
                /* Set CM Callback function */
                TIMER_CM_CB_ARR[ID] = P2callback;
            }
            else
            {
                // TODO: This Section will be added with Timer1 Implementation
            }
        }
        else
        {
            /* Callback Function Pointer is NULL Pointer */
            timer_status = PTR_USED_IS_NULL_PTR;
        }
    }
    else
    {
        /* Timer ID isn't existing */
        timer_status = VALUE_IS_NOT_EXISTED;
    }

    /* Return Timer Status Value */
    return timer_status;
}

/**
 * @brief This Static API is used to calculate number of overflows and Timer Initial value.
 * @param ID The ID of used Timer.
 */
static void timer_calculations(timer_id_t ID)
{
    uint16_t timer_required_counts[TIMER_MAX_ID];

    /* Check if there is a required initial value or not */
    if (timer_required_counts[ID] != TIMER_WITH_ZERO_COUNTS)
    {
        /* Calculate the number of required counts */
        timer_required_counts[ID] = TIMER_COUNTs[ID] % TIMER_MAX_COUNT_VALUE[ID];
        /* Calculate the initial value */
        TIMER_INITIAL_VALUE[ID] = TIMER_MAX_COUNT_VALUE[ID] - timer_required_counts[ID];
        /* Update the number of required overflows */
        TIMER_REQUIRED_OVFs[ID]++;
    }
    else
    {
        /* do Nothing */
    }
    
    /* Calculate and update the number of required overflows */
    TIMER_REQUIRED_OVFs[ID] += (TIMER_COUNTs[ID] / TIMER_MAX_COUNT_VALUE[ID]);
}

/**
 * @brief This Static API is used to apply busy wait until the required time is elapsed.
 * @param ID The ID of timer that will be used.
 * @return The status of the API (DRIVER_IS_OK or VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER).
 */
static driver_status_t timer_busy_wait(timer_id_t ID)
{
    driver_status_t timer_status = DRIVER_IS_OK;
    uint8_t current_ovf_number = TIMER_WITH_ZERO_OVFS;

    /* Calculate Initial Value and number of OVFs*/
    timer_calculations(ID);    

/* Check which Busy Wait method is used */
#if (TIMER_BUSY_WAIT_METHOD == TIMER_BUSY_WAIT_0)
    /* Check if mode used is normal mode */
    if (TIMER_INFO_ARR[ID].timer_cfg.mode == TIMER_NORMAL_MODE)
    {
        /* Check which timer is used */
        if (ID == TIMER_0)
        {
            /* Wait until the time is elapsed */
            while (current_ovf_number < TIMER_REQUIRED_OVFs[ID])
            {
                /* Check if the cycle is first cycle or not */
                if (current_ovf_number == TIMER_WITH_ZERO_OVFS)
                {
                    /* Set Counter Initial value */
                    TCNT0->reg = TIMER_INITIAL_VALUE[ID];
                }
                else
                {
                    /* Do Nothing */
                }
                /* Check if the flag is raised or not */
                if (TIFR->bits.TOV0 == TIMER_FLAG_IS_RAISED)
                {
                    /* Clear timer Flag */
                    TIFR->bits.TOV0 = TIMER_CLEAR_FLAG;
                    /* Increment Number of current overflows */
                    current_ovf_number++;
                }
                else
                {
                    /* Do Nothing */
                }
            }
        }
        else if (ID == TIMER_1)
        {
            // TODO: This section will be added with Timer 1 Implementation.
        }
        else
        {
            // TODO: This section will be added with Timer 2 Implementation.
        }
    }
    /* Check if mode used is compare match mode and initial value will be compared */
    else if ((TIMER_INFO_ARR[ID].timer_cfg.mode == TIMER_COMPARE_MATCH_MODE) && (TIMER_INITIAL_VALUE[ID] != TIMER_MAX_COUNT_VALUE[ID]))
    {
        /* Check which timer is used */
        if (ID == TIMER_0)
        {
            /* Set Timer compare match value to Maximum value */
            OCR0->reg = TIMER_0_MAX_COUNT_VALUE;
            /* Wait until the time is elapsed */
            while (current_ovf_number < TIMER_REQUIRED_OVFs[ID])
            {
                /* Check if the cycle is first cycle or not */
                if (current_ovf_number == TIMER_WITH_ZERO_OVFS)
                {
                    /* Set Counter Initial value */
                    TCNT0->reg = TIMER_INITIAL_VALUE[ID];
                }
                else
                {
                    /* Do Nothing */
                }
                /* Check if the flag is raised or not */
                if (TIFR->bits.OCF0 == TIMER_FLAG_IS_RAISED)
                {
                    /* Clear timer Flag */
                    TIFR->bits.OCF0 = TIMER_CLEAR_FLAG;
                    /* Increment Number of current overflows */
                    current_ovf_number++;
                }
                else
                {
                    /* Do Nothing */
                }
            }
        }
        else if (ID == TIMER_1)
        {
            // TODO: This section will be added with Timer 1 Implementation.
        }
        else
        {
            // TODO: This section will be added with Timer 2 Implementation.
        }
    }
#elif (TIMER_BUSY_WAIT_METHOD == TIMER_BUSY_WAIT_1)
    /* Check if mode used is acceptable or not */
    if ((TIMER_INFO_ARR[ID].timer_cfg.mode == TIMER_NORMAL_MODE) || (TIMER_INFO_ARR[ID].timer_cfg.mode == TIMER_COMPARE_MATCH_MODE) && (timer_initial_value != TIMER_MAX_COUNT_VALUE[ID]))
    {
        /* Wait until the time is elapsed */
        while (current_ovf_number < TIMER_REQUIRED_OVFs[ID])
        {
            /* Check which timer is used */
            if (ID == TIMER_0)
            {
                /* Check if the cycle is first cycle or not */
                if (current_ovf_number == TIMER_WITH_ZERO_OVFS)
                {
                    /* Set Counter Initial value */
                    TCNT0->reg = TIMER_INITIAL_VALUE[ID];
                }
                else
                {
                    /* Do Nothing */
                }
                if (TIMER_INFO_ARR[ID].timer_cfg.mode == TIMER_COMPARE_MATCH_MODE)
                {
                    /* Set Timer compare match value to Maximum value */
                    OCR0->reg = TIMER_0_MAX_COUNT_VALUE;
                    /* Check if the Compare match flag is raised or not */
                    if (TIFR->bits.OCF0 == TIMER_FLAG_IS_RAISED)
                    {
                        /* Clear timer Flag */
                        TIFR->bits.OCF0 = TIMER_CLEAR_FLAG;
                        /* Increment Number of current overflows */
                        current_ovf_number++;
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
                else
                {
                    /* Check if the flag is raised or not */
                    if (TIFR->bits.TOV0 == TIMER_FLAG_IS_RAISED)
                    {
                        /* Clear timer Flag */
                        TIFR->bits.TOV0 = TIMER_CLEAR_FLAG;
                        /* Increment Number of current overflows */
                        current_ovf_number++;
                    }
                    else
                    {
                        /* Do Nothing */
                    }
                }
            }
            else if (ID == TIMER_1)
            {
                // TODO: This section will be added with Timer 1 Implementation.
            }
            else
            {
                // TODO: This section will be added with Timer 2 Implementation.
            }
        }
    }
#else
    /* Do Nothing */
#endif
    else
    {
        /* Input is not acceptable (Wrong mode or initial value will cause wrong period )*/
        timer_status = VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER;
    }

    /* Return Timer Status */
    return timer_status;
}

/**
 * @brief This API is used to set the required period in micro-seconds (us).
 * @param ID The ID of used Timer.
 * @param period_us The Period in micro-seconds.
 * @return The status of the API (DRIVER_IS_OK, VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER or VALUE_IS_NOT_EXISTED).
 * @note The equation that's used to update time is period = N * (prescaler / CPU clock).
 * Where N is the number of counts, Period is the required period and prescaler & CPU Clock must be configured in Timer_cfg file.
 */
driver_status_t timer_set_period_us(timer_id_t ID, uint16_t period_us)
{
    driver_status_t timer_status = DRIVER_IS_OK;

    /* Check if the Timer ID is existing or not */
    if (ID < TIMER_MAX_ID)
    {
/* Check that CPU_CLK Value is accepted or not */
#if (CPU_CLK_MHZ <= MAX_ACCEPTABLE_CPU_CLK)
/* Check if the prescaler value is existing */
#if ((TIMER_PRESCALER_VALUE >= TIMER_WITH_NO_PRESCALING) && (TIMER_PRESCALER_VALUE <= TIMER_WITH_EXT_CLK_RISING_EDGE))
        /* Calculate Number of OVFs that's needed to achieve the chosen period */
        TIMER_COUNTs[ID] = ((uint32_t)period_us * (uint32_t)CPU_CLK_MHZ) / (uint32_t)TIMER_PRESCALER_VALUE;
        /* Check which Technique is used */
        if(TIMER_INFO_ARR[ID].timer_cfg.tech == TIMER_BUSY_WAIT_TECH)
        {
            /* Call Busy wait function */
            timer_status = timer_busy_wait(ID);
        
        }
        else if(TIMER_INFO_ARR[ID].timer_cfg.tech == TIMER_INTERRUPT_TECH)
        {
            /* Do Nothing as it's already set by timer_set_interrupt_status API */
        }
        else
        {
            /* Timer technique isn't existing */
            timer_status = VALUE_IS_NOT_EXISTED;
        }
#else
        /* Presacler Value is not existing */
        timer_status = VALUE_IS_NOT_EXISTED;
#endif
#else
        /* CPU Clock value is not accepted */
        timer_status = VALUE_IS_NOT_ACCEPTED_FOR_THIS_DRIVER;
#endif
    }
    else
    {
        /* Timer ID is not existing */
        timer_status = VALUE_IS_NOT_EXISTED;
    }

    /* Return the value of Timer status */
    return timer_status;
}

/**
 * @brief This API is used to start Timer counting.
 * @param ID The ID of used Timer.
 * @return The status of the API (DRIVER_IS_OK or VALUE_IS_NOT_EXISTED).
 * @note This API must be called after setting of Timer configurations and Period or PWM Properities.
 */
driver_status_t timer_start(timer_id_t ID)
{
    driver_status_t timer_status = DRIVER_IS_OK;
/* Check if the prescaler value is existing */
#if((TIMER_PRESCALER_VALUE >= TIMER_WITH_NO_PRESCALING) && (TIMER_PRESCALER_VALUE <= TIMER_WITH_EXT_CLK_RISING_EDGE))
    /* Check which Timer is used */
    if(ID == TIMER_0)
    {
        /* Set Prescaler for Timer 0 */
        TCCR0->bits.CS0 = GET_BIT(TIMER_PRESCALER_VALUE, BIT0);
        TCCR0->bits.CS1 = GET_BIT(TIMER_PRESCALER_VALUE, BIT1);
        TCCR0->bits.CS2 = GET_BIT(TIMER_PRESCALER_VALUE, BIT2);
    }
    else if(ID == TIMER_1)
    {
        // TODO: This section will be added with the implementation of Timer 1.
    }
    else if(ID == TIMER_2)
    {
        // TODO: This section will be added with the implementation of Timer 2.
    }
    else
    {
        /* The Timer ID isn't existing */
        timer_status = VALUE_IS_NOT_EXISTED;
    }

#else
    /* The Timer Prescaler isn't existing */
    timer_status = VALUE_IS_NOT_EXISTED;
#endif

    /* Return the Timer status */
    return timer_status;
}

driver_status_t timer_stop(timer_id_t);
