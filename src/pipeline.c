#include "pipeline.h"
#include "text.h"

void pipeline_run(Pipeline *p) {
	text_wait_write("");
	nes_set_ppu_ctrl(0);
	nes_set_arr_renderer_enabled(true);
	nes_set_arr_renderer_enabled(false);
	text_wait_write("");
}
