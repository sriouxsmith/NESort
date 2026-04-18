#include "comb.h"

#include "../array.h"

void comb_sort(uint8_t len) {
	uint8_t i, k;
	bool swapped = true;
	uint32_t gap = len * 256;

	while (gap > 256 || swapped) {
		gap = gap * 10 / 13;

		if (gap < 256) {
			gap = 256;
		}

		k = gap / 256;
		swapped = false;
		for (i = 0; i + k < len; ++i) {
			if (arr_compare_indices(false, i, i + k) > 0) {
				arr_swap(false, i, i + k);
				swapped = true;
			}
		}
	}
}
