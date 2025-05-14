#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _COLEMAK, // DH variant
  _DVORAK,
  _UTIL,
  _LOWER,
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
  MA_CODE,
  CK_LSP, // custom keycode
  CK_RSP, // custom keycode
};


/*********************** [END] Macro declarations ************************/

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
#define LOWER MO(_LOWER)

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

// JIS
#define JP_AT KC_LBRC // "@" symbol using JIS config
#define JP_LPA KC_ASTERISK // "(" Left parenthesis
#define JP_RPA KC_LEFT_PAREN // ")" Right parenthesis
#define JP_LCB KC_RCBR // "{" Left curly brace
#define JP_RCB KC_PIPE // "}" Right curly brace
#define JP_LSB KC_RBRC // "[" left square bracket
#define JP_RSB KC_BSLS // "]" Right bracket
#define JP_BSLS A(KC_JYEN)  // "\" backslash
#define JP_PIPE S(KC_JYEN) // "|" pipe
#define JP_POT KC_EQL // "^"
#define JP_CURD KC_TILD // "~"
#define JP_BCKT KC_GRV // "`" 
#define JP_EQU KC_UNDS // "=" 
#define JP_PLUS KC_COLN // "+" 
#define JP_ASTR KC_DQUO // "*" 
#define JP_AND KC_CIRC // "&" 
#define JP_QUOT KC_AMPR // " ' "
#define JP_DQUO KC_AT // " " " 
#define JP_COLO KC_QUOT // :
#define JP_SCLN KC_SCLN// ;
//SP
#define SP_N A(KC_N) // "  ˜  " 
#define SP_ACCE A(KC_E) // input spanish accent using JIS


#define MM_LE G(KC_LEFT) // move to the start of the current line (*1)
#define MM_RI G(KC_RGHT) // move to the end of the current line   (*2)
#define SP_LE A(KC_LEFT) // move the caret one word to the left   (*3)
#define SP_RI A(KC_RGHT) // move the caret one word to the right  (*4)


#define JI_QUOT S(KC_7) // input ' using JIS
#define JI_LCBR S(KC_RBRC) // input { using JIS
#define JI_LPRN KC_ASTR // input ( using JIS
#define ALFRED C(KC_SPC) // activate alfred in OSx
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
#define QWE_ON TO(_QWERTY) // activates only base layer

// Custom mod-tap
#define MO_QUOT LT(0, JP_COLO ) // @ on hold : on tap
#define MO_X LT(0, KC_X) // Cut on hold X on tap
#define MO_C LT(0, KC_C) // Copy on hold C on tap
#define MO_V LT(0, KC_V) // Paste on hold V on tap
#define MO_D LT(0, KC_D) // Paste on hold, D on tap, for colemak
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

#define MO_SLSH CTL_T(KC_SLSH)
#define MO_DOT OPT_T(KC_DOT)
#define MO_COMM CMD_T(KC_COMM)

#define CK_LSFT OSM(MOD_LSFT)


#define EXTRA_DELAY 200

/*********************** [END] Aliases ************************/
/*********************** [START] Keyboard Template ************************/

/*

  [_LAYER] = LAYOUT_preonic_grid (
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘
  ),

*/

