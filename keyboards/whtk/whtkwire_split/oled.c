/* Copymaster 2023 Alexander Metz
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

typedef enum _screen_t {
    SCREEN_BOOTLOADER,
    SCREEN_STARTUP,
    SCREEN_MODE,
    SCREEN_LAYER,
    SCREEN_CLEAR,
} screen_t;

typedef struct _display_t {
    screen_t screen;
    uint32_t timestamp;
    uint32_t duration;
} display_t;

display_t display = {
    .screen = SCREEN_CLEAR,
    .timestamp = 0,
    .duration = 0,
};

bool can_show(screen_t screen, uint32_t duration) {
    if (display.screen < screen && timer_elapsed32(display.timestamp) < display.duration) {
        // return if a higher priority screen has not yet timed out
        return false;
    }

    display.screen = screen;
    display.timestamp = timer_read32();
    display.duration = duration;
    return true;
}

void render_startup(void) {
    oled_clear();
    oled_write_ln("WHTKWIRE", false);
    oled_write_ln("SPLIT REV2", false);
}

void render_bootloader(void) {
    oled_clear();
    oled_write_ln("", false);
    oled_write_ln("BOOTLOADER", false);
}

void render_mode(mode_t mode) {
    oled_clear();

    switch (mode.os) {
        case OS_LINUX:
            oled_write_ln("LINUX", false);
            break;
        case OS_MAC:
            oled_write_ln("MAC", false);
            break;
        default:
            oled_write_ln("UNKNOWN", false);
            break;
    }
}

__attribute__((weak)) void render_layer(uint8_t layer) {}

void show_oled_bootloader(void) {
    // override all other screens
    render_bootloader();

    // force synchronous update of oled before rebooting MCU.
    oled_render();
}

bool oled_task_kb(void) {
    static bool startup = true;
    static uint8_t last_layer = 0;
    static bool layer_changed = true;
    static mode_t last_mode = { .raw = MODE_INIT };
    static bool mode_changed = true;

    mode_t current_mode = get_mode();
    if (last_mode.raw != current_mode.raw) {
        mode_changed = true;
        last_mode.raw = current_mode.raw;
    }

    uint8_t current_layer = get_highest_layer(layer_state);
    if (last_layer != current_layer) {
        layer_changed = true;
        last_layer = current_layer;
    }
    
    if (startup && can_show(SCREEN_STARTUP, 2000)) {
        render_startup();
        startup = false;
        return true;
    }

    if (mode_changed && can_show(SCREEN_MODE, 2000)) {
        render_mode(current_mode);
        mode_changed = false;
        return true;
    }

    if (layer_changed && can_show(SCREEN_LAYER, current_layer == 0 ? 2000 : 30000)) {
        render_layer(current_layer);
        layer_changed = false;
        return true;
    }

    if (can_show(SCREEN_CLEAR, 0)) {
        oled_clear();
        return true;
    }

    return false;
}


    // 'small_test', 64x32px
    // static const char epd_bitmap_small_test [] PROGMEM = {
	// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 
	// 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x00, 0x00, 0x38, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	// 0xff, 0xff, 0xff, 0xfe, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x1c, 0x23, 0xe0, 0xe0, 0x20, 0x10, 0x10, 0x09, 0x07, 0x03, 0x07, 0x06, 0x06, 0x0c, 
	// 0x0c, 0x18, 0x18, 0xf0, 0x30, 0x10, 0x10, 0xf0, 0xb0, 0xb0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x00, 0x00, 0x38, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
	// 0x7f, 0xff, 0xff, 0xff, 0x7f, 0x07, 0x0f, 0x1e, 0x1e, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x38, 0xc4, 0x07, 0x07, 0x04, 0x08, 0x08, 0x90, 0xe0, 0xc0, 0xe0, 0x60, 0x70, 0x30, 
	// 0x38, 0x1c, 0x1e, 0x0f, 0x0c, 0x0c, 0x0e, 0x0f, 0x0d, 0x0d, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	// 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    // };
    // oled_write_raw_P(epd_bitmap_small_test, sizeof(epd_bitmap_small_test));
