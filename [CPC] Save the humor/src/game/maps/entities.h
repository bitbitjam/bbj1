#ifndef _ENTITIES_H_
#define _ENTITIES_H_

// Useful constants
#define MAX_ENTITIES	16
#define MAX_JUMP		12
#define MAX_VELOCITY	1
#define MAX_AI_PROCESS	2

// Entity Types
#define ENT_PLAYER				0
#define	ENT_SCIENTIST_LEFTRIGHT	1
#define	ENT_TIEMAN_LEFTRIGHT	2
#define ENT_SOLDIER_LEFTRIGHT	3
#define ENT_GLADIATOR_LEFTRIGHT	4
#define ENT_ROMAN_LEFTRIGHT		5
#define ENT_ALIEN_LEFTRIGHT		6
#define	ENT_SCIENTIST_STATIC	7
#define	ENT_TIEMAN_STATIC		8
#define ENT_SOLDIER_STATIC		9
#define ENT_GLADIATOR_STATIC	10
#define ENT_ROMAN_STATIC		11
#define ENT_ALIEN_STATIC		12

// Global AI_STATES
#define ST_LAUGHING 		200
#define ST_LAUGHDELAY		50
#define ST_DEAD				255

// Joke States
#define JOK_NULL			0
#define JOK_LAUNCH			1
#define JOK_LAUNCHCYCLES	2
#define JOK_DOWN			2


// Entity main struct
typedef struct entity {
	unsigned char   type;		// Entity Type
	unsigned char*sprite;		// Appearance of the entity
	unsigned char  x,  y;		// Pixel position
			 char vx, vy;		// Pixel velocity 
//	unsigned char gx, gy;		// Entity partícular gravity (it lets you change gravity as per entity)
	unsigned char 	jump;	    // Cycles the user has been jumping (it counts up till MAX_JUMP)
	unsigned char  moved;		// True if the entity has been moved
	unsigned char stateAI;		// For AI purposes: it stores the last state of the agent
	unsigned char delayAI;		// Cicles of delay till next AI process (level of detail for AI)
			 char heading;		// Heading left or right for sprite proccessing
} TEntity;

// Entities of the game 
extern TEntity GAME_ENTITIES[MAX_ENTITIES];


void ent_moveEntity(TEntity* e);
char ent_moveJoke(TEntity* e);
void ent_draw(TEntity *e);
void ent_processAI(TEntity* e);
char ent_checkCollision(TEntity *eA, TEntity *eB, unsigned char w, unsigned char h);
char ent_checkCollisionWithJoke(TEntity *joke, TEntity *e);

#endif