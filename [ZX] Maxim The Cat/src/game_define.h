/*
 * FASE - Fucking Awesome Spectrum Engine
 *
 * Copyright (c) 2014 Antonio Villena - http://antoniovillena.es/
 * Copyright (c) 2014 David Colmenero Aka D_Skywalk - http://david.dantoine.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * game defines are mainly an adaptation of na_th_an code
 *
**/

// base game defines
#define gconst  20
#define maxvx   600
#define maxvy   600

// game defines
#define ENEMY_DEAD 0x80
#define PLAYER_PARP 0x80


// sprites
#define PLAYER_SPRITE 0
#define ENEMY_SPRITE_FRST 1
#define ENEMY_SPRITE_LAST 5



// mapa de durezas y atributos
#define T_WALKABLE 0
#define T_SPECIALE 2
#define T_OBSTACLE 8




unsigned char comportamiento_tiles [] = {
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	8, 8, 2, 8, 8,10, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	//1, 8, 8, 8, 8, 8, 8, 1, 1, 8, 8, 8, 1, 4,10,10,
	//0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
