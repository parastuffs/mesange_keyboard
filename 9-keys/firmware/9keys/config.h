#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0000 // OU
#define MANUFACTURER    Mesange keyboard
#define PRODUCT         9keys

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
