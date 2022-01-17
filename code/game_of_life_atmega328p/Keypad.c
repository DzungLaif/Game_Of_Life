/*
 * Keypad.c
 * Created: 12/23/2021 11:00:11 PM
 */ 

#include <util/delay.h>

#include "keypad.h"

//----- Initialize keypad ROWs as output and COLs as input -----//
void keypad_init(void)
{
	//Set the rows direction as output
	ROW0_DDR	|= (1 << ROW0);
	ROW1_DDR	|= (1 << ROW1);
	ROW2_DDR	|= (1 << ROW2);
	ROW3_DDR	|= (1 << ROW3);
	
	//Set the COL direction as input
	COL0_DDR	&= ~(1 << COL0);
	COL1_DDR	&= ~(1 << COL1);
	COL2_DDR	&= ~(1 << COL2);
	COL3_DDR	&= ~(1 << COL3);
	
	//Enable COL Pull-up
	COL0_PULLUP |= (1 << COL0);
	COL1_PULLUP |= (1 << COL1);
	COL2_PULLUP |= (1 << COL2);
	COL3_PULLUP |= (1 << COL3);
	
	//Set the rows High
	ROW0_PORT	|= (1 << ROW0);
	ROW1_PORT	|= (1 << ROW1);
	ROW2_PORT	|= (1 << ROW2);
	ROW3_PORT	|= (1 << ROW3);
	
}


//----- Scan the keypad and return the pressed key and returns null if no key pressed -----//
char keypad_scan(void)
{
	uint8_t row, input;
	
	// Loop on each row
	for(row = 0; row < 4; row++)
	{
		//Set all row high
		ROW0_PORT |= (1 << ROW0);
		ROW1_PORT |= (1 << ROW1);
		ROW2_PORT |= (1 << ROW2);
		ROW3_PORT |= (1 << ROW3);
		
		// Clear row number from iteration
		switch(row)
		{
			case 0: ROW0_PORT &= ~(1 << ROW0);	break;
			case 1: ROW1_PORT &= ~(1 << ROW1);	break;
			case 2: ROW2_PORT &= ~(1 << ROW2);	break;
			case 3: ROW3_PORT &= ~(1 << ROW3);	break;
		}
		
		// Must-have delay between Output and Input
		_delay_ms(10);
		
		// Read the Inputs
		input = (COL0_PIN & (1 << COL0));
		input |= (COL1_PIN & (1 << COL1));
		input |= (COL2_PIN & (1 << COL2));
		input |= (COL3_PIN & (1 << COL3));
		
		// Checking if this was Input
		if (ALL_COLS != 1)
		{
			// Waiting until key is released
			//while (ALL_COLS != 1);
			
			break;
		}
		
	}
	
	// When there is no Input
	if (row == 4) return 0;
	
	// Checking cases
	switch(row)
	{
		case 0:
		switch(input)
		{
			case CODE_1: return '1';
			case CODE_2: return '2';
			case CODE_3: return '3';
			case CODE_4: return 'A';
		}
		case 1:
		switch(input)
		{
			case CODE_1: return '4';
			case CODE_2: return '5';
			case CODE_3: return '6';
			case CODE_4: return 'B';
		}
		case 2:
		switch(input)
		{
			case CODE_1: return '7';
			case CODE_2: return '8';
			case CODE_3: return '9';
			case CODE_4: return 'C';
		}
		case 3:
		switch(input)
		{
			case CODE_1: return '*';
			case CODE_2: return '0';
			case CODE_3: return '#';
			case CODE_4: return 'D';
		}
	}
	return 0;
}