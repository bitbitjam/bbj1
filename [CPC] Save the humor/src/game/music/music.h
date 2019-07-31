#ifndef _MUSIC_H_
#define _MUSIC_H_

/// DEFINICION DE ESTRUCTURAS PARA LAS MUSICAS ( No tocar )
///
typedef struct MusicTable {
	int *effect_table;
	int *song_table;
	int *rule_table;
	int *sound_table;
} TMusicTable;

extern TMusicTable GLOBAL_MUSICS_TABLE[];

void music_reproducir_cancion(unsigned char song);
void music_pausar();
void music_continuar();

#endif