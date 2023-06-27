/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-25 12:55:48                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-27 10:22:24                              *
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

/**
 * @brief EEPROM Registers and Their bits .
 * @note EEPROM Address Registers (EEARL, EEARH). (R/W Registers except reserved bits which are read-only)
 * @note EEARH initial value is 0x00 or 0x01.
 * @note EEARL initial value is undefined.
 * @note EEPROM Address registers specify the EEPROM address in 1024 bytes EEPROM Space.
 * @note EEPROM Data Register (EEDR). (R/W Register).
 * @note EEDR contains data to be written at or read from specific address in EEPROM.
 * @note EEDR initial value is 0x00.
 * @note EEPROM Control Register (EECR). (R/W Registers except reserved bits which are read-only)
 * @note EECR initial value is 0x00 or 0x02.
 */

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t EEAR0    : 1;    /* EEPROM Address Bit 0 */
        uint8_t EEAR1    : 1;    /* EEPROM Address Bit 1 */
        uint8_t EEAR2    : 1;    /* EEPROM Address Bit 2 */
        uint8_t EEAR3    : 1;    /* EEPROM Address Bit 3 */
        uint8_t EEAR4    : 1;    /* EEPROM Address Bit 4 */
        uint8_t EEAR5    : 1;    /* EEPROM Address Bit 5 */
        uint8_t EEAR6    : 1;    /* EEPROM Address Bit 6 */
        uint8_t EEAR7    : 1;    /* EEPROM Address Bit 7 */
    }bits;

}EEARL_t;

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t EEAR8    : 1;    /* EEPROM Address Bit 8 */
        uint8_t EEAR9    : 1;    /* EEPROM Address Bit 9 */
        uint8_t Reserved : 6;    /* Reserved bits        */
    }bits;

}EEARH_t;

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t EEDR0    : 1;    /* EEPROM Data Bit 0 */
        uint8_t EEDR1    : 1;    /* EEPROM Data Bit 1 */
        uint8_t EEDR2    : 1;    /* EEPROM Data Bit 2 */
        uint8_t EEDR3    : 1;    /* EEPROM Data Bit 3 */
        uint8_t EEDR4    : 1;    /* EEPROM Data Bit 4 */
        uint8_t EEDR5    : 1;    /* EEPROM Data Bit 5 */
        uint8_t EEDR6    : 1;    /* EEPROM Data Bit 6 */
        uint8_t EEDR7    : 1;    /* EEPROM Data Bit 7 */
    }bits;

}EEDR_t;

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t EERE     : 1;    /* EEPROM Read Enable            */
        uint8_t EEWE     : 1;    /* EEPROM Write Enable           */
        uint8_t EEMWE    : 1;    /* EEPROM Master Write Enable    */
        uint8_t EERIE    : 1;    /* EEPROM Ready Interrupt Enable */
        uint8_t Reserved : 4;    /* Reserved bits                 */
    }bits;

}EECR_t;

/**
 * @brief EEPROM Registers Structure.
 */

typedef struct 
{
    volatile EECR_t  EECR ;
    volatile EEDR_t  EEDR ;
    volatile EEARL_t EEARL;
    volatile EEARH_t EEARH;
}EEPROM_Reg_S;


/**
 * @brief EEPROM Base Address.
 */
#define EEPROM_ADDRESS            0x3CU

/**
 * @brief Map EEPROM Registers and their bits to their Memory locations.
 */
#define EEPROM       ((EEPROM_Reg_S *) EEPROM_ADDRESS)
   
#endif
