#include "insertion.h"

#include "../array.h"

void insertion_sort(uint8_t len) {
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
