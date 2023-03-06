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
#include "whtkwire_split.h"

#include "state.h"
#include "oled.h"

void matrix_init_kb(void) {
    // Set to high pullup for low power glow
    setPinInputHigh(LED_PWR_PIN);

    // Set to high outout for bright glow
    // setPinOutput(LED_PWR_PIN);
    // writePinHigh(LED_PWR_PIN);
    init_state();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }

    if (clockwise) {
        tap_code(KC_WH_D);
        register_scroll(1);
    } else {
        tap_code(KC_WH_U);
        register_scroll(-1);
    }

    return false;
}