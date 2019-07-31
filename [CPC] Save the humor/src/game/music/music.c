#include "music.h"
#include <cpcwyzlib.h>

unsigned char g_music_playing = 0;

void music_reproducir_cancion(unsigned char song) {
	// Pausar música si estaba reproduciendo
	if (g_music_playing)
		music_pausar();
		
	// Iniciar el player y comenzar reproducción
	cpc_WyzInitPlayer(GLOBAL_MUSICS_TABLE[song].sound_table,  
						GLOBAL_MUSICS_TABLE[song].rule_table,
						GLOBAL_MUSICS_TABLE[song].effect_table, 
						GLOBAL_MUSICS_TABLE[song].song_table);
	cpc_WyzLoadSong(0);
	cpc_WyzSetPlayerOn();
	
	g_music_playing = 1;
}

void music_pausar() {
	if (g_music_playing)
		cpc_WyzSetPlayerOff();
	g_music_playing = 0;
}

void music_continuar() {
	if (!g_music_playing)
		cpc_WyzSetPlayerOn();
	g_music_playing = 1;
}

