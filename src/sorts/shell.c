#include "shell.h"

#include "../array.h"

void shell_sort(uint8_t len) {
	const uint8_t gaps[] = {57, 23, 10, 4, 1};

	uint8_t i, j, k, kx;

	for (k = 0; k < sizeof(gaps) / sizeof(uint8_t); ++k) {
		kx = gaps[k];
		if (kx >= len) continue;
		for (j = kx; j < len; ++j) {
			for (i = j - kx; i < len; i -= kx) {
				if (arr_compare_indices(false, i, i + kx) <= 0)
					break;
				arr_swap(false, i, i + kx);
			}
		}
	}
}
