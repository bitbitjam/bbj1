#include "include/newTypes.h"
#include "include/VDP_TMS9918.h"
#include "include/VDP_SPRITE.h"
#include "include/VDP_V9938.h"

#include "GameSprites.h"
#include "ConfigNPJ.h"

// Screen...
#include "gfx/Portada_Patterns.h"
#include "gfx/Portada_Colors.h"
#include "gfx/Creditos_Patterns.h"
#include "gfx/Creditos_Colors.h"

// Tiles
#include "gfx/Tiles_Colors.h"
#include "gfx/Tiles_Patterns.h"

// Game Screens
#include "gfx/Marcadores.h"
#include "gfx/Nivel1.h"
#include "gfx/Nivel2.h"
#include "gfx/Nivel3.h"
#include "gfx/Nivel4.h"

#define NUMBER_OF_SCREENS 7

#define  HALT __asm halt __endasm   //wait for the next interrupt

// Definitions of Labels -------------------------------------------------------

//BIOS addresses
#define CHGET  0x009F
#define GTSTCK 0x00D5
#define KILBUF 0x0156

#define NUM_OF_SPRITES_PJ        2
#define NUM_OF_FRAMES_PJ         4
#define NUM_OF_SPRITES_PER_NPJ   2
#define NUM_OF_FRAMES_PER_NPJ    4
#define PATTERN_NUM_OF_FIRST_NPJ (NUM_OF_FRAMES_PJ * NUM_OF_SPRITES_PJ * 2) + 2

#define DIST(x, y) (x > y ? x - y : y - x)


#define POS_CUP_X 120
#define POS_CUP_Y  32 

__sfr __at (0xA8) g_slotPort;

typedef struct
{
	byte x;
	byte y;
	char dx;
	char dy;
    byte lookingAt;
	byte speed;
	byte stepFrame;
	uint state;
	byte lives;
} Pj;

typedef struct
{
	byte id;
	byte x;
	byte y;
	char dx;
	char dy;
    byte lookingAt;
	byte xi;
	byte yi;
	byte xf;
	byte yf;
	byte speed;
	byte visionRange;
	byte stepFrame;
	uint state;
	byte color;
	const unsigned char *cfgInicial;
} Npj;

typedef struct
{
	byte numNPJs;
	Npj *npjs;
} GameScreen;

// Ouch, this seems twitter :o
typedef enum {stateInRoute = 0, stateReadyToFollow = 1, 
			  stateFollowing = 26, stateReadyToUnfollow = 27, 
			  stateReturningToRoute = 39, stateForceRoute = 40} StatesNPJ;

typedef enum {lookingAtRight = 0, lookingAtLeft = 1} LookingAt;

// Thx to AOrante for the TMS libs and all these functions!!! :D
// http://aorante.blogspot.com.es/2014/02/libreria-de-funciones-para-el-tms9918-c.html
// https://code.google.com/p/vdp-tms9918-sdcc-functionslib/
void print(byte column, byte line, char* text);
void vprint(uint vaddr, char* text);
void vpoke_block(uint address, char* block, uint size);
void WAIT(uint cicles);
byte inkey(void); // __naked;

//void putScreen(const unsigned char *patterns, const unsigned char *colors);
void putScreen(const unsigned char *patterns, uint sizePatterns, const unsigned char *colors, uint sizeColors);
void newGame(void);
void initPJ(void);
void initNPJs(void);
void putPJ(void);
void putNPJ(Npj *npj, byte zOrder);
void putCup(byte x, byte y);
void spritesOut(void);
void movePJ(void);
void moveNPJs(void);
void changeStatesNPJs(Npj *npj);
boolean checkNPJSeePJ(Npj *npj);
boolean checkNPJCollPJ(Npj *npj);
void dead(void);
void putMessageInScreen(char *msg, byte posX);
void saveScreen(void);
void restoreScreen(void);
void prepareScreen(byte screenNumber);
void checkScreen(void);
byte stick(void); // __naked;
void turnOnScreen(void);
void turnOffScreen(void);
void killBuf(void);
void memcpy(unsigned char *dest, const unsigned char *orig, uint size);
void rleDecode(const unsigned char *arrayEncoded, uint size, unsigned char *arrayDecoded);

