#include "whtk.h"
#include "quantum.h"


void matrix_init_kb(void) {
    matrix_init_user();
};

////////// Utilities for alternative shifted keycodes //////////
uint8_t mods_state = 0;

bool check_mod_and_clear(uint16_t mod_keycode) {
    bool mod_active = get_mods() & MOD_BIT(mod_keycode);

    if (mod_active) {
        del_mods(MOD_BIT(mod_keycode));
    }

    return mod_active;
}

void mod_set(uint16_t mod_keycode) {
    mods_state |= MOD_BIT(mod_keycode);
}

void mod_clear(uint16_t mod_keycode) {
    mods_state &= ~MOD_BIT(mod_keycode);
}

void mod_restore(uint16_t mod_keycode) {
    if (mods_state & MOD_BIT(mod_keycode)) {
        add_mods(MOD_BIT(KC_LSHIFT));
    } else {
        del_mods(MOD_BIT(KC_LSHIFT));
    }
}

void shift_cleared_alternative(keyrecord_t *record, uint16_t keycode, uint16_t modded_keycode) {
    if (record->event.pressed) {
        if (check_mod_and_clear(KC_LSHIFT) || check_mod_and_clear(KC_RSHIFT)) {
          register_code(modded_keycode);
        } else {
          register_code(keycode);
        }
    } else {
        mod_restore(KC_LSHIFT);
        mod_restore(KC_RSHIFT);
        unregister_code(keycode);
        unregister_code(modded_keycode);
    }
}

void shift_all_alternative(keyrecord_t *record, uint16_t keycode, uint16_t modded_keycode) {
    if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
          register_code(modded_keycode);
        } else {
          add_mods(MOD_BIT(KC_LSHIFT));
          register_code(keycode);
        }
    } else {
        mod_restore(KC_LSHIFT);
        unregister_code(keycode);
        unregister_code(modded_keycode);
    }
}

////////// Synchronized state between keyboard sides //////////
keyboard_state_t state = {
    .keypress_count = 0,
    .active_layer = LAYER_ALPHA,
    .modifiers = 0,
    .mode = MODE_LINUX
};

void set_keyboard_state(keyboard_state_t state_) {
    state = state_;
}

keyboard_state_t get_keyboard_state(void) {
    return state;
}

bool keyboard_state_equal(keyboard_state_t a, keyboard_state_t b) {
    return a.keypress_count == b.keypress_count &&
           a.active_layer == b.active_layer &&
           a.modifiers == b.modifiers &&
           a.mode == b.mode;
}

void register_keypress(void) {
    state.keypress_count++;
}

void update_keyboard_state(void) {
    state.active_layer = get_highest_layer(layer_state);
    state.modifiers = get_mods();
}

void set_mode(mode_t mode) {
    state.mode = mode;
}

mode_t get_mode(void) {
    return state.mode;
}
