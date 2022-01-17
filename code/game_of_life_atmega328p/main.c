/*
 * game_of_life_atmega328p.c
 * Created: 1/2/2022 2:28:38 PM
 */ 

#include "usart.h"
#include "eeprom_handle.h"
#include "lcd_handle.h"
#include "Keypad.h"

#include "game_operator.h"

#include <util/delay.h>
#include <string.h>

void append(char* s, char c) {
	int len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
}

int main(void)
{
	CLKPR = (1 << CLKPCE);
	CLKPR = 0;
	
	usart_init();
	
	eeprom_init();
	
	ILI9225_init();
	
	keypad_init();
	
	while (1) {
		game_init();	
		game_handle();
	}
	
	return 0;
}
