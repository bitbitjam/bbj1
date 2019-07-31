#include "sprites.h"

unsigned char spr_flipPixels0(unsigned char byte) {
	unsigned char even = byte & 0x55;
	unsigned char odd  = byte & 0xAA;
	return (even << 1) | (odd >> 1);
}
void spr_flipHorizontalMask(unsigned char* sprite) {
	//"MIERDA";
	unsigned char w = sprite[0] << 1;
	unsigned char h = sprite[1];
	sprite += 2;
	while (h--) {
		unsigned char w2 = w >> 2;	
		unsigned char d = w - 2;
		while (w2--) {
			unsigned char aux  = sprite[0];
			unsigned char aux2 = sprite[1];
			// We ought to swap internal pixels, not only bytes
			sprite[0] = spr_flipPixels0(sprite[d]);
			sprite[1] = spr_flipPixels0(sprite[d + 1]);
			sprite[d] = spr_flipPixels0(aux);
			sprite[d + 1] = spr_flipPixels0(aux2);
			sprite += 2;
			d -= 4;
		}
		sprite += w >> 1;
	}
}