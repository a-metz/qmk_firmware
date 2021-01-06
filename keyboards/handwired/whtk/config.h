#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    whtk
#define PRODUCT         whtk
#define DESCRIPTION     My split keyboard

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D2

#define MASTER_RIGHT

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4, B5 }
#define MATRIX_ROW_PINS { F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

#ifdef OLED_DRIVER_ENABLE
#   define OLED_DISPLAY_128X64
#	define OLED_FONT_H "glcdfont_improved.c"
#endif

#ifdef PS2_USE_INT
#   ifdef OLED_DRIVER_ENABLE
#       error "Cannot use PS2 while OLED is enabled"
#   endif

#   define PS2_MOUSE_USE_REMOTE_MODE
#   define PS2_CLOCK_PORT  PORTD
#   define PS2_CLOCK_PIN   PIND
#   define PS2_CLOCK_DDR   DDRD
#   define PS2_CLOCK_BIT   0
#   define PS2_DATA_PORT   PORTD
#   define PS2_DATA_PIN    PIND
#   define PS2_DATA_DDR    DDRD
#   define PS2_DATA_BIT    1

#   define PS2_INT_INIT() do {      \
        EICRA |= ((1<<ISC01) |      \
                  (0<<ISC00));      \
    } while (0)
    #define PS2_INT_ON()  do {      \
        EIMSK |= (1<<INT0);         \
    } while (0)
    #define PS2_INT_OFF() do {      \
        EIMSK &= ~(1<<INT0);        \
    } while (0)
#   define PS2_INT_VECT   INT0_vect
#endif