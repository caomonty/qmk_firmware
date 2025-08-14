// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    CC_A = SAFE_RANGE,
    CC_B,
    CC_C,
    CC_D,
    CC_E,
    CC_F,
    CC_G,
    CC_H,
    CC_I,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CC_A:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("I ");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CC_B:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("love ");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CC_C:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("my dearu ");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CC_D:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("so so so ");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CC_E:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("very ");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CC_F:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("much! ");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CC_G:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("ninety thousend quantisillion ");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CC_H:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("very very very very much ");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    case CC_I:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("to the end of the universe and beyond!");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        CC_A, CC_B,    CC_C,
        CC_D, CC_E,    CC_F,
        CC_G, CC_H,    CC_I
    )
};

