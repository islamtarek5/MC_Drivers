/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 10:25:18                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-07-01 19:20:22                              *
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

#define SUPER_LOOP_OS                   0U
#define TIME_TRIGGER_OS                 1U

/**
 * @brief EEPROM Ready Interrupt Options
 */

#define EEPROM_INTERRUPT_DISABLE        0U
#define EERPOM_INTERRUPT_ENABLE         1U

/**
 * @brief Boot Loader Options
 */

#define BOOT_LOADER_NOT_USED            0U
#define BOOT_LOADER_IS_USED             1U

/**
 * @section Magic Numbers
 */

/**
 * @brief EEPROM Address 
 */

#define EEPROM_ADDRESS_LEAST_BYTE       0U    
#define EEPROM_ADDRESS_MOST_BYTE        8U
#define EEPROM_NO_ADDRESS               0U

/**
 * @brief Write Condition
 */
#define EEPROM_DATA_REG_IS_AVAILABLE    0U

/**
 * @brief EEPROM Boundaries
 */

#define EEPROM_FIRST_LOCATION           0U
#define EEPROM_LAST_LOCATION            1023U

/**
 * @brief EEPROM Writing
 */

#define EEPROM_NOT_WRITTEN              0U
#define EEPROM_IS_WRITTEN               1U

/**
 * @brief Data length
 */

#define EEPROM_NO_DATA                  0U

#endif