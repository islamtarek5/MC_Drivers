/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-25 12:55:48                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-08-28 11:23:53                              *
 * @FilePath              : atmega32_reg.h                                   *
 ****************************************************************************/

#ifndef ATMEGA32_ATMEGA32_REG_H_
#define ATMEGA32_ATMEGA32_REG_H_

/**
 * @section Includes
 */

#include "../MC_driver.h"

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
#define EEPROM_BASE_ADDRESS            0x3CU

/**
 * @brief Map EEPROM Registers and their bits to their Memory locations.
 */
#define EEPROM       ((EEPROM_Reg_S *) EEPROM_BASE_ADDRESS)


/**
 * @brief Store Program Memory Control Register (SPMCR) and its bits . (R/W Registers except bits (5, 6) which are read-only)
 * @note SPMCR contains control bits needed to control Boot Loader options.
 * @note SPMCR initial Value is 0x00.
 */

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t SPMEN    : 1;    
        uint8_t PGERS    : 1;    
        uint8_t PGWRT    : 1;    
        uint8_t BLBSET   : 1;    
        uint8_t RWWSRE   : 1;    
        uint8_t Reserved : 1;    
        uint8_t RWWSB    : 1;    
        uint8_t SPMIE    : 1;    
    }bits;

}SPMCR_t;

/**
 * @brief Store Program Memory Control Register Address.
 */
#define SPMCR_ADDRESS            0x57U

/**
 * @brief Map Store Program Memory Control Register and its bits to its Memory location.
 */
#define SPMCR       ((volatile SPMCR_t *) SPMCR_ADDRESS)    


/**
 * @brief Oscillator Calibration Register (OSCCAL) and its bits . (R/W Register)
 * @note OSCCAL contatians the Internal RC Calibration Value.
 * @note If the internal RC is used as 1MHZ, the OSCCAL Value will be loaded automatically from signature row high byte.
 * @note If the internal RC isn't used as 1MHZ, the OSCCAL value must be loaded manually. 
 * @note OSCCAL Values can be 0x00, 0x7F or 0xFF.
 * @note OSCAL Value 0x00 (min: 50%  , max: 100% of Nominal frequency).
 * @note OSCAL Value 0x7F (min: 75%  , max: 150% of Nominal frequency).
 * @note OSCAL Value 0xFF (min: 100% , max: 200% of Nominal frequency).
 */

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t CAL0    : 1;    /* Calibration bit 0 */
        uint8_t CAL1    : 1;    /* Calibration bit 1 */
        uint8_t CAL2    : 1;    /* Calibration bit 2 */
        uint8_t CAL3    : 1;    /* Calibration bit 3 */
        uint8_t CAL4    : 1;    /* Calibration bit 4 */
        uint8_t CAL5    : 1;    /* Calibration bit 5 */
        uint8_t CAL6    : 1;    /* Calibration bit 6 */
        uint8_t CAL7    : 1;    /* Calibration bit 7 */
    }bits;

}OSCCAL_t;

/**
 * @brief Oscillator Calibration Register Address.
 */
#define OSCCAL_ADDRESS            0x51U

/**
 * @brief Map Oscillator Calibration Register and its bits to its Memory location.
 */
#define OSCAL       ((volatile OSCCAL_t *) OSCCAL_ADDRESS) 


/**
 * @brief MCU Control Register (MCUCR) and its bits . (R/W Register)
 * @note MCUCR is used to control Sleep modes and power management.
 * @note MCUCR initial Value is 0x00.
 */

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t ISC00    : 1;    // TODO 
        uint8_t ISC01    : 1;    // TODO 
        uint8_t ISC10    : 1;    // TODO 
        uint8_t ISC11    : 1;    // TODO 
        uint8_t SM       : 3;    /* Sleep Mode Select Bits */
        uint8_t SE       : 1;    /* Sleep Enable Bit       */
    }bits;

}MCUCR_t;

/**
 * @brief MCU Control Register Address.
 */
#define MCUCR_ADDRESS            0x55U

/**
 * @brief Map MCU Control Register and its bits to its Memory location.
 */
#define MCUCR       ((volatile MCUCR_t *) MCUCR_ADDRESS)    


