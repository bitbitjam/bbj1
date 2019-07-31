#ifndef _MAPAS_H_
#define _MAPAS_H_

extern unsigned char map_mapa_fase0[20][20];
extern unsigned char map_mapa_fase1[20][20];
extern unsigned char map_mapa_fase2[20][20];
//extern unsigned char map_mapa_fase3[20][20];
//extern unsigned char map_mapa_fase4[20][20];
//extern unsigned char map_mapa_fase5[20][20];

void maps_setTileMap(unsigned char *tilemap); //[20][20]);
void maps_setTileSet(unsigned char *tileset); //[][4*8]);
void maps_drawTileMapComplete(int mem_dir);
void maps_redrawTileRectangle(int mem_dir, unsigned char x, unsigned char y,
							  unsigned char width, unsigned char height);
char maps_checkSolidColision8x16(unsigned char x, unsigned char y, 
								unsigned char w, unsigned char h);
void maps_markTilesForRedraw(unsigned char x, unsigned char y,
							 unsigned char width, unsigned char height);
char maps_getTileInfo(unsigned char tx, unsigned char ty);
void maps_redrawMarkedTiles();

#endif