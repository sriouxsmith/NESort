#ifndef ARRAY_H
#define ARRAY_H

#include "nes.h"

#define ARR_MAX_LEN 120

/* Displayable */
extern uint8_t arr_main[ARR_MAX_LEN];
extern uint8_t arr_aux[ARR_MAX_LEN];

/* Invisible */
extern uint8_t arr_ext0[ARR_MAX_LEN];
extern uint8_t arr_ext1[ARR_MAX_LEN];

uint8_t arr_get_update_speed(void);
void arr_set_update_speed(uint8_t);
bool arr_is_aux_visible(void);
void arr_set_aux_visible(bool);

void arr_clear_updates(void);
void arr_update_all(void);
void arr_push_update(uint8_t col);
void arr_push_blank(void);

uint8_t arr_read(bool aux, uint8_t i);
int8_t arr_compare(uint8_t left, uint8_t right);
int8_t arr_compare_indices(bool aux, uint8_t left, uint8_t right);

void arr_write(bool aux, uint8_t i, uint8_t val);
void arr_swap(bool aux, uint8_t a, uint8_t b);

void arr_play(uint8_t val);

#endif
