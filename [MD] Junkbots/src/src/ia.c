#include "../inc/include.h"


static bool       has_place_to_go;
static Vect2D_u16 place_to_go;
//static u16        obstaculo_cnt = 0;

//static void find_place_to_go    ( bool diggable );
static void find_place_to_go    ( );
static void normalice_positions ( s16 *x, s16 *y );

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void normalice_positions ( s16 *x, s16 *y )
{
   if ( *y >= TERRAIN_MAX_HEIGHT )
   {
      *y = TERRAIN_MAX_HEIGHT - 1;
   }
   else if ( *y < 0 )
   {
      *y = 0;
   }

   if ( *x >= TERRAIN_MAX_WIDTH )
   {
      *x = TERRAIN_MAX_WIDTH - 1;
   }
   else if ( *x < 0 )
   {
      *x = 0;
   }
}



//static void find_place_to_go ( bool diggable )
static void find_place_to_go ( )
{
   u16 x, y;
   Vect2D_u16 listado[TERRAIN_MAX_HEIGHT * TERRAIN_MAX_HEIGHT];
   u16 nb_listado = 0;

   for ( y=0; y<TERRAIN_MAX_HEIGHT; y++ )
   {
      for ( x=0; x<TERRAIN_MAX_WIDTH; x++ )
      {
         //if ( terrain[y][x].is_diggable == diggable )
         if ( terrain[y][x].is_diggable )
         {
            listado [ nb_listado++ ] = (Vect2D_u16){ x, y };
         }
      }
   }

   if ( nb_listado )
   {
      has_place_to_go = true;
      place_to_go = listado [ random() % nb_listado ];
   }

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void ia_enemy()
{
   tPlayer *p = &players[1];

   if ( p->direction == DIRECTION_NONE  ||  p->move_cnt <= 0 )
   {
      // to do OK, dejemos que se ejecute la IA
   }
   else
   {
      return;
   }


   if ( p->timeout_free >0 )
   {
      return;
   }


   s16 x = p->x;
   s16 y = p->y;


   if ( has_place_to_go )
   {
      u16 direction = DIRECTION_NONE;

      if ( random() % 2 )
      {
         if      ( place_to_go.x > p->x ) { direction = DIRECTION_RIGHT; x = p->x + 1; }
         else if ( place_to_go.x < p->x ) { direction = DIRECTION_LEFT;  x = p->x - 1; }
         else if ( place_to_go.y > p->y ) { direction = DIRECTION_DOWN;  y = p->y + 1; }
         else if ( place_to_go.y < p->y ) { direction = DIRECTION_UP;    y = p->y - 1; }
      }
      else
      {
         if      ( place_to_go.y > p->y ) { direction = DIRECTION_DOWN;  y = p->y + 1; }
         else if ( place_to_go.y < p->y ) { direction = DIRECTION_UP;    y = p->y - 1; }
         else if ( place_to_go.x > p->x ) { direction = DIRECTION_RIGHT; x = p->x + 1; }
         else if ( place_to_go.x < p->x ) { direction = DIRECTION_LEFT;  x = p->x - 1; }
      }

      // si se topa con un obstatuclo para
      if (  ( direction == DIRECTION_NONE )  ||  ( terrain [ y ][ x ].bt == SOLID )  )
      {
         //++obstaculo_cnt;
         has_place_to_go = false;
      }
      else
      {
         if ( direction == DIRECTION_UP )
         {
            p->y -= 1;
            p->direction = DIRECTION_UP;
            p->move_cnt =  MAX_CNT;
         }
         else if ( direction == DIRECTION_DOWN )
         {
            p->y += 1;
            p->direction = DIRECTION_DOWN;
            p->move_cnt =  MAX_CNT;
         }
         else if ( direction == DIRECTION_LEFT )
         {
            p->x -= 1;
            p->direction = DIRECTION_LEFT;
            p->move_cnt =  MAX_CNT;
         }
         else if ( direction == DIRECTION_RIGHT )
         {
            p->x += 1;
            p->direction = DIRECTION_RIGHT;
            p->move_cnt  =  MAX_CNT;
         }
      }
   }


   if ( !has_place_to_go )
   {
      struct _options
      {
         u16 x, y;
         u16 direccion;
      }
      options[4];

      u16 nb_options = 0;


      y = p->y - 1;
      x = p->x;
      normalice_positions ( &x, &y );
      if ( terrain [ y ][ x ].is_diggable ) options [ nb_options++ ] = (struct _options){ x, y, DIRECTION_UP };

      y = p->y + 1;
      x = p->x;
      normalice_positions ( &x, &y );
      if ( terrain [ y ][ x ].is_diggable ) options [ nb_options++ ] = (struct _options){ x, y, DIRECTION_DOWN };

      y = p->y;
      x = p->x - 1;
      normalice_positions ( &x, &y );
      if ( terrain [ y ][ x ].is_diggable ) options [ nb_options++ ] = (struct _options){ x, y, DIRECTION_LEFT };

      y = p->y;
      x = p->x + 1;
      normalice_positions ( &x, &y );
      if ( terrain [ y ][ x ].is_diggable ) options [ nb_options++ ] = (struct _options){ x, y, DIRECTION_RIGHT };


      if ( nb_options )
      {
         u16 aux = random() % nb_options;

         p->x         = options[aux].x;
         p->y         = options[aux].y;
         p->direction = options[aux].direccion;
         p->move_cnt  = MAX_CNT;

         //obstaculo_cnt = 0;
      }
      else
      {
         //bool diggable = (obstaculo_cnt == 2 ) ? false : true;
         //find_place_to_go ( diggable );
         find_place_to_go ( );
      }
   }
}

