#pragma once

oled_rotation_t oled_init_user(oled_rotation_t rotation);

void render_test(void);

void render_qmk_logo(void);

void render_anim(void);

void register_keypress(bool keydown);
