#ifndef SORTPICKER_H
#define SORTPICKER_H

#include "nes.h"

typedef void (*SortFunction)(uint8_t len);

// Returns a sort function index corresponding to the user's choice
SortFunction sortpicker_run(void);

#endif
