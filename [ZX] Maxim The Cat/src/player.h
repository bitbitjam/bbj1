/*
 * FASE player
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
 *   player code
 *
**/


unsigned char player_life;

unsigned char _pl_estado_parp = 0;
unsigned char _pl_estado_counter = 0;


// na_th_an - churrera
void step (void) {
	#asm
		ld a, 16
		out (254), a
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		xor 16
		out (254), a
	#endasm	
}

void update_life()
{
    unsigned int scr, dst;
    char count;
    scr= 0x3d80 + player_life * 8;
    dst= 0x50de | *shadow << 8;
    for ( count= 0; count < 8; count++ )
    {
        zxmem[dst] = zxmem[scr++] ^ 0xff;
        dst+= 0x100;
    }
}

/*
  Player damaged, check life > 0
*/
void player_hit(void)
{
    player_life--;
    player.estado = PL_EST_TOCADO;
    _pl_estado_counter = 16;
    *drwout = (unsigned int) update_life;
}


void player_handler(void)
{

    // movimiento horizontal
    vx+= ax;
    x+= vx;

    if( vx + 8 >> 3 )
        ax= -vx >> 3;
    else
        ax = vx = 0;

    if( (unsigned int)x > scrw << 12 )
    {
        if( vx > 0 )
        {
            // comprobar bordes para pasar pantalla
            if( mapx < (mapw - 1) )
            {
                x = 0;
                mapx ++;
                update_screen();
            }
            else
            {
                x= scrw << 12;
                vx= 0;
            }
            
        }
        // comprobar bordes para pasar pantalla
        else if( mapx )
        {
            x= scrw << 12;
            mapx--;
            update_screen();
        }
        else
            vx = x = 0;
    }
    sprites[PLAYER_SPRITE].x = x >> 8;

    // movimiento vertical
    vy+= ay;
    y+= vy;

    if( vy + 8 >> 3 )
        ay= -vy >> 3;
    else
        ay = vy = 0;

    if( (unsigned int)y > scrh << 12 )
    {
        if( vy >= 0 )
        {
            // comprobar bordes para pasar pantalla
            if( mapy < (maph - 1) )
            {
                y = 0;
                mapy ++;
                update_screen();
            }
            else
            {
                y= scrh << 12;
                vy= 0;
            }
            
        }
        // comprobar bordes para pasar pantalla
        else if( mapy )
        {
            y= scrh << 12;
            mapy--;
            update_screen();
        }
        else
            vy = y = 0;
    }
    sprites[PLAYER_SPRITE].y = y >> 8;

    // mapa
    tmpx = sprites[PLAYER_SPRITE].x >> 3;
    tmpy = sprites[PLAYER_SPRITE].y >> 3;

    //print_value(3,10, (int) tmpx >> 1);

    // teclado jugador
    if( inKey(KeybYUIOP) & 0x01 ) // P
    {
        if( (((tmpx >> 1) + 1) != 15) && (check_tile((tmpx >> 1) + 1, tmpy >> 1) & T_OBSTACLE) )
            ax = vx= 0;
        else
            ax = (vx < maxvx) ? 40 : 0;

        player.facing = PL_FACE_LEFT; // prepare anim

    }
    else if( inKey(KeybYUIOP) & 0x02 ) // O
    {
        if( (!(tmpx & 1)) && (check_tile((tmpx >> 1) - 1, tmpy >> 1) & T_OBSTACLE) )
            ax = vx= 0;
        else
            ax = (vx > -maxvx) ? -40 : 0;

        player.facing = PL_FACE_RIGHT;
    }


    if( inKey(KeybGFDSA) & 0x01 ){ // A
        if((!(tmpy & 1)) && (check_tile(tmpx >> 1, (tmpy >> 1) + 1) & T_OBSTACLE) )
            ay = vy= 0;
        else
            ay = (vy < maxvy) ? 40 : 0;

        player.facing = PL_FACE_DOWN;
    }
    else if( inKey(KeybTREWQ) & 0x01 ) // Q
    {
        if( (check_tile(tmpx >> 1, (tmpy >> 1) - 1) & T_OBSTACLE) )
            ay = vy= 0;
        else
            ay = (vy > -maxvy) ? -40 : 0;

        player.facing = PL_FACE_UP;
    }
    
    // animacion
    if(sprites[PLAYER_SPRITE].f >= 4)
    {
        _pl_estado_parp ^= 1;
        if(_pl_estado_parp && (player.estado & PL_EST_TOCADO)) {
            sprites[PLAYER_SPRITE].f = 0;
            sprites[PLAYER_SPRITE].n = PLAYER_PARP; // blank frame

            if(!--_pl_estado_counter)
            {
                _pl_estado_counter = 0;
                player.estado &= ~PL_EST_TOCADO;
            }
        }
        // anima si hay velocidad
        else if( vx | vy )
        {
                // step snd on 48K machines
            if (*type_machine == MACHINE_48K)
                step();

            player.fanim ^= 1;
            sprites[PLAYER_SPRITE].f = 0;
            sprites[PLAYER_SPRITE].n = player.facing + player.fanim;
        }
        else
        {
            if(sprites[PLAYER_SPRITE].n != PL_FACE_IDLE)
            {
                sprites[PLAYER_SPRITE].f++;
                if(sprites[PLAYER_SPRITE].f & 128){
                    sprites[PLAYER_SPRITE].n = PL_FACE_IDLE;
                    sprites[PLAYER_SPRITE].f = 0;
                    
                    // win game
                    if(getroom() == 4)
                    {
                        playing = 0;
                        player_wins = 1;
                    }                        
                }
                else
                    sprites[PLAYER_SPRITE].n = player.facing;
            }
        }
    }
    else
        sprites[PLAYER_SPRITE].f++;

    // disparo con espacio
    if( inKey(KeybBNMs_) & 0x01 && !spacepressed && num_bullets<4 ){ 
        bullets[num_bullets].x = sprites[PLAYER_SPRITE].x;
        bullets[num_bullets].y = sprites[PLAYER_SPRITE].y;
        
        i = inKey(KeybTREWQ) << 3 & 8 | inKey(KeybGFDSA) << 2 & 4 | inKey(KeybYUIOP) & 3;
        
        // optimize!!
        if(!i)
            switch(player.facing)
            {
                case PL_FACE_LEFT:
                    i = 1; break;
                case PL_FACE_RIGHT:
                    i = 2; break;
                case PL_FACE_DOWN:
                    i = 4; break;
                case PL_FACE_UP:
                    i = 8; break;
            }
        dirbul[num_bullets]= i;
        num_bullets++;
    }
    spacepressed = inKey(KeybBNMs_) & 0x01;

    // usar teleport
    if((inKey(KeybBNMs_) & 0x04) && (check_tile(tmpx >> 1, tmpy >> 1) & T_SPECIALE))
    {
        switch (getroom())
        {
            case 3:
                setroom(23); break;
            case 23:
                setroom(3); break;
            
            case 18:
                setroom(8); break;
            case 8:
                setroom(18); break;
        
            case 13:
                setroom(9); break;
            case 9:
                setroom(13); break;
                
        }
    }        
}


void player_init()
{
    player_life = 5;
    update_life();

    player.facing = PL_FACE_LEFT;
    player.fanim  = 0;
    player.estado = 0;
    _pl_estado_parp = 0;
    _pl_estado_counter = 0;
    player.keys = 0;     
}

