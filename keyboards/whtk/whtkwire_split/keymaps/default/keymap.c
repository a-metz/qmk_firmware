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
        _______,       KC_PERC,       KC_LBRC,       KC_RBRC,       KC_PIPE,                      KC_PGDN,       XXXXXXX,       XXXXXXX,       KC_INS,        _______,
                                      _______,       _______,       _______,                      _______,       _______,       _______
    ),
    [LAYER_THUMB] = LAYOUT(
                       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,
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


////////// Display stuff //////////
#ifdef OLED_ENABLE

void render_oled(void) {
    // 'small_test', 64x32px
    static const char epd_bitmap_small_test [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x38, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1c, 0x23, 0xe0, 0xe0, 0x20, 0x10, 0x10, 0x09, 0x07, 0x03, 0x07, 0x06, 0x06, 0x0c, 
	0x0c, 0x18, 0x18, 0xf0, 0x30, 0x10, 0x10, 0xf0, 0xb0, 0xb0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x38, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
	0x7f, 0xff, 0xff, 0xff, 0x7f, 0x07, 0x0f, 0x1e, 0x1e, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x38, 0xc4, 0x07, 0x07, 0x04, 0x08, 0x08, 0x90, 0xe0, 0xc0, 0xe0, 0x60, 0x70, 0x30, 
	0x38, 0x1c, 0x1e, 0x0f, 0x0c, 0x0c, 0x0e, 0x0f, 0x0d, 0x0d, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_clear();
    oled_write_raw_P(epd_bitmap_small_test, sizeof(epd_bitmap_small_test));

    // uint8_t mods = get_mods();
    // switch (get_highest_layer(layer_state)) {
    //     case LAYER_ALP_PUN:
    //         if (mods) {
    //             oled_write_P(PSTR("\n"), false);
    //             oled_write_P(PSTR("        Alpha        "), false);
    //             oled_write_P(PSTR("\n"), false);
    //             render_mods();
    //         } else {
    //             oled_write_P(PSTR("\n"), false);
    //             oled_write_P(PSTR("        Alpha        "), false);
    //             oled_write_P(PSTR("\n"), false);
    //             render_os();
    //         }
    //         break;
    //     case LAYER_SYM_NAV:
    //         oled_write_P(PSTR("@ < > ^              "), false);
    //         oled_write_P(PSTR("# { } *     Symbol & "), false);
    //         oled_write_P(PSTR("$ ( ) &    Navigation"), false);
    //         if (mods) {
    //             render_mods();
    //         } else {
    //             oled_write_P(PSTR("% [ ] |\n"), false);
    //         }
    //         break;
    //     case LAYER_FUN_NUM:
    //         oled_write_P(PSTR("              0 1 2 3"), false);
    //         oled_write_P(PSTR("Function        4 5 6"), false);
    //         oled_write_P(PSTR("& Number        7 8 9"), false);
    //         render_mods();
    //         break;
    //     case LAYER_THUMB:
    //         oled_write_P(PSTR("\n"), false);
    //         oled_write_P(PSTR("     Thumb hold\n"), false);
    //         oled_write_P(PSTR("\n"), false);
    //         if (mods) {
    //             render_mods();
    //         } else {
    //             render_os();
    //         }
    //         break;
    //     case LAYER_UMLAUT:
    //         oled_write_P(PSTR("\n"), false);
    //         oled_write_P(PSTR("       Umlaut\n"), false);
    //         oled_write_P(PSTR("\n"), false);
    //         if (mods) {
    //             render_mods();
    //         } else {
    //             render_os();
    //         }
    //         break;
    //     default:
    //         break;
    // }
}

bool oled_task_user(void) {
    render_oled();
    return false;
}

#endif