/* Copyright 2022 xcd0
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
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
//enum custom_keycodes { };

#define L1(key) LT(1,key)
#define L2(key) LT(2,key)
#define L3(key) LT(3,key)
#define L4(key) LT(4,key)
#define L5(key) LT(5,key)
#define L6(key) LT(6,key)
#define CT(key) LCTL_T(key)
#define ST(key) LSFT_T(key)
#define GT(key) LGUI_T(key)
#define SL(key) LSFT(key)
#define CL(key) LCTL(key)
#define L1_MHEN L(1,KC_MHEN)
#define L2_HENK L(2,KC_HENK)
#define L3_HENK L(3,KC_HENK)
#define CT_HOME CT(KC_HOME)
#define GUI_INS GT(KC_INS)

	// KC_GRV , KC_LBRC     , 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
	KC_ESC  , KC_Q     , KC_W     , KC_E     , KC_R        , KC_T       , SL(KC_EQL)  , KC_EQL      , SL(KC_8)    , SL(KC_9)    , KC_Y     , KC_U       , KC_I       , KC_O      , KC_P       , KC_LBRC    ,
	KC_TAB  , KC_A     , KC_S     , KC_D     , KC_F        , KC_G       , KC_MINS     , SL(KC_MINS) , KC_RBRC     , KC_NUHS     , KC_H     , KC_J       , KC_K       , KC_L      , KC_SCLN    , KC_QUOT    ,
	KC_LALT , KC_Z     , KC_X     , KC_C     , KC_V        , KC_B       , SL(KC_JYEN) , GUI_INS     , SL(KC_RBRC) , SL(KC_NUHS) , KC_N     , KC_M       , KC_COMM    , KC_DOT    , KC_SLSH    , KC_RO      ,
	XXXXXXX , XXXXXXX  , XXXXXXX  , XXXXXXX  , CT(KC_HOME) , MO(1)      , ST(KC_SPC)  , KC_MHEN     , KC_HENK     , KC_BSPC     , KC_ENT   , L2(KC_END) , XXXXXXX    , XXXXXXX   , XXXXXXX    , XXXXXXX
	)       ,
	[1] = LAYOUT(
	_______ , KC_1     , KC_2     , KC_3     , KC_4        , KC_5       , _______     , _______     , _______     , _______     , KC_6     , KC_7       , KC_8       , KC_9      , KC_0       , XXXXXXX    ,
	_______ , SL(KC_1) , SL(KC_2) , SL(KC_3) , SL(KC_4)    , SL(KC_5)   , _______     , _______     , _______     , _______     , SL(KC_6) , SL(KC_7)   , SL(KC_8)   , SL(KC_9)  , XXXXXXX    , XXXXXXX    ,
	_______ , XXXXXXX  , XXXXXXX  , XXXXXXX  , SL(KC_INS)  , CL(KC_INS) , _______     , _______     , _______     , _______     , XXXXXXX  , XXXXXXX    , _______    , _______   , _______    , XXXXXXX    ,
	XXXXXXX , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______     , XXXXXXX    , _______     , _______     , _______     , _______     , _______  , _______    , XXXXXXX    , XXXXXXX   , XXXXXXX    , XXXXXXX
	)       ,
	[2] = LAYOUT(
	_______ , KC_F1    , KC_F2    , KC_F3    , KC_F4       , KC_F5      , DEBUG       , EEP_RST     , XXXXXXX     , XXXXXXX     , XXXXXXX  , XXXXXXX    , XXXXXXX    , XXXXXXX   , XXXXXXX    , XXXXXXX    ,
	_______ , KC_F6    , KC_F7    , KC_F8    , KC_F9       , KC_F10     , XXXXXXX     , XXXXXXX     , XXXXXXX     , XXXXXXX     , KC_LEFT  , KC_DOWN    , KC_UP      , KC_RGHT   , XXXXXXX    , XXXXXXX    ,
	_______ , KC_F11   , KC_F12   , XXXXXXX  , XXXXXXX     , XXXXXXX    , XXXXXXX     , RESET       , XXXXXXX     , XXXXXXX     , XXXXXXX  , XXXXXXX    , _______    , _______   , _______    , XXXXXXX    ,
	XXXXXXX , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX     , XXXXXXX    , _______     , _______     , _______     , _______     , _______  , XXXXXXX    , XXXXXXX    , XXXXXXX   , XXXXXXX    , XXXXXXX
	)       ,
	[3] = LAYOUT(
	_______ , S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)     , S(KC_T)    , _______     , _______     , _______     , _______     , S(KC_Y)  , S(KC_U)    , S(KC_I)    , S(KC_O)   , S(KC_P)    , S(KC_LBRC) ,
	_______ , S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)     , S(KC_G)    , _______     , _______     , _______     , _______     , S(KC_H)  , S(KC_J)    , S(KC_K)    , S(KC_L)   , S(KC_SCLN) , S(KC_QUOT) ,
	_______ , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)     , S(KC_B)    , _______     , _______     , _______     , _______     , S(KC_N)  , S(KC_M)    , S(KC_COMM) , S(KC_DOT) , S(KC_SLSH) , S(KC_RO)   ,
	XXXXXXX , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______     , _______    , XXXXXXX     , _______     , _______     , KC_DEL      , _______  , _______    , XXXXXXX    , XXXXXXX   , XXXXXXX    , XXXXXXX
	)
};
