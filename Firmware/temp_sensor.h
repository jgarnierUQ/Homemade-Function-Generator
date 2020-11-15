/*
 * temp_sensor.h
 *
 * Created: 28/09/2018 2:01:58 PM
 *  Author: jonga
 */ 


#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_
#define ADRESS 0b10010000

#define ADDRESS_WRITE 0b10010000
#define ADDRESS_READ 0b10010001

int read_temp();

#endif /* TEMP_SENSOR_H_ */