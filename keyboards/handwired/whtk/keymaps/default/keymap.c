#include QMK_KEYBOARD_H
#include "whtk.h"

#define KC_THUMB_L0 LT(LAYER_SYM_NAV, KC_SPC)
#define KC_THUMB_L1 LCTL_T(KC_TAB)
#define KC_THUMB_R0 LT(LAYER_FUN_NUM, KC_ENT)
#define KC_THUMB_R1 RSFT_T(KC_BSPC)
#define KC_THUMB_R1_F RSFT_T(KC_DEL)

#define KC_PREV_WORD LCTL(KC_LEFT)
#define KC_NEXT_WORD LCTL(KC_RGHT)
#define KC_PREV_TAB LCTL(KC_PGUP)
#define KC_NEXT_TAB LCTL(KC_PGDN)

#ifndef DYNAMIC_MACRO_ENABLE
#   define MACRO_1_PLAY KC_NO
#   define MACRO_1_REC KC_NO
#   define MACRO_2_PLAY KC_NO
#   define MACRO_2_REC KC_NO
#   define MACRO_REC_STOP KC_NO
#endif

enum custom_keycodes {
    TOGGLE_MODE = SAFE_RANGE,
    SWITCH_LINUX,
    SWITCH_MAC,
    KC_DOT_COMM,
    KC_EXLM_QUES,
    KC_SLSH_BSLS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_ALPHA] = LAYOUT_WHTK(
                                      KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH_BSLS,                 KC_QUOT,       KC_DOT_COMM,   KC_EXLM_QUES,  KC_SCLN,
                                      KC_W,          KC_E,          KC_R,          KC_T,                         KC_Y,          KC_U,          KC_I,          KC_O,
        MACRO_1_PLAY,  KC_Q,          KC_S,          KC_D,          KC_F,          KC_G,                         KC_H,          KC_J,          KC_K,          KC_L,          KC_P,          KC_PSCR,
        MACRO_2_PLAY,  KC_A,          KC_Z,          KC_X,          KC_C,          KC_V,                         KC_B,          KC_N,          KC_M,          KC_DEL,        KC_ESC,        KC_INS,
        KC_LALT,       KC_LSFT,                      KC_THUMB_L1,   KC_THUMB_L0,   KC_LGUI,                  OSL(LAYER_UMLAUT), KC_THUMB_R0,   KC_THUMB_R1,                  KC_RCTL,       KC_RALT
    ),
    [LAYER_SYM_NAV] = LAYOUT_WHTK(
                                      KC_AT,         KC_LT,         KC_GT,         KC_CIRC,                      KC_PREV_TAB,   KC_NEXT_TAB,   KC_NO,         KC_NO,
                                      KC_HASH,       KC_LCBR,       KC_RCBR,       KC_ASTR,                      KC_PGUP,       KC_PREV_WORD,  KC_UP,         KC_NEXT_WORD,
        RESET,         KC_NO,         KC_DLR,        KC_LPRN,       KC_RPRN,       KC_AMPR,                      KC_PGDN,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_NO,         KC_PAUS,
        TOGGLE_MODE,   KC_NO,         KC_PERC,       KC_LBRC,       KC_RBRC,       KC_PIPE,                      KC_HOME,       KC_HOME,       KC_NO,         KC_END,        KC_NO,         KC_SLCK,
        KC_TRNS,       KC_TRNS,                      KC_TRNS,       KC_TRNS,       KC_TRNS,                      KC_TRNS,       KC_TRNS,       KC_THUMB_R1_F,                KC_TRNS,       KC_TRNS
    ),
    [LAYER_FUN_NUM] = LAYOUT_WHTK(
                                      KC_NO,         KC_NO,         KC_NO,         KC_NO,                        KC_COMM,       KC_DOT,        KC_NO,         KC_NO,
                                      KC_F1,         KC_F2,         KC_F3,         KC_F4,                        KC_0,          KC_1,          KC_2,          KC_3,
        MACRO_1_REC,  MACRO_REC_STOP, KC_F5,         KC_F6,         KC_F7,         KC_F8,                        KC_NO,         KC_4,          KC_5,          KC_6,          KC_NO,         RESET,
        MACRO_2_REC,  MACRO_REC_STOP, KC_F9,         KC_F10,        KC_F11,        KC_F12,                       KC_NO,         KC_7,          KC_8,          KC_9,          KC_NO,         TOGGLE_MODE,
        KC_TRNS,       KC_TRNS,                      KC_TRNS,       KC_TRNS,       KC_TRNS,                      KC_TRNS,       KC_TRNS,       KC_TRNS,                      KC_TRNS,       KC_TRNS
    ),
    [LAYER_UMLAUT] = LAYOUT_WHTK(
                                      KC_NO,         KC_NO,         KC_NO,         KC_NO,                        KC_NO,         KC_NO,         KC_NO,         KC_NO,
                                      KC_NO,         KC_NO,         KC_NO,         KC_NO,                        KC_NO,         RALT(KC_Y),    KC_NO,         RALT(KC_P),
        KC_NO,         KC_NO,         RALT(KC_S),    KC_NO,         KC_NO,         KC_NO,                        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,
        KC_NO,         RALT(KC_Q),    KC_NO,         KC_NO,         KC_NO,         KC_NO,                        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,
        KC_NO,         KC_LSFT,                      KC_NO,         KC_NO,         KC_NO,                        KC_NO,         KC_NO,         KC_RSFT,                      KC_NO,         KC_NO
    )
};


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


////////// Mode alternatives //////////
bool process_record_user_mode(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode == SWITCH_LINUX || (keycode == TOGGLE_MODE && get_mode() == MODE_MAC)) {
            set_mode(MODE_LINUX);
            keymap_config.swap_lctl_lgui = false;
            return false;
        }

        if (keycode == SWITCH_MAC || (keycode == TOGGLE_MODE && get_mode() == MODE_LINUX)) {
            set_mode(MODE_MAC);
            keymap_config.swap_lctl_lgui = true;
            return false;
        }
    }

    // skip keycode remapping for linux mode
    if (get_mode() == MODE_LINUX) {
        return true;
    }

    switch (keycode) {
        KC_MAP(KC_PREV_WORD, LALT(KC_LEFT))
        KC_MAP(KC_NEXT_WORD, LALT(KC_RGHT))
        KC_MAP(KC_PREV_TAB, LCTL(LSFT(KC_TAB)))
        KC_MAP(KC_NEXT_TAB, LCTL(KC_TAB))
        KC_MAP(KC_HOME, LGUI(KC_LEFT))
        KC_MAP(KC_END, LGUI(KC_RGHT))

        KC_MAP(OSL(LAYER_UMLAUT), LALT(KC_U))  // mac umlaut leader

        default:
            return true;
    }

}
////////// Shifted keycodes //////////
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
    if (record->event.pressed)
    {
        register_keypress();
    }

    return process_record_user_mode(keycode, record) &&
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
