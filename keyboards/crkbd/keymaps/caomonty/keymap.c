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
#include <stdio.h>

enum crkbd_layers {
  _QWERTY,
  _WINQW,
  _WISHI,
  _UTIL,
  _WUTIL,
  _DESKTOP,
  _DIGITS,
  _WMANAGE,
  _CONFIG,
  _SYMBOLS,
};

/*********************** [START] Macro and keycode declarations ************************/

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  MA_SBRA,
  MA_CBRA,
  MA_PAR,
  MA_ALF,
  CK_LSP, // custom keycode
  CK_RSP, // custom keycode
};


/*********************** [END] Marcro declarations ************************/


/*********************** [START] Aliases ************************/

// Aliases to shorten code
#define LT_1 LT(_DIGITS, KC_TAB) // layer digits when held, tab when tapped
#define ENT_LT LT(_DESKTOP, KC_ENT)// layer change when held, enter when tapped
#define UTIL MO(_UTIL) // change to utility layer while held
#define CONFI MO(_CONFIG) // change to configuration layer while held
#define SF_UN RSFT_T(KC_RO) // shift when held, underscore when tapped
#define WMANA LM(_WMANAGE, MOD_LCTL | MOD_LALT | MOD_LSFT)  // change to windows management layer
#define DESK MO(_DESKTOP)  // change to desktop control layer
#define SPOT A(G(KC_SPC))  // Open spotlight, It may need to change the hotkey inside configuration
#define SCREEN G(S(KC_4))  // Mac screenshot hotkey
#define TERMF C(S(KC_T))   // New terminal at folder, (it needs configuration inside shortcuts -> services)
#define CGUI C(KC_LGUI) // Control + Left Gui
#define MINE TG(_MINE)
#define JIS_LPA KC_ASTERISK // Left parenthesis
#define JIS_RPA KC_LEFT_PAREN // Right parenthesis
#define JIS_LCB KC_RCBR // Left curly brace
#define JIS_RCB KC_PIPE // Right curly brace
#define JIS_LSB KC_RBRC // left square bracket
#define JIS_RSB KC_BSLS // Right bracket

#define SYM_AT KC_LBRC // @ symbol using JIS config

#define MM_LE G(KC_LEFT) // move to the start of the current line (*1)
#define MM_RI G(KC_RGHT) // move to the end of the current line   (*2)
#define SP_LE A(KC_LEFT) // move the caret one word to the left   (*3)
#define SP_RI A(KC_RGHT) // move the caret one word to the right  (*4)
#define EQUAL S(KC_MINS) // equals JIS
#define BSLS A(KC_JYEN)  // backslash
#define PIPE S(KC_JYEN) // pipe
#define MM_N A(KC_N) // input ˜ character JIS keyboard
#define BACKTIK S(KC_LBRC) // input ` character (JIS)
#define ACCENT A(KC_E) // input spanish accent using JIS
#define JI_LBRC KC_RBRC // input [ using JIS
#define JI_QUOT S(KC_7) // input ' using JIS
#define JI_LCBR S(KC_RBRC) // input { using JIS
#define JI_LPRN S(KC_8) // input ( using JIS
#define ALFRED LGUI(LALT(KC_SPC)) // activate alfred in OSx
#define WBACK LALT(KC_BSPC)

// Windows-specific codes to emulate the JIS keyboard on a US layout setup
#define WUTIL MO(_WUTIL)
#define WISHIFT MO(_WISHI)
#define WI_SLSH KC_SLSH
#define WM_LE A(KC_LEFT) // moves caret to the start of the line
#define WM_RI A(KC_RGHT) // moves caret to the end of the line
#define WP_LE C(KC_LEFT) // moves caret to the start of the previous word
#define WP_RI C(KC_RIGHT) // moves caret tot the next word
#define WI_ON TG(_WINQW) // toggles the layer on or off