Pj pj, pjBackup;
Npj gameNPJs[32], screenNPJsBackup[4];
GameScreen gameScreens[NUMBER_OF_SCREENS];
byte numCurrentScreen;
GameScreen *currentScreen;
unsigned char decodeBuffer[6144];

void main(void)
{
	//  Thx to Nerlaska, for the SDCC tutorials, tools, and this code!!! :D
	// http://albertodehoyonebot.blogspot.com.es/p/how-to-create-msx-roms-with-sdcc.html
	__asm
		di
		ld sp, (#0xFC4A)
		ei
	__endasm;

	g_slotPort = (g_slotPort & 0xCF) | ((g_slotPort & 0x0C) << 2);

	// Let's the party begin!!! (Poty poty!!! ^^U)
	

	// Switch off the fucking click of the keys... >_<
	// CLIKSW = F3DBH
	__asm
		ld hl, #0xF3DB
		ld (hl), #0
	__endasm;

	color(15, 1, 1);
	screen(4);
	setSpritesSize(1);
	setSpritesZoom(false);
	while(1)
	{
		turnOffScreen();
		HALT;
		putScreen(portadaPatternsRLE, portadaPatternsRLE_size, portadaColorsRLE, portadaColorsRLE_size);
		HALT;
		turnOnScreen();
		killBuf();
		while(inkey() != ' ');
		turnOffScreen();
		HALT;
		newGame();
		HALT;
		turnOnScreen();

		while(pj.lives > 0)
		{
			HALT;
			movePJ();
			if(pj.lives == 0) break; // ñapa
			moveNPJs();
		}
	}
}
//---------------------------------------------------------------------------

//print in screen 1 or 2 (& 4 :D )
void print(byte column, byte line, char* text)
{
	uint vaddr = BASE20 + (line << 5) + column; // calcula la posicion en la VRAM
	vprint(vaddr, text);
}
//---------------------------------------------------------------------------

void vprint(uint vaddr, char* text)
{
	while(*(text)) vpoke(vaddr++,*(text++));
}
//---------------------------------------------------------------------------

void vpoke_block(uint address, char* block, uint size)
{    
	while (size-->0){ vpoke(address++,*(block++));}
}
//---------------------------------------------------------------------------

// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
  return;
}
//---------------------------------------------------------------------------

byte inkey(void) //__naked
{
	__asm   
		   call    CHGET
		   ld l,a
	__endasm;
}

void putScreen(const unsigned char *patterns, uint sizePatterns, const unsigned char *colors, uint sizeColors)
{
	uint address;
	byte data = 0;
	//unsigned char decodeBuffer[7000];
	// One, name table
	for(address = BASE20; address < BASE20 + 256 * 3; ++address)
	{
		vpoke(address, data++);
	} 

	// Two, pattern table!
	rleDecode(patterns, sizePatterns, decodeBuffer);
	copyToVRAM((uint)decodeBuffer, BASE22, 256 * 8 * 3);

	// Tres!, el maique... oops, I said: Three, color table!
	rleDecode(colors, sizeColors, decodeBuffer);
	copyToVRAM((uint)decodeBuffer, BASE21, 256 * 8 * 3);
}
//---------------------------------------------------------------------------

