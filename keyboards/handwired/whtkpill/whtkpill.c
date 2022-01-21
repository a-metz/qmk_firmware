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
#include "whtkpill.h"


////////// Utilities for alternative shifted keycodes //////////
typedef struct _mod_cache {
    uint8_t mod_bit;
    bool empty;
    bool state;
} mod_cache_t;

mod_cache_t lshift_cache = {
    .mod_bit = MOD_BIT(KC_LSHIFT),
    .empty = true,
    .state = false,
};

mod_cache_t rshift_cache = {
    .mod_bit = MOD_BIT(KC_RSHIFT),
    .empty = true,
    .state = false,
};

bool get_state(mod_cache_t *mod_cache) {
    return (bool)(get_mods() & mod_cache->mod_bit);
}

void push_state(mod_cache_t *mod_cache,  bool current_state, bool desired_state) {
    if (desired_state == current_state || !mod_cache->empty) {
        return;
    }

    mod_cache->empty = false;
    mod_cache->state = current_state;

    if (desired_state) {
        add_mods(mod_cache->mod_bit);
    } else {
        del_mods(mod_cache->mod_bit);
    }
}

void pop_state(mod_cache_t *mod_cache) {
    if (mod_cache->empty) {
        return;
    }

    if (mod_cache->state) {
        add_mods(mod_cache->mod_bit);
    } else {
        del_mods(mod_cache->mod_bit);
    }

    mod_cache->empty = true;
}

uint8_t update_state(mod_cache_t *mod_cache, uint8_t modifiers) {
    if (mod_cache->empty) {
        return modifiers;
    }

    if (mod_cache->state) {
        modifiers |= mod_cache->mod_bit;
    } else {
        modifiers &= ~mod_cache->mod_bit;
    }

    return modifiers;
}

void restore_shift(void) {
    pop_state(&lshift_cache);
    pop_state(&rshift_cache);
}

void shift_alternative(keyrecord_t *record, uint16_t keycode_normal, uint16_t keycode_modified) {
    if (record->event.pressed) {
        // check whether the normal and modified keycode require shift to be held
        bool desired_shift_normal = keycode_normal & QK_LSFT;
        bool desired_shift_modified = keycode_modified & QK_LSFT;

        // check the current shift state
        bool current_lshift = get_state(&lshift_cache);
        bool current_rshift = get_state(&rshift_cache);

        // push released shift state to the right shift
        push_state(&rshift_cache, current_rshift, false);

        if (current_lshift || current_rshift) {
            // push the desired shift state to the left shift
            push_state(&lshift_cache, current_lshift, desired_shift_modified);

            register_code(keycode_modified & ~QK_LSFT);
        } else {
            // push the desired shift state to the left shift
            push_state(&lshift_cache, current_lshift, desired_shift_normal);

            register_code(keycode_normal & ~QK_LSFT);
        }
    } else {
        unregister_code(keycode_normal);
        unregister_code(keycode_modified);
    }
}


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
    state.modifiers = update_state(&rshift_cache, update_state(&lshift_cache, get_mods()));
}