// Custom mod-tap
#define MO_7 LT(0, KC_7) // () on hold 7 on tap
#define MO_8 LT(0, KC_8) // [] on hold 8 on tap
#define MO_9 LT(0, KC_9) // {} on hold 9 on tap
#define MO_P LT(0, KC_P) // @ on hold p on tap
#define MO_X LT(0, KC_X) // Cut on hold X on tap
#define MO_C LT(0, KC_C) // Copy on hold C on tap
#define MO_V LT(0, KC_V) // Paste on hold V on tap
#define ROKA LT(0, KC_HANJ) // change to Romaji input on tap, change to kanji on hold
#define DOT_3 LT(0, KC_3) // dot on hold 3 on tap,
#define COMM_2 LT(0, KC_2) // comma on hold, 2 on tap
#define W_SHIFT LT(0, KC_SLSH) // exclusive use for windows underscore and shift
#define LT_RSPC LT(0, CK_RSP) // custom behaviour on hold, space on tap
#define LT_LSPC LT(0, CK_LSP) // custom behaviour on hold, alfred on tap

// Desktop control related aliases
#define DC_MENU LCTL(KC_F2) // Move focus to menu bar default keybinding in MacOS
#define DC_DOCK LCTL(KC_F3) // Move focus to dock
#define DC_TOOL LCTL(KC_F5) // Move focus to window toolbar
#define DC_STAT LCTL(KC_F8) // Move focus to status bar side of menu bar
#define DC_DRWR LALT(LGUI(KC_QUOTE)) // Move focus to window drawer
#define DC_LPAD LALT(LGUI(KC_Q)) // Show Launchpad
#define DC_NOTI LALT(LGUI(LCTL(KC_B))) // Show Notification Center
#define DC_DASH LALT(LGUI(LCTL(KC_C))) // Show Dashboard
#define DC_HELP LSFT(LGUI(KC_SLASH)) // Position in menu Help search box
#define DC_LEFT C(KC_LEFT) // move to left desktop
#define DC_RGHT C(KC_RGHT) // move to right desktop
#define DC_EXPO C(KC_DOWN) // show expose
#define DC_MISI C(KC_UP)   // show mission control

/*********************** [END] Aliases ************************/

/*********************** [START] Keyboard Layout ************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       LT_1  ,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   MO_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UTIL   ,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, ENT_LT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    MO_X,    MO_C,    MO_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  SF_UN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LGUI, LT_LSPC,    LT_RSPC, KC_LALT, CONFI
                                      //`--------------------------'  `--------------------------'

  ),

  [_WINQW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       LT_1  ,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   MO_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      WUTIL  ,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_COLN, KC_ENT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      WISHIFT,    KC_Z,    MO_X,    MO_C,    MO_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, WI_SLSH, W_SHIFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LGUI, LT_LSPC,    LT_RSPC, KC_LALT, CONFI
                                      //`--------------------------'  `--------------------------'

  ),

  [_WISHI] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
  [_UTIL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      KC_PGUP, MM_LE  , KC_UP  , BACKTIK, PIPE   , KC_EQL ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, DESK   , WMANA  , XXXXXXX, XXXXXXX,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, ACCENT , WBACK  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      MM_N   , SP_LE  , _______, SP_RI  , BSLS   , _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CGUI   , CGUI   , _______,    SPOT   , _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_WUTIL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_PLUS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                      KC_PGUP, WM_LE  , KC_UP  , WM_RI  , _______, KC_DEL ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, DESK   , WMANA  , KC_F11 , KC_F12 ,                      _______, MM_N   , SP_LE  , _______, SP_RI  , BSLS   ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_GESC, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SYM_AT , KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_DIGITS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, KC_P7  , KC_P8  , KC_P9  , _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, KC_P4  , KC_P5  , KC_P6  , _______, EQUAL  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      _______, KC_P1  , KC_P2  , KC_P3  , _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, KC_PDOT, KC_P0
                                      //`--------------------------'  `--------------------------'
  ),

  [_CONFIG] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),
};

/*********************** [END] Keyboard Layout ************************/

/*********************** [START] OLED display config ************************/

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}




void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

/*********************** [END] OLED display config ************************/

