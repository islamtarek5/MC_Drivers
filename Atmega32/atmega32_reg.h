/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-25 12:55:48                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-25 13:42:48                              *
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

/**
 * @brief Stack Pointer Registers and their bits . (R/W Registers)
 * @note Stack Pointer Registers are divided into two 8-bit registers (SPL, SPH).
 * @note Stack Pointer Registers initial Value is 0x00.
 * @note Stack is implemented as growing from higher memory location to lower memory location.
 * @note Stack Pointer will decrease by PUSH instruction and increase by POP instruction.
 * @note Stack Pointer will change (increase or decrease) by one with data (Pop / Push) and by two with return address (Pop / Push).
 * @note Stack Pointer must be set to point above $60.
 */

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t SP0    : 1;    /* Stack Pointer Bit 0 */
        uint8_t SP1    : 1;    /* Stack Pointer Bit 1 */
        uint8_t SP2    : 1;    /* Stack Pointer Bit 2 */
        uint8_t SP3    : 1;    /* Stack Pointer Bit 3 */
        uint8_t SP4    : 1;    /* Stack Pointer Bit 4 */
        uint8_t SP5    : 1;    /* Stack Pointer Bit 5 */
        uint8_t SP6    : 1;    /* Stack Pointer Bit 6 */
        uint8_t SP7    : 1;    /* Stack Pointer Bit 7 */
    }bits;

}SPL_t;

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t SP8         : 1;    /* Stack Pointer Bit 8   */
        uint8_t SP9         : 1;    /* Stack Pointer Bit 9   */
        uint8_t SP10        : 1;    /* Stack Pointer Bit 10  */
        uint8_t SP11        : 1;    /* Stack Pointer Bit 11  */
        uint8_t Reserved    : 4;    /* Reserved bits         */
    }bits;

}SPH_t;

/**
 * @brief Stack Pointer Registers Addresses.
 */
#define SPL_ADDRESS            0x5DU
#define SPH_ADDRESS            0x5EU

/**
 * @brief Map Stack Pointer Registers and their bits to their Memory locations.
 */
#define SPL       ((volatile SPL_t *) SPL_ADDRESS)  
#define SPH       ((volatile SPH_t *) SPH_ADDRESS)     

#endif
