#include <cpcrslib.h>
#include "mapas.h"

// Size of a tile in bytes
#define	TILESIZE			(4*8+1)
#define MAX_MARKABLETILES	60


unsigned char* g_tilemap; 		 // Points to a 20x20 char array
unsigned char* g_tileset; 		 // Points to a undefinitely long list of tiles, each one of 4*8 chars
unsigned char  g_markedTiles[MAX_MARKABLETILES*2];// Tiles marked for redrawing
unsigned char  g_nMarkedTiles = 0;				  // Number of tiles marked (*2 = x,y)

void maps_setTileMap(unsigned char *tilemap){
	g_tilemap = tilemap; 
}

void maps_setTileSet(unsigned char *tileset) {
	g_tileset = tileset;
}

void maps_drawTileMapComplete(int mem_dir) {
	unsigned char i, j, t;
	for(i=0; i < 20; i++) {
		for(j=0; j < 20; j++) {
			t = g_tilemap[20*i + j];
			cpc_PutSp((g_tileset + TILESIZE*t+1), 8, 4, (int)mem_dir);
			mem_dir += 4;
		}
	}
}

void maps_redrawTileRectangle(int mem_dir, unsigned char x, unsigned char y,
							  unsigned char width, unsigned char height) {
	unsigned char i, j, t;
	for(j=y; j < y+height; j++) {
		for(i=x; i < x+width; i++) {
			t = g_tilemap[20*j + i];
			cpc_PutSp((g_tileset + TILESIZE*t+1), 8, 4, (int)mem_dir);
			mem_dir += 4;
		}
		mem_dir += 80 - 4*width;
	}
}

void maps_redrawMarkedTiles() {
	unsigned char x, y, t, *tile;
	unsigned int mempos;
	while (g_nMarkedTiles) {
		y = g_markedTiles[--g_nMarkedTiles];
		x = g_markedTiles[--g_nMarkedTiles];
		t = g_tilemap[20*y + x];
		//mempos = (int)(0xC000 + 0x50*y + (x << 2));
		tile = (g_tileset + TILESIZE*t+1);
		mempos = (int)(0xC000 + 0x50*y + (x << 2));
		cpc_PutSp(tile, 8, 4, mempos);
	}
}

void maps_markTilesForRedraw(unsigned char x, unsigned char y,
							 unsigned char width, unsigned char height) {
	unsigned char i, j;
	for(j=y; j < y+height; j++) {
		for(i=x; i < x+width; i++) {
			g_markedTiles[g_nMarkedTiles++] = i;
			g_markedTiles[g_nMarkedTiles++] = j;
		}
	}
}

char maps_getTileInfo(unsigned char tx, unsigned char ty) {
	unsigned char tile_id = g_tilemap[20*ty + tx];
	return g_tileset[TILESIZE*tile_id];
}

char maps_checkSolidColision8x16(unsigned char x, unsigned char y, 
								 unsigned char w, unsigned char h) {
/*
	// Calculate initial tile
	unsigned char tx = x >> 2;
	unsigned char ty = y >> 2;
	unsigned int ts;

	// Check only inferior tiles
	ty += h - 1;
	ts = *((unsigned int*)(g_tilemap + 20*ty + tx)); // Get 2 consecutive bytes (Beware! Little Endian!)
	// TileInfo: Bit 7 => Solid or not
	if ( ( 0x01 & g_tileset[TILESIZE*(ts & 0x00FF)]           ) ||	// First tile is solid OR
		 ( (w >> 1) && (0x01 & g_tileset[TILESIZE*(ts >> 8)]) ) ) {   // 2 tiles width and second tile is solid
		return 1;
	}
*/
	return 0;
}