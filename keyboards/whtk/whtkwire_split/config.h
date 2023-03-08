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

#define MASTER_RIGHT
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_OLED_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_LAYER_STATE_ENABLE

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10
// #define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 1
#define SERIAL_USART_RX_PAL_MODE 1
#define SERIAL_USART_TIMEOUT 20

#define I2C_DRIVER        I2CD1
#define I2C1_SCL_PIN      B6
#define I2C1_SDA_PIN      B7
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define OLED_IC OLED_IC_SSD1306
#define OLED_DISPLAY_WIDTH 64
#define OLED_DISPLAY_HEIGHT 32
#define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)
#define OLED_BLOCK_TYPE uint8_t
#define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 4)
#define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
#define OLED_COM_PINS COM_PINS_ALT
#define OLED_COLUMN_OFFSET 32
#define OLED_FONT_H "glcdfont_improved.c"
// #define OLED_TIMEOUT 60000

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
// #define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 0
// #define AUTO_MOUSE_DELAY 200
// #define AUTO_MOUSE_DEBOUNCE 25

#define ENCODERS_PAD_A { B9 }
#define ENCODERS_PAD_B { B8 }
#define ENCODER_RESOLUTION 2

#define LED_PWR_PIN B15