/*********************** [End] Keyboard Template ************************/
/*********************** [START] Keyboard Layout ************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_preonic_grid (

  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      LT_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      UTIL    , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , MO_QUOT , ENT_LT  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      CK_LSFT , KC_Z    , MO_X    , MO_C    , MO_V    , KC_B    , KC_N    , KC_M    , MO_COMM , MO_DOT  , MO_SLSH , SF_UN   ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      XXXXXXX , XXXXXXX , XXXXXXX , LOWER   , LT_LSPC , LT_LSPC , LT_RSPC , LT_RSPC , LOWER   , XXXXXXX , XXXXXXX , CONFI
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘

),
[_COLEMAK] = LAYOUT_preonic_grid (
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      LT_TAB  , KC_Q    , KC_W    , KC_F    , KC_P    , KC_B    , KC_J    , KC_L    , KC_U    , KC_Y    , MO_QUOT , KC_BSPC ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      UTIL    , KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , ENT_LT  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LSFT , KC_SLSH , MO_X    , MO_C    , MO_D    , KC_V    , KC_K    , KC_H    , KC_COMM , KC_DOT  , KC_Z    , SF_UN   ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      XXXXXXX , XXXXXXX , XXXXXXX , LOWER   , LT_LSPC , LT_LSPC , LT_RSPC , LT_RSPC , LOWER   , XXXXXXX , XXXXXXX , XXXXXXX
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘
), 
[_UTIL] = LAYOUT_preonic_grid (
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_PGUP , MM_LE   , KC_UP   , MM_RI   , SP_ACCE , WBACK   ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , JP_SCLN , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , KC_F9   , KC_F10  , KC_F11  , KC_F12  , SP_N    , SP_LE   , _______ , SP_RI   , JP_BSLS , KC_RSFT ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , ALFRED  , ALFRED  , _______ , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
[_LOWER] = LAYOUT_preonic_grid (
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_1    , KC_2    , KC_3   , KC_4     , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
[_DESKTOP] = LAYOUT_preonic_grid (
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , MA_PAR  , MA_SBRA , MA_CBRA , JP_PIPE , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , JP_LPA  , JP_LSB  , JP_LCB  , JP_CURD , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , JP_RPA  , JP_RSB  , JP_RCB  , JP_POT  , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
[_SYMBOLS] = LAYOUT_preonic_grid ( // []()(-{}@?%)
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      QK_GESC , MA_CODE , KC_LABK , KC_RABK , JP_QUOT , JP_DQUO , _______ , KC_LCBR , JP_LSB  , JP_RSB  , JP_AT   , KC_MINS ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_EXLM , KC_MINS , JP_PLUS , JP_EQU  , KC_HASH , JP_AND  , JP_PIPE , JP_LPA  , JP_RPA  , _______ , GUI_ENT ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , KC_SLSH , JP_ASTR , JP_BSLS , JP_POT  , KC_DLR  , JP_CURD , JP_LCB  , JP_RCB  , KC_PERC , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , KC_EISU , KC_EISU , KC_KANA , KC_KANA , _______ , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
[_DIGITS] = LAYOUT_preonic_grid (
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , KC_SLSH , JP_ASTR , JP_PIPE , KC_JYEN , KC_7    , KC_8    , KC_9    , KC_PAST , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , KC_MINS , JP_PLUS , JP_CURD , KC_DLR  , KC_4    , KC_5    , KC_6    , KC_PMNS , JP_EQU  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , KC_COMM , KC_DOT  , JP_POT  , KC_PSLS , KC_1    , KC_2    , KC_3    , KC_COLN , KC_DOT  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , KC_SPC  , KC_SPC  , KC_P0   , KC_0    , KC_DOT  , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
[_CONFIG] = LAYOUT_preonic_grid (
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , JP_AND  , JP_QUOT , KC_ASTR , KC_LPRN , _______ , QWE_ON  , COL_ON  , _______ , _______ , _______ , MACLOCK ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_RPRN , KC_UNDS , KC_PLUS , JP_DQUO , _______ , _______ , _______ , _______ , _______ , _______ , AU_ON ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_HASH , KC_LCBR , KC_RCBR , KC_PIPE , _______ , _______ , _______ , _______ , _______ , KC_UP   , AU_OFF ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_LEFT , KC_DOWN , KC_RGHT
  //└─────────┴─────────┴─────────┴─────────┴───────────────────┴───────────────────┴─────────┴─────────┴─────────┴─────────┘
  )
};

/*********************** [END] Keyboard Layout ************************/
/*********************** [START] Keyboard specific config ************************/

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
#endif
}
// [END] Layer indication with sound

