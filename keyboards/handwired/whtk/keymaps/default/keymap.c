#include QMK_KEYBOARD_H
#include "whtk.h"
#include "ps2_mouse.h"

#define KC_THUMB_L0 LT(LAYER_SYM_NAV, KC_SPC)
#define KC_THUMB_L1 LCTL_T(KC_TAB)
#define KC_THUMB_R0 LT(LAYER_FUN_NUM, KC_ENT)
#define KC_THUMB_R1 RSFT_T(KC_BSPC)

// thee row mode thumb keys
#define KC_THUMB_L0_3 LT(LAYER_BRC_NAV, KC_SPC)
#define KC_THUMB_R0_3 LT(LAYER_SYMBOL, KC_ENT)


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
    SHOW_LEGEND,
    TOGGLE_LEGEND,
    KC_DOT_COMM,
    KC_EXLM_QUES,
    KC_SLSH_BSLS,
    MOUSE_ACC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // four row mode layers
    [LAYER_ALP_PUN] = LAYOUT_WHTK(
                                      KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH_BSLS,                 KC_QUOT,       KC_DOT_COMM,   KC_EXLM_QUES,  KC_SCLN,
                                      KC_W,          KC_E,          KC_R,          KC_T,                         KC_Y,          KC_U,          KC_I,          KC_O,
        TOGGLE_MODE,   KC_Q,          KC_S,          KC_D,          KC_F,          KC_G,                         KC_H,          KC_J,          KC_K,          KC_L,          KC_P,          KC_PSCR,
      MO(LAYER_MOUSE), KC_A,          KC_Z,          KC_X,          KC_C,          KC_V,                         KC_B,          KC_N,          KC_M,          KC_DEL,        KC_ESC,        KC_INS,
        KC_LALT,       KC_LSFT,                      KC_THUMB_L1,   KC_THUMB_L0, KC_LGUI,                    OSL(LAYER_UMLAUT), KC_THUMB_R0,   KC_THUMB_R1,                  KC_RCTL,       KC_RALT
    ),
    [LAYER_SYM_NAV] = LAYOUT_WHTK(
                                      KC_AT,         KC_LT,         KC_GT,         KC_CIRC,                      XXXXXXX,       KC_PREV_TAB,   XXXXXXX,       KC_NEXT_TAB,
                                      KC_HASH,       KC_LCBR,       KC_RCBR,       KC_ASTR,                      KC_PGUP,       KC_PREV_WORD,  KC_UP,         KC_NEXT_WORD,
        TOGGLE_LEGEND, XXXXXXX,       KC_DLR,        KC_LPRN,       KC_RPRN,       KC_AMPR,                      KC_HOME,       KC_LEFT,       KC_DOWN,       KC_RGHT,       XXXXXXX,       KC_PAUS,
      TG(LAYER_MOUSE), XXXXXXX,       KC_PERC,       KC_LBRC,       KC_RBRC,       KC_PIPE,                      KC_PGDN,       XXXXXXX,       XXXXXXX,       XXXXXXX,       KC_END,        KC_SLCK,
        _______,       _______,                      _______,       _______,       _______,                      _______,       _______,       KC_BSPC,                      _______,       _______
    ),
    // three row mode layers
    [LAYER_ALPHA] = LAYOUT_WHTK(
                                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
                                      KC_W,          KC_E,          KC_R,          KC_T,                         KC_Y,          KC_U,          KC_I,          KC_O,
        TOGGLE_MODE,   KC_Q,          KC_S,          KC_D,          KC_F,          KC_G,                         KC_H,          KC_J,          KC_K,          KC_L,          KC_P,          XXXXXXX,
      MO(LAYER_MOUSE), KC_A,          KC_Z,          KC_X,          KC_C,          KC_V,                         KC_B,          KC_N,          KC_M,          KC_DEL,        KC_ESC,        XXXXXXX,
        KC_LALT,       KC_LSFT,                      KC_THUMB_L1,   KC_THUMB_L0_3, KC_LGUI,                 MO(LAYER_FUN_NUM),  KC_THUMB_R0_3, KC_THUMB_R1,                MO(LAYER_THUMB), KC_RALT
    ),
    [LAYER_THUMB] = LAYOUT_WHTK(
                                      _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,
                                      _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,       _______,
        _______,       _______,       _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,       _______,       _______,
        _______,       _______,                      KC_TAB,        KC_SPC,        _______,                      _______,       KC_ENT,        KC_BSPC,                      _______,       _______
    ),
    [LAYER_BRC_NAV] = LAYOUT_WHTK(
                                      _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,
                                      _______,       KC_LCBR,       KC_RCBR,       _______,                      KC_PGUP,       KC_PREV_WORD,  KC_UP,         KC_NEXT_WORD,
        TOGGLE_LEGEND, XXXXXXX,       KC_LT,         KC_LPRN,       KC_RPRN,       KC_GT,                        KC_HOME,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_PSCR,       _______,
      TG(LAYER_MOUSE), XXXXXXX,       _______,       KC_LBRC,       KC_RBRC,       _______,                      KC_PGDN,       KC_PREV_TAB,   XXXXXXX,       KC_NEXT_TAB,   KC_END,        _______,
        _______,       _______,                      _______,       _______,       _______,                      _______,       _______,       _______,                      _______,       _______
    ),
    [LAYER_SYMBOL] = LAYOUT_WHTK(
                                      _______,       _______,       _______,       _______,                      _______,       _______,       _______,       _______,
                                      KC_TILD,       KC_PLUS,       KC_UNDS,       KC_BSLS,                      KC_DQUO,       KC_COMM,       KC_QUES,       KC_COLN,
        _______,       _______,       KC_GRV,        KC_EQL,        KC_MINS,       KC_SLSH,                      KC_QUOT,       KC_DOT,        KC_EXLM,       KC_SCLN,       _______,       _______,
        _______,       _______,       KC_PIPE,       KC_AMPR,       KC_ASTR,       KC_CIRC,                      KC_AT,         KC_HASH,       KC_DLR,        KC_PERC,       _______,       _______,
        _______,       _______,                      _______,       _______,       _______,                      _______,       _______,       _______,                      _______,       _______
    ),
    // general layers
    [LAYER_FUN_NUM] = LAYOUT_WHTK(
                                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
                                      KC_F1,         KC_F2,         KC_F3,         KC_F4,                        KC_0,          KC_1,          KC_2,          KC_3,
        XXXXXXX,       XXXXXXX,       KC_F5,         KC_F6,         KC_F7,         KC_F8,                        KC_DOT,        KC_4,          KC_5,          KC_6,          XXXXXXX,       RESET,
        XXXXXXX,       XXXXXXX,       KC_F9,         KC_F10,        KC_F11,        KC_F12,                       KC_COMM,       KC_7,          KC_8,          KC_9,          XXXXXXX,       XXXXXXX,
        _______,       _______,                      _______,       _______,       _______,                      _______,       _______,       _______,                      _______,       _______
    ),
    [LAYER_UMLAUT] = LAYOUT_WHTK(
                                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
                                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       RALT(KC_Y),    XXXXXXX,       RALT(KC_P),
        XXXXXXX,       XXXXXXX,       RALT(KC_S),    XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       RALT(KC_Q),    XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       KC_LSFT,                      XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       KC_RSFT,                      XXXXXXX,       XXXXXXX
    ),
    [LAYER_MOUSE] = LAYOUT_WHTK(
                                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
                                      XXXXXXX,       KC_WH_U,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,       KC_WH_L,       KC_WH_D,       KC_WH_R,       XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
      MO(LAYER_MOUSE), XXXXXXX,       XXXXXXX,       XXXXXXX,       MOUSE_ACC,     XXXXXXX,                      XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,       XXXXXXX,
        XXXXXXX,       XXXXXXX,                      KC_BTN2,       KC_BTN1,       KC_BTN3,                      XXXXXXX,       XXXXXXX,       XXXXXXX,                      XXXXXXX,       XXXXXXX
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
    // show legend
    switch (keycode) {
        case SHOW_LEGEND:
            set_legend(record->event.pressed);
            return false;

        case TOGGLE_LEGEND:
            if (record->event.pressed) {
                set_legend(!get_legend());
            }
            return false;
    }
    return true;
}


