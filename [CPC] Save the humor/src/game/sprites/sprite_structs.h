#ifndef _SPRITE_STRUCTS_H_
#define _SPRITE_STRUCTS_H_

/// ESTRUCTURAS DE DATOS Y OTRAS CURIOSIDADES (No tocar)
///
typedef struct Sprite  		// minimun sprite structure
{
    char *sp0;    //2 bytes 01
    char *sp1;		//2 bytes	23
    int coord0;		//2 bytes	45	current superbuffer address
    int coord1;		//2 bytes	67  old superbuffer address
    unsigned char cx, cy;	// 2 bytes 89 	current coordinates
    unsigned char ox, oy;	// 2 bytes 1011  old coordinates
    unsigned char move1;	// los bits 4,3,2 definen el tipo de dibujo!!
} TSprite;

#endif