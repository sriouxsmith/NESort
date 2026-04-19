#include "options.h"
#include "text.h"
#include "array.h"
#include "bcd.h"
#include "distributions.h"
#include "shuffles.h"

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
	uint8_t l[NUM_DISTRIBUTIONS];
	uint8_t r[NUM_DISTRIBUTIONS];
} distribution_symbols = {
	{0x04, 0x08, 0x0a, 0x0c, 0x06},
	{0x05, 0x09, 0x0b, 0x0d, 0x07}
};

static const struct {
	uint8_t l[NUM_SHUFFLES];
	uint8_t r[NUM_SHUFFLES];
} shuffle_symbols = {
	{0x06, '-', 0x04, 0x85, 0x0e, 0x10, 0x12, 0x15, 0x95, 0x15, 0x14, 0x16},
	{0x07, '-', 0x05, 0x84, 0x0f, 0x11, 0x13, 0x15, 0x95, 0x95, 0x14, 0x17}
};

const uint8_t spr_x[NUM_OPTIONS] = {144, 144, 144, 144, 144, 144, 144,   8,  88};
const uint8_t spr_y[NUM_OPTIONS] = { 39,  47,  63,  71,  79,  95, 103, 119, 119};

static uint8_t option_index;
static uint8_t distribution_index;
static uint8_t shuffle_index;
static uint8_t seed_index;

void generate_seed(Pipeline *p) {
	p->seed = nes_get_rand8()
		| ((uint32_t)nes_get_rand8() << 8)
		| ((uint32_t)nes_get_rand8() << 16)
		| ((uint32_t)nes_get_rand8() << 24);
}

