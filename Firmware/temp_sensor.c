/*
 * temp_sensor.c
 *
 * Created: 28/09/2018 2:01:44 PM
 *  Author: jonga
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "i2cmaster.h"
#include "temp_sensor.h"

/**
  * @brief  Reads the temperature of the DS1621 through I2C
  * @param  None
  * @retval Temperature as read through the sensor
  */
int read_temp() {
	unsigned short result;
	int err;
	
	/*for (int i = 0; i < 0x78; i++) {
		i2c_start(i << 1);
 	}*/
	err = i2c_start(ADDRESS_WRITE);
	if (err == 1) {
		//printf("No device\n\r");
		return 1000;
	}
	i2c_write(0xEE);
	// Config reg read
	i2c_start(ADDRESS_WRITE);
	i2c_write(0xAA); 
	i2c_start(ADDRESS_READ);
	result = i2c_read(0);
	i2c_stop();
	return result;
}