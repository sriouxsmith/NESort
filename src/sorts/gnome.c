#include "gnome.h"

#include "../array.h"

void gnome_sort(uint8_t len) {
	uint8_t i = 1;

	while (i < len) {
		if (!i || arr_compare_indices(false, i, i - 1) >= 0)
			++i;
		else {
			arr_swap(false, i, i - 1);
			--i;
		}
	}
}
