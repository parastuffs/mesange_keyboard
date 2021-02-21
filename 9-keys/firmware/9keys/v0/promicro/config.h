#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID      0x0162
#define DEVICE_VER      0x0001

/* key matrix pins */
#define MATRIX_ROW_PINS { D1, D0, D4 }
#define MATRIX_COL_PINS { C6, D7, E6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Encoder pins */
#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTION 4
