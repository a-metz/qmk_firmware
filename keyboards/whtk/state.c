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
    .scroll_count = 0,
    .active_layer = 0,
    .modifiers = 0,
    .mode.raw = MODE_INIT,
    .drag_scroll = false,
};

keyboard_state_t get_keyboard_state(void) {
    return state;
}

void set_mode(mode_t mode) {
    uprintf("mode.os: %d\n", mode.os);
    state.mode = mode;
}

mode_t get_mode(void) {
    return state.mode;
}

void set_drag_scroll(bool drag_scroll) {
    state.drag_scroll = drag_scroll;
}

bool get_drag_scroll(void) {
    return state.drag_scroll;
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

void init_state(void) {
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
           a.scroll_count == b.scroll_count &&
           a.active_layer == b.active_layer &&
           a.modifiers == b.modifiers &&
           a.mode.raw == b.mode.raw &&
           a.drag_scroll == b.drag_scroll;
}

void register_keypress(void) {
    state.keypress_count++;
}

void update_keyboard_state(void) {
    layer_state_t new_active_layer = get_highest_layer(layer_state);
    if (new_active_layer != state.active_layer) {
        state.active_layer = get_highest_layer(layer_state);
        uprintf("active_layer: %d\n", new_active_layer);
    }

    uint8_t new_modifiers = get_mods();
    if (new_modifiers != state.modifiers) {
        state.modifiers = new_modifiers;
        uprintf("modifiers: %d\n", new_modifiers);
    }
}

void register_scroll(int8_t count) {
    state.scroll_count += count;
}

int8_t pop_scroll(void) {
    int8_t scroll = state.scroll_count;
    state.scroll_count = 0;
    return scroll;
}


