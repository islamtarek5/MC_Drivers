/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2024-01-09 17:07:46                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2024-01-10 14:29:50                              *
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
    TIMER_0 = (uint8_t) 0,
    TIMER_1              ,
    TIMER_2              ,
    TIMER_MAX_ID
}timer_id_t;

/**
 * @brief Timer Mode.
 */
typedef enum
{
   TIMER_NORMAL_MODE = (uint8_t)0               ,
   TIMER_PWM_PPHASE_CORRECT_WITH_8BITS_MODE     ,
   TIMER_PWM_PPHASE_CORRECT_WITH_9BITS_MODE     ,
   TIMER_PWM_PPHASE_CORRECT_WITH_10BITS_MODE    ,
   TIMER_COMPARE_MATCH_WITH_OCR_MODE            ,
   TIMER_FAST_PWM_WITH_8BITS_MODE               ,
   TIMER_FAST_PWM_WITH_9BITS_MODE               ,
   TIMER_FAST_PWM_WITH_10BITS_MODE              ,
   TIMER_PWM_PPHASE_FREQ_CORRECT_WITH_ICR_MODE  ,
   TIMER_PWM_PPHASE_FREQ_CORRECT_WITH_OCR_MODE  ,
   TIMER_PWM_PPHASE_CORRECT_WITH_ICR_MODE       ,
   TIMER_PWM_PPHASE_CORRECT_WITH_OCR_MODE       ,
   TIMER_COMPARE_MATCH_WITH_ICR_MODE            ,
                                                ,
   TIMER_FAST_PWM_WITH_ICR_MODE                 ,
   TIMER_FAST_PWM_WITH_OCR_MODE                 ,
   TIMER_MAX_MODE
}timer_mode_t;

/**
 * @brief Timer Working Technique.
 */
typedef enum
{
    TIMER_BUSY_WAIT_TECH    = (uint8_t)0    ,
    TIMER_INTERRUPT_TECH                    ,
    TIMER_MAX_TECH                          
}timer_tech_t;

/**
 * @brief Timer Output Pin function.
 */
typedef enum
{
    TIMER_NOT_USED_PIN  = (uint8_t)0    ,
    TIMER_TOGGLE_PIN                    ,
    TIMER_CLEAR_PIN                     ,
    TIMER_SET_PIN                       ,
    TIMER_NON_INVERTING_OUTPUT          ,
                                        ,
    TIMER_INVERTING_OUTPUT              ,
    TIMER_MAX_PIN_FUNC
}timer_Pin_func_t;

/**
 * @brief Timer Interrupt status.
 * 
 */
typedef enum
{
    TIMER_DISABLE_INTERRUPT = (uint8_t)0    ,
    TIMER_ENABLE_INTERRUPT                  ,
    TIMER_MAX_INTERRRUPT_STATE              
}timer_interrupt_status_t;

/**
 * @brief Callback function.
*/
typedef void (*timer_P2VCbFunc_t)(void);

/**
 * @brief Timer Structure.
*/
typedef struct 
{
    timer_id_t                  id              ;
    timer_mode_t                mode            ;
    timer_Pin_func_t            pinFunc         ;
    timer_tech_t                tech            ;
    timer_interrupt_status_t    interruptStatus ;
    timer_P2VCbFunc_t           callback        ;
}timer_cfg_S;

/**
 * @section APIs
 */

driver_status_t timer_init                  (timer_cfg_S *);
driver_status_t timer_set_mode              (timer_id_t, timer_mode_t);
driver_status_t timer_set_pin_function      (timer_id_t, timer_Pin_func_t);
driver_status_t timer_set_tech              (timer_id_t, timer_tech_t);
driver_status_t timer_set_inerrupt_status   (timer_id_t, timer_interrupt_status_t);
driver_status_t timer_set_callback_function (timer_id_t, timer_P2VCbFunc_t);
driver_status_t timer_set_period_us         (timer_id_t, uint16_t);
driver_status_t timer_set_pwm_info          (timer_id_t, uint8_t, uint8_t);
driver_status_t timer_start                 (timer_id_t);
driver_status_t timer_stop                  (timer_id_t);

#endif