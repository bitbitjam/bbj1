#include "levels.h"
#include "../sprites/tiles.h"
#include "../maps/mapas.h"

void initgamelevels() {
__asm

.globl _GAME_LEVELS
_GAME_LEVELS::
	;// LEVEL 0
	.dw _map_mapa_fase0, _ts_tilesPrincipales
	.db 1	;// Song
	.ascii "FASE;1;;LA;MAQUINA;DEL;TIEMPO"	;// 29 characters, 11 left to 40 bytes
	.db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0		;// \0 + 10 bytes
	.db 4	;// Num entities
	.db ENT_PLAYER,    10, 15	;// Entities (type, tx, ty)
	.db ENT_SCIENTIST_LEFTRIGHT, 5, 3
	.db ENT_SCIENTIST_LEFTRIGHT,14, 3
	.db ENT_TIEMAN_LEFTRIGHT,10,5
	.db 0, 0, 0
	.db 0, 0, 0
	.db 0, 0, 0
	;// LEVEL 1
	.dw _map_mapa_fase1, _ts_tilesPrincipales
	.db 2	;// Song
	.ascii "FASE;2;;SENADORES;ROMANOS"				;// 25 characters, 15 left to 40 bytes
	.db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0	;// \0 + 14 bytes	
	.db 5	;// Num entities
	.db ENT_PLAYER,    14, 5	;// Entities (type, tx, ty)
	.db ENT_SOLDIER_LEFTRIGHT, 14,13
	.db ENT_SOLDIER_LEFTRIGHT, 17,13
	.db ENT_ROMAN_LEFTRIGHT,4,12
	.db ENT_ROMAN_LEFTRIGHT,6,6
	.db 0, 0, 0
	.db 0, 0, 0
	;// LEVEL 2
	.dw _map_mapa_fase2, _ts_tilesPrincipales
	.db 1	;// Song
	.ascii "FASE;3;;BAÑOS;ROMANOS"								;// 21 characters, 19 left to 40 bytes
	.db 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0	;// \0 + 18 bytes	
	.db 4					;// Num entities
	.db ENT_PLAYER,	     9, 4	;// Entities (type, tx, ty)
	.db ENT_ROMAN_LEFTRIGHT, 1,1
	.db ENT_ROMAN_LEFTRIGHT, 19,1
	.db ENT_ALIEN_LEFTRIGHT, 9,14
	.db 0,15, 3
	.db 0, 0, 0
	.db 0, 0, 0
__endasm;

}
