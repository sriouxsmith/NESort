#include "pipeline.h"
#include "text.h"
#include "array.h"

#define WAIT 60

static void zero_arrays(bool visible) {
	static uint8_t i;

	for (i = 0; i < ARR_MAX_LEN; ++i) {
		if (visible) {
			arr_write(true, i, 0);
		} else {
			arr_main[i] = 0;
			arr_aux[i] = 0;
		}
		arr_ext0[i] = 0;
		arr_ext1[i] = 0;
	}

	arr_update_all();
}

static void check(uint8_t len) {
	uint8_t i;

	for (i = 0; i < len - 1; ++i)
		arr_compare_indices(false, i, i + 1);
}

void pipeline_run(Pipeline *p) {
	static bool is_aux_visible_save;
	static uint8_t update_speed_save;
	static uint8_t i;

	// set stage
	text_wait_write("");
	nes_set_ppu_ctrl(0);
	nes_set_arr_renderer_enabled(true);

	// clean state
	nes_seed_rand(p->seed);
	update_speed_save = arr_get_update_speed();
	arr_set_update_speed(2);
	zero_arrays(false);

	// setup array
	p->distribute(p->len, p->distincts);
	p->shuffle(p->len);
	zero_arrays(true);

	for (i = 0; i < WAIT - 12; ++i) arr_update_all();

	arr_set_update_speed(update_speed_save);
	p->sort(p->len);

	update_speed_save = arr_get_update_speed();
	arr_set_update_speed(2);

	check(p->len);
	arr_set_update_speed(update_speed_save);

	for (i = 0; i < WAIT; ++i) arr_update_all();

	nes_set_arr_renderer_enabled(false);
	text_wait_write("");
}
