#include "fisheryates.h"

#include "../array.h"

void fisheryates_shuffle(uint8_t len) {
	uint8_t i, j;

	for (i = 0; i < len; ++i) {
		j = nes_get_rand_bounded(i + 1);
		arr_swap(false, i, j);
	}
}
