#ifndef _TILES_SIN_COMPRIMIR_H
#define _TILES_SIN_COMPRIMIR_H

#define tam_h_tiles                          40
#define tam_v_tiles                          28


#define pos_vram_font           1312
#define pos_vram_tiles_text     25

#define tiles_font_credits_size              96
#define tiles_font1_size                     64
#define tiles_1985_logo_size                 117
#define tiles_intro_1_size                   432
#define tiles_intro_2_size                   358
#define tiles_intro_3_size                   284
#define tiles_intro_4_size                   385
#define tiles_intro_5_size                   530
#define tiles_records_title_size             23
#define tiles_records_text_size              192
#define tiles_logo_title_size                214
#define tiles_back_title_size                6
#define tiles_back_menu_size                 44
#define tiles_billboard_size                 16
#define tiles_bg_01_size                     665
#define tiles_bg_01_01_size                  26

#define map_1985_logo_x_size                 16
#define map_1985_logo_y_size                 10
#define map_logo_title_x_size                22
#define map_logo_title_y_size                15
#define map_back_title_x_size                40
#define map_back_title_y_size                28
#define map_back_menu_x_size                 64
#define map_back_menu_y_size                 64

// fuentes
extern const u16 pal_font_credits[16];
extern const u32 tiles_font_credits[tiles_font_credits_size*8];

extern const u16 pal_font_title[16];
extern const u16 pal_font1[16];
extern const u32 tiles_font1[tiles_font1_size*8];

// 1985 logo
extern const u16 pal_1985_logo[16];
extern const u16 map_1985_logo[map_1985_logo_x_size*map_1985_logo_y_size];
extern const u32 tiles_1985_logo[tiles_1985_logo_size * 8];

// intro
extern const u16 pal_intro_1[16];
extern const u16 map_intro_1[tam_h_tiles*tam_v_tiles];
extern const u32 tiles_intro_1[tiles_intro_1_size * 8];

extern const u16 pal_intro_2[16];
extern const u16 map_intro_2[tam_h_tiles*tam_v_tiles];
extern const u32 tiles_intro_2[tiles_intro_2_size * 8];

extern const u16 pal_intro_3[16];
extern const u16 map_intro_3[tam_h_tiles*tam_v_tiles];
extern const u32 tiles_intro_3[tiles_intro_3_size * 8];

extern const u16 pal_intro_4[16];
extern const u16 map_intro_4[tam_h_tiles*tam_v_tiles];
extern const u32 tiles_intro_4[tiles_intro_4_size * 8];

extern const u16 pal_intro_5[16];
extern const u16 map_intro_5[tam_h_tiles*tam_v_tiles];
extern const u32 tiles_intro_5[tiles_intro_5_size * 8];

// records
extern const u16 pal_records_title[16];
extern const u32 tiles_records_title[tiles_records_title_size * 8];

extern const u16 pal_records_text[16];
extern const u32 tiles_records_text[tiles_records_text_size * 8];

// titulo
extern const u16 pal_logo_title[16];
extern const u16 map_logo_title[map_logo_title_x_size*map_logo_title_y_size];
extern const u32 tiles_logo_title[tiles_logo_title_size*8];

extern const u16 pal_back_title[16];
extern const u16 map_back_title[map_back_title_x_size*map_back_title_y_size];
extern const u32 tiles_back_title[tiles_back_title_size * 8];

// menu
extern const u16 pal_back_menu[16];
extern const u16 map_back_menu[map_back_menu_x_size*map_back_menu_y_size];
extern const u32 tiles_back_menu[tiles_back_menu_size * 8];

extern const u16 pal_sprite_menu[16];
extern const u32 tiles_sprite_menu[16 * 8];


// carteles
extern const u32 tiles_number3[tiles_billboard_size*8];
extern const u32 tiles_number2[tiles_billboard_size*8];
extern const u32 tiles_number1[tiles_billboard_size*8];
extern const u32 tiles_GO1[tiles_billboard_size*8];
extern const u32 tiles_GO2[tiles_billboard_size*8];
extern const u32 tiles_TIMEUP1[tiles_billboard_size*8];
extern const u32 tiles_TIMEUP2[tiles_billboard_size*8];


// escenarios
extern const u16 pal_bg_01[16];
extern const u16 map_bg_01[tam_h_tiles*(tam_v_tiles-1)];
extern const u32 tiles_bg_01[tiles_bg_01_size*8];

extern const u16 pal_bg_01_01[16];
extern const u16 map_bg_01_01[tam_h_tiles*(tam_v_tiles-1)];
extern const u32 tiles_bg_01_01[tiles_bg_01_01_size*8];


// personajes
extern const u16 pal_chars01[16];
extern const u32 tiles_chars01[4][4][4*8];
extern const u32 tiles_heads[4][4][4*8];

extern const u32 tiles_weapons[4][32];
extern const u32 tiles_bullets[4*8];

extern const u32 tiles_death[5][4*4*8];


// enemigos
extern const u16 pal_enemies01[16];
extern const u32 tiles_enemies01[28*8];


// extras
extern const u32 tiles_flags[4][4*8];
extern const u32 tiles_towers[16*8];





#endif
