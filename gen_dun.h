#ifndef GEN_DUN_H
#define GEN_DUN_H

#define DUNGEON_ROWS 21
#define DUNGEON_COLUMNS 80
#define NUM_ROOMS 6
#define NUM_ROOM_CHARS 4

char dungeon[DUNGEON_ROWS][DUNGEON_COLUMNS];
int rooms[NUM_ROOMS][NUM_ROOM_CHARS];
int hardness[DUNGEON_ROWS][DUNGEON_COLUMNS];

int pc_x_position;
int pc_y_position;

int gen_dun(void);

#endif