/*********************** [START] Custom behaviour ************************/

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (record->event.pressed) {
//     set_keylog(keycode, record);
//   }
//   return true;
// }
#endif // OLED_ENABLE

/*********************** [END] Custom behaviour ************************/


// [START] Custom key behaviour
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
//-----> [START] Custom mode tap definitions ******************************
        case MO_8:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _WINQW) {
                    tap_code16(KC_LPRN);
                    tap_code16(KC_RPRN);
                    tap_code16(KC_LEFT);
                }
                else {
                    tap_code16(KC_ASTERISK); // intercept hold functon to send ()
                    tap_code16(KC_LEFT_PAREN);
                    tap_code16(KC_LEFT);

                }
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_7:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _WINQW) {
                    tap_code16(KC_LBRC); // send [] on windows
                    tap_code16(KC_RBRC);
                    tap_code16(KC_LEFT);
                }
                else {
                    tap_code16(KC_RBRC); // intercept hold function to send [] (JIS)
                    tap_code16(KC_BSLS);
                    tap_code16(KC_LEFT);
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_9:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _WINQW) {
                    tap_code16(KC_LCBR);
                    tap_code16(KC_RCBR);
                    tap_code16(KC_LEFT);
                }
                else {
                    tap_code16(KC_RCBR); // intercept hold function to send {}
                    tap_code16(KC_PIPE);
                    tap_code16(KC_LEFT);
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_P:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _WINQW) {
                    tap_code16(S(KC_2)); // send @ on windows
                }
                else {
                    tap_code16(KC_LBRC); // intercept hold function to send @ (JIS
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_X:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _WINQW) {
                    tap_code16(C(KC_X)); // cut on windows
                }
                else {
                    tap_code16(G(KC_X)); // intercept hold function to send cmd-X
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_C:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _WINQW) {
                    tap_code16(C(KC_C)); // copy on windows
                }
                else {
                    tap_code16(G(KC_C)); // intercept hold function to send # cmd-C
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_V:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _WINQW) {
                    tap_code16(C(KC_V)); // paste on windows
                }
                else {
                    tap_code16(G(KC_V)); // intercept hold function to send cmd-V
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case ROKA:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_HAEN); // intercept hold function to send HAEN
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case COMM_2:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_COMM); // intercept hold function to send comma
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case DOT_3:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_DOT); // intercept hold function to send dot
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case W_SHIFT:
            if (record->tap.count && record->event.pressed){
                tap_code16(KC_UNDS); // intercept tap function to send _
            } else if (record->event.pressed){
                // intercept hold function to press
                layer_on(_WISHI);
            } else {
                layer_off(_WISHI); // intercept hold function button release
            }
            return false;  // Return false to avoid normal processing of mod-tap
        case LT_LSPC:
            if (record->tap.count && record->event.pressed){
                tap_code16(ALFRED); // intercept tap function
            } else if (record->event.pressed){
                // intercept hold function to press
                layer_on(_SYMBOLS);
            } else {
                layer_off(_SYMBOLS); // intercept hold function button release
            }
            return false;  // Return false to avoid normal processing of mod-tap
        case LT_RSPC:
            if (record->tap.count && record->event.pressed){
                tap_code16(KC_SPC); // intercept tap function
            } else if (record->event.pressed){
                // intercept hold function to press
                layer_on(_SYMBOLS);
            } else {
                layer_off(_SYMBOLS); // intercept hold function button release
            }
            return false;  // Return false to avoid normal processing of mod-tap


//-----> [END] Custom mode tap definitions  ******************************

//-----> [START] Custom keycode definition  ******************************
        // case FOO:
        //       if (record->event.pressed) {
        //         // Do something when pressed
        //       } else {
        //         // Do something else when release
        //       }
        //       return false; // Skip all further processing of this key
//-----> [END] Custom keycode definition  ******************************

//-----> [START] Override keycode function  ******************************
        // case KC_ENTER:
        //       // Play a tone when enter is pressed
        //       if (record->event.pressed) {
        //         PLAY_SONG(tone_qwerty);
        //       }
        //       return true; // Let QMK send the enter press/release events
//-----> [END] Custom mode tap definitions  ******************************


// [START] Macro definitions ************************************
        case MA_SBRA:  // send [] JIS
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                tap_code16(KC_RBRC);
                tap_code16(KC_BSLS);
                tap_code16(KC_LEFT);
            } else {
                // when keycode MA_SBRA is released
            }
            break;

        case MA_CBRA: // send {} JIS
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                tap_code16(KC_RCBR); // intercept hold function to send {}
                tap_code16(KC_PIPE);
                tap_code16(KC_LEFT);
            } else {
                // when keycode MA_CBRA is released
            }
            break;

        case MA_PAR: // send () JIS
            if (record->event.pressed) {
                tap_code16(KC_ASTERISK);
                tap_code16(KC_LEFT_PAREN);
                tap_code16(KC_LEFT);
            }
            break;
        case MA_ALF:
            if (record->event.pressed) {
              tap_code16(LGUI(LALT(KC_SPC)));
            }
            break;
