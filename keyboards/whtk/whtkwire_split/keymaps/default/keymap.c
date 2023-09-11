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
#include QMK_KEYBOARD_H
#include "whtkwire_split.h"

#include "shift_alternative.h"
#include "state.h"
#include "oled.h"
#include "bitmaps.h"

//////////// Keymap //////////
typedef enum _layer_t {
    LAYER_ALP_PUN = 0,
    LAYER_SYM_NAV,
    LAYER_THUMB,
    LAYER_FUN_NUM,
    LAYER_UMLAUT,
    LAYER_POINTER,
} layer_t;

#define KC_THUMB_L0 LT(LAYER_SYM_NAV, KC_SPC)
#define KC_THUMB_L1 LCTL_T(KC_TAB)
#define KC_THUMB_R0 LT(LAYER_FUN_NUM, KC_ENT)
#define KC_THUMB_R1 RSFT_T(KC_BSPC)

#define KC_PREV_WORD LCTL(KC_LEFT)
#define KC_NEXT_WORD LCTL(KC_RGHT)
#define KC_PREV_TAB LCTL(KC_PGUP)
#define KC_NEXT_TAB LCTL(KC_PGDN)

#define KC_BSPC_WORD LCTL(KC_BSPC)
#define KC_DEL_WORD LCTL(KC_DEL)


enum custom_keycodes {
    TOGGLE_MODE = SAFE_RANGE,
    KC_SLSH_BSLS,
    KC_DOT_COMM,
    KC_EXLM_QUES,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_ALP_PUN] = LAYOUT(
                       KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH_BSLS,                 KC_QUOT,       KC_DOT_COMM,   KC_EXLM_QUES,  KC_SCLN,
        KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                         KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,
        KC_A,          KC_S,          KC_D,          KC_F,          KC_G,                         KC_H,          KC_J,          KC_K,          KC_L,          KC_ESC,
        KC_LSFT,       KC_Z,          KC_X,          KC_C,          KC_V,                         KC_B,          KC_N,          KC_M,          KC_DEL,        MO(LAYER_THUMB),
                                      KC_THUMB_L1,   KC_THUMB_L0,   KC_LGUI,                      KC_LALT,       KC_THUMB_R0,   KC_THUMB_R1
    ),
    [LAYER_SYM_NAV] = LAYOUT(
                       KC_AT,         KC_LT,         KC_GT,         KC_CIRC,                      XXXXXXX,       KC_PREV_TAB,   XXXXXXX,       KC_NEXT_TAB,
        TOGGLE_MODE,   KC_HASH,       KC_LCBR,       KC_RCBR,       KC_ASTR,                      KC_PGUP,       KC_PREV_WORD,  KC_UP,         KC_NEXT_WORD,  KC_PSCR,
        XXXXXXX,       KC_DLR,        KC_LPRN,       KC_RPRN,       KC_AMPR,                      KC_HOME,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_END,
        _______,       KC_PERC,       KC_LBRC,       KC_RBRC,       KC_PIPE,                      KC_PGDN,       XXXXXXX,       XXXXXXX,       KC_DEL_WORD,   TG(LAYER_THUMB),
                                      _______,       _______,       _______,                      _______,       _______,       KC_BSPC_WORD
    ),
    [LAYER_THUMB] = LAYOUT(
                       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       KC_INS,        _______,
                                      KC_TAB,        KC_SPC,        OSL(LAYER_UMLAUT),            KC_RALT,       KC_ENT,        KC_BSPC
    ),
    [LAYER_FUN_NUM] = LAYOUT(
                       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       KC_F1,         KC_F2,         KC_F3,         KC_F4,                        KC_0,          KC_1,          KC_2,          KC_3,          QK_BOOT,
        XXXXXXX,       KC_F5,         KC_F6,         KC_F7,         KC_F8,                        KC_DOT,        KC_4,          KC_5,          KC_6,          XXXXXXX,
        _______,       KC_F9,         KC_F10,        KC_F11,        KC_F12,                       KC_COMM,       KC_7,          KC_8,          KC_9,          XXXXXXX,
                                      _______,       _______,       _______,                      _______,       _______,       _______
    ),
    [LAYER_UMLAUT] = LAYOUT(
                       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       RALT(KC_Y),    XXXXXXX,       RALT(KC_P),    XXXXXXX,
        RALT(KC_Q),    RALT(KC_S),    XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        _______,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
                                      XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       KC_RSFT
    ),
    [LAYER_POINTER] = LAYOUT(
                       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,
        _______,       KC_BTN2,       KC_BTN3,       KC_BTN1,       _______,                      _______,       _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,
                                      _______,       _______,       _______,                      _______,       _______,       _______
    ),
};


