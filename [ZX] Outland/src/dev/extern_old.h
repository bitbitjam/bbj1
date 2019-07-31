// External custom code to be run from a script

extern unsigned char cad1[0];
extern unsigned char cad2[0];
extern unsigned char cad3[0];
extern unsigned char cad4[0];
extern unsigned char cad5[0];
extern unsigned char cad6[0];
extern unsigned char cad7[0];
extern unsigned char cad8[0];
extern unsigned char cad9[0];

unsigned char *cads [10] = {cad1, cad2, cad3, cad4, cad5, cad6, cad7, cad8, cad9};
#asm
	._cad1
		defm " BIENVENIDO A LA BASE  "
		defb 0
		defm " IO. ESPERO QUE SEPA   "
		defb 0
		defm " SER FLEXIBLE CON LOS  "
		defb 0
		defm " TRABAJADORES...       "
		defb 0
	
	._cad2
		defm " NO TENGO NADA MAS QUE "
		defb 0
		defm "    HABLAR CON USTED.  "
		defb 0
	
	._cad3
		defm " HOLA JEFE.  DEBERIA   "
		defb 0
		defm " HABLAR CON LA DOCTORA "
		defb 0
		defm " SOBRE LOS RECIENTES   "
		defb 0
		defm " SUICIDIOS...          "
		defb 0

	._cad4
		defm " DEBO VER AL DIRECTOR  "
		defb 0

	._cad5
		defm "                       "
		defb 0

	._cad6
		defm "                       "
		defb 0

	._cad7
		defm "                       "
		defb 0

	._cad8
		defm "                       "
		defb 0

	._cad9
		defm "                       "
		defb 0

#endasm


void draw_text (unsigned char x, unsigned char y, unsigned char c, char *s) {
	unsigned char m;
	while (*s) {
		m = (*s) - 32;
		sp_PrintAtInv (y, x ++, c, m);
		s ++;
	}
}

void draw_texts (unsigned char x, unsigned char y, unsigned char c, char *cad, unsigned char n, unsigned char width) {
	while (n > 0) {
		draw_text (x, y, c, cad);
		y ++;		
		cad += width;
		n --;	
		sp_UpdateNow ();
		peta_el_beeper (7 + ((rand () & 1) << 2));
	}	
}

void draw_rectangle (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c) {
	unsigned char i, j;
	for (i = y1; i <= y2; i ++)
		for (j = x1; j <= x2; j ++)
			sp_PrintAtInv (i, j, c, 0);	
}


void do_extern_action (unsigned char n) {
	saca_a_todo_el_mundo_de_aqui ();
	draw_rectangle (4, 6, 26, 14, 7);
	draw_texts (4, 7, 7, cads [n - 1], 7, 24);
	espera_activa (500);
}
