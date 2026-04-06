#include "options.h"
#include "text.h"

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


void options_init(Pipeline *p) {

}

bool options_run(Pipeline *p) {
	return false;
}
