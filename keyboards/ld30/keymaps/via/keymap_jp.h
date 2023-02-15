/* Copyright 2016 h-youhei
 * Copyright 2021 xcd0
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * JP106-layout (Japanese Standard)
 *
 * For more information, see
 * http://www2d.biglobe.ne.jp/~msyk/keyboard/layout/usbkeycode.html
 * note: This website is written in Japanese.
 */

// add keycode
// Copyright 2020 xcd0

#ifndef KEYMAP_JP_H
#define KEYMAP_JP_H

#include "keymap.h"

#define JP_ZHTG KC_GRV  // hankaku/zenkaku|kanzi
#define JP_YEN  KC_INT3 // yen, |
#define JP_CIRC KC_EQL  // ^, ~
#define JP_AT   KC_LBRC // @, `
#define JP_LBRC KC_RBRC // [, {
#define JP_COLN KC_QUOT // :, *
#define JP_RBRC KC_NUHS // ], }
#define JP_BSLS KC_INT1 // \, _
#define JP_BKSL KC_INT1 // \, _
#define JP_MHEN KC_INT5 // muhenkan
#define JP_HENK KC_INT4 // henkan
#define JP_KANA KC_INT2 // katakana/hiragana|ro-mazi

#define JP_MKANA KC_LANG1 //kana on MacOSX
#define JP_MEISU KC_LANG2 //eisu on MacOSX

//Aliases for shifted symbols
#define JP_DQT  LSFT(KC_2)    // "
#define JP_QUOT LSFT(KC_7)    // '
#define JP_QT   LSFT(KC_7)      // '
#define JP_BQT  LSFT(JP_AT)   // `
#define JP_AMPR LSFT(KC_6)    // &
#define JP_LPRN LSFT(KC_8)    // (
#define JP_RPRN LSFT(KC_9)    // )
#define JP_EQL  LSFT(KC_MINS) // =
#define JP_TILD LSFT(JP_CIRC) // ~
#define JP_PIPE LSFT(JP_YEN)  // |
#define JP_GRV  LSFT(JP_AT)   // `
#define JP_LCBR LSFT(JP_LBRC) // {
#define JP_PLUS LSFT(KC_SCLN) // +
#define JP_ASTR LSFT(JP_COLN) // *
#define JP_RCBR LSFT(JP_RBRC) // }
#define JP_UNDS LSFT(JP_BSLS) // _

// These symbols are correspond to US101-layout.
#define JP_MINS KC_MINS // -
#define JP_SCLN KC_SCLN // ;
#define JP_COMM KC_COMM // ,
#define JP_DOT  KC_DOT  // .
#define JP_SLSH KC_SLSH // /
// shifted
#define JP_EXLM KC_EXLM // !
#define JP_HASH KC_HASH // #
#define JP_DLR  KC_DLR  // $
#define JP_PERC KC_PERC // %
#define JP_LT   KC_LT   // <
#define JP_GT   KC_GT   // >
#define JP_QUES KC_QUES // ?

#define JP_Q KC_Q
#define JP_W KC_W
#define JP_E KC_E
#define JP_R KC_R
#define JP_T KC_T
#define JP_Y KC_Y
#define JP_U KC_U
#define JP_I KC_I
#define JP_A KC_A
#define JP_S KC_S
#define JP_D KC_D
#define JP_F KC_F
#define JP_G KC_G
#define JP_H KC_H
#define JP_J KC_J
#define JP_K KC_K
#define JP_Z KC_Z
#define JP_X KC_X
#define JP_C KC_C
#define JP_V KC_V
#define JP_B KC_B
#define JP_N KC_N
#define JP_M KC_M
#define JP_O KC_O
#define JP_P KC_P
#define JP_L KC_L

#define JP_1 KC_1
#define JP_2 KC_2
#define JP_3 KC_3
#define JP_4 KC_4
#define JP_5 KC_5
#define JP_6 KC_6
#define JP_7 KC_7
#define JP_8 KC_8
#define JP_9 KC_9
#define JP_0 KC_0

#define JP_F1 KC_F1
#define JP_F2 KC_F2
#define JP_F3 KC_F3
#define JP_F4 KC_F4
#define JP_F5 KC_F5
#define JP_F6 KC_F6
#define JP_F7 KC_F7
#define JP_F8 KC_F8
#define JP_F9 KC_F9
#define JP_F10 KC_F10
#define JP_F11 KC_F11
#define JP_F12 KC_F12
#define JP_F13 KC_F13
#define JP_F14 KC_F14
#define JP_F15 KC_F15
#define JP_F16 KC_F16
#define JP_F17 KC_F17
#define JP_F18 KC_F18
#define JP_F19 KC_F19
#define JP_F20 KC_F20
#define JP_F21 KC_F21
#define JP_F22 KC_F22
#define JP_F23 KC_F23
#define JP_F24 KC_F24

#define JP_BTN1 KC_BTN1
#define JP_BTN2 KC_BTN2
#define JP_BTN3 KC_BTN3
#define JP_WH_U KC_WH_U
#define JP_WH_D KC_WH_D
#define JP_MS_L KC_MS_L
#define JP_MS_U KC_MS_U
#define JP_MS_D KC_MS_D
#define JP_MS_R KC_MS_R

#define JP_LEFT KC_LEFT
#define JP_DOWN KC_DOWN
#define JP_UP   KC_UP
#define JP_RGHT KC_RGHT
#define JP_RIGH KC_RGHT

#define JP_ENT  KC_ENT
#define JP_SPC  KC_SPC
#define JP_BSPC KC_BSPC

#define JP_ESC  KC_ESC
#define JP_TAB  KC_TAB

#define JP_LALT KC_LALT
#define JP_LCTL KC_LCTL
#define JP_LSFT KC_LSFT
#define JP_LGUI KC_LGUI

#define JP_RALT KC_RALT
#define JP_RCTL KC_RCTL
#define JP_RSFT KC_RSFT
#define JP_RGUI KC_RGUI

#define JP_NMLK KC_NLCK
#define JP_NLCK KC_NLCK
#define JP_SCLK KC_SLCK     // scroll lock
#define JP_SLCK KC_SLCK     // scroll lock
#define JP_CPLK KC_CAPSLOCK
#define JP_CAPS KC_CAPSLOCK
#define JP_CLCK KC_CAPSLOCK

#define JP_PSCR KC_PSCR
#define JP_PAUS KC_PAUS
#define JP_HOME KC_HOME
#define JP_END  KC_END
#define JP_INS  KC_INS
#define JP_DEL  KC_DEL
#define JP_PGUP KC_PGUP
#define JP_PGDN KC_PGDN

#define JP_P1 KC_P1
#define JP_P2 KC_P2
#define JP_P3 KC_P3
#define JP_P4 KC_P4
#define JP_P5 KC_P5
#define JP_P6 KC_P6
#define JP_P7 KC_P7
#define JP_P8 KC_P8
#define JP_P9 KC_P9
#define JP_P0 KC_P0

#endif
