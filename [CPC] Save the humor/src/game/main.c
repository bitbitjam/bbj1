#include <cpcrslib.h>
#include <cpcwyzlib.h>
#include "sprites/sprites.h"
#include "sprites/tiles.h"
#include "music/music.h"
#include "maps/mapas.h"
#include "keyboardtable.h"
#include "maps/entities.h"
#include "maps/levels.h"

// Game Statuses
#define EST_EXIT		0
#define EST_MENU		1
#define EST_REDEFINE	2
#define EST_PLAY		3

// Entity sprite types
#define SP_CHARLIE		0
#define SP_SCIENTIST	1
#define SP_TIEMAN		2
#define SP_SOLDIER		3
#define SP_GLADIATOR	4
#define SP_ROMAN		5
#define SP_ALIEN		6

// Sprite USES
#define SPU_NORMAL		0
#define SPU_LAUGH1		1
#define SPU_LAUGH2		2

void pause(unsigned char p){
	unsigned char i;
	for (i=0; i < p; i++) {
		__asm
			halt
		__endasm;
	}
}

void scr_waitVSYNC() {
	__asm 
		;// Check if we are in VSYNC zone
		wait_vs:
			ld b, #0xF5
			in a,(c)
			rra
			jr nc, wait_vs ;// no, wait
	__endasm;
}

/// Assign the first standard keys
///
void assignStandardKeys(void) {
	unsigned char i = 0;
	extern int global_asignation_keys_array[];

	// Creating an array using ASM generates smaller code than using C
	__asm
		//ret						// Ensure we do not execute data as code
		jp end_data
		  _global_asignation_keys_array:
			.dw KEY_CURSOR_UP 		// 0: PLAYER 1 UP
			.dw KEY_CURSOR_DOWN 	// 1: PLAYER 1 DOWN
			.dw KEY_CURSOR_LEFT		// 2: PLAYER 1 LEFT
			.dw KEY_CURSOR_RIGHT	// 3: PLAYER 1 RIGHT
			.dw KEY_SPACE			// 4: PLAYER 1 FIRE
			.dw KEY_DEL				// 5: PAUSE GAME
			.dw KEY_ESC				// 6: EXIT GAME
			.dw KEY_1				// 7: MENU SELECT 1
			.dw KEY_2				// 8: MENU SELECT 2
			.dw KEY_0				// 9: MENU SELECT 0
			.dw KEY_NONE
	    end_data:
	__endasm;	
	
	/// GLOBAL KEY SIMBOLS
	///
	#define KEYID_P1_UP			0
	#define KEYID_P1_DOWN		1
	#define KEYID_P1_LEFT		2
	#define KEYID_P1_RIGHT		3
	#define KEYID_P1_FIRE		4
	#define KEYID_PAUSE_GAME	5
	#define KEYID_EXIT_GAME		6
	#define KEYID_MENU_1		7
	#define KEYID_MENU_2		8
	#define KEYID_MENU_0		9
	
	do { 
		cpc_AssignKey(i, global_asignation_keys_array[i]);
		++i;
	} while (global_asignation_keys_array[i] != KEY_NONE);
}

void set_colours(unsigned char inks[17]) {
    unsigned char x;
	cpc_SetBorder(inks[0]);
    for (x=0; x<17; x++) {
		cpc_SetInk(x, inks[x+1]);
    }
}

