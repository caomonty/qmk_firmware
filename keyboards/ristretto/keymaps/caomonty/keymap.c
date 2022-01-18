/* Copyright 2021 Brandon Lewis
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

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _LOWER_R1,
    _UTIL,
    // _DESKTOP,
    _DIGITS,
    // _WMANAGE,
    _SYMBOLS,
    _CONFIG,
  };

  enum keycodes {
    ROKA = SAFE_RANGE
  };

  // Aliases to shorten code
#define LT_1 LT(_DIGITS, KC_TAB) // layer digits when held, tab when tapped
#define MO_SYM MO(_SYMBOLS)
#define NUM_SP LT(_LOWER_R1, KC_SPACE) // layer lower r when held, space when tapped
#define UTIL MO(_UTIL) // change to utility layer while held
#define CONFI MO(_CONFIG) // change to configuration layer while held
#define SF_UN RSFT_T(KC_RO) // shift when held, underscore when tapped
#define WMANA LM(_WMANAGE, MOD_LCTL | MOD_LALT | MOD_LSFT)  // change to windows management layer
#define DESK MO(_DESKTOP)  // change to desktop control layer
#define SPOT A(G(KC_SPC))  // Open spotlight, It may need to change the hotkey inside configuration
#define SCREEN G(S(KC_4))  // Mac screenshot hotkey
#define TERMF C(S(KC_T))   // New terminal at folder, (it needs configuration inside shortcuts -> services)
#define CGUI C(KC_LGUI) // Control + Left Gui

#define MM_LE G(KC_LEFT) // move to the start of the current line (*1)
#define MM_RI G(KC_RGHT) // move to the end of the current line   (*2)
#define SP_LE A(KC_LEFT) // move the caret one word to the left   (*3)
#define SP_RI A(KC_RGHT) // move the caret one word to the right  (*4)
#define BSLS A(KC_JYEN)  // backslash
#define PIPE S(KC_JYEN) // pipe

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /// Characters use to build layout: ┌─┬─┐ └─┴─┘ ├─┼─┤ │
    ///* Blank
    // * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    // * │        │        │        │        │        │        │        │        │        │        │        │        │        │
    // * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
    // * │        │        │        │        │        │        │        │        │        │        │        │        │        │
    // * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
    // * │        │        │        │        │        │        │        │        │        │        │        │        │        │
    // * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┤
    // * │        │        │        │        │                 │        │                 │        │        │        │        │
    // * └────────┴────────┴────────┴────────┴─────────────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┘
    // */
    //[_BLANK] = LAYOUT(
    //  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______ , _______ ,
    //  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______ , _______ ,
    //  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______ , _______ ,
    //  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
    //),
    /* QWERTY
    * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    * │  Tab   │   Q    │    W   │    E   │    R   │   T    │        │   Y    │   U    │    I   │   O    │   P    │ Backsp │
    * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
    * │ LayerU │   A    │    S   │    D   │    F   │   G    │        │   H    │   J    │    K   │   L    │   :    │   Ent  │
    * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
    * │ Shift  │   Z    │    X   │    C   │    V   │   B    │        │   N    │   M    │    ,   │   .    │   /    │ shift _│
    * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┤
    * │ Ctl    │  Alt   │ Ro/Ka  │ GUI    │                 │ MUTE   │      Space      │ GUI    │ '      │   @    │ LayerC │
    * └────────┴────────┴────────┴────────┴─────────────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┘
    */
    [_QWERTY] = LAYOUT(
     LT_1    , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T              , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
     UTIL    , KC_A    , KC_S    , KC_D    , KC_F    , KC_G              , KC_H    , KC_J    , KC_K    , KC_L    , KC_QUOT , KC_ENT  ,
     KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B              , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , SF_UN   ,
     KC_LCTL , KC_LALT , _______ , KC_LGUI , NUM_SP  , NUM_SP  , KC_MUTE , NUM_SP  , NUM_SP  , KC_RGUI , KC_AMPR , KC_LBRC , CONFI
    ),
    /* LOWER_R1
    * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
    * │   ESC  │    1   │    2   │    3   │   4    │    5   │        │    6   │    7   │    8   │   9    │   0    │   -    │
    * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
    * │        │        │        │        │        │        │        │        │        │        │        │        │        │
    * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
    * │        │        │        │        │        │        │        │        │        │        │        │        │        │
    * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┤
    * │        │        │        │        │                 │        │                 │        │        │        │        │
    * └────────┴────────┴────────┴────────┴─────────────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┘
    */
    [_LOWER_R1] = LAYOUT(
     KC_GESC , KC_1    , KC_2    , KC_3    , KC_4    , KC_5              , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_MINS ,
     MO_SYM  , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______ , _______ ,
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
 ),
 /* DIGITS
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │    ¥   │   7    │   8    │   9    │   /    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │    $   │   4    │   5    │   6    │   *    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │   1    │   2    │   3    │   -    │        │
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │                 │        │        0        │   .    │   ,    │   +    │        │
 * └────────┴────────┴────────┴────────┴─────────────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
 [_DIGITS] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______           , KC_JYEN , KC_P7   , KC_P8   , KC_P9   , KC_PSLS , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______           , KC_DLR  , KC_P4   , KC_P5   , KC_P6   , KC_PAST , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , KC_P1   , KC_P2   , KC_P3   , KC_PMNS , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_P0   , KC_P0   , KC_PDOT , KC_COMM , KC_PPLS , _______
 ),
 /* UTIL
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │                 │        │                 │        │        │        │        │
 * └────────┴────────┴────────┴────────┴─────────────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
 [_UTIL] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , MM_LE   , KC_UP   , MM_RI   , A(KC_E) , KC_DEL  ,
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , KC_LEFT , KC_DOWN , KC_RGHT , KC_SCLN , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , SP_LE   , _______ , SP_RI   , BSLS    , _______ ,
  _______ , _______ , _______ , _______ , MO_SYM  , MO_SYM  , _______ , SPOT    , SPOT    , _______ , _______ , _______ , _______
 ),
 /* SYMBOLS
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │                 │        │                 │        │        │        │        │
 * └────────┴────────┴────────┴────────┴─────────────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
 [_SYMBOLS] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , KC_RBRC , KC_BSLS , PIPE    , KC_EQL  ,
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , KC_RCBR , KC_PIPE , _______ , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______ , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
 ),
 /* CONFIG
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┤        ├────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │                 │        │                 │        │        │        │        │
 * └────────┴────────┴────────┴────────┴─────────────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
 [_CONFIG] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , KC_INS  , _______ , _______ , SCREEN  ,
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______ , TERMF   ,
  _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , KC_UP   , _______ , _______ ,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_LEFT , KC_DOWN , KC_RGHT , _______
 ),
};

// OLED and Encoder function is located in the ristretto.c File

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // switch (keycode) {
    //     case QWERTY:
    //       if (record->event.pressed) {
    //         set_single_persistent_default_layer(_QWERTY);
    //       }
    //       return false;
    //       break;
    //     case COLEMAK:
    //       if (record->event.pressed) {
    //         set_single_persistent_default_layer(_COLEMAK);
    //       }
    //       return false;
    //       break;
    //     case DVORAK:
    //       if (record->event.pressed) {
    //         set_single_persistent_default_layer(_DVORAK);
    //       }
    //       return false;
    //       break;
    //     case LOWER:
    //       if (record->event.pressed) {
    //         layer_on(_LOWER);
    //         update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //       } else {
    //         layer_off(_LOWER);
    //         update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //       }
    //       return false;
    //       break;
    //     case RAISE:
    //       if (record->event.pressed) {
    //         layer_on(_RAISE);
    //         update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //       } else {
    //         layer_off(_RAISE);
    //         update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //       }
    //       return false;
    //       break;
    //     case BACKLIT:
    //       if (record->event.pressed) {
    //         register_code(KC_RSFT);
    //         #ifdef BACKLIGHT_ENABLE
    //           backlight_step();
    //         #endif
    //         #ifdef RGBLIGHT_ENABLE
    //           rgblight_step();
    //         #endif
    //         #ifdef __AVR__
    //         writePinLow(E6);
    //         #endif
    //       } else {
    //         unregister_code(KC_RSFT);
    //         #ifdef __AVR__
    //         writePinHigh(E6);
    //         #endif
    //       }
    //       return false;
    //       break;
    //   }
    return true;
};
