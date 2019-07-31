#define EXPLOSION_TERRAIN_MAX        10
#define EXPLOSION_TERRAIN_SPRITE_IND  2
#define EXPLOSION_TERRAIN_SPRITE_POS  2
#define EXPLOSION_TERRAIN_COUNTER    25


typedef struct
{
   u16 sprite;
   u16 timeout;
}
tExpTerrains;



void explosion_terrain_new    ( u16 x, u16 y );
void explosion_terrain_delete ( u16 i );
void explosion_terrain_update ( );
void explosion_reset_all      ( );
