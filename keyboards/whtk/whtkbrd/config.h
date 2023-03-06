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

#define SPLIT_USB_DETECT
#define MASTER_RIGHT

#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN A9   // USART TX pin
#define SERIAL_USART_RX_PIN A10  // USART RX pin
#define SERIAL_USART_PIN_SWAP    // Swap TX and RX pins if keyboard is master halve.
#define SELECT_SOFT_SERIAL_SPEED \
    1                              // or 0, 2, 3, 4, 5
                                   //  0: 460800 baud
                                   //  1: 230400 baud (default)
                                   //  2: 115200 baud
                                   //  3: 57600 baud
                                   //  4: 38400 baud
                                   //  5: 19200 baud
#define SERIAL_USART_DRIVER SD1    // USART driver of TX and RX pin
#define SERIAL_USART_TX_PAL_MODE 1 // Pin "alternate function"
#define SERIAL_USART_RX_PAL_MODE 1 // Pin "alternate function"
#define SERIAL_USART_TIMEOUT 20    // USART driver timeout. default 20

// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 20

#define MATRIX_COL_PINS \
    { A0, A1, A2, A3, A4, A5 }

#define MATRIX_ROW_PINS \
    { B0, B1, B2, B10, B11 }

#define I2C_DRIVER I2CD2
#define I2C2_SCL_PIN B6
#define I2C2_SDA_PIN B7
#define I2C2_SCL_PAL_MODE 1
#define I2C2_SDA_PAL_MODE 1

#define LED_PWR_PIN B8
#define LED_STAT_PIN B9