void newGame(void)
{
	//uint d = 0;
	initPJ();
	initNPJs();
	numCurrentScreen = 0;
	currentScreen = gameScreens;
	
	// Sprites to-to-to-ttotto the vram!!!
	copyToVRAM((uint)patternsSprites, BASE24, 18 * 32);

	copyToVRAM((uint)tilesPatterns, BANK0, 256 * 8);
	copyToVRAM((uint)tilesPatterns, BANK1, 256 * 8);
	copyToVRAM((uint)tilesPatterns, BANK2, 256 * 8);

	copyToVRAM((uint)tilesColors, BASE21, 256 * 8);
	copyToVRAM((uint)tilesColors, BASE21 + 256 * 8, 256 * 8);
	copyToVRAM((uint)tilesColors, BASE21 + 256 * 8 * 2, 256 * 8);

	copyToVRAM((uint)marcadores, BASE20, 32 * 3);
	prepareScreen(0);
}
//---------------------------------------------------------------------------

void initPJ(void)
{
	pj.x = 114;
	pj.y = 170;
	pj.dx = 0;
	pj.dy = 0;
    pj.lookingAt = lookingAtRight;    
	pj.stepFrame = 0;
	pj.state = 0;
	pj.speed = 3;
	pj.lives = 5;
}
//---------------------------------------------------------------------------

void initNPJs(void)
{
	byte n, e;
	byte numNPJsInScreen;
	uint indexNPJ = 0;
	const unsigned char *indexInitCfgNPJs = INITIAL_CONFIGURATION_OF_NPJS;
	for (n = 0; n < NUMBER_OF_SCREENS; ++n)
	{
		numNPJsInScreen = *indexInitCfgNPJs++;
		gameScreens[n].numNPJs = numNPJsInScreen;
		gameScreens[n].npjs = gameNPJs + indexNPJ;
		for(e = 0; e < numNPJsInScreen; ++e)
		{
			//  No haría falta copiar todos los datos... Algunos no van a cambiar y se podrían coger de la configuración
			// inicial, y así se ganaría memoria, pero bueno, quería dejarlo abierto por si le añadía más cosas :/ ...
			gameNPJs[indexNPJ].cfgInicial = indexInitCfgNPJs;
			gameNPJs[indexNPJ].id = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].x  = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].y  = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].dx = (char)(*indexInitCfgNPJs++);
			gameNPJs[indexNPJ].dy = (char)(*indexInitCfgNPJs++);
            gameNPJs[indexNPJ].lookingAt = lookingAtRight;
			gameNPJs[indexNPJ].xi = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].yi = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].xf = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].yf = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].speed = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].visionRange = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].color = *indexInitCfgNPJs++;
			gameNPJs[indexNPJ].stepFrame = 0;
			gameNPJs[indexNPJ++].state = 0;			
		}
	}
}
//---------------------------------------------------------------------------

void putPJ(void)
{
    byte numPatternBase = 0;
    uint addressAttributes = BASE23; // + (plano << 2);
	uint addressColorsSprites = BASE23 - 512; // + (plano << 4);
	byte n = 0;
	byte step = pj.stepFrame;

    if(pj.lookingAt == lookingAtLeft)
	{
		numPatternBase += (NUM_OF_SPRITES_PJ << 2);
	}
	
	if(step > 0 && step < 6)
	{
		numPatternBase += (NUM_OF_SPRITES_PJ << 1);
	}
	else if(step >= 6 && step < 12)
	{
		numPatternBase += (NUM_OF_SPRITES_PJ * 3);
	}
	vpoke_block(addressColorsSprites, (colorsSprites + (numPatternBase << 4)), (NUM_OF_SPRITES_PJ << 4));
    numPatternBase <<= 2;

	for(; n < NUM_OF_SPRITES_PJ; ++n)
	{
		vpoke(addressAttributes++, pj.y);
		vpoke(addressAttributes++, pj.x);
		vpoke(addressAttributes++, numPatternBase);
        //vpoke(addressAttributes++, 15); //color
		numPatternBase += 4;
		++addressAttributes;
	}

	if(pj.state == 1)
	{
		putCup(pj.x, pj.y - 16);
	}
}
//---------------------------------------------------------------------------

