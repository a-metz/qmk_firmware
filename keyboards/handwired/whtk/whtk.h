#pragma once

#include "quantum.h"

////////// Layout //////////
#define LAYOUT_WHTK( \
              L02, L03, L04, L05,      R05, R04, R03, R02,           \
              L12, L13, L14, L15,      R15, R14, R13, R12,           \
    L20, L21, L22, L23, L24, L25,      R25, R24, R23, R22, R21, R20, \
    L30, L31, L32, L33, L34, L35,      R35, R34, R33, R32, R31, R30, \
    L40, L41,      L43, L44, L45,      R45, R44, R43,      R41, R40 \
    ) \
    { \
      { KC_NO, KC_NO,   L02,   L03,   L04,   L05 }, \
      { KC_NO, KC_NO,   L12,   L13,   L14,   L15 }, \
      {   L20,   L21,   L22,   L23,   L24,   L25 }, \
      {   L30,   L31,   L32,   L33,   L34,   L35 }, \
      {   L40,   L41, KC_NO,   L43,   L44,   L45 }, \
                                                    \
      { KC_NO, KC_NO,   R02,   R03,   R04,   R05 }, \
      { KC_NO, KC_NO,   R12,   R13,   R14,   R15 }, \
      {   R20,   R21,   R22,   R23,   R24,   R25 }, \
      {   R30,   R31,   R32,   R33,   R34,   R35 }, \
      {   R40,   R41, KC_NO,   R43,   R44,   R45 }, \
    }

typedef enum _layer_t {
    LAYER_ALPHA = 0,
    LAYER_SYM_NAV,
    LAYER_FUN_NUM,
    LAYER_UMLAUT,
    LAYER_MOUSE,
} layer_t;

typedef enum _mode_t {
    MODE_LINUX = 0,
    MODE_MAC,
} mode_t;

////////// Utilities for alternative shifted keycodes //////////
typedef struct _mod_cache {
    uint8_t mod_bit;
    bool empty;
    bool state;
} mod_cache_t;

void restore_shift(void);

void shift_cleared(keyrecord_t *record, uint16_t keycode, uint16_t modded_keycode);

////////// Synchronized state between keyboard sides //////////
typedef struct _keyboard_state_t {
    uint8_t keypress_count;
    uint8_t mousemove_count;
    layer_t active_layer;
    uint8_t modifiers;
    mode_t mode;
    bool legend;
    bool mouse_accurate;
} keyboard_state_t;

void set_keyboard_state(keyboard_state_t);

keyboard_state_t get_keyboard_state(void);

bool keyboard_state_equal(keyboard_state_t a, keyboard_state_t b);

void register_keypress(void);

void register_mousemove(void);

void update_keyboard_state(void);

void set_mode(mode_t);

mode_t get_mode(void);

void set_legend(bool legend);

bool get_legend(void);

void set_mouse_accurate(bool mouse_accurate);

bool get_mouse_accurate(void);
