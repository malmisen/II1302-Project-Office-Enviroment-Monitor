/**
******************************************************************************
@brief header for the CCS811 & BME280 sensor functions.
@details bla bla bla
@file CCS811_BME280.h
@author  Sebastian Divander,       sdiv@kth.se
@author  Jonatan Lundqvist Silins, jonls@kth.se
@date 06-04-2021
@version 1.0
******************************************************************************
*/


#ifndef INC_CCS811_BME280_H_
#define INC_CCS811_BME280_H_


#include "i2c.h"

#define DEVICE_ADDR 	0xB6 	// Default I2C Address
#define STATUS_REG 		0x00	// Status register, R, 1 byte
#define MEAS_RES 		0x01	// Measurement mode and conditions register, R/W, 1 byte
#define ALG_RES_DATA 	0x02	// Algorithm result, R, 8 bytes
#define RAWDATAREG 		0x03	// ?
#define HW_ID 			0x20 	// Hardware ID, R, 1 byte, should be 0x81
#define APP_START		0xF4	// ?
#define ERROR_ID		0xE0    // Reported errors, R, 1 byte

typedef enum
{
	CCS881_SUCCESS = 0,		// Success status
	CCS881_ERROR, 			// Some internal sensor error, error status set
	CCS881_ID_ERR, 			// HW ID returns a bad value
	CCS881_SAT_ERR			// if a reading is out of bounds, saturated etc

} SENSOR_STATUS;


/**
 *
 */
void
CCS811_read_register(uint8_t reg_addr, uint8_t* buffer);

/**
 *
 */
SENSOR_STATUS
CCS881_init(void);





#endif /* INC_CCS811_BME280_H_ */
