#include QMK_KEYBOARD_H

#define _ALPHA 0
#define _FUNC 1
#define _MOUSE 2
#define _NUMERIC 3
#define _UMLAUT 4

#define KC_THUMB_L0 LT(_FUNC, KC_SPC)
#define KC_THUMB_L1 LCTL_T(KC_TAB)
#define KC_THUMB_R0 LT(_NUMERIC, KC_ENT)
#define KC_THUMB_R1 RSFT_T(KC_BSPC)
#define KC_THUMB_R1_F RSFT_T(KC_DEL)

#define KC_PREV_WORD LCTL(KC_LEFT)
#define KC_NEXT_WORD LCTL(KC_RGHT)
#define KC_PREV_TAB LCTL(KC_PGUP)
#define KC_NEXT_TAB LCTL(KC_PGDN)

#define MACRO_1_PLAY DYN_MACRO_PLAY1
#define MACRO_1_REC DYN_REC_START1
#define MACRO_2_PLAY DYN_MACRO_PLAY2
#define MACRO_2_REC DYN_REC_START2
#define MACRO_REC_STOP DYN_REC_STOP

enum custom_keycodes {
    NORMAL_MODE = SAFE_RANGE,
    MAC_MODE,
    KC_CTL_TAB,
    KC_SFT_BSPC,
    KC_DOT_COMM,
    KC_EXLM_QUES,
    KC_SLSH_BSLS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ALPHA] = LAYOUT_WHTK(
        KC_NO,         KC_NO,         KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH_BSLS,  KC_QUOT,       KC_DOT_COMM,   KC_EXLM_QUES,  KC_SCLN,       KC_VOLD,       KC_VOLU,
        MACRO_1_PLAY,  KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,          KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,          KC_PSCR,
        MACRO_2_PLAY,  KC_A,          KC_S,          KC_D,          KC_F,          KC_G,          KC_H,          KC_J,          KC_K,          KC_L,          KC_ESC,        KC_INS,
        KC_LALT,       KC_LSFT,       KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,          KC_N,          KC_M,          KC_DEL,        KC_RCTL,       KC_RALT,
                                      KC_DEL,        KC_ENT,                                                                    NORMAL_MODE,   MAC_MODE,
                                                                    KC_THUMB_L1,   KC_THUMB_L0,   KC_THUMB_R0,   KC_THUMB_R1,
                                                                    KC_LGUI,       MO(_MOUSE),    OSL(_UMLAUT),  TO(_MOUSE),
                                                                    LSFT(KC_LGUI), SH_TG,         TO(_NUMERIC),  TO(_FUNC)
    ),
    [_FUNC] = LAYOUT_WHTK(
        DYN_REC_STOP,  KC_NO,         KC_AT,         KC_LT,         KC_GT,         KC_CIRC,       KC_PREV_TAB,   KC_NEXT_TAB,   KC_NO,         KC_NO,         KC_MUTE,       KC_NO,
        MACRO_1_REC,   KC_NO,         KC_HASH,       KC_LCBR,       KC_RCBR,       KC_ASTR,       KC_PGUP,       KC_PREV_WORD,  KC_UP,         KC_NEXT_WORD,  KC_NO,         KC_PAUS,
        MACRO_2_REC,   KC_NO,         KC_DLR,        KC_LPRN,       KC_RPRN,       KC_AMPR,       KC_PGDN,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_NO,         KC_SLCK,
        KC_TRNS,       KC_TRNS,       KC_PERC,       KC_LBRC,       KC_RBRC,       KC_PIPE,       KC_HOME,       KC_HOME,       KC_NO,         KC_END,        KC_TRNS,       KC_TRNS,
                                      KC_NO,         KC_NO,                                                                     KC_NO,         KC_NO,
                                                                    KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_THUMB_R1_F,
                                                                    KC_TRNS,       KC_TRNS,       TO(_ALPHA),    KC_TRNS,
                                                                    KC_TRNS,       RESET,         KC_TRNS,       KC_TRNS
    ),
    [_NUMERIC] = LAYOUT_WHTK(
        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_COMM,       KC_DOT,        KC_NO,         KC_NO,         KC_NO,         KC_NO,
        KC_NO,         KC_NO,         KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_0,          KC_1,          KC_2,          KC_3,          KC_NO,         KC_NO,
        KC_NO,         KC_NO,         KC_F5,         KC_F6,         KC_F7,         KC_F8,         KC_NO,         KC_4,          KC_5,          KC_6,          KC_NO,         KC_NO,
        KC_TRNS,       KC_TRNS,       KC_F9,         KC_F10,        KC_F11,        KC_F12,        KC_NO,         KC_7,          KC_8,          KC_9,          KC_TRNS,       KC_TRNS,
                                      KC_NO,         KC_NO,                                                                     KC_NO,         KC_NO,
                                                                    KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS,
                                                                    KC_TRNS,       KC_TRNS,       TO(_ALPHA),    KC_TRNS,
                                                                    KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
    ),
    [_UMLAUT] = LAYOUT_WHTK(
        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,
        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         RALT(KC_Y),    KC_NO,         RALT(KC_P),    KC_NO,         KC_NO,
        KC_NO,         RALT(KC_Q),    RALT(KC_S),    KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,
        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,
                                      KC_NO,         KC_NO,                                                                     KC_NO,         KC_NO,
                                                                    KC_NO,         KC_NO,         KC_NO,         KC_RSFT,
                                                                    KC_NO,         KC_NO,         TO(_ALPHA),    KC_NO,
                                                                    KC_NO,         KC_NO,         KC_NO,         KC_NO
    ),
    [_MOUSE] = LAYOUT_WHTK(
        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_MPLY,       KC_MNXT,
        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_WH_U,       KC_WH_D,       KC_MS_U,       KC_WH_R,       KC_NO,         KC_NO,
        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_WH_D,       KC_MS_L,       KC_MS_D,       KC_MS_R,       KC_NO,         KC_NO,
        KC_TRNS,       KC_TRNS,       KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_BTN3,       KC_NO,         KC_NO,         KC_NO,         KC_TRNS,       KC_TRNS,
                                      KC_NO,         KC_NO,                                                                     KC_NO,         KC_NO,
                                                                    KC_TRNS,       KC_TRNS,       KC_BTN1,       KC_BTN2,
                                                                    KC_TRNS,       KC_TRNS,       TO(_ALPHA),    KC_TRNS,
                                                                    KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS
    ),
};

