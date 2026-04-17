#ifndef SHUFFLES_H
#define SHUFFLES_H

#include "nes.h"

#define NUM_SHUFFLES 12

typedef void (*ShuffleFunction)(uint8_t len);

extern const ShuffleFunction shuffles[NUM_SHUFFLES];

#endif
