#include "counting.h"

#include "../array.h"

void counting_sort(uint8_t len) {
	uint8_t i;

	for (i = 0; i < len; ++i) {
		uint8_t count_i = arr_read(false, i);
		uint8_t count = arr_read(true, count_i - 1) + 1;

		arr_play(count_i);
		arr_write(true, count_i - 1, count);
	}

	for (i = 1; i < ARR_MAX_LEN; ++i)
		arr_write(true, i, arr_read(true, i) + arr_read(true, i - 1));

	for (i = len - 1; i < 128; --i) {
		uint8_t count_i = arr_read(false, i);
		uint8_t count = arr_read(true, count_i - 1) - 1;

		arr_play(count_i);
		arr_write(true, count_i - 1, count);
		arr_ext0[count] = count_i;
	}

	for (i = 0; i < len; ++i) {
		arr_play(arr_ext0[i]);
		arr_push_blank();
		arr_write(false, i, arr_ext0[i]);
	}
}
