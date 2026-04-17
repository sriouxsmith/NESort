#ifndef PIPELINE_H
#define PIPELINE_H

#include "nes.h"

#include "distributions.h"
#include "shuffles.h"
#include "sorts.h"

typedef struct {
	uint32_t seed;

	DistributionFunction distribute;
	ShuffleFunction shuffle;
	SortFunction sort;

	uint8_t len;
	uint8_t distincts;
} Pipeline;

void pipeline_run(Pipeline *p);

#endif
