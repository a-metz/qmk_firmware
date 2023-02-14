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

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10
// Swap TX and RX pins if keyboard is master halve. Disable this for boards with hardwired crossover.
//#define SERIAL_USART_PIN_SWAP
#define SELECT_SOFT_SERIAL_SPEED 1
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 1
#define SERIAL_USART_RX_PAL_MODE 1
#define SERIAL_USART_TIMEOUT 20

#define I2C_DRIVER        I2CD2
#define I2C2_SCL_PIN      B6
#define I2C2_SDA_PIN      B7
#define I2C2_SCL_PAL_MODE 1
#define I2C2_SDA_PAL_MODE 1

#define OLED_DISPLAY_128X64
#define OLED_IC OLED_IC_SSD1306
#define OLED_FONT_H "glcdfont_improved.c"
