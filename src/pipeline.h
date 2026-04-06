#ifndef PIPELINE_H
#define PIPELINE_H

#include "nes.h"

typedef struct {
	uint32_t seed;

	void (*distribute)(uint8_t len, uint8_t distincts);
	void (*shuffle)(uint8_t len);
	void (*sort)(uint8_t len);

	uint8_t len;
	uint8_t distincts;
} Pipeline;

#endif
