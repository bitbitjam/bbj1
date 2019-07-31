#include <genesis.h>


typedef enum { false = 0, true = !false } bool;


#define ABS(x) ((x)<0 ? -(x) : (x))





#define MAX_CNT 16
#define VEL_INC  2



#include "gfx.h"
#include "spritedispacher.h"
#include "bomb.h"
#include "main.h"
#include "ia.h"
#include "terrain.h"
#include "explosion.h"
#include "screen.h"
#include "game.h"

