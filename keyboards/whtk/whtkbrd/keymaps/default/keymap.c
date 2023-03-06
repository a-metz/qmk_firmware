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
#include "whtkbrd.h"

#include "shift_alternative.h"
#include "state.h"
#include "oled.h"

//////////// Keymap //////////
typedef enum _layer_t {
    LAYER_ALP_PUN = 0,
    LAYER_SYM_NAV,
    LAYER_THUMB,
    LAYER_FUN_NUM,
    LAYER_UMLAUT,
} layer_t;

#define KC_THUMB_L0 LT(LAYER_SYM_NAV, KC_SPC)
#define KC_THUMB_L1 LCTL_T(KC_TAB)
#define KC_THUMB_R0 LT(LAYER_FUN_NUM, KC_ENT)
#define KC_THUMB_R1 RSFT_T(KC_BSPC)

#define KC_PREV_WORD LCTL(KC_LEFT)
#define KC_NEXT_WORD LCTL(KC_RGHT)
#define KC_PREV_TAB LCTL(KC_PGUP)
#define KC_NEXT_TAB LCTL(KC_PGDN)

enum custom_keycodes {
    TOGGLE_MODE = SAFE_RANGE,
    KC_SLSH_BSLS,
    KC_DOT_COMM,
    KC_EXLM_QUES,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_ALP_PUN] = LAYOUT(
        XXXXXXX,       XXXXXXX,       KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH_BSLS,                 KC_QUOT,       KC_DOT_COMM,   KC_EXLM_QUES,  KC_SCLN,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                         KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,          XXXXXXX,
        XXXXXXX,       KC_A,          KC_S,          KC_D,          KC_F,          KC_G,                         KC_H,          KC_J,          KC_K,          KC_L,          KC_ESC,        XXXXXXX,
        XXXXXXX,       KC_LSFT,       KC_Z,          KC_X,          KC_C,          KC_V,                         KC_B,          KC_N,          KC_M,          KC_DEL,      MO(LAYER_THUMB), XXXXXXX,
                                      XXXXXXX,       KC_THUMB_L1,   KC_THUMB_L0,   KC_LGUI,                      KC_LALT,       KC_THUMB_R0,   KC_THUMB_R1,   XXXXXXX
    ),
    [LAYER_SYM_NAV] = LAYOUT(
        XXXXXXX,       XXXXXXX,       KC_AT,         KC_LT,         KC_GT,         KC_CIRC,                      XXXXXXX,       KC_PREV_TAB,   XXXXXXX,       KC_NEXT_TAB,   XXXXXXX,       XXXXXXX,
        XXXXXXX,       TOGGLE_MODE,   KC_HASH,       KC_LCBR,       KC_RCBR,       KC_ASTR,                      KC_PGUP,       KC_PREV_WORD,  KC_UP,         KC_NEXT_WORD,  KC_PSCR,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_DLR,        KC_LPRN,       KC_RPRN,       KC_AMPR,                      KC_HOME,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_END,        XXXXXXX,
        XXXXXXX,       _______,       KC_PERC,       KC_LBRC,       KC_RBRC,       KC_PIPE,                      KC_PGDN,       XXXXXXX,       XXXXXXX,       KC_INS,        _______,       XXXXXXX,
                                      XXXXXXX,       _______,       _______,       _______,                      _______,       _______,       _______,       XXXXXXX
    ),
    [LAYER_THUMB] = LAYOUT(
        XXXXXXX,       XXXXXXX,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,       XXXXXXX,
        XXXXXXX,       _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,       XXXXXXX,
        XXXXXXX,       _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,       XXXXXXX,
                                      XXXXXXX,       KC_TAB,        KC_SPC,        OSL(LAYER_UMLAUT),            KC_RALT,       KC_ENT,        KC_BSPC,       XXXXXXX
    ),
    [LAYER_FUN_NUM] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_F1,         KC_F2,         KC_F3,         KC_F4,                        KC_0,          KC_1,          KC_2,          KC_3,          RESET,         XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_F5,         KC_F6,         KC_F7,         KC_F8,                        KC_DOT,        KC_4,          KC_5,          KC_6,          XXXXXXX,       XXXXXXX,
        XXXXXXX,       _______,       KC_F9,         KC_F10,        KC_F11,        KC_F12,                       KC_COMM,       KC_7,          KC_8,          KC_9,          XXXXXXX,       XXXXXXX,
                                      XXXXXXX,       _______,       _______,       _______,                      _______,       _______,       _______,       XXXXXXX
    ),
    [LAYER_UMLAUT] = LAYOUT(
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       RALT(KC_Y),    XXXXXXX,       RALT(KC_P),    XXXXXXX,       XXXXXXX,
        XXXXXXX,       RALT(KC_Q),    RALT(KC_S),    XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       _______,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
                                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       KC_RSFT,       XXXXXXX
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
    // nothing for now
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


////////// Key based tapping term //////////
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        // space
        case KC_THUMB_L0:
        // enter
        case KC_THUMB_R0:
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


////////// Update LEDs //////////
void update_leds(void) {
    switch (get_highest_layer(layer_state)) {
        case LAYER_ALP_PUN:
            writePinLow(LED_PWR_PIN);
            writePinLow(LED_STAT_PIN);
            break;
        case LAYER_SYM_NAV:
            writePinLow(LED_PWR_PIN);
            writePinHigh(LED_STAT_PIN);
            break;
        case LAYER_FUN_NUM:
            writePinHigh(LED_PWR_PIN);
            writePinLow(LED_STAT_PIN);
            break;
        case LAYER_THUMB:
            break;
        case LAYER_UMLAUT:
            break;
        default:
            break;
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
    update_keyboard_state();
    update_leds();
}
