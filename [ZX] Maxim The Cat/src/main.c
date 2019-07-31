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
**/

#include  <stdlib.h>
#include  "fase.h"
#include  "game.h"
#include  "game_define.h"
#include  "utils.h"

#include "player.h"

extern unsigned char *ending;
extern unsigned char *menu;
/* const */ unsigned char data[20]= {
  0x00, 0x42, 0xff0, 0,
  0x08, 0x60, 0x60, 2,
  0x09, 0x58, 0x48, 3,
  0x0a, 0x22, 0x02, 1,
  0x0b, 0x50, 0x6e, 2};


void init_engine( void )
{
    spacepressed= num_bullets= *shadow= 0;
    x= 0x3000;
    y= 0x6000;

    player_init();

    // inicializar engine
    fase_init();

    mapx=0;
    mapy=2;
    prepare_screen();
}


void fill_data(void)
{
    // pasar datos a sprites y balas
    for ( i = PLAYER_SPRITE; i < ENEMY_SPRITE_LAST; i++ )
    {
        sprites[i].n= data[0 | i<<2];
        sprites[i].x= data[1 | i<<2];
        sprites[i].y= data[2 | i<<2];
        sprites[i].f= data[3 | i<<2];
    }

    for ( i = 0; i < 4; i++ )
        bullets[i].y= 255;
}


void end_game ( void )
{
    fase_stop();

    Dzx7b((unsigned int) (&ending-1), 0x5aff);
    Pause(700);
}

void game_over ( void )
{
    // border
    M_OUTP(0xfe, 2);

    print_str(10,4, TRUE, " GAME OVER ");

    i= 0xff;
    do{
        fase_dwframe();
    }while(--i);

    fase_stop();
}


void actors_handler ( void )
{
    // movimiento de los enemigos
    for ( i = ENEMY_SPRITE_FRST; i < ENEMY_SPRITE_LAST; i++ )
    {
        if( sprites[i].n < ENEMY_DEAD )
      	{
            if((player_life) && (player.estado != PL_EST_TOCADO) &&
                (abs(sprites[PLAYER_SPRITE].x-sprites[i].x) + abs(sprites[PLAYER_SPRITE].y-sprites[i].y) < 16 ) )
            {
                player_hit();
            }

      	    // deteccion de disparos
            for ( j= 0; j < num_bullets; j++ )
	        {
                if( abs(bullets[j].x-sprites[i].x) + abs(bullets[j].y-sprites[i].y) < 10 )
                {
                    sprites[i].n += ENEMY_DEAD;
                    remove_bullet( j );
                    drawtile(sprites[i].x >> 4, sprites[i].y >> 4, 68);
                }
            }
        
            if( sprites[i].f & 1 )
            {
                if( sprites[i].y > 0 )
                    sprites[i].y--;
                else
                    sprites[i].f ^= 1;
            }
            else
            {
                if( sprites[i].y < (scrh << 4) )
                    sprites[i].y++;
                else
                    sprites[i].f ^= 1;

                if( sprites[i].f & 2 )
                {
                    if( sprites[i].x > 0 )
                        sprites[i].x--;
                    else
                        sprites[i].f ^= 2;
                }
                else
                {
                    if( sprites[i].x< (scrw << 4) )
                        sprites[i].x++;
                    else
                        sprites[i].f ^= 2;
                }
            }
        }
    }
    
    // movimiento de las balas
    for ( i = 0; i < num_bullets; i++ )
    {
        if( dirbul[i] & 3 )
        {
            if( dirbul[i] & 1 )
            {
                if( bullets[i].x < (scrw << 4) )
                    bullets[i].x += 4;
                else
                    remove_bullet( i );
            }
            else
            {
                if( bullets[i].x > 4 )
                    bullets[i].x -= 4;
                else
                    remove_bullet( i );
            }
        }
        if( dirbul[i]&12 )
        {
            if( dirbul[i]&4 )
            {
                if( bullets[i].y < (scrh << 4) )
                    bullets[i].y += 4;
                else
                    remove_bullet( i );
            }
            else
            {
                if( bullets[i].y > 4 )
                    bullets[i].y -= 4;
                else
                    remove_bullet( i );
            }
        }
    }
}


void run_game ( void )
{

    playing = 1;
    player_wins = 0;

    while (playing)
    {
        // esto hace que el engine procese un frame generando el escenario
        fase_dwframe();
        
        actors_handler();
        player_handler();

        if ( player_life == 0 )
        {
            playing = 0;
            player_wins = 0;
        }
    }
    
    if( player_wins )
        end_game();
    else
        game_over();
    
}

void main ( void )
{
    while(1)
    {
        // border
        M_OUTP(0xfe, 0);

        Dzx7b((unsigned int) (&menu-1), 0x5aff);
        //while(!inKey(KeybBNMs_)); // not work, need the engine running...
        Pause(300);

        init_engine();
        fill_data();

        run_game();
    }
}


// screens
#asm
        BINARY  "menu.rcs.zx7b"
._menu

        BINARY  "ending.rcs.zx7b"
._ending
#endasm

