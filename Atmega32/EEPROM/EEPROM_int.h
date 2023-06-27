/*****************************************************************************
 * @Author                : Islam Tarek<islamtarek0550@gmail.com>            *
 * @CreatedDate           : 2023-06-27 10:22:06                              *
 * @LastEditors           : Islam Tarek<islamtarek0550@gmail.com>            *
 * @LastEditDate          : 2023-06-27 10:45:07                              *
 * @FilePath              : EEPROM_int.h                                     *
 ****************************************************************************/

#ifndef EEPROM_EEPROM_INT_H_
#define EEPROM_EEPROM_INT_H_

/**
 * @section Includes
 */

#include <stdint.h>


/**
 * @section APIs
 */

void EEPROM_init                (void);
void EEPROM_write_byte          (uint16_t address, uint8_t byte);
void EEPROM_write_data          (uint16_t base_address, uint8_t * data, uint16_t length);
void EEPROM_read_data           (uint16_t base_address, uint8_t * data, uint16_t length);
void EEPROM_enable_interrupt    (void);
void EEPROM_disable_interrupt   (void);

#endif