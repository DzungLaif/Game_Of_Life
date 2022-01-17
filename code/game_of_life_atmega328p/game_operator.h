/*
 * game_operator.h
 * Created: 1/2/2022 3:00:23 PM
 */ 


#ifndef GAME_OPERATOR_H_
#define GAME_OPERATOR_H_

#define WORLD_DIMENSION_HEIGHT		16
#define WORLD_DIMENSION_WIDTH		16	//MUST BE DIVIDED BY 8

#define CELL_SIZE					10	//in pixels
#define WORLD_MARGIN				8	//in pixels

void write_world_to_eeprom();
void read_world_from_eeprom();
void world_display(int color_mode);
void world_init();
void game_init();
void game_handle();
void generate_random_world(int density);
void generate_empty_world();
void next_world_generation();
void migrate_to_next_world();
void display_cellular(int w, int i, int h, int state, int color_mode) ;

#endif /* GAME_OPERATOR_H_ */