void putNPJ(Npj* npj, byte zOrder)
{
	byte numPatternBase = (PATTERN_NUM_OF_FIRST_NPJ + (npj->id * NUM_OF_SPRITES_PER_NPJ * NUM_OF_FRAMES_PER_NPJ * 2));
	byte colorBase = (PATTERN_NUM_OF_FIRST_NPJ + (npj->color * 16));
	byte plane = (zOrder * NUM_OF_SPRITES_PER_NPJ) + NUM_OF_SPRITES_PJ + 2;
	uint addressAttributes = BASE23 + (plane << 2);
	uint addressColorsSprites = BASE23 - 512 + (plane << 4);
    byte step = npj->stepFrame;
	byte n = 0;

    if(npj->lookingAt == lookingAtLeft)
	{
		numPatternBase += (NUM_OF_SPRITES_PER_NPJ << 2);
		colorBase += (NUM_OF_SPRITES_PER_NPJ << 2);
	}

	// A little messy... :/
	if(step >= 3 && step < 6)
	{
		if(npj->dx || npj->dy)
		{
			numPatternBase += (NUM_OF_SPRITES_PER_NPJ << 1);
			colorBase += (NUM_OF_SPRITES_PER_NPJ << 1);
		}
		else
		{
			numPatternBase += (NUM_OF_SPRITES_PER_NPJ);
			colorBase += (NUM_OF_SPRITES_PER_NPJ);
		}
	}
	else if(step >= 9 && step < 12)
	{
		if(npj->dx || npj->dy)
		{
			numPatternBase += (NUM_OF_SPRITES_PER_NPJ * 3);
			colorBase += (NUM_OF_SPRITES_PER_NPJ * 3);
		}
		else
		{
			numPatternBase += (NUM_OF_SPRITES_PER_NPJ);
			colorBase += (NUM_OF_SPRITES_PER_NPJ);
		}
	}
	/*else
	{
		numPatternBase += NUM_OF_SPRITES_PER_NPJ;
	}*/

    vpoke_block(addressColorsSprites, (colorsSprites + (colorBase * 16)), (NUM_OF_SPRITES_PER_NPJ << 4));
	numPatternBase <<= 2;

	for(; n < NUM_OF_SPRITES_PER_NPJ; ++n)
	{
		vpoke(addressAttributes++, npj->y);
		vpoke(addressAttributes++, npj->x);
		vpoke(addressAttributes++, numPatternBase);
		numPatternBase += 4;
		++addressAttributes;
	}
}
//---------------------------------------------------------------------------

void putCup(byte x, byte y)
{
    //uint addressAttributes = BASE23; // + (plano << 2);
	//uint addressColorsSprites = BASE23 - 512; // + (plano << 4);

	// Patterns of the cup are 16 & 17
	vpoke_block(BASE23 - 512 + (NUM_OF_SPRITES_PJ * 16), (colorsSprites + (16 << 4)), 32);
	vpoke(BASE23 + (NUM_OF_SPRITES_PJ << 2), y);
	vpoke(BASE23 + (NUM_OF_SPRITES_PJ << 2) + 1, x);
	vpoke(BASE23 + (NUM_OF_SPRITES_PJ << 2) + 2, 16 << 2);
	vpoke(BASE23 + (NUM_OF_SPRITES_PJ << 2) + 4, y);
	vpoke(BASE23 + (NUM_OF_SPRITES_PJ << 2) + 5, x);
	vpoke(BASE23 + (NUM_OF_SPRITES_PJ << 2) + 6, 17 << 2);
}
//---------------------------------------------------------------------------

void spritesOut(void)
{
	byte n;
	for(n = 0; n < NUM_OF_SPRITES_PJ + 2 + (NUM_OF_SPRITES_PER_NPJ * 4); ++n)
	{
		vpoke(BASE23 + (n << 2), 195);
	}
}
//---------------------------------------------------------------------------

