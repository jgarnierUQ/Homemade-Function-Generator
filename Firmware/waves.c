/*
 * waves.c
 *
 * Created: 2/09/2018 9:06:30 PM
 *  Author: jonga
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "waves.h"

//Wave 1
uint8_t waveOneType = SINE;
uint8_t waveOneAmplitude = 255;
uint8_t waveOneOffset = 128;
int waveOneFrequency = 1000;

//Wave 2
uint8_t waveTwoType = SINE;
uint8_t waveTwoAmplitude = 255;
uint8_t waveTwoOffset = 128;
int waveTwoFrequency = 1000;

//Arrays for storing values of the current waves outputs
uint8_t outputWave1[LUT_SIZE];
uint8_t outputWave2[LUT_SIZE];

//Phase accumulator stuff
uint32_t accumulator1;
uint32_t phase1;
uint32_t accumulator2;
uint32_t phase2;

//Sine lookup table
uint8_t sineLookup[LUT_SIZE] = {128,131,134,137,140,143,146,149,
	152,155,158,162,165,167,170,173,
	176,179,182,185,188,190,193,196,
	198,201,203,206,208,211,213,215,
	218,220,222,224,226,228,230,232,
	234,235,237,238,240,241,243,244,
	245,246,248,249,250,250,251,252,
	253,253,254,254,254,255,255,255,
	255,255,255,255,254,254,254,253,
	253,252,251,250,250,249,248,246,
	245,244,243,241,240,238,237,235,
	234,232,230,228,226,224,222,220,
	218,215,213,211,208,206,203,201,
	198,196,193,190,188,185,182,179,
	176,173,170,167,165,162,158,155,
	152,149,146,143,140,137,134,131,
	128,124,121,118,115,112,109,106,
	103,100,97,93,90,88,85,82,
	79,76,73,70,67,65,62,59,
	57,54,52,49,47,44,42,40,
	37,35,33,31,29,27,25,23,
	21,20,18,17,15,14,12,11,
	10,9,7,6,5,5,4,3,
	2,2,1,1,1,0,0,0,
	0,0,0,0,1,1,1,2,
	2,3,4,5,5,6,7,9,
	10,11,12,14,15,17,18,20,
	21,23,25,27,29,31,33,35,
	37,40,42,44,47,49,52,54,
	57,59,62,65,67,70,73,76,
	79,82,85,88,90,93,97,100,
	103,106,109,112,115,118,121,124};
	
//Triangle lookup table
uint8_t triangleLookup[LUT_SIZE] = {2,4,6,8,10,12,14,16,
	18,20,22,24,26,28,30,32,
	34,36,38,40,42,44,46,48,
	50,52,54,56,58,60,62,64,
	66,68,70,72,74,76,78,80,
	82,84,86,88,90,92,94,96,
	98,100,102,104,106,108,110,112,
	114,116,118,120,122,124,126,128,
	129,131,133,135,137,139,141,143,
	145,147,149,151,153,155,157,159,
	161,163,165,167,169,171,173,175,
	177,179,181,183,185,187,189,191,
	193,195,197,199,201,203,205,207,
	209,211,213,215,217,219,221,223,
	225,227,229,231,233,235,237,239,
	241,243,245,247,249,251,253,255,
	253,251,249,247,245,243,241,239,
	237,235,233,231,229,227,225,223,
	221,219,217,215,213,211,209,207,
	205,203,201,199,197,195,193,191,
	189,187,185,183,181,179,177,175,
	173,171,169,167,165,163,161,159,
	157,155,153,151,149,147,145,143,
	141,139,137,135,133,131,129,128,
	126,124,122,120,118,116,114,112,
	110,108,106,104,102,100,98,96,
	94,92,90,88,86,84,82,80,
	78,76,74,72,70,68,66,64,
	62,60,58,56,54,52,50,48,
	46,44,42,40,38,36,34,32,
	30,28,26,24,22,20,18,16,
	14,12,10,8,6,4,2,0};
	
//Sawtooth lookup table
uint8_t sawToothLookup[LUT_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255};

//Square lookup table
uint8_t squareLookup[LUT_SIZE] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
/**
  * @brief  Generates the lookup table values for a sine wave with amplitude and offset taken into account
  * @param  Sine value for normal +/-3V wave with no offset, max amplitude, desired offset, frequency, type of wave
  * @retval Lookup table value
  */
int generate_wave(int index, int amplitude, int offset, int frequency, int type) {
	int output;
	int scaledOffset;
	
	//Calculate the offset required
	if (offset < 128) {
		scaledOffset = -1 * (128 - offset);
	} else {
		scaledOffset = offset - 128;
	}
	int byte;
	
	//Manipulate value of lookup table
	switch (type) {
		case SINE:
			output = (amplitude / 255.0) * sineLookup[index] + ((255.0 - amplitude) / 255.0) * 128.0 + scaledOffset;
			break;
			
		case TRIANGLE:
			output = (amplitude / 255.0) * triangleLookup[index] + ((255.0 - amplitude) / 255.0) * 128.0 + scaledOffset;
			break;
			
		case SAWTOOTH:
			output = (amplitude / 255.0) * sawToothLookup[index] + ((255.0 - amplitude) / 255.0) * 128.0 + scaledOffset;
			break;
			
		case REVERSE_SAWTOOTH:
			output = (amplitude / 255.0) * sawToothLookup[255 - index] + ((255.0 - amplitude) / 255.0) * 128.0 + scaledOffset;
			break;
			
		case SQUARE:
			output = (amplitude / 255.0) * squareLookup[index] + ((255.0 - amplitude) / 255.0) * 128.0 + scaledOffset;
			break;
	}
	return output;
}

/**
  * @brief  Updates the output lookup tables
  * @param  Desired amplitude, offset, frequency, which wave, and type of wave
  * @retval None
  */
void update_lookup_table(int amplitude, int offset, int frequency, int wave, int type) {
	int i;
	int prescalar;
	
	if (wave == WAVE_1) {
		for (i = 0; i < LUT_SIZE; i++) {
			outputWave1[i] = generate_wave(i, amplitude, offset, frequency, type);
		}
		
	} else if (wave == WAVE_2) {
		for (i = 0; i < LUT_SIZE; i++) {
			outputWave2[i] = generate_wave(i, amplitude, offset, frequency, type);
		}
	}
}

/**
  * @brief  Calculates the value of the phase. Should only be called once, not continually due to the function taking a long time.
  * @param  Desired frequency, which wave
  * @retval None
  */
void init_phase_accumulator(int frequency, int wave) {
	if (wave == WAVE_1) {
		accumulator1 = 0;
		phase1 = (uint32_t) ((frequency * 256. * 16777216.) / SAMPLE_RATE + 0.5);
	} else {
		accumulator2 = 0;
		phase2 = (uint32_t) ((frequency * 256. * 16777216.) / SAMPLE_RATE + 0.5);
	}
	
	
}