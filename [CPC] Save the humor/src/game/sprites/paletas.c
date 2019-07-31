
///
///  EN ESTE ARCHIVO SE DEFINEN LAS DISTINTAS PALETAS QUE QUERAMOS USAR
///     - Podéis definir tantas paletas distintas como queráis copiando el modelo 
///       y poniéndoles otro nombre.
///     - Recordad que sólo se puede usar una única paleta de 16 colores a la vez en pantalla
///    	- El primer color de la paleta es el color de fondo
///		- Las etiquetas para los nombres de las paletas deben seguir 
///			el mismo esquema que las de los sprites (consultad personaje.c).
///         En este caso, los nombres de paleta empezarán siempre por _pal_
///       Ejemplo:
///           _pal_miPaletaDeLaSuerte:
///     - Los números de cada color son los números que usa el CPC (van del 0 al 31)
///         Si queréis probarlos, podéis usar la orden INK de BASIC en el emulador
///         Ejemplo: 
///				Nada más arrancar el CPC ponéis INK 1,6. Esto elige el color 6 (rojo)
///             como primer color de la paleta actual. Por defecto, el texto sale en 
///             el primer color de la paleta, por lo que podéis ver el cambio inmediato.
///
void data_paletas_0() {
__asm 

.globl _pal_paletaPrincipal
_pal_paletaPrincipal::
	.db #00								// Color del Borde
    .db #0x01,#0x18,#0x14,#0x06,#0x1A,#0x00,#0x02,#0x08	// Los 16 Colores de la paleta (el primero, el de fondo)
	.db #0x0D,#0x0A,#0x0C,#0x0F,#0x0E,#0x10,#0x03,#0x15
	
	
/// Paleta especial para colores de texto multicolor. (No tocar)
.globl _pal_texto_multicolor
_pal_texto_multicolor::
	.db #000,#002,#008,#010,#032,#034,#040,#042
	.db #128,#130,#136,#138,#160,#162,#168,#170
	
__endasm;
}