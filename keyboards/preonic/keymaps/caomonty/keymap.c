#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _UTIL,
  _DESKTOP,
  _DIGITS,
  _WMANAGE,
  _CONFIG,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE
};

float util_on[][2] = SONG(M__NOTE(_C4, 1),);
float desktop_on[][2] = SONG(M__NOTE(_D4, 1),);
float numeric_on[][2] = SONG(M__NOTE(_E4, 1),);
float windows_on[][2] = SONG(M__NOTE(_F4, 1));
float config_on[][2] = SONG(M__NOTE(_B4, 1),);

// Aliases to shorten code
#define LT_1 LT(_DIGITS, KC_TAB) // layer digits when held, tab when tapped
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

/* Qwerty
┌─┬─┐ └─┴─┘ ├─┼─┤ │
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │  Gesc  │   1    │   2    │    3   │    4   │   5    │   6    │    7   │    8   │   9    │    0   │   -    │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │  Tab   │   Q    │    W   │    E   │    R   │   T    │   Y    │   U    │    I   │   O    │   P    │ Backsp │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │ LayerU │   A    │    S   │    D   │    F   │   G    │   H    │   J    │    K   │   L    │   :    │   Ent  │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │ Shift  │   Z    │    X   │    C   │    V   │   B    │   N    │   M    │    ,   │   .    │   /    │ shift _│
 * ├────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┼────────┤
 * │ Ctl    │  Alt   │ Romaji │ Kanji  │ GUI    │      Space      │ GUI    │ Ctl    │   '    │    @   │ LayerC │
 * └────────┴────────┴────────┴────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┴────────┘
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,      KC_8,     KC_9,      KC_0,    KC_MINS,
  LT_1,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,      KC_I,     KC_O,      KC_P,    KC_BSPC,
  UTIL,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,      KC_K,     KC_L,      KC_QUOT, KC_ENT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,      KC_COMM,  KC_DOT,    KC_SLSH, SF_UN,
  KC_LCTL,  KC_LALT, KC_HAEN, KC_HANJ, KC_LGUI, KC_SPC,  KC_SPC,  KC_RGUI,   KC_RCTL,  KC_AMPR,   KC_LBRC, CONFI
),
///* Blank
// * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
// * │        │        │        │        │        │        │        │        │        │        │        │        │
// * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
// * │        │        │        │        │        │        │        │        │        │        │        │        │
// * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
// * │        │        │        │        │        │        │        │        │        │        │        │        │
// * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
// * │        │        │        │        │        │        │        │        │        │        │        │        │
// * ├────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┼────────┤
// * │        │        │        │        │        │                 │        │        │        │        │        │
// * └────────┴────────┴────────┴────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┴────────┘
// */
//[_BLANK] = LAYOUT_preonic_grid(
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//),
/* Utility
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │   ~    │        │        │        │        │        │        │        │   [    │    ]   │   ^    │   |    │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │  pg up │   *1   │   up   │   *2   │ Accent │ Delete │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │ pg down│   left │   down │  right │   :    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │   *3   │        │   *4   │   \    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │                 │        │        │        │        │        │
 * └────────┴────────┴────────┴────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┴────────┘
 */
[_UTIL] = LAYOUT_preonic_grid(
  KC_PLUS, KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_RBRC, KC_BSLS, PIPE,    KC_EQL,
  _______, KC_F6,  KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_PGUP, MM_LE,   KC_UP,   MM_RI,   A(KC_E), KC_DEL,
  _______, DESK,   WMANA,   _______,  KC_F11,  KC_F12,  KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, _______,
  _______, _______, _______, _______, _______, _______, _______, SP_LE,   _______, SP_RI,   BSLS,    _______,
  _______, _______, _______, _______, CGUI,    SPOT,    SPOT,    _______, _______, _______, _______, _______
),
/* Dektop Control
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │ Menu   │Notific │MissionC│ Dash   │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │ Dock   │Left Des│ Expose │Rght Des│        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │ Tool   │ Stat   │ Drawer │Laun pad│        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │      Help       │        │        │        │        │        │
 * └────────┴────────┴────────┴────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┴────────┘
 */
