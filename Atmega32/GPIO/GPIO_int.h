/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-28 11:52:17                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-30 17:27:04                              *
 * @FilePath              : GPIO_int.h                                       *
 ****************************************************************************/

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

/**
 * @section Includes
 */

#include "../../MC_driver.h"


/**
 * @section Typedefs
 */

/**
 * @brief GPIO Pins enum.
 */
typedef enum
{
    PIN_0   = (uint8_t) 0x01,
    PIN_1   = (uint8_t) 0x02,
    PIN_2   = (uint8_t) 0x04,
    PIN_3   = (uint8_t) 0x08,
    PIN_4   = (uint8_t) 0x10,
    PIN_5   = (uint8_t) 0x20,
    PIN_6   = (uint8_t) 0x40,
    PIN_7   = (uint8_t) 0x80,
    PIN_ALL = (uint8_t) 0xFF
}gpio_pin_t;

/**
 * @brief GPIO Ports enum
 */

typedef enum
{
    PORT_A  = (uint8_t) 0,
    PORT_B               ,
    PORT_C               ,
    PORT_D               ,
    PORT_MAX
}gpio_port_t;

/**
 * @brief GPIO Levels enum
 */

typedef enum
{
    PIN_LOW_LEVEL = (uint8_t)0,
    PIN_HIGH_LEVEL            ,
    PIN_MAX_LEVEL
}gpio_level_t;

/**
 * @brief GPIO Modes enum
 */

typedef enum
{
    PIN_OUTPUT = (uint8_t) 0,
    PIN_FLOATING_INPUT      ,
    PIN_PULL_UP_INPUT       ,
    PIN_PULL_DOWN_INPUT     ,
    PIN_MAX_MODE
}gpio_mode_t;


/**
 * @section APIs
 */

driver_status_t GPIO_set_pin_mode (gpio_port_t, gpio_pin_t, gpio_mode_t);
driver_status_t GPIO_set_pin_level(gpio_port_t, gpio_pin_t, gpio_level_t);
driver_status_t GPIO_get_pin_level(gpio_port_t, gpio_pin_t, gpio_level_t *);
driver_status_t GPIO_tog_pin_level(gpio_port_t, gpio_pin_t);

#endif