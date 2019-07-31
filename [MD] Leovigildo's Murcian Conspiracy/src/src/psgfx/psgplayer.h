/*

PARA AGREGAR EFECTOS DE SONIDO
------------------------------

1.- Colocar los archivos de Mod2PSG2 convertidos a VGM al directorio "psgfx" (C:\GQ-Player\GQ-Player\psgfx)
2.- Editar vgmpsgfx.bat (C:\GQ-Player\GQ-Player\vgmpsgfx.bat) y añadir líneas con el nombre del nuevo archivo
3.- Agregar líneas como estas de INCLUDES con el nombre del nuevo archivo
4.- Añadir a "_list" los datos el nuevo efecto de sonido

*/

/////////////////////////
// sfx
#include "sfx_ok.h"
#include "sfx_select.h"
#include "sfx_start.h"

extern

/*
PARA AGREGAR EFECTOS DE SONIDO
------------------------------

1.- Colocar los archivos de Mod2PSG2 convertidos a VGM al directorio "psgfx" (C:\GQ-Player\GQ-Player\psgfx)
2.- Editar vgmpsgfx.bat (C:\GQ-Player\GQ-Player\vgmpsgfx.bat) y añadir líneas con el nombre del nuevo archivo
3.- Agregar líneas como estas de INCLUDES con el nombre del nuevo archivo
4.- Añadir a "_list" los datos el nuevo efecto de sonido
*/

static const PSG _list [] =
{
	{ "Ok",          (u8*) sfx_ok_data,      0 },
	{ "Select",      (u8*) sfx_select_data,     0 },
	{ "Start",       (u8*) sfx_start_data,      0 },


               // <-- Añadir líneas como las de arriba.
               //     Primero título, luego el nombre del VGM, y luego
               //     el patrón, que para nosotros siempre será 0


	{ "EOF",                 NULL,         0 } // no quitar!
};
