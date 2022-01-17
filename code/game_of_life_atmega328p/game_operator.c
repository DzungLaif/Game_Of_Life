/*
 * game_operator.c
 * Created: 1/2/2022 3:00:08 PM
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "game_operator.h"
#include "eeprom_handle.h"
#include "lcd_handle.h"
#include "keypad.h"
#include "usart.h"

#define TOTAL_ROWS	WORLD_DIMENSION_HEIGHT
#define TOTAL_COLS	WORLD_DIMENSION_WIDTH/8

uint8_t current_world[TOTAL_ROWS][TOTAL_COLS];

void write_world_to_eeprom() {
	for (int h = 0; h < TOTAL_ROWS; h++)
		for (int w = 0; w < TOTAL_COLS; w++) {
			int address = (h*TOTAL_COLS) + w ; 
			eeprom_write(address, current_world[h][w]);
			_delay_us(1);
			/*
			serial_print("[");
			serial_printInt(h);
			serial_print(",");
			serial_printInt(w);
			serial_print("] Wrote ");
			serial_printInt(current_world[h][w]);
			serial_print(" at address ");
			serial_printInt(address);
			serial_tx_char(13);
			*/
		}
}

void read_world_from_eeprom() {
	for (int h = 0; h < TOTAL_ROWS; h++)
		for (int w = 0; w < TOTAL_COLS; w++) {
			int address = (h*TOTAL_COLS) + w ;
			current_world[h][w] = eeprom_read(address);
			
			/*
			serial_print("[");
			serial_printInt(h);
			serial_print(",");
			serial_printInt(w);
			serial_print("] Read ");
			serial_printInt(current_world[h][w]);
			serial_print(" at address ");
			serial_printInt(address);
			serial_tx_char(13);
			*/
		}
}

int game_rule_check(int h, int w, int i) {
	int bit[8];
	for (int j = 0; j < 8; j++) bit[j] = 0;
	
	/**             -------------> w+
	**		bit[0]		bit[1]		bit[2]		|
	**		bit[7]	   [h, w+i]		bit[3]		|
	**		bit[6]		bit[5]		bit[4]		v h+
	**/
	
	if (h > 0) {
		bit[1] = (current_world[h-1][w] & (0x80 >> i)) >> (7-i);
		
		if (i > 0) bit[0] = (current_world[h-1][w] & (0x80 >> (i-1))) >> (7-(i-1));
		else {
			if (w > 0) bit[0] =  current_world[h-1][w-1] & (0x01);
			else bit[0] = 0;
		}
		
		if (i < 7) //19 1 6
			bit[2] = (current_world[h-1][w] & (0x80 >> (i+1))) >> (7-(i+1));
		else {
			if (w < WORLD_DIMENSION_WIDTH-1) bit[2] =  current_world[h-1][w+1] & (0x80);
			else bit[2] = 0;
		}
	}
	else {
		bit[0] = 0;	bit[1] = 0;	bit[2] = 0;
	}
	
	if (h < WORLD_DIMENSION_HEIGHT-1) {
		bit[5] = (current_world[h+1][w] & (0x80 >> i)) >> (7-i);
		
		if (i > 0) bit[6] = (current_world[h+1][w] & (0x80 >> (i-1))) >> (7-(i-1));
		else {
			if (w > 0) bit[6] =  current_world[h+1][w-1] & (0x01);
			else bit[6] = 0;
		}
		
		if (i < 7)
		bit[4] = (current_world[h+1][w] & (0x80 >> (i+1))) >> (7-(i+1));
		else {
			if (w < WORLD_DIMENSION_WIDTH-1) bit[4] =  current_world[h+1][w+1] & (0x80);
			else bit[4] = 0;
		}
	}
	else {
		bit[4] = 0;	bit[5] = 0;	bit[6] = 0;
	}
	
	if (i > 0) bit[7] = (current_world[h][w] & (0x80 >> (i-1))) >> (7-(i-1));
	else {
		if (w > 0) bit[7] =  current_world[h][w-1] & (0x01);
		else bit[7] = 0;
	}
	// 20 1 5
	if (i < 7) bit[3] = (current_world[h][w] & (0x80 >> (i+1))) >> (7-(i+1));
	else {
		if (w < WORLD_DIMENSION_WIDTH-1) bit[3] =  current_world[h][w+1] & (0x80);
		else bit[3] = 0;
	}
	
	int total_neightboor = 0;
	int current_cell = (current_world[h][w] & (0x80 >> i)) >> (7-i);
	int check_case = 1;
	
	for (int j = 0; j < 8; j++)
		if (bit[j]) total_neightboor++;
	
	if (((total_neightboor > 3) | (total_neightboor < 2)) & (current_cell)) check_case = 3;
	else if ((total_neightboor == 3) & (!current_cell)) check_case = 2;
	
	/*
	if (check_case != 1) {
		serial_print("[");
		serial_printInt(h);
		serial_print(",");
		serial_printInt(w);
		serial_print(",");
		serial_printInt(i);
		serial_print("] : case ");
		serial_printInt(check_case);
		serial_print(" neightboors ");
		serial_printInt(total_neightboor);
		serial_print(" [");
		for (int j = 0; j < 8; j++) {serial_printInt(bit[j]); serial_tx_char(',');};
		serial_print("]");
		serial_tx_char(13);
		}
	*/
	return check_case;
		
}

