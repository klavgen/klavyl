#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1EE7
#define DEVICE_VER      0x0001
#define MANUFACTURER    Klavgen
#define PRODUCT         Klavyl

// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { D4, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6 }

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

#define SOFT_SERIAL_PIN D0
