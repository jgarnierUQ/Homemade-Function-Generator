/*
 * functionGenerator.c
 *
 * Created: 17/08/2018 3:42:33 PM
 * Author : jonga
 */ 

/* 
		DAC1
A7 A6 A5 A4 A3 A2 A1 A0

		DAC2
D7 D6 D5 D4 D3 D2 C1 C0

(MSB) ... (LSB)
*/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <util/delay.h>
#include <math.h>
#include "timer.h"
#include "serialio.h"
#include "waves.h"
#include "decode.h"
#include "i2cmaster.h"
#include "temp_sensor.h"

#define SYSCLK 20000000L
#define SET 0
#define NOT_SET 1
#define LUT_SIZE 256

ISR(TIMER0_COMPA_vect);
ISR(TIMER1_COMPA_vect);
ISR(TIMER2_COMPA_vect);

//Index values for lookup tables - overflows over 255 and goes back to 0
uint8_t index1 = 0;
uint8_t index2 = 0;

//Values to output to DAC
uint8_t outputValue1;
uint8_t outputValue2;

//Initialising temperature sensor variables
int tempCounter = 0;
int temp = 0;
int tempFlag = NOT_SET;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void) {	
	
	//Set up pins as outputs
	DDRA = 0xFF;
	DDRC = 0XFF;
	DDRD = 0XFF;
	
	//Initalise timer and interrupt to fire at 50kHz
	init_timer_0();
	init_timer_1();
	
	//Initialize USART
	init_serial_stdio(9600,0);
	
	//Initialise lookup tables
	update_lookup_table(waveOneAmplitude, waveOneOffset, waveOneFrequency, WAVE_1, waveOneType);
	update_lookup_table(waveTwoAmplitude, waveTwoOffset, waveTwoFrequency, WAVE_2, waveTwoType);
	
	//Initialise phase accumulator values
	init_phase_accumulator(waveOneFrequency, WAVE_1);
	init_phase_accumulator(waveTwoFrequency, WAVE_2);
	
	//Initialise I2C communication
	i2c_init();
	
	//Turn on global interrupts
	sei();
	printf("starting again\n\r");
	//Main loop - Everything handled by interrupts
	while (1) {
		if (tempFlag == 0) {
			//Send temp
			temp = read_temp();
			printf("%d\n\r", temp);
			tempFlag = NOT_SET;
		}
		_delay_us(1);
	}
}

//Timer interrupt to increment lookup table index - WAVE 2
ISR(TIMER0_COMPA_vect) {
	if (tempCounter == 100) { //Every second
		//Set flag to read temperature
		tempFlag = SET;
		tempCounter = 0;
	}
	tempCounter++;
}

//Timer interrupt to increment lookup table index - WAVE 1
ISR(TIMER1_COMPA_vect) {
	//Compute DAC1 value
	index1 = (uint8_t) (accumulator1 >> 24) & 0xFF;
	outputValue1 = outputWave1[index1];
	accumulator1 += phase1;
	
	//Compute DAC2 value
	index2 = (uint8_t) (accumulator2 >> 24) & 0xFF;
	outputValue2 = outputWave2[index2];
	accumulator2 += phase2;
	
	//Output to DAC1
	PORTA = (outputValue1 & 0xFF);
	
	//Output to DAC2
	PORTD = (outputValue2 & 0b11111100);
	PORTC = ((outputValue2 << 6) & 0b11000000);
}

ISR(USART0_RX_vect) {
	//Interrupt entered - char has been received
	char input;

	//Extract character from UART Data register and place in input variable
	input = UDR0;

	//Handle received char
	handle_input(input);
	UDR0 = input;
}