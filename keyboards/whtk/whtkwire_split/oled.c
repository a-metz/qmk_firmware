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
#include "bitmaps.h"

typedef enum _screen_t {
    SCREEN_BOOTLOADER,
    SCREEN_STARTUP,
    SCREEN_MODE,
    SCREEN_MODIFIERS,
    SCREEN_LAYER,
    SCREEN_IDLE,
} screen_t;

typedef struct _display_t {
    screen_t screen;
    uint32_t timestamp;
    uint32_t duration;
} display_t;

display_t display = {
    .screen = SCREEN_IDLE,
    .timestamp = 0,
    .duration = 0,
};

bool show_dynamic_timed(screen_t screen, uint32_t duration) {
    if (display.screen < screen && timer_elapsed32(display.timestamp) < display.duration) {
        // return if a higher priority screen has not yet timed out
        return false;
    }

    display.screen = screen;
    display.timestamp = timer_read32();
    display.duration = duration;
    return true;
}

bool show_static(screen_t screen) {
    if (display.screen == screen) {
        // return if the screen is already shown
        return false;
    }

    if (display.screen < screen && timer_elapsed32(display.timestamp) < display.duration) {
        // return if a higher priority screen has not yet timed out
        return false;
    }

    display.screen = screen;
    display.timestamp = timer_read32();
    display.duration = 0;
    return true;
}

void render_startup(void) {
    oled_clear();
    oled_write_ln("WHTKWIRE", false);
    oled_write_ln("SPLIT REV2", false);
}

void render_bootloader(void) {
    oled_clear();
    oled_write_ln("BOOTLOADER", false);
}

void render_mode(mode_t mode) {
    oled_clear();

    if (!is_keyboard_master()) {
        // only master holds mode state
        return;
    }

    switch (mode.os) {
        case OS_LINUX:
            oled_write_raw_rect(bitmap_linux, 16, 0, SIZE_LINUX, 4);
            break;
        case OS_MAC:
            oled_write_raw_rect(bitmap_mac, 16, 0, SIZE_MAC, 4);
            break;
        default:
            oled_write_ln("UNKNOWN", false);
            break;
    }
}

void render_modifiers(uint8_t modifiers) {
    static const uint8_t SIZE_GAP = 5;

    oled_clear();

    bool ctrl = modifiers & MOD_MASK_CTRL;
    bool alt = modifiers & MOD_MASK_ALT;
    bool shift = modifiers & MOD_MASK_SHIFT;
    bool super = modifiers & MOD_MASK_GUI;

    // calculate string length and necessary padding to center text
    uint8_t num_gaps = ctrl + alt + shift + super;
    if (num_gaps > 0) {
        // don't count trailing space
        num_gaps -= 1;
    }
    
    uint8_t length = (num_gaps * SIZE_GAP) + (ctrl * SIZE_CTRL) + (alt * SIZE_ALT) + (shift * SIZE_SHIFT) + (super * SIZE_SUPER);
    uint8_t x_offset = (OLED_DISPLAY_WIDTH - length + 1) / 2;

    if (ctrl) {
        oled_write_raw_rect(bitmap_ctrl, x_offset, 1, SIZE_CTRL, 2);
        x_offset += SIZE_CTRL + SIZE_GAP;
    }
    if (alt) {
        oled_write_raw_rect(bitmap_alt, x_offset, 1, SIZE_ALT, 2);
        x_offset += SIZE_ALT + SIZE_GAP;
    }
    if (shift) {
        oled_write_raw_rect(bitmap_shift, x_offset, 1, SIZE_SHIFT, 2);
        x_offset += SIZE_SHIFT + SIZE_GAP;
    }
    if (super) {
        oled_write_raw_rect(bitmap_super, x_offset, 1, SIZE_SUPER, 2);
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
    static uint8_t last_modifiers = 0;
    static bool modifiers_changed = false;

    mode_t current_mode = get_mode();
    if (last_mode.raw != current_mode.raw) {
        mode_changed = true;
        last_mode.raw = current_mode.raw;
    }

    uint8_t current_modifiers = get_mods();
    if (last_modifiers != current_modifiers) {
        modifiers_changed = true;
        last_modifiers = current_modifiers;
    }

    uint8_t current_layer = get_highest_layer(layer_state);
    if (last_layer != current_layer) {
        layer_changed = true;
        last_layer = current_layer;
    }
    
    if (startup && show_dynamic_timed(SCREEN_STARTUP, 2000)) {
        render_startup();
        startup = false;
        return true;
    }

    if (mode_changed && show_dynamic_timed(SCREEN_MODE, 2000)) {
        render_mode(current_mode);
        mode_changed = false;
        return true;
    }

    if (modifiers_changed && show_dynamic_timed(SCREEN_MODIFIERS, current_modifiers ? 2000 : 0)) {
        render_modifiers(current_modifiers);
        modifiers_changed = false;
        return true;
    }

    if (layer_changed && show_dynamic_timed(SCREEN_LAYER, current_layer == 0 ? 2000 : 30000)) {
        render_layer(current_layer);
        layer_changed = false;
        return true;
    }

    if (show_static(SCREEN_IDLE)) {
        oled_clear();
        return true;
    }

    return false;
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (is_keyboard_left()) {
        return OLED_ROTATION_180;
    }
    return rotation;
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
