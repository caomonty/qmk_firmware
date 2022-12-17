#include QMK_KEYBOARD_H

/**************** SOME GLOBALS *********************/

bool onMac = false;
const float led_dim_ratio = 0.50;

/**************** [START] LAYOUT lightning *********************/

/*
[LEDS]
 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14
15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29
30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,       42,  43
44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,       56,  57
58,  59,  60,            61,                 62,  63,  64,  65,  66,  67

[KEYS]
ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   -,   =,  BCK, INS
TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   [,   ],    \,PGUP
CPS, A,   S,   D,   F,   G,   H,   J,   K,   L,   COL, QOT,  RETURN,PGDN
SFT, Z,   X,   C,   V,   B,   N,   M,   COM, DOT, SLS, SHIFT,    UP, DEL
CTL, GUI, ALT,           SPACEBAR,           ALT, FN, CTL, LFT, DWN, RIT
*/

/**************** [END] LAYOUT lightning *********************/


/***********************  [START] Layer mapping  ************************/


enum layers {
    _MAC,
    _WIN,
    _WANI,
    _MINE,
    _ARROW,
    _UTIL,
    _UTIL2,
    _WMAN,
    _MOUSE,
    _DI,
    _CONFIG
};

/***********************  [END] Layer mapping  ************************/


/***********************  [START] Layer lighting mapping  ************************/

//const layers_leds_map[] = {
//    [_WIN] = 29,
//    [_MAC] = 30,
//    [_UTIL] = 14,
//    [_UTIL2] = 15,
//    [_MOUSE] = 16,
//    [_DI] = 17
//};

/***********************  [END] Layer lighting mapping  ************************/


/*********************** MACROS DEFINITION START ************************/


enum custom_keycodes {
    M_HOME = SAFE_RANGE,
    M_END,
    M_PIPE,
    M_RO,
    M_SLFT,
    M_SRGHT,
    M_MUP,
    M_MDWN,
    M_ENT,
    M_L_MAC,
    M_L_WIN,
    M_PARENT,
    M_SQ_L,
    M_SQ_R,
    M_CR_L,
    M_CR_R,
    M_L_GAME,
    M_L_GAME_ALT,
    M_L_UTIL,
    M_L_UTIL_2,
    M_L_MOUSE,
    M_BSLS,
    M_SPLFT,
    M_SPRGH,
    M_CTL_Z,
    M_CTL_X,
    M_CTL_C,
    M_CTL_V,
    M_SPOT,
};

/*********************** MACROS DEFINITION END ************************/

