#define BOMB_TIMEOUT        35+1
#define BOMB_SPRITE_POS      3

#define BOMB_EXPLOSION_TIMEOUT     40+1
#define BOMB_EXPLOSION_SPRITE_POS   4

#define BOMB_EXPLOSION_RANGE       22


typedef struct
{
   u16   sprite;
   u16   timeout;

   s16  x;
   s16  y;

   bool active;
}
tBomb;

void bomb_new ( s16 x, s16 y );
void bomb_update ( );
