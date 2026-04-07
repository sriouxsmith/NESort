#ifndef NES_H
#define NES_H

#include <stdint.h>
#include <stdbool.h>

#define NES_BUTTON_A      0x80
#define NES_BUTTON_B      0x40
#define NES_BUTTON_SELECT 0x20
#define NES_BUTTON_START  0x10
#define NES_BUTTON_UP     0x08
#define NES_BUTTON_DOWN   0x04
#define NES_BUTTON_LEFT   0x02
#define NES_BUTTON_RIGHT  0x01

#define nes_nametable_addr(x, y) (0x2000 + ((y) << 5) + (x))

extern uint8_t nes_vram_buffer[32];

void nes_wait_frame(void);
void nes_set_ppu_ctrl(uint8_t);
void nes_set_ppu_mask(uint8_t);
void nes_clear_nametable(void);
void nes_set_vram_update(uint8_t len, const uint8_t *src, uint16_t dest);
uint8_t nes_get_new_buttons(void);
void nes_seed_rand(uint32_t);
uint8_t nes_get_rand8(void);
void nes_hide_spr(uint8_t start_index);
// returns the next available sprite index
uint8_t nes_put_spr(uint8_t x, uint8_t y, uint8_t tile,
		uint8_t attr, uint8_t index);


#endif
