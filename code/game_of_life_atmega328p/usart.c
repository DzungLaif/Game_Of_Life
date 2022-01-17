/*
 * USART.c
 * Created: 12/23/2021 11:45:02 PM
 */ 

#include "usart.h"
#include <stdlib.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void usart_init(void)
{
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	serial_println("Serial begin at Baudrate 9600.");
}

void serial_tx_char(char DataByte)
{
	while ((UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
	UDR0 = DataByte;
}

void serial_print(char* str)
{
	for (uint8_t j = 0; j < (strlen(str) + 1); j++)
		serial_tx_char(str[j]);
}

void serial_println(char* str)
{
	for (uint8_t j = 0; j < (strlen(str) + 1); j++)
		serial_tx_char(str[j]);
	serial_tx_char(13);
}

void serial_printInt(uint8_t number)
{
	char temp[10];
	
	itoa(number, temp, 10);
	
	serial_print(temp);	
}