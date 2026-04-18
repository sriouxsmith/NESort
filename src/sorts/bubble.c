#include "bubble.h"

#include "../array.h"

void bubble_sort(uint8_t len) {
	bool swapped;

	uint8_t i, j;

	for (j = len - 1; j < len; --j) {
		swapped = false;

		for (i = 0; i < j; ++i) {
			if (arr_compare_indices(false, i, i + 1) > 0) {
				arr_swap(false, i, i + 1);
				swapped = true;
			}
		}

		if (!swapped) break;
	}
}
