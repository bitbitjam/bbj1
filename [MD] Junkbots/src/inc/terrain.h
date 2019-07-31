#define TERRAIN_MAX_BLOCKS 15
#define TERRAIN_MIN_BLOCKS 6

#define TERRAIN_MAX_HEIGHT 14
#define TERRAIN_MAX_WIDTH  20

#define BT_NONE   { SOFT,   0,  0,  0,  0, false }
#define BT_HIDDEN { SOLID,  0,  0,  0,  0, false }
#define BT_FLOOR  { SOLID,  1,  2,  3,  4, false }
#define BT_SOFT   { SOFT,   5,  6,  7,  8, true  }
#define BT_ROCK   { SOLID,  9, 10, 11, 12, false }





typedef enum { SOFT, SOLID } tBlocktype;


typedef struct
{
   tBlocktype bt;
   u16         tile1;
   u16         tile2;
   u16         tile3;
   u16         tile4;
   bool       is_diggable;
}
tBigtile;

tBigtile   terrain [ 30 ] [ 20 ];
Vect2D_u16 item;


void bigtile_draw ( tBigtile bt, u16 x, u16 y );
bool terrain_can_remove ( u16 x, u16 y );
void terrain_remove ( u16 x, u16 y );
void terrain_draw ();
void terrain_draw_blocks ();
void terrain_hidde_item ();