const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = MIRROR_WHTK;


//////////// Custom keycodes //////////
#define KC_MAP(kc_from, kc_to) case (kc_from): map_to((kc_to), record); return false;

void map_to(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return true;
    }
}


////////// Mac mode alternatives //////////
bool mac_mode = false;

bool process_record_user_mac_mode(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NORMAL_MODE:
            mac_mode = false;
            keymap_config.swap_lctl_lgui = false;
            return false;

        case MAC_MODE:
            mac_mode = true;
            keymap_config.swap_lctl_lgui = true;
            return false;

        default:
            break;
    }

    // skip mac mode processing if it's not active
    if (!mac_mode) {
        return true;
    }

    switch (keycode) {
        KC_MAP(KC_PREV_WORD, LALT(KC_LEFT))
        KC_MAP(KC_NEXT_WORD, LALT(KC_RGHT))
        KC_MAP(KC_PREV_TAB, LCTL(LSFT(KC_TAB)))
        KC_MAP(KC_NEXT_TAB, LCTL(KC_TAB))
        KC_MAP(KC_HOME, LGUI(KC_LEFT))
        KC_MAP(KC_END, LGUI(KC_RGHT))

        KC_MAP(OSL(_UMLAUT), LALT(KC_U))  // mac umlaut leader

        default:
            return true;
    }

}


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

bool process_record_user_shift_alternative(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSHIFT:
        case KC_RSHIFT:
            if (record->event.pressed) {
                mod_set(keycode);
            } else {
                mod_clear(keycode);
            }
            return true;

        case KC_DOT_COMM:
            shift_cleared_alternative(record, KC_DOT, KC_COMM);
            return false;

        case KC_EXLM_QUES:
            shift_all_alternative(record, KC_EXLM, KC_QUES);
            return false;

        case KC_SLSH_BSLS:
            shift_cleared_alternative(record, KC_SLSH, KC_BSLS);
            return false;

        default:
            return true;
      }
}


////////// Process key stroke //////////
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_user_mac_mode(keycode, record) &&
           process_record_user_custom(keycode, record) &&
           process_record_user_shift_alternative(keycode, record);
}


////////// Key based tapping term //////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_THUMB_L0:
        case KC_THUMB_R0:
            return TAPPING_TERM_LAYER;

        case KC_THUMB_L1:
        case KC_THUMB_R1:
        case KC_THUMB_R1_F:
            return TAPPING_TERM_MODIFIER;

        default:
            return TAPPING_TERM;
    }
}