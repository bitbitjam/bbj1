#ifndef __WYZPLAYER_H__
#define __WYZPLAYER_H__

extern void  			msx_WyzLoadSong(unsigned char numero);
extern void     		msx_WyzStartEffect(unsigned char canal, unsigned char efecto);
extern void    			msx_WyzSetPlayerOn(void);
extern void     		msx_WyzSetPlayerOff(void);
extern void  			msx_WyzConfigurePlayer(unsigned char valor);
extern unsigned char 	msx_WyzTestPlayer(void);
extern void 			msx_WyzInitPlayer(int *sonidos, int *pautas, int *efectos, int *canciones);
extern void				msx_WyzSetTempo(unsigned char tempo);

#endif
