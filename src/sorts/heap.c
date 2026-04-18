#include "heap.h"

#include "../array.h"

void heap_sort(uint8_t len) {
	uint8_t root;
	uint8_t child;
	uint8_t start = len / 2;
	uint8_t end = len;

	while (end > 1) {
		if (start > 0) --start;
		else arr_swap(false, --end, 0);

		root = start;
		while (2 * root + 1 < end) {
			child = 2 * root + 1;
			if (child + 1 < end
				&& arr_compare_indices(false, child, child + 1) < 0)
			{
				++child;
			}

			if (arr_compare_indices(false, root, child) < 0) {
				arr_swap(false, root, child);
				root = child;
			} else break;
		}
	}
}