// [START] Macro definitions ************************************
    }
    return true;
};
// [END] Custom key behaviour


// try to enable rolling motion on custom mod-tap key to a better performance while fast typing
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
        case W_SHIFT:
            return true; // immediately select the hold action when another key is pressed
        default:
            return false; // other keys behave as normal
    }
}
// [END] custom mod tap definition


// preonic code -------------------------------------------------------------------------------------------------------------



// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// /* Qwerty
// ┌─┬─┐ └─┴─┘ ├─┼─┤ │
//  * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
//  * │  Gesc  │   1    │   2    │    3   │    4   │   5    │   6    │    7   │    8   │   9    │    0   │   -    │
//  * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//  * │  Tab   │   Q    │    W   │    E   │    R   │   T    │   Y    │   U    │    I   │   O    │   P    │ Backsp │
//  * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//  * │ LayerU │   A    │    S   │    D   │    F   │   G    │   H    │   J    │    K   │   L    │   :    │   Ent  │
//  * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
//  * │ Shift  │   Z    │    X   │    C   │    V   │   B    │   N    │   M    │    ,   │   .    │   /    │ shift _│
//  * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┼────────┼────────┼────────┤
//  * │ Ctl    │  Alt   │ Ro/Ka  │ GUI    │                 │      Space      │ GUI    │ '      │   @    │ LayerC │
//  * └────────┴────────┴────────┴────────┴─────────────────┴─────────────────┴────────┴────────┴────────┴────────┘
//  */
// [_QWERTY] = LAYOUT_preonic_grid(
//   KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    MO_7,      MO_8,     MO_9,      KC_0,    KC_MINS,
//   LT_1,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,      KC_I,     KC_O,      MO_P,    KC_BSPC,
//   UTIL,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,      KC_K,     KC_L,      KC_QUOT, ENT_LT ,
//   KC_LSFT,  KC_Z,    MO_X,    MO_C,    MO_V,    KC_B,    KC_N,    KC_M,      KC_COMM,  KC_DOT,    KC_SLSH, SF_UN  ,
//   KC_LCTL,  KC_LALT, ROKA,    KC_LGUI, LT_LSPC, LT_LSPC, LT_RSPC, LT_RSPC,   KC_RGUI,  KC_AMPR,   ROKA   , CONFI
// ),
// [_WINQW] = LAYOUT_preonic_grid(
//     KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    MO_7,      MO_8,     MO_9,      KC_0,    KC_MINS,
//     LT_1,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,      KC_I,     KC_O,      MO_P,    KC_BSPC,
//     WUTIL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,      KC_K,     KC_L,      KC_COLN, KC_ENT,
//     WISHIFT,  KC_Z,    MO_X,    MO_C,    MO_V,    KC_B,    KC_N,    KC_M,      KC_COMM,  KC_DOT,    WI_SLSH, W_SHIFT,
//     KC_LCTL,  KC_LCTL, ROKA,    KC_LGUI, ALFRED , ALFRED,  KC_SPC,  KC_SPC,    KC_RGUI,  KC_AMPR,   ROKA   , CONFI
// ),
// [_WISHI] = LAYOUT_preonic_grid(
//  _______, KC_EXLM, KC_DQUO, KC_HASH, KC_DLR , KC_PERC, KC_AMPR, KC_QUOT, KC_LPRN, KC_RPRN, KC_PIPE, KC_EQL ,
//  _______, S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), _______,
//  _______, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), _______, S(KC_ENT),
//  _______, S(KC_Z), S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), KC_LT  , KC_GT  , KC_QUES, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// ),
// [_UTIL] = LAYOUT_preonic_grid(
//   KC_PLUS, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_AMPR, BACKTIK, PIPE,    KC_EQL,
//   _______, KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_PGUP, MM_LE,   KC_UP,   MM_RI,   ACCENT , WBACK ,
//   _______, _______, DESK,     WMANA,   KC_F11,  KC_F12,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, _______,
//   KC_CAPS, _______, _______,  _______, _______, _______, MM_N   , SP_LE,   _______, SP_RI,   BSLS,    _______,
//   _______, _______, _______,  _______, CGUI,    CGUI,    SPOT,    SPOT,    _______, _______, _______, _______
// ),
// [_WUTIL] = LAYOUT_preonic_grid(
//   KC_PLUS, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_AMPR, BACKTIK, PIPE,    KC_EQL,
//   _______, KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_PGUP, WM_LE,   KC_UP,   WM_RI,   _______, KC_DEL,
//   _______, _______, _______,  _______, KC_F11,  KC_F12,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, _______,
//   KC_CAPS, _______, _______,  _______, _______, _______, MM_N   , WP_LE,   _______, WP_RI,   KC_BSLS, _______,
//   _______, _______, _______,  _______, _______, _______, _______, _______,    _______, _______, _______, _______
// ),
// [_DESKTOP] = LAYOUT_preonic_grid(
//   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//   _______, _______, MA_PAR , MA_SBRA, MA_CBRA, _______, DC_MENU, DC_NOTI, DC_MISI, DC_DASH, _______, _______,
//   _______, _______, JIS_LPA, JIS_LSB, JIS_LCB, _______, DC_DOCK, DC_LEFT, DC_EXPO, DC_RGHT, _______, _______,
//   _______, _______, JIS_RPA, JIS_RSB, JIS_RCB, _______, DC_TOOL, DC_STAT, DC_DRWR, DC_LPAD, _______, _______,
//   _______, _______, _______, _______, _______, _______, DC_HELP, DC_HELP, _______, _______, _______, _______
// ),
// [_SYMBOLS] = LAYOUT_preonic_grid(
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  KC_GESC, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SYM_AT , KC_MINS,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
// ),
// [_DIGITS] = LAYOUT_preonic_grid(
//   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//   _______, _______, _______, KC_PMNS, KC_PPLS, _______, KC_JYEN, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
//   _______, _______, _______, KC_PSLS, KC_PAST, _______, KC_DLR , KC_P4,   KC_P5,   KC_P6,   KC_PAST, EQUAL  ,
//   _______, _______, _______, _______, _______, _______, KC_EQL,  KC_P1,   COMM_2,  DOT_3,   KC_PMNS, _______,
//   _______, _______, _______, _______, KC_SPC , KC_SPC , _______, KC_P0,   KC_PDOT, KC_COMM, KC_PPLS, _______
// ),
// [_WMANAGE] = LAYOUT_preonic_grid(
//   KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,      KC_8,     KC_9,      KC_0,    KC_MINS,
//   KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,      KC_I,     KC_O,      KC_P,    KC_BSPC,
//   _______,  KC_A,    _______, KC_D,    KC_F,    KC_G,    KC_H,    KC_J,      KC_K,     KC_L,      KC_SCLN, KC_ENT,
//   KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,      KC_COMM,  KC_DOT,    KC_SLSH, KC_RO,
//   KC_LCTL,  KC_LALT, _______, _______, KC_LGUI, KC_SPC,  KC_SPC,  KC_RGUI,   KC_M   ,  KC_COMM,   KC_DOT , _______
// ),
// [_CONFIG] = LAYOUT_preonic_grid(
//   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SCREEN,
//   _______, _______, CK_UP  , _______, _______, _______, _______, _______, KC_INS,  _______, _______, _______,
//   _______, CK_ON  , CK_DOWN, CK_OFF , _______, _______, _______, _______, _______, _______, _______, TERMF,
//   _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______,
//   _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______
// )

// };


// //-----> [START] Behaviour on layer change ******************************
// layer_state_t layer_state_set_user(layer_state_t state){
//   switch (get_highest_layer(state)) {
//     case _UTIL:
//       PLAY_SONG(util_on);
//       break;
//     case _DESKTOP:
//       PLAY_SONG(desktop_on);
//       break;
//     case _DIGITS:
//       PLAY_SONG(numeric_on);
//       break;
//     case _WMANAGE:
//       PLAY_SONG(windows_on);
//       break;
//     case _CONFIG:
//       PLAY_SONG(config_on);
//       break;
//   }
//   return state;
// }

// //-----> [END] Behaviour on layer change ******************************

// // [END] Layer indication with sound




