/*
 * makerom.c
 *
 *  Created on: Apr 25, 2020
 *      Author: pedward
 */

#include <stdio.h>

#include "text.xbm"
#include "chars.h"

int xbm_char_height=18;
int rom_glyph_half=8;
int baseline_offset=3;

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int main(void)
{
	FILE *rom,*out;
	char buffer[4096];
	char *p,n;
	int c,i,d;

	rom = fopen("HERCULES.bin","r");
	out = fopen("combined.rom","w");

	fread(buffer,4096,1,rom);
	fwrite(buffer,2048,1,out);
	fwrite(buffer,2048,1,out);

	fread(buffer,4096,1,rom);
	fwrite(buffer,2048,1,out);
	fwrite(buffer,2048,1,out);

	fclose(rom);

	p=charlist;

	while(*p) {
		c=*p;
		d=(c-'!')*xbm_char_height;

		fseek(out, (c*rom_glyph_half)+2048,SEEK_SET);
		for(i=0;i<rom_glyph_half;i++) {
			n=reverse(text_bits[d+i+baseline_offset]);
			fwrite(&n,1,1,out);
		}
		fseek(out, (c*rom_glyph_half)+2048+4096,SEEK_SET);
		for(i=rom_glyph_half;i<2*rom_glyph_half;i++) {
			n=reverse(text_bits[d+i+baseline_offset]);
			fwrite(&n,1,1,out);
		}
		p++;
	}

	fclose(out);

	return 0;
}