void next_world_generation() {
	uint8_t temp_world[TOTAL_ROWS][TOTAL_COLS]; 
	
	for (int h = 0; h < TOTAL_ROWS; h++)
		for (int w = 0; w < TOTAL_COLS; w++)
			temp_world[h][w] = current_world[h][w];
	
 	for (int h = 0; h < TOTAL_ROWS; h++)
		for (int w = 0; w < TOTAL_COLS; w++)
			for (int bit = 0; bit < 8; bit++)
			{
				switch(game_rule_check(h, w, bit)) 
				{
					case 1: //stays the same (do nothing)
						break;
					case 2: //becomes alive
						temp_world[h][w] = (temp_world[h][w] | (0x80 >> bit));
						break;
					case 3: //dies
						temp_world[h][w] = (temp_world[h][w] ^ (0x80 >> bit));
						break;
				}
			}
			
	for (int h = 0; h < TOTAL_ROWS; h++)
		for (int w = 0; w < TOTAL_COLS; w++)
			current_world[h][w] = temp_world[h][w];	
}

void generate_empty_world() {
	for (int h = 0; h < TOTAL_ROWS; h++)
	for (int w = 0; w < TOTAL_COLS; w++)
	current_world[h][w] = 0x00;
}

void display_cellular( int h, int w, int i, int state, int color_mode) {
	uint16_t color = COLOR_BLACK;
	
	if (!color_mode) color = (state?COLOR_WHITE:COLOR_BLACK);
	else {
		int state_color = game_rule_check(h, w, i);
		
		switch(state_color) {
			case 1:
				if (state) color = COLOR_YELLOWGREEN;
				break;
			case 2:
				color = COLOR_GREEN;
				break;
			case 3:
				color = COLOR_RED;
				break;	
		}
	}
	
	w = w*8 + i;
	
	ILI9225_fillRectangle(
	(w*CELL_SIZE) + WORLD_MARGIN,
	(h*CELL_SIZE) + WORLD_MARGIN,
	(w*CELL_SIZE) + WORLD_MARGIN + CELL_SIZE,
	(h*CELL_SIZE) + WORLD_MARGIN + CELL_SIZE,
	color);
	
}	 

void world_display(int color_mode) {
	for (int h = 0; h < TOTAL_ROWS; h++)
		for (int w = 0; w < TOTAL_COLS; w++) {
			
			uint8_t divider = 0x80;
			
			for (uint8_t i = 0; i <= 7; i++)
			{
				if (current_world[h][w] & divider)
					display_cellular(h, w, i, 1, color_mode);
				else
					display_cellular(h, w, i, 0, color_mode);
					
				divider = divider >> 1;
			}
		}
}

