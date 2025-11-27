#ifdef __INTELLISENSE__
#include "quantum.h"
#else
#include QMK_KEYBOARD_H
#endif

// Слои
enum sofle_layers {
    BASE,
    FN,
    NUM,
    MEDIA,
    OMARCHY,
    SYMB
};
    /*  
     * BASE Layer - QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.  
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |  
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
     * |   `  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |  
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
     * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |  
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|  
     * |LSft  |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RSft  |  
     * -----------------------------------------/       /      \      \-----------------------------------------'  
     *           | LGUI | LAlt | LCTR |OMARC | /Enter  /        \Space \  |MEDIA | RCTR | RAlt | RGUI |  
     */
// for workspaces 1..10 and GUI+Shift+number for 11..20. The last entry
// is a default/back key.
enum custom_keycodes {
    OM_WSP1 = SAFE_RANGE,
    OM_WSP2, OM_WSP3, OM_WSP4, OM_WSP5, OM_WSP6, OM_WSP7, OM_WSP8, OM_WSP9, OM_WSP10,
    OM_WSP11, OM_WSP12, OM_WSP13, OM_WSP14, OM_WSP15, OM_WSP16, OM_WSP17, OM_WSP18, OM_WSP19, OM_WSP20,
    OM_WSP_DEFAULT
};

const uint16_t omarchy_keys[21] = {
    OM_WSP1,  OM_WSP2,  OM_WSP3,  OM_WSP4,  OM_WSP5,  OM_WSP6,  OM_WSP7,  OM_WSP8,  OM_WSP9,  OM_WSP10,
    OM_WSP11, OM_WSP12, OM_WSP13, OM_WSP14, OM_WSP15, OM_WSP16, OM_WSP17, OM_WSP18, OM_WSP19, OM_WSP20,
    OM_WSP_DEFAULT // default
};

// file-scope state for encoder behavior
static bool is_muted = false;
static bool right_enc_pressed = false;

/*  
 * BASE Layer - QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.  
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bspc |  
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * |   `  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |  
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |  
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|  
 * |LSft  |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RSft  |  
 * -----------------------------------------/       /      \      \-----------------------------------------'  
 *           | LGUI | LAlt | LCTL |MO(OM) | /Space  /        \Enter \  |MEDIA | RCTL | RAlt | RGUI |  
 */

/*
 * FN Layer - Special Functions
 * ,-----------------------------------------.                    ,-----------------------------------------.  
 * | ESC  | F1   | F2   | F3   | F4   | F5   |                    | F6   | F7   | F8   | F9   | F10  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * |   `  |      |      |      |      |      |                    |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * | Tab  |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|  
 * |LSft  |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |      |
 * -----------------------------------------/       /      \      \-----------------------------------------'  
 *           | LGUI | LAlt | LCTL |MO(OM) | /Space  /        \Enter \  |MEDIA | RCTL | RAlt | RGUI |  
 */

/*
 * NUM Layer - Calculator / Numpad
 * ,-----------------------------------------.                    ,-----------------------------------------.  
 * | ESC  | P7   | P8   | P9   | P/   | P*   |                    | P-   |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * |   `  | P4   | P5   | P6   | P+   |      |                    |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * | Tab  | P1   | P2   | P3   | P0   |      |-------.    ,-------|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  NUMP |    |       |------+------+------+------+------+------|  
 * |LSft  |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |      |
 * -----------------------------------------/       /      \      \-----------------------------------------'  
 *          | LGUI | LAlt | LCTL |MO(OM) | /Space  /        \Enter \  |MEDIA | RCTL | RAlt | RGUI |  
 */

/*
 * MEDIA Layer - Media Controls
 * ,-----------------------------------------.                    ,-----------------------------------------.  
 * | ESC  |      |      |      |      |      | BSPC |                    |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * |   `  |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * | Tab  |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|  
 * |LSft  |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |      |
 * -----------------------------------------/       /      \      \-----------------------------------------'  
 *          | LGUI | LAlt | LCTL |MO(OM) | /Space  /        \Enter \  |MEDIA | RCTL | RAlt | RGUI |  
 */

