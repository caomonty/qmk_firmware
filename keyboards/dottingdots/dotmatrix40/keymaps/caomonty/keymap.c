// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "timer.h"

#define FAST_SCROLL_THRESHOLD 100
#define VERY_FAST_SCROLL_THRESHOLD 50
#define FAST_MULTIPLIER 2
#define VERY_FAST_MULTIPLIER 4

/*----------------------------------------------------------------------------
   Layer definitions
----------------------------------------------------------------------------*/
enum dotmatrix_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _UTIL,
  _LOWER,
  _DIGITS,
  _SYMBOLS,
  _CONFIG,
};

/*----------------------------------------------------------------------------
   Custom keycodes
----------------------------------------------------------------------------*/
enum dotmatrix_keycodes {
  QWERTY = SAFE_RANGE,
  MA_SBRA,
  MA_CBRA,
  MA_PAR,
  MA_ALF,
  MA_CODE,
  CK_LSP,
  CK_RSP,
  CK_COLO // colon-on-tap custom keycode
};

/*----------------------------------------------------------------------------
   Aliases and custom macros
----------------------------------------------------------------------------*/
/*********************** [START] Aliases ************************/

// Aliases Fix japanese key codes
#define KC_RO KC_INTERNATIONAL_1
#define KC_JYEN KC_INTERNATIONAL_3
#define KC_KANA KC_LANGUAGE_1
#define KC_EISU KC_LANGUAGE_2

// Custom layer tap and hold
#define LT_TAB LT(_DIGITS, KC_TAB) // layer digits when held, tab when tapped
#define ENT_LT LT(_SYMBOLS, KC_ENT)// layer change when held, enter when tapped
#define UTIL MO(_UTIL)
#define LOWER MO(_LOWER)

// Aliases to shorten code
#define CONFI MO(_CONFIG) // change to configuration layer while held
#define SF_UN RSFT_T(KC_UNDS) // shift when held, underscore when tapped (was KC_RO)
#define SPOT A(G(KC_SPC))  // Open spotlight
#define SCREEN G(S(KC_4))  // Mac screenshot hotkey
#define TERMF C(S(KC_T))   // New terminal at folder
#define CGUI C(KC_LGUI) // Control + Left Gui
#define MINE TG(_MINE)
#define GUI_ENT G(KC_ENT) // Gui + Enter

// Symbol Aliases (updated for US ANSI layout)
#define JP_AT KC_AT          // @
#define JP_LPA KC_LPRN       // (
#define JP_RPA KC_RPRN       // )
#define JP_LCB KC_LCBR       // {
#define JP_RCB KC_RCBR       // }
#define JP_LSB KC_LBRC       // [
#define JP_RSB KC_RBRC       // ]
#define JP_BSLS KC_BSLS      // "\"
#define JP_PIPE KC_PIPE      // |
#define JP_POT KC_CIRC       // ^
#define JP_CURD KC_TILD      // ~
#define JP_BCKT KC_GRV       // `
#define JP_EQU KC_EQL        // =
#define JP_PLUS KC_PLUS      // +
#define JP_ASTR KC_ASTR      // *
#define JP_AND KC_AMPR       // &
#define JP_QUOT KC_QUOT      // '
#define JP_DQUO KC_DQUO      // "
#define JP_COLO KC_COLN      // :
#define JP_SCLN KC_SCLN      // ;

// Spanish input (mac-specific, may need app level config)
#define SP_N A(KC_N) 
#define SP_ACCE A(KC_E) 

#define MM_LE G(KC_LEFT)
#define MM_RI G(KC_RGHT)
#define SP_LE A(KC_LEFT)
#define SP_RI A(KC_RGHT)

#define JI_QUOT KC_QUOT
#define JI_LCBR KC_LCBR
#define JI_LPRN KC_LPRN
#define ALFRED C(KC_SPC)
#define WBACK LALT(KC_BSPC)
#define MACLOCK G(C(KC_Q))

