#include "sortpicker.h"

static void init(void) {
	nes_set_ppu_ctrl(0x18);
	nes_set_ppu_mask(0);
	nes_wait_frame();
	nes_clear_nametable();
	nes_set_ppu_mask(0x1e);
}

SortFunction sortpicker_run(void) {
	init();

	while (1) {
		nes_wait_frame();
	}

	return (SortFunction)0;
}
