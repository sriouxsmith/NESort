#include "shell.h"

#include "../array.h"

void shell_sort(uint8_t len) {
	const uint8_t gaps[] = {57, 23, 10, 4, 1};

	uint8_t i, j, k, kx;

	for (k = 0; k < sizeof(gaps) / sizeof(uint8_t); ++k) {
		kx = gaps[k];
		if (kx >= len) continue;
		for (j = kx; j < len; ++j) {
			uint8_t e = arr_read(false, j);
			for (i = j; i >= kx; i -= kx) {
				if (arr_compare(e, arr_read(false, i - kx)) >= 0)
					break;
				arr_write(false, i, arr_read(false, i - kx));
			}

			arr_write(false, i, e);
		}
	}
}
