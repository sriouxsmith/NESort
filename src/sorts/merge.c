#include "merge.h"

#include "../array.h"

void merge(uint8_t start, uint8_t middle, uint8_t end) {
	uint8_t i = start;
	uint8_t j = middle;
	uint8_t k;
	
	for (k = start; k < end; ++k) {
		if (i < middle && (j >= end ||
			arr_compare_indices(false, j, i) > 0))
		{
			arr_write(true, k, arr_main[i]);
			arr_write(false, i++, 0);
		} else {
			arr_write(true, k, arr_main[j]);
			arr_write(false, j++, 0);
		}
	}
}

void merge_sort_main(uint8_t start, uint8_t end) {
	uint8_t i, m;

	if (end - start < 2) return;

	m = (start + end) / 2;
	merge_sort_main(start, m);
	merge_sort_main(m, end);
	merge(start, m, end);

	for (i = start; i < end; ++i) {
		arr_write(false, i, arr_aux[i]);
		arr_write(true, i, 0);
	}
}

void merge_sort(uint8_t len) {
	merge_sort_main(0, len);
}
