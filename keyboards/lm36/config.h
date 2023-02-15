// Copyright 2023 xcd0 (@xcd0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

//#include "config_common.h"

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

// 何も設定していないと(0,0)をBOOTMAGICキーとしてしまう。
// 総当たりマトリクスを使っているので(0,0)は常にTrueになっている。
// (0,1)を設定して起動時にBOOTMAGICキーが勝手に押されないようにする。
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

// PCB上のBOOTSELボタンを2連打することでリセットできるようにする
// Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
// Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
// Specify a optional status led by GPIO number which blinks when entering the bootloader
//#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17

// タップダンス
#define TAPPING_TERM 200