unsigned char* getSpriteTypeForEntity(unsigned char type, unsigned char use) {
	switch (use) {
		case SPU_NORMAL:
			switch (type) {
				case ENT_PLAYER: 
					return sm_charlie1;
				case ENT_SCIENTIST_STATIC:
				case ENT_SCIENTIST_LEFTRIGHT:
					return sm_cientificos;
				case ENT_TIEMAN_STATIC:
				case ENT_TIEMAN_LEFTRIGHT:
					return sm_encorbatado;
				case ENT_SOLDIER_STATIC:
				case ENT_SOLDIER_LEFTRIGHT:
					return sm_soldao;
				case ENT_GLADIATOR_STATIC:
				case ENT_GLADIATOR_LEFTRIGHT:
					return sm_gladiador;
				case ENT_ROMAN_STATIC:
				case ENT_ROMAN_LEFTRIGHT:
					return sm_romano;
				case ENT_ALIEN_STATIC:
				case ENT_ALIEN_LEFTRIGHT:
					return sm_alien;
			}
			break;

		case SPU_LAUGH1:
			switch (type) {
				case ENT_PLAYER: 
					return sm_charlie1;
				case ENT_SCIENTIST_STATIC:
				case ENT_SCIENTIST_LEFTRIGHT:
					return sm_cientificosrisa1;
				case ENT_TIEMAN_STATIC:
				case ENT_TIEMAN_LEFTRIGHT:
					return sm_encorbatadorisa1;
				case ENT_SOLDIER_STATIC:
				case ENT_SOLDIER_LEFTRIGHT:
					return sm_soldaorisa1;
				case ENT_GLADIATOR_STATIC:
				case ENT_GLADIATOR_LEFTRIGHT:
					return sm_gladiadorrisa1;
				case ENT_ROMAN_STATIC:
				case ENT_ROMAN_LEFTRIGHT:
					return sm_romanorisa1;
				case ENT_ALIEN_STATIC:
				case ENT_ALIEN_LEFTRIGHT:
					return sm_alienrisa1;
			}
			break;
		case SPU_LAUGH2:
			switch (type) {
				case ENT_PLAYER: 
					return sm_charlie1;
				case ENT_SCIENTIST_STATIC:
				case ENT_SCIENTIST_LEFTRIGHT:
					return sm_cientificosrisa2;
				case ENT_TIEMAN_STATIC:
				case ENT_TIEMAN_LEFTRIGHT:
					return sm_encorbatadorisa2;
				case ENT_SOLDIER_STATIC:
				case ENT_SOLDIER_LEFTRIGHT:
					return sm_soldaorisa2;
				case ENT_GLADIATOR_STATIC:
				case ENT_GLADIATOR_LEFTRIGHT:
					return sm_gladiadorrisa2;
				case ENT_ROMAN_STATIC:
				case ENT_ROMAN_LEFTRIGHT:
					return sm_romanorisa2;
				case ENT_ALIEN_STATIC:
				case ENT_ALIEN_LEFTRIGHT:
					return sm_alienrisa2;
			}
	}
	
	return sm_alien;
}

unsigned char estado_redefinir() {
	unsigned char t;
	unsigned char m[6][10] = { ";;SALTO;;", ";;ABAJO;;", "IZQUIERDA", ";DERECHA;", ";DISPARO;", ";;PAUSA;;" };

	// Colores multicolor para letras
	cpc_SetInkGphStr(1, pal_texto_multicolor[7]);
	cpc_SetInkGphStr(2, pal_texto_multicolor[8]);
	cpc_SetInkGphStr(3, pal_texto_multicolor[5]);
	
	// Bucle de redefinir teclas
	for(t=0; t < 6; t++) {
		cpc_PrintGphStrXY(m[t],22,155);
		cpc_RedefineKey(t);
	}
	cpc_PrintGphStrXY(";;;;;;;;;",22,155);
	
	return EST_MENU;
}

