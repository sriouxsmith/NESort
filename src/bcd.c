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

uint8_t bcd_render_as_spr(uint8_t x, uint8_t y, uint8_t index,
		uint8_t len, uint8_t *bcd)
{
	static uint8_t *bcd_working;

	static uint8_t new_x;
	static uint8_t new_index;
	static uint8_t new_len;
	static uint8_t i;

	bcd_working = bcd;
	for (new_len = len; new_len > 1 && !bcd_working[new_len - 1]; --new_len);

	new_x = 8 * (new_len - 1) + x;
	new_index = index;

	for (i = 0; i < new_len; ++i) {
		new_index = nes_put_spr(new_x, y, bcd[i] + 0x30, 0, new_index);
		new_x -= 8;
	}

	return new_index;
}
