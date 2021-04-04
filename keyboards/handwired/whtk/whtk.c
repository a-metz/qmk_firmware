#include "whtk.h"
#include "quantum.h"


////////// Utilities for alternative shifted keycodes //////////
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

bool get_state_and_push(mod_cache_t *mod_cache, bool desired_state) {
    bool mod_state = (bool)(get_mods() & mod_cache->mod_bit);

    if (desired_state == mod_state || !mod_cache->empty) {
        return mod_state;
    }

    mod_cache->empty = false;
    mod_cache->state = mod_state;

    if (desired_state) {
        add_mods(mod_cache->mod_bit);
    } else {
        del_mods(mod_cache->mod_bit);
    }

    return mod_state;
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

void shift_cleared(keyrecord_t *record, uint16_t keycode, uint16_t modded_keycode) {
    if (record->event.pressed) {
        bool desired_state = (keycode & QK_LSFT) || (modded_keycode & QK_LSFT);
        bool lshift = get_state_and_push(&lshift_cache, desired_state);
        bool rshift = get_state_and_push(&rshift_cache, desired_state);
        if (lshift || rshift) {
            register_code(modded_keycode);
        } else {
            register_code(keycode);
        }
    } else {
        unregister_code(keycode);
        unregister_code(modded_keycode);
    }
}


////////// Synchronized state between keyboard sides //////////
keyboard_state_t state = {
    .keypress_count = 0,
    .active_layer = LAYER_ALPHA,
    .modifiers = 0,
    .mode = MODE_INIT,
    .legend = false,
};

void set_keyboard_state(keyboard_state_t state_) {
    state = state_;
}

keyboard_state_t get_keyboard_state(void) {
    return state;
}

bool keyboard_state_equal(keyboard_state_t a, keyboard_state_t b) {
    return a.keypress_count == b.keypress_count &&
           a.mousemove_count == b.mousemove_count &&
           a.active_layer == b.active_layer &&
           a.modifiers == b.modifiers &&
           a.mode == b.mode &&
           a.legend == b.legend &&
           a.mouse_accurate == b.mouse_accurate;
}

void register_keypress(void) {
    state.keypress_count++;
}

void register_mousemove(void) {
    state.mousemove_count++;
}

void update_keyboard_state(void) {
    state.active_layer = get_highest_layer(layer_state);
    state.modifiers = update_state(&rshift_cache, update_state(&lshift_cache, get_mods()));
}

void set_mode(mode_t mode) {
    state.mode = mode;
    eeconfig_update_kb(mode);
}

mode_t get_mode(void) {
    return state.mode;
}

void set_legend(bool legend) {
    state.legend = legend;
}

bool get_legend(void) {
    return state.legend;
}

void set_mouse_accurate(bool mouse_accurate) {
    state.mouse_accurate = mouse_accurate;
}

bool get_mouse_accurate(void) {
    return state.mouse_accurate;
}


////////// Load persistent state //////////
void keyboard_post_init_user(void) {
  state.mode = eeconfig_read_kb();
  if (state.mode == MODE_INIT || state.mode > MODE_MAC)
  {
    // default mode if eeprom value is invalid
    state.mode = MODE_LINUX;
  }
}
