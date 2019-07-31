#include "main.h"


///////////////////////////////////////////////////////////////////////////////////////
//
//  void flagsControl(){
//  control de las banderas
//
///////////////////////////////////////////////////////////////////////////////////////
void flagsControl( u8 *time2flag, u8 ticks, u8 num_players ){

    u8 numFlag = 0;
    u8 numPlayer;

    /////////////////////////////////////////////////////////////
    // calculamos el nuevo intervalo para generar una bandera
    if( *time2flag == 255 ){
        *time2flag = random()%30;

        if( *time2flag < 10 )
            *time2flag = 2;
        else if( *time2flag >= 10 && *time2flag < 20 )
            *time2flag = 3;
        else
            *time2flag = 4;
    }


    if( ticks == 60 )
        *time2flag -= 1;

    /////////////////////////////////////////////////////////////
    // ha pasado el intervalo y generamos una bandera
    if( *time2flag == 0 ){

        numFlag = random()%4;

        if( flags[numFlag].state == 0 ){
            flags[numFlag].step = 0;
            flags[numFlag].state = 1;
            flags[numFlag].sprite.posx = flags[numFlag].x = 24+random()%272;
            flags[numFlag].sprite.posy = flags[numFlag].y = 24+random()%172;
            VDP_setSpriteP(flags[numFlag].sprite_num, &flags[numFlag].sprite);
        }
        else{
            // si una bandera no se ha cogido y el random cae sobre ella varias veces,
            // la desactivo por si acaso no se puede coger
            flags[numFlag].step++;
            if( flags[numFlag].step == 2 ){
                flags[numFlag].state = 0;
                flags[numFlag].sprite.posx = flags[numFlag].x = screen_width;
                VDP_setSpriteP(flags[numFlag].sprite_num, &flags[numFlag].sprite);
            }
        }
        *time2flag = 255;
    }


    //////////////////////////////////////////////////
    // compruebo las colisiones
    for( numFlag = 0; numFlag < max_num_flags; numFlag++){

        for( numPlayer = 0; numPlayer < num_players; numPlayer++){

            if( player[numPlayer].hp && flags[numFlag].state ){
                if( (flags[numFlag].x+char_collision_right >= fix32ToInt(player[numPlayer].x)+char_collision_left) && (flags[numFlag].x+char_collision_left <= fix32ToInt(player[numPlayer].x)+char_collision_right)){
                    if( (flags[numFlag].y+char_collision_down >= fix32ToInt(player[numPlayer].y)+char_collision_up) && (flags[numFlag].y+char_collision_up <= fix32ToInt(player[numPlayer].y)+char_collision_down)){

                        flags[numFlag].state = 0;
                        flags[numFlag].sprite.posx = flags[numFlag].x = screen_width;
                        VDP_setSpriteP(flags[numFlag].sprite_num, &flags[numFlag].sprite);

                        // bandera capturada es del mismo color
                        if( player[numPlayer].team == numFlag )
                            updatePlayerScore( numPlayer, 2 );
                        // de otro
                        else
                            updatePlayerScore( numPlayer, 3 );
                    }
                }
            }
        }
    }



/*
VDP_drawNumberBG( APLAN, *time2flag, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 2, 2);
VDP_drawNumberBG( APLAN, flags[0].state, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 2, 3);
VDP_drawNumberBG( APLAN, flags[1].state, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 2, 4);
VDP_drawNumberBG( APLAN, flags[2].state, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 2, 5);
VDP_drawNumberBG( APLAN, flags[3].state, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 2, 6);*/
}

