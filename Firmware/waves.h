/*
 * waves.h
 *
 * Created: 2/09/2018 9:06:21 PM
 *  Author: jonga
 */ 


#ifndef WAVES_H_
#define WAVES_H_

#define LUT_SIZE 256
#define SYSCLK 20000000L
#define SAMPLE_RATE 100000
#define SET 0
#define NOT_SET 1
#define WAVE_1 1
#define WAVE_2 2

#define SINE 0
#define TRIANGLE 1
#define SAWTOOTH 2
#define REVERSE_SAWTOOTH 3
#define SQUARE 4

//Wave 1
extern uint8_t waveOneType;
extern uint8_t waveOneAmplitude;
extern uint8_t waveOneOffset;
extern int waveOneFrequency;

//Wave 2
extern uint8_t waveTwoType;
extern uint8_t waveTwoAmplitude;
extern uint8_t waveTwoOffset;
extern int waveTwoFrequency;

//Lookup tables
uint8_t sineLookup[LUT_SIZE];
uint8_t triangleLookup[LUT_SIZE];
uint8_t sawToothLookup[LUT_SIZE];
uint8_t squareLookup[LUT_SIZE];

//Output wave tables
extern uint8_t outputWave1[LUT_SIZE];
extern uint8_t outputWave2[LUT_SIZE];

//Phase accumulator stuff
extern uint32_t accumulator1;
extern uint32_t phase1;
extern uint32_t accumulator2;
extern uint32_t phase2;

int generate_wave(int index, int amplitude, int offset, int frequency, int type);
void update_lookup_table(int amplitude, int offset, int frequency, int wave, int type);
void init_phase_accumulator(int frequency, int wave);


#endif /* WAVES_H_ */