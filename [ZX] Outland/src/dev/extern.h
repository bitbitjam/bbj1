// External custom code to be run from a script

//optimized print_str
void pinta_str_border (unsigned char x, unsigned char y, unsigned char c, unsigned char *s, unsigned char border) {
	while (*s)	{
	    if(border){
            sp_PrintAtInv (y - 1, x, c, 0); //SPACE CHR is 0 (32 - 32)
            sp_PrintAtInv (y + 1, x, c, 0);
		}
        sp_PrintAtInv (y, x ++, c, (*s ++) - 32);
	}
}

void do_extern_action (unsigned char n_action) {
    switch (n_action){
        case 0:
			break;

        case 1:
	        print_str (3, 5, 79, " BIENVENIDO A LA BASE IO.   ");
	        print_str (3, 6, 79, " ESPERO QUE SEPA SER FLE-   ");
	        print_str (3, 7, 79, " XIBLE CON MIS TRABAJADORES ");
			break;

        case 2:
	        print_str (5, 9, 79, "  HOLA JEFE.  DEBERIA  ");
	        print_str (5, 10, 79, " HABLAR CON LA DOCTORA ");
	        print_str (5, 11, 79, " SOBRE LOS SUICIDIOS...");
	        print_str (5, 12, 79, " TRES ESTA SEMANA!!     ");
            break;

        case 3:
	        print_str (2,  4, 79, " LOS SUICIDAS TENIAN UNOS  ");
	        print_str (2,  5, 79, " RESULTADOS SANGUINEOS MUY ");
	        print_str (2,  6, 79, " PECULIARES. TRAIGAME UNA  ");
	        print_str (2,  7, 79, " MUESTRA Y PODRE DARLE MAS ");
	        print_str (2,  8, 79, "           DATOS.          ");
            break;

        case 4:
	        print_str (5, 5, 79, " TENGO QUE VER  ");
	        print_str (5, 6, 79, " AL DIRECTOR DE ");
	        print_str (5, 7, 79, " LA BASE IO.    ");
            break;

        case 6:
	        print_str (1, 10, 79, " ES UN POTENCIADOR MUY FUERTE ");
	        print_str (1, 11, 79, " PARA INCREMENTAR LA CARGA DE ");
	        print_str (1, 12, 79, " TRABAJO. EN DOSIS PROLONGADAS");
	        print_str (1, 13, 79, " PUEDE SER ALUCINOGENO.       ");
	        print_str (1, 14, 79, " ESTE VIAL LO HE VISTO ANTES. ");
	        print_str (1, 15, 79, " ESTABAN METIENDO CAJAS CON EL");
	        print_str (1, 16, 79, " EN LA OFICINA DEL DIRECTOR   ");
            break;

        case 7:
	        print_str (3, 11, 79, " MALDICION TODOS VACIOS!!   ");
	        print_str (3, 12, 79, " DEBO ENCONTRAR TODOS LOS   ");
	        print_str (3, 13, 79, " VIALES Y SALIR DE AQUI CON ");
	        print_str (3, 14, 79, " VIDA PARA PODER DENUNCIAR  ");
	        print_str (3, 15, 79, " ESTA LOCURA...             ");
            break;

        case 8:
	        print_str (3, 11, 79, " UGGGGHHH!!!! ");
            break;
    }
	sp_UpdateNow ();
	espera_activa(2000);
	espera_activa(2000);
	espera_activa(2000);
	espera_activa(2000);
	espera_activa(2000);
	espera_activa(2000);
	espera_activa(2000);
	espera_activa(2000);
	espera_activa(2000);
}