////////// Mode alternatives //////////
void update_default_layer(void) {
    if (get_mode().rows == ROWS_3)
    {
        layer_move(LAYER_ALPHA);
    }
    else
    {
        layer_move(LAYER_ALP_PUN);
    }
}

void update_swap_lctl_lgui(void) {
    keymap_config.swap_lctl_lgui = (get_mode().os == OS_MAC);
}

void switch_mode(mode_t mode) {
    set_mode(mode);
    update_default_layer();
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
        if (mode.rows == ROWS_3)
        {
            mode.rows = ROWS_4;
        }
        else
        {
            mode.rows = ROWS_3;
        }
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
    if (mode.rows != ROWS_3 && mode.rows != ROWS_4)
    {
        // default rows if eeprom value is invalid
        mode.rows = ROWS_3;
    }
    mode.padding = 0;
    set_mode(mode);
    update_default_layer();
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
        case KC_DOT_COMM:
            shift_cleared(record, KC_DOT, KC_COMM);
            return false;

        case KC_EXLM_QUES:
            shift_cleared(record, KC_EXLM, KC_QUES);
            return false;

        case KC_SLSH_BSLS:
            shift_cleared(record, KC_SLSH, KC_BSLS);
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
        case KC_THUMB_L0_3:
        // enter
        case KC_THUMB_R0:
        case KC_THUMB_R0_3:
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


////////// Touchpad config //////////
#ifdef PS2_MOUSE_ENABLE

void ps2_mouse_init_user(void) {
    ps2_mouse_set_resolution(PS2_MOUSE_8_COUNT_MM);
    // ps2_mouse_set_sample_rate(200);
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool is_mouse_layer_active = get_highest_layer(layer_state) == LAYER_MOUSE;
    bool is_mouse_accurate_pressed = (keycode == MOUSE_ACC) && record->event.pressed;
    if (is_mouse_layer_active) {
        if (is_mouse_accurate_pressed) {
            ps2_mouse_set_resolution(PS2_MOUSE_2_COUNT_MM);
            set_mouse_accurate(true);
        } else {
            ps2_mouse_set_resolution(PS2_MOUSE_4_COUNT_MM);
            set_mouse_accurate(false);
        }
    } else {
        ps2_mouse_set_resolution(PS2_MOUSE_8_COUNT_MM);
        set_mouse_accurate(false);
    }
}

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    register_mousemove();
}

#endif
