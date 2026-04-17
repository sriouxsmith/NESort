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
void arr_update_all(void);
void arr_push_update(uint8_t col);
void arr_push_blank(void);

uint8_t arr_read(bool aux, uint8_t i);
void arr_write(bool aux, uint8_t i, uint8_t val);
int8_t arr_compare(uint8_t left, uint8_t right);

void arr_play(uint8_t val);

#endif
