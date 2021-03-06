/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "split_util.h"
extern keymap_config_t keymap_config;

extern uint8_t is_master;
#ifdef OLED_DRIVER_ENABLE
    #include "bongo_animation.h"
#endif


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
/*#define _QWERTY 0*/
/*#define _LOWER 1*/
/*#define _RAISE 2*/
/*#define _ADJUST 3*/

enum crkbd_layers {
    _COLEM= 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

/*enum custom_keycodes {*/
  /*QWERTY = SAFE_RANGE,*/
  /*LOWER,*/
  /*RAISE,*/
  /*ADJUST,*/
  /*BACKLIT,*/
  /*RGBRST*/
/*};*/

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEM] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL,KC_SPC,MO(_LOWER),   MO(_RAISE), KC_ENT, KC_RALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_LGUI,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV , XXXXXXX,                      KC_MINS, KC_EQL , KC_LBRC, KC_RBRC, KC_BSLS, KC_RCTL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL,KC_LALT, MO(_LOWER), MO(_RAISE),KC_ENT,KC_RALT \
                                      //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_F11,  KC_F12, XXXXXXX, KC_PSCR, KC_PAUS,                      KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_HOME,  KC_END,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MENU, KC_PGDN, KC_PGUP, XXXXXXX, XXXXXXX, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LCTL, KC_SPC, MO(_LOWER), MO(_RAISE),KC_LCTRL,KC_RALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_MUTE, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                      XXXXXXX, KC_VOLU, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         KC_LGUI,  KC_SPC,MO(_LOWER),  MO(_RAISE),KC_ENT, KC_RALT \
                                      //`--------------------------'  `--------------------------'
  )
};


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
    void set_layer_indicators(uint8_t r, uint8_t g, uint8_t b) {
        rgb_matrix_set_color(6, r, g, b);
        /*rgb_matrix_set_color(2, r, g, b);*/
    }

    /*if (host_keyboard_led_state().caps_lock)*/
    /*{*/
        /*rgb_matrix_set_color(28, 0xFF, 0xFF, 0xFF);*/
    /*}*/

    switch (biton32(layer_state)) {
        case _LOWER:
            set_layer_indicators(0,0,64);
            break;
        case _RAISE:
            set_layer_indicators(64,0,0);
            break;
        case _ADJUST:
            set_layer_indicators(0,64,0);
            break;
        default:
            break;
    }
}
#endif

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_0;
    } else {
        return OLED_ROTATION_270;
    }
}

static const char *layer_str_P(void) {
    switch (biton32(layer_state)) {
        case _COLEM:
            return PSTR("COL");
            break;
        case _LOWER:
            return PSTR("LWR");
            break;
        case _RAISE:
            return PSTR("RSE");
            break;
        case _ADJUST:
            return PSTR("ADJ");
            break;
        default:
            return PSTR("NDF");
    }
}

static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("L:"), false);
    oled_write_P(layer_str_P(), false);
    oled_write_P(PSTR("  "), false);
    //Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCRL") : PSTR("    "), false);
}

static void render_small_status(void) {
    led_t led_state = host_keyboard_led_state();
    if (!(led_state.num_lock || led_state.caps_lock || led_state.scroll_lock)) {
        oled_advance_page(true);
    }

    oled_write_P(PSTR("L:"), false);
    oled_write_P(layer_str_P(), false);

    oled_advance_page(true);
    oled_write_char(' ', false);
    oled_write_char(led_state.num_lock ? 'N' : ' ', false);
    oled_write_char(led_state.caps_lock ? 'C' : ' ', false);
    oled_write_char(led_state.scroll_lock ? 'S' : ' ', false);
}

static void render_small_qmk_corne_logo(void) {
    static const char logo[96] PROGMEM = {
        0x50, 0xf8, 0xfc, 0xfe, 0x1c, 0xfe, 0xfc, 0x1e, 0xfc, 0xfe, 0x1c, 0xfe, 0xfc, 0xf8, 0x50, 0x00,
        0x00, 0xc0, 0xe0, 0x00, 0xe0, 0xf8, 0xfc, 0x1c, 0xe0, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x1e, 0x00,
        0x15, 0x3f, 0x7f, 0xff, 0x7c, 0xf9, 0x7b, 0xe0, 0x7b, 0xf9, 0x7c, 0xff, 0x7f, 0x3f, 0x15, 0x00,
        0xc0, 0x47, 0x0f, 0xce, 0x4f, 0xc7, 0x1f, 0xdf, 0x5f, 0x0f, 0xdf, 0x5f, 0xdc, 0x18, 0xd8, 0xce,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x01
    };
    oled_write_raw_P(logo, 96);
}

static void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);
}

char wpm_str[9];

void oled_task_user(void) {
    if (is_master) {
        render_crkbd_logo();
        oled_render();
        oled_set_cursor(1,3);
        // Renders the current keyboard state (layer, lock, caps, scroll, etc)
        render_status();
        oled_render();
    } else {
        render_anim();
        render_small_qmk_corne_logo();
        oled_set_cursor(0, 3);
        render_small_status();
        oled_render();
        oled_set_cursor(0, 13);
        sprintf(wpm_str, " WPM:  %03d", get_current_wpm());
        oled_write(wpm_str, false);
        oled_render();
    }
}

#endif
