////////////////////////////////////////////////////////////////////////////////////////////
//// ACC2 SONG
////
void the_ACC2_music() {  
__asm

.globl _SONG_TABLE_ACC2
_SONG_TABLE_ACC2:
    .DW _SONG_ACC2

.globl _EFFECT_TABLE_ACC2
_EFFECT_TABLE_ACC2:

.globl _RULE_TABLE_ACC2
_RULE_TABLE_ACC2:
    .DW P0, P1
	P0: .DB 11,0,10,0,9,0,8,0,129
	P1: .DB 8,0,74,0,11,0,43,0,10,0,72,0,8,0,40,0,8,0,132

.globl _SOUND_TABLE_ACC2
_SOUND_TABLE_ACC2:
    .DW 0

_SONG_ACC2:
	.DB 0x08, 0x07, 0x00, 0x00, 0x3f, 0x01, 0x7b, 0x7e, 0x76, 0x7e, 0x79, 0x7e, 0x74, 0x7e, 0x32, 0x34, 0x76, 0x6f, 0x7e, 0x72, 0x7e, 0x74, 0x7e, 0x72, 0x7e, 0x74, 0x76, 0x7b, 0x7e, 0x76, 0x7e, 0x79, 0x7e, 0x74, 0x7e, 0x32, 0x34, 0x76, 0x6f, 0x7e, 0x72, 0x7e, 0x74, 0x7e, 0x72, 0x7e, 0x74, 0x76, 0x6f, 0x7e, 0x71, 0x7e, 0x72, 0x7e, 0x31, 0x72, 0x71, 0x72, 0x34, 0x76, 0x77, 0x34, 0x76, 0x7e, 0x35, 0x36, 0x35, 0x36, 0x35, 0x76, 0x6f, 0x7e, 0x71, 0x7e, 0x72, 0x7e, 0x31, 0x72, 0x71, 0x72, 0x34, 0x76, 0x77, 0x34, 0x76, 0x7e, 0x35, 0x36, 0x35, 0x36, 0x35, 0x76, 0x00, 0xc1, 0x00, 0x3f, 0x00, 0x23, 0x01, 0x1e, 0x01, 0x21, 0x23, 0x01, 0x17, 0x23, 0x01, 0x1e, 0x01, 0x21, 0x23, 0x01, 0x17, 0x21, 0x01, 0x1c, 0x01, 0x1f, 0x21, 0x01, 0x15, 0x21, 0x01, 0x1c, 0x01, 0x1f, 0x21, 0x01, 0x15, 0x23, 0x01, 0x1e, 0x01, 0x21, 0x23, 0x01, 0x17, 0x23, 0x01, 0x1e, 0x01, 0x21, 0x23, 0x01, 0x17, 0x21, 0x01, 0x1c, 0x01, 0x1f, 0x21, 0x01, 0x15, 0x21, 0x01, 0x1c, 0x01, 0x1f, 0x21, 0x01, 0x15, 0x1f, 0x01, 0x1a, 0x01, 0x1d, 0x1f, 0x01, 0x13, 0x1f, 0x01, 0x1a, 0x01, 0x1d, 0x1f, 0x01, 0x13, 0x1e, 0x01, 0x19, 0x01, 0x1c, 0x1e, 0x01, 0x52, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x1f, 0x01, 0x1a, 0x01, 0x1d, 0x1f, 0x01, 0x13, 0x1f, 0x01, 0x1a, 0x01, 0x1d, 0x1f, 0x01, 0x13, 0x1e, 0x01, 0x19, 0x01, 0x1c, 0x1e, 0x01, 0x52, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x00, 0xc1, 0x00, 0x00
__endasm;
}
