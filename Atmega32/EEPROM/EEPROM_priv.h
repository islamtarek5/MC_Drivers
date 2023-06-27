/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 10:25:18                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-27 11:15:01                              *
 * @FilePath              : EEPROM_priv.h                                    *
 ****************************************************************************/

#ifndef EEPROM_EEPROM_PRIV_H_
#define EEPROM_EEPROM_PRIV_H_

/**
 * @section Configuration Options
 */

/**
 * @brief OS Options
 */

#define SUPER_LOOP_OS               0U
#define TIME_TRIGGER_OS             1U

/**
 * @brief EEPROM Ready Interrupt Options
 */

#define EEPROM_INTERRUPT_DISABLE    0U
#define EERPOM_INTERRUPT_ENABLE     1U

/**
 * @section Magic Numbers
 */

/**
 * @brief Address Magic Numbers
 */

#define ADDRESS_LSB                 0U    
#define ADDRESS_MSB                 8U

#endif