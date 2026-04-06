#include "bcd.h"

void bcd_from_binary(uint8_t value, uint8_t *bcd_out) {
	static uint8_t value_working;
	static uint8_t *bcd;
	static uint8_t i;

	value_working = value;
	bcd = bcd_out;

	bcd[0] = 0;
	bcd[1] = 0;
	bcd[2] = 0;

	for (i = 0; i < 8; i++) {
		if (bcd[0] >= 5) bcd[0] += 3;
		if (bcd[1] >= 5) bcd[1] += 3;
		if (bcd[2] >= 5) bcd[2] += 3;

		bcd[2] = (bcd[2] << 1) | (bcd[1] >> 3);
		bcd[1] = ((bcd[1] << 1) & 0xf) | (bcd[0] >> 3);
		bcd[0] = ((bcd[0] << 1) & 0xf) | ((value_working & 0x80) >> 7);

		value_working <<= 1;
	}

	bcd[0] &= 0x0f;
	bcd[1] &= 0x0f;
	bcd[2] &= 0x0f;
}
