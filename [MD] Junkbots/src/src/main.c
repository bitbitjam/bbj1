#include "../inc/include.h"


static Vect2D_u16 player_positions[2] = { {4,2}, {19,2} };


tPlayer players[2] =
{
   { 0, 4, 2, 0, 0, DIRECTION_NONE, MAX_CNT, VEL_INC, 0 },
   { 0,15, 2, 0, 0, DIRECTION_NONE, MAX_CNT, VEL_INC, 0 }
} ;





static u32 _counter = 0;
static u16 yscroll = 0;
static u16 xscroll_b[28] = {};
static u16 oldButtons = 0xffff, pressedButtons; // borrowed from Artemio Urbina

Sprite sprites[MAX_SPRITE];




void draw_int ( s32 value, u16 x, u16 y, u16 min )
{
   u8 str[40];
   intToStr ( value, str, min );
   VDP_drawText ( str, x, y );
}

void draw_uint ( u32 value, u16 x, u16 y, u16 min )
{
   u8 str[40];
   uintToStr ( value, str, min );
   VDP_drawText ( str, x, y );
}


void freeze_player ( u16 i )
{
   if ( players[i].timeout_free == 0 )
   {
      players[i].timeout_free = FREEZE_TIME;
   }
}


void freeze_update ( )
{
   u16 i;

   for ( i=0; i<2; i++ )
   {
      if ( players[i].timeout_free > 0 )
      {
         -- players[i].timeout_free;
      }
   }
}


void handle_joy ( )
{
   u16 i;

   for ( i=0; i<2; i++ )
   {
      tPlayer *p = &players[i];

      if ( p->direction != DIRECTION_NONE )
      {
         continue;
      }

      if ( p->timeout_free >0 )
      {
         continue;
      }

      u16 value = JOY_readJoypad(i);
      pressedButtons = value & ~oldButtons;
      oldButtons = value;


      if ( value & BUTTON_UP  &&  p->y > 0 && terrain_can_remove ( p->x, p->y - 1 ) )
      {
         p->y -= 1;
         p->direction = DIRECTION_UP;
         p->move_cnt =  MAX_CNT;
      }
      else if ( value & BUTTON_DOWN  && p->y < TERRAIN_MAX_HEIGHT-1  &&  terrain_can_remove ( p->x, p->y + 1 ) )
      {
         p->y += 1;
         p->direction = DIRECTION_DOWN;
         p->move_cnt =  MAX_CNT;
      }
      else if ( value & BUTTON_LEFT  && p->x > 0  &&  terrain_can_remove ( p->x - 1, p->y ) )
      {
         p->x -= 1;
         p->direction = DIRECTION_LEFT;
         p->move_cnt =  MAX_CNT;
      }
      else if ( value & BUTTON_RIGHT && p->x < TERRAIN_MAX_WIDTH-1  &&  terrain_can_remove ( p->x + 1, p->y ) )
      {
         p->x += 1;
         p->direction = DIRECTION_RIGHT;
         p->move_cnt  =  MAX_CNT;
      }

      if ( pressedButtons & BUTTON_BTN )
      {
         bomb_new ( p->x_pixels, p->y_pixels ) ;
      }
   }
}


void sprite_init ( )
{
   sd_reset();

   SPR_clear();
   SPR_update(sprites, MAX_SPRITE);
   SPR_end ( );

   SPR_init(500);

   u16 i;

   players[0] = (tPlayer ) { 0, 4, 2, 0, 0, DIRECTION_NONE, MAX_CNT, VEL_INC, 0 };
   players[1] = (tPlayer ) { 0,15, 2, 0, 0, DIRECTION_NONE, MAX_CNT, VEL_INC, 0 };

   for ( i=0; i<2; i++ )
   {
      tPlayer *p = &players[i];

      p->x_pixels = p->x * 8 * 2;
      p->y_pixels = p->y * 8 * 2;
      p->sprite   = sd_new();

      SPR_initSprite ( &sprites[p->sprite], &leo, p->x_pixels, p->y_pixels, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
      SPR_setAnim ( &sprites[p->sprite], i );
   }

   VDP_setPalette(PAL3, leo.palette->data);
}



void update_scroll ()
{
//   u8 str[5];
//   uintToStr(players[0].y, str, 2);
//   VDP_drawText(str, 0,0);
//   uintToStr(VDP_getScreenHeight() / 16, str, 2);
//   VDP_drawText(str, 5,0);

   if ( _counter % 5 == 0 )
   {
      ++xscroll_b[0];
      ++xscroll_b[1];
      ++xscroll_b[2];
   }

   if ( _counter % 6 == 0 )
   {
      ++xscroll_b[3];
      ++xscroll_b[4];
      ++xscroll_b[5];
   }

   VDP_setScrollingMode ( HSCROLL_TILE, VSCROLL_PLANE );
   VDP_setHorizontalScrollTile(PLAN_B , 0, xscroll_b, 6, 1);
   VDP_setVerticalScroll ( PLAN_A, yscroll );
   //VDP_setHorizontalScrollTile(() PLAN_B, xscroll_b );
}




void move_players()
{
   u16 i;

   for ( i=0; i<2; i++ )
   {
      tPlayer *p = &players[i];

      if ( p->direction == DIRECTION_NONE  || p->move_cnt <= 0 )
      {
         continue;
      }

      p->move_cnt -= p->vel;

      if ( p->direction == DIRECTION_UP    ) p->y_pixels -= p->vel;
      if ( p->direction == DIRECTION_DOWN  ) p->y_pixels += p->vel;
      if ( p->direction == DIRECTION_LEFT  ) p->x_pixels -= p->vel;
      if ( p->direction == DIRECTION_RIGHT ) p->x_pixels += p->vel;

      if ( p->move_cnt <= 0 )
      {
         terrain_remove ( p->x, p->y );

         p->direction = DIRECTION_NONE;
         p->move_cnt = 0;
      }


      SPR_setPosition ( &sprites[i], p->x_pixels, p->y_pixels );
   }

   SPR_update(sprites, MAX_SPRITE);
}



s16 check_item ()
{
   u16 i;

   for ( i=0; i<2; i++ )
   {
      tPlayer *p = &players[i];

      if ( p->x == item.x && p->y == item.y )
      {
         return i;
      }
   }

   return -1;
}


int main ()
{
   VDP_init();
   VDP_setPlanSize ( 64, 128 );
   VDP_setScrollingMode ( HSCROLL_TILE, VSCROLL_PLANE );

   game();

   return 0;
}


