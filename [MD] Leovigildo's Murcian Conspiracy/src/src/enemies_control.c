#include "main.h"


//////////////////////////////////////////////////////////////////////////////////////
//
//  void enemiesGenerator( void secs ){
//  genera un enemigo cada x tiempo
//
//////////////////////////////////////////////////////////////////////////////////////
void enemiesGenerator( u8 secs ){

    u8 a, b;

    if( secs % 5 == 0 ){

        for( b = 0; b < max_num_enemies; b++ ){

            // si el enemigo esta inactivo, lo activo y le doy valores
            if( enemies[b].state == state_enemy_inactive){

                enemies[b].state = state_enemy_active;

                enemies[b].x = FIX32(init_pos_x1);
                enemies[b].y = FIX32(init_pos_x2);
                enemies[b].sprite.posx = fix32ToInt(enemies[b].x);
                enemies[b].sprite.posy = fix32ToInt(enemies[b].y);


                a = random(100);

                if( a > 50 ){
                    enemies[b].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,0, enemiesTilePos);
                    enemies[b].direction = state_walk_right;
                }else{
                    enemies[b].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,1, enemiesTilePos);
                    enemies[b].direction = state_walk_left;
                }

                b = max_num_enemies;

                VDP_setSpriteP(enemies_sprite+b, &enemies[b].sprite);
            }
        }
    }
}



