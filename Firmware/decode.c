/*
 * decode.c
 *
 * Created: 2/09/2018 7:36:58 PM
 *  Author: jonga
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "decode.h"
#include "waves.h"

//Counter for which parameter is being read in
uint8_t paramCount;

//Wave Parameters strings
char waveOneOrTwo[2];
char type[2];
char amplitude[4];
char offset[4];
char frequency[6];

//Wave Parameters ints and floats
uint8_t numWaveOneOrTwo;
uint8_t numType;
uint8_t numAmplitude;
uint8_t numOffset;
int numFrequency;

/**
  * @brief  Receives input chars that are sent from GUI and updates waves accordingly
  * @param  Character received from GUI
  * @retval None
  */
void handle_input(char rxChar) {
	if (rxChar == '<') {
		//Start character
		paramCount = 0;		
		
	} else if (rxChar == ',') {
		//Next parameter
		paramCount++;
		
	} else if (rxChar == '>') {		
		//Convert to ints and floats
		numWaveOneOrTwo = atoi(waveOneOrTwo);
		numType = atoi(type);
		numAmplitude = atoi(amplitude);
		numOffset = atoi(offset);
		numFrequency = atoi(frequency);
		
		//Update waves
		if (numWaveOneOrTwo == WAVE_1) {
			//Set new parameters
			waveOneType = numType;
			waveOneAmplitude = numAmplitude;
			waveOneOffset = numOffset;
			waveOneFrequency = numFrequency;
			
			//Update lookup table
			update_lookup_table(waveOneAmplitude, waveOneOffset, waveOneFrequency, WAVE_1, waveOneType);
			
			//Update Phase Accumulator
			init_phase_accumulator(waveOneFrequency, WAVE_1);
			
		} else if (numWaveOneOrTwo == WAVE_2) {
			//Set new parameters
			waveTwoType = numType;
			waveTwoAmplitude = numAmplitude;
			waveTwoOffset = numOffset;
			waveTwoFrequency = numFrequency;
			
			//Update lookup table
			update_lookup_table(waveTwoAmplitude, waveTwoOffset, waveTwoFrequency, WAVE_2, waveTwoType);
			
			//Update Phase Accumulator
			init_phase_accumulator(waveTwoFrequency, WAVE_2);
		}
		
		//Clear strings
		memset(waveOneOrTwo,0,strlen(waveOneOrTwo));
		memset(type,0,strlen(type));
		memset(amplitude,0,strlen(amplitude));
		memset(offset,0,strlen(offset));
		memset(frequency,0,strlen(frequency));

	} else {
		//Add the char to current parameter string
		switch (paramCount) {
			case 0:
				sprintf(waveOneOrTwo, "%s%c", waveOneOrTwo, rxChar);
				break;
										
			case 1:
				sprintf(type, "%s%c", type, rxChar);
				break;

			case 2:
				sprintf(amplitude, "%s%c", amplitude, rxChar);
				break;
				
			case 3:
				sprintf(offset, "%s%c", offset, rxChar);
				break;
				
			case 4:
				sprintf(frequency, "%s%c", frequency, rxChar);
				break;
		}
	}
}

