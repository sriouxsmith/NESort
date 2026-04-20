#include "intro.h"

#include "../array.h"

static uint8_t log2x2;

static void heap_sort(uint8_t lo, uint8_t len) {
	uint8_t root;
	uint8_t child;
	uint8_t start = len / 2;
	uint8_t end = len;

	while (end > 1) {
		if (start > 0) --start;
		else arr_swap(false, lo + --end, lo);

		root = start;
		while (2 * root + 1 < end) {
			child = 2 * root + 1;
			if (child + 1 < end
				&& arr_compare_indices(false,
					lo + child, lo + child + 1) < 0)
			{
				++child;
			}

			if (arr_compare_indices(false, lo + root, lo + child) < 0) {
				arr_swap(false, lo + root, lo + child);
				root = child;
			} else break;
		}
	}
}

static void insertion_sort(uint8_t len) {
	uint8_t i, j;
	uint8_t e;

	for (j = 1; j < len; ++j) {
		e = arr_read(false, j);

		for (i = j - 1; i < len; --i) {
			if (arr_compare(arr_read(false, i), e) <= 0)
				break;
			arr_write(false, i + 1, arr_read(false, i));
		}
		arr_write(false, i + 1, e);
	}
}

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

static void quick_sort_main(uint8_t start, uint8_t end, uint8_t depth) {
	uint8_t p;

	if (start >= 128 || end >= 128 || (end - start) < 8)
		return;

	if (depth < log2x2) {
		p = partition(start, end);

		quick_sort_main(start, p, depth + 1);
		quick_sort_main(p + 1, end, depth + 1);
	} else heap_sort(start, end - start + 1);
}

void intro_sort(uint8_t len) {
	if (len >= 64) log2x2 = 12;
	else if (len >= 32) log2x2 = 10;
	else if (len >= 16) log2x2 = 8;
	else if (len >= 8) log2x2 = 6;
	else if (len >= 4) log2x2 = 4;
	else if (len >= 2) log2x2 = 2;

	quick_sort_main(0, len - 1, 0);
	insertion_sort(len);
}
