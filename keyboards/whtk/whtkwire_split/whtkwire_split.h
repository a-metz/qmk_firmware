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

#include "quantum.h"

#define ___ KC_NO

#define LAYOUT( \
             L01, L02, L03, L04,      R04, R03, R02, R01, \
        L10, L11, L12, L13, L14,      R14, R13, R12, R11, R10, \
        L20, L21, L22, L23, L24,      R24, R23, R22, R21, R20, \
        L30, L31, L32, L33, L34,      R34, R33, R32, R31, R30, \
                  L42, L43, L44,      R44, R43, R42 \
    ) { \
        { ___, L01, L02, L03, L04} , \
        { L10, L11, L12, L13, L14} , \
        { L20, L21, L22, L23, L24} , \
        { L30, L31, L32, L33, L34} , \
        { ___, ___, L42, L43, L44} , \
        { R44, R43, R42, ___, ___} , \
        { R34, R33, R32, R31, R30} , \
        { R24, R23, R22, R21, R20} , \
        { R14, R13, R12, R11, R10} , \
        { R04, R03, R02, R01, ___} \
    }

