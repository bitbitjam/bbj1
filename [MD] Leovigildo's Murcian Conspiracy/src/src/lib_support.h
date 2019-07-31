#ifndef _LIBSUPPORT_H_
#define _LIBSUPPORT_H_

#define updateVScroll(ppos)                                         \
{                                                                   \
    *((volatile u16*)GFX_CTRL_PORT) = 0x4000;   			        \
    *((volatile u16*)GFX_DATA_PORT) = (ppos);                       \
}

// SRAM
#define SRAM_CONTROL    0xA130F1
#define SRAM_BASE       0x200001

// ITOA
#define INT_DIGITS 19	// enough for 64 bit integer

typedef unsigned long size_t;

_voidCallback *VIntCallback();

void SRAM_enable();     // Enable SRAM in Read Write mode.
void SRAM_enableRO();	// Enable SRAM in Read Only mode.
void SRAM_disable();	// Disable SRAM.
u8 SRAM_readByte(u32 offset);	            // Read a byte from the SRAM.
void SRAM_writeByte(u32 offset, u8 val);	// Write a byte to the SRAM.

extern u16 SRAM_readWord(u32 offset);	// Read a word from the SRAM.
extern u32 SRAM_readLong(u32 offset);	// Read a long from the SRAM.
extern void SRAM_writeWord(u32 offset, u16 val);  // Write a word to the SRAM.
extern void SRAM_writeLong(u32 offset, u32 val); // Write a long to the SRAM.


extern u16 vscroll_a;
extern u8 start_line;

extern void bgAsmHIntCB(void);

char *strncpy(char *dst, const char *src, size_t n);
char *itoa( int i );
void str_cat(char *dest, const char *src);

void VDP_drawNumberBG(u16 plan, int num, u16 flags, u16 x, u16 y);
void VDP_setTileMapRectMirrorEx( u16 plano, const u16 *map, u16 baseindex, u16 baseflags, u16 x, u16 y, u16 width, u16 height );
void setHorizontalScroll(u16 plan, u16 line, u16 value);
unsigned long strLen(const char *str);

extern const u8 sinus_table[50];
extern const u16 palette_white[16];

#endif
