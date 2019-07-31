#include "../inc/include.h"



tBomb bombs      [ MAX_SPRITE ];
tBomb explosions [ MAX_SPRITE ];

u8 move_screen_current = 0;
u8 move_screen_counter = 0;

const Vect2D_s16 move_screen_pos[2][3] =
{
 { {3,-3}, {-2, 2 }, {1,-1} },
 { {-3,3}, {2, -2 }, {-1,1} },
};


static void _new_explosion    (s16 x, s16 y );

static void _delete_bomb      ( u16 i );
static void _delete_explosion ( u16 i );

static u16  _find_bomb        ( );
static u16  _find_explosion   ( );

static void _players_in_range ( u16 explosion, u16 range );

////////////////////////////////////////////////////////////////////////////////


void _move_screen ( u16 i )
{
   if ( !move_screen_current )
   {
      move_screen_current = i;
      move_screen_counter = 3;
   }

   if ( move_screen_current == i )
   {
//      --move_screen_counter;
//
//      s16 array_x [ 40 ];
//      s16 array_y;
//      u16 i;
//      u16 aux = random() % 2;
//
//
//      for ( i=0; i<40; i++)
//      {
//         //array_x[i]+=move_screen_pos[aux][move_screen_counter].x;
//         array_y += move_screen_counter; //move_screen_pos[aux][move_screen_counter].y;
//      }
//
//      //VDP_setHorizontalScrollTile(PLAN_A , 0, array_x, 40, 1);
      VDP_setVerticalScroll ( PLAN_A, move_screen_counter );
   }
}


static u16 _find_bomb ( )
{
   u16 i;

   for ( i=0; i<MAX_SPRITE; i++ )
   {
      if ( !bombs[i].active )
      {
         return i;
      }
   }

   return 0;
}


static u16 _find_explosion ( )
{
   u16 i;

   for ( i=0; i<MAX_SPRITE; i++ )
   {
      if ( !explosions[i].active )
      {
         return i;
      }
   }

   return 0;
}


static void _delete_bomb ( u16 i )
{
   _new_explosion ( bombs[i].x, bombs[i].y );

   u16 sprite = bombs[i].sprite;

   bombs[i].sprite  = 0;
   bombs[i].timeout = 0;
   bombs[i].x       = - 40;
   bombs[i].y       = - 40;
   bombs[i].active  = false;

   SPR_setPosition(&sprites[sprite], -40, -40 );
   sd_delete( sprite );
}


static void _delete_explosion ( u16 i )
{
   u16 sprite = explosions[i].sprite;

   explosions[i].sprite  = 0;
   explosions[i].timeout = 0;
   explosions[i].x       = - 40;
   explosions[i].y       = - 40;
   explosions[i].active  = false;

   SPR_setPosition(&sprites[sprite], -40, -40 );
   sd_delete( sprite );
}


static void _new_explosion ( s16 x, s16 y )
{
   u16 i      = _find_explosion();
   u16 sprite = sd_new();

   explosions[i].sprite  = sprite;
   explosions[i].timeout = BOMB_EXPLOSION_TIMEOUT;
   explosions[i].x       = x;
   explosions[i].y       = y;
   explosions[i].active  = true;

   SPR_initSprite ( &sprites[sprite], &leo, x, y, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
   SPR_setAnim ( &sprites[sprite], BOMB_EXPLOSION_SPRITE_POS );
}


static void _players_in_range ( u16 explosion, u16 range )
{
   u16 x = explosions[explosion].x + 8;
   u16 y = explosions[explosion].y + 8;

   u16 i;

   for ( i=0; i<2; i++ )
   {
      u16 player_x = players[i].x_pixels + 8;
      u16 player_y = players[i].y_pixels + 8;

      s16 rest_x = x - player_x;
      s16 rest_y = y - player_y;

      if ( ABS(rest_x) <= range && ABS(rest_y) <= range )
      {
         freeze_player ( i );
      }
   }
}


////////////////////////////////////////////////////////////////////////////////


void bomb_new ( s16 x, s16 y )
{
   u16 i      = _find_bomb ();
   u16 sprite = sd_new();


   bombs[i].sprite  = sprite;
   bombs[i].timeout = BOMB_TIMEOUT;
   bombs[i].x       = x;
   bombs[i].y       = y;
   bombs[i].active  = true;

   SPR_initSprite ( &sprites[sprite], &leo, x, y, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
   SPR_setAnim ( &sprites[sprite], BOMB_SPRITE_POS );
}



void bomb_update ( )
{
   u16 i;

   for ( i=0; i<MAX_SPRITE; i++ )
   {
      if ( bombs[i].timeout > 0 )
      {
         --bombs[i].timeout;

         if ( bombs[i].timeout == 0 )
         {
            _delete_bomb ( i );
         }
      }

      if ( explosions[i].timeout > 0 )
      {
         _move_screen ( i );

         --explosions[i].timeout;

         _players_in_range ( i, BOMB_EXPLOSION_RANGE );

         if ( explosions[i].timeout == 0 )
         {
            _delete_explosion ( i );
         }
      }

   }
}
