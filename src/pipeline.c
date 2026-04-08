#include "pipeline.h"
#include "text.h"

void pipeline_run(Pipeline *p) {
	text_wait_write("");
	nes_set_ppu_ctrl(0);
	text_wait_write("");
}
