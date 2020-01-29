/* 2020 David DiPaola. Licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/). */

#include <stdint.h>

#include <stdio.h>

#include "../vincent.h"
size_t vincent_data_length = sizeof(vincent_data) / sizeof(*vincent_data);

void
print_info(uint8_t ch) {
	/* the Vincent font is glyphs 0x01-0x7F of CP437 */
	if (ch > 0x7F) {
		printf("WAT");
	}
	else if (ch == 0x7F) {
		printf("house (U+2302, CP437+7F)");
	}
	else if (ch >= 0x20) {
		printf("'%c'", (char)ch);
	}
	else if (ch == 0x1F) {
		printf("black down-pointing triangle (U+25BC, CP437+1F)");
	}
	else if (ch == 0x1E) {
		printf("black up-pointing triangle (U+25B2, CP437+1E)");
	}
	else if (ch == 0x1D) {
		printf("left right arrow (U+2194, CP437+1D)");
	}
	else if (ch == 0x1C) {
		printf("right angle (U+221F, CP437+1C)");
	}
	else if (ch == 0x1B) {
		printf("leftwards arrow (U+2190, CP437+1B)");
	}
	else if (ch == 0x1A) {
		printf("rightwards arrow (U+2192, CP437+1A)");
	}
	else if (ch == 0x19) {
		printf("downwards arrow (U+2193, CP437+19)");
	}
	else if (ch == 0x18) {
		printf("upwards arrow (U+2191, CP437+18)");
	}
	else if (ch == 0x17) {
		printf("up down arrow with base (U+21A8, CP437+17)");
	}
	else if (ch == 0x16) {
		printf("black rectangle (U+25AC, CP437+16)");
	}
	else if (ch == 0x15) {
		printf("section sign (U+00A7, CP437+15)");
	}
	else if (ch == 0x14) {
		printf("pilcrow (U+00B6, CP437+14)");
	}
	else if (ch == 0x13) {
		printf("double exclamation mark (U+203C, CP437+13)");
	}
	else if (ch == 0x12) {
		printf("up down arrow (U+2195, CP437+12)");
	}
	else if (ch == 0x11) {
		printf("black left-pointing pointer (U+25C4, CP437+11)");
	}
	else if (ch == 0x10) {
		printf("black right-pointing pointer (U+25BA, CP437+10)");
	}
	else if (ch == 0x0F) {
		printf("white sun with rays (U+263C, CP437+0F)");
	}
	else if (ch == 0x0E) {
		printf("beamed eighth notes (U+266B, CP437+0E)");
	}
	else if (ch == 0x0D) {
		printf("eighth note (U+266A, CP437+0D)");
	}
	else if (ch == 0x0C) {
		printf("female sign (U+2640, CP437+0C)");
	}
	else if (ch == 0x0B) {
		printf("male sign (U+2642, CP437+0B)");
	}
	else if (ch == 0x0A) {
		printf("inverse white circle (U+25D9, CP437+0A)");
	}
	else if (ch == 0x09) {
		printf("white circle (U+25CB, CP437+09)");
	}
	else if (ch == 0x08) {
		printf("inverse bullet (U+25D8, CP437+08)");
	}
	else if (ch == 0x07) {
		printf("bullet (U+2022, CP437+07)");
	}
	else if (ch == 0x06) {
		printf("black spade suit (U+2660, CP437+06)");
	}
	else if (ch == 0x05) {
		printf("black club suit (U+2663, CP437+05)");
	}
	else if (ch == 0x04) {
		printf("black diamond suit (U+2666, CP437+04)");
	}
	else if (ch == 0x03) {
		printf("black heart suit (U+2665, CP437+03)");
	}
	else if (ch == 0x02) {
		printf("black smiling face (U+263B, CP437+02)");
	}
	else if (ch == 0x01) {
		printf("white smiling face (U+263A, CP437+01)");
	}
	else if (ch == 0x00) {
		printf("blank (NUL)");
	}
}

void
print_horiz(int xbm) {
	printf(
		"#define vh_width 8" "\n"
		"#define vh_height 1024" "\n"
		"static unsigned char vh_bits[] = {" "\n"
	);

	for (size_t i=0; i<vincent_data_length; i++) {
		printf("\t" "/* 0x%02zX -- ", i);
		print_info(i);
		printf(" */" "\n");

		printf("\t");

		uint8_t * row = vincent_data + i;
		uint8_t   out[8];
		for (size_t j=0; j<8; j++) {
			if (xbm) {
				out[j] = 
					(((row[0]>>(7-j))&1) << 7) |
					(((row[1]>>(7-j))&1) << 6) |
					(((row[2]>>(7-j))&1) << 5) |
					(((row[3]>>(7-j))&1) << 4) |
					(((row[4]>>(7-j))&1) << 3) |
					(((row[5]>>(7-j))&1) << 2) |
					(((row[6]>>(7-j))&1) << 1) |
					(((row[7]>>(7-j))&1) << 0)
				;
			}
			else {  /* ST7565 */
				out[j] = 
					(((row[7]>>(7-j))&1) << 7) |
					(((row[6]>>(7-j))&1) << 6) |
					(((row[5]>>(7-j))&1) << 5) |
					(((row[4]>>(7-j))&1) << 4) |
					(((row[3]>>(7-j))&1) << 3) |
					(((row[2]>>(7-j))&1) << 2) |
					(((row[1]>>(7-j))&1) << 1) |
					(((row[0]>>(7-j))&1) << 0)
				;
			}
		}
		for (size_t j=0; j<8; j++) {
			printf("0x%02X, ", out[j]);
		}

		printf("\n");
	}

	printf("};" "\n");
}

void
print_gb(void) {
	for (size_t i=0; i<vincent_data_length; i++) {
		printf("\t" "/* 0x%02zX -- ", i);
		print_info(i);
		printf(" */" "\n");

		uint8_t * glyph = vincent_data + i;
		for (size_t row=0; row<8; row++) {
			for (size_t j=0; j<2; j++) {  /* GameBoy tile format is 2bpp */
				printf("\t" "%%");
				for (ssize_t px=7; px>=0; px--) {
					printf("%i", (glyph[row]>>px)&1);
				}
				printf("\n");
			}
		}
	}
}

int
main() {
	//print_horiz(0);
	print_gb();
}