unsigned char estado_juego() {
	unsigned char level = 0, i, dead = 0;

	// TODO: Reescribir entero. Cita célebre de Esta Casa es Una Ruina
	//       "- En este escalón, aquí fue donde empezó todo...
	//        - A convertirse en MIERDA!"
	//
	cpc_SetInkGphStr(0, pal_texto_multicolor[4]);
	cpc_SetInkGphStr(1, pal_texto_multicolor[1]);
	cpc_SetInkGphStr(2, pal_texto_multicolor[0]);
	cpc_SetInkGphStr(3, pal_texto_multicolor[6]);	
	
	// Level loop
	do {
		// Level initialization
		TLevel* lvl = &(GAME_LEVELS[level]);
		TEntity* jugador, *chiste;
		unsigned char someOneMoved = 0, j = 0, killed = 0;

		// Screen and song
		cpc_ClrScr();
		music_reproducir_cancion(lvl->song);
		cpc_PutSprite(s_marcador_izq,  0xC640);
		cpc_PutSprite(s_marcador_dcha, 0xC668);
		
		// Inicializar y dibujar mapa de prueba
		maps_setTileMap(lvl->map);
		maps_setTileSet(lvl->tileset);
		maps_drawTileMapComplete( 0xC000 );
		cpc_PrintGphStr(lvl->title, (int*)(0xC6EA));

				
		// Create level entities		
		for (i=0; i < lvl->numEntities; i++) {
			TEntity* e = &GAME_ENTITIES[i];
			e->type = lvl->initEnt[i].type;
			e->sprite = getSpriteTypeForEntity(e->type, SPU_NORMAL);
			e->x = (lvl->initEnt[i].tx << 2);
			e->y = (lvl->initEnt[i].ty << 2);
			e->vx = e->vy = e->jump = e->moved = e->stateAI = 0;
			e->heading=-1;
			j = (++j) % MAX_AI_PROCESS;
			e->delayAI = j;
		}
		jugador = &GAME_ENTITIES[0];
		chiste = &GAME_ENTITIES[lvl->numEntities];
		chiste->sprite  = sm_chistaco;
		chiste->stateAI = JOK_NULL;

		// Play Level Loop
		do {
			// Escaneo de teclado y comprobaciones
			//pause(3);
		gameloop:
			scr_waitVSYNC();
			cpc_ScanKeyboard();
		
			// Jump
			if (cpc_TestKeyF(KEYID_EXIT_GAME)) 		goto escape;
			if (cpc_TestKeyF(KEYID_PAUSE_GAME)) {
				while (cpc_AnyKeyPressed());
				while (!cpc_AnyKeyPressed());
				goto gameloop;
			}
			if (cpc_TestKeyF(KEYID_P1_UP))	 		jugador->vy = -1;
			if (cpc_TestKeyF(KEYID_P1_LEFT)) 		jugador->vx = -1;
			else if (cpc_TestKeyF(KEYID_P1_RIGHT)) 	jugador->vx = +1;
			if (cpc_TestKeyF(KEYID_P1_FIRE) && chiste->stateAI == JOK_NULL) { 
				// Shot a Joke
				chiste->x = jugador->x + 4*jugador->heading;
				chiste->y = jugador->y + 2;
				chiste->heading = jugador->heading;
				chiste->vx = jugador->heading;
				chiste->vy = -1;
				chiste->stateAI = JOK_LAUNCH;
				chiste->delayAI = JOK_LAUNCHCYCLES;
			}
			
			// Move the joke
			if (chiste->stateAI != JOK_NULL) {
				if (chiste->stateAI == JOK_LAUNCH && !chiste->delayAI--) {
					chiste->stateAI = JOK_DOWN;
					chiste->vy = 1;
				}
				if (!ent_moveJoke(chiste)) {
					// Joke perished
					chiste->stateAI = JOK_NULL;
				} 
			}
			
			// Mover entidades
			someOneMoved = 0;
			ent_moveEntity(jugador);
			if (jugador->moved) {
				someOneMoved++;
			}
			for (i=1; i < lvl->numEntities; i++) {
				TEntity* e = &GAME_ENTITIES[i];
				if (e->stateAI == ST_LAUGHING) {
					if ( !(e->delayAI-- & 3) ) {
						e->sprite  = getSpriteTypeForEntity(e->type, 
														(e->delayAI & 4) ? SPU_LAUGH1 : SPU_LAUGH2);
						e->vx = (e->delayAI & 4) ? -1 : 1;
						ent_moveEntity(e);
						someOneMoved++;
					} else if (e->delayAI < 1) {
						e->stateAI = ST_DEAD; 
						killed++;
						maps_markTilesForRedraw(e->x >> 2, e->y >> 2, 
												(e->x & 3) ? 2 : 1, 
												(e->y & 3) ? 3 : 2);
					}
				} else if (e->stateAI != ST_DEAD && e->delayAI--) {
					e->delayAI = MAX_AI_PROCESS;
					ent_processAI(e);
					ent_moveEntity(e);
					if (e->moved) {
						someOneMoved++;
					}
				}
			}

			// Colision detection
			for (i=1; i < lvl->numEntities; i++) {
				TEntity* e = &GAME_ENTITIES[i];
				if (e->stateAI != ST_DEAD) {
					if (chiste->stateAI != JOK_NULL && 
						ent_checkCollisionWithJoke(chiste, e)) {
						e->stateAI = ST_LAUGHING;
						e->delayAI = ST_LAUGHDELAY;
						e->sprite  = getSpriteTypeForEntity(e->type, SPU_LAUGH1);
					} else if (ent_checkCollision(jugador, e, 3, 7)) {
						e->moved = 1;
						jugador->moved = 1;
						dead = 1;
						someOneMoved+=2;
						// goto exit
					}
				}
			}
	
			// Redraw
			if (someOneMoved) {
				maps_redrawMarkedTiles();
				for (i=0; i < lvl->numEntities; i++) {
					TEntity* e = &GAME_ENTITIES[i];
					if (e->stateAI != ST_DEAD) {
						ent_draw(e);
						e->moved = e->vx = e->vy = 0;
					}
				}
				/*
				for (i=0; someOneMoved && i < lvl->numEntities; i++) {
					TEntity* e = &GAME_ENTITIES[i];
					if (e->moved) {
						ent_draw(e);
						e->moved = e->vx = e->vy = 0;
						someOneMoved--;
					}
				}*/
			}
			// Redraw the joke
			if (chiste->stateAI != JOK_NULL) {
				ent_draw(chiste);
			}
		} while (killed < lvl->numEntities-1 && !dead);
		
		// If player is heading left, flip again (always starts heading left)
		if (jugador->heading > 0)
			spr_flipHorizontalMask(jugador->sprite);
		
		// Check if we are dead
		//if (dead) { // TODO: Muerte }

	} while (!dead && ++level < NUM_GAME_LEVELS);
escape:

	return EST_MENU;
}


