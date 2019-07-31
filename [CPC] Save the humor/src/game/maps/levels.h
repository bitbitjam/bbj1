#ifndef _LEVELS_H_
#define _LEVELS_H_

#include "entities.h"

/// Struct groping and entity and its type
typedef struct entity_init_pos {
	unsigned char type;		// Entity type
	unsigned char tx, ty;	// Initial position
} TEntityInitPos;

/// Struct containing all the information about a level
typedef struct level {
	unsigned char*	map;		// 20x20 tilemap of the level
	unsigned char* 	tileset;	// Tileset containing the tiles used by this map
	unsigned char   song;		// Song that will be played
	unsigned char   title[40];	// Title of the level
	unsigned char	numEntities;// Total number of entities (including main character)
	TEntityInitPos	initEnt[7]; // Initial positions of entities (0 = main Character)
} TLevel;

#define NUM_GAME_LEVELS	3
extern TLevel GAME_LEVELS[NUM_GAME_LEVELS];

#endif