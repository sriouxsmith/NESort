#ifndef BCD_H
#define BCD_H

#include "nes.h"

void bcd_from_binary(uint8_t value, uint8_t *bcd_out);
// returns the next available index
uint8_t bcd_render_as_spr(uint8_t x, uint8_t y, uint8_t index,
		uint8_t len, uint8_t *bcd);


#endif
