#include "genesis.h"
#include "main.h"


////////////////////////////////////////////////////////
//
// void exitIntro(){
// salimos de la intro
//
////////////////////////////////////////////////////////
void exitIntro(){

    VDP_fadeOutAll (60, 0);
    VDP_clearPlan(APLAN, 0);
    VDP_clearPlan(BPLAN, 0);
    waitTick(TICKPERSECOND * 1);
}


////////////////////////////////////////////////////////
//
// void waitBetweenMessages(u8 time)
// pausa entre mensajes
//
////////////////////////////////////////////////////////
u8 waitBetweenMessages(u8 time){

    u8 i;
    u16 state;

    for(i = 0; i < time; i++){

        // control de boton start
        state = JOY_readJoypad(JOY_1);

        if( state & BUTTON_START )
            return 1;

        VDP_waitVSync();
    }

    VDP_clearPlan(APLAN, 0);

    return 0;
}


////////////////////////////////////////////////////////
//
// u8 waitBetweenLetters(u8 time)
// pausa entre letras
//
////////////////////////////////////////////////////////
u8 waitBetweenLetters(u8 time){

    u8 i;
    u16 state;

    for(i = 0; i < time; i++){

        // control de boton start
        state = JOY_readJoypad(JOY_1);

        if( state & BUTTON_START )
            return 1;

        VDP_waitVSync();
    }

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////
//
//  u8 introControl(){
//  la intro del juego
//
//////////////////////////////////////////////////////////////////////////////////////
u8 introControl(){

    // cadenas de texto de l intro
    const char *str[num_strings_intro] = {
        "THE DAY IS 14 JUNE OF 2014.",

        "POCKET LUCHO IS CELEBRATING",
        "HIS BIRTHDAY AND NOT CODING",
        "AT ALL... LAZY BASTARD.",

        "MEANWHILE IN BARCELONA,",
        "MANUTRIGGER IS DRAWING",
        "VOLUPTUOUS SEXY VIXENS",

        "INSTEAD OF THE ANTAREX",
        "GFX THAT HIS COLLEAGUES",
        "ARE WAITING FOR... DAMM BASTARD.",

        "SUDDENLY... SOMETHING HAPPENS",
        "AND THE BASTARD ALARM",
        "IS ACTIVATED.",

        "LEOVIGILDO IS PLANNING A",
        "CONSPIRACY FOR CONQUER MURCIA",
        "WITH THE HELP OF HIS DOLPHINS",

        "THAT EAT ONION RINGS AND",
        "HIS ARMY OF CREACIONIST",
        "CYBORG NINJA FROGS.",

        "THE PIXEL BASTARD MUST PROTECT",
        "THE FREE PEOPLE OF MURCIA AND",
        "DEFEAT LEOVIGILDO*S CONSPIRACY+"
    };

    // numero de cadenas por pantalla
    const u8 num_strings[num_screens_intro] = {1, 3, 3, 3, 3, 3, 3, 3};

    // posicion en pantalla de cada cadena
    const u8 pos_strings[num_strings_intro][2] = {
        {pos_x_strg1, pos_y_strg1},
        {pos_x_strg2, pos_y_strg2}, {pos_x_strg3, pos_y_strg3}, {pos_x_strg4, pos_y_strg4},
        {pos_x_strg5, pos_y_strg5}, {pos_x_strg6, pos_y_strg6}, {pos_x_strg7, pos_y_strg7},
        {pos_x_strg8, pos_y_strg8}, {pos_x_strg9, pos_y_strg9}, {pos_x_strg10, pos_y_strg10},
        {pos_x_strg11, pos_y_strg11},{pos_x_strg12, pos_y_strg12},{pos_x_strg13, pos_y_strg13},
        {pos_x_strg14, pos_y_strg14},{pos_x_strg15, pos_y_strg15},{pos_x_strg16, pos_y_strg16},
        {pos_x_strg17, pos_y_strg17},{pos_x_strg18, pos_y_strg18},{pos_x_strg19, pos_y_strg19},
        {pos_x_strg20, pos_y_strg20},{pos_x_strg21, pos_y_strg21},{pos_x_strg22, pos_y_strg22},
    };

    // graficos de cada pantalla
    const INTRO _introGfxList [] = {
        { 0, 0, 0, 0 },
        { (u16*) map_intro_1, (u32*)tiles_intro_1, (u16*)pal_intro_1, tiles_intro_1_size },
        { (u16*) map_intro_2, (u32*)tiles_intro_2, (u16*)pal_intro_2, tiles_intro_2_size },
        { 0, 0, (u16*)pal_intro_2, 0 },
        { (u16*) map_intro_3, (u32*)tiles_intro_3, (u16*)pal_intro_3, tiles_intro_3_size },
        { (u16*) map_intro_4, (u32*)tiles_intro_4, (u16*)pal_intro_4, tiles_intro_4_size },
        { 0, 0, (u16*)pal_intro_4, 0 },
        { (u16*) map_intro_5, (u32*)tiles_intro_5, (u16*)pal_intro_5, tiles_intro_5_size },
        { 0, 0, 0, tiles_intro_2_size } // no quitar!
    };

    // cadena temporal que dibujaremos
    char str_temp[32];

    // para el dibujado de las letras una a una
    u8 a, b, c, num_string;
    u32 len;

    // retraso para hacer casar la musica en 50-60 hz
    u8 delay = 0;
    /*if(!IS_PALSYSTEM)
        delay = 5;
    else*/
        delay = 3;

    // reseteo la pantalla
    VDP_resetSprites();
    VDP_updateSprites();
    VDP_clearPlan(APLAN, 0);
    VDP_clearPlan(BPLAN, 0);

    VDP_setReg(7, 0x0E);    // cambia el color del fondo


    SND_startPlay_VGM(bgm00);

    ////////////////////////////////////////////////////////////////////////
    // cargo la paleta inicial y los tiles de la fuente
    VDP_setPalette(PAL0, palette_black);
    VDP_setPalette(PAL1, palette_black);
    VDP_setPalette(PAL2, palette_black);
    VDP_setPalette(PAL3, palette_black);

    VDP_loadTileData( tiles_font_credits, pos_vram_font, 96, 1);
    VDP_setPalette(PAL0, pal_font_credits);

    ////////////////////////////////////////////////////////////////////////
    // para cada pantalla de la intro
    num_string = 0;
    for( a = 0; a < num_screens_intro; a++ ){

        // dibujamos su ilustracion
        if( _introGfxList[a].size != 0 ){

            VDP_fadePal(PAL1, (u16*)_introGfxList[a-1].pal,palette_black, 30, 0);
            VDP_loadTileData( (u32*)_introGfxList[a].data, 1, _introGfxList[a].size, 1);
            VDP_setTileMapRectEx( BPLAN, (u16*)_introGfxList[a].map, 1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 0, 0, tam_map_h_tiles, tam_map_v_tiles+1);   // plano, data, index, baseflags, x, y, w, h
            VDP_fadePal(PAL1, palette_black, (u16*)_introGfxList[a].pal, 30, 0);
            VDP_setPalette(PAL1, (u16*)_introGfxList[a].pal);
        }

        // para cada frase de la pantalla
        for( b = 0; b < num_strings[a]; b++ ){

            // copiamos la cadena que toca
            len = strlen(str[num_string]);
            strncpy( str_temp, str[num_string], len);

            // dibuja el texto letra a letra
            for(c = 0; c < len; c++){

                // dibuja la letra que toque
                VDP_setTileMap(APLAN, TILE_ATTR_FULL(PAL0, 1, 0, 0, pos_vram_font_intro+(int)str_temp[c]), c+pos_strings[num_string][0], pos_strings[num_string][1]);

                // espera entre letras y si se pulsa START salimos
                if( waitBetweenLetters(delay) ){
                    exitIntro();
                    return 1;
                }
            }

            num_string++;
        }

        if( _introGfxList[a+1].size == 0 ){
            if( waitBetweenMessages(30) ){
                exitIntro();
                return 1;
            }
        }
        else{
            if( waitBetweenMessages(delayBetweenMessages) ){
                exitIntro();
                return 1;
            }
        }
    }

    exitIntro();

    return 0;
}


////////////////////////////////////////////////////////
//
// void creditsScreen(){
// creditos iniciales del juego
//
////////////////////////////////////////////////////////
void creditsScreen(){

    // reseteo la pantalla
    VDP_resetSprites();
    VDP_updateSprites();
    VDP_clearPlan(APLAN, 0);
    VDP_clearPlan(BPLAN, 0);

    VDP_setReg(7, 0x0E);    // cambia el color del fondo

    ////////////////////////////////////////////////////////////////////////
    // cargo la paleta inicial y los tiles de la fuente
    VDP_setPalette(PAL0, palette_black);
    VDP_setPalette(PAL1, palette_black);
    VDP_setPalette(PAL2, palette_black);
    VDP_setPalette(PAL3, palette_black);

    VDP_loadTileData( tiles_font_credits, pos_vram_font, tiles_font_credits_size, 1);

    VDP_drawText("pixel bastards in",11,1);
    VDP_drawText("LEOVIGILDO*S MURCIAN CONSPIRACY+",4,3);

    VDP_drawText("bitbitjam COMPO 2014",10,6);

    VDP_drawText("code by POCKET LUCHO",10,9);

    VDP_drawText("graphics by TRIGGERHAPPY",8,11);

    VDP_drawText("sound by CLICKING BUTTONS IN VGM",4,13);

    VDP_drawText("produced by 1985ALTERNATIVO",7,16);


    VDP_drawText("special thanks to CHILLY WILLY,",5,19);
    VDP_drawText("KANEDA, SHIRU, STEF, THEELF, ",7,20);
    VDP_drawText(" DSKYWALK, MGARCIAGUERRA",8,21);
    VDP_drawText("           AND YOU...",5,22);

    VDP_drawText("not produced by or under license", 4, 25);
    VDP_drawText("   from sega enterprises ltd", 4, 26);

    VDP_fadePal(PAL0, palette_black, pal_font_credits, 60, 0);
    VDP_setPalette(PAL0, pal_font_credits);

    waitTick(TICKPERSECOND * 5);

    VDP_fadeOutAll (60, 0);
}


//////////////////////////////////////////////////////////////////////////////////////
//
// void draw1985Logo()
// dibuja el logo de 1985
//
//////////////////////////////////////////////////////////////////////////////////////
void draw1985Logo(){

   // reseteo las capas, los sprites
    VDP_resetSprites();
    VDP_updateSprites();
    VDP_clearPlan(APLAN, 0);
    VDP_clearPlan(BPLAN, 0);

    // cargo la paleta inicial
    VDP_setPalette(PAL0, palette_black);
    VDP_setPalette(PAL1, palette_black);
    VDP_setPalette(PAL2, palette_black);
    VDP_setPalette(PAL3, palette_black);

    // cargo los tiles del logo
    VDP_loadTileData( tiles_1985_logo, 1, logo1985_tiles_size, 1);

    // plano, data, index, baseflags, x, y, w, h
    VDP_setTileMapRectEx( APLAN, map_1985_logo, 1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 12, 8, 16, 10);

    VDP_fadePal(PAL1, palette_black, pal_1985_logo, 30, 0);

    // espera
    psgFxPlay(SELECT_SFX);
    VDP_fadePal(PAL1, palette_white, pal_1985_logo, 20, 0);
    waitTick(TICKPERSECOND * 3);

    // fade de salida
    VDP_fadeOutAll (30, 0);
}


///////////////////////////////////////////////////////////////////////////////////////
//
//  title_Screen()
//  pantalla de titulo
//
///////////////////////////////////////////////////////////////////////////////////////
u8 titleScreen(){

    u8 exit = 0;
    u8 a = 0;
    u8 startPressed = 0;
    u16 state;
    u8 start_game = 0;  // indica si comenzamos un juego, 0 si salimos por tiempo
    //u8 seconds = 0;     // control de salida por tiempo

    // para el efecto persiana
    u8 bg_assemble_start_line;

	// reseteo las capas, los sprites
    VDP_resetSprites();
    VDP_updateSprites();
    VDP_clearPlan(APLAN, 0);
    VDP_clearPlan(BPLAN, 0);

    // cargo la paleta inicial
    VDP_setPalette(PAL0, palette_black);
    VDP_setPalette(PAL1, palette_black);
    VDP_setPalette(PAL2, palette_black);
    VDP_setPalette(PAL3, palette_black);

    VDP_setReg(7, 0x00);    // cambia el color del fondo

    // muevo el scroll a su posicion original
    VDP_setHorizontalScroll(BPLAN, 0);
    VDP_setVerticalScroll(BPLAN, 0);
    VDP_setHorizontalScroll(APLAN, 0);
    VDP_setVerticalScroll(APLAN, 0);

    // cambio el registro 11 del vdp para el efecto
    vscroll_a = 0;
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    // cargo los tiles del logo
    VDP_loadTileData( tiles_logo_title, 1, tiles_logo_title_size, 1);

    //carga los tiles del FONDO en VRAM
    VDP_loadTileData( tiles_back_title, 1+tiles_logo_title_size, tiles_back_title_size, 1);

    // dibuja el fondo (plano, data, index, baseflags, x, y, w, h)
    VDP_setTileMapRectEx( BPLAN, map_back_title, 1+tiles_logo_title_size, TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 0, 0, map_back_title_x_size, map_back_title_y_size );

    // plano, data, index, baseflags, x, y, w, h
    VDP_setTileMapRectEx( APLAN, map_logo_title, 1, TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), 9, 3, map_logo_title_x_size,  map_logo_title_y_size);

    // carga los tiles de la FUENTE
    VDP_loadTileData( tiles_font_credits, pos_vram_font, 96, 1);

    VDP_drawTextBG( APLAN, "NOT PRODUCED BY OR UNDER LICENSE", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 4, 25);
    VDP_drawTextBG( APLAN, "   OF SEGA ENTERPRISES LTD.", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 4, 27);

    // linea en la que empieza el efecto
    bg_assemble_start_line = 144;

    // reproduce la MUSICA
    SND_startPlay_VGM(bgm01);

    // paletas
    VDP_fadePal(PAL1, palette_black, pal_logo_title, 30, 1);
    VDP_setPalette(PAL3, pal_font_credits);

    SYS_setHIntCallback((_voidCallback *) bgAsmHIntCB);     // seleccionamos la rutina a ejecutar en la interrupcion HSYNC
    VDP_setHIntCounter(0);                                  // interrupcion cada scanline
    VDP_setHInterrupt(1);                                   // activa la interrupcion HINT

    // bucle de dibujado del logo
    while(bg_assemble_start_line > 1){

        // esperamos a VSync para actualizar lo relacionado con el dibujado del efecto
        VDP_waitVSync();

        // cada frame mueve la "cortina" una linea hacia arriba.
        // cuando termina, desactiva la interrupcion HINT
        start_line = --bg_assemble_start_line;
        VDP_setVerticalScroll(APLAN, vscroll_a + start_line--);
    }
    VDP_setHInterrupt(0);

    VDP_fadePal(PAL0, palette_black, pal_back_title, 30, 0);
    VDP_setPalette(PAL0, pal_back_title);

    //////////////////////////////////////////////////////////
    // bucle hasta que pulsamos start o salimos por tiempo
    a = 0;
    while( exit == 0){

        a++;
        if( a == 40 ){
            a = 0;
            /*seconds++;

            // control de salida por tiempo
            if( seconds == 60 ){
                start_game = 0;
                SND_stopPlay_VGM();
                VDP_fadeOutAll (60, 0);
                return start_game;
            }*/
        }

        // dibujado del press start
        if( a == 0 )
            VDP_drawTextBG( APLAN, "PRESS START", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 20);
        if( a == 30 )
            VDP_drawTextBG( APLAN, "           ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 20);

        // control de boton start
        state = JOY_readJoypad(JOY_1);

        if( state & BUTTON_START )
            exit = start_game = startPressed = 1;


        VDP_waitVSync();
    }

    //////////////////////////////////////////////////////////
    // elejimos numero de jugadores
    VDP_drawTextBG( APLAN, "           ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 20);
    VDP_drawTextBG( APLAN, "ONE PLAYER ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 19);
    VDP_drawTextBG( APLAN, "two players", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 21);
    a = exit = 0;
    start_game = 1;
    while( exit == 0 ){

        a++;
        if( a == 40 )
            a = 0;

        // dibujado del press start
        if( start_game == 1 ){
            if( a == 0 )
                VDP_drawTextBG( APLAN, "ONE PLAYER ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 19);
            if( a == 30 )
                VDP_drawTextBG( APLAN, "           ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 19);
        }
        else{
            if( a == 0 )
                VDP_drawTextBG( APLAN, "TWO PLAYERS", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 21);
            if( a == 30 )
                VDP_drawTextBG( APLAN, "           ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 21);
        }

        // control de boton start
        state = JOY_readJoypad(JOY_1);

        if( state & BUTTON_START && startPressed == 0 )
            exit = 1;
        else if( state & BUTTON_DOWN && start_game == 1 ){
            start_game = 2;
            VDP_drawTextBG( APLAN, "one player ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 19);
            VDP_drawTextBG( APLAN, "TWO PLAYERS", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 21);
        }
        else if( state & BUTTON_UP && start_game == 2 ){
            start_game = 1;
            VDP_drawTextBG( APLAN, "ONE PLAYER ", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 19);
            VDP_drawTextBG( APLAN, "two players", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 14, 21);
        }
        else if( !( state & BUTTON_START) && startPressed == 1 )
            startPressed = 0;


        VDP_waitVSync();
    }

    SND_stopPlay_VGM();
    VDP_fadeOutAll (45, 0);

    return start_game;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void drawTextRecords(const char *str, u16 basetile, u8 flag, u16 x, u16 y){
// dibuja el texto de la pantalla de records
//
//////////////////////////////////////////////////////////////////////////////////////////////////////
void drawTextRecords(const char *str, u16 basetile, u8 flag, u16 x, u16 y){

    u32 len;
    u16 data[40];
    u16 i;

    len = strLen(str);

    for (i = 0; i < len; i++) data[i] = (str[i] - 32 + 64*flag);

    // plano, data, index, baseflags, x, y, w, h
    VDP_setTileMapRectEx( APLAN, data, basetile, TILE_ATTR_FULL(PAL1, 0, 0, 0, 0), x, y, len, 1 );
}


///////////////////////////////////////////////////////////////////////////////////////
//
//  recordsScreen()
//  pantalla de records
//
///////////////////////////////////////////////////////////////////////////////////////
void recordsScreen(){

    u8 a, b, c, d, temp_x;

    // para la pantalla de records
    char *positionTable[4];
    char *numbersTable[10];

	positionTable[0]="ST";
    positionTable[1]="ND";
    positionTable[2]="RD";
    positionTable[3]="TH";

    numbersTable[0]="1";
    numbersTable[1]="2";
    numbersTable[2]="3";
    numbersTable[3]="4";
    numbersTable[4]="5";
    numbersTable[5]="6";
    numbersTable[6]="7";
    numbersTable[7]="8";
    numbersTable[8]="9";
    numbersTable[9]="10";

    // reseteo la pantalla
    VDP_resetSprites();
    VDP_updateSprites();
    VDP_clearPlan(APLAN, 0);
    VDP_clearPlan(BPLAN, 0);

    ////////////////////////////////////////////////////////////////////////
    // cargo la paleta inicial y los tiles de la fuente
    VDP_setPalette(PAL0, palette_black);
    VDP_setPalette(PAL1, palette_black);
    VDP_setPalette(PAL2, palette_black);
    VDP_setPalette(PAL3, palette_black);

    // fuente de paleta rotatoria
    VDP_loadTileData( tiles_records_text, pos_vram_tiles_text, tiles_records_text_size, 1);
    VDP_setPalette(PAL1, pal_records_text);

    // rellena un cuadrado con el logo de 23x1 del tile con paleta 0 en (8,2)
    VDP_loadTileData( tiles_records_title, 1, tiles_records_title_size, 1);
    VDP_fillTileMapRectInc(APLAN, TILE_ATTR_FULL(PAL2, 0, 0, 0, 1), 8, 2, tiles_records_title_size, 1);
    VDP_setPalette(PAL2, pal_records_title);

    // fuente de paleta normal
    VDP_loadTileData( tiles_font_credits, pos_vram_font, tiles_font_credits_size, 1);
    VDP_drawTextBG( APLAN, "RANK     NAME      SCORE   STAGE", TILE_ATTR_FULL(PAL3, 0, 0, 0, 0), 4, 5);
    VDP_setPalette(PAL3, pal_font_credits);

    ///////////////////////////////////
    // ciclo la paleta de los records
    u8 segs, ticks;
    u16 temp_color; // color temporal

    // dibujamos poco a poco y ciclamos la paleta
    a = b = c = d = segs = ticks = 0;
    while(segs < 6){

        // control de salida
        ticks++;
        if( ticks == 60 ){
            ticks = 0;
            segs++;
        }

        // ejecucion con retardo
        c++;
        if( c == 8 ){
            c = 0;

            /////////////////////////////////////////////////
            // ciclamos la PAL1 (16-31)
            temp_color = VDP_getPaletteColor(26);
            for( d = 26; d > 18; d-- )
                VDP_setPaletteColor(d, VDP_getPaletteColor(d-1));

            VDP_setPaletteColor(18, temp_color);

            // cambiamos la PAL2 (32-47)
            if( VDP_getPaletteColor(33) == 0x000E )
               VDP_setPaletteColor(33, 0x0EEE);
            else
                VDP_setPaletteColor(33, 0x000E);


            /////////////////////////////////////////////////
            // dibujo el texto de los records poco a poco
            if( a < 10 ){
                // segun b, dibujo con uno de los 3 tipos de letra disponibles en la fuente

                // posicion
                if( a < 4 )
                    drawTextRecords(positionTable[a], TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 5, 7+2*a);
                else
                    drawTextRecords(positionTable[3], TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 5, 7+2*a);

                drawTextRecords(".", TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 7, 7+2*a);
                if( a != 9 )
                    drawTextRecords(numbersTable[a], TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 4, 7+2*a);
                else
                    drawTextRecords(numbersTable[a], TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 3, 7+2*a);

                // nombre
                drawTextRecords(namesTable[a], TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 10, 7+2*a);

                // puntuacion
                if( pointsTable[a] > 9999 )
                    temp_x = 0;
                else if( pointsTable[a] > 999 )
                    temp_x = 1;
                else if( pointsTable[a] > 99 )
                    temp_x = 2;
                else if( pointsTable[a] > 9 )
                    temp_x = 3;
                else
                    temp_x = 4;

                drawTextRecords("00000", TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 23, 7+2*a);
                drawTextRecords(itoa(pointsTable[a]), TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 23+temp_x, 7+2*a);

                // fase
                drawTextRecords(itoa((stagesTable[a]/5)+1), TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 32, 7+2*a);
                drawTextRecords("-", TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 33, 7+2*a);
                drawTextRecords(itoa(stagesTable[a]%5), TILE_ATTR_FULL(PAL1, 1, 0, 0, pos_vram_tiles_text), b, 34, 7+2*a);

                b++;
                b %= 3;
            }
            a++;
        }

        // sincroniza la pantalla
        VDP_waitVSync();
    }

    VDP_fadeOutAll (60, 0);
}
