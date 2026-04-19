#include "shaker.h"

#include "../array.h"

void shaker_sort(uint8_t len) {
	uint8_t i;
	uint8_t start = 0;
	uint8_t end = len - 1;
	bool swapped = true;

	while (swapped) {
		swapped = false;

		for (i = start; i < end; ++i) {
			if (arr_compare_indices(false, i, i + 1) > 0) {
				swapped = true;
				arr_swap(false, i, i + 1);
			}
		}

		if (!swapped) break;

		swapped = false;
		--end;
		for (i = end; i > start; --i) {
			if (arr_compare_indices(false, i - 1, i) > 0) {
				swapped = true;
				arr_swap(false, i - 1, i);
			}
		}

		++start;
	}
}