void generate_random_world(int density) {
	for (int h = 0; h < TOTAL_ROWS; h++)
		for (int w = 0; w < TOTAL_COLS; w++) {
			uint8_t divider = 0x80;
			uint8_t temp = 0x00;
			
			for (int bit = 0; bit < 8; bit++) {
				if (rand() % 100 < density)
					temp = temp + divider;
				divider = divider >> 1;
			}
			
			current_world[h][w] = temp;
		}
}

void world_init() {
	ILI9225_drawRectangle(WORLD_MARGIN-1, WORLD_MARGIN-1,
		WORLD_MARGIN+CELL_SIZE*WORLD_DIMENSION_WIDTH+1,
		WORLD_MARGIN+CELL_SIZE*WORLD_DIMENSION_HEIGHT+1,
		COLOR_WHITE);
}

void game_init() {
	ILI9225_clear();
	ILI9225_drawRectangle(WORLD_MARGIN - 1, WORLD_MARGIN - 1,
						ILI9225_LCD_WIDTH  - (WORLD_MARGIN + 1),
						ILI9225_LCD_HEIGHT - (WORLD_MARGIN + 1),
						COLOR_WHITE);
	
	ILI9225_setFont(Terminal12x16, 0);
	ILI9225_drawText(20, 30, "GAME OF LIFE", strlen("GAME OF LIFE"), COLOR_WHITE);
	
	ILI9225_setFont(Terminal6x8, 0);
	ILI9225_drawText(50, 60, "ATMEGA328P", strlen("ATMEGA328P"), COLOR_ORANGE);
	
	ILI9225_drawText(20, 90, "KEYPAD INSTRUCTION:", strlen("KEYPAD INSTRUCTION:"), COLOR_WHITE);
	ILI9225_drawText(30, 110, "Press * to start", strlen("Press * to start"), COLOR_WHITE);
	ILI9225_drawText(75, 120, "a new world", strlen("a new world"), COLOR_WHITE);

	ILI9225_drawText(30, 140, "Press # to continue", strlen("Press # to continue"), COLOR_WHITE);
	ILI9225_drawText(35, 150, "world from EEPROM", strlen("world from EEPROM"), COLOR_WHITE);
	
	ILI9225_drawText(32, 185, "Cre: Lai Ngoc Dung", strlen("Cre: Lai Ngoc Dung"), COLOR_ORANGE);
}

int display_rand() {
	ILI9225_clear();

	ILI9225_drawRectangle(WORLD_MARGIN - 1, WORLD_MARGIN - 1,
	ILI9225_LCD_WIDTH  - (WORLD_MARGIN + 1),
	ILI9225_LCD_HEIGHT - (WORLD_MARGIN + 1),
	COLOR_WHITE);
	
	ILI9225_setFont(Terminal11x16, 0);
	ILI9225_drawText(20, 30, "Press 1-9", strlen("Press 1-9"), COLOR_WHITE);
	
	ILI9225_setFont(Terminal6x8, 0);
	ILI9225_drawText(20, 50, "to choose cell density", strlen("to choose cell density"), COLOR_ORANGE);
	ILI9225_drawText(20, 60, "of your random world", strlen("of your random world"), COLOR_ORANGE);

	ILI9225_drawText(20, 90, "EXAMPLE:", strlen("EXAMPLE:"), COLOR_WHITE);
	ILI9225_drawText(30, 110, "Press 2 for ", strlen("Press 2 for "), COLOR_WHITE);
	ILI9225_drawText(40, 120, "20% cell density", strlen("20% cell density"), COLOR_WHITE);
	ILI9225_drawText(30, 135, "Press 3 for ", strlen("Press 3 for "), COLOR_WHITE);
	ILI9225_drawText(40, 145, "30% cell density", strlen("30% cell density"), COLOR_WHITE);
	
	ILI9225_drawText(40, 185, "Press D to exit", strlen("Press D to exit"), COLOR_ORANGE);

	char key_pressed = 0;
	while ((key_pressed < 49) | (key_pressed > 57)) {
		key_pressed = keypad_scan();
		
		if (key_pressed == 'D') return 0;
	}
	
	return (key_pressed - 48);
}

