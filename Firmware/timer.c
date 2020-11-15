/*
 * timer.c
 *
 * Created: 18/08/2018 11:08:52 AM
 *  Author: jonga
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "timer.h"

/**
  * @brief  Initialise timer 0
  * @param  None
  * @retval None
  */
void init_timer_0(void) {
	//OCR0A = Clock/(Prescalar * Rate) - 1
	OCR0A = 194;
	
	//Clear on compare match
	TCCR0A |= (0 << COM0A1) | (0 << COM0A0);
	
	//CTC mode
	TCCR0A |= (0 << WGM02) | (1 << WGM01) | (0 << WGM00);
	
	//1024 Prescalar
	TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
	
	//Enable the particular interrupt
	TIMSK0 |= (1 << OCIE0A);
	
	//Clear specific interrupt flag
	TIFR0 |= (1 << OCF0A);
}

/**
  * @brief  Initialise timer 1
  * @param  None
  * @retval None
  */
void init_timer_1(void) {
	//OCR1A = Clock/(Prescalar * Rate) - 1
	//399 = 50kHz
	OCR1A = 199;
	
	 //CTC mode
	TCCR1A = 0;
	
	//No Prescaler - CTC Mode
	TCCR1B = (1<<WGM12) | (1<<CS10) | (0 <<CS11) | (0 << CS12); 
	
	//Enable interrupt on timer on output compare match
	TIMSK1 = (1<<OCIE1A); 
	
	//Ensure interrupt flag is cleared
	TIFR1 = (1<<OCF1A);
}

/**
  * @brief  Initialise timer 2
  * @param  None
  * @retval None
  */
void init_timer_2(void) {
	//OCR0A = Clock/(Prescalar * Rate) - 1
	OCR2A = 100;
	
	//Clear on compare match
	TCCR2A |= (0 << COM2A1) | (0 << COM2A0);
	
	//CTC mode
	TCCR2A |= (0 << WGM22) | (1 << WGM21) | (0 << WGM20);
	
	//No prescaling
	TCCR2B |= (0 << CS22) | (0 << CS21) | (1 << CS20);
	
	//Enable the particular interrupt
	TIMSK2 |= (1 << OCIE2A);
	
	//Clear specific interrupt flag
	TIFR2 |= (1 << OCF2A);
}
