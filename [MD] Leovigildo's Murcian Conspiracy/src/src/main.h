#ifndef _MAIN_H_
#define _MAIN_H_

/////////////////////////
// libreria
#include "genesis.h"

/////////////////////////
// includes del juego
#include "lib_support.h"
#include "uncompressed_gfx.h"
#include "init_game.h"
#include "players_control.h"
#include "shots_control.h"
#include "flags_control.h"
#include "credits_logo_intro_title_records_control.h"
#include "sram_control.h"
#include "psgplayer.h"
#include "time_control.h"
#include "enemies_control.h"

/////////////////////////
// musicas
#include "bgm00.h"
#include "bgm01.h"
#include "bgm03.h"

/////////////////////////
// defines
//#define ver             "B.7/06/14"
#define ver             "B.8/6/14"

// tamaño de la cadena para los nombres de la pantalla de records
#define GD_MAX_NAME_LEN        10

// tamaño pantalla
#define screen_width            320
#define screen_height           224
#define screen_width_tiles      screen_width/8
#define tam_map_h_tiles         40
#define tam_map_v_tiles         27
#define tam_map_tiles           tam_map_h_tiles*tam_map_v_tiles


// tamaños tiles
#define size_tiles_char          4
#define size_tiles_char_shots    11
#define size_tiles_charset       23*size_tiles_char
#define chars_tile_size_x        2
#define chars_tile_size_y        2
#define shot_chars_tile_size_x   1
#define shot_chars_tile_size_y   1

// posicion jugadores en paleta
#define player_palette_pos1     17
#define player_palette_pos2     18
#define menu_palette_pos1       33
#define menu_palette_pos2       34

// tipos de tiles
#define forest_tile             7
#define ice_tile                8
#define water_tile              9
#define home_tile               10
#define destructible_tile1A     14
#define destructible_tile1B     15
#define indestructible_tile     16

// numero de los sprites
#define billboard1_sprite       0
#define billboard2_sprite       1

#define player1_head_sprite     2
#define player1_weapon_sprite   3
#define player1_sprite          4

#define player2_head_sprite     5
#define player2_weapon_sprite   6
#define player2_sprite          7

#define player3_head_sprite     8
#define player3_weapon_sprite   9
#define player3_sprite          10

#define player4_head_sprite     11
#define player4_weapon_sprite   12
#define player4_sprite          13

#define shot_player_sprite      14
#define enemies_sprite          54
//#define flag_sprite             14



// posiciones iniciales
#define init_pos_x1     152
#define init_pos_x2     8
#define init_pos_x3     296

#define init_pos_y1     8
#define init_pos_y2     192

#define  pos_y_head            10
#define  pos_y_weapon          2
#define  pos_x_weapon          14

// topes de desplazamiento del jugador
#define screen_top_right        305
#define screen_top_left         0
#define screen_top_up           0
#define screen_top_down         200

// posicion de los frames del jugador
#define char_side_walk1        0
#define char_side_walk2        1
#define char_side_walk3        2
#define char_side_walk4        3


#define char_down_swim1        9
#define char_down_swim2        10
#define char_down_swim3        11
#define char_up_swim1          12
#define char_up_swim2          13
#define char_up_swim3          14
#define char_up_swim4          14
#define char_side_swim1        15
#define char_side_swim2        16
#define char_side_swim3        17
#define char_side_swim4        17
#define char_down_shot         18
#define char_up_shot           19
#define char_side_shot         20
#define char_dead1             21
#define char_dead2             22

// velocidad de la animacion del jugador
#define  vel_anim1             1
#define  vel_anim2             9
#define  vel_anim3             17
#define  vel_anim4             25
#define  vel_anim5             33
#define  vel_anim6             41
#define  vel_anim_menu1        12
#define  vel_anim_menu2        24
#define  vel_anim_menu3        36
#define  vel_anim_menu4        48

// velocidad de movimiento
#define  player_speed          1.2
#define  enemy_speed           0.6
#define  gravity_speed         FIX32(0.3)
#define  jump_speed            FIX32(5.2)
#define  player_slow_speed     player_speed/2
#define  player_fast_speed     player_speed*2
#define  shot_speed            FIX32(3.2)
#define  shot_despx            13
#define  shot_despy            -1
#define  shot_frame1           4
#define  shot_frame2           8



// colisiones del jugador
#define char_collision_left     1
#define char_collision_mid_hor  8
#define char_collision_right    15
#define char_collision_up       1
#define char_collision_mid_ver  8
#define char_collision_down     15

// estados del jugador
#define state_stand             0
#define state_walk_up           1
#define state_walk_right        2
#define state_walk_down         3
#define state_walk_left         4
#define state_dead              5
#define state_shot              6
#define state_jump              7

#define immunity_duration       180

// estados de los disparos
#define state_shot_inactive     0
#define state_shot_active       1
#define state_shot_collision    2
#define state_shot_anim1        5
#define state_shot_anim2        10
#define state_shot_end          15

// estados de los enemigos
#define state_enemy_inactive    0
#define state_enemy_active      1
#define state_enemy_dead        2

// numero maximo de jugadores, disparos, enemigos...
#define max_num_players         4
#define max_num_player_shots    10
#define max_num_flags           4
#define max_num_enemies         20

// colisiones de los disparos
#define shot_collision_left     0
#define shot_collision_right    8
#define shot_collision_up       0
#define shot_collision_down     8

// duracion del retardo del disparo y sus animaciones
#define shot_delay              20
#define vel_anim_shot1          1
#define vel_anim_shot2          4
#define vel_anim_shot3          6



// colores de la paleta de los jugadores para hacer cambios
#define dark_green              0x0286
#define soft_green              0x02CA

#define dark_yellow             0x00AE
#define soft_yellow             0x04EE

