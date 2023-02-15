/* Copyright 2021 xcd0
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

#include "joy_stick.h"
#include "keymap_jp.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    // 左手用デバイスとして振る舞うつもり といっても右手も使える
    [0] = LAYOUT(
        JP_ESC,   JP_1,    JP_2,     JP_3,     JP_4,    JP_5,    JP_6, \
        JP_TAB,   JP_Q,    JP_W,     JP_E,     JP_R,    JP_T,    JP_Y,  \
        JP_LCTL,  JP_A,    JP_S,     JP_D,     JP_F,    JP_G,    JP_H,  \
        JP_LSFT,  JP_Z,    JP_X,     JP_C,     JP_V,    JP_B,    JP_N,  \
                                    TT(1),  JP_SPC \
    ),
    [1] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
            XXXXXXX, XXXXXXX, XXXXXXX, JP_UP,   XXXXXXX, XXXXXXX, XXXXXXX, \
            DEBUG,   XXXXXXX, JP_LEFT, JP_DOWN, JP_RGHT, XXXXXXX, XXXXXXX, \
            RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF(2),   \
                                       XXXXXXX, XXXXXXX \
    ),
    [2] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    MO(3),      \
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F5,      XXXXXXX,    XXXXXXX,    \
            XXXXXXX, XXXXXXX, S(KC_2), KC_ENT,  S(C(KC_T)), C(KC_PGUP), C(KC_PGDN), \
            C(KC_Z), C(KC_A), C(KC_C), C(KC_V), C(KC_W),    A(KC_LEFT), A(KC_RGHT), \
                                       XXXXXXX, XXXXXXX \
    ),
    [3] = LAYOUT(
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
            DEBUG,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
            RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DF(0),   \
                                       XXXXXXX, XXXXXXX \
    )
};

void keyboard_post_init_user(void) {
	setPinInputHigh( F5 );
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if( !readPin( F5 ) ) {
		dprint("pushd");
	}
	return true;
}
