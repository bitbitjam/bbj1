#include "define.h"

#define Keyb54321 0xf7
#define KeybTREWQ 0xfb
#define KeybGFDSA 0xfd
#define KeybVCXZc 0xfe
#define Keyb67890 0xef
#define KeybYUIOP 0xdf
#define KeybHJKLe 0xbf
#define KeybBNMs_ 0x7f

#define tilepaint(from_x, from_y, to_x, to_y) *repaint= from_x|from_y<<4|to_x<<8|to_y<<12

#define SILENCIA_PLAYER		0xC062
#define MACHINE_PTR         0xFFF6

#define FASE_RUNNING 1
#define FASE_STOPPED 0

#define MACHINE_48K  0xC9
#define MACHINE_128K 0xC3


unsigned char fase_status = FASE_STOPPED;
unsigned char * type_machine = MACHINE_PTR;


#define FALSE 0
#define TRUE 1

typedef struct {
  unsigned char n; // n frame
  unsigned char x;
  unsigned char y;
  unsigned char f; // extra - para uso propio
} SPRITE;

typedef struct {
  unsigned char x;
  unsigned char y;
} BULLET;

SPRITE *sprites= 0x5b00;
BULLET *bullets= 0x5b30;
unsigned char *ptr_tmp = 0;
unsigned char *ptr_jmp = 0;
unsigned char *tiles= 0x5b40;
unsigned char *screen= 0x5c00;
unsigned char *shadow= 0x5c01;
unsigned int *repaint= 0x5c02;
unsigned int *drwout= 0x5c06;
unsigned char *zxmem= 0;


unsigned char i, j, mapx, mapy, spacepressed, dirbul[4], num_bullets;
unsigned char tmpx, tmpy;
short x, vx, ax, y, vy, ay;

char __FASTCALL__ inKey ( unsigned char row ){
    #asm
        ld      b, l
        ld      c, $fe
        in      a, (c)
        cpl
        ld      l, a
    #endasm
}

void __FASTCALL__ Pause ( unsigned int msecs ){
    #asm
loop1:  
        ld      bc, 21
loop2:  djnz    loop2
        dec     c
        jr      nz, loop2

        dec     hl
        ld      a, l
        or      h
        jr      nz, loop1
    #endasm
}

void __CALLEE__ Dzx7b ( unsigned int source, unsigned int addr ){
    #asm
        pop     af
        pop     de
        pop     hl
        push    af
        jp      dzx7a
    #endasm
}



void fase_init()
{
    asm("call    0xfffc");
    fase_status = FASE_RUNNING;

    // active AY player on 128K machines
    if (*type_machine == MACHINE_128K)
    {
        #asm
        ld      bc, $7ffd
        ld      a, $11
        out     (c), a
        xor     a
        call    $c087
        ld      bc, $7ffd
        ld      a, $10
        out     (c), a
        #endasm
    }
}

void fase_stop()
{
    // active AY player on 128K machines
    if (*type_machine == MACHINE_128K)
    {
        #asm
        ld      bc, $7ffd
        ld      a, $11
        out     (c), a
        call    $c062
        ld      bc, $7ffd
        ld      a, $10
        out     (c), a
        #endasm
    }

    asm("call    0xfff6");
    fase_status = FASE_STOPPED;
}

#define fase_dwframe() asm("call 0xfff9")