/*********************** [START] keymap ************************/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT_60_tsangan_hhkb(
        KC_GESC,          KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,        KC_JYEN, KC_DEL,
        LT(_DI, KC_TAB),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_AMPR,       KC_BSPC,
        MO(_UTIL),        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,                LT(_UTIL2, KC_ENT),
        KC_LSFT,                   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_RO), MO(_CONFIG),
        XXXXXXX,          KC_LALT, KC_LGUI,                            KC_SPC,                                      KC_RGUI, KC_RCTL,       XXXXXXX
    ),
    [_WIN] = LAYOUT_60_tsangan_hhkb(
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        KC_LGUI, KC_LALT,                            _______,                                     _______, _______, _______
    ),
    [_WANI] = LAYOUT_60_tsangan_hhkb( // utility layer to wanikani reviews, the only change is ~ instead of esc
        KC_PLUS,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,        _______, _______,                            _______,                                     _______, _______, _______
    ),
    [_MINE] = LAYOUT_60_tsangan_hhkb( // Specifically made for minecraft playing on mac
        _______,         _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TAB,          _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LCTL,         _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_DOT,                     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,         KC_LGUI,   KC_LSFT,                            _______,                                     _______, _______, _______
    ),
    [_ARROW] = LAYOUT_60_tsangan_hhkb( // add arrows
        _______,         _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TAB,          _______,   _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______,
        KC_LCTL,         _______,   _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,
        KC_LSFT,                     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RSFT, _______,
        _______,         KC_LGUI,   KC_LSFT,                            _______,                                     _______, _______, _______
    ),
    [_UTIL] = LAYOUT_60_tsangan_hhkb(
        KC_SLEP, _______,    _______,                         _______, _______, _______, _______, _______, KC_RBRC, KC_BSLS, _______, _______, M_PIPE,   _______,  _______,
        _______, MO(_DI),    MO(_MOUSE),                      _______, _______, _______, KC_PGUP, M_HOME,  KC_UP,   M_END,   _______, A(KC_E), _______,  _______,
        _______, MO(_UTIL2), LM(_WMAN, MOD_LCTL | MOD_LALT),  _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,           M_ENT,
        _______,             _______,                         _______, _______, _______, _______, _______, M_SPLFT, _______, M_SPRGH, M_BSLS,   _______, _______,
        _______, _______,    _______,                                                    M_SPOT,                                      KC_HAEN,  KC_HANJ, _______
    ),
    [_UTIL2] = LAYOUT_60_tsangan_hhkb(
        _______, _______, _______, _______, _______, _______, _______, _______, M_CR_L,  M_CR_R,  _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, M_MUP,   _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, M_SLFT,  M_MDWN,  M_SRGHT, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, M_BSLS, _______, _______,
        _______, KC_HANJ, _______,                            _______,                                     _______, _______, _______
    ),
    [_WMAN] = LAYOUT_60_tsangan_hhkb(  // Window manager layer (macOS, magnet)
        _______, _______,    _______,    _______, _______, _______, _______, _______, KC_RBRC, KC_BSLS, _______, _______,  _______,  _______,  _______,
        _______, _______,    _______,    _______, _______, _______, KC_U,    KC_E,    KC_UP,   KC_T,    KC_I,    _______,  _______,  _______,
        _______, _______,    _______,    KC_LGUI, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,            _______,
        _______,             _______,    _______, _______, _______, _______, KC_J,    KC_D,    KC_F,    KC_G,    KC_K,     _______,  _______,
        _______, _______,    _______,                               KC_C,                                        _______,  _______,  _______
    ),
    [_MOUSE] = LAYOUT_60_tsangan_hhkb(
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______,   _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,   _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,          _______,
        _______,          _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                              KC_BTN1,                                     _______, _______, _______
    ),
    [_DI] = LAYOUT_60_tsangan_hhkb(
        _______, _______, _______, _______, _______, _______, _______, _______, KC_RCBR, KC_PIPE, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, KC_PAST, KC_7,    KC_8,    KC_9,    KC_PPLS, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_PSLS, KC_4,    KC_5,    KC_6,    KC_PMNS, _______,          _______,
        _______,          _______, _______, _______, _______, _______, KC_DOT,  KC_1,    KC_2,    KC_3,    M_BSLS,  _______, _______,
        _______, _______, _______,                            KC_0,                                        _______, _______, _______
    ),
    [_CONFIG] = LAYOUT_60_tsangan_hhkb(
        _______,          KC_F1,      KC_F2,     KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, EEP_RST,
        _______,          _______,    _______,   _______, _______, _______,   _______, _______, _______,   _______, _______, KC_UP,   _______, RESET,
        _______,          TG(_ARROW), _______,   _______, _______, _______,   _______, _______, _______,   _______, KC_LEFT, KC_RGHT,          _______,
        _______,                      _______,   _______, _______, _______,   _______, _______, TG(_MINE), _______, _______, KC_DOWN, _______, _______,
        _______,          _______,    _______,                                _______,                                     _______,   _______, _______
    )
};

/*********************** [END] keymap ************************/


//**************** [START] MATRIX SCANS Lightning *********************//

void rgb_matrix_indicators_user(void) {

    #ifdef RGB_MATRIX_ENABLE

    /*Ensure some leds don't completeley turn off if hsv value setting is below 100 in the rgb matrix config */
//    const uint8_t led_constant_val = rgb_matrix_config.hsv.v < 100 ? 100 : rgb_matrix_config.hsv.v;

    // Colors for layar indication
    // main
//    const uint8_t main_hsv_h = 0;
//    const uint8_t main_hsv_s = 255;
    // mac
//    const uint8_t mac_hsv_h = 0;
//    const uint8_t mac_hsv_s = 0;
     // gaming
//    const uint8_t gaming_hsv_h = 191;
//    const uint8_t gaming_hsv_s = 255;
    // const uint8_t gaming_comp_hsv_h = 64;
    // const uint8_t gaming_comp_hsv_s = 255;
//    const uint8_t gaming_second_hsv_h = 234;
//    const uint8_t gaming_second_hsv_s = 255;
    // util
//    const uint8_t util_hsv_h = 149;
//    const uint8_t util_hsv_s = 255;
    // util 2
//    const uint8_t util2_hsv_h = 85;
//    const uint8_t util2_hsv_s = 250;
    // mouse
//    const uint8_t mouse_hsv_h = 30;
//    const uint8_t mouse_hsv_s = 250;

    /* CapsLock LED indicator */
//    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
//        rgb_matrix_set_color_hsv(30, 999, 0, led_constant_val, 0.75); // WHITE
//    }
//    rgb matrix set color all TODO Check this function

    /* Current layer LED indicator */
    // rgb_matrix_set_color_hsv(layers_leds_map[get_highest_layer(layer_state)], 999, 0, led_constant_val, led_dim_ratio); // WHITE



    /* Blinking LED indicator when recording Dynamic Macro */

    /* Blinking LED indicator when playing Dynamic Macro */
    /* END Blinking LED indicator when playing Dynamic Macro */

// Layer indicators
    switch (biton32(layer_state)) {
//        case _WIN:
//            rgb_matrix_set_color(index, r, g, b)
// rgb(255, 107, 129) wild watermelon
//            rgb_matrix_set_color_all(255, 107, 129);
//            break;
//        case _MAC:
 //            watermelor color = rgb(255, 71, 87)
//            rgb_matrix_set_color_all(200, 20, 5);
//            break;
        case _MINE:
            rgb_matrix_set_color_all(255, 107, 129);
            break;
        case _UTIL:
        // ufo green rgb(46, 213, 115)
            rgb_matrix_set_color_all(46, 213, 115);
            break;
        case _UTIL2:
        // lime soap rgb(123, 237, 159)
            rgb_matrix_set_color_all(123, 237, 159);
            break;
        case _MOUSE:
        // bright greek rgb(55, 66, 250)
            rgb_matrix_set_color_all(55, 66, 250);
            break;
        case _DI:
        // saturated sky rgb(83, 82, 237)
            rgb_matrix_set_color_all(83, 82, 237);
            break;
        case _CONFIG: // color yellow as warning
            rgb_matrix_set_color_all(255, 255, 0);
            break;
    }

    #endif /* RGB_MATRIX */
}

