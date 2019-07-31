////////////////////////////////////////////////////////////////////////////////////////////
////  DATOS DE LAS DISTINTAS M�SICAS Y EFECTOS DE SONIDO: LOS DA EL WYZTRACKER!
////
void the_global_music_table() {

__asm

///----------------------------------------------------------------------------------------------------------------
/// DECLARACI�N DE S�MBOLOS GLOBALES DE LOS DATOS DE LAS CANCIONES ( 4 por canci�n )
///		- A�adir 4 por cada nueva canci�n que se quiera a�adir a las canciones del juego
///     - Los 4 s�mbolos tienen que estar definidos en un archivo aparte y declarados como globales con .globl
///     - Los nombres de los identificadores deben ser distintos (para no colisionar)
///----------------------------------------------------------------------------------------------------------------
.globl _GLOBAL_MUSICS_TABLE
_GLOBAL_MUSICS_TABLE::
	.DW _EFFECT_TABLE_HERRERO, 	_SONG_TABLE_HERRERO,_RULE_TABLE_HERRERO,_SOUND_TABLE_HERRERO	
	.DW _EFFECT_TABLE_ACCION, 	_SONG_TABLE_ACCION, _RULE_TABLE_ACCION, _SOUND_TABLE_ACCION	
	.DW _EFFECT_TABLE_ACC2, 	_SONG_TABLE_ACC2,	_RULE_TABLE_ACC2,	_SOUND_TABLE_ACC2
	
__endasm;

}
