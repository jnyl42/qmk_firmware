#include "levinson.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _FN3 5
#define _FN4 6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  FN3,
  FN4,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_CAPW LGUI(LSFT(KC_3))        // Capture whole screen
#define KC_CPYW LGUI(LSFT(LCTL(KC_3)))  // Copy whole screen
#define KC_CAPP LGUI(LSFT(KC_4))        // Capture portion of screen
#define KC_CPYP LGUI(LSFT(LCTL(KC_4)))  // Copy portion of screen
#define KC_X1 LOWER
#define KC_X2 RAISE
#define KC_X3 FN3
#define KC_X4 MT(MOD_LSFT, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH, X4 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL, X3 ,LGUI,LALT, X1 ,SPC ,     ENT , X2 ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_COLEMAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB , Q  , W  , F  , P  , G  ,      J  , L  , U  , Y  ,SCLN,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , R  , S  , T  , D  ,      H  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      K  , M  ,COMM,DOT ,SLSH, X4 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL, X3 ,LGUI,LALT, X1 ,SPC ,     ENT , X2 ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_DVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TAB ,QUOT,COMM,DOT , P  , Y  ,      F  , G  , C  , R  , L  ,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     BSPC, A  , O  , E  , U  , I  ,      D  , H  , T  , N  , S  ,SLSH,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT,SCLN, Q  , J  , K  , X  ,      B  , M  , W  , V  , Z  , X4 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
      X3 ,LCTL,LALT,LGUI, X1 ,LALT,     SPC , X2 ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,PMNS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     GRV , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,UNDS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,MPRV,MPLY,MNXT,    ,         ,VOLD,VOLU,MUTE,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,LALT,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_RAISE] = LAYOUT_kc(
  //,----+------+----+----+----+----.    ,----+----+----+----+----+----.
     ESC ,      ,    , UP ,    ,    ,     PGUP,HOME,LPRN,RPRN,BSLS,PIPE,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
     CAPS,SELECT,LEFT,DOWN,RGHT,DEL ,     PGDN, END,LBRC,RBRC,MINS,UNDS,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
         , UNDO ,CUT ,COPY,PASTE,   ,     LEFT,RGHT,LCBR,RCBR,PLUS,PEQL,
  //|----+------+----+----+----+----|    |----+----+----+----+----+----|
         ,      ,    ,    ,    ,LALT,         ,    ,    ,    ,    ,
  //`----+------+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_FN3] = LAYOUT_kc(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

/* Adjust (Lower + Raise)
 * ,------------------------------------------  ------------------------------------------.
 * |      |      |RGB Tg|Hue Up|Sat Up|Val Up|  |Qwerty|Colemk|Dvorak|      |      |Aud on|
 * |------+------+------+------+------+-------  -------+------+------+------+------+------|
 * | Reset|      |RGB Md|Hue Dn|Sat Dn|Val Dn|  |      |      |      |      |      |Audoff|
 * |------+------+------+------+------+------|  -------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |AGnorm|
 * |------+------+------+------+------+-------  -------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |AGswap|
 * `------------------------------------------  ------------------------------------------'
 */
  [_ADJUST] = LAYOUT_ortho_4x12( \
    _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,    QWERTY,  COLEMAK, DVORAK,  _______, _______, AU_ON,   \
    RESET,   _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,    _______, _______, _______, _______, _______, AU_OFF,  \
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, AG_NORM, \
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, AG_SWAP  \
  )


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
