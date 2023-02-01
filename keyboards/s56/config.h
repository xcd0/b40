// Copyright 2023 xcd0 (@xcd0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT


#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

// タップダンス
//#define TAPPING_TERM 200
#define TAPPING_TERM 500
#define PERMISSIVE_HOLD
#define FORCE_NKRO

//#define SERIAL_DEBUG

/*
#define VENDOR_ID    0xFF00
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER xcd0
#define PRODUCT      s56

#define MATRIX_ROWS 8
#define MATRIX_COLS 8
#define DIODE_DIRECTION COL2ROW

#define MATRIX_ROW_PINS { D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6 }
#define UNUSED_PINS { D1, D0, D4, C6 }
*/
#define SOFT_SERIAL_PIN D2
