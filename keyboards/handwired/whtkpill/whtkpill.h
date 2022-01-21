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

#define ___ KC_NO

#define LAYOUT( \
             L01, L02, L03, L04,      R05, R06, R07, R08, \
        L10, L11, L12, L13, L14,      R15, R16, R17, R18, R19, \
        L20, L21, L22, L23, L24,      R25, R26, R27, R28, R29, \
        L30, L31, L32, L33, L34,      R35, R36, R37, R38, R39, \
                  L42, L43, L44,      R45, R46, R47 \
    ) { \
        { ___, L01, L02, L03, L04,      R05, R06, R07, R08, ___ }, \
        { L10, L11, L12, L13, L14,      R15, R16, R17, R18, R19 }, \
        { L20, L21, L22, L23, L24,      R25, R26, R27, R28, R29 }, \
        { L30, L31, L32, L33, L34,      R35, R36, R37, R38, R39 }, \
        { ___, ___, L42, L43, L44,      R45, R46, R47, ___, ___ } \
    }

typedef enum _layer_t {
    LAYER_ALP_PUN = 0,
    LAYER_SYM_NAV,
    LAYER_THUMB,
    LAYER_FUN_NUM,
    LAYER_UMLAUT,
} layer_t;


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

void set_mode(mode_t);

mode_t get_mode(void);

void toggle_mode(void);

typedef struct _keyboard_state_t {
    uint8_t keypress_count;
    layer_t active_layer;
    uint8_t modifiers;
    mode_t mode;
} keyboard_state_t;

void update_keyboard_state(void);

bool keyboard_state_equal(keyboard_state_t a, keyboard_state_t b);

void register_keypress(void);
