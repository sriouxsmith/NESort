#include "text.h"

const char *raw_text;
uint8_t line;
bool    is_text_done;

void text_init(const char *text) {
	raw_text = text;
	line = 0;
	is_text_done = false;
}

void text_update(void) {
	static char c;
	static uint8_t i;

	if (line == TEXT_MAX_LINES)
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
	for ( ; i < TEXT_MAX_LINE_WIDTH; ++i)
		nes_vram_buffer[i] = ' ';

	nes_set_vram_update(TEXT_MAX_LINE_WIDTH, nes_vram_buffer,
			nes_nametable_addr(1, line + 3));
	
	++line;
}

void text_wait_write(const char *text) {
	static uint8_t i;

	text_init(text);

	for (i = 0; i < TEXT_MAX_LINES; ++i) {
		text_update();
		nes_wait_frame();
	}
}
