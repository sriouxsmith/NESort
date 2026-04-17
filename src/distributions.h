#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H

#include "nes.h"

#define NUM_DISTRIBUTIONS 5

typedef void (*DistributionFunction)(uint8_t len, uint8_t distincts);

extern const DistributionFunction distributions[NUM_DISTRIBUTIONS];

#endif