//**************** [END] MATRIX SCANS Lightning *********************//

//**************** [START] MACROS *********************//


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M_HOME: // send cursor the the most left
        if (record->event.pressed) {
            SEND_STRING(SS_LCMD(SS_TAP(X_LEFT)));
        } else {
        }
        break;

    case M_END: // send cursor to the most right
        if (record->event.pressed) {
            SEND_STRING(SS_LCMD(SS_TAP(X_RIGHT)));
        } else {
        }
        break;

    case M_PIPE:  // send the pipe symbol | on a JIS layout
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_TAP(X_JYEN)));
        } else {
        }
        break;

    case M_RO:  // send inverted slash on a JIS layout
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_TAP(X_RO)));
        } else {
        }
        break;

    case M_SLFT: // send ctrl + left, on mac: move to left desktop
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_LEFT)));
        } else {
        }
        break;

    case M_SRGHT:  // send ctr + right, on mac: move to right desktop
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_RIGHT)));
        } else {
        }
        break;

    case M_SPLFT:  // move cursor to the left by a whole word
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
        } else {
        }
        break;

    case M_SPRGH:  // move cursor to the right by a whole word
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_TAP(X_RIGHT)));
        } else {
        }
        break;

    case M_ENT:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)) SS_TAP(X_ENT));
        } else {
        }
        break;

    case M_MUP:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_UP)));
        } else {
        }
        break;

    case M_MDWN:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL(SS_TAP(X_DOWN)));
        } else {
        }
        break;

    case M_L_MAC:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("l_mac");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_L_WIN:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("l_win");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_L_GAME:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("l_game");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_L_GAME_ALT:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("l_game_alt");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_L_UTIL:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("l_util");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_L_UTIL_2:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("l_util_2");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_L_MOUSE:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("l_mouse");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_SQ_L:  // send left square bracket
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_RBRC));
        } else {
        }
        break;

    case M_SQ_R:  // send right square bracket
        if (record->event.pressed) {
            SEND_STRING(SS_TAP(X_BSLS));
        } else {
        }
        break;

    case M_CR_L:  // send left curly braces
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_TAP(X_RBRC)));
        } else {
        }
        break;

    case M_CR_R:  // send right curly braces
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_TAP(X_BSLS)));
        } else {
        }
        break;

    case M_PARENT:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LSFT(SS_TAP(X_8) SS_TAP(X_9)) SS_TAP(X_LEFT));

        } else {
            // when keycode QMKBEST is released
        }
        break;

    case M_BSLS:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LALT(SS_TAP(X_JYEN)));
        } else {
            // when keycode QMKBEST is released
        }
        break;


    case M_CTL_Z: // ⌃Z
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_Z)));
        } else {
            // when keycode QMK is released
        }
        break;

    case M_CTL_X:  // ⌃X
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_X)));
        } else {
            // when keycode QMK is released
        }
        break;

    case M_CTL_C: // ⌃C
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_C)));
        } else {
            // when keycode QMK is released
        }
        break;

    case M_CTL_V:  // ⌃V
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_V)));
        } else {
            // when keycode QMK is released
        }
        break;

    case M_SPOT:
        // mac spotlight hotkey
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LGUI(SS_LALT(SS_TAP(X_SPACE))));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    }
    return true;
};


//**************** [END] MACROS *********************//



