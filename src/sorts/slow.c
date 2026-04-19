#include "slow.h"

#include "../array.h"

void slow_sort_main(uint8_t start, uint8_t end) {
	while (start < end) {
		uint8_t m = (start + end) / 2;

		slow_sort_main(start, m);
		slow_sort_main(m + 1, end);
		if (arr_compare_indices(false, end, m) < 0)
			arr_swap(false, end, m);
		--end;
	}
}

void slow_sort(uint8_t len) {
	slow_sort_main(0, len - 1);
}
