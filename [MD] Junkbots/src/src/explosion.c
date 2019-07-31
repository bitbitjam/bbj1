#include "../inc/include.h"



tExpTerrains expTerrains [MAX_SPRITE];


static u16   _find ();
static void _delete ( i );
//////////////////////////////////////////////////////////////////////////////////////////


static u16 _find ()
{
   u16 i;
   u16 min = EXPLOSION_TERRAIN_COUNTER;

   for ( i=0; i<MAX_SPRITE; i++ )
   {
      if ( expTerrains[i].timeout < min )
      {
         min = expTerrains[i].timeout;
      }

      if ( expTerrains[i].timeout == 0 )
      {
         return i;
      }
   }

   return min;
}


static void _delete ( i )
{
   u16 sprite = expTerrains[i].sprite;

   expTerrains[i].timeout = 0;
   expTerrains[i].sprite  = 0;

   SPR_setPosition(&sprites[sprite], -40, -40);
   sd_delete( sprite );
}


//////////////////////////////////////////////////////////////////////////////////////////


void explosion_terrain_new ( u16 x, u16 y )
{
   u16 aux = _find();
   u16 sprite = sd_new();

   expTerrains[aux].timeout = EXPLOSION_TERRAIN_COUNTER;
   expTerrains[aux].sprite  = sprite;

   SPR_initSprite(&sprites[sprite], &leo, x*8*2, y*8*2, TILE_ATTR(PAL3, TRUE, FALSE, FALSE));
   SPR_setAnim(&sprites[sprite], EXPLOSION_TERRAIN_SPRITE_POS );
}


void explosion_terrain_update ( )
{
   u16 i;

   for ( i=0; i<EXPLOSION_TERRAIN_MAX; i++ )
   {
      if ( expTerrains[i].timeout > 0 )
      {
         --expTerrains[i].timeout;

         if ( expTerrains[i].timeout == 0 )
         {
            _delete ( i );
         }
      }

   }
}


void explosion_reset_all ()
{
   u16 i;

   for ( i=0; i<EXPLOSION_TERRAIN_MAX; i++ )
   {
      _delete ( i );
   }
}