//////////// Custom keycode handling //////////
#define KC_MAP(kc_from, kc_to) case (kc_from): map_to((kc_to), record); return false;

void map_to(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code16(keycode);
    } else {
        unregister_code16(keycode);
    }
}

bool process_record_user_custom(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode == QK_BOOT) {
            show_oled_bootloader();
        }
    }

    return true;
}


////////// Mode alternatives //////////
bool process_record_user_mode(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (keycode == TOGGLE_MODE) {
            toggle_mode();
            return false;
        }
    }

    // skip keycode remapping for non-mac mode
    if (get_mode().os != OS_MAC) {
        return true;
    }

    // alternatives in mac mode
    switch (keycode) {
        KC_MAP(KC_PREV_WORD, LALT(KC_LEFT))
        KC_MAP(KC_NEXT_WORD, LALT(KC_RGHT))
        KC_MAP(KC_PREV_TAB, LCTL(LSFT(KC_TAB)))
        KC_MAP(KC_NEXT_TAB, LCTL(KC_TAB))
        KC_MAP(KC_HOME, LGUI(KC_LEFT))
        KC_MAP(KC_END, LGUI(KC_RGHT))
        KC_MAP(KC_BSPC_WORD, LALT(KC_BSPC))
        KC_MAP(KC_DEL_WORD, LALT(KC_DEL))

        KC_MAP(OSL(LAYER_UMLAUT), LALT(KC_U))  // mac umlaut leader

        default:
            return true;
    }

}


////////// Shifted keycodes //////////
bool process_record_user_shift_alternative(uint16_t keycode, keyrecord_t *record) {
    restore_shift();

    switch (keycode) {
        case KC_SLSH_BSLS:
            shift_alternative(record, KC_SLSH, KC_BSLS);
            return false;

        case KC_DOT_COMM:
            shift_alternative(record, KC_DOT, KC_COMM);
            return false;

        case KC_EXLM_QUES:
            shift_alternative(record, KC_EXLM, KC_QUES);
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

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (IS_LAYER_ON(LAYER_SYM_NAV)) {
        set_drag_scroll(true);
    } else {
        set_drag_scroll(false);
    }

    update_keyboard_state();
}


////////// Key based tapping term //////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // space
        case KC_THUMB_L0:
        // enter
        case KC_THUMB_R0:
        // thumb hold
        case TT(LAYER_THUMB):
            return TAPPING_TERM_LAYER;
        // control
        case KC_THUMB_L1:
        // shift
        case KC_THUMB_R1:
            return TAPPING_TERM_MODIFIER;

        default:
            return TAPPING_TERM;
    }
}


////////// Keymap specific render layer override //////////
void render_layer(uint8_t layer) {
    switch (layer) {
        case LAYER_ALP_PUN:
            oled_write_raw(bitmap_alpha, OLED_MATRIX_SIZE);
            break;
        case LAYER_SYM_NAV:
            if (is_keyboard_left())
            {
                oled_write_raw(bitmap_sym, OLED_MATRIX_SIZE);
            } else {
                oled_write_raw(bitmap_nav, OLED_MATRIX_SIZE);
            }
            break;
        case LAYER_FUN_NUM:
            if (is_keyboard_left())
            {
                oled_write_raw(bitmap_func, OLED_MATRIX_SIZE);
            } else {
                oled_write_raw(bitmap_num, OLED_MATRIX_SIZE);
            }
            break;
        case LAYER_THUMB:
            oled_write_raw(bitmap_thumb, OLED_MATRIX_SIZE);
            break;
        case LAYER_UMLAUT:
            oled_write_raw(bitmap_umlaut, OLED_MATRIX_SIZE);
            break;
        case LAYER_POINTER:
            oled_write_raw(bitmap_pointer, OLED_MATRIX_SIZE);
            break;
        default:
            break;
    }
}


////////// Pointing device //////////
void pointing_device_init_user(void) {
    set_auto_mouse_layer(LAYER_POINTER);
    set_auto_mouse_enable(true);
}


////////// Encoder //////////
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t current_layer = get_highest_layer(layer_state);
    if (current_layer == LAYER_SYM_NAV) {
        if (get_mode().os != OS_MAC) {
            if (clockwise) {
                tap_code16(LALT(KC_RGHT));
            } else {
                tap_code16(LALT(KC_LEFT));
            }
        } else {
            if (clockwise) {
                tap_code16(KC_NEXT_WORD);
            } else {
                tap_code16(KC_PREV_WORD);
            }
        }
    } else {
        if (clockwise) {
            tap_code16(KC_RGHT);
        } else {
            tap_code16(KC_LEFT);
        }
    }

    return true;
}