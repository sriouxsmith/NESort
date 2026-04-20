#include "bitonic.h"

#include "../array.h"

void comp_swap(uint8_t a, uint8_t b, uint8_t asc) {
	int8_t comp = arr_compare_indices(false, a, b);
	if (asc && comp > 0 || !asc && comp < 0)
		arr_swap(false, a, b);
}

void bitonic_sort(uint8_t len) {
	uint16_t i, j, k;
	uint16_t n = len;
	
	for (k = 2; k < n * 2; k *= 2) {
		bool m = !!(((n + (k - 1)) / k) % 2);

		for (j = k >> 1; j > 0; j >>= 1) {
			for (i = 0; i < n; ++i) {
				uint16_t ij = i ^ j;

				if (ij > i && ij < n) {
					comp_swap(i, ij, !(i & k) == m);
				}
			}
		}
	}
}
