#include "main.h"

//////////////////////////////////////////////////////////////////////////////////////
//
//  void updatePlayerScore( u8 num_player, u8 flag )
//  actualiza la puntuacion del jugador
//
//////////////////////////////////////////////////////////////////////////////////////
void updatePlayerScore( u8 num_player, u8 flag ){

    u8 posX = 0;

    // muerte normal
    if( flag == 0 )
        player[num_player].score++;
    // muerte de un miembro de tu equipo
    else if( flag == 1 ){

        if( player[num_player].score > 0 )
            player[num_player].score--;
    }
    // modo bandera (propia)
    else if( flag == 2 )
            player[num_player].score += 20;

    // modo bandera (ajena)
    else if( flag == 3 )
            player[num_player].score += 10;


    if( num_player == 0 )
        posX = 8;
    else if( num_player == 1 )
        posX = 18;
    else if( num_player == 2 )
        posX = 28;
    else if( num_player == 3 )
        posX = 38;

    if( player[num_player].score >= 10 && player[num_player].score < 100 )
        posX--;
    else if( player[num_player].score >= 100 && player[num_player].score < 1000 )
        posX -= 2;
    else if( player[num_player].score >= 1000 && player[num_player].score < 10000 )
        posX -= 3;
    else if( player[num_player].score > 10000 )
        posX -= 4;

    VDP_drawNumberBG( APLAN, player[num_player].score, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), posX, 27);
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  u8 move_player( u8 player, u8 direction ){
//  muevo al jugador y al que este empujando
//
//////////////////////////////////////////////////////////////////////////////////////
void movePlayer( u8 ticks, u8 num_player, u8 direction ){

    // compruebo si estoy chocando con otro jugador o el escenario con tiles obstaculo
    u8 player_collided = playerCollisionDetection(num_player, direction);

    ////////////////////////////////////////
    // derecha
    if( direction == state_walk_right ){

        // sino la hay, muevo al jugador
        if(!player_collided && player[num_player].collision[0] <= water_tile && player[num_player].collision[1] <= water_tile && player[num_player].collision[2] <= water_tile){

            // si podemos nadar y estamos en algo de agua
            if(player[num_player].swim && (player[num_player].collision[0] == water_tile || player[num_player].collision[1] == water_tile || player[num_player].collision[2] == water_tile)){

                // movemos el sprite mas lento si ya estamos DENTRO del agua
                if( player[num_player].collision[3] == water_tile ){
                    player[num_player].x = fix32Add(player[num_player].x, FIX32(player_slow_speed));
                    player[num_player].x_map = fix32Add(player[num_player].x_map, FIX32(player_slow_speed));
                }
                else{
                    player[num_player].x = fix32Add(player[num_player].x, FIX32(player_speed));
                    player[num_player].x_map = fix32Add(player[num_player].x_map, FIX32(player_speed));
                }

                player[num_player].sprite.posx = fix32ToInt(player[num_player].x);
                player[num_player].sprite_head.posx = fix32ToInt(player[num_player].x)+2;
                player[num_player].sprite_weapon.posx = fix32ToInt(player[num_player].x)+pos_x_weapon;

                // cambiamos de frame
                if( player[num_player].collision[3] == water_tile )
                    updatePlayerGfxRight( num_player, 1 );
                else
                    updatePlayerGfxRight( num_player, 0 );
            }
            else{
                // si no podemos nadar hay que comprobar que no haya nada de agua para movernos
                if(player[num_player].collision[0] != water_tile && player[num_player].collision[1] != water_tile && player[num_player].collision[2] != water_tile){
                    player[num_player].x = fix32Add(player[num_player].x, FIX32(player_speed));
                    player[num_player].x_map = fix32Add(player[num_player].x_map, FIX32(player_speed));
                    player[num_player].sprite.posx = fix32ToInt(player[num_player].x);
                    player[num_player].sprite_head.posx = fix32ToInt(player[num_player].x)+2;
                    player[num_player].sprite_weapon.posx = fix32ToInt(player[num_player].x)+pos_x_weapon;
                    updatePlayerGfxRight( num_player, 0 );
                }
            }
        }
        // colision completa, pasamos a stand
        else{
            player[num_player].state = state_stand;
            updatePlayerGfxRight( num_player, 0 );
        }
    }

    ////////////////////////////////////////
    // izquierda
    else if( direction == state_walk_left ){

        // sino la hay, muevo al jugador
        if(!player_collided && player[num_player].collision[0] <= water_tile && player[num_player].collision[1] <= water_tile && player[num_player].collision[2] <= water_tile){

            // si podemos nadar y estamos en algo de agua
            if(player[num_player].swim && (player[num_player].collision[0] == water_tile || player[num_player].collision[1] == water_tile || player[num_player].collision[2] == water_tile)){

                // movemos el sprite mas lento si ya estamos DENTRO del agua
                if( player[num_player].collision[3] == water_tile ){
                    player[num_player].x = fix32Sub(player[num_player].x, FIX32(player_slow_speed));
                    player[num_player].x_map = fix32Sub(player[num_player].x_map, FIX32(player_slow_speed));
                }
                else{
                    player[num_player].x = fix32Sub(player[num_player].x, FIX32(player_speed));
                    player[num_player].x_map = fix32Sub(player[num_player].x_map, FIX32(player_speed));
                }

                player[num_player].sprite.posx = fix32ToInt(player[num_player].x);
                player[num_player].sprite_head.posx = fix32ToInt(player[num_player].x)-1;
                player[num_player].sprite_weapon.posx = fix32ToInt(player[num_player].x)-pos_x_weapon;

                // cambiamos de frame
                if( player[num_player].collision[3] == water_tile )
                    updatePlayerGfxLeft( num_player, 1 );
                else
                    updatePlayerGfxLeft( num_player, 0 );
            }
            else{
                // si no podemos nadar hay que comprobar que no haya nada de agua para movernos
                if(player[num_player].collision[0] != water_tile && player[num_player].collision[1] != water_tile && player[num_player].collision[2] != water_tile){
                    player[num_player].x = fix32Sub(player[num_player].x, FIX32(player_speed));
                    player[num_player].x_map = fix32Sub(player[num_player].x_map, FIX32(player_speed));
                    player[num_player].sprite.posx = fix32ToInt(player[num_player].x);
                    player[num_player].sprite_head.posx = fix32ToInt(player[num_player].x)-1;
                    player[num_player].sprite_weapon.posx = fix32ToInt(player[num_player].x)-pos_x_weapon;
                    updatePlayerGfxLeft( num_player, 0 );
                }
            }
        }
        // colision completa, pasamos a stand
        else{
            player[num_player].state = state_stand;
            updatePlayerGfxLeft( num_player, 0 );
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  void updatePlayerGfxRight( u8 num_player ){
//  actualiza el sprite con la animacion de ANDAR DERECHA
//
//////////////////////////////////////////////////////////////////////////////////////
void updatePlayerGfxRight( u8 num_player, u8 state ){

    // cambiamos de frame
    player[num_player].frame++;

    // estado normal
    if( state == 0 ){
        if( player[num_player].frame == vel_anim1 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk1], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim2 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk2], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim3 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk3], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim4 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk4], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim5 )
            player[num_player].frame = 0;
    }
    // estado agua
    else if( state == 1 ){
        if( player[num_player].frame == vel_anim1 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim1], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim2 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim2], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim3 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim3], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim4 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim4], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim5 )
            player[num_player].frame = 0;
    }

    // actualizamos su valor en la tabla de sprites
    player[num_player].sprite.tile_attr = TILE_ATTR_FULL(PAL1, 0, 0, 0, player[num_player].tile_pos);
    player[num_player].sprite_head.tile_attr = TILE_ATTR_FULL(PAL1, 0, 0, 0, player[num_player].tile_pos+size_tiles_char);
    player[num_player].sprite_weapon.tile_attr = TILE_ATTR_FULL(PAL1, 0, 0, 0, player[num_player].tile_pos+size_tiles_char*2);

    VDP_setSpriteP(player[num_player].sprite_num, &player[num_player].sprite);
    VDP_setSpriteP(player[num_player].sprite_num-1, &player[num_player].sprite_weapon);
    VDP_setSpriteP(player[num_player].sprite_num-2, &player[num_player].sprite_head);
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  void updatePlayerGfxLeft( u8 num_player ){
//  actualiza el sprite con la animacion de ANDAR IZQUIERDA
//
//////////////////////////////////////////////////////////////////////////////////////
void updatePlayerGfxLeft( u8 num_player, u8 state ){

    // cambiamos de frame
    player[num_player].frame++;

    // estado normal
    if( state == 0 ){
        if( player[num_player].frame == vel_anim1 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk1], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim2 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk2], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim3 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk3], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim4 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk4], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim5 )
            player[num_player].frame = 0;
    }
    // estado agua
    else if( state == 1 ){
        if( player[num_player].frame == vel_anim1 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim1], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim2 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim2], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim3 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim3], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim4 )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim4], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].frame == vel_anim5 )
            player[num_player].frame = 0;
    }

    // actualizamos su valor en la tabla de sprites
    player[num_player].sprite.tile_attr = TILE_ATTR_FULL(PAL1, 0, 0, 1, player[num_player].tile_pos);
    player[num_player].sprite_head.tile_attr = TILE_ATTR_FULL(PAL1, 0, 0, 1, player[num_player].tile_pos+size_tiles_char);
    player[num_player].sprite_weapon.tile_attr = TILE_ATTR_FULL(PAL1, 0, 0, 1, player[num_player].tile_pos+size_tiles_char*2);

    VDP_setSpriteP(player[num_player].sprite_num, &player[num_player].sprite);
    VDP_setSpriteP(player[num_player].sprite_num-1, &player[num_player].sprite_weapon);
    VDP_setSpriteP(player[num_player].sprite_num-2, &player[num_player].sprite_head);
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  void updatePlayerGfxStand( u8 num_player ){
//  actualiza el sprite con la animacion de STAND
//
//////////////////////////////////////////////////////////////////////////////////////
void updatePlayerGfxStand( u8 num_player, u8 state ){

    // stand en el agua
    if( state == 1 ){

       /* if( player[num_player].direction == state_walk_right )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim1], player[num_player].tile_pos, size_tiles_char, 1);

        else if( player[num_player].direction == state_walk_left )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_swim1], player[num_player].tile_pos, size_tiles_char, 1);*/
    }
    // stand normal
    else{
        /*if( player[num_player].direction == state_walk_right )*/
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk1], player[num_player].tile_pos, size_tiles_char, 1);

         /*else if( player[num_player].direction == state_walk_left )
            VDP_loadTileData( tiles_chars01[player[num_player].character][char_side_walk1], player[num_player].tile_pos, size_tiles_char, 1);*/
    }
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  void updatePlayerGfxDeath( u8 a ){
//  actualiza el sprite con la animacion de MUERTE
//
//////////////////////////////////////////////////////////////////////////////////////
u8 updatePlayerGfxDeath( u8 a ){

    player[a].frame++;

    if( player[a].frame == vel_anim1 ){
        VDP_loadTileData( tiles_death[0], player[a].tile_pos, size_tiles_char*4, 1);

        player[a].sprite.posx = player[a].sprite.posx-8;
        player[a].sprite.posy = player[a].sprite.posy-8;
        VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
    }

    else if( player[a].frame == vel_anim2 )
        VDP_loadTileData( tiles_death[1], player[a].tile_pos, size_tiles_char*4, 1);

    else if( player[a].frame == vel_anim3)
        VDP_loadTileData( tiles_death[2], player[a].tile_pos, size_tiles_char*4, 1);

    else if( player[a].frame == vel_anim4)
        VDP_loadTileData( tiles_death[3], player[a].tile_pos, size_tiles_char*4, 1);

    else if( player[a].frame == vel_anim5)
        VDP_loadTileData( tiles_death[4], player[a].tile_pos, size_tiles_char*4, 1);

    else if( player[a].frame == vel_anim6)
        return 1;

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  void initPlayer( u8 a ){
//  reinicio al jugador tras morir
//
//////////////////////////////////////////////////////////////////////////////////////
void initPlayer( u8 a ){

    player[a].x = player[a].x_init;
    player[a].y = player[a].y_init;

    VDP_loadTileData( tiles_chars01[player[a].character][char_side_walk1], player[a].tile_pos, size_tiles_char, 1);
    VDP_loadTileData(tiles_weapons[0], player[a].tile_pos+size_tiles_char*2, size_tiles_char, 1);
    VDP_loadTileData(tiles_heads[player[a].character][0],  player[a].tile_pos+size_tiles_char, size_tiles_char, 1);

    player[a].state = state_stand;
    player[a].frame = 0;
    player[a].immunity = 1;
    player[a].hp = 10;

    player[a].sprite.posx = fix32ToInt(player[a].x);
    player[a].sprite.posy = fix32ToInt(player[a].y);

    player[a].sprite.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);

    player[a].sprite_weapon.posx = fix32ToInt(player[a].x)+pos_x_weapon;
    player[a].sprite_weapon.posy = fix32ToInt(player[a].y)-pos_y_weapon;

    player[a].sprite_head.posx = fix32ToInt(player[a].x)+1;
    player[a].sprite_head.posy = fix32ToInt(player[a].y)-pos_y_head;

    VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
    VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
    VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  u8 playerCollisionDetection( u8 num_player, u8 direction ){
//  calcula la colision del jugador con el escenario y el resto de jugadores
//
//////////////////////////////////////////////////////////////////////////////////////
u8 playerCollisionDetection( u8 num_player, u8 direction ){

    short range = 3;

    // desplazamientos para las colisiones con el mapa
    short desp_x1, desp_y1, desp_x2, desp_y2, desp_x3, desp_y3, desp_x4, desp_y4;
    desp_x1 = desp_y1 = desp_x2 = desp_y2 = desp_x3 = desp_y3 = 0;

    // aqui guardaremos temporalmente los datos de los jugadores a comprobar
    u8 numPlayerA, numPlayerB, numPlayerC;
    numPlayerA = numPlayerB = numPlayerC = 0;

    // reseteo las colisiones del jugador
    player[num_player].collision[0] = player[num_player].collision[1] = player[num_player].collision[2] = player[num_player].collision[3] = 0;

    /////////////////////////////////////////////////////////////////////////////
    // calculo el desplazamiento de la posicion de los 3 puntos de colision
    /////////////////////////////////////////////////////////////////////////////
	// arriba
	if( direction == state_walk_up ){

        desp_x1 = char_collision_left;
        desp_y1 = char_collision_up-range;

        desp_x2 = char_collision_mid_hor;
        desp_y2 = char_collision_up-range;

        desp_x3 = char_collision_right;
        desp_y3 = char_collision_up-range;
    }

    // abajo
	else if( direction == state_walk_down ){

        desp_x1 = char_collision_left;
        desp_y1 = char_collision_down+range;

        desp_x2 = char_collision_mid_hor;
        desp_y2 = char_collision_down+range;

        desp_x3 = char_collision_right;
        desp_y3 = char_collision_down+range;
    }

    // derecha
	else if( direction == state_walk_right ){

        desp_x1 = char_collision_right+range;
        desp_y1 = char_collision_up;

        desp_x2 = char_collision_right+range;
        desp_y2 = char_collision_mid_ver;

        desp_x3 = char_collision_right+range;
        desp_y3 = char_collision_down;
    }

    // izquierda
	else if( direction == state_walk_left ){

        desp_x1 = char_collision_left-range;
        desp_y1 = char_collision_up;

        desp_x2 = char_collision_left-range;
        desp_y2 = char_collision_mid_ver;

        desp_x3 = char_collision_left-range;
        desp_y3 = char_collision_down;
    }

    // punto central del personaje paa dibujarlo nadando
    desp_x4 = char_collision_mid_hor;
    desp_y4 = char_collision_mid_ver;


    ///////////////////////////////////////////////////////////////////////////////
    // comprueba los puntos de colision con el mapa de tiles en memoria
    ///////////////////////////////////////////////////////////////////////////////
    player[num_player].collision[0] = map_temp[((fix32ToInt(player[num_player].y)+desp_y1)>>3)*screen_width_tiles+((fix32ToInt(player[num_player].x)+desp_x1)>>3)];
    player[num_player].collision[1] = map_temp[((fix32ToInt(player[num_player].y)+desp_y2)>>3)*screen_width_tiles+((fix32ToInt(player[num_player].x)+desp_x2)>>3)];
    player[num_player].collision[2] = map_temp[((fix32ToInt(player[num_player].y)+desp_y3)>>3)*screen_width_tiles+((fix32ToInt(player[num_player].x)+desp_x3)>>3)];
    player[num_player].collision[3] = map_temp[((fix32ToInt(player[num_player].y)+desp_y4)>>3)*screen_width_tiles+((fix32ToInt(player[num_player].x)+desp_x4)>>3)];

    // debug
    /*VDP_drawTextBG( APLAN, "   ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 0);
    VDP_drawNumberBG( APLAN, ((fix32ToInt(player[num_player].y)+desp_y1)>>3)*40+((fix32ToInt(player[num_player].x)+desp_x1)>>3), TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 0);


    VDP_drawNumberBG( APLAN, player[num_player].collision[0], TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 1);
    VDP_drawNumberBG( APLAN, player[num_player].collision[1], TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 2);
    VDP_drawNumberBG( APLAN, player[num_player].collision[2], TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 3);*/

    ////////////////////////////////////////////////////
    // COLISION JUGADOR CON EL RESTO DE JUGADORES
    ////////////////////////////////////////////////////
    // segun el jugador detecto la colision con el resto
    if( !player[num_player].immunity ){
        if( num_player == 0 ){
            numPlayerA = 1;
            numPlayerB = 2;
            numPlayerC = 3;
        }
        else if( num_player == 1 ){
            numPlayerA = 0;
            numPlayerB = 2;
            numPlayerC = 3;
        }
        else if( num_player == 2 ){
            numPlayerA = 0;
            numPlayerB = 1;
            numPlayerC = 3;
        }
        else if( num_player == 3 ){
            numPlayerA = 0;
            numPlayerB = 1;
            numPlayerC = 2;
        }

        /////////////////////
        // arriba
        if( direction == state_walk_up ){
            if( player[numPlayerA].hp && !player[numPlayerA].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerA].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerA].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerA].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up-range == fix32ToInt(player[numPlayerA].y)+char_collision_down)){

                        return 1;
                        //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                    }
                }
            }

            if( player[numPlayerB].hp && !player[numPlayerB].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerB].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerB].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerB].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up-range == fix32ToInt(player[numPlayerB].y)+char_collision_down)){
                        return 1;
                    }
                }
            }

            if( player[numPlayerC].hp && !player[numPlayerC].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerC].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerC].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerC].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up-range == fix32ToInt(player[numPlayerC].y)+char_collision_down)){
                        return 1;
                    }
                }
            }
        }

        /////////////////////
        // derecha
        else if( direction == state_walk_right ){
            if( player[numPlayerA].hp && !player[numPlayerA].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right+range == fix32ToInt(player[numPlayerA].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerA].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerA].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerA].y)+char_collision_down)){

                        return 1;
                        //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                    }
                }
            }

            if( player[numPlayerB].hp && !player[numPlayerB].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right+range == fix32ToInt(player[numPlayerB].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerB].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerB].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerB].y)+char_collision_down)){
                        return 1;
                    }
                }
            }

            if( player[numPlayerC].hp && !player[numPlayerC].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right+range == fix32ToInt(player[numPlayerC].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerC].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerC].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerC].y)+char_collision_down)){
                        return 1;
                    }
                }
            }
        }

        /////////////////////
        // abajo
        else if( direction == state_walk_down ){
            if( player[numPlayerA].hp && !player[numPlayerA].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerA].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerA].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down+range == fix32ToInt(player[numPlayerA].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerA].y)+char_collision_down)){

                        return 1;
                        //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                    }
                }
            }

            if( player[numPlayerB].hp && !player[numPlayerB].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerB].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerB].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down+range == fix32ToInt(player[numPlayerB].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerB].y)+char_collision_down)){
                        return 1;
                    }
                }
            }

            if( player[numPlayerC].hp && !player[numPlayerC].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerC].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left <= fix32ToInt(player[numPlayerC].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down+range == fix32ToInt(player[numPlayerC].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerC].y)+char_collision_down)){
                        return 1;
                    }
                }
            }
        }

        /////////////////////
        // izquierda
        else if( direction == state_walk_left ){
            if( player[numPlayerA].hp && !player[numPlayerA].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerA].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left-range == fix32ToInt(player[numPlayerA].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerA].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerA].y)+char_collision_down)){

                        return 1;
                            //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                    }
                }
            }

            if( player[numPlayerB].hp && !player[numPlayerB].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerB].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left-range == fix32ToInt(player[numPlayerB].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerB].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerB].y)+char_collision_down)){
                        return 1;
                    }
                }
            }

            if( player[numPlayerC].hp && !player[numPlayerC].immunity){
                if( (fix32ToInt(player[num_player].x)+char_collision_right >= fix32ToInt(player[numPlayerC].x)+char_collision_left) && (fix32ToInt(player[num_player].x)+char_collision_left-range == fix32ToInt(player[numPlayerC].x)+char_collision_right)){
                    if( (fix32ToInt(player[num_player].y)+char_collision_down >= fix32ToInt(player[numPlayerC].y)+char_collision_up) && (fix32ToInt(player[num_player].y)+char_collision_up <= fix32ToInt(player[numPlayerC].y)+char_collision_down)){
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  void playersControl( u8 ticks, u16 state_p1, u16 state_p2, u16 state_p3, u16 state_p4  )
//  control de los jugadores
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void playersControl( u8 ticks, u16 state_p1, u16 state_p2, u16 state_p3, u16 state_p4  ){

    u8 a, b, c;
    u16 state_p[4];

    state_p[0] = state_p1;
    state_p[1] = state_p2;
    state_p[2] = state_p3;
    state_p[3] = state_p4;

    u8 player_collided;

    ///////////////////////////////////////////////////////
    // CONTROL DE LAS PULSACIONES
    ///////////////////////////////////////////////////////
    for( a = 0; a < 2; a++ ){ // max_num_players

        // si el jugador tiene vida
        if( player[a].hp ){


//VDP_drawNumberBG( APLAN, player[a].state, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 0, a);
//VDP_drawNumberBG( APLAN, player[a].jump_pressed, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 2, a);

            ////////////////////////////////////////////////////////////////////
            // SALTO y gravedad
            ////////////////////////////////////////////////////////////////////
            // Si se pulsa B y no estamos saltando
            if( state_p[a] & BUTTON_B && player[a].state < state_dead && player[a].jump_pressed == 0 && player[a].vel_y == 0){

                psgFxPlay(SELECT_SFX);

                player[a].state = state_jump;
                player[a].vel_y = 0;
                player[a].vel_y = fix32Sub(player[a].vel_y, jump_speed);

                // modificamos en consonancia su posicion relativa a la pantalla y la relativa al mapa
                player[a].y = fix32Add(player[a].y, player[a].vel_y);
                player[a].y_map = fix32Add(player[a].y_map, player[a].vel_y);

                player[a].jump_pressed = 1;
            }

            // compruebvo la colision del juegador con lo que hay abajo suyo
            player_collided = playerCollisionDetection( a, state_walk_down );

            // si no hay colision con algun tile, otro jugador o esta saltando, se modifica su velocidad vertical
            if(!player_collided && player[a].collision[0] <= water_tile && player[a].collision[1] <= water_tile && player[a].collision[2] <= water_tile ){

                // compruebvo la colision del juegador con lo que hay arriba suyo
                player_collided = playerCollisionDetection( a, state_walk_up );

                // noy ningun tile arriba suyo
                if((!player_collided && player[a].collision[0] <= water_tile && player[a].collision[1] <= water_tile && player[a].collision[2] <= water_tile)
                  || player[a].vel_y == 0 ){
                    // modificamos su velocidad vertical
                    player[a].vel_y = fix32Add(player[a].vel_y, gravity_speed);
                }
                else{
                    player[a].vel_y = gravity_speed;
                }

                // modificamos en consonancia su posicion relativa a la pantalla y la relativa al mapa
                player[a].y = fix32Add(player[a].y, player[a].vel_y);
                player[a].y_map = fix32Add(player[a].y_map, player[a].vel_y);

                /////////////////////////////////////////////////////////////////////////////////////
                // Si se pulsa DERECHA y no he llegado al tope derecho de la pantalla
                ////////////////////////////////////////////////////////////////////////////
                if( state_p[a] & BUTTON_RIGHT )
                    movePlayer(ticks, a, state_walk_right);

                /////////////////////////////////////////////////////////////////////////////////////////////
                // Si se pulsa IZQUIERDA y no he llegado al tope izquierdo de la pantalla
                ////////////////////////////////////////////////////////////////////////////
                if( state_p[a] & BUTTON_LEFT )
                    movePlayer(ticks, a, state_walk_left);

                // posicion del sprite
                player[a].sprite.posy = fix32ToInt(player[a].y);
                player[a].sprite_head.posy = fix32ToInt(player[a].y)-pos_y_head;
                player[a].sprite_weapon.posy = fix32ToInt(player[a].y)-pos_y_weapon;

                VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);
                VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
                VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
            }
            else{

                player[a].vel_y = 0;

                // correccion del salto chapucero total pero no hay tiempo para nada mejor cojones!
                if( fix32ToInt(player[a].y)%8 == 7 ){
                    player[a].y = intToFix32(fix32ToInt(player[a].y)+1);
                    player[a].y_map = intToFix32(fix32ToInt(player[a].y_map)+1);
                    player[a].sprite.posy = fix32ToInt(player[a].y);
                    player[a].sprite_head.posy = fix32ToInt(player[a].y)-pos_y_head;
                    player[a].sprite_weapon.posy = fix32ToInt(player[a].y)-pos_y_weapon;

                    VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);
                    VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
                    VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
                }
                if( fix32ToInt(player[a].y)%8 == 6 ){
                    player[a].y = intToFix32(fix32ToInt(player[a].y)+2);
                    player[a].y_map = intToFix32(fix32ToInt(player[a].y_map)+2);
                    player[a].sprite.posy = fix32ToInt(player[a].y);
                    player[a].sprite_head.posy = fix32ToInt(player[a].y)-pos_y_head;
                    player[a].sprite_weapon.posy = fix32ToInt(player[a].y)-pos_y_weapon;

                    VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);
                    VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
                    VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
                }
                else if( fix32ToInt(player[a].y)%8 == 1){
                    player[a].y = intToFix32(fix32ToInt(player[a].y)-1);
                    player[a].y_map = intToFix32(fix32ToInt(player[a].y_map)-1);
                    player[a].sprite.posy = fix32ToInt(player[a].y);
                    player[a].sprite_head.posy = fix32ToInt(player[a].y)-pos_y_head;
                    player[a].sprite_weapon.posy = fix32ToInt(player[a].y)-pos_y_weapon;

                    VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);
                    VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
                    VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
                }
                else if( fix32ToInt(player[a].y)%8 == 2 ){
                    player[a].y = intToFix32(fix32ToInt(player[a].y)-2);
                    player[a].y_map = intToFix32(fix32ToInt(player[a].y_map)-2);
                    player[a].sprite.posy = fix32ToInt(player[a].y);
                    player[a].sprite_head.posy = fix32ToInt(player[a].y)-pos_y_head;
                    player[a].sprite_weapon.posy = fix32ToInt(player[a].y)-pos_y_weapon;

                    VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);
                    VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
                    VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
                }
                else if( fix32ToInt(player[a].y)%8 == 3 ){
                    player[a].y = intToFix32(fix32ToInt(player[a].y)-3);
                    player[a].y_map = intToFix32(fix32ToInt(player[a].y_map)-3);
                    player[a].sprite.posy = fix32ToInt(player[a].y);
                    player[a].sprite_head.posy = fix32ToInt(player[a].y)-pos_y_head;
                    player[a].sprite_weapon.posy = fix32ToInt(player[a].y)-pos_y_weapon;

                    VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);
                    VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
                    VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
                }

                // vuelvo a permitir el salto si no está pulsado B ni estoy saltando
                if( !(state_p[a] & BUTTON_B) )
                    player[a].jump_pressed = 0;

                /////////////////////////////////////////////////////////////////////////////////////
                // Si se pulsa DERECHA y no he llegado al tope derecho de la pantalla
                ////////////////////////////////////////////////////////////////////////////
                if( state_p[a] & BUTTON_RIGHT ){

                    if( player[a].direction != state_walk_right )
                        player[a].direction = state_walk_right;

                    player[a].state = state_walk_right;
                    movePlayer(ticks, a, state_walk_right);
                }

                /////////////////////////////////////////////////////////////////////////////////////////////
                // Si se pulsa IZQUIERDA y no he llegado al tope izquierdo de la pantalla
                ////////////////////////////////////////////////////////////////////////////
                if( state_p[a] & BUTTON_LEFT ){
                    if( player[a].direction != state_walk_left )
                        player[a].direction = state_walk_left;

                    player[a].state = state_walk_left;
                    movePlayer(ticks, a, state_walk_left);
                }

                /////////////////////////////////////////////////////////////////////////////////////////////
                // si no hay nada pulsado, ponemos el stand
                /////////////////////////////////////////////////////////////////////////////////////////////
                //if((!(state_p[a] & BUTTON_UP) && !(state_p[a] & BUTTON_DOWN) && !(state_p[a] & BUTTON_LEFT) && !(state_p[a] & BUTTON_RIGHT) && player[a].state != state_shot ) || player[a].state == state_stand){
                if( !(state_p[a] & BUTTON_LEFT) && !(state_p[a] & BUTTON_RIGHT)){

                    // dejamos el frame de stand
                    if(player[a].frame != 0){
                        player[a].frame = 0;

                        // stand de agua
                        if( player[a].collision[3] == water_tile )
                            updatePlayerGfxStand( a, 1 );
                        else
                            updatePlayerGfxStand( a, 0 );
                    }

                    // y no estoy pisando el hielo, me paro, sino, 'resbala'
                    if( player[a].collision[3] != ice_tile )
                        player[a].state = state_stand;
                }
            }

            /////////////////////////////////////////////////////////////////////////////////////////////
            // Si se pulsa A y el disparo no esta activo
            ////////////////////////////////////////////////////////////////////////////
           if( state_p[a] & BUTTON_A && player[a].fire_pressed == 0 ){

               psgFxPlay(CONFIRM_SFX);

                b = 0;
                c = 225;
                while( b < max_num_player_shots ){
                    if( playerShot[a][b].state == state_shot_inactive ){
                        c = b;
                        b = max_num_player_shots;
                    }
                    b++;
                }

                // hay un disparo libre
                if( c < 255 ){
                    // en el agua no se puede disparar
                    if( player[a].swim && player[a].collision[3] == water_tile ){
                        ;
                    }
                    else{
                        // creo el disparo
                        if( player[a].direction == state_walk_right ){
                            playerShot[a][c].x = fix32Add(player[a].x, FIX32(shot_despx));
                            playerShot[a][c].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, weaponTilePos);
                        }
                        else {
                            playerShot[a][c].x = fix32Sub(player[a].x, FIX32(shot_despx));
                            playerShot[a][c].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,1, weaponTilePos);
                        }

                        playerShot[a][c].y = fix32Add(player[a].y, FIX32(shot_despy));
                        playerShot[a][c].sprite.posx = fix32ToInt(playerShot[a][c].x);
                        playerShot[a][c].sprite.posy = fix32ToInt(playerShot[a][c].y);

                        playerShot[a][c].state = player[a].fire_pressed = state_shot_active;
                        playerShot[a][c].direction = player[a].direction;
                    }
                }
            }

            ////////////////////////////////////////////////////////////////////////////
            // para evitar el disparo continuo
            ////////////////////////////////////////////////////////////////////////////
            if(!(state_p[a] & BUTTON_A) && player[a].fire_pressed == 1 && playerShot[a][0].state != state_shot_active)
                player[a].fire_pressed = 0;

        }
        /////////////////////////////////////////////////////////////////////////////////////////////
        // han matado al jugador
        /////////////////////////////////////////////////////////////////////////////////////////////
        else if( player[a].state == state_dead){

            player[a].sprite.size = SPRITE_SIZE(chars_tile_size_x*2,chars_tile_size_y*2);

            player[a].sprite.posy = fix32ToInt(player[a].y);
            player[a].sprite_weapon.posx = screen_width;
            player[a].sprite_head.posx = screen_width;



            VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
            VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
            VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);

            // actualizo la animacion de muerte
            if( updatePlayerGfxDeath(a)){
                // ha salido dela pantalla, restauro el jugador al estado y graficos iniciales
                initPlayer(a);
                 psgFxPlay(ERROR_SFX);
            }

        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        // control de la inmortalidad
        /////////////////////////////////////////////////////////////////////////////////////////////
        if( player[a].immunity > 0 ){

            // parpadeo
            ticks %= 10;
            if( ticks < 6 ){
                player[a].sprite.posx = player[a].sprite_head.posx = player[a].sprite_weapon.posx = screen_width;
            }
            else{
                player[a].sprite.posx = fix32ToInt(player[a].x);
                player[a].sprite_head.posx = fix32ToInt(player[a].x)+1;

                if( player[a].direction == 2 )
                    player[a].sprite_weapon.posx = fix32ToInt(player[a].x)+pos_x_weapon;
                else
                    player[a].sprite_weapon.posx = fix32ToInt(player[a].x)-pos_x_weapon;
            }

            // regresa a la vida tras 3 segundos
            player[a].immunity++;
            if( player[a].immunity == immunity_duration ){
                player[a].immunity = 0;

                player[a].sprite.posx = fix32ToInt(player[a].x);
                player[a].sprite_head.posx = fix32ToInt(player[a].x)+1;

                if( player[a].direction == 2 )
                    player[a].sprite_weapon.posx = fix32ToInt(player[a].x)+pos_x_weapon;
                else
                    player[a].sprite_weapon.posx = fix32ToInt(player[a].x)-pos_x_weapon;
            }

            VDP_setSpriteP(player[a].sprite_num, &player[a].sprite);
            VDP_setSpriteP(player[a].sprite_num-1, &player[a].sprite_weapon);
            VDP_setSpriteP(player[a].sprite_num-2, &player[a].sprite_head);
        }
    }
}





