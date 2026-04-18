#include "linear.h"
#include "distutils.h"

#include "../array.h"

void linear_distribution(uint8_t len, uint8_t distincts) {
	uint8_t i;
	for (i = 0; i < ARR_MAX_LEN; ++i)
		arr_ext0[i] = i + 1;

	distribute_standard(len, distincts, arr_ext0);
}