#define dark_violet             0x0866
#define soft_violet             0x0E88

#define dark_red                0x0008
#define soft_red                0x000E

#define dark_grey               0x0666
#define soft_grey               0x0AAA


//////////////////////////////////////////
//////////////////////////////////////////
// structs
//////////////////////////////////////////
//////////////////////////////////////////
// jugador
typedef struct{
    fix32 x;			    // posicion x
	fix32 y;			    // y

	fix32 x_map;			// posicion x en el mapa
	fix32 y_map;			// y

	fix32 x_init;			// posicion x inicial
	fix32 y_init;			// y

	fix32 vel_x, vel_y;     // para salto y correcion del salto

	u32 score;              // puntuacion

	u8 character;           // personaje del jugador
	u8 team;                // equipo del personaje (para el multiplayer)

    u8 direction;           // direccion a la que mira el personaje
	u8 frame;               // frame de la animacion

	u8 collision[4];        // 3 puntos de colision pq el tile puede ser mas pequeño que la distancia entre 2 puntos y necesito uno central
                            // el 4 es el punto central del sprite para dibujarlo nadando

    u16 hp;                 // vida restante

	u8 state;               // estados del jugador
	u8 fire_pressed;        // para evitar el disparo continuo
	u8 jump_pressed;        // para evitar el salto continuo

	u8 swim;                // para nadar
	u8 immunity;            // inmunidad

	// sprite
	u8 sprite_num;          // numero del sprite
    SpriteDef sprite;       // sprite del cuerpo
    SpriteDef sprite_head;  // sprite de la cabeza
    SpriteDef sprite_weapon;// sprite del arma

    u16 tile_pos;           // posicion en vram de sus tiles

}player_struct;

///////////////////////////
// enemigos
typedef struct{
    fix32 x;			    // posicion x
	fix32 y;			    // y

	fix32 x_map;			// posicion x en el mapa
	fix32 y_map;			// y

	fix32 vel_x, vel_y;     // para salto y correcion del salto

    u8 direction;           // direccion a la que mira el personaje
	u8 frame;               // frame de la animacion

	u8 collision[4];        // 3 puntos de colision pq el tile puede ser mas pequeño que la distancia entre 2 puntos y necesito uno central
                            // el 4 es el punto central del sprite para dibujarlo nadando
    u16 hp;                 // vida restante

	u8 state;               // estados del jugador

	// sprite
	SpriteDef sprite;

}enemy_struct;


///////////////////////////
// disparo
typedef struct{
    fix32 x, y;			    // posicion x, y

	u8 state;               // estado de la bola
	u8 direction;           // direccion del disparo

	// sprite
	u8 sprite_num;          // numero del sprite
    SpriteDef sprite;       // sprite
    u16 tile_pos;           // posicion en vram de sus tiles

}shot_struct;


///////////////////////////
// banderas
typedef struct{
    u16 x;
    u8 y;			    // posicion x, y

    u8 state;
    u8 step;

    // sprite
	u8 sprite_num;          // numero del sprite
    SpriteDef sprite;       // sprite
    u16 tile_pos;           // posicion en vram de sus tiles

}flag_struct;

//////////////////////////////////////////////////////
// Game data struct, arranged like this:
//
//   0    1    2    3    4   5       14  15
//  ______________________________//_________
// |    |    |    |    |    |           |    |
// | ID |    SCORE     | ST |    NAME   | CS |
// |____|____|____|____|____|____//_____|____|
//
//////////////////////////////////////////////////////
typedef union{

    u8 data[16];                        // Raw data
    struct{
        u8 id;                          // Game ID
        u8 score[3];                    // Score (24 bits)
        u8 st;                          // Stage
        char name[GD_MAX_NAME_LEN];     // Player name
        u8 cs;                          // Checksum
    };
}game_data;


//////////////////////////////////////////////////////
// logros
//////////////////////////////////////////////////////
typedef union{

    u32 achievements;
    struct{

        u8 achiev1:1;
        u8 achiev2:1;
        u8 achiev3:1;
        u8 achiev4:1;
        u8 achiev5:1;
        u8 achiev6:1;
        u8 achiev7:1;
        u8 achiev8:1;
        u8 achiev9:1;
        u8 achiev10:1;
        u8 achiev11:1;
        u8 achiev12:1;
        u8 achiev13:1;
        u8 achiev14:1;
        u8 achiev15:1;
        u8 achiev16:1;
        u8 achiev17:1;
        u8 achiev18:1;
        u8 achiev19:1;
        u8 achiev20:1;
        u8 achiev21:1;
        u8 achiev22:1;
        u8 achiev23:1;
        u8 achiev24:1;
        u8 achiev25:1;
        u8 achiev26:1;
        u8 achiev27:1;
        u8 achiev28:1;
        u8 achiev29:1;
        u8 achiev30:1;
        u8 achiev31:1;
        u8 achiev32:1;
    };
}achievData;

//////////////////////////////////////////
//////////////////////////////////////////
// globales
//////////////////////////////////////////
//////////////////////////////////////////
u16 map_temp[40*27];

player_struct       player[max_num_players];
shot_struct         playerShot[max_num_players][max_num_player_shots];
enemy_struct        enemies[max_num_enemies];

u16                 weaponTilePos;
u16                 enemiesTilePos;
flag_struct         flags[max_num_flags];
flag_struct         castles[max_num_players];


SpriteDef sprite_menu[50];      // sprite de fondo del menu
SpriteDef sprite_cursor;


//  para el efecto de scroll por persiana de Doragasu
u16 vscroll_a;
u8 start_line;

// puntuacion
u32 pointsTable[10];
char namesTable[10][12];
u8 stagesTable[10];

// Datos de logros
achievData ad;

u16 comp60hz;

#endif