//////////////////////////////////////////////////////////////////////////////////////
//
//  u8 enemyCollisionDetection( u8 num_enemy, u8 direction ){
//  calcula la colision del enemigo con el escenario y el resto de jugadores
//
//////////////////////////////////////////////////////////////////////////////////////
u8 enemyCollisionDetection( u8 num_enemy, u8 direction ){

    short range = 3;
    u8 a;

    // desplazamientos para las colisiones con el mapa
    short desp_x1, desp_y1, desp_x2, desp_y2, desp_x3, desp_y3, desp_x4, desp_y4;
    desp_x1 = desp_y1 = desp_x2 = desp_y2 = desp_x3 = desp_y3 = 0;

    // reseteo las colisiones del jugador
    //enemies[num_enemy].collision[0] = enemies[num_enemy].collision[1] = enemies[num_enemy].collision[2] = enemies[num_enemy].collision[3] = 0;

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
    enemies[num_enemy].collision[0] = map_temp[((fix32ToInt(enemies[num_enemy].y)+desp_y1)>>3)*screen_width_tiles+((fix32ToInt(enemies[num_enemy].x)+desp_x1)>>3)];
    enemies[num_enemy].collision[1] = map_temp[((fix32ToInt(enemies[num_enemy].y)+desp_y2)>>3)*screen_width_tiles+((fix32ToInt(enemies[num_enemy].x)+desp_x2)>>3)];
    enemies[num_enemy].collision[2] = map_temp[((fix32ToInt(enemies[num_enemy].y)+desp_y3)>>3)*screen_width_tiles+((fix32ToInt(enemies[num_enemy].x)+desp_x3)>>3)];
    enemies[num_enemy].collision[3] = map_temp[((fix32ToInt(enemies[num_enemy].y)+desp_y4)>>3)*screen_width_tiles+((fix32ToInt(enemies[num_enemy].x)+desp_x4)>>3)];

    // debug
    /*VDP_drawTextBG( APLAN, "   ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 0);
    VDP_drawNumberBG( APLAN, ((fix32ToInt(enemies[num_enemy].y)+desp_y1)>>3)*40+((fix32ToInt(enemies[num_enemy].x)+desp_x1)>>3), TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 0);


    VDP_drawNumberBG( APLAN, enemies[num_enemy].collision[0], TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 1);
    VDP_drawNumberBG( APLAN, enemies[num_enemy].collision[1], TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 2);
    VDP_drawNumberBG( APLAN, enemies[num_enemy].collision[2], TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 1, 3);*/

    ////////////////////////////////////////////////////
    // COLISION JUGADOR CON EL RESTO DE JUGADORES
    ////////////////////////////////////////////////////
    // segun el jugador detecto la colision con el resto
    for( a = 0; a < max_num_players; a++ ){

        //if( !player[a].immunity && player[a].hp > 0){

            /////////////////////
            // arriba
            if( direction == state_walk_up ){

                if( (fix32ToInt(enemies[num_enemy].x)+char_collision_right >= fix32ToInt(player[a].x)+char_collision_left) && (fix32ToInt(enemies[num_enemy].x)+char_collision_left <= fix32ToInt(player[a].x)+char_collision_right)){
                    if( (fix32ToInt(enemies[num_enemy].y)+char_collision_down >= fix32ToInt(player[a].y)+char_collision_up) && (fix32ToInt(enemies[num_enemy].y)+char_collision_up-range == fix32ToInt(player[a].y)+char_collision_down)){

                        player[a].state = state_dead;
                        player[a].hp = 0;
                        return 1;
                        //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                    }
                }
            }

            /////////////////////
            // derecha
            else if( direction == state_walk_right ){

                if( (fix32ToInt(enemies[num_enemy].x)+char_collision_right+range == fix32ToInt(player[a].x)+char_collision_left) && (fix32ToInt(enemies[num_enemy].x)+char_collision_left <= fix32ToInt(player[a].x)+char_collision_right)){
                    if( (fix32ToInt(enemies[num_enemy].y)+char_collision_down >= fix32ToInt(player[a].y)+char_collision_up) && (fix32ToInt(enemies[num_enemy].y)+char_collision_up <= fix32ToInt(player[a].y)+char_collision_down)){

                        player[a].state = state_dead;
                         player[a].hp = 0;
                        return 1;
                        //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                    }
                }
            }

            /////////////////////
            // abajo
            else if( direction == state_walk_down ){

                if( (fix32ToInt(enemies[num_enemy].x)+char_collision_right >= fix32ToInt(player[a].x)+char_collision_left) && (fix32ToInt(enemies[num_enemy].x)+char_collision_left <= fix32ToInt(player[a].x)+char_collision_right)){
                    if( (fix32ToInt(enemies[num_enemy].y)+char_collision_down+range == fix32ToInt(player[a].y)+char_collision_up) && (fix32ToInt(enemies[num_enemy].y)+char_collision_up <= fix32ToInt(player[a].y)+char_collision_down)){

                        player[a].state = state_dead;
                         player[a].hp =  0;
                        return 1;
                        //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                    }
                }
            }

            /////////////////////
            // izquierda
            else if( direction == state_walk_left ){

                if( (fix32ToInt(enemies[num_enemy].x)+char_collision_right >= fix32ToInt(player[a].x)+char_collision_left) && (fix32ToInt(enemies[num_enemy].x)+char_collision_left-range == fix32ToInt(player[a].x)+char_collision_right)){
                    if( (fix32ToInt(enemies[num_enemy].y)+char_collision_down >= fix32ToInt(player[a].y)+char_collision_up) && (fix32ToInt(enemies[num_enemy].y)+char_collision_up <= fix32ToInt(player[a].y)+char_collision_down)){

                        player[a].state = state_dead;
                         player[a].hp = 0;
                        return 1;
                            //VDP_drawNumberBG( APLAN, 1, TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 3, 5);
                    }
                }
            }
        //}
    }

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////////////////////////
void animateEnemy( u8 a ){

    u8 mirror = 0;

    if( enemies[a].direction == state_walk_left )
        mirror = 1;

    enemies[a].frame++;

    if( enemies[a].state == state_enemy_active ){

        if( enemies[a].frame == vel_anim1 )
           enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,mirror, enemiesTilePos);

        else if( enemies[a].frame == vel_anim2 )
            enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,mirror, enemiesTilePos+size_tiles_char);

        else if( enemies[a].frame == vel_anim3)
            enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,mirror, enemiesTilePos+size_tiles_char*2);

        else if( enemies[a].frame == vel_anim4)
             enemies[a].frame = 0;
    }
    else if( enemies[a].state == state_enemy_dead ){

        if( enemies[a].frame == vel_anim1 )
           enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,mirror, enemiesTilePos+size_tiles_char*3);

        else if( enemies[a].frame == vel_anim2 )
            enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,mirror, enemiesTilePos+size_tiles_char*4);

        else if( enemies[a].frame == vel_anim3)
            enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,mirror, enemiesTilePos+size_tiles_char*5);

        else if( enemies[a].frame == vel_anim4)
             enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,mirror, enemiesTilePos+size_tiles_char*6);

        else if( enemies[a].frame == vel_anim5){
             enemies[a].frame = 0;
             enemies[a].state = state_enemy_inactive;
             enemies[a].x = FIX32(screen_width);
            enemies[a].sprite.posx = fix32ToInt(enemies[a].x);
        }

    }

     VDP_setSpriteP( enemies_sprite+a, &enemies[a].sprite);

}


