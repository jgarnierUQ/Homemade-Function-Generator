/*
 * serial.h
 *
 * Created: 18/08/2018 1:36:57 PM
 *  Author: jonga
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_Flush( void );


#endif /* SERIAL_H_ */