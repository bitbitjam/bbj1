#include "main.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//
// int main()
//
////////////////////////////////////////////////////////////////////////////////////////////////
int main(){

    u16 state_p1, state_p2, state_p3, state_p4;     // control del pad

    // contador general (parpadeo pause), ticks, control de la pause,
    // numero de jugadores, modo de juego, tiempo de juego, fase actual,
    // control de salida del bucle del juego
    u8 a, ticks, pause, pause_control, num_players, mode, mins, secs, stage, exit;

    u8 time2flag = 255;                             // tiempo entre banderas

    a = ticks = pause = pause_control = num_players = mode = mins = secs = stage = state_p1 = state_p2 = state_p3 = state_p4 = 0;
    pause_control = 1;

    // control de los hz
    comp60hz = IS_PALSYSTEM ? 0 : 1;

	// control de la interrupcion vertical (actualizacion del PSG y SPRITES)
	//SYS_setInterruptMaskLevel ( 4 );
    SYS_setVIntCallback ( (_voidCallback*) VIntCallback );

    initSRAM();         // inicia la SRAM
    creditsScreen();    // pantalla de creditos

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  BUCLE INFINITO
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while(1){

        //////////////////////////////////////////////////////////////////
        // logos, intro y titulo
        //////////////////////////////////////////////////////////////////
        while( num_players == 0 ){

            recordsScreen();
          draw1985Logo();                       // logo de 1985
            introControl();                       // pantalla de intro

            num_players = titleScreen();          // pantalla de titulo

            /*if( num_players == 0 )                  // si no se elige nada en la pantalla de titulo, salen los records y repetimos
                recordsScreen();                    // pantalla de records
            else{
                num_players = menuScreen( &mode );  // menu de eleccion de modo
                if( mode > 0){                      // vamos al menu del multiplayer si hay mas de un jugador
                    num_players = multiplayerMenuScreen( mode, num_players, &mins, &stage );
                    if( num_players == 0 )
                        mode = 0;
                }
            }*/


//num_players = 2;
stage = 0;
mode = 1;
player[0].team = 0;
player[0].character = 0;
player[1].team = 1;
player[1].character = 1;
        }


        ////////////////////////////////////////////////////////////////////////
        // doy valor inicial a las variables del juego (personajes, disparos...)
        // y carga los tiles de los personajes e inicia sus sprites
        initGame(num_players, mode, stage, &mins, &secs);

        //////////////////////////////////////////////////////////////////
        // bucle de juego
        //////////////////////////////////////////////////////////////////
        exit = 0;
        while( exit == 0 ){

            //////////////////////////////////////////////////////////////////////////
            // LEEMOS los PADS, dependiendo si hay un teamplayer conectado o no
            state_p1 = JOY_readJoypad(JOY_1);
            if( JOY_getPortType(PORT_1) != 16 )
                state_p2 = JOY_readJoypad(JOY_2);
            else{
                state_p2 = JOY_readJoypad(JOY_3);
                state_p3 = JOY_readJoypad(JOY_4);
                state_p4 = JOY_readJoypad(JOY_5);
            }

            ///////////////////////////////////////////////////////////////////////////
            // BUCLE DE JUEGO si no estoy en pausa
            if( pause == 0 ){

                playersControl(ticks, state_p1, state_p2, state_p3, state_p4);      // control de los jugadores
                playersShotsControl(ticks);                                         // control de los disparos
                enemiesControl();

                // control de las banderas SOLO si estamos en el modo 2
                if( mode == 2 )
                    flagsControl( &time2flag, ticks, num_players );

                // control del tiempo
                exit = timeControl( &ticks, &mins, &secs );

                // salimos del bucle si se ha agotado
                if( exit ){
                    /*if( scoreScreen(num_players) == 0 ){
                        num_players =  multiplayerMenuScreen( mode, num_players, &mins, &stage );
                        if( num_players == 0 )
                            mode = 0;
                        else*/
                            initGame(num_players, mode, stage, &mins, &secs);
                   /* }
                    else
                        num_players = mode = 0;*/
                }
            }
            ///////////////////////////////////////////////////////////////////////////////////////
            // en PAUSA sólo mostramos el mensaje intermitente de pausa
            else{

                a++;
                if( a == 10 )	a = 0;

                if( a < 5 )
                    VDP_drawTextBG( APLAN, " P1 PAUSE  P2 PAUSE  P3 PAUSE  P4 PAUSE", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 0, 27);
                else
                    VDP_drawTextBG( APLAN, " P1        P2        P3        P4      ", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 0, 27);
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // control de la PAUSA, necesito 2 variables para controlar que suelte el boton antes de volver al bucle de juego
            if( state_p1 & BUTTON_START ){

                // se ha pulsado start y no estaba en pausa, entro en pausa
                if( pause_control == 0 && pause == 0 ){

                    pause = 1;
                    //VGM_stop();
                }

                // se ha pulsado start, habiendose soltado antes, y como estoy en pausa, salgo de la pausa
                if( pause_control == 1 && pause == 1 ){

                    pause = 0;
                    pause_control = 2;

                    // redibujamos las puntuaciones tras la pausa
                    VDP_drawTextBG( APLAN, " P1 00000  P2 00000  P3 00000  P4 00000", TILE_ATTR_FULL(PAL0, 0, 0, 0, 0), 0, 27);
                    updatePlayerScore( 0, 255 ); updatePlayerScore( 1, 255 ); updatePlayerScore( 2, 255 ); updatePlayerScore( 3, 255 );

                    //VGM_start();
                }
            }
            else{
                // si estoy en pausa y he soltado el start
                if( pause == 1 )	pause_control = 1;

                // no estoy en pausa y se ha soltado el start
                if( pause == 0 )	pause_control = 0;

            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // sincronizo la pantalla con el barrido (en la interrupcion se actualiza PSG y SPRITES)
            VDP_waitVSync();
        }
    }

    return (0);
}