/**
 * @brief Special Function Input/output Register (SFIOR) and its bits . (R/W Register Except bit 4)
 * @note SFIOR contains Pull-up Disable bit (PUD) which can be used to diable all internal Pull-up.
 * @note SFIOR initial Value is 0x00.
 */

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t PSR10    : 1;    //TODO 
        uint8_t PSR2     : 1;    //TODO 
        uint8_t PUD      : 1;    /* Pull-up disable */
        uint8_t ACME     : 1;    //TODO 
        uint8_t Reserved : 1;    /* Reserved bit    */
        uint8_t ADTS0    : 1;    //TODO 
        uint8_t ADTS1    : 1;    //TODO 
        uint8_t ADTS2    : 1;    //TODO 
    }bits;

}SFIOR_t;

/**
 * @brief SFIOR Address.
 */
#define SFIOR_ADDRESS            0x50U

/**
 * @brief Map SFIOR and its bits to its Memory location.
 */
#define SFIOR       ((volatile SFIOR_t *) SFIOR_ADDRESS)    


/**
 * @brief GPIO Registers and their pins.
 * @note Port Input Pins Register (PIN) and its bits. (Read only Register)
 * @note PIN contains the input value of the MCU pins.
 * @note PIN initial Value is unknown (N/A, floating value).
 * @note Port Data Direction Register (DDR) and its bits. (R/W Register)
 * @note DDR is used to control the pin direction of MCU either Input or output.
 * @note DDR initial Value is 0x00 (Pins are input initially).
 * @note Port Data Register (PORT) and its bits. (R/W Register)
 * @note PORT contains the value by which pin will be driven as output.
 * @note PORT initial Value is 0x00 (Pins has low level initially).
 */

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t PIN0: 1;  /* Port Input Bit0 */  
        uint8_t PIN1: 1;  /* Port Input Bit1 */   
        uint8_t PIN2: 1;  /* Port Input Bit2 */  
        uint8_t PIN3: 1;  /* Port Input Bit3 */   
        uint8_t PIN4: 1;  /* Port Input Bit4 */  
        uint8_t PIN5: 1;  /* Port Input Bit5 */   
        uint8_t PIN6: 1;  /* Port Input Bit6 */  
        uint8_t PIN7: 1;  /* Port Input Bit7 */  
    }bits;

}PIN_t;

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t DD0: 1;  /* Port Direction Bit0 */  
        uint8_t DD1: 1;  /* Port Direction Bit1 */   
        uint8_t DD2: 1;  /* Port Direction Bit2 */  
        uint8_t DD3: 1;  /* Port Direction Bit3 */   
        uint8_t DD4: 1;  /* Port Direction Bit4 */  
        uint8_t DD5: 1;  /* Port Direction Bit5 */   
        uint8_t DD6: 1;  /* Port Direction Bit6 */  
        uint8_t DD7: 1;  /* Port Direction Bit7 */  
    }bits;

}DDR_t;

typedef union 
{
    uint8_t reg;
    struct 
    {
        uint8_t PORT0: 1;  /* Port Output Bit0 */  
        uint8_t PORT1: 1;  /* Port Output Bit1 */   
        uint8_t PORT2: 1;  /* Port Output Bit2 */  
        uint8_t PORT3: 1;  /* Port Output Bit3 */   
        uint8_t PORT4: 1;  /* Port Output Bit4 */  
        uint8_t PORT5: 1;  /* Port Output Bit5 */   
        uint8_t PORT6: 1;  /* Port Output Bit6 */  
        uint8_t PORT7: 1;  /* Port Output Bit7 */  
    }bits;

}PORT_t;

/* GPIO Registers Structure */
typedef struct 
{
    volatile PIN_t  PIN ;
    volatile DDR_t  DDR ;
    volatile PORT_t PORT;
}GPIO_Reg_S;

/**
 * @brief GPIO Base Addresses.
 */
#define GPIO_A_BASE_ADDRESS            0x39U
#define GPIO_B_BASE_ADDRESS            0x36U
#define GPIO_C_BASE_ADDRESS            0x33U
#define GPIO_D_BASE_ADDRESS            0x30U

/**
 * @brief Map GPIO Registers and their bits to their Memory locations.
 */
#define GPIO_A_REGS       ((GPIO_Reg_S *) GPIO_A_BASE_ADDRESS)
#define GPIO_B_REGS       ((GPIO_Reg_S *) GPIO_B_BASE_ADDRESS)
#define GPIO_C_REGS       ((GPIO_Reg_S *) GPIO_C_BASE_ADDRESS)
#define GPIO_D_REGS       ((GPIO_Reg_S *) GPIO_D_BASE_ADDRESS)

#endif
