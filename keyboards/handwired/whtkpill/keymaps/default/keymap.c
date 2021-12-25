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


#define KC_THUMB_L0 LT(LAYER_SYM_NAV, KC_SPC)
#define KC_THUMB_L1 LCTL_T(KC_TAB)
#define KC_THUMB_R0 LT(LAYER_FUN_NUM, KC_ENT)
#define KC_THUMB_R1 RSFT_T(KC_BSPC)


typedef enum _layer_t {
    // four row mode layers
    LAYER_ALP_PUN = 0,
    LAYER_SYM_NAV,
    // general layers
    LAYER_FUN_NUM,
    LAYER_UMLAUT,
    LAYER_MOUSE,
} layer_t;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_ALP_PUN] = LAYOUT(
                       KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH,                      KC_QUOT,       KC_DOT,        KC_EXLM,       KC_SCLN,
        KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                         KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,
        KC_A,          KC_S,          KC_D,          KC_F,          KC_G,                         KC_H,          KC_J,          KC_K,          KC_L,          KC_ESC,
        KC_LSFT,       KC_Z,          KC_X,          KC_C,          KC_V,                         KC_B,          KC_N,          KC_M,          KC_DEL,        XXXXXXX,
                                      KC_THUMB_L1,   KC_THUMB_L0,   KC_LGUI,                      KC_LALT,       KC_THUMB_R0,   KC_THUMB_R1
    ),
    [LAYER_SYM_NAV] = LAYOUT(
                       KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH,                      KC_QUOT,       KC_DOT,        KC_EXLM,       KC_SCLN,
        KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,                         KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,
        KC_A,          KC_S,          KC_D,          KC_F,          KC_G,                         KC_H,          KC_J,          KC_K,          KC_L,          KC_ESC,
        KC_LSFT,       KC_Z,          KC_X,          KC_C,          KC_V,                         KC_B,          KC_N,          KC_M,          KC_DEL,        XXXXXXX,
                                      KC_THUMB_L1,   KC_THUMB_L0,   KC_LGUI,                      KC_LALT,       KC_THUMB_R0,   KC_THUMB_R1
    ),
};

#ifdef OLED_ENABLE

static void render_oled(void) {
    oled_write_P(PSTR("Whtkpill\n"), false);
    oled_write_P(PSTR("\n"), false);
    switch (get_highest_layer(layer_state)) {
        case LAYER_ALP_PUN:
            oled_write_P(PSTR("LAYER_ALP_PUN\n"), false);
            break;
        case LAYER_SYM_NAV:
        default:
            oled_write_P(PSTR("LAYER_SYM_NAV\n"), false);
            break;
    }
}

bool oled_task_user(void) {
    render_oled();
    return false;
}

#endif