#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_3x3(
        KC_A, KC_B, KC_C,
        KC_D, KC_E, KC_F,
        KC_G, KC_H, KC_I
    )
};
