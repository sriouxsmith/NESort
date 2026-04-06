#ifndef TEXT_H
#define TEXT_H

#include "nes.h"

#define TEXT_MAX_LINES      24
#define TEXT_MAX_LINE_WIDTH 30

void text_init(const char *text);
void text_update(void);
void text_wait_write(const char *text);

#endif