// Windows-specific codes
#define WISHIFT MO(_WISHI)
#define WI_SLSH KC_SLSH
#define WM_LE A(KC_LEFT)
#define WM_RI A(KC_RGHT)
#define WP_LE C(KC_LEFT)
#define WP_RI C(KC_RGHT)
#define COL_ON TO(_COLEMAK)
#define QWE_ON TO(_QWERTY)

// mod tap
#define MO_SLSH CTL_T(KC_SLSH)
#define MO_DOT OPT_T(KC_DOT)
#define MO_COMM CMD_T(KC_COMM)

// Custom mod-tap
#define MO_QUOT LT(0, JP_COLO)
#define MO_X LT(0, KC_X)
#define MO_C LT(0, KC_C)
#define MO_V LT(0, KC_V)
#define MO_D LT(0, KC_D)
#define ROKA LT(0, KC_EISU)
#define DOT_3 LT(0, KC_3)
#define COMM_2 LT(0, KC_2)
#define W_SHIFT LT(0, KC_SLSH)
#define LT_RSPC LT(0, CK_RSP)
#define LT_LSPC LT(0, CK_LSP)
#define LT_RSHF LT(0, CK_RSHF)

// Desktop control
#define DC_MENU LCTL(KC_F2)
#define DC_DOCK LCTL(KC_F3)
#define DC_TOOL LCTL(KC_F5)
#define DC_STAT LCTL(KC_F8)
#define DC_DRWR LALT(LGUI(KC_QUOTE))
#define DC_LPAD LALT(LGUI(KC_Q))
#define DC_NOTI LALT(LGUI(LCTL(KC_B)))
#define DC_DASH LALT(LGUI(LCTL(KC_C)))
#define DC_HELP LSFT(LGUI(KC_SLASH))
#define DC_LEFT C(KC_LEFT)
#define DC_RGHT C(KC_RGHT)
#define DC_EXPO C(KC_DOWN)
#define DC_MISI C(KC_UP)

#define CK_LSFT OSM(MOD_LSFT)

#define EXTRA_DELAY 200


