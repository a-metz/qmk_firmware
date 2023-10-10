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
#include "oled.h"
#include "state.h"

#include "quantum.h"

#define NUM_COLUMNS OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH

void write_spaces(uint8_t num) {
    for (uint8_t i = 0; i < num; i++) {
        oled_write_P(PSTR(" "), false);
    }
}

void render_mods(void)
{
    uint8_t mods = get_mods();
    bool ctrl = mods & MOD_MASK_CTRL;
    bool alt = mods & MOD_MASK_ALT;
    bool shift = mods & MOD_MASK_SHIFT;
    bool super = mods & MOD_MASK_GUI;

    // calculate string length and necessary padding to center text
    uint8_t spaces = ctrl + alt + shift + super;
    if (spaces > 0) {
        // don't count trailing space
        spaces -= 1;
    }
    uint8_t length = spaces + (ctrl * 4) + (alt * 3) + (shift * 5) + (super * 5);
    uint8_t left_padding = (NUM_COLUMNS - length + 1) / 2;
    uint8_t right_padding = NUM_COLUMNS - left_padding - length;

    write_spaces(left_padding);
    if (ctrl) oled_write_P(PSTR("CTRL "), false);
    if (alt) oled_write_P(PSTR("ALT "), false);
    if (shift) oled_write_P(PSTR("SHIFT "), false);
    if (super) oled_write_P(PSTR("SUPER"), false);
    write_spaces(right_padding);
}

void pad_center(uint8_t length) {
    write_spaces((NUM_COLUMNS - length + 1) / 2);
}

void render_os(void) {
    switch (get_mode().os) {
        case OS_LINUX:
            pad_center(5);
            oled_write_P(PSTR("Linux\n"), false);
            break;
        case OS_MAC:
            pad_center(3);
            oled_write_P(PSTR("Mac\n"), false);
            break;
        default:
            oled_write_P(PSTR("\n"), false);
            break;
    }
}

void render_bootloader(void) {
    oled_write_P(PSTR("Bootloader\n\n\n\n"), false);
}