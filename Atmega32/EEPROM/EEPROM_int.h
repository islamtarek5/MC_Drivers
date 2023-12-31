/*****************************************************************************
 * @Author                : Islam Tarek<islam.tarek@valeo.com>               *
 * @CreatedDate           : 2023-06-27 10:22:06                              *
 * @LastEditors           : Islam Tarek<islam.tarek@valeo.com>               *
 * @LastEditDate          : 2023-08-07 22:42:33                              *
 * @FilePath              : EEPROM_int.h                                     *
 ****************************************************************************/

#ifndef EEPROM_EEPROM_INT_H_
#define EEPROM_EEPROM_INT_H_

/**
 * @section Includes
 */

#include "../../MC_driver.h"


/**
 * @section APIs
 */

driver_status_t EEPROM_init       (void);
driver_status_t EEPROM_write_byte (uint16_t address, uint8_t byte);
driver_status_t EEPROM_write_data (uint16_t base_address, uint8_t * data, uint16_t length, uint16_t * actual_length);
driver_status_t EEPROM_read_data  (uint16_t base_address, uint8_t * data, uint16_t length, uint16_t * actual_length);
void EEPROM_enable_interrupt      (void);
void EEPROM_disable_interrupt     (void);

#endif