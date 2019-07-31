#include "main.h"

///////////////////////////////////////////////////////////////////////////////////////
//
//  u8 timeControl( u8 *ticks, u8 *mins, u8 *secs )
//  control del tiempo y la salida si llega a cero
//
///////////////////////////////////////////////////////////////////////////////////////
u8 timeControl( u8 *ticks, u8 *mins, u8 *secs ){

    if( *ticks == 60 ){

        *ticks = 0;

        if( *secs == 0 ){

            *secs = 59;
            *mins -= 1;

            if( *mins == 9 )
                VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 17, 0);

            VDP_drawNumberBG( APLAN, *mins, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 18, 0);
        }
        else{
            *secs -= 1;
            enemiesGenerator(*secs);
        }

        if( *secs > 9 )
            VDP_drawNumberBG( APLAN, *secs, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 20, 0);
        else
            VDP_drawNumberBG( APLAN, *secs, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 21, 0);

        ///////////////////////////////////////////////////////////////////////////////////////
        // salimos por tiempo y vamos a la pantalla de puntuacion
        if( *mins == 0 && *secs == 0 ){

            psgFxPlay(START_SFX);
            VDP_loadTileData( tiles_TIMEUP1,  player[3].tile_pos+size_tiles_char*5+16, tiles_billboard_size, 0);
            VDP_loadTileData( tiles_TIMEUP2,  player[3].tile_pos+size_tiles_char*5+32, tiles_billboard_size, 0);
            sprite_menu[0].posx = 128;
            sprite_menu[1].posx = 160;
            VDP_setSpriteP(billboard1_sprite, &sprite_menu[0]);
            VDP_setSpriteP(billboard2_sprite, &sprite_menu[1]);
            VDP_updateSprites();
            waitTick(TICKPERSECOND * 2);

            VDP_fadeOutAll (60, 0);
            waitTick(TICKPERSECOND * 1);

            return 1;
        }

    }
    else
        *ticks += 1;

    return 0;
}

