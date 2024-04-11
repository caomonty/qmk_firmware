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
  _COLEMAK, // DH variant
  _DVORAK,
  _UTIL,
  _DESKTOP,
  _DIGITS,
  _CONFIG,
  _SYMBOLS,
};

/*********************** [START] Macro and keycode declarations ************************/

enum crkbd_keycodes {
  QWERTY = SAFE_RANGE,
  MA_SBRA,
  MA_CBRA,
  MA_PAR,
  MA_ALF,
  CK_LSP, // custom keycode
  CK_RSP, // custom keycode
};


/*********************** [END] Macro declarations ************************/
/*********************** [START] Aliases ************************/

// Aliases Fix japanese key codes
#define KC_RO KC_INTERNATIONAL_1
#define KC_JYEN KC_INTERNATIONAL_3
#define KC_KANA KC_LANGUAGE_1
#define KC_EISU KC_LANGUAGE_2

// Custom layer tap and hold
#define LT_TAB LT(_DIGITS, KC_TAB) // layer digits when held, tab when tapped
#define ENT_LT LT(_DESKTOP, KC_ENT)// layer change when held, enter when tapped
#define UTIL MO(_UTIL)

// Aliases to shorten code
 // change to utility layer while held
#define CONFI MO(_CONFIG) // change to configuration layer while held
#define SF_UN RSFT_T(KC_RO) // shift when held, underscore when tapped
#define DESK MO(_DESKTOP)  // change to desktop control layer
#define SPOT A(G(KC_SPC))  // Open spotlight, It may need to change the hotkey inside configuration
#define SCREEN G(S(KC_4))  // Mac screenshot hotkey
#define TERMF C(S(KC_T))   // New terminal at folder, (it needs configuration inside shortcuts -> services)
#define CGUI C(KC_LGUI) // Control + Left Gui
#define MINE TG(_MINE)
#define GUI_ENT G(KC_ENT) // Gui + Enter


// Symbol Aliases

#define SYM_AT KC_LBRC // "@" symbol using JIS config
#define JIS_LPA KC_ASTERISK // "(" Left parenthesis
#define JIS_RPA KC_LEFT_PAREN // ")" Right parenthesis
#define JIS_LCB KC_RCBR // "{" Left curly brace
#define JIS_RCB KC_PIPE // "}" Right curly brace
#define JIS_LSB KC_RBRC // "[" left square bracket
#define JIS_RSB KC_BSLS // "]" Right bracket
#define BSLS A(KC_JYEN)  // "\" backslash
#define PIPE S(KC_JYEN) // "|" pipe
#define POT KC_EQL // "^"
#define CURD KC_TILD // "~"
#define BACKTIK KC_GRV // "`" character (JIS) // KC_LCBR
#define EQUAL KC_UNDS // "=" equals JIS
#define PLUS KC_COLN // "+" equals JIS
#define ASTER KC_DQUO // "*" equals JIS
#define DIV KC_SLSH // "/" equals JIS
#define MINUS KC_MINS // "-" equals JIS

#define MM_LE G(KC_LEFT) // move to the start of the current line (*1)
#define MM_RI G(KC_RGHT) // move to the end of the current line   (*2)
#define SP_LE A(KC_LEFT) // move the caret one word to the left   (*3)
#define SP_RI A(KC_RGHT) // move the caret one word to the right  (*4)
#define MM_N A(KC_N) // input ˜ character JIS keyboard
#define ACCENT A(KC_E) // input spanish accent using JIS
#define JI_QUOT S(KC_7) // input ' using JIS
#define JI_LCBR S(KC_RBRC) // input { using JIS
#define JI_LPRN KC_ASTR // input ( using JIS
#define ALFRED LGUI(LALT(KC_SPC)) // activate alfred in OSx
#define WBACK LALT(KC_BSPC)
#define MACLOCK G(C(KC_Q))

// Windows-specific codes to emulate the JIS keyboard on a US layout setup
#define WISHIFT MO(_WISHI)
#define WI_SLSH KC_SLSH
#define WM_LE A(KC_LEFT) // moves caret to the start of the line
#define WM_RI A(KC_RGHT) // moves caret to the end of the line
#define WP_LE C(KC_LEFT) // moves caret to the start of the previous word
#define WP_RI C(KC_RIGHT) // moves caret tot the next word
#define COL_ON TO(_COLEMAK) // deactivates all layers but Base and Colemak
#define DVO_ON TO(_DVORAK) // deactivates all layers but Base and Dvorak
#define QWE_ON TO(_QWERTY) // activates only base layer

// Custom mod-tap
#define MO_QUOT LT(0, KC_QUOT) // @ on hold : on tap
#define MO_X LT(0, KC_X) // Cut on hold X on tap
#define MO_C LT(0, KC_C) // Copy on hold C on tap
#define MO_V LT(0, KC_V) // Paste on hold V on tap
#define ROKA LT(0, KC_EISU) // change to Romaji input on tap, change to kanji on hold
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

#define EXTRA_DELAY 200

/*********************** [END] Aliases ************************/
/*********************** [START] Keyboard Template ************************/

/*

  [_QWERTY] = LAYOUT_split_3x6_3(
  //.-----------------------------------------------------.                    .-----------------------------------------------------.
     LT_TAB  ,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,  KC_P , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UTIL   ,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, MO_QUOT, ENT_LT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    MO_X,    MO_C,    MO_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  SF_UN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, LT_LSPC, KC_LGUI,    CONFI  , LT_RSPC, KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

*/