/*
 * OMARCHY Layer - Workspace Control (left half mapped to workspace keys)
 * ,-----------------------------------------.                    ,-----------------------------------------.  
 * | ESC  | WS1  | WS2  | WS3  | WS4  | WS5  | BSPC  |                    |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * |   `  | WS6  | WS7  | WS8  | WS9  | WS10 |                    |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|  
 * | Tab  | WS11 | WS12 | WS13 | WS14 | WS15 |-------.    ,-------|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  WSPC |    |       |------+------+------+------+------+------|  
 * |LSft  | WS16 | WS17 | WS18 | WS19 | WS20 |-------|    |-------|      |      |      |      |      |      |      |
 * -----------------------------------------/       /      \      \-----------------------------------------'  
 *           | LGUI | LAlt | LCTL |MO(OM) | /Space  /        \Enter \  |MEDIA | RCTL | RAlt | RGUI |  
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_ESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_BSPC,
        KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,
        KC_LSFT, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,
        KC_LCTL, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,
        KC_LGUI, KC_LALT, KC_LCTL, MO(OMARCHY), KC_SPC, KC_ENT, MO(MEDIA), MO(FN), MO(SYMB), KC_RSFT
    ),
    [FN] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_BSPC,
        KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LGUI, KC_LALT, KC_LCTL, MO(OMARCHY), KC_SPC, KC_ENT, MO(MEDIA), MO(FN), MO(SYMB), KC_RSFT
    ),
    [NUM] = LAYOUT(
        KC_ESC, KC_P7, KC_P8, KC_P9, KC_PSLS, KC_PAST, KC_BSPC,
        KC_TAB, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_NO,  KC_NO,
        KC_LSFT,KC_P1, KC_P2, KC_P3, KC_P0,  KC_NO,  KC_NO,
        KC_LCTL,KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO,
        KC_LGUI, KC_LALT, KC_LCTL, MO(OMARCHY), KC_SPC, KC_ENT, MO(MEDIA), MO(FN), MO(SYMB), KC_RSFT
    ),
    [MEDIA] = LAYOUT(
        KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC,
        KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LSFT,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LCTL,KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LGUI, KC_LALT, KC_LCTL, MO(OMARCHY), KC_SPC, KC_ENT, MO(MEDIA), MO(FN), MO(SYMB), KC_RSFT
    ),
    [OMARCHY] = LAYOUT(
        KC_ESC, omarchy_keys[0],  omarchy_keys[1],  omarchy_keys[2],  omarchy_keys[3],  omarchy_keys[4],  KC_BSPC,
        KC_TAB, omarchy_keys[5],  omarchy_keys[6],  omarchy_keys[7],  omarchy_keys[8],  omarchy_keys[9],  omarchy_keys[10],
        KC_LSFT,omarchy_keys[11], omarchy_keys[12], omarchy_keys[13], omarchy_keys[14], omarchy_keys[15], omarchy_keys[16],
        KC_LCTL,omarchy_keys[17], omarchy_keys[18], omarchy_keys[19], omarchy_keys[20], KC_NO, KC_NO,
        KC_LGUI, KC_LALT, KC_LCTL, MO(OMARCHY), KC_SPC, KC_ENT, MO(MEDIA), MO(FN), MO(SYMB), KC_RSFT
    )
};
// Энкодеры
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // левый энкодер - громкость
        // change volume by 2 steps per notch
        if (clockwise) {
            tap_code(KC_VOLU);
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { // правый энкодер - NUM
        // scroll through pages
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

// Нажатие энкодеров
bool encoder_is_pressed(uint8_t index) {
    if (index == 0) { // левый энкодер
        tap_code(KC_MUTE);
        is_muted = !is_muted;
        return true;
    } else if (index == 1) { // правый энкодер
        // Momentary NUM: press -> layer_on, release -> layer_off
        if (!right_enc_pressed) {
            layer_on(NUM);
            right_enc_pressed = true;
        } else {
            layer_off(NUM);
            right_enc_pressed = false;
        }
        return true;
    }
    return false;
}

// Доп. слои через зажатие кнопки
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle OMARCHY workspace keycodes (send GUI+number or GUI+Shift+number)
    if (!record->event.pressed) return true;
    switch (keycode) {
        case OM_WSP1:  register_code(KC_LGUI); tap_code(KC_1);  unregister_code(KC_LGUI); return false;
        case OM_WSP2:  register_code(KC_LGUI); tap_code(KC_2);  unregister_code(KC_LGUI); return false;
        case OM_WSP3:  register_code(KC_LGUI); tap_code(KC_3);  unregister_code(KC_LGUI); return false;
        case OM_WSP4:  register_code(KC_LGUI); tap_code(KC_4);  unregister_code(KC_LGUI); return false;
        case OM_WSP5:  register_code(KC_LGUI); tap_code(KC_5);  unregister_code(KC_LGUI); return false;
        case OM_WSP6:  register_code(KC_LGUI); tap_code(KC_6);  unregister_code(KC_LGUI); return false;
        case OM_WSP7:  register_code(KC_LGUI); tap_code(KC_7);  unregister_code(KC_LGUI); return false;
        case OM_WSP8:  register_code(KC_LGUI); tap_code(KC_8);  unregister_code(KC_LGUI); return false;
        case OM_WSP9:  register_code(KC_LGUI); tap_code(KC_9);  unregister_code(KC_LGUI); return false;
        case OM_WSP10: register_code(KC_LGUI); tap_code(KC_0);  unregister_code(KC_LGUI); return false;

        case OM_WSP11: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_1); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP12: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_2); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP13: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_3); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP14: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_4); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP15: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_5); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP16: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_6); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP17: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_7); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP18: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_8); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP19: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_9); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;
        case OM_WSP20: register_code(KC_LGUI); register_code(KC_LSFT); tap_code(KC_0); unregister_code(KC_LSFT); unregister_code(KC_LGUI); return false;

        case OM_WSP_DEFAULT: tap_code(KC_BSPC); return false;
    }
    return true;
}