/*********************** [END] Keyboard specific config ************************/
/*********************** [START] Custom key definitions ************************/

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


/*********************** [END] Custom key definitions ************************/
/*********************** [START] Extra optimizations ************************/

/*********************** [END] Extra optimizations ************************/


/*----------------------------------------------------------------------------
   Process record (custom keycodes & mod–tap behaviors)
----------------------------------------------------------------------------*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO_QUOT:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_LBRC);
                return false;
            }
            return true;

        case MO_X:
            if (!record->tap.count && record->event.pressed) {
                if (biton32(layer_state) == _COLEMAK) {
                    tap_code16(G(KC_X));
                } else {
                    tap_code16(G(KC_X));
                }
                return false;
            }
            return true;

        case MO_C:
            if (!record->tap.count && record->event.pressed) {
                if (biton32(layer_state) == _COLEMAK) {
                    tap_code16(G(KC_C));
                } else {
                    tap_code16(G(KC_C));
                }
                return false;
            }
            return true;

        case MO_V:
            if (!record->tap.count && record->event.pressed) {
                if (biton32(layer_state) == _COLEMAK) {
                    tap_code16(G(KC_V));
                } else {
                    tap_code16(G(KC_V));
                }
                return false;
            }
            return true;

        case MO_D:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(G(KC_V));
                return false;
            }
            return true;

        case ROKA:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_KANA);
                return false;
            }
            return true;

        case COMM_2:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_COMM);
                return false;
            }
            return true;

        case DOT_3:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(KC_DOT);
                return false;
            }
            return true;

        case LT_LSPC:
            if (record->tap.count && record->event.pressed) {
                tap_code16(ALFRED);
            } else if (record->event.pressed) {
                layer_on(_SYMBOLS);
            } else {
                    layer_off(_SYMBOLS);
            }
            return false;

        case LT_RSPC:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_SPC);
            } else if (record->event.pressed) {
                layer_on(_SYMBOLS);
            } else {
                layer_off(_SYMBOLS);
            }
            return false;

        // Custom macro definitions
        case MA_SBRA:  // Send [] (JIS style)
            if (record->event.pressed) {
                tap_code16(JP_LSB);
                tap_code16(JP_RSB);
                tap_code16(KC_LEFT);
            }
            break;

        case MA_CBRA: // Send {} (JIS style)
            if (record->event.pressed) {
                tap_code16(KC_RCBR);
                tap_code16(KC_PIPE);
                tap_code16(KC_LEFT);
            }
            break;

        case MA_PAR: // Send () (JIS style)
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

        case MA_CODE: // Send ```
            if (record->event.pressed) {
                tap_code16(JP_BCKT);
                tap_code16(JP_BCKT);
                tap_code16(JP_BCKT);
            }
            break;
    }
    return true;
}

/*********************** [START] Extra optimizations ************************/

// Hold on other keypress takes precedence, as this returns hold before the tapping term finishes
// Choose hold on other key press, when you don't care about rolling motion, and whant to have the 
// hold action activate as soon as other key is pressed while the dual action key is pressed
// This means rolling motion will activate the hold action, this makes sense when you want to activate
// a modifier that does not make too much sense to be a tap
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
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

// permissive hold allows rolling motion under the tapping term be computed as a tap tap
// this makes sense when you are mapping keys that the tap is super fast, such as spaces or letters
// this will allow to perform rolling motion and get the tap tap expected behaviour
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_RSPC:
            // Activate permissive hold on this key
            return true;
        case MO_SLSH:
            return true;
        case MO_DOT:
            return true;
        case MO_COMM:
            return true;
        default:
            // Use default mode for every other key
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT_RSPC:
            return QUICK_TAP_TERM - 120; // the default is 120 so this key is basically disabling the quick tap term
        default:
            return QUICK_TAP_TERM;
    }
}
/*********************** [END] Extra optimizations ************************/