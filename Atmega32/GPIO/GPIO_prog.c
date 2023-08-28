/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-08-28 11:54:20                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-28 13:43:45                              *
 * @FilePath              : GPIO_prog.c                                      *
 ****************************************************************************/

/**
 * @section Includes
 */

#include "../atmega32_reg.h"
#include "GPIO_int.h"
#include "GPIO_priv.h"


/**
 * @section Global Variables
 */

/**
 * @brief GPIO Ports Array contains registers of Atmega32 ports.
 */

static GPIO_Reg_S * GPIO_PORTS[PORT_MAX] =
{
    GPIO_A_REGS,
    GPIO_B_REGS,
    GPIO_C_REGS,
    GPIO_D_REGS
};


/**
 * @section APIs Implementation 
 */

/**
 * @brief This API is used to set mode for one or more pins of same port.
 * @param port The Port whose pin or pins mode will be set (PORT_A -> PORT_D).
 * @param pin  The Pin or Pins whose mode will be set (PIN_0 -> PIN_7, PIN_0 | PIN_1 | ...| PIN_7 or PIN_ALL).
 * @param mode The mode by which pins can be set (PIN_FLOATING_INPUT, PIN_PULL_UP_INPUT or PIN_OUTPUT).
 * @example GPIO_set_pin_mode(PORT_A, PIN_0, PIN_OUTPUT).
 * @example GPIO_set_pin_mode(PORT_B, PIN_0 | PIN_1 | PIN_3, PIN_PULL_UP_INPUT).
 * @example GPIO_set_pin_mode(PORT_C, PIN_ALL, PIN_FLOATING_INPUT).
 * @return The status of the API (DRIVER_IS_OK or VALUE_IS_NOT_EXISTED). 
 */
driver_status_t GPIO_set_pin_mode (gpio_port_t port, gpio_pin_t pin, gpio_mode_t mode)
{
    driver_status_t GPIO_status = DRIVER_IS_OK;

    /* check if Port existed or not */
    if(port < PORT_MAX)
    {
        /* check if Pin existed or not */
        if(pin <= PIN_ALL)
        {
            /* Set Pin(s) Mode */
            switch (mode)
            {
            case PIN_FLOATING_INPUT:
                /* Disable Pull-up for Pin */
                ((GPIO_PORTS[port]->PORT).reg) &= ~pin;
                /* Set Pin Direction to Input */
                ((GPIO_PORTS[port]->DDR).reg) &= ~pin;
                break;
            case PIN_PULL_UP_INPUT:
                /* Enable Pull-up for all Ports */
                ((SFIOR->bits).PUD) = CLEAR_VALUE;
                /* Enable Pull-up for Pin */
                ((GPIO_PORTS[port]->PORT).reg) |= pin;
                /* Set Pin Direction to Input*/
                ((GPIO_PORTS[port]->DDR).reg) &= ~pin;
            case PIN_OUTPUT:
                /* Set Pin Direction to Output */
                ((GPIO_PORTS[port]->DDR).reg) |= pin;             
            default:
                /* Mode value is not existed */
                GPIO_status = VALUE_IS_NOT_EXISTED; 
                break;
            }   
        }
        else
        {
            /* Pin value is not existed */
            GPIO_status = VALUE_IS_NOT_EXISTED;   
        }
    }
    else
    {
        /* Port value is not existed */
        GPIO_status = VALUE_IS_NOT_EXISTED;
    }

    /* Return API status */
    return GPIO_status;
}

/**
 * @brief This API is used to set level for one or more pins of same port.
 * @param port The Port whose pin or pins level will be set (PORT_A -> PORT_D).
 * @param pin The Pin or Pins whose level will be set (PIN_0 -> PIN_7, PIN_0 | PIN_1 | ...| PIN_7 or PIN_ALL).
 * @param level The level by which pins can be set (PIN_LOW_LEVEL or PIN_HIGH_LEVEL).
 * @example GPIO_set_pin_level(PORT_A, PIN_0, PIN_LOW_LEVEL).
 * @example GPIO_set_pin_level(PORT_B, PIN_0 | PIN_1 | PIN_3, PIN_HIGH_LEVEL).
 * @example GPIO_set_pin_level(PORT_C, PIN_ALL, PIN_LOW_LEVEL).
 * @return The status of the API (DRIVER_IS_OK or VALUE_IS_NOT_EXISTED).
 */
driver_status_t GPIO_set_pin_level(gpio_port_t port, gpio_pin_t pin, gpio_level_t level)
{
    driver_status_t GPIO_status = DRIVER_IS_OK;

    /* check if Port existed or not */
    if(port < PORT_MAX)
    {
        /* check if Pin existed or not */
        if(pin <= PIN_ALL)
        {
            /* Set Pin(s) Mode */
            switch (level)
            {
            case PIN_LOW_LEVEL:
                /* Set Pin level */
                ((GPIO_PORTS[port]->PORT).reg) &= ~pin;
                break;
            case PIN_HIGH_LEVEL:
                /* Set Pin Level */
                ((GPIO_PORTS[port]->PORT).reg) |= pin;           
            default:
                /* Level value is not existed */
                GPIO_status = VALUE_IS_NOT_EXISTED; 
                break;
            }   
        }
        else
        {
            /* Pin value is not existed */
            GPIO_status = VALUE_IS_NOT_EXISTED;   
        }
    }
    else
    {
        /* Port value is not existed */
        GPIO_status = VALUE_IS_NOT_EXISTED;
    }
    
    /* Return API status */
    return GPIO_status;
}

driver_status_t GPIO_get_pin_level(gpio_port_t, gpio_pin_t, gpio_level_t *);
driver_status_t GPIO_tog_pin_level(gpio_port_t, gpio_pin_t);
