#include "../../macrodeck.h" /* This should be QMK_KEYBOARD_H, but evaluates to nothing for some reason. */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x4(
        KC_A, KC_B, KC_C, KC_D,
        KC_E, KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K, KC_L,
        KC_M, KC_N, KC_O, KC_P,
        KC_Q, KC_R, KC_S, KC_T
    )
};