//////////////////////////////////////////////////////////////////////////////////////
//
//  void enemiesGenerator( void secs ){
//  genera un enemigo cada x tiempo
//
//////////////////////////////////////////////////////////////////////////////////////
void enemiesControl(){

    u8 a;

    // para todos los enemigos
    for( a = 0; a < max_num_enemies; a++ ){

        // si esta activo
        if( enemies[a].state == state_enemy_active ){

            // compruebvo la colision del juegador con lo que hay abajo suyo
            enemyCollisionDetection( a, state_walk_down );

             // si no hay colision con algun tile, otro jugador o esta saltando, se modifica su velocidad vertical
            if( enemies[a].collision[0] <= water_tile && enemies[a].collision[1] <= water_tile && enemies[a].collision[2] <= water_tile ){

                enemies[a].vel_y = enemies[a].vel_y+gravity_speed;

                // modificamos en consonancia su posicion relativa a la pantalla y la relativa al mapa
                enemies[a].y = fix32Add(enemies[a].y, enemies[a].vel_y);
                enemies[a].y_map = fix32Add(enemies[a].y_map, enemies[a].vel_y);

                ////////////////////////////////////////////////////////////////////////////
                // si va a la DERECHA y no he llegado al tope derecho de la pantalla
                ////////////////////////////////////////////////////////////////////////////
                if( enemies[a].direction == state_walk_right ){
                    enemyCollisionDetection( a, state_walk_right );
                    enemies[a].x = fix32Add(enemies[a].x,FIX32(enemy_speed));
                }else{
                    enemyCollisionDetection( a, state_walk_left );
                    enemies[a].x = fix32Sub(enemies[a].x,FIX32(enemy_speed));
                }

                // cambio de orientacion al llegar a los extremos
                if( enemies[a].sprite.posx > screen_width-24 ){
                    enemies[a].direction = state_walk_left;
                    enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,1, enemiesTilePos);
                }
                else if( enemies[a].sprite.posx < 8 ){
                    enemies[a].direction = state_walk_right;
                    enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,0, enemiesTilePos);
                }

                // posicion del sprite
                enemies[a].sprite.posx = fix32ToInt(enemies[a].x);
                enemies[a].sprite.posy = fix32ToInt(enemies[a].y);
                VDP_setSpriteP(enemies_sprite+a, &enemies[a].sprite);
            }
            else{

                enemies[a].vel_y = 0;

                // correccion del salto chapucero total pero no hay tiempo para nada mejor cojones!
                if( fix32ToInt(enemies[a].y)%8 == 7 ){
                    enemies[a].y = intToFix32(fix32ToInt(enemies[a].y)+1);
                    enemies[a].y_map = intToFix32(fix32ToInt(enemies[a].y_map)+1);
                    enemies[a].sprite.posy = fix32ToInt(enemies[a].y);

                    VDP_setSpriteP(enemies_sprite+a, &enemies[a].sprite);
                }
                if( fix32ToInt(enemies[a].y)%8 == 6 ){
                    enemies[a].y = intToFix32(fix32ToInt(enemies[a].y)+2);
                    enemies[a].y_map = intToFix32(fix32ToInt(enemies[a].y_map)+2);
                    enemies[a].sprite.posy = fix32ToInt(enemies[a].y);

                    VDP_setSpriteP(enemies_sprite+a, &enemies[a].sprite);
                }
                else if( fix32ToInt(enemies[a].y)%8 == 1){
                    enemies[a].y = intToFix32(fix32ToInt(enemies[a].y)-1);
                    enemies[a].y_map = intToFix32(fix32ToInt(enemies[a].y_map)-1);
                    enemies[a].sprite.posy = fix32ToInt(enemies[a].y);

                    VDP_setSpriteP(enemies_sprite+a, &enemies[a].sprite);
                }
                else if( fix32ToInt(enemies[a].y)%8 == 2 ){
                    enemies[a].y = intToFix32(fix32ToInt(enemies[a].y)-2);
                    enemies[a].y_map = intToFix32(fix32ToInt(enemies[a].y_map)-2);
                    enemies[a].sprite.posy = fix32ToInt(enemies[a].y);

                    VDP_setSpriteP(enemies_sprite+a, &enemies[a].sprite);
                }
                else if( fix32ToInt(enemies[a].y)%8 == 3 ){
                    enemies[a].y = intToFix32(fix32ToInt(enemies[a].y)-3);
                    enemies[a].y_map = intToFix32(fix32ToInt(enemies[a].y_map)-3);
                    enemies[a].sprite.posy = fix32ToInt(enemies[a].y);

                    VDP_setSpriteP(enemies_sprite+a, &enemies[a].sprite);
                }

                ////////////////////////////////////////////////////////////////////////////
                // si va a la DERECHA y no he llegado al tope derecho de la pantalla
                ////////////////////////////////////////////////////////////////////////////
                if( enemies[a].direction == state_walk_right ){
                    enemyCollisionDetection( a, state_walk_right );
                    enemies[a].x = fix32Add(enemies[a].x,FIX32(enemy_speed));
                }else{
                    enemyCollisionDetection( a, state_walk_left );
                    enemies[a].x = fix32Sub(enemies[a].x,FIX32(enemy_speed));
                }

                // cambio de orientacion al llegar a los extremos
                if( enemies[a].sprite.posx > screen_width-24){
                    enemies[a].direction = state_walk_left;
                    enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,1, enemiesTilePos);
                }
                else if( enemies[a].sprite.posx < 8 ){
                    enemies[a].direction = state_walk_right;
                    enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,0, enemiesTilePos);
                }

                // posicion del sprite
                enemies[a].sprite.posx = fix32ToInt(enemies[a].x);
                enemies[a].sprite.posy = fix32ToInt(enemies[a].y);
                VDP_setSpriteP(enemies_sprite+a, &enemies[a].sprite);
            }
        }

        animateEnemy(a);
    }
}