void movePJ(void)
{
    const speed = 4;
    byte s = stick();
    pj.dx = pj.dy = 0;
    switch(s)
    {
        case 1:
            pj.dy = -speed;
            break;
        case 2:
            pj.dx = +speed;
            pj.dy = -speed;
            break;
        case 3:
            pj.dx = +speed;
            break;
        case 4:
            pj.dx = +speed;
            pj.dy = +speed;
            break;
        case 5:
            pj.dy = +speed;
            break;
        case 6:
            pj.dx = -speed;
            pj.dy = +speed;
            break;
        case 7:
            pj.dx = -speed;
            break;
        case 8:
            pj.dx = -speed;
            pj.dy = -speed;
            break;
    }
	if(s)
	{
		++(pj.stepFrame);
		if(pj.stepFrame >= 12) pj.stepFrame = 1;
	}
	else
		pj.stepFrame = 0;
    pj.x += pj.dx;    
    pj.y += pj.dy;
	if(pj.dx > 0)
		pj.lookingAt = lookingAtRight;
	else if (pj.dx < 0)
		pj.lookingAt = lookingAtLeft;
	checkScreen();
	if(pj.lives == 0) return;
    putPJ();
}
//---------------------------------------------------------------------------

void moveNPJs(void)
{
	byte n;
	int x, y;
	char dx, dy;
	Npj *npjs = currentScreen[numCurrentScreen].npjs;
    uint state;

    for(n = 0; n < currentScreen[numCurrentScreen].numNPJs; ++n)
    {
        x = npjs->x;
        y = npjs->y;
        dx = npjs->dx;
        dy = npjs->dy;
		state = npjs->state;
        if(state == stateInRoute)
        {
            // State 0 => Usual behaviour => Move from (xi, yi) to (xf,yf)
            x += dx;
            y += dy;            
			if(dx < 0 && x < npjs->xi)
            {
                x = npjs->xi;
                npjs->dx = -dx;
            }
            else if(dx > 0 && x > npjs->xf)
            {
                x = npjs->xf;
                npjs->dx = -dx;
            }
            
			if(dy < 0 && y < npjs->yi)
            {
                y = npjs->yi;
                npjs->dy = -dy;
            }
            else if(dy > 0 && y > npjs->yf)
            {
                y = npjs->yf;
                npjs->dy = -dy;
            }
        }
		else if(state == stateFollowing)
		{		
			if(x < pj.x)
				dx = +2;
			else if(x > pj.x)
				dx = -2;
			else
				dx = 0;

			if(y < pj.y)
				dy = +2;
			else if(y > pj.y)
				dy = -2;
			else
				dy = 0;

			x += dx;
			y += dy;
			npjs->dx = dx;
			npjs->dy = dy;
		}
		else if(state == stateReturningToRoute || state == stateForceRoute)
		{		
			if(x < npjs->xi)
				dx = +2;
			else if(x > npjs->xi)
				dx = -2;
			else
				dx = 0;

			if(y < npjs->yi)
				dy = +2;
			else if(y > npjs->yi)
				dy = -2;
			else
				dy = 0;

			x += dx;
			y += dy;
			
			if(dx < 0 && x < npjs->xi)
            {
                x = npjs->xi;
                dx = 0;
            }
            else if(dx > 0 && x > npjs->xi)
            {
                x = npjs->xi;
                dx = 0;
            }
            
			if(dy < 0 && y < npjs->yi)
            {
                y = npjs->yi;
                dy = 0;
            }
            else if(dy > 0 && y > npjs->yi)
            {
                y = npjs->yi;
                dy = 0;
            }

			npjs->dx = dx;
			npjs->dy = dy;
		}

		if(npjs->dx > 0)
			npjs->lookingAt = lookingAtRight;
		else if (npjs->dx < 0)
			npjs->lookingAt = lookingAtLeft;

        npjs->x = (byte)x;
        npjs->y = (byte)y;
        putNPJ(npjs, n);      
		changeStatesNPJs(npjs);
		if(checkNPJCollPJ(npjs)) 
		{
			dead();
			if(pj.lives == 0) return;
		}
		++(npjs->stepFrame);
        if(npjs->stepFrame >= 12) npjs->stepFrame = 0;
		
        ++npjs;
    }
}
//---------------------------------------------------------------------------

