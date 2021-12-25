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
             L01, L02, L03, L04,      R05, R06, R07, R08, \
        L10, L11, L12, L13, L14,      R15, R16, R17, R18, R19, \
        L20, L21, L22, L23, L24,      R25, R26, R27, R28, R29, \
        L30, L31, L32, L33, L34,      R35, R36, R37, R38, R39, \
                  L42, L43, L44,      R45, R46, R47 \
    ) { \
        { ___, L01, L02, L03, L04,      R05, R06, R07, R08, ___ }, \
        { L10, L11, L12, L13, L14,      R15, R16, R17, R18, R19 }, \
        { L20, L21, L22, L23, L24,      R25, R26, R27, R28, R29 }, \
        { L30, L31, L32, L33, L34,      R35, R36, R37, R38, R39 }, \
        { ___, ___, L42, L43, L44,      R45, R46, R47, ___, ___ } \
    }
