#include "sortpicker.h"

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
	"satisfy the heap property.n\n"
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
