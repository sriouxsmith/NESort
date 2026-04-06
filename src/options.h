#ifndef OPTIONS_H
#define OPTIONS_H

#include "nes.h"
#include "pipeline.h"

//
// Run the options screen. Return false if options were not committed.
// NOTE: does not touch Pipeline.sort so the caller must supply that somehow.
//
bool options_run(Pipeline *p);

//
// Setup the default options
//
void options_init(Pipeline *p);

#endif
