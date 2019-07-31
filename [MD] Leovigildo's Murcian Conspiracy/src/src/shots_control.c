#include "main.h"


//////////////////////////////////////////////////////////////////////////////////////
//
//  u8 playerCollisionDetection( u8 num_player, u8 direction ){
//  calcula la colision del jugador con el escenario y el resto de jugadores
//
//////////////////////////////////////////////////////////////////////////////////////
u8 playerShotsCollisionDetection( u8 num_player, u8 b, u8 direction ){

    short range = 1;    // rango de la colision

    // aqui guardaremos temporalmente los datos de los jugadores a comprobar
    u8 numPlayerA, numPlayerB, numPlayerC;
    numPlayerA = numPlayerB = numPlayerC = 0;

    /////////////////////////////////////////////////////////
    // segun el jugador detecto la colision con el resto
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

    u8 a;

    // para todos los disparos de los jugadores

    if( playerShot[num_player][b].state == state_shot_active ){

            //////////////////////////////////////////////////
            // compruebo las colisiones segun la direccion
            // arriba
            /*if( direction == state_walk_up ){
                if( player[numPlayerA].hp && !player[numPlayerA].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerA].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerA].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerA].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up-range <= fix32ToInt(player[numPlayerA].y)+char_collision_down)){

                            player[numPlayerA].hp = player[numPlayerA].frame = 0;
                            player[numPlayerA].state = state_dead;

                            // si matas a un jugador de tu equipo te resta puntuacion
                            if( player[numPlayerA].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                                //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                        }
                    }
                }

                if( player[numPlayerB].hp && !player[numPlayerB].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerB].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerB].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerB].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up-range <= fix32ToInt(player[numPlayerB].y)+char_collision_down)){

                            player[numPlayerB].hp = player[numPlayerB].frame = 0;
                            player[numPlayerB].state = state_dead;

                            if( player[numPlayerB].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                        }
                    }
                }

                if( player[numPlayerC].hp && !player[numPlayerC].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerC].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerC].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerC].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up-range <= fix32ToInt(player[numPlayerC].y)+char_collision_down)){

                            player[numPlayerC].hp = player[numPlayerC].frame = 0;
                            player[numPlayerC].state = state_dead;

                            if( player[numPlayerC].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                        }
                    }
                }
            }*/

            // derecha
            if( direction == state_walk_right ){
                if( player[numPlayerA].hp && !player[numPlayerA].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right+range >= fix32ToInt(player[numPlayerA].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerA].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerA].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerA].y)+char_collision_down)){

                            player[numPlayerA].hp = player[numPlayerA].frame = 0;
                            player[numPlayerA].state = state_dead;

                            if( player[numPlayerA].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                            //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                        }
                    }
                }

                if( player[numPlayerB].hp && !player[numPlayerB].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right+range >= fix32ToInt(player[numPlayerB].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerB].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerB].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerB].y)+char_collision_down)){

                            player[numPlayerB].hp = player[numPlayerB].frame = 0;
                            player[numPlayerB].state = state_dead;

                            if( player[numPlayerB].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                        }
                    }
                }

                if( player[numPlayerC].hp && !player[numPlayerC].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right+range >= fix32ToInt(player[numPlayerC].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerC].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerC].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerC].y)+char_collision_down)){

                            player[numPlayerC].hp = player[numPlayerC].frame = 0;
                            player[numPlayerC].state = state_dead;

                            if( player[numPlayerC].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                        }
                    }
                }
            }

            // abajo
           /* else if( direction == state_walk_down ){
                if( player[numPlayerA].hp && !player[numPlayerA].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerA].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerA].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down+range >= fix32ToInt(player[numPlayerA].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerA].y)+char_collision_down)){

                            player[numPlayerA].hp = player[numPlayerA].frame = 0;
                            player[numPlayerA].state = state_dead;

                            if( player[numPlayerA].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                            //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                        }
                    }
                }

                if( player[numPlayerB].hp && !player[numPlayerB].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerB].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerB].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down+range >= fix32ToInt(player[numPlayerB].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerB].y)+char_collision_down)){

                            player[numPlayerB].hp = player[numPlayerB].frame = 0;
                            player[numPlayerB].state = state_dead;

                            if( player[numPlayerB].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                        }
                    }
                }

                if( player[numPlayerC].hp && !player[numPlayerC].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerC].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(player[numPlayerC].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down+range >= fix32ToInt(player[numPlayerC].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerC].y)+char_collision_down)){

                            player[numPlayerC].hp = player[numPlayerC].frame = 0;
                            player[numPlayerC].state = state_dead;

                            if( player[numPlayerC].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                        }
                    }
                }
            }*/

            // izquierda
            else if( direction == state_walk_left ){
                if( player[numPlayerA].hp && !player[numPlayerA].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerA].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left-range <= fix32ToInt(player[numPlayerA].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerA].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerA].y)+char_collision_down)){

                            player[numPlayerA].hp = player[numPlayerA].frame = 0;
                            player[numPlayerA].state = state_dead;

                            if( player[numPlayerA].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                            //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                        }
                    }
                }

                if( player[numPlayerB].hp && !player[numPlayerB].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerB].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left-range <= fix32ToInt(player[numPlayerB].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerB].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerB].y)+char_collision_down)){

                            player[numPlayerB].hp = player[numPlayerB].frame = 0;
                            player[numPlayerB].state = state_dead;

                            if( player[numPlayerB].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                        }
                    }
                }

                if( player[numPlayerC].hp && !player[numPlayerC].immunity){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(player[numPlayerC].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left-range <= fix32ToInt(player[numPlayerC].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(player[numPlayerC].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(player[numPlayerC].y)+char_collision_down)){

                            player[numPlayerC].hp = player[numPlayerC].frame = 0;
                            player[numPlayerC].state = state_dead;

                            if( player[numPlayerC].team != player[num_player].team )
                                updatePlayerScore( num_player, 0 );
                            else
                                updatePlayerScore( num_player, 1 );

                            return 1;
                        }
                    }
                }
            }

    }

    // con los enemigos
    if( playerShot[num_player][b].state == state_shot_active ){

        for( a = 0; a < max_num_enemies; a++ ){

            // derecha
            if( direction == state_walk_right ){
                if( enemies[a].state == state_enemy_active){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right+range >= fix32ToInt(enemies[a].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left <= fix32ToInt(enemies[a].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(enemies[a].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(enemies[a].y)+char_collision_down)){

                            enemies[a].frame = 0;
                            enemies[a].state = state_enemy_dead;

                            updatePlayerScore( num_player, 2 );

                            return 1;
                            //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                        }
                    }
                }

            }

            // izquierda
            else if( direction == state_walk_left ){
               if( enemies[a].state == state_enemy_active){
                    if( (fix32ToInt(playerShot[num_player][b].x)+shot_collision_right >= fix32ToInt(enemies[a].x)+char_collision_left) && (fix32ToInt(playerShot[num_player][b].x)+char_collision_left-range <= fix32ToInt(enemies[a].x)+char_collision_right)){
                        if( (fix32ToInt(playerShot[num_player][b].y)+shot_collision_down >= fix32ToInt(enemies[a].y)+char_collision_up) && (fix32ToInt(playerShot[num_player][b].y)+shot_collision_up <= fix32ToInt(enemies[a].y)+char_collision_down)){

                            enemies[a].frame = 0;
                            enemies[a].state = state_enemy_dead;

                            updatePlayerScore( num_player, 2 );

                            return 1;
                            //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                        }
                    }
                }

            }
        }
    }


    ///////////////////////////////////////////////////////////////////
    // COLISIONES CON EL MAPA
    ///////////////////////////////////////////////////////////////////
    // desplazamientos para las colisiones con el mapa
    /*short desp_x1, desp_y1;     // desplazamientos de la colision segun la direccion del disparo
    u16 temp1, temp2;                  // para el calculo de la posicion en el vector temporal del mapa

    desp_x1 = desp_y1 = temp1 = temp2 = 0;

    ///////////////////////////////////////////////////////////////////////////////
    // comprueba los puntos de colision con el mapa de tiles en memoria
    ///////////////////////////////////////////////////////////////////////////////
	// arriba
	if( direction == state_walk_up ){

	    // desplazamientos de la colision segun la direccion del disparo
        desp_y1 = ((fix32ToInt(playerShot[num_player][b].y))+shot_collision_up-range)>>3;
        desp_x1 = fix32ToInt(playerShot[num_player][b].x)>>3;

        // calculo de la posicion del disparo en el vector temporal del mapa
        temp1 = desp_y1*screen_width_tiles+desp_x1;

        // segun la posicion del disparo respecto a la rejilla de tiles compruebo una columna o dos
        if( fix32ToInt(playerShot[num_player][b].x)%8 >= 2 ){

            // debug
            //VDP_drawTextBG( APLAN, "2", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), (fix32ToInt(playerShot[num_player][b].x)>>3)+1, fix32ToInt(playerShot[num_player][b].y)>>3);
            //VDP_drawTextBG( APLAN, "1", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, fix32ToInt(playerShot[num_player][b].y)>>3);

            // puede chocar con un tile destructible e indestructible
            if(map_temp[temp1] >= destructible_tile1A){

                ///////////////////////////////////////////
                // tile entero
                // si es destructible ademas borro el tile
                if(map_temp[temp1] == destructible_tile1A){
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1);
                    map_temp[temp1] = destructible_tile1B;
                }
                ///////////////////////////////////////////
                // tile dañado
                // si es destructible ademas borro el tile
                else if(map_temp[temp1] == destructible_tile1B){
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    map_temp[temp1] = 0;
                }

                /////////////////////////////////////
                // segunda columna
                if(map_temp[temp1+1] == destructible_tile1A){
                    map_temp[temp1+1] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1+1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1+1, desp_y1);
                }
                else if(map_temp[temp1+1] == destructible_tile1B){
                    map_temp[temp1+1] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1+1, desp_y1);
                }

                // desactivo el disparo en ambos casos por igual
                return 1;
            }
            else if( map_temp[temp1+1] >= destructible_tile1A){

                // segunda columna
                if( map_temp[temp1+1] == destructible_tile1A){
                    map_temp[temp1+1] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1+1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1+1, desp_y1);
                }
                else if( map_temp[temp1+1] == destructible_tile1B){
                    map_temp[temp1+1] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1+1, desp_y1);
                }

                return 1;
            }
        }
        else{

            // debug
            //VDP_drawTextBG( APLAN, "1", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, fix32ToInt(playerShot[num_player][b].y)>>3);

            // solo compruebo una columna
            if(map_temp[temp1] >= destructible_tile1A){

                if(map_temp[temp1] == destructible_tile1A){
                    map_temp[temp1] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1);
                }
                else if(map_temp[temp1] == destructible_tile1B){
                    map_temp[temp1] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                }

                return 1;
            }
        }
    }

    // abajo
	else if( direction == state_walk_down ){

        // desplazamientos de la colision segun la direccion del disparo
        desp_y1 = ((fix32ToInt(playerShot[num_player][b].y))+shot_collision_down+range)>>3;
        desp_x1 = fix32ToInt(playerShot[num_player][b].x)>>3;

        // calculo de la posicion del disparo en el vector temporal del mapa
        temp1 = desp_y1*screen_width_tiles+desp_x1;

        // segun la posicion del disparo respecto a la rejilla de tiles compruebo una columna o dos
        if( fix32ToInt(playerShot[num_player][b].x)%8 >= 2 ){

            // debug
            //VDP_drawTextBG( APLAN, "2", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), (fix32ToInt(playerShot[num_player][b].x)>>3)+1, fix32ToInt(playerShot[num_player][b].y)>>3);
            //VDP_drawTextBG( APLAN, "1", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, fix32ToInt(playerShot[num_player][b].y)>>3);

            // puede chocar con un tile destructible e indestructible
            if(map_temp[temp1] >= destructible_tile1A){

                // si es destructible ademas borro el tile
                if(map_temp[temp1] == destructible_tile1A){
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1);
                    map_temp[temp1] = destructible_tile1B;
                }
                else if(map_temp[temp1] == destructible_tile1B){
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    map_temp[temp1] = 0;
                }

                // segunda columna
                if(map_temp[temp1+1] == destructible_tile1A){
                    map_temp[temp1+1] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1+1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1+1, desp_y1);
                }
                else if(map_temp[temp1+1] == destructible_tile1B){
                    map_temp[temp1+1] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1+1, desp_y1);
                }

                // desactivo el disparo en ambos casos por igual
                return 1;
            }
            else if( map_temp[temp1+1] >= destructible_tile1A){

                // segunda columna
                if( map_temp[temp1+1] == destructible_tile1A){
                    map_temp[temp1+1] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1+1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1+1, desp_y1);
                }
                else if( map_temp[temp1+1] == destructible_tile1B){
                    map_temp[temp1+1] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1+1, desp_y1);
                }

                return 1;
            }
        }
        else{
            // debug
            //VDP_drawTextBG( APLAN, "1", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, fix32ToInt(playerShot[num_player][b].y)>>3);

            // solo compruebo una columna
            if(map_temp[temp1] >= destructible_tile1A){

                if(map_temp[temp1] == destructible_tile1A){
                    map_temp[temp1] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1);
                }
                else if(map_temp[temp1] == destructible_tile1B){
                    map_temp[temp1] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                }

                return 1;
            }
        }
    }

    // derecha
	if( direction == state_walk_right ){

	    // desplazamientos de la colision segun la direccion del disparo
        desp_x1 = (((fix32ToInt(playerShot[num_player][b].x))+shot_collision_right+range)>>3);
        desp_y1 = fix32ToInt(playerShot[num_player][b].y)>>3;

        // calculo de la posicion del disparo en el vector temporal del mapa
        temp1 = desp_y1*screen_width_tiles+desp_x1;
        temp2 = temp1 + screen_width_tiles;


        // segun la posicion del disparo respecto a la rejilla de tiles compruebo una fila o dos
        if( fix32ToInt(playerShot[num_player][b].y)%8 < 2 ){

            // debug
            //VDP_drawTextBG( APLAN, "1", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, fix32ToInt(playerShot[num_player][b].y)>>3);

            // solo compruebo una fila
            if(map_temp[temp1] >= destructible_tile1A){

                if(map_temp[temp1] == destructible_tile1A){
                    map_temp[temp1] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1);
                }
                else if(map_temp[temp1] == destructible_tile1B){
                    map_temp[temp1] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                }


                return 1;
            }
        }
        else{
            // debug
            //VDP_drawTextBG( APLAN, "2", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, (fix32ToInt(playerShot[num_player][b].y)>>3)+1);
            //VDP_drawTextBG( APLAN, "1", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, fix32ToInt(playerShot[num_player][b].y)>>3);

            // compruebo ambas filas
            // puede chocar con un tile destructible e indestructible
            if(map_temp[temp1] >= destructible_tile1A){

                // si es destructible ademas borro el tile
                if(map_temp[temp1] == destructible_tile1A){
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1);
                    map_temp[temp1] = destructible_tile1B;
                }
                else if(map_temp[temp1] == destructible_tile1B){
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    map_temp[temp1] = 0;
                }

                // segunda columna
                if(map_temp[temp2] == destructible_tile1A){
                    map_temp[temp2] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1+1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1+1);
                }
                else if(map_temp[temp2] == destructible_tile1B){
                    map_temp[temp2] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1+1);
                }

                // desactivo el disparo en ambos casos por igual
                return 1;
            }
            else if( map_temp[temp2] >= destructible_tile1A){

                // segunda columna
                if( map_temp[temp2] == destructible_tile1A){
                    map_temp[temp2] = destructible_tile1B;
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1+1);
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1+1);
                }
                else if( map_temp[temp2] == destructible_tile1B){
                    map_temp[temp2] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1+1);
                }

                return 1;
            }
        }
    }

    // izquierda
	else if( direction == state_walk_left ){

	    // desplazamientos de la colision segun la direccion del disparo
        desp_x1 = (((fix32ToInt(playerShot[num_player][b].x))+char_collision_left-range)>>3);
        desp_y1 = fix32ToInt(playerShot[num_player][b].y)>>3;

        // calculo de la posicion del disparo en el vector temporal del mapa
        temp1 = desp_y1*screen_width_tiles+desp_x1;
        temp2 = temp1 + screen_width_tiles;

        // segun la posicion del disparo respecto a la rejilla de tiles compruebo una fila o dos
        if( fix32ToInt(playerShot[num_player][b].y)%8 < 2 ){

            // debug
            //VDP_drawTextBG( APLAN, "1", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, fix32ToInt(playerShot[num_player][b].y)>>3);

            // solo compruebo una fila
            if(map_temp[temp1] >= destructible_tile1A){

                if(map_temp[temp1] == destructible_tile1A){
                    map_temp[temp1] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1);
                }
                else if(map_temp[temp1] == destructible_tile1B){
                    map_temp[temp1] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                }

                return 1;
            }
        }
        else{
            // debug
            //VDP_drawTextBG( APLAN, "2", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, (fix32ToInt(playerShot[num_player][b].y)>>3)+1);
            //VDP_drawTextBG( APLAN, "1", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), fix32ToInt(playerShot[num_player][b].x)>>3, fix32ToInt(playerShot[num_player][b].y)>>3);

            // compruebo las dos filas
            // puede chocar con un tile destructible e indestructible
           if(map_temp[temp1] >= destructible_tile1A){

                // si es destructible ademas borro el tile
                if(map_temp[temp1] == destructible_tile1A){
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1);
                    map_temp[temp1] = destructible_tile1B;
                }
                else if(map_temp[temp1] == destructible_tile1B){
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1);
                    map_temp[temp1] = 0;
                }

                // segunda columna
                if(map_temp[temp2] == destructible_tile1A){
                    map_temp[temp2] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1+1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1+1);
                }
                else if(map_temp[temp2] == destructible_tile1B){
                    map_temp[temp2] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1+1);
                }

                // desactivo el disparo en ambos casos por igual
                return 1;
            }
            else if( map_temp[temp2] >= destructible_tile1A){

                // segunda columna
                if( map_temp[temp2] == destructible_tile1A){
                    map_temp[temp2] = destructible_tile1B;
                    //VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1+1);
                    VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, map_temp[destructible_tile1B]), desp_x1, desp_y1+1);
                }
                else if( map_temp[temp2] == destructible_tile1B){
                    map_temp[temp2] = 0;
                    VDP_drawTextBG( APLAN, " ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), desp_x1, desp_y1+1);
                }

                return 1;
            }
        }
    }*/

    // si llego aqui es que no ha habido colision con nada
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  void playersShotsControl(){
//  control de los disparos del jugador
//
//////////////////////////////////////////////////////////////////////////////////////
void playersShotsControl( u8 ticks ){

    u8 a, b;

    ticks %= 10;

    ////////////////////////////////
    // si el disparo esta activo
    for( b = 0; b < max_num_players; b++ ){ //
        for( a = 0; a < max_num_player_shots; a++){

            // si el disparo esta activo
            if( playerShot[b][a].state == state_shot_active ){

                // derecha
                if( playerShot[b][a].direction == state_walk_right ){

                    if( playerShot[b][a].sprite.posx > screen_width || playerShotsCollisionDetection( b, a, playerShot[b][a].direction )){
                        playerShot[b][a].state = state_shot_collision;
                        //playerShot[b][a].sprite.posx = playerShot[b][a].sprite.posx+4;
                    }
                    else{
                        playerShot[b][a].x = fix32Add(playerShot[b][a].x, shot_speed );
                        playerShot[b][a].sprite.posx = fix32ToInt(playerShot[b][a].x);
                    }
                }

                // izquierda
                else{

                   if( fix32ToInt(playerShot[b][a].x) < 0 || playerShotsCollisionDetection( b, a, playerShot[b][a].direction)){
                        playerShot[b][a].state = state_shot_collision;





                    }
                    else{
                        playerShot[b][a].x = fix32Sub(playerShot[b][a].x, shot_speed );
                        playerShot[b][a].sprite.posx = fix32ToInt(playerShot[b][a].x);
                    }
                }

                VDP_setSpriteP(playerShot[b][a].sprite_num, &playerShot[b][a].sprite);
            }

            // ha chocado con algo
            else if( playerShot[b][a].state >= state_shot_collision ){

               /* // le cambiamos el grafico cuando toca
                if( playerShot[b][a].state == state_shot_collision ){
                    playerShot[b][a].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, playerShot[b][3].tile_pos+2);
                    VDP_setSpriteP(playerShot[b][a].sprite_num, &playerShot[b][a].sprite);
                }
                else if( playerShot[b][a].state == state_shot_anim1 ){
                    playerShot[b][a].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, playerShot[b][3].tile_pos+3);
                    VDP_setSpriteP(playerShot[b][a].sprite_num, &playerShot[b][a].sprite);
                }
                else if( playerShot[b][a].state == state_shot_anim2 ){
                    playerShot[b][a].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, playerShot[b][3].tile_pos+4);
                    VDP_setSpriteP(playerShot[b][a].sprite_num, &playerShot[b][a].sprite);
                }

                playerShot[b][a].state++;

                // fin del disparo
                if( playerShot[b][a].state == state_shot_end ){*/

                    playerShot[b][a].state = state_shot_inactive;

                    // sacamos el sprite de la pantalla
                    playerShot[b][a].x = FIX32(screen_width);
                    playerShot[b][a].sprite.posx = fix32ToInt(playerShot[b][a].x);
                    VDP_setSpriteP(playerShot[b][a].sprite_num, &playerShot[b][a].sprite);
               // }
            }


        }
    }
}



