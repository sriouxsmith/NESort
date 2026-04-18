#include "distutils.h"

#include "../array.h"

void distribute_standard(uint8_t len, uint8_t distincts, const uint8_t *base) {
	uint8_t i;
	for (i = 0; i < len; ++i) {
		if (distincts == 1)
			arr_write(false, i, base[60]);
		else arr_write(false, i,
				base[i * distincts
				/ len * (ARR_MAX_LEN - 1)
				/ (distincts - 1)]);
	}
}
