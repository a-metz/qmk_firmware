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
#include "whtkpill.h"


//////////// Keymap //////////
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
        XXXXXXX,       KC_F1,         KC_F2,         KC_F3,         KC_F4,                        KC_0,          KC_1,          KC_2,          KC_3,          RESET,
        XXXXXXX,       KC_F5,         KC_F6,         KC_F7,         KC_F8,                        KC_DOT,        KC_4,          KC_5,          KC_6,          XXXXXXX,
        XXXXXXX,       KC_F9,         KC_F10,        KC_F11,        KC_F12,                       KC_COMM,       KC_7,          KC_8,          KC_9,          XXXXXXX,
                                      _______,       _______,       _______,                      _______,       _______,       _______
    ),
    [LAYER_UMLAUT] = LAYOUT(
                       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       RALT(KC_Y),    XXXXXXX,       RALT(KC_P),    XXXXXXX,
        RALT(KC_Q),    RALT(KC_S),    XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        KC_LSFT,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
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
void update_swap_lctl_lgui(void) {
    keymap_config.swap_lctl_lgui = (get_mode().os == OS_MAC);
}

void switch_mode(mode_t mode) {
    set_mode(mode);
    update_swap_lctl_lgui();
    eeconfig_update_user(mode.raw);
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

void keyboard_post_init_user(void) {
    // load persistent value
    mode_t mode = {
        .raw = eeconfig_read_user()
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
#define NUM_COLUMNS OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH

static void render_oled(void) {
    oled_write_P(PSTR("Whtkpill\n"), false);
    oled_write_P(PSTR("\n"), false);
    switch (get_highest_layer(layer_state)) {
        case LAYER_ALP_PUN:
            oled_write_P(PSTR("Alpha\n"), false);
            break;
        case LAYER_SYM_NAV:
            oled_write_P(PSTR("Symbol & Navigation\n"), false);
            break;
        case LAYER_FUN_NUM:
            oled_write_P(PSTR("Function & Number\n"), false);
            break;
        case LAYER_THUMB:
            oled_write_P(PSTR("Thumb hold\n"), false);
            break;
        case LAYER_UMLAUT:
            oled_write_P(PSTR("Umlaut\n"), false);
            break;
        default:
            oled_write_P(PSTR("\n"), false);
            break;
    }
    oled_write_P(PSTR("\n"), false);
    switch (get_mode().os) {
        case OS_LINUX:
            oled_write_P(PSTR("Linux\n"), false);
            break;
        case OS_MAC:
            oled_write_P(PSTR("Mac\n"), false);
            break;
        default:
            oled_write_P(PSTR("\n"), false);
            break;
    }

    oled_write_P(PSTR("\n"), false);
    uint8_t mods = get_mods();
    if (mods) {
        bool ctrl = mods & MOD_MASK_CTRL;
        bool alt = mods & MOD_MASK_ALT;
        bool shift = mods & MOD_MASK_SHIFT;
        bool super = mods & MOD_MASK_GUI;
        // calculate string length and necessary padding to center text
        uint8_t length = (ctrl * 5) + (alt * 4) + (shift * 6) + (super * 6) - 1;
        uint8_t padding = (NUM_COLUMNS - length + 1) / 2;

        for (uint8_t i = 0; i < padding; i++) {
            oled_write_P(PSTR(" "), false);
        }
        if (ctrl) oled_write_P(PSTR("CTRL "), false);
        if (alt) oled_write_P(PSTR("ALT "), false);
        if (shift) oled_write_P(PSTR("SHIFT "), false);
        if (super) oled_write_P(PSTR("SUPER"), false);
    }
    oled_write_P(PSTR("\n"), false);

}

bool oled_task_user(void) {
    render_oled();
    return false;
}

#endif