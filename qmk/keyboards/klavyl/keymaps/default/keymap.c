#include QMK_KEYBOARD_H

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_LCAG LCAG(KC_NO)

enum custom_keycodes {
  KC_COMMA_LBRACE = SAFE_RANGE,
  KC_DOT_RBRACE,
  KC_LBRACKET_RBRACKET,
  KC_LANGLEBR_RANGLEBR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_GRAVE,         KC_1,          KC_2,          KC_3,         KC_4,            KC_5,           KC_6,                                             KC_7,                  KC_8,          KC_9,            KC_0,             KC_MINUS,        KC_EQUAL,           KC_BSPACE,
    KC_TAB,           KC_Q,          KC_W,          KC_E,         KC_R,            KC_T,           KC_DOT,                                           KC_DOT,                KC_Y,          KC_U,            KC_I,             KC_O,            KC_P,               KC_BSLASH,
    LT(1,KC_ESCAPE),  LCTL_T(KC_A),  LALT_T(KC_S),  LGUI_T(KC_D), LSFT_T(KC_F),    LCAG_T(KC_G),   KC_DOT,                                           KC_LEFT_BRACKET,       LCAG_T(KC_H),  LSFT_T(KC_J),    LGUI_T(KC_K),     LALT_T(KC_L),    LCTL_T(KC_SCOLON),  LT(2,KC_QUOTE),
    KC_LEFT_SHIFT,    KC_Z,          KC_X,          KC_C,         KC_V,            KC_B,           KC_DOT,                                           KC_RIGHT_BRACKET,      KC_N,          KC_M,            KC_COMMA_LBRACE,  KC_DOT_RBRACE,   KC_SLASH,           LSFT_T(KC_LANGLEBR_RANGLEBR),
                                                                  LT(2,KC_SPACE),  KC_ENTER,       KC_AUDIO_VOL_DOWN,                                KC_AUDIO_VOL_UP,       KC_ENTER,      LT(1,KC_SPACE)
  ),

  [1] = LAYOUT(
    RESET,            KC_F1,         KC_F2,         KC_F3,        KC_F4,           KC_F5,          KC_F6,                                            KC_NO,                 KC_NO,         KC_NO,           KC_NO,            KC_NO,           KC_NO,              KC_NO,
    EEPROM_RESET,     KC_NO,         KC_MS_BTN2,    KC_MS_UP,     KC_MS_BTN1,      KC_MS_WH_DOWN,  KC_NO,                                            RESET,                 KC_MAC_CUT,    KC_MS_BTN1,      KC_NO,            KC_MS_BTN2,      KC_NO,              KC_NO,
    KC_CAPS,          KC_PGUP,       KC_MS_LEFT,    KC_MS_DOWN,   KC_MS_RIGHT,     KC_MS_WH_UP,    KC_NO,                                            EEPROM_RESET,          KC_MAC_COPY,   KC_LSHIFT,       KC_LGUI,          KC_LALT,         KC_LCTRL,           KC_NO,
    KC_NO,            KC_PGDOWN,     KC_MAC_CUT,    KC_MAC_COPY,  KC_MAC_PASTE,    KC_NO,          KC_NO,                                            KC_NO,                 KC_MAC_PASTE,  KC_MS_LEFT,      KC_MS_UP,         KC_MS_DOWN,      KC_MS_RIGHT,        KC_NO,
                                                                  KC_NO,           KC_NO,          KC_NO,                                            KC_NO,                 KC_NO,         KC_NO
  ),

  [2] = LAYOUT(
    RESET,            KC_NO,         KC_NO,         KC_NO,        KC_NO,           KC_NO,          KC_NO,                                            KC_F7,                 KC_F8,         KC_F9,           KC_F10,           KC_F11,          KC_F12,             KC_DELETE,
    EEPROM_RESET,     KC_NO,         KC_NO,         KC_NO,        KC_NO,           KC_NO,          KC_NO,                                            RESET,                 KC_MAC_CUT,    LALT(KC_LEFT),   KC_UP,            LALT(KC_RIGHT),  KC_NO,              KC_NO,
    KC_NO,            KC_LCTRL,      KC_LALT,       KC_LGUI,      KC_LSHIFT,       KC_LCAG,        KC_NO,                                            EEPROM_RESET,          KC_MAC_COPY,   KC_LEFT,         KC_DOWN,          KC_RIGHT,        KC_PGUP,            KC_NO,
    KC_NO,            KC_NO,         KC_MAC_CUT,    KC_MAC_COPY,  KC_MAC_PASTE,    KC_NO,          KC_NO,                                            KC_NO,                 KC_MAC_PASTE,  LGUI(KC_LEFT),   KC_NO,            LGUI(KC_RIGHT),  KC_PGDOWN,          KC_NO,
                                                                  KC_NO,           KC_NO,          KC_NO,                                            KC_NO,                 KC_NO,         KC_NO
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_COMMA_LBRACE:
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSHIFT)) {
          register_code(KC_LBRACKET);
        } else {
          register_code(KC_COMMA);
        }
      } else {
        unregister_code(KC_LBRACKET);
        unregister_code(KC_COMMA);
      }
      return false;
    case KC_DOT_RBRACE:
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSHIFT)) {
          register_code(KC_RBRACKET);
        } else {
          register_code(KC_DOT);
        }
      } else {
        unregister_code(KC_RBRACKET);
        unregister_code(KC_DOT);
      }
      return false;
    case KC_LBRACKET_RBRACKET: {
      static bool we_unshifted = false;
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSHIFT)) {
          we_unshifted = true;
          unregister_code(KC_LSHIFT);
          register_code(KC_RBRACKET);
        } else {
          register_code(KC_LBRACKET);
        }
      } else {
        if (we_unshifted) {
          we_unshifted = false;
          register_code(KC_LSHIFT);
        }
        unregister_code(KC_RBRACKET);
        unregister_code(KC_LBRACKET);
      }
      return false;
    }
    case KC_LANGLEBR_RANGLEBR: {
      static bool we_shifted = false;
      if (record->event.pressed) {
        if (get_mods() & MOD_BIT(KC_LSHIFT)) {
          register_code(KC_DOT);
        } else {
          we_shifted = true;
          register_code(KC_LSHIFT);
          register_code(KC_COMMA);
        }
      } else {
        if (we_shifted) {
          we_shifted = false;
          unregister_code(KC_LSHIFT);
        }
        unregister_code(KC_DOT);
        unregister_code(KC_COMMA);
      }
      return false;
    }
  }
  return true;
}
