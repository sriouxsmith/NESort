#include "nes.h"

#include "sortpicker.h"
#include "pipeline.h"
#include "options.h"

const uint8_t palette[] = {
	0x0f, 0x00, 0x10, 0x30,
	0x0f, 0x29, 0x27, 0x30,
	0x0f, 0x05, 0x16, 0x27,
	0x0f, 0x0b, 0x1a, 0x29,

	0x0f, 0x00, 0x10, 0x30,
	0x0f, 0x29, 0x27, 0x30,
	0x0f, 0x05, 0x16, 0x27,
	0x0f, 0x0b, 0x1a, 0x29
};

void main(void) {
	static SortFunction sort;
	static Pipeline pipeline;
	static bool is_options_init;

	nes_set_ppu_mask(0);
	nes_set_vram_update(32, palette, 0x3f00);
	nes_wait_frame();
	nes_clear_nametable();
	nes_set_ppu_mask(0x1e);
	nes_seed_rand(3141592654);

	is_options_init = false;

	while (1) {
		nes_set_ppu_ctrl(0x18);
		sort = sortpicker_run();
		if (!is_options_init) {
			options_init(&pipeline);
			is_options_init = true;
		}
		if (!options_run(&pipeline))
			continue;
		pipeline_run(&pipeline);
	}
}
