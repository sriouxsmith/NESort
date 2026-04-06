#include "options.h"
#include "text.h"
#include "array.h"
#include "bcd.h"

const char options_text[] =
	"           OPTIONS\n"
	"\n"
	"   Length:\n"
	"   No. uniques:\n"
	"\n"
	"   Seed:\n"
	"   Distribution:\n"
	"   Shuffle:\n"
	"\n"
	"   Show Aux.:\n"
	"   Speed:\n"
	"\n"
	"  [Reset]   [Generate Seed]\n"
	"\n"
	"Use right/A and left/B to\n"
	"change options. Press start to\n"
	"start the demo or select to\n"
	"go back to the sort selection.\n"
	"\n"
	"While sorting, press select to\n"
	"toggle aux. display, start to\n"
	"pause, or up & down to change\n"
	"the speed. To stop the sort,\n"
	"press select while paused.";

uint8_t length_bcd[3];
uint8_t uniques_bcd[3];
uint8_t speed_bcd[3];

void options_init(Pipeline *p) {
	p->len = 120;
	p->distincts = 120;
	arr_set_aux_visible(false);
	arr_set_update_speed(1);
}

bool options_run(Pipeline *p) {
	static uint8_t buttons;

	text_init(options_text);

	bcd_from_binary(p->len, length_bcd);
	bcd_from_binary(p->distincts, uniques_bcd);
	bcd_from_binary(arr_get_update_speed(), speed_bcd);

	while (1) {
		(void)nes_get_rand8();

		buttons = nes_get_new_buttons();

		if (buttons & NES_BUTTON_SELECT)
			return false;
		
		text_update();
		nes_wait_frame();
	}
}
