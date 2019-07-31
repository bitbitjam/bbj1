#include "../inc/include.h"

Vect2D_u16 item;



const tBigtile terrain_template [ TERRAIN_MAX_HEIGHT ] [ TERRAIN_MAX_WIDTH ] =
{
   { BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN },
   { BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN, BT_HIDDEN },
   { BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE,   BT_NONE   },
   { BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_SOFT,   BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_SOFT,   BT_FLOOR,  BT_FLOOR,  BT_FLOOR,  BT_FLOOR  },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   14
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   20
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_ROCK,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_ROCK,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_SOFT,   BT_SOFT,   BT_ROCK,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
//   { BT_ROCK,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT,   BT_SOFT   },
};




tBigtile terrain [ 30 ] [ 20 ];




void bigtile_draw ( tBigtile t, u16 x, u16 y )
{
   VDP_setTileMapXY ( APLAN, TILE_ATTR_FULL(PAL2,0,0,0,TILE_USERINDEX + t.tile1), x*2+0, y*2+0 );
   VDP_setTileMapXY ( APLAN, TILE_ATTR_FULL(PAL2,0,0,0,TILE_USERINDEX + t.tile2), x*2+1, y*2+0 );
   VDP_setTileMapXY ( APLAN, TILE_ATTR_FULL(PAL2,0,0,0,TILE_USERINDEX + t.tile3), x*2+0, y*2+1 );
   VDP_setTileMapXY ( APLAN, TILE_ATTR_FULL(PAL2,0,0,0,TILE_USERINDEX + t.tile4), x*2+1, y*2+1 );
}


bool terrain_can_remove ( u16 x, u16 y )
{
   return terrain[y][x].bt != SOLID;
}


void terrain_remove ( u16 x, u16 y )
{
   tBigtile none = BT_NONE;
   bigtile_draw ( none, x, y );

   if ( terrain[y][x].is_diggable )
   {
      explosion_terrain_new ( x, y );
   }

   terrain[y][x] = none;

}


void terrain_draw ()
{
   VDP_loadTileSet ( &tileset, TILE_USERINDEX, 0);
   VDP_setPalette  ( PAL2, tilespal.data );

   u16 x, y;

   for ( y=0; y<TERRAIN_MAX_HEIGHT; y++ )
   {
      for ( x=0; x<TERRAIN_MAX_WIDTH; x++ )
      {
         terrain[y][x] = terrain_template[y][x];
         bigtile_draw ( terrain[y][x], x, y );
      }
   }
}


void terrain_draw_blocks ()
{
   //u16 nb_blocks = 20;
   u16 nb_blocks = ( random() & ( TERRAIN_MAX_BLOCKS - TERRAIN_MIN_BLOCKS ) ) + TERRAIN_MIN_BLOCKS;
   u16 i, x, y;

   tBigtile block = BT_ROCK;


   for ( i=0; i<nb_blocks; i++ )
   {
      x = ( random() % 20 ) + 0;
      y = ( random() %  9 ) + 5;

      terrain[y][x] = block;
      bigtile_draw ( terrain[y][x], x, y );
   }
}


void terrain_hidde_item ()
{
   VDP_loadTileSet ( &tileset, TILE_USERINDEX, 0);
   VDP_setPalette  ( PAL2, tilespal.data );

   Vect2D_u16 diggables [ TERRAIN_MAX_HEIGHT * TERRAIN_MAX_WIDTH ];
   u16 counter = 0;

   u16 x, y;

   for ( y=0; y<TERRAIN_MAX_HEIGHT; y++ )
   {
      for ( x=0; x<TERRAIN_MAX_WIDTH; x++ )
      {
         if ( terrain[y][x].is_diggable )
         {
            diggables[counter].x = x;
            diggables[counter].y = y;

            ++counter;
         }
      }
   }

   if ( counter )
   {
      u16 aux = random() % counter;

      item.x = diggables[aux].x;
      item.y = diggables[aux].y;

//      draw_uint ( item.x, 0,0,2);
//      draw_uint ( item.y, 3,0,2);
   }
}
