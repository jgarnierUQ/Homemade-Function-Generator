# Homemade-Function-Generator
Project at uni where I designed the hardware and firmware for a function generator capable of generating sine, square, triangle, sawtooth, and reverse sawtooth waves up to 10kHz.

The whole project was comprised of three blocks that connected to each other: The function generator, a filter, and a power amplifier.

<img src="https://github.com/jgarnierUQ/Homemade-Function-Generator/blob/main/functionGenAllBlocks.JPG" alt="drawing" width="700"/>

I was responsible for the function generator block, of which I designed all of the hardware and firmware.
<img src="https://github.com/jgarnierUQ/Homemade-Function-Generator/blob/main/functionGen.JPG" alt="drawing" width="700"/>

I utilised an Atmega324 for the processor as we were limited to 8-bit microcontrollers for this project. I was able to output the required waveforms by creating my own Digital to Analog Converters using resistor ladders, and then using look-up tables in firmware to control the waveforms.

This project was quite challenging but extremely rewarding once it was a working product. By far the most challenging aspect was the firmware, specifically being able to change the frequency of the waves. For this I implemented a phase accumulator (https://en.wikipedia.org/wiki/Numerically-controlled_oscillator), which caused a lot of headaches but got the job done! All of the code is available to view as well as my hardware schematics and Altium layouts.