/*----------------------------------------------------------------------------
   Keymaps
   (Mapping: Use preonic rows 2-5 to fill the 4 physical rows on dotmatrix.)


  [_LAYER] = LAYOUT (
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ ,    _______   , _______ ,    _______   , _______ , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  ),

----------------------------------------------------------------------------*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      LT_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      UTIL    , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , CK_COLO , ENT_LT  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      CK_LSFT , KC_Z    , MO_X    , MO_C    , MO_V    , KC_B    , KC_N    , KC_M    , MO_COMM , MO_DOT  , MO_SLSH , SF_UN   ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      XXXXXXX , XXXXXXX , XXXXXXX , LOWER   ,   LT_LSPC    , KC_NO   ,   LT_RSPC    , LOWER   , XXXXXXX  , XXXXXXX , XXXXXXX
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
  
  [_COLEMAK] = LAYOUT(
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      LT_TAB  , KC_Q    , KC_W    , KC_F    , KC_P    , KC_B    , KC_J    , KC_L    , KC_U    , KC_Y    , CK_COLO , KC_BSPC ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      UTIL    , KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , ENT_LT  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LSFT , KC_Z    , MO_X    , MO_C    , MO_D    , KC_V    , KC_K    , KC_H    , MO_COMM , MO_DOT  , MO_SLSH , SF_UN   ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      XXXXXXX , XXXXXXX , XXXXXXX , LOWER   ,   LT_LSPC    , KC_NO   ,   LT_RSPC    , LOWER   , CONFI   , KC_LALT , XXXXXXX
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
  
  [_DVORAK] = LAYOUT(
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      LT_TAB  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      UTIL    , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , MO_QUOT , ENT_LT  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      KC_LSFT , KC_Z    , MO_X    , MO_C    , MO_V    , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , SF_UN   ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      XXXXXXX , XXXXXXX , XXXXXXX , LOWER   ,   LT_LSPC    , KC_NO   ,   LT_RSPC    , LT_RSPC , LOWER   , XXXXXXX , XXXXXXX
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
  
  [_UTIL] = LAYOUT(
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      _______ , _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_PGUP , MM_LE   , KC_UP   , MM_RI   , SP_ACCE , WBACK   ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , JP_SCLN , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , KC_F9   , KC_F10  , KC_F11  , KC_F12  , SP_N    , SP_LE   , _______ , SP_RI   , JP_BSLS , KC_RSFT ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______      , KC_NO   , ALFRED       , ALFRED  , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  ),

  [_LOWER] = LAYOUT(
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      _______ , KC_1    , KC_2    , KC_3   , KC_4     , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_EXLM , KC_DQUO , KC_HASH , KC_DLR  , KC_PERC , KC_AMPR , KC_QUOT , KC_LPRN , KC_RPRN , KC_RPRN , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______      , _______ , _______      , _______ , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
  
  [_DIGITS] = LAYOUT(
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      _______ , _______ , _______ , KC_SLSH , JP_ASTR , JP_PIPE , KC_JYEN , KC_7    , KC_8    , KC_9    , KC_PAST , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , KC_MINS , JP_PLUS , JP_CURD , KC_DLR  , KC_4    , KC_5    , KC_6    , KC_PMNS , JP_EQU  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , KC_COMM , KC_DOT  , JP_POT  , KC_PSLS , KC_1    , KC_2    , KC_3    , KC_COLN , KC_DOT  ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , KC_SPC       , KC_NO   , KC_P0        , KC_DOT  , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  ),
  
  [_SYMBOLS] = LAYOUT(
// Actual symbol representation
// //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
//             ,  ```    ,  <      ,  >      ,  '      ,  ''     ,         ,  `      ,  [      ,  ]      ,   @     ,   -     ,
// //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//             ,  !      ,  -      ,  +      ,  =      ,  #      ,  &      ,  |      ,  (      ,  )      ,         ,         ,
// //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//             ,         ,  /      ,  *      ,  \      ,  ^      ,  $      ,  ~      ,  {      ,  }      ,  %      ,         ,
// //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
//             ,         ,         ,         ,              ,         ,              ,         ,         ,         ,         
// //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      QK_GESC , MA_CODE , KC_LABK , KC_RABK , JP_QUOT , JP_DQUO , _______ , KC_GRV  , JP_LSB  , JP_RSB  , JP_AT   , KC_MINS ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_EXLM , KC_MINS , JP_PLUS , JP_EQU  , KC_HASH , JP_AND  , JP_PIPE , JP_LPA  , JP_RPA  , _______ , GUI_ENT ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , KC_SLSH , JP_ASTR , JP_BSLS , JP_POT  , KC_DLR  , JP_CURD , JP_LCB  , JP_RCB  , KC_PERC , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______      , KC_EISU , _______      , _______ , _______ , _______ , _______
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
// OLD layout
//   //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
//       QK_GESC , MA_CODE , KC_LABK , KC_RABK , JP_QUOT , JP_DQUO , JP_AND  , JP_SCLN , JP_LSB  , JP_RSB  , JP_AT   , KC_MINS ,
//   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//       _______ , KC_EXLM , KC_MINS , JP_PLUS , JP_EQU  , KC_HASH , JP_PIPE , JP_COLO , JP_LPA  , JP_RPA  , KC_QUES , GUI_ENT ,
//   //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
//       _______ , JP_POT  , KC_SLSH , JP_ASTR , JP_BSLS , _______ , JP_CURD , KC_DLR  , JP_LCB  , JP_RCB  , KC_PERC , _______ ,
//   //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
//       _______ , _______ , _______ , _______ , KC_EISU      , KC_EISU , KC_KANA      , KC_KANA , _______ , _______ , _______
//   //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  ),

  [_CONFIG] = LAYOUT(
  //┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐
      _______ , JP_AND  , JP_QUOT , KC_ASTR , KC_LPRN , _______ , QWE_ON  , COL_ON  , _______ , _______ , _______ , MACLOCK ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_RPRN , KC_UNDS , KC_PLUS , JP_DQUO , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , KC_HASH , KC_LCBR , KC_RCBR , KC_PIPE , _______ , _______ , _______ , _______ , _______ , KC_UP   , _______ ,
  //├─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤
      _______ , _______ , _______ , _______ , _______      , _______ , _______      , _______ , _______ , KC_LEFT , KC_DOWN
  //└─────────┴─────────┴─────────┴─────────┴──────────────┴─────────┴──────────────┴─────────┴─────────┴─────────┴─────────┘
  )
}; 




/*----------------------------------------------------------------------------
   Process record (custom keycodes & mod–tap behaviors)
----------------------------------------------------------------------------*/
static bool lspc_held = false;
static bool rspc_held = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_COLO:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // Temporarily disable Shift
                    uint8_t mods = get_mods();
                    del_mods(MOD_MASK_SHIFT);   // Remove Shift
                    tap_code16(KC_SCLN);        // Send semicolon
                    set_mods(mods);             // Restore mods
                } else {
                    tap_code16(KC_COLN);  // Tap: send colon
                }
            }
            return false;  // Skip default processing

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
            
        case RSFT_T(KC_UNDS):
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_UNDS); // Send KC_UNDS on tap
                return false;        // Return false to ignore further processing of key
            }
            break;

        case LT_LSPC:
            if (record->tap.count && record->event.pressed) {
                tap_code16(ALFRED);
            } else if (record->event.pressed) {
                lspc_held = true;
                layer_on(_SYMBOLS);
                if (rspc_held) {
                    layer_on(_CONFIG);
                }
            } else {
                lspc_held = false;
                layer_off(_SYMBOLS);
                layer_off(_CONFIG);  // turn off _CONFIG if either released
            }
            return false;

        case LT_RSPC:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_SPC);
            } else if (record->event.pressed) {
                rspc_held = true;
                layer_on(_SYMBOLS);
                if (lspc_held) {
                    layer_on(_CONFIG);
                }
            } else {
                rspc_held = false;
                layer_off(_SYMBOLS);
                layer_off(_CONFIG);  // turn off _CONFIG if either released
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
            return 0; // the default is 120 so this key is basically disabling the quick tap term
        default:
            return QUICK_TAP_TERM;
    }
}
/*********************** [END] Extra optimizations ************************/

