#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xB5B5
#define PRODUCT_ID 0xB5B5
#define DEVICE_VER 0x0001
#define MANUFACTURER Mesange_keyboard
#define PRODUCT NineKeys
#define DESCRIPTION test keyboard

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* row pins */
#define ROW_A  C6
#define ROW_B  D7
#define ROW_C  E6

/* columns 0 - 16 */
#define SHR_LATCH D4 /* SRCLK */
#define SHR_CLOCK D0 /* RCLK */
#define SHR_DATA  D1 /* SER */
#define SHR_COLS { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }

#define PIN_CAPS_LOCK B4
#define PIN_NUM_LOCK  B5

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
