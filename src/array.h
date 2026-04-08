#ifndef ARRAY_H
#define ARRAY_H

#include "nes.h"

#define MAX_LEN 120

/* Displayable */
extern uint8_t arr_main[MAX_LEN];
extern uint8_t arr_aux[MAX_LEN];

/* Invisible */
extern uint8_t arr_ext0[MAX_LEN];
extern uint8_t arr_ext1[MAX_LEN];

uint8_t arr_get_update_speed(void);
void arr_set_update_speed(uint8_t);
bool arr_is_aux_visible(void);
void arr_set_aux_visible(bool);

void arr_clear_updates(void);

#endif
