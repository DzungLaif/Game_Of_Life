/*
 * USART.h
 * Created: 12/23/2021 11:45:27 PM
 */ 

#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <string.h>

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

void usart_init(void);
void serial_tx_char(char DataByte);
void serial_print(char* str);
void serial_println(char* str);
void serial_printInt(uint8_t number);

#endif /* USART_H_ */