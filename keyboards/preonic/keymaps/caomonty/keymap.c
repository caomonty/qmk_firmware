#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _QWERTY_WIN,
  _UTIL,
  _WUTIL,
  _DESKTOP,
  _DIGITS,
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

float util_on[][2] = SONG(M__NOTE(_C4, 1),);
float desktop_on[][2] = SONG(M__NOTE(_D4, 1),);
float numeric_on[][2] = SONG(M__NOTE(_E4, 1),);
float windows_on[][2] = SONG(M__NOTE(_F4, 1));
float config_on[][2] = SONG(M__NOTE(_B4, 1),);
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
#define WUTIL MO(_WUTIL)
#define WISHIFT MO(_WISHI)
#define WI_SLSH KC_SLSH
#define WM_LE A(KC_LEFT) // moves caret to the start of the line
#define WM_RI A(KC_RGHT) // moves caret to the end of the line
#define WP_LE C(KC_LEFT) // moves caret to the start of the previous word
#define WP_RI C(KC_RIGHT) // moves caret tot the next word
#define WI_ON TG(_QWERTY_WIN) // toggles the layer on or off

// Custom mod-tap
#define MO_Q LT(0, KC_Q) // 1 on hold q on tap
#define MO_W LT(0, KC_W) // 2 on hold w on tap
#define MO_E LT(0, KC_E) // 3 on hold e on tap
#define MO_R LT(0, KC_R) // 4 on hold r on tap
#define MO_T LT(0, KC_T) // 5 on hold t on tap
#define MO_Y LT(0, KC_Y) // 6 on hold y on tap
#define MO_U LT(0, KC_U) // 7 on hold y on tap
#define MO_I LT(0, KC_I) // 8 on hold y on tap
#define MO_O LT(0, KC_O) // 9 on hold y on tap
#define MO_P LT(0, KC_P) // 0 on hold p on tap
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │        │        │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │ ⇆ | [#]│  Q | 1 │  W | 2 │  E | 3 │  R | 4 │ T | 5  │ Y | 6  │ U | 7  │ I | 8  │ O | 9  │ P | @  │ ← | ?  │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │ C | [U]│   A    │    S   │    D   │    F   │   G    │   H    │   J    │    K   │   L    │  : | @ │   Ent  │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │   ⇧    │   Z    │    X   │    C   │    V   │   B    │   N    │   M    │    ,   │   .    │   /    │ shift _│
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │  ___   │  CTL   │ Alt    │ GUI    │ Alfred | [¥1]   │   Space | [¥1]  │ GUI    │ '      │   @    │ LayerC │
 * └────────┴────────┴────────┴────────┴─────────────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
[_QWERTY] = LAYOUT_preonic_grid (
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX,   XXXXXXX, XXXXXXX,
  LT_TAB,   MO_Q,    MO_W,    MO_E,    MO_R,    MO_T,    MO_Y,    MO_U,      MO_I,     MO_O,      MO_P,    KC_BSPC,
  UTIL,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,      KC_K,     KC_L,      MO_QUOT, ENT_LT ,
  KC_LSFT,  KC_Z,    MO_X,    MO_C,    MO_V,    KC_B,    KC_N,    KC_M,      KC_COMM,  KC_DOT,    KC_SLSH, SF_UN  ,
  XXXXXXX,  KC_LCTL, KC_LALT, KC_LGUI, LT_LSPC, LT_LSPC, LT_RSPC, LT_RSPC,   CONFI,    KC_LEFT,   KC_DOWN, KC_RGHT
),
[_QWERTY_WIN] = LAYOUT_preonic_grid(
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* Utility
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │   ~    │  F1    │ F2     │ F3     │ F4     │  F5    │        │        │   '    │    `   │   |    │   ^    │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │  F6    │ F7     │ F8     │ F9     │ F10    │  pg up │   *1   │   up   │   *2   │ Accent │ Delete │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │ DeskMa │ WinMa  │        │ F11    │ F12    │ pg down│   left │   down │  right │   :    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │ Caps   │        │        │        │        │        │        │   *3   │        │   *4   │   \    │        │
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │  Ctrl + GUI     │   Spotlight     │        │        │        │        │
 * └────────┴────────┴────────┴────────┴─────────────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
[_UTIL] = LAYOUT_preonic_grid(
  _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, KC_F1  ,  KC_F2  , KC_F3  , KC_F4  , KC_PGUP, MM_LE,   KC_UP,   MM_RI,   ACCENT , WBACK ,
  _______, _______, KC_F5  ,  KC_F6  , KC_F7  , KC_F8  , KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_SCLN, _______,
  _______, _______, KC_F9  ,  KC_F10 , KC_F11 , KC_F12 , MM_N   , SP_LE,   _______, SP_RI,   BSLS,    KC_RSFT,
  _______, _______, _______,  _______, CGUI,    CGUI,    SPOT,    SPOT,    _______, _______, _______, _______
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
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │                 │     Help        │        │        │        │        │
 * └────────┴────────┴────────┴────────┴─────────────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
[_DESKTOP] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, MA_PAR , MA_SBRA, MA_CBRA, PIPE   , _______, _______, _______, _______, _______, _______,
  _______, _______, JIS_LPA, JIS_LSB, JIS_LCB, CURD   , _______, _______, _______, _______, _______, _______,
  _______, _______, JIS_RPA, JIS_RSB, JIS_RCB, POT    , _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_SYMBOLS] = LAYOUT_preonic_grid(
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
 QK_GESC, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, SYM_AT , KC_MINS,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, GUI_ENT,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLSH, _______,
 _______, _______, _______, _______, KC_EISU, KC_EISU, KC_KANA, KC_KANA, _______, _______, _______, _______
),
/* Digits
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │        │    {   │    }   │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │   /    │    *   │    |   │    ¥   │   7    │   8    │    9   │   /    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │   -    │    +   │    ~   │    $   │   4    │   5    │   6    │   *    │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │    ,   │   .    │    ^   │    ^   │   1    │   2    │   3    │   -    │        │
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │                 │        0        │   .    │   ,    │   +    │        │
 * └────────┴────────┴────────┴────────┴─────────────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
[_DIGITS] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, DIV    , ASTER  , PIPE   , KC_JYEN, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
  _______, _______, _______, MINUS  , PLUS   , CURD   , KC_DLR , KC_P4,   KC_P5,   KC_P6,   KC_PAST, EQUAL  ,
  _______, _______, _______, KC_COMM, KC_DOT , POT    , KC_EQL,  KC_P1,   COMM_2,  DOT_3,   KC_PMNS, _______,
  _______, _______, _______, _______, KC_SPC , KC_SPC , _______, KC_P0,   KC_PDOT, KC_COMM, KC_PPLS, _______
),

/* Config
 * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
 * │        │        │        │        │        │        │        │        │        │        │        │ScreenC │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │Freq up │        │        │        │        │        │  Ins   │        │        │        │
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │Click on│FreqDown│ClickOff│        │        │        │        │        │        │        │TermFold│
 * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │        │        │        │        │        │  Up    │        │        │
 * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┼────────┼────────┼────────┤
 * │        │        │        │        │                 │                 │  Left  │ Down   │ Right  │        │
 * └────────┴────────┴────────┴────────┴─────────────────┴─────────────────┴────────┴────────┴────────┴────────┘
 */
[_CONFIG] = LAYOUT_preonic_grid(
  AU_ON  , KC_TILD, KC_EXLM, KC_DLR , KC_PERC, _______, _______, _______, _______, _______, _______, _______,
  AU_OFF , KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, _______, _______, _______, _______, _______, _______, MACLOCK,
  _______, KC_RPRN, KC_UNDS, KC_PLUS, KC_AT  , _______, _______, _______, _______, _______, _______, _______,
  _______, KC_HASH, KC_LCBR, KC_RCBR, KC_PIPE, _______, _______, _______, _______, _______, KC_UP,   _______,
  KC_QUES, KC_COLN, KC_DQUO, KC_LABK, KC_RABK, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
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
    case _CONFIG:
      PLAY_SONG(config_on);
      break;
  }
  return state;
}

// [END] Layer indication with sound

// [START] Custom key behaviour
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
//-----> [START] Custom mode tap definitions *****************************
        case MO_Q:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_1); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_W:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_2); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_E:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_3); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_R:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_4); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_T:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_5); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_Y:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_6); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_U:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_7); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_I:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_8); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_O:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_9); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_P:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_LBRC); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode
        case MO_QUOT:
            if (!record->tap.count && record->event.pressed){
                tap_code16(KC_LBRC); // intercept hold function
                return false;
            }
            return true;  // Return true for normal processing of tap keycode

        case MO_X:
            if (!record->tap.count && record->event.pressed){
                if (biton32(layer_state) == _QWERTY_WIN) {
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
                if (biton32(layer_state) == _QWERTY_WIN) {
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
                if (biton32(layer_state) == _QWERTY_WIN) {
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
// [END] Custom key behaviour

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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO_Q:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_W:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_E:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_R:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_T:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_Y:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_U:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_I:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_O:
            return TAPPING_TERM + EXTRA_DELAY;
        case MO_P:
            return TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}

// [END] custom mod tap definition

// void keyboard_post_init_user(void) {
// #ifdef AUDIO_ENABLE
//   wait_ms(500);
// #endif
// }

// [START]  Useful templates
// ┌─┬─┐ └─┴─┘ ├─┼─┤ │

///* Blank
// * ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐
// * │        │        │        │        │        │        │        │        │        │        │        │        │
// * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
// * │        │        │        │        │        │        │        │        │        │        │        │        │
// * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
// * │        │        │        │        │        │        │        │        │        │        │        │        │
// * ├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
// * │        │        │        │        │        │        │        │        │        │        │        │        │
// * ├────────┼────────┼────────┼────────┼────────┴────────┼────────┴────────┼────────┼────────┼────────┼────────┤
// * │        │        │        │        │                 │                 │        │        │        │        │
// * └────────┴────────┴────────┴────────┴─────────────────┴─────────────────┴────────┴────────┴────────┴────────┘
// */
//[_BLANK] = LAYOUT_preonic_grid(
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//),

// [END] Useful templates
