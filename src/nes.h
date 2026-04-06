#ifndef NES_H
#define NES_H

#include <stdint.h>
#include <stdbool.h>

void nes_wait_frame(void);
void nes_set_ppu_ctrl(uint8_t);
void nes_set_ppu_mask(uint8_t);
void nes_clear_nametable(void);
void nes_set_vram_update(uint8_t len, const uint8_t *src, uint16_t dest);
uint8_t nes_get_new_buttons(void);

#endif