void display_generating() {
	ILI9225_clear();

	ILI9225_drawRectangle(WORLD_MARGIN - 1, WORLD_MARGIN - 1,
	ILI9225_LCD_WIDTH  - (WORLD_MARGIN + 1),
	ILI9225_LCD_HEIGHT - (WORLD_MARGIN + 1),
	COLOR_WHITE);
	
	ILI9225_setFont(Terminal12x16, 0);
	ILI9225_drawText(20, 40, "GENERATING", strlen("GENERATING"), COLOR_ORANGE);
	ILI9225_drawText(40, 60, "WORLD", strlen("WORLD"), COLOR_ORANGE);
	
	ILI9225_setFont(Terminal6x8, 0);
	ILI9225_drawText(30, 80, "Please wait...", strlen("Please wait..."), COLOR_WHITE);
}

void display_continuing() {
	ILI9225_clear();

	ILI9225_drawRectangle(WORLD_MARGIN - 1, WORLD_MARGIN - 1,
	ILI9225_LCD_WIDTH  - (WORLD_MARGIN + 1),
	ILI9225_LCD_HEIGHT - (WORLD_MARGIN + 1),
	COLOR_WHITE);
	
	ILI9225_setFont(Terminal12x16, 0);
	ILI9225_drawText(20, 40, "CONTINUING", strlen("CONTINUING"), COLOR_ORANGE);
	ILI9225_drawText(40, 60, "WORLD", strlen("WORLD"), COLOR_ORANGE);
	
	ILI9225_setFont(Terminal6x8, 0);
	ILI9225_drawText(30, 80, "Please wait...", strlen("Please wait..."), COLOR_WHITE);
}

void  display_game_info() {
	ILI9225_drawText(10, 180, "Hold C to toggle color", strlen("Hold C to toggle color"), COLOR_ORANGE);
	ILI9225_drawText(10, 190, "Hold D to exit", strlen("Hold D to exit"), COLOR_ORANGE);
}

void game_on() {
	char key_pressed = 0;
	int color_mode = 0;
	
	while ((key_pressed != 'D')) {
		key_pressed = keypad_scan();
		if (key_pressed == 'C') color_mode = !color_mode;
		next_world_generation();
		write_world_to_eeprom();
		world_display(color_mode);
	}
	
}

void start_new_game() {
	int rand_num = display_rand();
	
	if (!rand_num) return;
	
	display_generating();
	
	generate_random_world(rand_num*10);
	write_world_to_eeprom();
	
	ILI9225_clear();
	world_init();
	display_game_info();
	
	world_display(0);
	game_on();
}

void continue_game() {
	display_continuing();
	read_world_from_eeprom();
	
	ILI9225_clear();
	world_init();
	display_game_info();
	
	world_display(0);
	game_on();
}

void exit_game() {
	ILI9225_clear();

	ILI9225_drawRectangle(WORLD_MARGIN - 1, WORLD_MARGIN - 1,
	ILI9225_LCD_WIDTH  - (WORLD_MARGIN + 1),
	ILI9225_LCD_HEIGHT - (WORLD_MARGIN + 1),
	COLOR_WHITE);
	
	ILI9225_setFont(Terminal12x16, 0);
	ILI9225_drawText(20, 100, "EXIT GAME...", strlen("EXIT GAME..."), COLOR_YELLOW);
	
	_delay_ms(3000);
}

void game_handle() {
	char key_pressed;
	
	while (1)
	{
		key_pressed = keypad_scan();
		
		if (key_pressed == '*') {
			start_new_game();
			exit_game();
			break;
		}
		else if (key_pressed == '#') {
			continue_game();
			exit_game();	
			break;
		}
	}
}
