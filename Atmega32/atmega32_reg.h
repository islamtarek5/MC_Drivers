/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-25 12:55:48                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-25 13:09:40                              *
 * @FilePath              : atmega32_reg.h                                   *
 ****************************************************************************/

#ifndef ATMEGA32_ATMEGA32_REG_H_
#define ATMEGA32_ATMEGA32_REG_H_

/**
 * @section Includes
 */

#include <stdint.h>

/**
 * @section Atmega32 Registers
 */

/**
 * @brief Status Register and its bits . (R/W Register)
 * @note Status Register contains information about the result of recen executed arithmetic instruction.
 * @note Status Register initial Value is 0x00.
 * @note Status Register isn't automatically stored when entering interrupt routine and restored when returning from it. It must be handled by SW.
 */

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t C    : 1;    /* Carry Flag                       */
        uint8_t Z    : 1;    /* Zero Flag                        */
        uint8_t N    : 1;    /* Negative Flag                    */
        uint8_t V    : 1;    /* Two's Complement Overglow Flag   */
        uint8_t S    : 1;    /* Sign Bit                         */
        uint8_t H    : 1;    /* Half Carry Flag                  */
        uint8_t T    : 1;    /* Bit Copy Storage                 */
        uint8_t I    : 1;    /* Global Intetrrupt Enable Bit     */
    }bits;

}SREG_t;

/**
 * @brief Status Register Address.
 */
#define SREG_ADDRESS            0x5FU

/**
 * @brief Map Status Register and its bits to its Memory location.
 */
#define SREG       ((volatile SREG_t *) SREG_ADDRESS)    


#endif
