#pragma once

#include "quantum.h"

#define ANIM_WIDTH 62
#define ANIM_HEIGHT 5
extern const char PROGMEM anim_frames[][ANIM_WIDTH * ANIM_HEIGHT];

#define LAYER_BITMAP_WIDTH 36
#define LAYER_BITMAP_HEIGHT 6
extern const char bitmap_alpha [] PROGMEM;
extern const char bitmap_func [] PROGMEM;
extern const char bitmap_nav [] PROGMEM;
extern const char bitmap_symbol [] PROGMEM;
extern const char bitmap_num [] PROGMEM;

#define MODE_BITMAP_WIDTH 21
#define MODE_BITMAP_HEIGHT 4
extern const char bitmap_mac [] PROGMEM;
extern const char bitmap_linux [] PROGMEM;

#define LEGEND_BITMAP_WIDTH 128
#define LEGEND_BITMAP_HEIGHT 6 // cut off bottom row
extern const char bitmap_alpha_legend [] PROGMEM;
extern const char bitmap_alpha_shift_legend [] PROGMEM;
extern const char bitmap_func_num_legend [] PROGMEM;
extern const char bitmap_sym_nav_legend [] PROGMEM;