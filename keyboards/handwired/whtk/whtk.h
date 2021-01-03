#pragma once

#include "quantum.h"


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

////////// Utilities for alternative shifted keycodes //////////
bool check_mod_and_clear(uint16_t mod_keycode);

void mod_set(uint16_t mod_keycode);

void mod_clear(uint16_t mod_keycode);

void mod_restore(uint16_t mod_keycode);

void shift_cleared_alternative(keyrecord_t *record, uint16_t keycode, uint16_t modded_keycode);

void shift_all_alternative(keyrecord_t *record, uint16_t keycode, uint16_t modded_keycode);
