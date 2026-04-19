#include "bogo.h"

#include "../array.h"

void bogo_sort(uint8_t len) {
	uint8_t i, j;

	while (true) {
		bool sorted = true;

		for (i = 0; i < len - 1; ++i) {
			if (arr_compare_indices(false, i, i + 1) >= 0) {
				sorted = false;
				break;
			}
		}

		if (sorted) return;

		for (i = 0; i < len; ++i) {
			j = nes_get_rand_bounded(i + 1);
			arr_swap(false, i, j);
		}
	}
}
