#include "sortpicker.h"

#define NUM_SORTS (sizeof(sort_text) / sizeof(const char *))

#define MAX_LINES      24
#define MAX_LINE_WIDTH 30

static const char *const sort_text[] = {
	"\xa4\xa5 Heap Sort                 3\n"
	"\xb4\xb5\n"
	"\n"
	"An improvement on selection\n"
	"sort which first organizes the\n"
	"data into a binary max heap\n"
	"and uses it to find the next\n"
	"highest item in logarithmic\n"
	"time. This is done by swapping\n"
	"the top parent with the last\n"
	"child, removing it from the\n"
	"tree, and then reordering to\n"
	"satisfy the heap property.\n"
	"\n"
	"The heap is stored implicitly\n"
	"on the original array. For any\n"
	"parent (index i), the left\n"
	"child is at 2i + 1 and the\n"
	"right child at 2i + 2.\n"
	"\n"
	"Time:   O(nlogn)\n"
	"Space:  O(1)\n"
	"Stable: no"
};

uint8_t cur_index; // initialized to 0 on startup

const char *raw_text;
uint8_t line;
bool    is_text_done;

static void reset_text_engine(void) {
	raw_text = sort_text[cur_index];
	line = 0;
	is_text_done = false;
}

static void update_text(void) {
	static char c;
	static uint8_t i;

	if (line == MAX_LINES - 1)
		return;

	if (is_text_done) {
		i = 0;
		goto clear_line;
	}

	for (i = 0; ; ++i) {
		c = *raw_text++;

		if (c == '\0') {
			is_text_done = true;
			break;
		} else if (c == '\n')
			break;

		nes_vram_buffer[i] = c;
	}

clear_line:
	for ( ; i < MAX_LINE_WIDTH; ++i)
		nes_vram_buffer[i] = ' ';

	nes_set_vram_update(MAX_LINE_WIDTH, nes_vram_buffer,
			nes_nametable_addr(1, line + 3));
	
	++line;
}

static void init(void) {
	nes_set_ppu_ctrl(0x18);
	nes_set_ppu_mask(0);
	nes_wait_frame();
	nes_clear_nametable();
	nes_set_ppu_mask(0x1e);

	reset_text_engine();
}

SortFunction sortpicker_run(void) {
	static uint8_t buttons;

	init();

	while (1) {
		buttons = nes_get_new_buttons();

		if (buttons & NES_BUTTON_START)
			return (SortFunction)0;

		if (buttons & NES_BUTTON_RIGHT) {
			++cur_index;
			if (cur_index >= NUM_SORTS)
				cur_index = 0;
			reset_text_engine();
		} else if (buttons & NES_BUTTON_LEFT) {
			--cur_index;
			if (cur_index >= NUM_SORTS)
				cur_index = NUM_SORTS - 1;
			reset_text_engine();
		} else if (buttons & NES_BUTTON_UP) {
			cur_index += 5;
			if (cur_index >= NUM_SORTS)
				cur_index = NUM_SORTS - 1;
			reset_text_engine();
		} else if (buttons & NES_BUTTON_DOWN) {
			cur_index -= 5;
			if (cur_index >= NUM_SORTS)
				cur_index = 0;
			reset_text_engine();
		}
		
		update_text();
		nes_wait_frame();
	}
}