/*********************** [End] Keyboard Template ************************/
/*********************** [START] Keyboard Layout ************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     LT_TAB  ,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,  KC_P , KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UTIL   ,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, MO_QUOT, ENT_LT ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    MO_X,    MO_C,    MO_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  SF_UN ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, LT_LSPC, KC_LGUI,    CONFI  , LT_RSPC, KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

  [_COLEMAK] = LAYOUT_split_3x6_3( // DH variant
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, MO_QUOT,  _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I, KC_O    , _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_Z,    MO_X,    MO_C,    KC_D,    MO_V,                         KC_K,    KC_H, _______,  _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'

  ),

  [_DVORAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______,  KC_SLSH, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,   KC_R, KC_L    ,  _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,   KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N, KC_S    , _______ ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, MO_QUOT,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M, KC_W  ,  KC_V  , KC_Z    , _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'

  ),

  [_UTIL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, _______, KC_F1  ,  KC_F2  , KC_F3  , KC_F4  ,                      KC_PGUP, MM_LE,   KC_UP,   MM_RI,   ACCENT , WBACK ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, KC_F5  ,  KC_F6  , KC_F7  , KC_F8  ,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, KC_F9  ,  KC_F10 , KC_F11 , KC_F12 ,                      MM_N   , SP_LE,   _______, SP_RI,   BSLS,    KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______ , _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_DESKTOP] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, _______, MA_PAR , MA_SBRA, MA_CBRA, PIPE   ,                       _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, JIS_LPA, JIS_LSB, JIS_LCB, CURD   ,                       _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, JIS_RPA, JIS_RSB, JIS_RCB, POT    ,                       _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     QK_GESC, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SYM_AT , KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, GUI_ENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, KC_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_EISU, _______,    _______, KC_KANA, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_DIGITS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, _______, _______, DIV    , ASTER  , PIPE   ,                       KC_JYEN, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, MINUS  , PLUS   , CURD   ,                       KC_DLR , KC_P4,   KC_P5,   KC_P6,   KC_PAST, EQUAL  ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, KC_COMM, KC_DOT , POT    ,                       KC_EQL ,  KC_P1 ,  COMM_2,  DOT_3 , KC_PMNS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_SPC , _______,    _______, KC_P0   , _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_CONFIG] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, _______,                       QWE_ON , COL_ON ,  DVO_ON, _______, _______, MACLOCK,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_RPRN, KC_UNDS, KC_PLUS, KC_AT  , _______,                       _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_HASH, KC_LCBR, KC_RCBR, KC_PIPE, _______,                       _______, _______, _______, _______, KC_UP,   _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

/*********************** [END] Keyboard Layout ************************/
/*********************** [START] Keyboard specific config ************************/

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0xFF, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xff, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

// [START] Layer indication with sound
layer_state_t layer_state_set_user(layer_state_t state){
  oled_write_P(PSTR("Layer: "), false);
  switch (get_highest_layer(state)) {
    case _QWERTY:
        oled_write_ln_P(PSTR("QWERTY"), false);
        break;
    case _COLEMAK:
        oled_write_ln_P(PSTR("COLEMAK"), false);
        break;
    case _DVORAK:
        oled_write_ln_P(PSTR("DVORAK"), false);
        break;
    case _UTIL:
        oled_write_ln_P(PSTR("Util"), false);
        break;
    case _DESKTOP:
        oled_write_ln_P(PSTR("Desk"), false);
        break;
    case _DIGITS:
        oled_write_ln_P(PSTR("Digits"), false);
        break;
    case _CONFIG:
        oled_write_ln_P(PSTR("Config"), false);
        break;
    case _SYMBOLS:
        oled_write_ln_P(PSTR("Symbols"), false);
        break;
  }
  return state;
}

// [END] Layer indication with sound

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // oled_render_layer_state();
        // oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE

/*********************** [END] Keyboard specific config ************************/
/*********************** [START] Custom key definitions ************************/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
//-----> [START] Custom mode tap definitions *****************************
        case MO_QUOT:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_LBRC); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode

        case MO_X:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _COLEMAK) {
                    // tap_code16(C(KC_X)); // todo find a better way to do it on  windows
                    tap_code16(G(KC_X));
                }
                else {
                    tap_code16(G(KC_X)); // intercept hold function to send cmd-X
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_C:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _COLEMAK) {
                    tap_code16(G(KC_C)); // todo find a better way to do it on  windows
                }
                else {
                    tap_code16(G(KC_C)); // intercept hold function to send # cmd-C
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_V:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _COLEMAK) {
                    // tap_code16(C(KC_V)); // paste on windows
                    tap_code16(G(KC_V));
                }
                else {
                    tap_code16(G(KC_V)); // intercept hold function to send cmd-V
                }

                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case ROKA:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_KANA); // intercept hold function to send KANA
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
        // case W_SHIFT:
        //     if (record->tap.count && record->event.pressed){
        //         tap_code16(KC_UNDS); // intercept tap function to send _
        //     } else if (record->event.pressed){
        //         // intercept hold function to press
        //         layer_on(_WISHI);
        //     } else {
        //         layer_off(_WISHI); // intercept hold function button release
        //     }
        //     return false;  // Return false to avoid normal processing of mod-tap
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
/*********************** [END] Custom key definitions ************************/
/*********************** [START] Extra optimizations ************************/

// try to enable rolling motion on custom mod-tap key to a better performance while fast typing
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
        case W_SHIFT:
            return true; // immediately select the hold action when another key is pressed
        case SF_UN:
            return true;
        case LT_LSPC:
            return true;
        case ENT_LT:
            return true;
        case UTIL:
            return true;
        case LT_TAB:
            return true;
        default:
            return false; // other keys behave as normal
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_RSPC:
            // Activate permissive hold on this key
            return true;
        default:
            // Use default mode for every other key
            return false;
    }
}
/*********************** [END] Extra optimizations ************************/
