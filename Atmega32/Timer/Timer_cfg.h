/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2024-01-10 11:00:42                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2024-01-16 12:57:57                              *
 * @FilePath              : Timer_cfg.h                                      *
 ****************************************************************************/

#ifndef TIMER_TIMER_CFG_H_
#define TIMER_TIMER_CFG_H_

/**
 * @brief CPU Clock in MHZ.
 * @note Maximum acceptable value is 16MHZ and it's applicable when External clock is used(fuse bits).
 */
#define CPU_CLK_MHZ         8U

/**
 * @brief Timers'Prescalers.
 * @note Options 
 * TIMER_WITH_NO_PRESCALING       
 * TIMER_WITH_PRESCALER_BY_8      
 * TIMER_WITH_PRESCALER_BY_64     
 * TIMER_WITH_PRESCALER_BY_256    
 * TIMER_WIHT_PRESCALER_BY_1024   
 * TIMER_WITH_EXT_CLK_FALLING_EDGE
 * TIMER_WITH_EXT_CLK_RISING_EDGE 
 */
#define TIMER_PRESCALER_VALUE   TIMER_WITH_NO_PRESCALING

#endif 