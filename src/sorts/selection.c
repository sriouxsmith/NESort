#include "selection.h"

#include "../array.h"

void selection_sort(uint8_t len) {
	uint8_t i, j;

	for (i = 0; i < len - 1; ++i) {
		uint8_t min = i;

		for (j = i + 1; j < len; ++j) {
			if (arr_compare_indices(false, j, min) < 0)
				min = j;
		}

		arr_swap(false, i, min);
	}
}
