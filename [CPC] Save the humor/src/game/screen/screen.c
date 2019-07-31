#include "screen.h"

extern unsigned char scr_visible_page;
extern unsigned char scr_hidden_page;

void scr_setScreenBuffers(char main_scr, char buffer_scr) {
	// Load new values for Screen Pages
	scr_visible_page = main_scr;
	scr_hidden_page = buffer_scr;
	__asm	
		ret
		;// Define Screen Pages
		.globl _scr_visible_page
		.globl _scr_hidden_page
		_scr_visible_page:: .DB #0xC0	;// C000 - FFFF
		_scr_hidden_page::  .DB #0x40	;// 4000 - 7FFF
	__endasm;
}

void scr_setFBScreenPage(char page, char offset) {
	__asm 
		;// Save Registers
		PUSH IX

		;// Get the page
		LD  IX, #4	;// 2 + 2 = Return Address + IX Saved
		ADD IX, SP
		LD 	A, (IX)
		;ld a,(base_visible)
		
		;// Use R12/R13 to set the screen address for the given page
		;// Put the bits in the correct place for CRTC
		srl a
		srl a
	
		;// Select CRTC R12
		ld bc, #0xBC0C
		out (c),c
		;// Ouput the selected Page to CRTC R12 (Next address B = 0xBD)
		inc b
		out (c),a

		;// Select CRTC R13 (BC = 0xBC0D)
		dec b
		inc c
		out (c),c
		;// Ouput 0 to CRTC R13 (Next address B = 0xBD)
		inc b
		ld  a, 1(IX)
		out (c),a
		
		;// Restore Regiters
		POP IX
	__endasm;
}

char scr_swapScreenBuffers() {
	unsigned char aux = scr_visible_page;
	
	// Swap Screen Buffers
	scr_visible_page = scr_hidden_page;
	scr_hidden_page  = aux;
	// Wait for VSYNC
	scr_waitVSYNC();
	// Move Screen Frame Buffer Pointer
	scr_setFBScreenPage(scr_visible_page, 0x04);
	
	return scr_visible_page;
}

void scr_waitVSYNC() {
	__asm 
		;// Check if we are in VSYNC zone
		wait_vs:
			ld b, #0xF5
			in a,(c)
			rra
			jr nc, wait_vs ;// no, wait
	__endasm;
}

void scr_putSprite8x16_buffer0100(unsigned char *destiny, unsigned char *sprite) {
	__asm
		POP AF  ; DIRECCION DE RETORNO
		POP HL	; RONALDO: SPRITE DATA
		POP DE	; RONALDO: DESTINATION ADDRESS
		PUSH DE	; RONALDO: Dejar la pila en el mismo estado que estaba al salir para no afectar a 	variables locales de C
		PUSH HL
		PUSH AF ; DIRECCION DE RETORNO
		LD A, #16	; 16 de alto
	siguiente_fila:
		LDI		; 8 de ancho = 8 LDIs
		LDI
		LDI
		LDI
		LDI
		LDI
		LDI	
		LDI
		EX DE,HL		; COMPROBAR SI PASAMOS A FILA MULTIPLO DE 8
		LD BC,#0xC6F8	; #0x10000 = #0x4100 + #0xBF00
		ADD HL,BC		; Sumo #0x800 - #0x8 + #0xBF00 = C6F8 (Siguiente fila + BF00, para ver 
						; si pasamos de 0xFFFF)
   		JP C, fila_especial
		LD BC,#0x4100	; Como hemos sumado #0xBF00 de más, añadimos #0x4100 para dar la vuelta
		ADD HL, BC
	decrementar_fila:
		EX DE,HL
		DEC A
		JP NZ, siguiente_fila
		RET
	fila_especial:		;; VALOR ERRONEO!!!
		LD BC,#0x148	; La fila siguiente es restando #0x4000 - #0x50 + #8 = #0x3FB8
		ADD HL,BC		; Y a eso le sumamos #0x4100 y le restamos #0x7F8 => -#0x670 => +#0xF990
		JP decrementar_fila
	__endasm;
}