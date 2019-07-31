#include "genesis.h"
#include "main.h"

/////////////////////////////////////////////////////////////////
//
// void initRecords(){
// valores iniciales de la pantalla de records
//
/////////////////////////////////////////////////////////////////
void initRecords(){

    strcpy(namesTable[0], "POCKETLUCHO");
    strcpy(namesTable[1], "MANUTRIGGER");
    strcpy(namesTable[2], "DORAGASUMAN");
    strcpy(namesTable[3], "MURCIANATOR");
    strcpy(namesTable[4], "ALBERTRUCHO");
    strcpy(namesTable[5], "THE BRUCER ");
    strcpy(namesTable[6], "MANVEREITOR");
    strcpy(namesTable[7], "DANISNOWMAN");
    strcpy(namesTable[8], "JORDIMONTOR");
    strcpy(namesTable[9], "VAKAPPTRON ");

    pointsTable[0] = 55000;
    pointsTable[1] = 23500;
    pointsTable[2] = 12500;
    pointsTable[3] = 2000;
    pointsTable[4] = 1500;
    pointsTable[5] = 1000;
    pointsTable[6] = 750;
    pointsTable[7] = 500;
    pointsTable[8] = 50;
    pointsTable[9] = 5;

    stagesTable[0] = 20;
    stagesTable[1] = 18;
    stagesTable[2] = 15;
    stagesTable[3] = 13;
    stagesTable[4] = 12;
    stagesTable[5] = 12;
    stagesTable[6] = 8;
    stagesTable[7] = 6;
    stagesTable[8] = 3;
    stagesTable[9] = 1;

    // Inicializar logros a 0
    ad.achievements = 0;

    // Logro 18 conseguido!
    //ad.achiev18 = 1;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void initVars( u8 num_players, u8 mode, u8 time, u8 stage ){
// doy valor inicial a las variables del juego (personajes...)
// y carga los tiles de los personajes e inicia sus sprites
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initGame( u8 num_players, u8 mode, u8 stage, u8 *mins, u8 *secs ){

    u16 a, c;
    u8 b;
    u8 num_castles = 0;
//    u8 castlesTemp[4];

    // desactivo el modo HS
    VDP_setHilightShadow(0);

    // reseteo las capas, los sprites
    VDP_clearPlan(APLAN, 0);
    VDP_clearPlan(BPLAN, 0);
    VDP_resetSprites();
    VDP_updateSprites();

    // muevo el scroll a su posicion original
    VDP_setHorizontalScroll(BPLAN, 0);
    VDP_setVerticalScroll(BPLAN, 0);
    VDP_setHorizontalScroll(APLAN, 0);
    VDP_setVerticalScroll(APLAN, 0);

    // cambia el color del fondo
    VDP_setReg(7, 0x20);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// TIEMPO DE LA PARTIDA
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if( *mins == 0 )
        *mins = 3;
    else if( *mins == 1 )
        *mins = 5;
    else if( *mins == 2 )
        *mins = 10;
    *secs = 0;}


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// CARGA Y DIBUJADO DE LOS MAPAS DE TILES (PAL 2 y 3)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // cargo el mapa de tiles de la rom al vector de trabajo
    // 40*27 = 1080
    for( a = 0; a < tam_map_tiles; a++)
        map_temp[a] = map_bg_01_01[a];


    //carga los tiles en VRAM del fondo fijo
    VDP_loadTileData( tiles_bg_01, 1, tiles_bg_01_size, 1);
    VDP_setPalette(PAL2, pal_bg_01);

    VDP_setTileMapRectEx( BPLAN, map_bg_01, 1, TILE_ATTR_FULL(PAL2, 0, 0, 0, 0), 0, 0, tam_map_h_tiles, tam_map_v_tiles );    // plano, data, index, baseflags, x, y, w, h

    //carga los tiles en VRAM del fondo interactivo
    VDP_loadTileData( tiles_bg_01_01, tiles_bg_01_size+1, tiles_bg_01_01_size, 1);
    VDP_setPalette(PAL3, pal_bg_01_01);

    // dibujo el mapa tile a tile para poder cambiar la prioridad de los tiles del bosque
    c = 0;
    for( a = 0; a < tam_map_v_tiles; a++ ){
        for( b = 0;  b < tam_map_h_tiles; b++ ){

            if( map_temp[c] != forest_tile )
                VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 0, 0, 0, tiles_bg_01_size+1+map_temp[c]), b, a);
            else
                VDP_setTileMap (APLAN, TILE_ATTR_FULL(PAL3, 1, 0, 0, tiles_bg_01_size+1+map_temp[c]), b, a);

            c++;
        }
    }}


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// CARGA DE LOS TILES EN VRAM DE LOS SPRITES (PAL 1)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // posicion de los tiles en vram
    player[0].tile_pos = tiles_bg_01_size+tiles_bg_01_01_size+1;
    player[1].tile_pos = player[0].tile_pos+size_tiles_char*4;
    player[2].tile_pos = player[1].tile_pos+size_tiles_char*4;
    player[3].tile_pos = player[2].tile_pos+size_tiles_char*4;

    //flags[0].tile_pos = player[3].tile_pos+size_tiles_char*5;

    weaponTilePos = player[3].tile_pos+size_tiles_char*5;

    enemiesTilePos = weaponTilePos+size_tiles_char*4;


    ////////////////////////////////////////////
    // PERSONAJES
    VDP_loadTileData( tiles_chars01[0][0], player[0].tile_pos, size_tiles_char, 1);
    VDP_loadTileData( tiles_chars01[1][0], player[1].tile_pos, size_tiles_char, 1);
    VDP_loadTileData( tiles_chars01[2][0], player[2].tile_pos, size_tiles_char, 1);
    VDP_loadTileData( tiles_chars01[3][0], player[3].tile_pos, size_tiles_char, 1);

    VDP_loadTileData(tiles_heads[player[0].character][0],  player[0].tile_pos+size_tiles_char, size_tiles_char, 1);
    VDP_loadTileData(tiles_heads[player[1].character][0],  player[1].tile_pos+size_tiles_char, size_tiles_char, 1);
    VDP_loadTileData(tiles_heads[player[2].character][0],  player[2].tile_pos+size_tiles_char, size_tiles_char, 1);
    VDP_loadTileData(tiles_heads[player[3].character][0],  player[3].tile_pos+size_tiles_char, size_tiles_char, 1);

    VDP_loadTileData(tiles_weapons[0], player[0].tile_pos+size_tiles_char*2, size_tiles_char, 1);
    VDP_loadTileData(tiles_weapons[0], player[1].tile_pos+size_tiles_char*2, size_tiles_char, 1);
    VDP_loadTileData(tiles_weapons[0], player[2].tile_pos+size_tiles_char*2, size_tiles_char, 1);
    VDP_loadTileData(tiles_weapons[0], player[3].tile_pos+size_tiles_char*2, size_tiles_char, 1);

    VDP_loadTileData(tiles_bullets, weaponTilePos, 4, 1);

    ////////////////////////////////////////////
    // ENEMIGOS
    VDP_loadTileData(tiles_enemies01, enemiesTilePos, size_tiles_char*7, 1);

    ///////////////////////////////////////////////
    // BANDERAS
    if( mode == 2 ){
        VDP_loadTileData( tiles_flags[0], flags[0].tile_pos, size_tiles_char, 1);
        VDP_loadTileData( tiles_flags[1], flags[1].tile_pos, size_tiles_char, 1);
        VDP_loadTileData( tiles_flags[2], flags[2].tile_pos, size_tiles_char, 1);
        VDP_loadTileData( tiles_flags[3], flags[3].tile_pos, size_tiles_char, 1);
    }

    ///////////////////////////////////////////////
    // TORRES
    else if( mode == 3 ){
        VDP_loadTileData( tiles_towers, flags[0].tile_pos, 16, 1);
    }

    ////////////////////////////////////////////
    // CARTELES
    VDP_loadTileData( tiles_number3,  enemiesTilePos+size_tiles_char*7, 16, 1);
    VDP_loadTileData( tiles_GO2,  enemiesTilePos+size_tiles_char*7+32, 16, 1);

    VDP_setPalette(PAL0, pal_enemies01);
    VDP_setPalette(PAL1, pal_chars01);}


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // BANDERAS (mode 2), valores iniciales y sprites
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*if( mode < 3 ){

        // indice de los SPRITES
        for( a = 0; a < max_num_flags; a++)
            flags[a].sprite_num = flag_sprite+a;

        // valores iniciales de los SPRITES
        for( a = 0; a < max_num_flags; a++){
            flags[a].state = flags[a].step = 0;
            flags[a].sprite.posx = screen_width;
            flags[a].sprite.posy = 0;
            flags[a].sprite.size = SPRITE_SIZE(chars_tile_size_x, chars_tile_size_y);
            flags[a].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[a].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
            flags[a].sprite.link  = flags[a+1].sprite_num;
            VDP_setSpriteP(flags[a].sprite_num, &flags[a].sprite);
        }
    }*/


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CASTILLOS (mode 3), valores iniciales, sprites y posiciones
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /* else if( mode == 3 ){

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        {// calculo del NUMERO de CASTILLOS
        num_castles = 0;
        castlesTemp[0] = castlesTemp[1] = castlesTemp[2] = castlesTemp[3] = 2;

        for( a = 0; a < num_players; a++){

            for( b = 0; b < max_num_players; b++ ){
                if( player[a].team != castlesTemp[b] ){
                    if( castlesTemp[b] == 2 ){
                        castlesTemp[b] = player[a].team;
                        b = 4;
                    }
                }
                else
                    b = 4;
            }
        }

        if( castlesTemp[3] != 2 )
            num_castles = 4;
        else if( castlesTemp[2] != 2 )
            num_castles = 3;
        else
            num_castles = 2;}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        {// valores iniciales de los SPRITES
        // indice de los SPRITES (o hay banderas o castillos, usan su mismo indice)
        for( a = 0; a < max_num_players; a++)
            castles[a].sprite_num = flag_sprite+a;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        {// castillo numero 1
        castles[0].state = 1;
        castles[0].sprite.size = SPRITE_SIZE(chars_tile_size_x, chars_tile_size_y);
        castles[0].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[0].character].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
        castles[0].sprite.link  = castles[1].sprite_num;}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        {// castillo numero 2
        castles[1].state = 1;
        castles[1].sprite.size = SPRITE_SIZE(chars_tile_size_x, chars_tile_size_y);
        if( player[1].team != player[0].team)
            castles[1].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[1].character].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
        else if( player[2].team != player[0].team)
            castles[1].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[2].character].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
        else if( player[3].team != player[0].team)
            castles[1].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[3].character].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
        castles[1].sprite.link  = castles[2].sprite_num;}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        {// castillo numero 3
        castles[2].state = 0;
        castles[2].sprite.size = SPRITE_SIZE(chars_tile_size_x, chars_tile_size_y);
        if( num_players == 3 )
            castles[2].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[2].character].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
        else{

           // player 1 y 2 son de distinto equipo, 2 castillos usados
           if( player[1].team != player[0].team){

                if( player[2].team != player[0].team && player[2].team != player[1].team)
                    castles[2].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[2].character].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
                else
                    castles[2].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[3].character].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
           }
           else{
                castles[2].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[3].character].tile_pos);
           }
        }
        castles[2].sprite.link  = castles[3].sprite_num;}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        {// castillo numero 4
        castles[3].state = 0;
        castles[3].sprite.size = SPRITE_SIZE(chars_tile_size_x, chars_tile_size_y);
        castles[3].sprite.tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, flags[player[3].character].tile_pos); // paleta, prioridad, vflip, hflip, tile 1
        castles[3].sprite.link  = 0;}

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        {// posiciones de los castillos, dependen de su numero
        if( num_castles == 2 ){
            castles[0].sprite.posx = init_pos_x1;
            castles[0].sprite.posy = init_pos_y1;

            castles[1].sprite.posx = init_pos_x1;
            castles[1].sprite.posy = init_pos_y2;

            castles[2].sprite.posx = screen_width;
            castles[3].sprite.posx = screen_width;
        }

        else if( num_castles == 3 ){
            castles[0].sprite.posx = init_pos_x1;
            castles[0].sprite.posy = init_pos_y1;

            castles[1].sprite.posx = init_pos_x2;
            castles[1].sprite.posy = init_pos_y2;

            castles[2].sprite.posx = init_pos_x3;
            castles[2].sprite.posy = init_pos_y2;
            castles[2].state = 1;

            castles[3].sprite.posx = screen_width;
        }
        else if( num_castles == 4 ){
            castles[0].sprite.posx = init_pos_x2;
            castles[0].sprite.posy = init_pos_y1;

            castles[1].sprite.posx = init_pos_x3;
            castles[1].sprite.posy = init_pos_y1;

            castles[2].sprite.posx = init_pos_x2;
            castles[2].sprite.posy = init_pos_y2;
            castles[2].state = 1;

            // castillo 4
            castles[3].sprite.posx = init_pos_x3;
            castles[3].sprite.posy = init_pos_y2;
            castles[3].state = 1;
        }}

        // actualizamos sus valores
        VDP_setSpriteP(castles[0].sprite_num, &castles[0].sprite);
        VDP_setSpriteP(castles[1].sprite_num, &castles[1].sprite);
        VDP_setSpriteP(castles[2].sprite_num, &castles[2].sprite);
        VDP_setSpriteP(castles[3].sprite_num, &castles[3].sprite);}
    }
*/

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// JUGADORES, valores iniciales, posiciones, paletas y sprites
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // valores iniciales comunes de todos los jugadores
    for( a = 0; a < max_num_players; a++){

        player[a].frame =  player[a].score = 0;
        player[a].state = state_stand;

        player[a].collision[0] = player[a].collision[1] = player[a].collision[2] = player[a].collision[3] = 0;

        player[a].fire_pressed = player[a].jump_pressed = 0;
        player[a].swim = 0;
        player[a].immunity = 1;
        player[a].score = 0;
        player[a].hp = 0;
        player[a].vel_x = player[a].vel_y = 0;

        player[a].x = FIX32(screen_width);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // POSICIONES iniciales de los jugadores
    // modos muertes o banderas
    if( mode == 1 || mode == 2 ){

        player[0].hp = 10;
        player[1].hp = 10;

        player[0].x = player[0].x_map = player[0].x_init = FIX32(init_pos_x2);
        player[0].y = player[0].y_map = player[0].y_init = FIX32(init_pos_y2);
        player[0].direction = 1;

        if( num_players == 2 ){

            player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x3);
            player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y2);
            player[1].direction = 3;

            player[2].x = FIX32(screen_width);
            player[3].x = FIX32(screen_width);
        }
        else if( num_players == 3 ){
            player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x3);
            player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y2);

            player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x1);
            player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y1);
            player[2].hp = 10;

            player[3].x = FIX32(screen_width);
        }
        else if( num_players == 4 ){
            player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x3);
            player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y2);

            player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x2);
            player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y1);
            player[2].hp = 10;

            player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x3);
            player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y1);
            player[3].hp = 10;
        }
    }
    // modo castillos
    else if( mode == 3 ){

        player[0].hp = 10;
        player[1].hp = 10;

        if( num_players == 2 ){
            // arriba centro
            player[0].x = player[0].x_map = player[0].x_init = FIX32(init_pos_x1);
            player[0].y = player[0].y_map = player[0].y_init = FIX32(init_pos_y1+24);

            // abajo centro
            player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x1);
            player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y2-24);

            player[2].x = FIX32(screen_width);
            player[3].x = FIX32(screen_width);
        }
        else if( num_players == 3 ){
            player[0].x = player[0].x_map = player[0].x_init = FIX32(init_pos_x1-24);
            player[0].y = player[0].y_map = player[0].y_init = FIX32(init_pos_y1);

            player[2].hp = 10;

            // jugador 2 mismo bando que el 1 -> dos castillos
            if( player[1].team == player[0].team ){
                player[1].x = player[0].x_map = player[0].x_init = FIX32(init_pos_x1+24);
                player[1].y = player[0].y_map = player[0].y_init = FIX32(init_pos_y1);

                player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x1);
                player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2-24);
            }
            // jugador 3 mismo bando que el 1 -> dos castillos
            else if( player[2].team == player[0].team ){
                player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x1+24);
                player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y1);

                player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x1);
                player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y2-24);
            }
            // jugador 3 mismo bando que el 2 -> dos castillos
            else if( num_castles == 2 ){
                player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x1-24);
                player[1].y = player[0].y_map = player[1].x_init = FIX32(init_pos_y2);

                player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x1+24);
                player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2);
            }
            // todos diferentes -> 3 castillos
            else if( num_castles == 3 ){
                player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x2+24);
                player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y2);

                player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x3-24);
                player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2);
            }

            player[3].x = FIX32(screen_width);
        }
        else if( num_players == 4 ){

            player[2].hp = 10;
            player[3].hp = 10;

            // dos castillos, arriba centro y abajo centro
            if( num_castles == 2 ){
                player[0].x = player[0].x_map = player[0].x_init = FIX32(init_pos_x1-24);
                player[0].y = player[0].y_map = player[0].y_init = FIX32(init_pos_y1);

                if( player[1].team == player[0].team ){
                    player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x1+24);
                    player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y1);

                    // abajo
                    player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x1-24);
                    player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2);

                    player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x1+24);
                    player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y2);
                }
                else{
                    player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x1-24);
                    player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y2);

                    if( player[2].team == player[0].team ){
                        player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x1+24);
                        player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y1);

                        player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x1+24);
                        player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y2);
                    }
                    else{
                        player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x1+24);
                        player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2);

                        player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x1+24);
                        player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y1);
                    }
                }
            }

             // 3 castillos, arriba centro y abajo esquinas
            if( num_castles == 3 ){
                player[0].x = player[0].x_map = player[0].x_init = FIX32(init_pos_x1-24);
                player[0].y = player[0].y_map = player[0].y_init = FIX32(init_pos_y1);

                // segundo jugador arriba y los otros dos abajo
                if( player[1].team == player[0].team ){
                    player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x1+24);
                    player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y1);

                    player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x2+24);
                    player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2);

                    player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x3-24);
                    player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y2);
                }
                else{
                    // segundo jugador abajo izquierda
                    player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x2+24);
                    player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y2);

                    // tercer jugador arriba y el cuarto abajo derecha
                    if( player[2].team == player[0].team ){
                        player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x1+24);
                        player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y1);

                        player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x3-24);
                        player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y2);
                    }
                    else{
                        // tercer jugador abajo izquierda y el cuarto abajo derecha
                        if( player[2].team == player[1].team ){
                            player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x2);
                            player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2-24);

                            player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x3-24);
                            player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y2);
                        }
                        else{
                            // tercer jugador abajo derecha
                            player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x3-24);
                            player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2);

                            // cuarto jugador arriba
                            if( player[3].team == player[0].team ){
                                player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x1+24);
                                player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y1);
                            }
                            // cuarto jugador abajo izquierda
                            else if( player[3].team == player[1].team ){
                                player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x2);
                                player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y2-24);
                            }
                            // cuarto jugador abajo derecha
                            else{
                                player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x3);
                                player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y2-24);
                            }
                        }
                    }
                }
            }

            // 4 castillos cada uno en una esquina
            else if( num_castles == 4 ){
                player[0].x = player[0].x_map = player[0].x_init = FIX32(init_pos_x2+24);
                player[0].y = player[0].y_map = player[0].y_init = FIX32(init_pos_y1);

                player[1].x = player[1].x_map = player[1].x_init = FIX32(init_pos_x3-24);
                player[1].y = player[1].y_map = player[1].y_init = FIX32(init_pos_y1);

                player[2].x = player[2].x_map = player[2].x_init = FIX32(init_pos_x2+24);
                player[2].y = player[2].y_map = player[2].y_init = FIX32(init_pos_y2);

                player[3].x = player[3].x_map = player[3].x_init = FIX32(init_pos_x3-24);
                player[3].y = player[3].y_map = player[3].y_init = FIX32(init_pos_y2);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // cambio los colores de la PALETA de los jugadores segun el equipo que toque y si hay mas de dos jugadores
    if( num_players > 2 ){

        if( num_players == 3 ){
            a = random()%5;
            while( a == player[0].team || a == player[1].team || a == player[2].team || a == 2)
                a = random()%5;

            player[3].team = a;
        }

        for( a = 0; a < max_num_players; a++ ){
            if( player[a].team ==  0){
                VDP_setPaletteColor(player_palette_pos1+player[a].character*2, dark_green);
                VDP_setPaletteColor(player_palette_pos2+player[a].character*2, soft_green);
            }
            else if( player[a].team ==  1){
                VDP_setPaletteColor(player_palette_pos1+player[a].character*2, dark_yellow);
                VDP_setPaletteColor(player_palette_pos2+player[a].character*2, soft_yellow);
            }
            else if( player[a].team ==  3){
                VDP_setPaletteColor(player_palette_pos1+player[a].character*2, dark_violet);
                VDP_setPaletteColor(player_palette_pos2+player[a].character*2, soft_violet);
            }
            else if( player[a].team ==  4){
                VDP_setPaletteColor(player_palette_pos1+player[a].character*2, dark_red);
                VDP_setPaletteColor(player_palette_pos2+player[a].character*2, soft_red);
            }
        }

        /////////////////////////////////////////////////////////////
        // BUG BUG BUG BUG BUG BUG BUG BUG BUG BUG BUG BUG BUG BUG
        {if( player[0].character == 3 ){
            if( player[0].team == 0){
                VDP_setPaletteColor(23, dark_green);
                VDP_setPaletteColor(24, soft_green);
            }
            else if( player[0].team ==  1){
                VDP_setPaletteColor(23, dark_yellow);
                VDP_setPaletteColor(24, soft_yellow);
            }
            else if( player[0].team ==  3){
                VDP_setPaletteColor(23, dark_violet);
                VDP_setPaletteColor(24, soft_violet);
            }
            else if( player[0].team ==  4){
                VDP_setPaletteColor(23, dark_red);
                VDP_setPaletteColor(24, soft_red);
            }
        }
        else if( player[1].character == 3 ){
            if( player[1].team == 0){
                VDP_setPaletteColor(23, dark_green);
                VDP_setPaletteColor(24, soft_green);
            }
            else if( player[1].team ==  1){
                VDP_setPaletteColor(23, dark_yellow);
                VDP_setPaletteColor(24, soft_yellow);
            }
            else if( player[1].team ==  3){
                VDP_setPaletteColor(23, dark_violet);
                VDP_setPaletteColor(24, soft_violet);
            }
            else if( player[1].team ==  4){
                VDP_setPaletteColor(23, dark_red);
                VDP_setPaletteColor(24, soft_red);
            }
        }
        else if( player[2].character == 3 ){
            if( player[2].team == 0){
                VDP_setPaletteColor(23, dark_green);
                VDP_setPaletteColor(24, soft_green);
            }
            else if( player[2].team ==  1){
                VDP_setPaletteColor(23, dark_yellow);
                VDP_setPaletteColor(24, soft_yellow);
            }
            else if( player[2].team ==  3){
                VDP_setPaletteColor(23, dark_violet);
                VDP_setPaletteColor(24, soft_violet);
            }
            else if( player[2].team ==  4){
                VDP_setPaletteColor(23, dark_red);
                VDP_setPaletteColor(24, soft_red);
            }
        }
        else if( player[3].character == 3 ){
            if( player[3].team == 0){
                VDP_setPaletteColor(23, dark_green);
                VDP_setPaletteColor(24, soft_green);
            }
            else if( player[3].team ==  1){
                VDP_setPaletteColor(23, dark_yellow);
                VDP_setPaletteColor(24, soft_yellow);
            }
            else if( player[3].team ==  3){
                VDP_setPaletteColor(23, dark_violet);
                VDP_setPaletteColor(24, soft_violet);
            }
            else if( player[3].team ==  4){
                VDP_setPaletteColor(23, dark_red);
                VDP_setPaletteColor(24, soft_red);
            }
        }}
    }
    else{
        // calculo los players 3 y 4 en modo de dos jugadores para no repetir colores en el hud
        a = random()%4;
        while( a == player[0].character || a == player[1].character )
            a = random()%4;

        player[2].character = a;

        a = random()%4;
        while( a == player[0].character || a == player[1].character || a == player[2].character)
            a = random()%4;

        player[3].character = a;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// defino los SPRITES de los jugadores

    // INDICES de los sprites
    player[0].sprite_num = player1_sprite;
    player[1].sprite_num = player2_sprite;
    player[2].sprite_num = player3_sprite;
    player[3].sprite_num = player4_sprite;

    // PERSONAJE 1
    player[0].sprite_head.posx = fix32ToInt(player[0].x)+1;
    player[0].sprite_head.posy = fix32ToInt(player[0].y)-pos_y_head;
    player[0].sprite_head.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[0].sprite_head.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, player[0].tile_pos+size_tiles_char); // paleta, prioridad, vflip, hflip, tile 1
    player[0].sprite_head.link  = player1_weapon_sprite;
    VDP_setSpriteP(player[0].sprite_num-2, &player[0].sprite_head);

    player[0].sprite_weapon.posx = fix32ToInt(player[0].x)+pos_x_weapon;
    player[0].sprite_weapon.posy = fix32ToInt(player[0].y)-pos_y_weapon;
    player[0].sprite_weapon.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[0].sprite_weapon.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, player[0].tile_pos+size_tiles_char*2); // paleta, prioridad, vflip, hflip, tile 1
    player[0].sprite_weapon.link  = player1_sprite;
    VDP_setSpriteP(player[0].sprite_num-1, &player[0].sprite_weapon);

    player[0].sprite.posx = fix32ToInt(player[0].x);
    player[0].sprite.posy = fix32ToInt(player[0].y);
    player[0].sprite.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[0].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, player[0].tile_pos+char_side_walk1); // paleta, prioridad, vflip, hflip, tile 1
    player[0].sprite.link  = player2_head_sprite;
    VDP_setSpriteP(player[0].sprite_num, &player[0].sprite);

    // PERSONAJE 2
    player[1].sprite_head.posx = fix32ToInt(player[1].x)+1;
    player[1].sprite_head.posy = fix32ToInt(player[1].y)-pos_y_head;
    player[1].sprite_head.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[1].sprite_head.tile_attr = TILE_ATTR_FULL(PAL1,0,0,1, player[1].tile_pos+size_tiles_char); // paleta, prioridad, vflip, hflip, tile 1
    player[1].sprite_head.link  = player2_weapon_sprite;
    VDP_setSpriteP(player[1].sprite_num-2, &player[1].sprite_head);

    player[1].sprite_weapon.posx = fix32ToInt(player[1].x)-pos_x_weapon;
    player[1].sprite_weapon.posy = fix32ToInt(player[1].y)-pos_y_weapon;
    player[1].sprite_weapon.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[1].sprite_weapon.tile_attr = TILE_ATTR_FULL(PAL1,0,0,1, player[1].tile_pos+size_tiles_char*2); // paleta, prioridad, vflip, hflip, tile 1
    player[1].sprite_weapon.link  = player2_sprite;
    VDP_setSpriteP(player[1].sprite_num-1, &player[1].sprite_weapon);

    player[1].sprite.posx = fix32ToInt(player[1].x);
    player[1].sprite.posy = fix32ToInt(player[1].y);
    player[1].sprite.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[1].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,1, player[1].tile_pos+char_side_walk1); // paleta, prioridad, vflip, hflip, tile 1
    player[1].sprite.link  = player3_head_sprite;
    VDP_setSpriteP(player[1].sprite_num, &player[1].sprite);

    // PERSONAJE 3
    player[2].sprite_head.posx = fix32ToInt(player[2].x)+1;
    player[2].sprite_head.posy = fix32ToInt(player[2].y)-pos_y_head;
    player[2].sprite_head.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[2].sprite_head.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, player[2].tile_pos+size_tiles_char); // paleta, prioridad, vflip, hflip, tile 1
    player[2].sprite_head.link  = player3_weapon_sprite;
    VDP_setSpriteP(player[2].sprite_num-2, &player[2].sprite_head);

    player[2].sprite_weapon.posx = fix32ToInt(player[2].x)+pos_x_weapon;
    player[2].sprite_weapon.posy = fix32ToInt(player[2].y)-pos_y_weapon;
    player[2].sprite_weapon.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[2].sprite_weapon.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, player[2].tile_pos+size_tiles_char*2); // paleta, prioridad, vflip, hflip, tile 1
    player[2].sprite_weapon.link  = player3_sprite;
    VDP_setSpriteP(player[2].sprite_num-1, &player[2].sprite_weapon);

    player[2].sprite.posx = fix32ToInt(player[2].x);
    player[2].sprite.posy = fix32ToInt(player[2].y);
    player[2].sprite.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[2].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, player[2].tile_pos+char_side_walk1); // paleta, prioridad, vflip, hflip, tile 1
    player[2].sprite.link  = player4_head_sprite;
    VDP_setSpriteP(player[2].sprite_num, &player[2].sprite);

    // PERSONAJE 4
    player[3].sprite_head.posx = fix32ToInt(player[3].x)+1;
    player[3].sprite_head.posy = fix32ToInt(player[3].y)-pos_y_head;
    player[3].sprite_head.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[3].sprite_head.tile_attr = TILE_ATTR_FULL(PAL1,0,0,1, player[3].tile_pos+size_tiles_char); // paleta, prioridad, vflip, hflip, tile 1
    player[3].sprite_head.link  = player4_weapon_sprite;
    VDP_setSpriteP(player[3].sprite_num-2, &player[3].sprite_head);

    //player[3].sprite_weapon.posx = fix32ToInt(player[3].x)-pos_x_weapon;
    player[3].sprite_weapon.posy = fix32ToInt(player[3].y)-pos_y_weapon;
    player[3].sprite_weapon.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[3].sprite_weapon.tile_attr = TILE_ATTR_FULL(PAL1,0,0,1, player[3].tile_pos+size_tiles_char*2); // paleta, prioridad, vflip, hflip, tile 1
    player[3].sprite_weapon.link  = player4_sprite;
    VDP_setSpriteP(player[3].sprite_num-1, &player[3].sprite_weapon);

    player[3].sprite.posx = fix32ToInt(player[3].x);
    player[3].sprite.posy = fix32ToInt(player[3].y);
    player[3].sprite.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
    player[3].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,1, player[3].tile_pos+char_side_walk1); // paleta, prioridad, vflip, hflip, tile 1
    player[3].sprite.link  = shot_player_sprite;
    VDP_setSpriteP(player[3].sprite_num, &player[3].sprite);}}


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// DISPAROS de los jugadores, valores iniciales, posiciones, paletas y sprites
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // valores iniciales comunes de todos los jugadores
    for( b = 0; b < max_num_players; b++){
        for( a = 0; a < max_num_player_shots; a++){
            playerShot[b][a].x = FIX32(screen_width);
            playerShot[b][a].y = FIX32(0);
            playerShot[b][a].state = state_shot_inactive;
            playerShot[b][a].direction = 0;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// defino los SPRITES de los disparos

    // INDICES de los sprites
    for( b = 0; b < max_num_players; b++){
        for( a = 0; a < max_num_player_shots; a++){
            playerShot[b][a].sprite_num = shot_player_sprite+max_num_player_shots*b+a;
        }

        for( a = 0; a < max_num_player_shots; a++){
            playerShot[b][a].sprite.posx = fix32ToInt(playerShot[b][a].x);
            playerShot[b][a].sprite.posy = fix32ToInt(playerShot[b][a].y);
            playerShot[b][a].sprite.size = SPRITE_SIZE(shot_chars_tile_size_x, shot_chars_tile_size_y);
            playerShot[b][a].sprite.tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, weaponTilePos); // paleta, prioridad, vflip, hflip, tile 1
            if( a < max_num_player_shots-1 )
                playerShot[b][a].sprite.link  = playerShot[b][a+1].sprite_num;
            else
                playerShot[b][a].sprite.link  = playerShot[b][a-1].sprite_num+2;
            VDP_setSpriteP(playerShot[b][a].sprite_num, &playerShot[b][a].sprite);
        }
    }}}








    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// ENEMIGOS, valores iniciales, posiciones, paletas y sprites
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // valores iniciales comunes de todos los enemigos
    for( a = 0; a < max_num_enemies; a++){
        enemies[a].x = FIX32(screen_width);
        enemies[a].y = FIX32(0);
        enemies[a].state = state_enemy_inactive;
        enemies[a].direction = 0;
        enemies[a].vel_x = enemies[a].vel_y = 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// defino los SPRITES de los enemigos
    for( a = 0; a < max_num_enemies; a++){
        enemies[a].sprite.posx = fix32ToInt(enemies[a].x);
        enemies[a].sprite.posy = fix32ToInt(enemies[a].y);
        enemies[a].sprite.size = SPRITE_SIZE(chars_tile_size_x,chars_tile_size_y);
        enemies[a].sprite.tile_attr = TILE_ATTR_FULL(PAL0,0,0,0, enemiesTilePos); // paleta, prioridad, vflip, hflip, tile 1
        if( a < max_num_enemies-1 )
            enemies[a].sprite.link  = enemies_sprite+a+1;
        else
            enemies[a].sprite.link  = 0;
        VDP_setSpriteP(enemies_sprite+a, &enemies[a].sprite);
    }}}


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// CARGA Y DIBUJADO DEL HUD (PAL 0)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    VDP_loadTileData( tiles_font1, pos_vram_font, tiles_font1_size, 1);

    VDP_drawTextBG( APLAN, " P1 00000", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 0, 27);
    //VDP_drawTextBG( APLAN, " P1 00000  P2 00000  P3 00000  P4 00000", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 0, 27);

     // dibujo el fondo de los marcadores del color que toca
    if( player[0].character == 0 )
        VDP_drawTextBG( BPLAN, "$$$$$$$$$$", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 0, 27);
    else if( player[0].character == 1 )
        VDP_drawTextBG( BPLAN, "%%%%%%%%%%", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 0, 27);
    else if( player[0].character == 2 )
        VDP_drawTextBG( BPLAN, "&&&&&&&&&&", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 0, 27);
    else if( player[0].character == 3 )
        VDP_drawTextBG( BPLAN, "''''''''''", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 0, 27);

    VDP_drawTextBG( APLAN, "P2 00000", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 11, 27);

    if( player[1].character == 0 )
        VDP_drawTextBG( BPLAN, "$$$$$$$$$$", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 10, 27);
    else if( player[1].character == 1 )
        VDP_drawTextBG( BPLAN, "%%%%%%%%%%", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 10, 27);
    else if( player[1].character == 2 )
        VDP_drawTextBG( BPLAN, "&&&&&&&&&&", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 10, 27);
    else if( player[1].character == 3 )
        VDP_drawTextBG( BPLAN, "''''''''''", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 10, 27);

    VDP_drawTextBG( APLAN, "P3 00000", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 21, 27);

    if( player[2].character == 0 )
        VDP_drawTextBG( BPLAN, "$$$$$$$$$$", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 20, 27);
    else if( player[2].character == 1 )
        VDP_drawTextBG( BPLAN, "%%%%%%%%%%", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 20, 27);
    else if( player[2].character == 2 )
        VDP_drawTextBG( BPLAN, "&&&&&&&&&&", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 20, 27);
    else if( player[2].character == 3 )
        VDP_drawTextBG( BPLAN, "''''''''''", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 20, 27);

    VDP_drawTextBG( APLAN, "P4 00000", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 31, 27);

    if( player[3].character == 0 )
        VDP_drawTextBG( BPLAN, "$$$$$$$$$$", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 30, 27);
    else if( player[3].character == 1 )
        VDP_drawTextBG( BPLAN, "%%%%%%%%%%", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 30, 27);
    else if( player[3].character == 2 )
        VDP_drawTextBG( BPLAN, "&&&&&&&&&&", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 30, 27);
    else if( player[3].character == 3 )
        VDP_drawTextBG( BPLAN, "''''''''''", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 30, 27);

    // tiempo
    VDP_drawTextBG( BPLAN, "      ", TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 17, 0);

    if( *mins == 3 )
        VDP_drawTextBG( APLAN, " 3:00 ", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 17, 0);
    else if( *mins == 5 )
        VDP_drawTextBG( APLAN, " 5:00 ", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 17, 0);
    else if( *mins == 10 )
        VDP_drawTextBG( APLAN, "10:00 ", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 17, 0);}


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // SONIDO
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Z80_init();
    //SND_startPlay_TFM(db_03);


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    {// CARTEL DE SALIDA  (3,2,1 GO!)
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // SPRITES del cartel
    {sprite_menu[0].posx = 144;
    sprite_menu[0].posy = 88;
    sprite_menu[0].size = SPRITE_SIZE(4,4);
    sprite_menu[0].tile_attr = TILE_ATTR_FULL(PAL1,1,0,0, enemiesTilePos+size_tiles_char*7); // paleta, prioridad, vflip, hflip, tile 1
    sprite_menu[0].link  = billboard2_sprite;
    VDP_setSpriteP(billboard1_sprite, &sprite_menu[0]);

    sprite_menu[1].posx = screen_width;
    sprite_menu[1].posy = 88;
    sprite_menu[1].size = SPRITE_SIZE(4,4);
    sprite_menu[1].tile_attr = TILE_ATTR_FULL(PAL1,0,0,0, enemiesTilePos+size_tiles_char*7+32); // paleta, prioridad, vflip, hflip, tile 1
    sprite_menu[1].link  = billboard2_sprite+1;
    VDP_setSpriteP(billboard2_sprite, &sprite_menu[1]);

    VDP_updateSprites();}

    SND_startPlay_VGM(bgm03);

    psgFxPlay(CONFIRM_SFX);
    waitTick(TICKPERSECOND * 1);

    VDP_loadTileData( tiles_number2, enemiesTilePos+size_tiles_char*7, tiles_billboard_size, 0);
    psgFxPlay(CONFIRM_SFX);
    waitTick(TICKPERSECOND * 1);

    VDP_loadTileData( tiles_number1, enemiesTilePos+size_tiles_char*7, tiles_billboard_size, 0);
    psgFxPlay(CONFIRM_SFX);
    waitTick(TICKPERSECOND * 1);

    VDP_loadTileData( tiles_GO1, enemiesTilePos+size_tiles_char*7, tiles_billboard_size, 0);
    psgFxPlay(START_SFX);

    a = b = 0;
    while( b < 60 ){

        if( a == 0 ){
            sprite_menu[0].posx = 128;
            sprite_menu[1].posx = 160;
            VDP_setSpriteP(billboard1_sprite, &sprite_menu[0]);
            VDP_setSpriteP(billboard2_sprite, &sprite_menu[1]);
            VDP_updateSprites();
        }
        else if( a == 10 ){
            sprite_menu[0].posx = screen_width;
            sprite_menu[1].posx = screen_width;
            VDP_setSpriteP(billboard1_sprite, &sprite_menu[0]);
            VDP_setSpriteP(billboard2_sprite, &sprite_menu[1]);
            VDP_updateSprites();
        }

        a++;
        b++;
        a%=20;

        VDP_waitVSync();
    }}
}

