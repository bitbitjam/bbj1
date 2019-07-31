#ifndef _SPRITES_H
#define _SPRITES_H

#include "sprite_structs.h"

/// IDENTIFICADORES GLOBALES DE SPRITES
///   Para que el programa pueda acceder a los datos de los sprites, hay que
///   declarar su existencia aquí, poniendo el nombre global que tienen sin
///   el subrayado de delante.
///   Añadid los vuestros conforme los creéis.
///
extern unsigned char sm_charlie1[];
extern unsigned char sm_cientificos[];
extern unsigned char sm_encorbatado[];
extern unsigned char sm_soldao[];
extern unsigned char sm_gladiador[];
extern unsigned char sm_romano[];
extern unsigned char sm_alien[];
extern unsigned char sm_chistaco[];
extern unsigned char sm_protamorir1[];
extern unsigned char sm_protamorir2[];
extern unsigned char sm_soldaorisa1[];
extern unsigned char sm_soldaorisa2[];
extern unsigned char sm_gladiadorrisa1[];
extern unsigned char sm_gladiadorrisa2[];
extern unsigned char sm_romanorisa1[];
extern unsigned char sm_romanorisa2[];
extern unsigned char sm_cientificosrisa1[];
extern unsigned char sm_cientificosrisa2[];
extern unsigned char sm_encorbatadorisa1[];
extern unsigned char sm_encorbatadorisa2[];
extern unsigned char sm_alienrisa1[];
extern unsigned char sm_alienrisa2[];

/// IDENTIFICADORES GLOBALES DE LAS PALETAS
///   Igual que los sprites, deben ser declarados
extern unsigned char pal_paletaPrincipal[];
extern unsigned char pal_texto_multicolor[];

/// BANNERS Y CARTELES
extern unsigned char s_bannermenu[];
extern unsigned char s_marcador_izq[];
extern unsigned char s_marcador_dcha[];

/// MÉTODOS
void spr_flipHorizontalMask(unsigned char* sprite);

#endif