/*----------------------------------------------------------------------------
   Encoder mapping
   (For now, every layer uses the same mapping.)
----------------------------------------------------------------------------*/
// #if defined(ENCODER_MAP_ENABLE)
// const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
//   [_QWERTY] = { ENCODER_CCW_CW(MS_WHLD, MS_WHLU) },
//   [_COLEMAK] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
//   [_DVORAK] = { ENCODER_CCW_CW(KC_UP, KC_DOWN) },
//   [_UTIL]    = { ENCODER_CCW_CW(KC_UP, KC_DOWN) },
//   [_DESKTOP] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
//   [_DIGITS]  = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
//   [_CONFIG]  = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
//   [_SYMBOLS] = { ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
// };
// #endif




static uint16_t last_encoder_time = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
    // Optional: only handle encoder 0
    if (index != 0) return false;

    // Measure how fast the encoder is turning
    uint16_t now = timer_read();
    uint16_t delta = now - last_encoder_time;
    last_encoder_time = now;

    uint8_t repeat = 1;
    if (delta < VERY_FAST_SCROLL_THRESHOLD) {
        repeat = VERY_FAST_MULTIPLIER;
    } else if (delta < FAST_SCROLL_THRESHOLD) {
        repeat = FAST_MULTIPLIER;
    }

    // Use KC_UP/KC_DOWN to move caret along with screen
    for (uint8_t i = 0; i < repeat; i++) {
        tap_code(clockwise ? KC_DOWN : KC_UP);
    }

    return false;
}



