/*
 * makerom.c
 *
 *  Created on: Apr 25, 2020
 *      Author: pedward
 */

#include "comic_sans.xbm"
#include <stdio.h>

char *charlist = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNMOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

int xbm_char_height=18;
int rom_char_height=16;

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
		d=(c-'!')*18;

		fseek(out, (c*8)+2048,SEEK_SET);
		for(i=0;i<8;i++) {
			n=reverse(comic_sans_bits[d+i]);
			fwrite(&n,1,1,out);
		}
		fseek(out, (c*8)+2048+4096,SEEK_SET);
		for(i=8;i<16;i++) {
			n=reverse(comic_sans_bits[d+i]);
			fwrite(&n,1,1,out);
		}
		p++;
	}

	fclose(out);

	return 0;
}
