/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 10:26:29                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-27 11:01:23                              *
 * @FilePath              : EEPROM_cfg.h                                     *
 ****************************************************************************/

#ifndef EEPROM_EEPROM_CFG_H_
#define EEPROM_EEPROM_CFG_H_

/**
 * @section Configurations
 */

/**
 * @brief EEPROM Initial Address
 * @note Minimum Available Address is 0
 * @note Maximum Available Address is 1023
 */

#define EEPROM_INITIAL_ADDRESS      0U

/**
 * @brief OS Configuration
 * @note Options are SUPER_LOOP_OS or TIME_TRIGGER_OS
 */

#define OS      SUPER_LOOP_OS

/**
 * @brief EEPROM Interrupt Configuration
 * @note Options are EEPROM_INTERRUPT_DISABLE or EERPOM_INTERRUPT_ENABLE
 */

#define EEPROM_INTERRUPT    EEPROM_INTERRUPT_DISABLE


#endif