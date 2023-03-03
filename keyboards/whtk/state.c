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
#include "state.h"

////////// Keyboard state //////////
keyboard_state_t state = {
    .keypress_count = 0,
    .active_layer = 0,
    .modifiers = 0,
    .mode.raw = MODE_INIT,
};

void set_mode(mode_t mode) {
    state.mode = mode;
}

mode_t get_mode(void) {
    return state.mode;
}

void update_swap_lctl_lgui(void) {
    keymap_config.swap_lctl_lgui = (get_mode().os == OS_MAC);
}

void switch_mode(mode_t mode) {
    set_mode(mode);
    update_swap_lctl_lgui();
    eeconfig_update_kb(mode.raw);
}

void toggle_mode(void) {
    mode_t mode = get_mode();
    if (mode.os == OS_LINUX)
    {
        mode.os = OS_MAC;
    }
    else
    {
        mode.os = OS_LINUX;
    }
    switch_mode(mode);
}

void keyboard_post_init_kb(void) {
    // load persistent value
    mode_t mode = {
        .raw = eeconfig_read_kb()
    };
    if (mode.os != OS_LINUX && mode.os != OS_MAC)
    {
        // default os if eeprom value is invalid
        mode.os = OS_LINUX;
    }
    mode.unused_0 = 0;
    mode.unused_1 = 0;
    mode.unused_2 = 0;
    set_mode(mode);
    update_swap_lctl_lgui();
}

bool keyboard_state_equal(keyboard_state_t a, keyboard_state_t b) {
    return a.keypress_count == b.keypress_count &&
           a.active_layer == b.active_layer &&
           a.modifiers == b.modifiers &&
           a.mode.raw == b.mode.raw;
}

void register_keypress(void) {
    state.keypress_count++;
}

void update_keyboard_state(void) {
    state.active_layer = get_highest_layer(layer_state);
    state.modifiers = get_mods();
}

void register_scroll(int8_t count) {
    state.scroll_count += count;
}

int8_t pop_scroll(void) {
    int8_t scroll = state.scroll_count;
    state.scroll_count = 0;
    return scroll;
}