void options_init(Pipeline *p) {
	p->len = 120;
	p->distincts = 120;
	arr_set_aux_visible(false);
	arr_set_update_speed(1);
	generate_seed(p);
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

static void draw_seed(uint32_t seed) {
	static uint32_t working_seed;
	static uint8_t tile;
	static uint8_t i;

	working_seed = seed;
	for (i = 0; i < 8; ++i) {
		tile = (working_seed >> 28) & 0x0f;
		tile += tile >= 10 ? 0x37 : 0x30;

		nes_vram_buffer[i] = tile;
		working_seed <<= 4;
	}

	nes_set_vram_update(8, nes_vram_buffer, 0x2114);
}

static uint8_t draw_symbol(uint8_t left, uint8_t right, uint8_t y, uint8_t index) {
	static uint8_t new_index;
	new_index = index;
	new_index = nes_put_spr(160, y, left & 0x7f, left >= 0x80 ? 0x40 : 0,
			new_index);
	new_index = nes_put_spr(168, y, right & 0x7f, right >= 0x80 ? 0x40 : 0,
			new_index);
	return new_index;
}

static void update_display(Pipeline *p) {
	static uint8_t length_bcd[3];
	static uint8_t uniques_bcd[3];
	static uint8_t speed_bcd[3];

	static uint8_t index;

	index = nes_put_spr(spr_x[option_index], spr_y[option_index], 0x7f, 0, 0);
	index = nes_put_spr(8 * seed_index + 160, 55, '_', 0, index);

	bcd_from_binary(p->len, length_bcd);
	bcd_from_binary(p->distincts, uniques_bcd);
	bcd_from_binary(arr_get_update_speed(), speed_bcd);

	index = bcd_render_as_spr(160, 39, index, 3, length_bcd);
	index = bcd_render_as_spr(160, 47, index, 3, uniques_bcd);
	index = bcd_render_as_spr(160, 104, index, 3, speed_bcd);

	if (arr_is_aux_visible()) {
		index = nes_put_spr(160, 95, 'y', 0, index);
		index = nes_put_spr(168, 95, 'e', 0, index);
		index = nes_put_spr(176, 95, 's', 0, index);
	} else {
		index = nes_put_spr(160, 95, 'n', 0, index);
		index = nes_put_spr(168, 95, 'o', 0, index);
	}

	index = draw_symbol(distribution_symbols.l[distribution_index],
			distribution_symbols.r[distribution_index],
			71, index);
	index = draw_symbol(shuffle_symbols.l[shuffle_index],
			shuffle_symbols.r[shuffle_index],
			79, index);

	nes_hide_spr(index);

	draw_seed(p->seed);
	nes_wait_frame();
}

bool options_run(Pipeline *p) {
	static uint8_t buttons;

	text_wait_write(options_text);

	while (1) {
		(void)nes_get_rand8();

		buttons = nes_get_new_buttons();

		if (buttons & NES_BUTTON_SELECT)
			return false;
		if (buttons & NES_BUTTON_START) {
			p->distribute = distributions[distribution_index];
			p->shuffle = shuffles[shuffle_index];

			return true;
		}

		switch (option_index) {
		case 0: // length
			if (buttons & NES_BUTTON_RIGHT) {
				if (p->len < ARR_MAX_LEN) ++p->len;
			} else if (buttons & NES_BUTTON_LEFT) {
				if (p->len >= 3) --p->len;
			} else if (buttons & NES_BUTTON_A) {
				if (p->len >= ARR_MAX_LEN - 9)
					p->len = ARR_MAX_LEN;
				else p->len += 10;
			} else if (buttons & NES_BUTTON_B) {
				if (p->len < 12) p->len = 2;
				else p->len -= 10;
			}

			if (p->distincts > p->len) p->distincts = p->len;
			break;

		case 1: // num distincts
			if (buttons & NES_BUTTON_RIGHT) {
				if (p->distincts < p->len) ++p->distincts;
			} else if (buttons & NES_BUTTON_LEFT) {
				if (p->distincts >= 2) --p->distincts;
			} else if (buttons & NES_BUTTON_A) {
				if (p->distincts >= p->len - 9)
					p->distincts = p->len;
				else p->distincts += 10;
			} else if (buttons & NES_BUTTON_B) {
				if (p->distincts < 11) p->distincts = 1;
				else p->distincts -= 10;
			}
			break;

		case 2: // seed
			if (buttons & NES_BUTTON_RIGHT) {
				if (seed_index < 7) ++seed_index;
			} else if (buttons & NES_BUTTON_LEFT) {
				if (seed_index >= 1) --seed_index;
			} else if (buttons & NES_BUTTON_A) {
				p->seed += (1ul << (4 * (7 - seed_index)));
			} else if (buttons & NES_BUTTON_B) {
				p->seed -= (1ul << (4 * (7 - seed_index)));
			}
			break;

		case 3: // distribution
			if (buttons & (NES_BUTTON_RIGHT | NES_BUTTON_A)) {
				if (distribution_index < NUM_DISTRIBUTIONS - 1)
					++distribution_index;
			} else if (buttons & (NES_BUTTON_LEFT | NES_BUTTON_B)) {
				if (distribution_index >= 1)
					--distribution_index;
			}
			break;

		case 4: // shuffle
			if (buttons & (NES_BUTTON_RIGHT | NES_BUTTON_A)) {
				if (shuffle_index < NUM_SHUFFLES - 1)
					++shuffle_index;
			} else if (buttons & (NES_BUTTON_LEFT | NES_BUTTON_B)) {
				if (shuffle_index >= 1)
					--shuffle_index;
			}
			break;

		case 5: // show aux
			if (buttons & (NES_BUTTON_RIGHT | NES_BUTTON_A
				| NES_BUTTON_LEFT | NES_BUTTON_B))
			{
				arr_set_aux_visible(!arr_is_aux_visible());
			}
			break;

		case 6: // speed
			if (buttons & NES_BUTTON_RIGHT) {
				if (arr_get_update_speed() < 100)
					arr_set_update_speed(
						arr_get_update_speed() + 1
					);
			} else if (buttons & NES_BUTTON_LEFT) {
				if (arr_get_update_speed() >= 2)
					arr_set_update_speed(
						arr_get_update_speed() - 1
					);
			} else if (buttons & NES_BUTTON_A) {
				if (arr_get_update_speed() >= 90)
					arr_set_update_speed(100);
				else arr_set_update_speed(
					arr_get_update_speed() + 10
				);
			} else if (buttons & NES_BUTTON_B) {
				if (arr_get_update_speed() < 11)
					arr_set_update_speed(1);
				else arr_set_update_speed(
					arr_get_update_speed() - 10
				);
			}
			break;

		case 7: // reset
			if (buttons & NES_BUTTON_A) options_init(p);
			if (buttons & NES_BUTTON_RIGHT) ++option_index;
			break;

		case 8: // generate seed
			if (buttons & NES_BUTTON_A) generate_seed(p);
			if (buttons & NES_BUTTON_LEFT) --option_index;
			break;
		}

		handle_navigation(buttons);
		update_display(p);
	}
}
