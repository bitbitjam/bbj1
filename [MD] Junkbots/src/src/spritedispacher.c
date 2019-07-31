#include "../inc/include.h"


bool used_sprites [ MAX_SPRITE ];



static u16 _find ( )
{
   u16 i;

   for ( i = 0; i<MAX_SPRITE; i++)
   {
      if ( ! used_sprites[i] )
      {
         return i;
      }
   }

   return MAX_SPRITE-1;
}


u16 sd_new ( )
{
   u16 i = _find();
   used_sprites[ i ] = true;

   return i;
}


void sd_delete ( u16 i )
{
   used_sprites[i] = false;
}


void sd_reset()
{
   u16 i;

   for ( i = 0; i<MAX_SPRITE; i++)
   {
      sd_delete( i);
   }
}
