#include "options.h"
#include "text.h"
#include "array.h"
#include "bcd.h"

#define NUM_OPTIONS 9

static const char options_text[] =
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

static const struct {
	uint8_t spr_x[NUM_OPTIONS];
	uint8_t spr_y[NUM_OPTIONS];
} options = {
	{144, 144, 144, 144, 144, 144, 144,   8,  88},
	{ 39,  47,  63,  71,  79,  95, 103, 119, 119}
};

static uint8_t length_bcd[3];
static uint8_t uniques_bcd[3];
static uint8_t speed_bcd[3];

static uint8_t option_index;

void options_init(Pipeline *p) {
	p->len = 120;
	p->distincts = 120;
	arr_set_aux_visible(false);
	arr_set_update_speed(1);
}

static void handle_navigation(uint8_t buttons) {
	if (buttons & NES_BUTTON_DOWN) {
		++option_index;
		if (option_index >= NUM_OPTIONS)
			option_index = NUM_OPTIONS - 1;
	} else if (buttons & NES_BUTTON_UP) {
		--option_index;
		if (option_index >= NUM_OPTIONS)
			option_index = 0;
	}
}

static void update_display(Pipeline *p) {
	static uint8_t index;

	index = nes_put_spr(options.spr_x[option_index],
			options.spr_y[option_index],
			0x7f, 0, 0);

	nes_hide_spr(index);
	nes_wait_frame();
}

bool options_run(Pipeline *p) {
	static uint8_t buttons;

	text_wait_write(options_text);

	bcd_from_binary(p->len, length_bcd);
	bcd_from_binary(p->distincts, uniques_bcd);
	bcd_from_binary(arr_get_update_speed(), speed_bcd);

	while (1) {
		(void)nes_get_rand8();

		buttons = nes_get_new_buttons();

		if (buttons & NES_BUTTON_SELECT)
			return false;
		if (buttons & NES_BUTTON_START)
			return true;

		handle_navigation(buttons);
		update_display(p);
	}
}
