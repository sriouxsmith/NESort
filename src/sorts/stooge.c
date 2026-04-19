#include "stooge.h"

#include "../array.h"

void stooge_sort_main(uint8_t start, uint8_t end) {
	if (start >= end)
		return;

	if (arr_compare_indices(false, start, end) > 0)
		arr_swap(false, start, end);

	if (end - start + 1 > 2) {
		uint8_t t = (end - start + 1) / 3;

		stooge_sort_main(start, end - t);
		stooge_sort_main(start + t, end);
		stooge_sort_main(start, end - t);
	}
}

void stooge_sort(uint8_t len) {
	stooge_sort_main(0, len - 1);
}