[_DESKTOP] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, DC_MENU, DC_NOTI, DC_MISI, DC_DASH, _______, _______,
  _______, _______, _______, _______, _______, _______, DC_DOCK, DC_LEFT, DC_EXPO, DC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, DC_TOOL, DC_STAT, DC_DRWR, DC_LPAD, _______, _______,
  _______, _______, _______, _______, _______, DC_HELP, DC_HELP, _______, _______, _______, _______, _______
),
/* Digits
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │    ¥   │        │    {   │    }   │    /   │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │    $   │   7    │   8    │    9   │   *    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │   4    │   5    │   6    │   -    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │   1    │   2    │   3    │   +    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        0        │   0    │        │   .    │ Enter  │        │
 * └────────┴────────┴────────┴────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┴────────┘
 */
[_DIGITS] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, KC_JYEN, _______, KC_RCBR, KC_PIPE, KC_PSLS, _______,
  _______, _______, _______, _______, _______, _______, KC_DLR,  KC_P7,   KC_P8,   KC_P9,   KC_PAST, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______,
  _______, _______, _______, _______, _______, _______, _______, KC_P0,   _______, KC_PDOT, KC_PENT, _______
),

/* Window Management (using moom) it needs customization inside the software
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │Upper L │Upper   │Upper R │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │Lower L │Lower   │Lower R │        │Revert  │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │Half L  │        │Half R  │        │Full Scr│
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │Third L │Third M │Third R │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │ 55% Centered  W │        │        │        │        │        │
 * └────────┴────────┴────────┴────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┴────────┘
 */
[_WMANAGE] = LAYOUT_preonic_grid(
  KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,      KC_8,     KC_9,      KC_0,    KC_MINS,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,      KC_I,     KC_O,      KC_P,    KC_BSPC,
  _______,  KC_A,    _______, KC_D,    KC_F,    KC_G,    KC_H,    KC_J,      KC_K,     KC_L,      KC_SCLN, KC_ENT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,      KC_COMM,  KC_DOT,    KC_SLSH, KC_RO,
  KC_LCTL,  KC_LALT, KC_HAEN, KC_HANJ, KC_LGUI, KC_SPC,  KC_SPC,  KC_RGUI,   KC_RCTL,  KC_AMPR,   KC_LBRC, _______
),

/* Config
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │        │        │        │EEP rese│
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │Audio on│Audio of│Music sw│Mus mode│        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │Click on│Click of│clic rst│Voice - │Voice + │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┴────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │freq up │freq dow│        │                 │        │        │        │        │        │
 * └────────┴────────┴────────┴────────┴────────┴─────────────────┴────────┴────────┴────────┴────────┴────────┘
 */
[_CONFIG] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SCREEN,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, AU_ON,   AU_OFF,  MU_TOG,  MU_MOD,  _______, _______, _______, _______, _______, _______, TERMF,
  _______, CK_ON,   CK_OFF,  CK_RST,  MUV_DE,  MUV_IN,  _______, _______, _______, KC_UP,   _______, _______,
  _______, _______, CK_UP,   CK_DOWN, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______
)


};


bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;



uint8_t previous_layer = 0;
bool sound_layer = false;
bool start_up_sound = true;

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
    // [START] start up sound fix
    if (start_up_sound) {
      wait_ms(500);
      start_up_sound = false;
    }
    // [END] start up sound fix
#endif
}

// [START] Layer indication with sound
layer_state_t layer_state_set_user(layer_state_t state){
  switch (get_highest_layer(state)) {
    case _UTIL:
      PLAY_SONG(util_on);
      break;
    case _DESKTOP:
      PLAY_SONG(desktop_on);
      break;
    case _DIGITS:
      PLAY_SONG(numeric_on);
      break;
    case _WMANAGE:
      PLAY_SONG(windows_on);
      break;
    case _CONFIG:
      PLAY_SONG(config_on);
      break;
  }
  return state;
}

// [END] Layer indication with sound

// void keyboard_post_init_user(void) {
// #ifdef AUDIO_ENABLE
//   wait_ms(500);
// #endif
// }
