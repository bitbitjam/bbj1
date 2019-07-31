#ifndef _INTRO_H_
#define _INTRO_H_

#define pos_vram_font_intro     1280
#define logo1985_tiles_size     117

// intro
#define delayBetweenMessages    90
#define num_screens_intro       8
#define num_strings_intro       22

#define pos_x_strg1     7
#define pos_y_strg1     23

#define pos_x_strg2     7
#define pos_y_strg2     21
#define pos_x_strg3     7
#define pos_y_strg3     23
#define pos_x_strg4     9
#define pos_y_strg4     25

#define pos_x_strg5     9
#define pos_y_strg5     21
#define pos_x_strg6     9
#define pos_y_strg6     23
#define pos_x_strg7     9
#define pos_y_strg7     25

#define pos_x_strg8     9
#define pos_y_strg8     21
#define pos_x_strg9     9
#define pos_y_strg9     23
#define pos_x_strg10    5
#define pos_y_strg10    25

#define pos_x_strg11    5
#define pos_y_strg11    21
#define pos_x_strg12    9
#define pos_y_strg12    23
#define pos_x_strg13    13
#define pos_y_strg13    25

#define pos_x_strg14    8
#define pos_y_strg14    21
#define pos_x_strg15    6
#define pos_y_strg15    23
#define pos_x_strg16    6
#define pos_y_strg16    25

#define pos_x_strg17    8
#define pos_y_strg17    21
#define pos_x_strg18    9
#define pos_y_strg18    23
#define pos_x_strg19    11
#define pos_y_strg19    25

#define pos_x_strg20    5
#define pos_y_strg20    21
#define pos_x_strg21    6
#define pos_y_strg21    23
#define pos_x_strg22    5
#define pos_y_strg22    25

typedef struct
{
	u16  *map;
	u32  *data;
	u16  *pal;
	u16  size;
}
INTRO;

u8 introControl();

void creditsScreen();
void draw1985Logo();
u8 titleScreen();
void recordsScreen();

#endif
