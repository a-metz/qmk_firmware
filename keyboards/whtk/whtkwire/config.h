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
#pragma once

#include "config_common.h"

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001

#define MANUFACTURER whtk
#define PRODUCT whtkpill

#define MATRIX_ROWS 5
#define MATRIX_COLS 10
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 50

#define MATRIX_COL_PINS \
    { A4, A3, A2, A1, A0, A8, B15, B14, B13, B12 }

#define MATRIX_ROW_PINS \
    { B3, B4, B5, B6, B7 }

#define I2C_DRIVER        I2CD1
#define I2C1_SCL_PIN      B8
#define I2C1_SDA_PIN      B9
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PAL_MODE 4

#define OLED_DISPLAY_128X32
#define OLED_IC OLED_IC_SSD1305
#define OLED_COLUMN_OFFSET 4
#define OLED_FONT_H "glcdfont_improved.c"