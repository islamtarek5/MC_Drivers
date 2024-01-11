/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2024-01-09 17:07:46                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2024-01-11 14:37:51                              *
 * @FilePath              : timer_int.h                                      *
 ****************************************************************************/

#ifndef TIMER_TIMER_INT_H_
#define TIMER_TIMER_INT_H_

/**
 * @section Includes.
 */

#include "../../MC_driver.h"

/**
 * @section Typedefs.
 */

/**
 * @brief Timer ID.
 */
typedef enum
{
    TIMER_0 = (uint8_t)0,
    TIMER_1,
    TIMER_2,
    TIMER_MAX_ID
} timer_id_t;

/**
 * @brief Timer Mode.
 */
typedef enum
{
    TIMER_NORMAL_MODE = (uint8_t)0,              /* Normal Mode (Used with all timers, Top Value is 255 with timer0 and timer2 but 65535 with timer1)*/
    TIMER_PWM_PPHASE_CORRECT_MODE,               /* PWM Phase Correct Mode with 8 bits in case of Timer1 (Used with all timers, , Top value is 255)*/
    TIMER_PWM_PPHASE_CORRECT_WITH_9BITS_MODE,    /* PWM Phase Correct Mode with 9 bits (Used with Timer1 only, Top value is 511) */
    TIMER_PWM_PPHASE_CORRECT_WITH_10BITS_MODE,   /* PWM Phase Correct Mode with 10 bits (Used with Timer1 only, Top value is 1023) */
    TIMER_COMPARE_MATCH_MODE,                    /* Compare Match Mode with OCR1A in case of Timer1 (Used with all timers, Top value is value of OCR Registers "OCR1A in case of Timer1") */
    TIMER_FAST_PWM_MODE,                         /* Fast PWM Mode with 8 bits in case of Timer1 (Used with all timers, Top value is 255) */
    TIMER_FAST_PWM_WITH_9BITS_MODE,              /* Fast PWM Mode with 9 bits (Used with Timer1 only, Top value is 511) */
    TIMER_FAST_PWM_WITH_10BITS_MODE,             /* Fast PWM Mode with 10 bits (Used with Timer1 only, Top value is 1023) */
    TIMER_PWM_PPHASE_FREQ_CORRECT_WITH_ICR_MODE, /* PWM Phase and Frequency correct with ICR1 (Used with Timer1 only, Top value is value of ICR1 Register)*/
    TIMER_PWM_PPHASE_FREQ_CORRECT_WITH_OCR_MODE, /* PWM Phase and Frequency correct with OCR1A (Used with Timer1 only, Top value is value of OCR1A Register)*/
    TIMER_PWM_PPHASE_CORRECT_WITH_ICR_MODE,      /* PWM Phase Correct Mode with ICR1 (Used with Timer1 only, Top value is value of ICR1 Register) */
    TIMER_PWM_PPHASE_CORRECT_WITH_OCR_MODE,      /* PWM Phase Correct Mode with OCR1A (Used with Timer1 only, Top value is value of OCR1A Register) */
    TIMER_COMPARE_MATCH_WITH_ICR_MODE,           /* Compare Match Mode with ICR1 (Used with Timer1 only, Top value is value of ICR1 Register) */
    TIMER_RESERVED_MODE_VALUE,                   /* Reserved Value in case of TImer1 */
    TIMER_FAST_PWM_WITH_ICR_MODE,                /* Fast PWM Mode with ICR1 (Used with Timer1 only, Top value is value of ICR1 Register) */
    TIMER_FAST_PWM_WITH_OCR_MODE,                /* Fast PWM Mode with OCR1A (Used with Timer1 only, Top value is value of OCR1A Register) */
    TIMER_MAX_MODE
} timer_mode_t;

/**
 * @brief Timer Working Technique.
 */
typedef enum
{
    TIMER_BUSY_WAIT_TECH = (uint8_t)0,
    TIMER_INTERRUPT_TECH,
    TIMER_MAX_TECH
} timer_tech_t;

/**
 * @brief Timer Output Pin function.
 */
typedef enum
{
    TIMER_PIN_NOT_USED = (uint8_t)0, /* The Timer Pin is used as GPIO Pin (Used with all Modes and must be used with Normal mode) */
    TIMER_TOGGLE_PIN,                /* The Timer Pin will bed toggled when compare match occurs (Used with Compare Match Mode only) */
    TIMER_CLEAR_PIN,                 /* The Timer Pin will be cleared when compare match occurs (Used with Compare Match Mode only) */
    TIMER_SET_PIN,                   /* The Timer Pin will be set when compare match occurs(Used with Compare Match Mode only) */
    TIMER_RESERVED_PIN_FUNC_VALUE,   /* Reserved Value in case of PWM Mode only */
    TIMER_NON_INVERTING_OUTPUT,      /* The Time will generate Non_Inverting PWM on its pin (Used with PWM Mode only) */
    TIMER_INVERTING_OUTPUT,          /* The Time will generate Inverting PWM on its pin (Used with PWM Mode only) */
    TIMER_MAX_PIN_FUNC
} timer_Pin_func_t;

/**
 * @brief Timer Interrupt status.
 *
 */
typedef enum
{
    TIMER_DISABLE_ALL_INTERRUPTS = (uint8_t)0,  /* Disable All Interrupts (Used with all Timers) */
    TIMER_ENABLE_OVF_INERRUPT,                  /* Enable Overflow Interrupt only (Used with all Timers) */
    TIMER_ENABLE_CM_INTERRUPT,                  /* ُEnable Compare Match Interrupt only (Used with all Timers) */
    TIMER_ENABLE_BOTH_OVF_AND_CM_INTERRUPTS,    /* Enable Both Overflow and compare match Interrupts (Used with all Timers) */
    TIMER_ENABLE_ALL_INTERRUPTS,                /* Enable All Interrupts (Used with Timer1 only)*/
    TIMER_MAX_INTERRRUPT_STATE
} timer_interrupt_status_t;

/**
 * @brief Callback function.
 */
typedef void (*timer_P2VCbFunc_t)(void);

/**
 * @brief Timer Structure.
 */
typedef struct
{
    timer_id_t id;
    timer_mode_t mode;
    timer_Pin_func_t pinFunc;
    timer_tech_t tech;
} timer_cfg_S;

/**
 * @section APIs
 */

driver_status_t timer_init(timer_cfg_S *);
driver_status_t timer_set_inerrupt_status(timer_id_t, timer_interrupt_status_t);
driver_status_t timer_set_callback_function(timer_id_t, timer_P2VCbFunc_t);
driver_status_t timer_set_period_us(timer_id_t, uint16_t);
driver_status_t timer_set_pwm_info(timer_id_t, uint8_t, uint8_t);
driver_status_t timer_start(timer_id_t);
driver_status_t timer_stop(timer_id_t);

#endif