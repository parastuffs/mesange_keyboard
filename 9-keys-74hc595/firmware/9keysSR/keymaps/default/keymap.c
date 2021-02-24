#include "../../9keys.h" /* This should be QMK_KEYBOARD_H, but evaluates to nothing for some reason. */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_3x3(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I
    )
};
