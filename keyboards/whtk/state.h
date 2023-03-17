/* Copyright 2022 Alexander Metz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"

////////// Keyboard state //////////
#define MODE_INIT 0
#define OS_LINUX 1
#define OS_MAC 2

typedef union {
    uint32_t raw;
    struct {
        uint8_t os;
        uint8_t unused_0;
        uint8_t unused_1;
        uint8_t unused_2;
    };
} mode_t;

typedef struct _keyboard_state_t {
    uint8_t keypress_count;
    int8_t scroll_count;
    layer_state_t active_layer;
    uint8_t modifiers;
    mode_t mode;
    bool drag_scroll;
} keyboard_state_t;

void init_state(void);

keyboard_state_t get_keyboard_state(void);

void set_mode(mode_t);

mode_t get_mode(void);

void set_drag_scroll(bool);

bool get_drag_scroll(void);

void toggle_mode(void);

void update_keyboard_state(void);

bool keyboard_state_equal(keyboard_state_t a, keyboard_state_t b);

void register_keypress(void);

void register_scroll(int8_t count);

int8_t pop_scroll(void);