unsigned char estado_menu() {
	unsigned char st=EST_MENU, m=0;
	cpc_ClrScr();
	
	music_reproducir_cancion(m);
	
	// Colores multicolor para letras
	cpc_SetInkGphStr(0, 0);
	cpc_SetInkGphStr(1, pal_texto_multicolor[10]);
	cpc_SetInkGphStr(2, pal_texto_multicolor[4]);
	cpc_SetInkGphStr(3, pal_texto_multicolor[15]);
	
	// Pintar el menú
	cpc_PutSprite(s_bannermenu, 0xC14C);

	cpc_PrintGphStrXY("1;;PLAY;GAME",20,80); 
	cpc_PrintGphStrXY("2;;DEFINE;KEYS",20,100); 
	cpc_PrintGphStrXY("0;;EXIT;GAME",20,130); 
	
	cpc_SetInkGphStr(3, pal_texto_multicolor[1]);
	
	cpc_PrintGphStrXY("FREMOS;SOLDIERS;2014",15,190);
	do {
		pause(8);
		cpc_ScanKeyboard();
		if 		(cpc_TestKeyF(KEYID_MENU_1)) st=EST_PLAY;
		else if (cpc_TestKeyF(KEYID_MENU_2)) st=EST_REDEFINE;
		else if (cpc_TestKeyF(KEYID_MENU_0)) st=EST_EXIT;
	} while (st == EST_MENU);
	
	return st;
}

  
int main() {  
	// Crear punteros a las funciones de los distintos estados, empezando en estado 1
	typedef unsigned char(*TPEstado)(void);
	TPEstado estados[3] = { estado_menu, estado_redefinir, estado_juego };
	unsigned char st=EST_MENU;
	
	// INICIALIZAR
	set_colours(pal_paletaPrincipal);
	cpc_SetModo(0);
	cpc_DisableFirmware();
	assignStandardKeys();

	// Controlar estados del juego
	do {
		st = estados[st-1]();
	} while (st != EST_EXIT);

	// Terminar y restaurar
	music_pausar();
	cpc_EnableFirmware();

	return 0;
}
