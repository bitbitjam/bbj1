#include <cpcrslib.h>
#include "entities.h"
#include "mapas.h"
#include "../sprites/sprites.h"


// AI States for LEFT_RIGHT
#define	AI_GOING_LEFT	0
#define AI_GOING_RIGHT	1

TEntity GAME_ENTITIES[MAX_ENTITIES];

unsigned char abs(char n) { 
	return (n < 0) ? -n : n;
}

void ent_moveEntity(TEntity* e) {
	unsigned char tx = (e->x >> 2);	// (tx, ty) tile position of the entity
	unsigned char ty = (e->y >> 2);
	unsigned char d_tx = (e->x & 3);	// d_tx, d_ty displacement (0-3) inside the tile position
	unsigned char d_ty = (e->y & 3);
	unsigned char orig_tx = tx;			// Origintal tile positions
	unsigned char orig_dtx = d_tx; 		// Origintal displacements
	
	// Check horizontal movement (BEWARE! Assume vx € [-1, 1])
	if (e->vx) {
		// Only check collitions when we move at a tile boundary
		if (!d_tx) {
			unsigned char h1 = (d_ty) ? 3-1 : 2-1; 	// height in tiles - 1 (2 or 1)
			unsigned char tileinfo = maps_getTileInfo(tx + e->vx, ty + h1);
			if (tileinfo & 0x01) 	// Bit 7 = 1 ==> Tile is solid
				e->vx = 0;
		}
		
		// Update X position before checking Y
		e->x += e->vx;
		tx   = (e->x >> 2);
		d_tx = (e->x & 3);
		e->moved = 1;
		// Flipping sprite on direction change
		if (! (e->vx + e->heading) ) {
			e->heading = -e->heading;
			spr_flipHorizontalMask(e->sprite);
		}						
	}
	
	// Check for jump
	if (e->vy < 0 && e->jump < MAX_JUMP) {
		e->jump++;
	// And for gravity
	} else {
		e->jump = MAX_JUMP;
		e->vy = 1;		// Assume we are always falling
		if (!d_ty) {    // Only check for collision at tile boundary
			unsigned char tileinfo = maps_getTileInfo(tx, ty + 2);
			if (d_tx)	// Sometimes the entity occupies 2 tiles width
				tileinfo |= maps_getTileInfo(tx + 1, ty + 2);
			if (tileinfo & 0x01) {	// Bit 7 = 1 ==> Tile is solid (or some of the two)
				e->vy = 0;
				e->jump = 0;
			}
		}
	}

    // Update Y position 
	if (e->vy) {
		e->y += e->vy;
		e->moved = 1;
	}

	// Mark tiles for redraw if moved
	if (e->moved) {
		unsigned char w = (orig_dtx) ? 2 : 1;
		unsigned char h = (d_ty) ? 3 : 2;
		maps_markTilesForRedraw(orig_tx, ty, w, h);
	}
}

void ent_processAI(TEntity* e) {
	unsigned char tx = (e->x >> 2);	// (tx, ty) tile position of the entity
	unsigned char ty = (e->y >> 2);
	unsigned char d_tx = (e->x & 3);	// (tx, ty) tile position of the entity
	unsigned char d_ty = (e->y & 3);	
	
	/// TODO: Disastrous, horrible, fast code. Please, change ASAP :)
	switch (e->type) {
		case ENT_SCIENTIST_LEFTRIGHT:
		case ENT_TIEMAN_LEFTRIGHT:
		case ENT_SOLDIER_LEFTRIGHT:
		case ENT_GLADIATOR_LEFTRIGHT:
		case ENT_ROMAN_LEFTRIGHT:
		case ENT_ALIEN_LEFTRIGHT: {
			switch (e->stateAI) {
				case AI_GOING_LEFT:	{
					e->vx = -1;
					// Check if there is a left solid tile when we are at boundary
					if (!d_tx) {
						// We want the tile that is at the same level of our feet
						unsigned char h1 = (d_ty) ? 3-1 : 2-1; 
						if (maps_getTileInfo(tx - 1, ty + h1) & 0x01) { // Check if the tile is solid
							e->stateAI = AI_GOING_RIGHT;
							e->vx = 0;
						}
					}
					break;
				}
				case AI_GOING_RIGHT: {
					e->vx = 1;
					// Check if there is a left solid tile when we are at boundary
					if (!d_tx) {
						// We want the tile that is at the same level of our feet
						unsigned char h1 = (d_ty) ? 3-1 : 2-1; 
						if (maps_getTileInfo(tx + 1, ty + h1) & 0x01) { // Check if the tile is solid
							e->stateAI = AI_GOING_LEFT;
							e->vx = 0;
						}
					}
					break;
				}
			}
		}
	}
}

char ent_checkCollision(TEntity *eA, TEntity *eB, unsigned char w, unsigned char h) {
	if (abs(eA->x - eB->x) < w) {
		if (abs(eA->y - eB->y) < h) {
			return 1;
		}
	}
	return 0;
}

char ent_checkCollisionWithJoke(TEntity *joke, TEntity *e) {
	unsigned char dy = abs(joke->y - e->y);
	if (abs(joke->x - e->x) < 3) {
		if ( ( joke->y >= e->y && dy < 3 ) || dy < 7 ) {
			return 1;
		}
	}
	return 0;
}

char ent_moveJoke(TEntity* e) {
	unsigned char tx = (e->x >> 2);	// (tx, ty) tile position of the entity
	unsigned char ty = (e->y >> 2);
	unsigned char d_tx = (e->x & 3);	// d_tx, d_ty displacement (0-3) inside the tile position
	unsigned char d_ty = (e->y & 3);
	unsigned char orig_tx = tx;			// Origintal tile positions
	unsigned char orig_dtx = d_tx;			// Origintal tile positions
	e->moved = 0;
	
	// Check horizontal movement (BEWARE! Assume vx € [-1, 1])
	if (e->vx) {
		// Only check collitions when we move at a tile boundary
		if (!d_tx) {
			// Bit 7 = 1 ==> Tile is solid
			if (  maps_getTileInfo(tx + e->vx, ty) & 0x01 ||
			    (d_ty && maps_getTileInfo(tx + e->vx, ty + 1) & 0x01) ) 
				goto markRedrawTiles;
		}
		
		// Update X position before checking Y
		e->x += e->vx;
		d_tx = (e->x & 3);
		tx   = (e->x >> 2);
		e->moved = 1;
	}
	
	// Check for Y movement
	if (e->vy) {
		if (!d_ty) {    // Only check for collision at tile boundary
			// Bit 7 = 1 ==> Tile is solid (or some of the two)
			if (  maps_getTileInfo(tx, ty + e->vy) & 0x01 || 
				 (d_tx && maps_getTileInfo(tx + 1, ty + e->vy) & 0x01) ) {
				e->moved = 0;
				goto markRedrawTiles;
			}
		}
		
		// Update Y position 
		e->y += e->vy;
		e->moved = 1;
	}

markRedrawTiles: {
		unsigned char w = (orig_dtx) ? 2 : 1;
		unsigned char h = (d_ty) ? 2 : 1;
		maps_markTilesForRedraw(orig_tx, ty, w, h);
	}
	return e->moved;
}

void ent_draw(TEntity *e) {
	cpc_PutMaskSprite(e->sprite, cpc_GetScrAddress(e->x, e->y << 1));
}
