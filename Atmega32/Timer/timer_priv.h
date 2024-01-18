/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2024-01-09 17:07:50                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2024-01-18 13:32:47                              *
 * @FilePath              : timer_priv.h                                     *
 ****************************************************************************/

#ifndef TIMER_TIMER_PRIV_H_
#define TIMER_TIMER_PRIV_H_

/**
 * @brief Maximum Pin function bits value.
 */
#define MAX_PIN_FUNCTION_ACCEPTED_VALUE 3U

/**
 * @brief Maximum CPU Value that works with atmega32
 * @note This Value can be applied as external clock so clock must be set to be external with Fuse bits.
 */
#define MAX_ACCEPTABLE_CPU_CLK          16U

/**
 * @brief Prescaler Options.
 */
#define TIMER_WITH_NO_PRESCALING        1U
#define TIMER_WITH_PRESCALER_BY_8       2U
#define TIMER_WITH_PRESCALER_BY_64      3U
#define TIMER_WITH_PRESCALER_BY_256     4U
#define TIMER_WIHT_PRESCALER_BY_1024    5U
#define TIMER_WITH_EXT_CLK_FALLING_EDGE 6U
#define TIMER_WITH_EXT_CLK_RISING_EDGE  7U

/**
 * @brief Timers' Max count Values
 */
#define TIMER_0_MAX_COUNT_VALUE         0xFFU
#define TIMER_1_MAX_COUNT_VALUE         0XFFFFU
#define TIMER_2_MAX_COUNT_VALUE         0xFFU

/**
 * @brief Overflow values.
 */
#define TIMER_WITH_ZERO_OVFS            0U

/**
 * @brief Timer Number of Counts.
 */
#define TIMER_WITH_ZERO_COUNTS          0U

/**
 * @brief Time Flag Values.
 */
#define TIMER_FLAG_IS_CLEARED           0U
#define TIMER_FLAG_IS_RAISED            1U 
#define TIMER_CLEAR_FLAG                1U

/**
 * @brief Timer Stop Value.
 */
#define TIMER_STOP                      0U

#endif