void changeStatesNPJs(Npj *npj)
{
	const byte speedFast = 2;
	const byte speedSlow = 1;
    uint state = npj->state;
    boolean pjIsVisible = checkNPJSeePJ(npj);
    if(state == stateInRoute)
    {
		if(pjIsVisible)
		{
			npj->lookingAt = npj->x < pj.x ? lookingAtRight : lookingAtLeft;
			npj->dx = npj->dy = 0;			
			state = stateReadyToFollow;
		}
    }
	else if(state < stateFollowing)
    {
		if(pjIsVisible)
	        ++state;
		else
			state = stateReturningToRoute;
    }
	else if(state == stateFollowing)
    {
		if(!pjIsVisible)
		{
			npj->dx = npj->dy = 0;
	        state = stateReadyToUnfollow;
		}
    }
	else if(state < stateReturningToRoute)
    {
		if(pjIsVisible)
		{
		    npj->lookingAt = npj->x < pj.x ? lookingAtRight : lookingAtLeft;
			npj->dx = npj->dy = 0;
	        state = stateReadyToFollow;
		}
		else
			++state;
    }
	else if(state == stateReturningToRoute)
    {
		if(pjIsVisible)
		{
			npj->lookingAt = npj->x < pj.x ? lookingAtRight : lookingAtLeft;
			npj->dx = npj->dy = 0;
	        state = stateReadyToFollow;
		}
		else
		{
			
			if(npj->x == npj->xi && npj->y == npj->yi)
			{		
				state = stateInRoute;
				npj->dx = npj->cfgInicial[3];
				npj->dy = npj->cfgInicial[4];
			}
		}
    }
	else if(state == stateForceRoute)
    {
		if(npj->x == npj->xi && npj->y == npj->yi)
		{		
			state = stateInRoute;
			npj->dx = npj->cfgInicial[3];
			npj->dy = npj->cfgInicial[4];
		}
    }

    npj->state = state;    

}
//---------------------------------------------------------------------------

boolean checkNPJSeePJ(Npj *npj) 
{
    const byte distanceX = npj->visionRange;
    const byte distanceY = npj->visionRange;
    byte pjX = pj.x;
    byte pjY = pj.y;
    byte npjX = npj->x;
    byte npjY = npj->y;
    if(DIST(pjX, npjX) < distanceX && DIST(pjY, npjY) <  distanceY) 
	{
		return true;
	}
    return false;
}
//---------------------------------------------------------------------------

