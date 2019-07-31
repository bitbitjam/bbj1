#include "genesis.h"
#include "main.h"

// tabla de seno para el logo de la pantalla de titulo
const u8 sinus_table[50] = {
	18,  20,  22,  24,  26,  28,  30,  32,
	34,  34,  36,  36,  36,  36,  36,  36,
	34,  34,  32,  30,  28,  26,  24,  22,
	20,  18,  16,  14,  12,  10,  8,  6,
	4,  2,  2,  0,  0,  0,  0,  0,
	0,  2,  2,  4,  6,  8,  10,  12,
	14,  16
};

// paleta blanca
const u16 palette_white[16] = {
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,

    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF
};

////////////////////////////////////////////////////////////////////////////////////////////////
//
// _voidCallback *VIntCallback()
// control de la interrupcion vertical (actualizacion del PSG)
//
////////////////////////////////////////////////////////////////////////////////////////////////
_voidCallback *VIntCallback(){

	if ( !comp60hz || ( comp60hz && ( vtimer % 6 ) ) ){
		psgFxFrame();
        VDP_updateSprites();    // actualizo los sprites
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////
// FUNCIONES PARA LEER Y ESCRIBIR EN SRAM
//////////////////////////////////////////////////////////////////////////////////////////
void SRAM_enable(){    *(vu8*)SRAM_CONTROL = 1; }

void SRAM_enableRO(){    *(vu8*)SRAM_CONTROL = 3; }

void SRAM_disable(){    *(vu8*)SRAM_CONTROL = 0; }

u8 SRAM_readByte(u32 offset){    return *(vu8*)(SRAM_BASE + (offset * 2)); }

void SRAM_writeByte(u32 offset, u8 val) {    *(vu8*)(SRAM_BASE + (offset * 2)) = val; }


////////////////////////////////////////////////////////////////////////////////////
//
//  char *strncpy(char *dst, CONST char *src, size_t n){
//  copia una cadena origen en destino
//
////////////////////////////////////////////////////////////////////////////////////
char *strncpy(char *dst, const char *src, size_t n){

    if (n != 0) {
        char *d = dst;
        const char *s = src;

        do{
            if ((*d++ = *s++) == 0) {
                // NUL pad the remaining n-1 bytes
                while (--n) {
                    *d++ = 0;
                }
                break;
            }
        }while (--n);
     }
     return dst;
}


////////////////////////////////////////////////////////////////////////////////////
//
//  char *itoa(i)
//  convierte un entero en string
//
////////////////////////////////////////////////////////////////////////////////////
char *itoa( int i ){

    /* Room for INT_DIGITS digits, - and '\0' */
    static char buf[INT_DIGITS + 2];
    char *p = buf + INT_DIGITS + 1;	/* points to terminating '\0' */

    if(i >= 0){
        do{
            *--p = '0' + (i % 10);
            i /= 10;
        }while (i != 0);

        return p;
    }
    else{			/* i < 0 */
        do{
            *--p = '0' - (i % 10);
            i /= 10;
        }while (i != 0);

        *--p = '-';
    }

    return p;
}


////////////////////////////////////////////////////////////////////////////////////
//
//  void str_cat(char *dest, const char *src){
//  copia una cadena origen en destino
//
////////////////////////////////////////////////////////////////////////////////////
void str_cat(char *dest, const char *src){

    while (*dest!= '\0')
        *dest++ ;
    do
    {
        *dest++ = *src++;
    }
    while (*src != '\0') ;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  void bgAsmHIntCB(void)
//  efecto de scroll de persiana por Doragasu
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bgAsmHIntCB(void)
{
    if (start_line)
        updateVScroll(vscroll_a + start_line--);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  void VDP_setTileMapRectMirrorEx( u16 plano, const u16 *map, u16 baseindex, u16 baseflags, u16 x, u16 y, u16 width, u16 height ){
//  dibujo el mapa de tiles en el plano indicado, x,y, ancho, alto, tile inicial y paleta
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VDP_setTileMapRectMirrorEx( u16 plano, const u16 *map, u16 baseindex, u16 baseflags, u16 x, u16 y, u16 width, u16 height ){

    vu32 *plctrl;
    vu16 *pwdata;
    u32 addr;
    u32 planwidth;
    u16 j;
    u16 temp_height = 0;

    VDP_setAutoInc(2);

    // puntero al puerto del vdp
    plctrl = (u32 *) GFX_CTRL_PORT;
    pwdata = (u16 *) GFX_DATA_PORT;

    planwidth = VDP_getPlanWidth();;
    addr = plano + (2 * (x + (planwidth * y)));

    while(temp_height < height){

        *plctrl = GFX_WRITE_VRAM_ADDR(addr);

        j = width;
        while (j--){
            *pwdata = baseflags | (map[j + temp_height*width] + baseindex);
            //*pwdata = *mapa++ + tile_inicial;
        }

        temp_height++;

		addr += planwidth * 2;
	}
}


//////////////////////////////////////////////////////////////////////////////////////
//
// void VDP_drawNumberBG(u16 plan, int num, u16 flags, u16 x, u16 y){
// dibuja el numero num, en el plano plan, con las flags pasadas, en x, y
//
//////////////////////////////////////////////////////////////////////////////////////
void VDP_drawNumberBG(u16 plan, int num, u16 flags, u16 x, u16 y){

    char str[16];

    intToStr(num, str, 1);

    VDP_drawTextBG( plan, str, flags, x, y);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// void setHorizontalScroll(u16 plan, u16 line, u16 value){
// hace scroll del plano en horizontal
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setHorizontalScroll(u16 plan, u16 line, u16 value){

    vu16 *pw;
    vu32 *pl;
    u16 addr;

    // puntero al puerto vdp
    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

    addr = HSCRL + ((line & 0xFF) * 4);
    if (plan == BPLAN) addr += 2;

    *pl = GFX_WRITE_VRAM_ADDR(addr);
    *pw = value;
}


////////////////////////////////////////////////////////////////
//
// u32 strLen_(const char *str){
// devuelve la longitud de la cadena
//
////////////////////////////////////////////////////////////////
unsigned long strLen(const char *str){

    const char *src;

    src = str;

    while (*src++);

    return (src - str) - 1;
}
