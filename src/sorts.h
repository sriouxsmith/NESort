#ifndef SORTS_H
#define SORTS_H

#include "nes.h"

#define NUM_SORTS 24

typedef void (*SortFunction)(uint8_t len);

extern const SortFunction sorts[NUM_SORTS];

#endif
