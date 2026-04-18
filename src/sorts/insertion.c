#include "insertion.h"

#include "../array.h"

void insertion_sort(uint8_t len) {
	uint8_t i, j;

	for (j = 1; j < len; ++j) {
		for (i = j - 1; i < len; --i) {
			if (arr_compare_indices(false, i, i + 1) <= 0)
				break;
			arr_swap(false, i, i + 1);
		}
	}
}
