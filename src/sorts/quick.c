#include "quick.h"

#include "../array.h"

static int8_t partition(uint8_t start, uint8_t end) {
	uint8_t i = start - 1;
	uint8_t j = end + 1;
	uint8_t e = arr_read(false, (start + end) / 2);

	while (1) {
		do { ++i; } while (arr_compare(arr_read(false, i), e) < 0);
		do { --j; } while (arr_compare(arr_read(false, j), e) > 0);

		if (i >= j) return j;

		arr_swap(false, i, j);
	}
}

static void quick_sort_main(uint8_t start, uint8_t end) {
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