boolean checkNPJCollPJ(Npj *npj)
{
	if((DIST(npj->x, pj.x) < 16) && (DIST(npj->y, pj.y) < 16))
	{
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
void dead(void)
{
	uint address;
	char str[15] = "QUEDAN x VIDAS";
	//const char msg[] = "Quedan x vidas";
	//memcpy((unsigned char *)str, (const unsigned char *)msg, 15);	
	--(pj.lives);
	str[7] = '0' + pj.lives;
	color(15, 1, 15);
	WAIT(25);
	color(15, 1, 1);
	spritesOut();
	for(address = BASE20 + (32 * 3); address < BASE20 + (256 * 3); ++address)
	{
		vpoke(address, 0);
	}
	if(pj.lives == 0)
	{
		putMessageInScreen("GAME OVER", 11);
		WAIT(300);
		return;
	}

	putMessageInScreen(str, 8);
	WAIT(100);
	killBuf();
	while(inkey() != ' ');
	restoreScreen();
	--(pj.lives); // A little bug in the eleventh hour... >_<
	prepareScreen(numCurrentScreen);
}
//---------------------------------------------------------------------------

void putMessageInScreen(char *msg, byte posX)
{
	print(posX, 14, msg);
}
//---------------------------------------------------------------------------

void saveScreen(void)
{
	memcpy((unsigned char *)&pjBackup, (const unsigned char *)&pj, sizeof(Pj));
	memcpy((unsigned char *)&(screenNPJsBackup), (const unsigned char *)&(currentScreen[numCurrentScreen].npjs), currentScreen[numCurrentScreen].numNPJs * sizeof(Npj));
}
//---------------------------------------------------------------------------

void restoreScreen(void)
{
	memcpy((unsigned char *)&pj, (const unsigned char *)&pjBackup, sizeof(Pj));
	memcpy((unsigned char *)&(currentScreen[numCurrentScreen].npjs), (const unsigned char *)&(screenNPJsBackup), currentScreen[numCurrentScreen].numNPJs * sizeof(Npj));	
}
//---------------------------------------------------------------------------

void prepareScreen(byte screenNumber)
{
	uint dirScreen = 0;
	byte sprite1 = 0, sprite2 = 0;
	byte n;
	char livesStr[2];

	numCurrentScreen = screenNumber;

	switch(screenNumber)
	{
		case 0:
			sprite1 = 2;
			sprite2 = 0;
			dirScreen = (uint)nivel1scr;
			break;
		case 1:
			sprite1 = 0;
			sprite2 = 1;
			dirScreen = (uint)nivel2scr;
			break;
		case 2:
			sprite1 = 2;
			sprite2 = 1;
			dirScreen = (uint)nivel3scr;
			break;
		case 3:
			sprite1 = 3;
			sprite2 = 2;
			dirScreen = (uint)nivel4scr;
			break;
		case 4:
			sprite1 = 2;
			sprite2 = 1;
			dirScreen = (uint)nivel3scr;
			break;
		case 5:
			sprite1 = 0;
			sprite2 = 1;
			dirScreen = (uint)nivel2scr;
			break;
		case 6:
			sprite1 = 2;
			sprite2 = 3;
			dirScreen = (uint)nivel1scr;
			break;
	}
	HALT;
	turnOffScreen();
	copyToVRAM(dirScreen, BASE20 + (32 * 3), (256 * 3) - (32 * 3));
	copyToVRAM((uint)(patternsSprites + ((18 + ((sprite1 << 4)) << 5))), BASE24 + (18 * 32), 16 * 32);
	copyToVRAM((uint)(patternsSprites + ((18 + ((sprite2 << 4)) << 5))), BASE24 + (34 * 32), 16 * 32);
	if(screenNumber == 3)
		putCup(POS_CUP_X, POS_CUP_Y);
	else
		putCup(POS_CUP_X, 195);

	for(n = NUM_OF_SPRITES_PJ + 2; n < NUM_OF_SPRITES_PJ + 2 + (NUM_OF_SPRITES_PER_NPJ * 4); ++n)
	{
		vpoke(BASE23 + (n << 2), 195);
	}
	livesStr[1] = 0;
	livesStr[0] = pj.lives + '0';
	print(30, 1, livesStr);
	saveScreen();
	turnOnScreen();
}
//---------------------------------------------------------------------------

void checkScreen(void)
{
	byte newScreen = 0;
	byte n;

	if(pj.x < 4)
	{
		
		pj.x = 4;
	}
	else if(pj.x > 236)
	{
		pj.x = 236;
	}
	switch(numCurrentScreen)
	{
		case 3:
			if(pj.state == 0)
			{
				if((pj.x > POS_CUP_X - 16 && pj.x < POS_CUP_X + 32) &&
				   (pj.y > POS_CUP_Y - 16 && pj.y < POS_CUP_Y + 30))
				{	
					pj.state = 1;
					for(n = 0; n < currentScreen[numCurrentScreen].numNPJs; ++n)
						currentScreen[numCurrentScreen].npjs[n].state = stateForceRoute;
				}
			}
			//break;
		default:
			if(pj.y < 25)
			{
				if(numCurrentScreen == 3)
				{
					pj.y = 25;
				}
				else
				{
					if(((numCurrentScreen == 0 || numCurrentScreen == 6) && (pj.x >= 11 * 8 && pj.x <= 20 * 8)) ||
						((numCurrentScreen == 1  || numCurrentScreen == 5) && ((pj.x >= 6 * 8 && pj.x <= 8 * 8) || (pj.x >= 22 * 8 && pj.x <= 24 * 8))) ||
						((numCurrentScreen == 2 || numCurrentScreen == 4) && ((pj.x >= 6 * 8 && pj.x <= 8 * 8) || (pj.x >= 22 * 8 && pj.x <= 24 * 8))))
					{
						pj.y = 174;
						prepareScreen(pj.state == 0 ? (numCurrentScreen + 1) : (numCurrentScreen - 1));
					}
					else
					{
						pj.y = 25;
					}
					
				}
			}
			else if (pj.y > 174)
			{
				if(numCurrentScreen == 0)
				{
					pj.y = 174;
				}
				else if(numCurrentScreen == 6)
				{
					turnOffScreen();
					spritesOut();
					HALT;					
					putScreen(creditosPatternsRLE, creditosPatternsRLE_size, creditosColorsRLE, creditosColorsRLE_size);
					turnOnScreen();
					WAIT(300);
					pj.lives = 0;
					return;
				}
				else
				{
					if(((numCurrentScreen == 1 || numCurrentScreen == 5) && (pj.x >= 14 * 8 && pj.x <= 16 * 8)) ||
						(((numCurrentScreen == 2 || numCurrentScreen == 4)) && ((pj.x >= 6 * 8 && pj.x <= 8 * 8) || (pj.x >= 22 * 8 && pj.x <= 24 * 8))) ||
						((numCurrentScreen == 3) && ((pj.x >= 6 * 8 && pj.x <= 8 * 8) || (pj.x >= 22 * 8 && pj.x <= 24 * 8))))
					{
						pj.y = 25;
						prepareScreen(pj.state == 0 ? (numCurrentScreen - 1) : (numCurrentScreen + 1));
					}
					else
					{
						pj.y = 174;
					}
				}
			}
	}
	
	
}
//---------------------------------------------------------------------------

byte stick(void) // __naked
{
    __asm
            xor     a
            call    GTSTCK
            cp      #0
            jr      nz, endStick
            ld      a, #1
            call    GTSTCK
            cp      #0
            jr      nz, endStick
            ld      a, #2
            call    GTSTCK
        endStick:
            ld      l, a
    __endasm;
}
//---------------------------------------------------------------------------

void turnOnScreen(void)
{
	__asm
		call 0x44
	__endasm;
}
//---------------------------------------------------------------------------

void turnOffScreen(void)
{
	__asm
		call 0x41
	__endasm;
}
//---------------------------------------------------------------------------

void killBuf(void)
{
	__asm
		call KILBUF
	__endasm;
}
//---------------------------------------------------------------------------

void memcpy(unsigned char *dest, const unsigned char *orig, uint size)
{
	int index;
	for(index = 0; index < size; ++index)
		dest[index] = orig[index];
}
//---------------------------------------------------------------------------

void rleDecode(const unsigned char *arrayEncoded, uint size, unsigned char *arrayDecoded)
{
    uint i, p, r;
	unsigned char value, rep; 
	p=0;
    for(r=0;r < size; ++r)
	{
		if((unsigned char)arrayEncoded[r] == (unsigned char)0xEA)
		{
			value=arrayEncoded[r+2];
			rep=arrayEncoded[r+1];
			r+=2;
			for(i = 0;i < rep; ++i)
			{
				arrayDecoded[p]=value;
				p++;
				if(p == 6144) return;
			}
        }
    else {
        arrayDecoded[p]=arrayEncoded[r];
        p++;
		if(p == 6144) return;
    }
    }
}
