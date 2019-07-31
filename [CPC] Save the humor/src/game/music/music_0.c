////////////////////////////////////////////////////////////////////////////////////////////
////  DATOS DE LA CANCION (DADOS POR EL WYZTRACKER)
////	- Crear un nuevo fichero para cada m�sica que hag�is
////
void the_music_0() {  // Cambiar el nombre (debe ser distinto en cada fichero)

__asm

///----------------------------------------------------------------------------------------------------------------
/// TABLA DE CANCIONES 
///    - A�adir un nuevo _SONG_X por cada canci�n, si es que hay varias dentro de una misma. (No es necesario)
///----------------------------------------------------------------------------------------------------------------
.globl _SONG_TABLE_0	/// <<- _SONG_TABLE_0 es un identificador global, cambiar cuando se cree una canci�n nueva
_SONG_TABLE_0:			/// <<-
    .dw _SONG_0

///----------------------------------------------------------------------------------------------------------------
/// TABLA DE EFECTOS DE SONIDO DE LA CANCI�N 0
///		- Dado por el WYZTracker
///----------------------------------------------------------------------------------------------------------------
.globl _EFFECT_TABLE_0  /// <<- _EFFECT_TABLE_0 es un identificador global, cambiar cuando se cree una canci�n nueva
_EFFECT_TABLE_0:		/// <<-

///----------------------------------------------------------------------------------------------------------------
/// TABLA DE PATRONES DE LA CANCION 0
///		- Dado por el WYZtraker
///----------------------------------------------------------------------------------------------------------------
.globl _RULE_TABLE_0    /// <<- _RULE_TABLE_0 es un identificador global, cambiar cuando se cree una canci�n nueva
_RULE_TABLE_0:			/// <<-
    .dw PAUTA_0, PAUTA_1, PAUTA_2, PAUTA_3, PAUTA_4, PAUTA_5, PAUTA_6, PAUTA_7

    ;Pautas (instrumentos)
    ;Instrumento 'Harmonica'
    PAUTA_0:	.DB	42,0,11,0,12,0,11,0,10,0,9,0,129
    ;Instrumento 'triririn'
    PAUTA_1:	.DB	73,0,10,0,42,0,9,0,8,0,7,0,7,0,7,0,7,0,6,0,6,0,6,0,6,0,136
    ;Instrumento 'chip1'
    PAUTA_2:	.DB	70,0,7,0,40,0,7,0,6,0,5,0,129
    ;Instrumento 'onda1'
    PAUTA_3:	.DB	73,0,10,0,11,0,12,0,11,0,10,0,9,0,8,0,129
    ;Instrumento 'Onda2'
    PAUTA_4:	.DB	71,0,8,0,8,0,8,0,7,0,6,0,6,0,6,0,6,0,6,0,6,0,5,0,5,0,5,0,5,0,5,0,5,0,140
    ;Instrumento 'Chip2'
    PAUTA_5:	.DB	68,0,5,0,37,0,5,0,4,0,3,0,129
    ;Instrumento 'Harmonica vol 2'
    PAUTA_6:	.DB	38,0,7,0,8,0,8,0,7,0,7,0,6,0,129
    ;Instrumento 'Bajo v2'
    PAUTA_7:	.DB	77,0,44,0,11,0,9,0,8,0,8,0,8,0,7,0,7,0,6,0,7,0,6,0,6,0,5,0,5,0,129

///----------------------------------------------------------------------------------------------------------------
/// TABLA DE SONIDOS DE LA CANCI�N 0
///		- Dado por el WYZTracker
///----------------------------------------------------------------------------------------------------------------
.globl _SOUND_TABLE_0   /// <<- _SOUND_TABLE_0 es un identificador global, cambiar cuando se cree una canci�n nueva
_SOUND_TABLE_0:			/// <<-
    .dw SONIDO0, SONIDO1, SONIDO2, SONIDO3

             ;Efectos
             ;Efecto 'bass drum'
             SONIDO0:	.DB	209,61,0,46,91,0,209,121,0,255
             ;Efecto 'drum'
             SONIDO1:	.DB	232,44,0,23,59,5,232,58,3,0,9,2,0,8,1,0,7,1,255
             ;Efecto 'cascabeles'
             SONIDO2:	.DB	16,9,1,255
             ;Efecto 'bass drum vol 2'
             SONIDO3:	.DB	186,57,0,0,102,0,162,131,0,255

///----------------------------------------------------------------------------------------------------------------
/// DATOS DE LA CANCION 0
///    Se obtienen del fichero .mus. Hay que abrirlo con un editor hexadecimal y copiarlo aqu�
///    Tal cual salen los n�meros hexadecimales, se ponen de 4 en 4 con 0x delante (para indicar que son en hexadecimal)
///    Esto pod�is hacerlo con Buscar y Reemplazar, que es bastante r�pido.
///----------------------------------------------------------------------------------------------------------------
_SONG_0:
    .dw 0x0706,0x0000,0x073f,0x4e4c,0x4e4e,0x4e4c,0x4e51,0x4947
    .dw 0x4949,0x4947,0x494c,0x4e4c,0x4e4e,0x4e4c,0x4e51,0x4947
    .dw 0x4949,0x4947,0x494c,0x3f00,0xd504,0xfefe,0xfed5,0xddfe
    .dw 0xfefe,0xfedc,0xd5fe,0xfefe,0xfed5,0xddfe,0xfefe,0xfedc
    .dw 0xdafe,0xfefe,0xfedc,0xdafe,0xfefe,0xfed8,0xdafe,0xfefe
    .dw 0xfedc,0xdafe,0xfefe,0xfed8,0xdafe,0xfefe,0xfed8,0x00fe
    .dw 0x043f,0xfeda,0xdcfe,0xfefe,0xfeda,0xd8fe,0xfefe,0xfeda
    .dw 0xdcfe,0xfefe,0xfeda,0xd8fe,0xfefe,0x013f,0x0129,0x0126
    .dw 0x0128,0x6624,0x023f,0x3f26,0x6801,0x0129,0x012b,0x012d
    .dw 0x4174,0x3f70,0xb002,0x3fbe,0x7005,0x013f,0x0129,0x0126
    .dw 0x0128,0x6624,0x023f,0x3f26,0x6801,0x0129,0x012b,0x012d
    .dw 0x4170,0x3f6b,0xab02,0x053f,0x3fab,0x2901,0x2601,0x2801
    .dw 0x2401,0x3f66,0x2602,0x013f,0x2968,0x2b01,0x2d01,0x7401
    .dw 0x7041,0x023f,0xbeb0,0x013f,0x3432,0xbeb5,0x3234,0xbeb4
    .dw 0x3032,0x0132,0x416d,0x3f6b,0xab02,0x053f,0x3f6b,0x3201
    .dw 0xb534,0x34be,0xb432,0x32be,0x3230,0x6d01,0x6b41,0x023f
    .dw 0x3fab,0xab05,0x7f00,0x7f00,0x7f02,0x7f02,0x7f02,0x7f00
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f00
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f02,0x7f02,0x7f01
    .dw 0x7f02,0x7f02,0x7f02,0x7f00,0x7f02,0x7f00,0x7f02,0x7f01
    .dw 0x7f02,0x7f01,0x0001,0x0000
		
__endasm;
}