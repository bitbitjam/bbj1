#ifndef _SCREEN_H_
#define _SCREEN_H_

void scr_setScreenBuffers(char main_scr, char buffer_scr);
char scr_swapScreenBuffers();
void scr_setFBScreenPage(char page, char offset);
void scr_waitVSYNC();
void scr_putSprite8x16_buffer0100(unsigned char *destiny, unsigned char *sprite);

#endif