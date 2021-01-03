#include "whtk.h"


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
