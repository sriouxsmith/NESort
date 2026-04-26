#include "../sorts.h"

#include "selection.h"
#include "heap.h"
#include "insertion.h"
#include "shell.h"
#include "bubble.h"
#include "comb.h"
#include "gnome.h"
#include "shaker.h"
#include "quick.h"
#include "merge.h"
#include "intro.h"
#include "counting.h"
#include "bitonic.h"
#include "stooge.h"
#include "slow.h"
#include "bogo.h"

const SortFunction sorts[] = {
	selection_sort,
	heap_sort,
	insertion_sort,
	shell_sort,
	bubble_sort,
	comb_sort,
	gnome_sort,
	shaker_sort,
	quick_sort,
	merge_sort,
	intro_sort,
	selection_sort,
	counting_sort,
	selection_sort,
	selection_sort,
	selection_sort,
	selection_sort,
	selection_sort,
	bitonic_sort,
	selection_sort,
	selection_sort,
	stooge_sort,
	slow_sort,
	bogo_sort
};
