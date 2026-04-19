#include "quick.h"

#include "../array.h"

int8_t partition(uint8_t start, uint8_t end) {
	uint8_t i = start - 1;
	uint8_t j = end + 1;

	while (1) {
		do { ++i; } while (arr_compare_indices(false, i, start) < 0);
		do { --j; } while (arr_compare_indices(false, j, start) > 0);

		if (i >= j) return j;

		arr_swap(false, i, j);
	}
}

void quick_sort_main(uint8_t start, uint8_t end) {
	uint8_t p;

	while (start < 128 && end < 128 && start < end) {
		p = partition(start, end);

		if ((p - start) < (end - p)) {
			quick_sort_main(start, p);
			start = p + 1;
		} else {
			quick_sort_main(p + 1, end);
			end = p;
		}
	}
}

void quick_sort(uint8_t len) {
	quick_sort_main(0, len - 1);
}
