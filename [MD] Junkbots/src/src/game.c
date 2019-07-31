#include "../inc/include.h"


static u16 level = 1;


static you_found_it ();
static you_lose ();


////////////////////////////////////////////////////////////////////////////////////////////////////


static you_found_it ()
{
   ++level;

   explosion_reset_all ();

   u16 sp = sd_new();
   SPR_initSprite ( &sprites[sp], &leo, players[0].x_pixels+8, players[0].y_pixels+8, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
   SPR_setAnim ( &sprites[sp], 5 );
   SPR_update(sprites, MAX_SPRITE);

   VDP_drawText ("You found it!", 13,13 );
   waitMs(1000);

   while(1)
   {
      if ( JOY_readJoypad(JOY_1) )
      {
         break;
      }

      SPR_update(sprites, MAX_SPRITE);
      VDP_waitVSync();
   }


   VDP_fadeOutAll(10,0);
}


static you_lose ()
{
   level = 1;

   explosion_reset_all ();

   u16 sp = sd_new();
   SPR_initSprite ( &sprites[sp], &leo, players[1].x_pixels+8, players[1].y_pixels+8, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
   SPR_setAnim ( &sprites[sp], 5 );
   SPR_update(sprites, MAX_SPRITE);

   VDP_drawText ("You lose!", 15,13 );
   waitMs(1000);

   while(1)
   {
      if ( JOY_readJoypad(JOY_1) )
      {
         break;
      }

      SPR_update(sprites, MAX_SPRITE);
      VDP_waitVSync();
   }

   VDP_fadeOutAll(10,0);
}


////////////////////////////////////////////////////////////////////////////////////////////////////


void game ()
{
   level = 1;

   while ( 1 )
   {
      screen_title ( );

      bool go = game_loop();

      screen_gameover ( go );
   }

}


bool game_loop()
{

   while ( 1 )
   {
      u32 _counter = 0;
      s16 who_found_item = - 1;

      terrain_draw ();
      terrain_draw_blocks ();
      terrain_hidde_item ();

      sprite_init ();


      VDP_setPalette(PAL1,bgb_image.palette);
      u16 ind = TILE_USERINDEX+600;
      VDP_drawImageEx ( BPLAN, &bgb_image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, TRUE );

      SYS_enableInts();

      VDP_setScrollingMode ( HSCROLL_TILE, VSCROLL_PLANE );

      VDP_setPalette(PAL0,palette_grey);

      VDP_drawText("LEVEL: ",16,0);
      draw_uint(level, 23,0,1 );

      while ( true )
      {
         ia_enemy();
         freeze_update();

         handle_joy();

         move_players();
         who_found_item = check_item();

         if ( who_found_item == 0 ) // player 1
         {
            you_found_it();

            if ( level == 7 )
            {
               return true;
            }
            else
            {
               break;
            }
         }
         else if ( who_found_item == 1 ) // player 2
         {
            you_lose();

            return false;
         }


         explosion_terrain_update();
         bomb_update ( );

         update_scroll();

         //waitMs(50);

         VDP_waitVSync();
         ++_counter;
      }
   }


}







