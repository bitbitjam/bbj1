
#define FREEZE_TIME 100


typedef enum { DIRECTION_NONE, DIRECTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT } tDirection;



typedef struct
{
   u16 sprite;

   s16 x;
   s16 y;

   s16 x_pixels;
   s16 y_pixels;

   tDirection direction;
   s8 move_cnt;
   u16 vel;

   u16 timeout_free;
}
tPlayer;


tPlayer players [ 2 ];



Sprite sprites[MAX_SPRITE];



void freeze_player ( u16 i );
void handle_joy ( );
void sprite_init ( );
void update_scroll ();
s16  check_item ();
int  main ();
