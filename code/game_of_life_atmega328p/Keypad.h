/*
 * Keypad.h
 * Created: 12/23/2021 10:58:47 PM
 */ 

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <stdint.h>
#include <avr/io.h>

//----- I/O Pins Configurations -----//
/*					4x4 Keypad Layouts
||			-------------------------------------
||	ROW0	|	[1]		[2]		[3]		[A]		|
||	ROW1	|	[4]		[5]		[6]		[B]		|
||	ROW2	|	[7]		[8]		[9]		[C]		|
||	ROW3	|	[*]		[0]		[#]		[D]		|
||			-------------------------------------
||				COL0	COL1	COL2	COL3			
*/

#define		ROW0			1
#define		ROW0_DDR		DDRB
#define		ROW0_PORT		PORTB	

#define		ROW1			0
#define		ROW1_DDR		DDRB
#define		ROW1_PORT		PORTB

#define		ROW2			7
#define		ROW2_DDR		DDRD
#define		ROW2_PORT		PORTD

#define		ROW3			6
#define		ROW3_DDR		DDRD
#define		ROW3_PORT		PORTD

#define		COL0			5
#define		COL0_DDR		DDRD
#define		COL0_PIN		PIND
#define		COL0_PULLUP		PORTD

#define		COL1			4
#define		COL1_DDR		DDRD
#define		COL1_PIN		PIND
#define		COL1_PULLUP		PORTD

#define		COL2			3
#define		COL2_DDR		DDRD
#define		COL2_PIN		PIND
#define		COL2_PULLUP		PORTD

#define		COL3			2
#define		COL3_DDR		DDRD
#define		COL3_PIN		PIND
#define		COL3_PULLUP		PORTD

#define		ALL_COLS		 (((COL0_PIN & (1 << COL0)) >> COL0)\
							& ((COL1_PIN & (1 << COL1)) >> COL1)\
							& ((COL2_PIN & (1 << COL2)) >> COL2)\
							& ((COL3_PIN & (1 << COL3)) >> COL3))
						
#define		CODE_1			0x1C
#define		CODE_2			0x2C
#define		CODE_3			0x34
#define		CODE_4			0x38

//----- Functions Prototypes -----//
void keypad_init(void);
char keypad_scan(void);

#endif /* KEYPAD_H_ */