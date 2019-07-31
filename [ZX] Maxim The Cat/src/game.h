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
 *
 * game defines are mainly an adaptation of na_th_an code
 * 
**/

unsigned char map_attr [150];

typedef struct {
  unsigned char facing;
  unsigned char fanim;
  
  unsigned char estado;

  unsigned char keys;
}PLAYER;

PLAYER player;

unsigned char playing, player_wins;


#define PL_FACE_LEFT    0
#define PL_FACE_RIGHT   2
#define PL_FACE_UP      4
#define PL_FACE_DOWN    6

#define PL_FACE_IDLE    14

#define PL_EST_NORMAL    0
#define PL_EST_SALTANDO  1

#define PL_EST_TOCADO    2
#define PL_EST_TPARPADEA 3



