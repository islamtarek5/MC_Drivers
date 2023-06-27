/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 10:26:29                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-27 12:35:06                              *
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
 * @note in Case of TIME_TRIGGER_OS, OS_PERIOD_MS must be set by the period value in milliseconds.
 */

#define OS              SUPER_LOOP_OS
#define EEPROM_PERIOD_MS            10U
/**
 * @brief EEPROM Interrupt Configuration
 * @note Options are EEPROM_INTERRUPT_DISABLE or EERPOM_INTERRUPT_ENABLE
 */

#define EEPROM_INTERRUPT    EEPROM_INTERRUPT_DISABLE

/**
 * @brief BOOT LOADER Configuration
 * @note Options are BOOT_LOADER_IS_USED or BOOT_LOADER_NOT_USED
 */

#define BOOT_LOADER_USAGE   BOOT_LOADER_NOT_USED

#endif