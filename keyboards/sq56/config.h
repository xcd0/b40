// Copyright 2023 xcd0 (@xcd0)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define NO_ACTION_ONESHOT
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define MATRIX_COL 6
#define MATRIX_ROWS 12

#define SPLIT_HAND_PIN D1 // 左右を決定するためにピンを読み込みます。ピンが high の場合、それが左側です。low であれば、その半分側が右側であると決定されます。
//#define MASTER_RIGHT
//#define MASTER_LEFT
//#define SPLIT_USB_DETECT // スタートアップの挙動を変更して、マスタ/スレーブの決定時にアクティブな USB 接続を検出します。このオプションがタイムアウトになった場合、その片側はスレーブと見なされます。

// タップダンス
#define TAPPING_TERM 500 //#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define FORCE_NKRO

//#define SERIAL_DEBUG
#define SOFT_SERIAL_PIN D2

// encoder
#define ENCODERS_PAD_A { B5, E6 }
#define ENCODERS_PAD_B { B4, D7 }

#define ENCODERS_PAD_A_RIGHT { B5, E6 }
#define ENCODERS_PAD_B_RIGHT { B4, D7 }

// via
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

