/*
Copyright 2021 xcd0

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xF110
#define PRODUCT_ID   0x0001
#define DEVICE_VER   0x0001
#define MANUFACTURER xcd0
#define PRODUCT      ld30

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS { D1, D0, D4, C6, D7 }
#define MATRIX_COL_PINS { B1, B3, B2, B6, B5, B4, E6 }
//#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

//#define SOFT_SERIAL_PIN D0  // or D1, D2, D3, E6

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

//#define FORCE_NKRO

//#define DEBUG_ACTION
//#define NO_DEBUG // dprintが無効になる
//#define NO_PRINT // print xprint uprintが無効になる
//#define USER_PRINT // uprintが有効になる
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#define NO_ACTION_TAPPING
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT

/* Bootmagic Lite key configuration */
//#define BOOTMAGIC_LITE_ROW 0
//#define BOOTMAGIC_LITE_COLUMN 0

#define JOYSTICK_BUTTON_COUNT 0
#define JOYSTICK_AXES_COUNT 2
//#define ANALOG_JOYSTICK_X_AXIS_PIN F7 // A0(F7) にX軸
//#define ANALOG_JOYSTICK_Y_AXIS_PIN F6 // A1(F6) にY軸
#define ANALOG_JOYSTICK_X_AXIS_PIN F6 // A0(F7) にX軸
#define ANALOG_JOYSTICK_Y_AXIS_PIN F7 // A1(F6) にY軸
#define ANALOG_JOYSTICK_CLICK_PIN  F5 // A2(F5) に中央ボタン
#define JOYSTICK_X_PIN ANALOG_JOYSTICK_X_AXIS_PIN
#define JOYSTICK_Y_PIN ANALOG_JOYSTICK_Y_AXIS_PIN

