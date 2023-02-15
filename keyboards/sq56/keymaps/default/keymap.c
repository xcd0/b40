#include QMK_KEYBOARD_H

#include "keymap_japanese.h"
#include "sq56.h"

// tap dance {{{1
enum custom_keycodes {
  MACRO1= SAFE_RANGE,
  MACRO2,
  MACRO3,
  MACRO4,
};

// 必要な数のタップダンス状態のタイプを定義します
typedef enum { // {{{2
	TD_NONE,
	TD_UNKNOWN, 
	TD_TAP1,   // ただのタップ                   モールスで言えば.
	TD_HOLD1,  // ただのホールド                 モールスで言えば_
	TD_TAP2,   // ダブルタップ                   モールスで言えば..
	TD_HOLD2,  // ダブルタップしてからホールド   モールスで言えば._
	TD_TAP2_,  // ダブルタップにならない遅い2回のタップ
	TD_TAP3,   // トリプルタップ                 モールスで言えば...
	TD_HOLD3,  // トリプルタップしてからホールド モールスで言えば.._
	TD_TAP3_,  // トリプルタップにならない遅い3回のタップ
	TD_TAP4,   // ....
	TD_HOLD4,  // ..._
	TD_TAP4_,
	TD_TAP5,   // .....
	TD_HOLD5,  // ...._
	TD_TAP5_,
} td_state_t; // }}}2

typedef struct { bool is_press_action; td_state_t state; } td_tap_t;

 // カスタムタップダンスキー。他のタップダンスキーはこの列挙型に追加します
// T_HM   HOME_MHEN,    // . HOME _ HOME .. 無変換
// T_EH   END_HENK,     // . END  _ END  .. 変換
// T_ESL1 ESC_SFT__L1,  // . ESC  _ LSFT .. ESCx2      ._ L1 ... L1固定
// T_TCL2 TAB_CTL__L2,  // . TAB  _ LCTL .. TABx2      ._ L2 ... L2固定
// T_A_L3 LALT_L3       // . LALT _ LALT .. L3(トグル) ._ L3(押している間)
// T_G_L2 LGUI_L2       // . LGUI _ LGUI .. L2(トグル) ._ L2(押している間)
enum {
	HOME_MHEN,
	END_HENK,
	ESC_SFT__L1,
	TAB_CTL__L2,
	LGUI_L2,
	LALT_L3,
};

// 現在のタップダンスの状態を決定します
td_state_t cur_dance(qk_tap_dance_state_t *state) { // {{{2
	switch( state->count ){
		case  1: if( state->interrupted || !state->pressed ) { return TD_TAP1; }else{ return TD_HOLD1; }
		case  2:
			if( state->interrupted ) { return TD_TAP2; }
			if( state->pressed ) { return TD_HOLD2; }
			return TD_TAP2_; // ダブルタップにならない程度に遅い２回連打
		case  3:
			if( state->interrupted ) { return TD_TAP3; }
			if( state->pressed ) { return TD_HOLD3; }
			return TD_TAP3_;
		case  4:
			if( state->interrupted ) { return TD_TAP4; }
			if( state->pressed ) { return TD_HOLD4; }
			return TD_TAP4_;
		case  5:
			if( state->interrupted ) { return TD_TAP5; }
			if( state->pressed ) { return TD_HOLD5; }
			return TD_TAP5_;
		default: return TD_UNKNOWN;
	}
} // }}}2

// 個々のタップダンスキーごとにtd_tap_t構造体のインスタンス生成 {{{2
static td_tap_t hm_state   = { .is_press_action = true, .state = TD_NONE };
static td_tap_t eh_state   = { .is_press_action = true, .state = TD_NONE };
static td_tap_t esl1_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t tcl2_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t al3_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t gl2_state = { .is_press_action = true, .state = TD_NONE };
// }}}2

// T_HM   HOME_MHEN,    // . HOME _ HOME .. 無変換 {{{2
void hm_finished(qk_tap_dance_state_t *state, void *user_data) {
	hm_state.state = cur_dance(state);
	switch (hm_state.state) {
		case TD_TAP1:  register_code(KC_HOME); break;
		case TD_HOLD1: register_code(KC_HOME); break;
		case TD_TAP2:  register_code(KC_MHEN); break;
		case TD_TAP2_: tap_code(KC_MHEN); register_code(KC_MHEN); break;
		default: break;
	}
}
void hm_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (hm_state.state) {
		case TD_TAP1:  unregister_code(KC_HOME); break;
		case TD_HOLD1: unregister_code(KC_HOME); break;
		case TD_TAP2:  unregister_code(KC_MHEN); break;
		case TD_TAP2_: unregister_code(KC_MHEN); break;
		default: break;
	}
	hm_state.state = TD_NONE;
}
// }}}2

// T_EH   END_HENK,     // . END  _ END  .. 変換 {{{2
void eh_finished(qk_tap_dance_state_t *state, void *user_data) {
	eh_state.state = cur_dance(state);
	switch (eh_state.state) {
		case TD_TAP1:  register_code(KC_END); break;
		case TD_HOLD1: register_code(KC_END); break;
		case TD_TAP2:  register_code(KC_HENK); break;
		case TD_TAP2_: tap_code(KC_HENK); register_code(KC_HENK); break;
		default: break;
	}
}
void eh_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (eh_state.state) {
		case TD_TAP1:  unregister_code(KC_END); break;
		case TD_HOLD1: unregister_code(KC_END); break;
		case TD_TAP2:  unregister_code(KC_HENK); break;
		case TD_TAP2_: unregister_code(KC_HENK); break;
		default: break;
	}
	eh_state.state = TD_NONE;
}
// }}}2

// esl1 ESC_SFT__L2,   // . ESC _ LSFT .. ESCx2 ._ L2 ... L3固定 {{{2
void esl1_finished(qk_tap_dance_state_t *state, void *user_data) {
	esl1_state.state = cur_dance(state);
	switch (esl1_state.state) {
		case TD_TAP1:  register_code(KC_ESC); break;
		case TD_HOLD1: register_code(KC_LSFT); break;
		case TD_TAP2:  tap_code(KC_ESC); register_code(KC_ESC); break;
		case TD_TAP2_: tap_code(KC_ESC); register_code(KC_ESC); break;
		case TD_TAP3: // ... でレイヤー固定
		case TD_HOLD2: // ._の時ホールドしている間はレイヤーを維持する
			if( !layer_state_is(1) ){ layer_on(1); } // 解除する
		default: break;
	}
}
void esl1_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (esl1_state.state) {
		case TD_TAP1:  unregister_code(KC_ESC); break;
		case TD_HOLD1: unregister_code(KC_LSFT); break;
		case TD_TAP2:  unregister_code(KC_ESC); break;
		case TD_TAP2_: unregister_code(KC_ESC); break;
		case TD_TAP3: break; // 解除しない 
		case TD_HOLD2: // ._の時ホールドしている間はレイヤーを維持する
			if( layer_state_is(1) ){ layer_off(1); } // 解除する
			break;
		default: break;
	}
	esl1_state.state = TD_NONE;
}
// }}}2

// tcl2 TAB_CTL__L3,   // . TAB _ LCTL .. TABx2 ._ L3 ... L3固定 {{{2
void tcl2_finished(qk_tap_dance_state_t *state, void *user_data) {
	tcl2_state.state = cur_dance(state);
	switch (tcl2_state.state) {
		case TD_TAP1:  register_code(KC_TAB); break;
		case TD_HOLD1: register_code(KC_LCTL); break;
		case TD_TAP2:  tap_code(KC_TAB); register_code(KC_TAB); break;
		case TD_TAP2_: tap_code(KC_TAB); register_code(KC_TAB); break;
		case TD_TAP3: // ... でレイヤー固定
		case TD_HOLD2:
			if( !layer_state_is(2) ) { layer_on(2); }// ._の時ホールドしている間はレイヤーを維持する
			break;
		default: break;
	}
}
void tcl2_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (tcl2_state.state) {
		case TD_HOLD1: unregister_code(KC_LCTL); break;
		case TD_TAP1:
		case TD_TAP2:
		case TD_TAP2_: unregister_code(KC_TAB); break;
		case TD_TAP3: break; // 解除しない 
		case TD_HOLD2: // ._の時ホールドしている間はレイヤーを維持する
			if( layer_state_is(2) ){ layer_off(2); } // 解除する
			break;
		default: break;
	}
	tcl2_state.state = TD_NONE;
}
// }}}2

// T_G_L2 LGUI_L2       // . LGUI _ LGUI .. L2(トグル) ._ L2(押している間) // {{{2
void gl2_finished(qk_tap_dance_state_t *state, void *user_data) {
	gl2_state.state = cur_dance(state);
	switch (gl2_state.state) {
		case TD_TAP1: 
			if( layer_state_is(2) ){ layer_off(2); } // レイヤー固定した時の解除
			else{ register_code(KC_LGUI); }
			break;
		case TD_HOLD1: register_code(KC_LGUI); break;
		case TD_TAP2: // .. でレイヤー固定
		case TD_HOLD2: // ._の時ホールドしている間はレイヤーを維持する
			if( ! layer_state_is(2) ){ layer_on(2); }
			break;
		default: break;
	}
}
void gl2_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (gl2_state.state) {
		case TD_TAP1: if( layer_state_is(2) ){ break; } // レイヤー固定した時の解除
		case TD_HOLD1: unregister_code(KC_LGUI); break;
		case TD_TAP2: break; // .. でレイヤー固定 レイヤーを解除しない
		case TD_HOLD2: // ._の時ホールドしている間はレイヤーを維持する
			if( layer_state_is(2) ){ layer_off(2); } // 解除する
			break;
		default: break;
	}
	gl2_state.state = TD_NONE;
}
// }}}2

// T_A_L3 LALT_L3       // . LALT _ LALT .. L3(トグル) ._ L3(押している間) {{{2
void al3_finished(qk_tap_dance_state_t *state, void *user_data) {
	al3_state.state = cur_dance(state);
	switch (al3_state.state) {
		case TD_TAP1: 
			if( layer_state_is(3) ){ layer_off(3); } // レイヤー固定した時の解除
			else{ register_code(KC_LALT); }
			break;
		case TD_HOLD1: register_code(KC_LALT); break;
		case TD_TAP2: // .. でレイヤー固定
		case TD_HOLD2: // ._の時ホールドしている間はレイヤーを維持する
			if( ! layer_state_is(3) ){ layer_on(3); }
			break;
		default: break;
	}
}
void al3_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (al3_state.state) {
		case TD_TAP1: if( layer_state_is(3) ){ break; } // レイヤー固定した時の解除
		case TD_HOLD1: unregister_code(KC_LALT); break;
		case TD_TAP2: break; // .. でレイヤー固定 レイヤーを解除しない
		case TD_HOLD2: // ._の時ホールドしている間はレイヤーを維持する
			if( layer_state_is(3) ){ layer_off(3); } // 解除する
			break;
		default: break;
	}
	al3_state.state = TD_NONE;
}
// }}}2

// タップダンスキーを機能に関連付けます
qk_tap_dance_action_t tap_dance_actions[] = {
	[HOME_MHEN]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, hm_finished, hm_reset),
	[END_HENK]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, eh_finished, eh_reset),
	[ESC_SFT__L1]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esl1_finished, esl1_reset),
	[TAB_CTL__L2]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tcl2_finished, tcl2_reset),
	[LGUI_L2]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gl2_finished, gl2_reset),
	[LALT_L3]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL, al3_finished, al3_reset),
}; //}}}

// マクロ{{{
// MT(MOD_LALT,JP_MHEN) MT(MOD_LSFT,JP_BSPC) MT(MOD_LGUI,JP_HENK)
#define CG_LEFT C(G(KC_LEFT))
#define CG_RGHT C(G(KC_RGHT))
#define GUI_TAB G(KC_TAB)

#define A_HOME ALT_T(KC_HOME)
#define A_MHEN ALT_T(KC_MHEN)
#define G_END  GUI_T(KC_END)
#define G_HENK GUI_T(KC_HENK)
#define C_TAB  CTL_T(KC_TAB)
#define C_ESC  CTL_T(KC_ESC)
#define C_INS   C(KC_INS)
#define S_INS   S(KC_INS)
#define S_SPC  SFT_T(KC_SPC)
#define S_ESC  SFT_T(KC_ESC) // esc -> shift
#define L1_G   LT(1,JP_G)
#define L1_H   LT(1,JP_H)
#define L1_SPC LT(1,KC_SPC)
#define L1_MHEN LT(1,KC_MHEN)
#define L2_HENK LT(2,KC_HENK)
#define L2_HOME LT(2,KC_HOME)
#define L2_B   LT(2,JP_B)
#define L2_SCLN   LT(2, JP_SCLN)
#define L3_COLN   LT(3, JP_COLN)
#define L3_V   LT(3,JP_V)
#define L3_END  LT(3,KC_END)
#define L4_C   LT(4,JP_C)
#define L4_B   LT(4,JP_B)
#define L4_DEL LT(4,KC_DEL)
#define L5_V   LT(5,JP_V)

#define T_HM   TD(HOME_MHEN)
#define T_EH   TD(END_HENK)
#define T_ESL1 TD(ESC_SFT__L1)
#define T_TCL2 TD(TAB_CTL__L2)
#define T_G_L2 TD(LGUI_L2) // . LGUI _ LGUI .. L4(トグル) ._ L4(押している間)
#define T_A_L3 TD(LALT_L3) // . LALT _ LALT .. L3(トグル) ._ L3(押している間)

// }}}

// キーマップ
// T_ESL1 ESC_SFT__L1, // . ESC  _ LSFT .. ESCx2  ._ L1 ... L1固定
// T_TCL2 TAB_CTL__L2, // . TAB  _ LCTL .. TABx2  ._ L2 ... L2固定
// T_HM   HOME_MHEN,   // . HOME        .. 無変換
// T_EH   END_HENK,    // . END         .. 変換
// T_G_L2 LGUI_L2      // . LGUI _ LGUI .. L4固定 ._ L2(押している間)
// T_A_L3 LALT_L3      // . LALT _ LALT .. L3固定 ._ L2(押している間)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  JP_1,    JP_2,    JP_3,    JP_4,    JP_5,                        JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS,
        KC_TAB,  JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,                        JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,    JP_AT,
        KC_LCTL, JP_A,    JP_S,    JP_D,    JP_F,    JP_G,    KC_LSFT,   KC_LSFT, JP_H,    JP_J,    JP_K,    JP_L,    L2_SCLN, L3_COLN,
        KC_LSFT, JP_Z,    JP_X,    JP_C,    L3_V,    L2_B,    KC_SPC,    KC_SPC,  JP_N,    JP_M,    JP_COMM, JP_DOT,  JP_SLSH, JP_BSLS,
                          A_MHEN,  KC_LCTL, KC_LSFT, L1_SPC,                      KC_BSPC, KC_ENT,  L4_DEL,  G_HENK,

                                            KC_WH_U,                                     KC_WH_U, 
                                S(KC_WH_U), KC_WH_D, S(KC_WH_D),             S(KC_WH_U), KC_WH_D, S(KC_WH_D) 
    ),
    [1] = LAYOUT(
        KC_ESC,  JP_1,    JP_2,    JP_3,    JP_4,    JP_5,                        JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS,
        KC_TAB,  JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC,                     JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_CIRC, _______,
        KC_LCTL, JP_QUES, JP_PLUS, JP_ASTR, JP_MINS, JP_UNDS, XXXXXXX,   XXXXXXX, JP_PIPE, JP_DQUO, JP_LBRC, JP_RBRC, XXXXXXX, _______,
        KC_LSFT, KC_HOME, XXXXXXX, XXXXXXX, JP_EQL,  KC_END,  XXXXXXX,   XXXXXXX, JP_TILD, JP_GRV,  JP_LCBR, JP_RCBR, JP_BSLS, JP_UNDS,
                          KC_MHEN, KC_LCTL, KC_LSFT, KC_SPC,                      KC_BSPC, KC_ENT,  KC_DEL,  KC_HENK,

                                            KC_WH_U,                                     KC_WH_U, 
                                S(KC_WH_U), KC_WH_D, S(KC_WH_D),             S(KC_WH_U), KC_WH_D, S(KC_WH_D) 
    ),
    [2] = LAYOUT(
        KC_ESC,  JP_1,    JP_2,    JP_3,    JP_4,    JP_5,                        JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS,
        KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_PSLS, KC_P7,   KC_P8,   KC_P9,  KC_PMNS, XXXXXXX,
        KC_LCTL, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,   XXXXXXX, KC_PAST, KC_P4,   KC_P5,   KC_P6,  KC_PPLS, XXXXXXX,
        KC_LSFT, KC_F11,  KC_F12,  C_INS,   S_INS,   XXXXXXX, XXXXXXX,   XXXXXXX, KC_P0,   KC_P1,   KC_P2,   KC_P3,  KC_PENT, RESET,
                          KC_MHEN, KC_LCTL, KC_LSFT, KC_SPC,                      KC_BSPC, KC_ENT,  KC_DEL,  KC_HENK,

                                            KC_WH_U,                                     KC_WH_U, 
                                S(KC_WH_U), KC_WH_D, S(KC_WH_D),             S(KC_WH_U), KC_WH_D, S(KC_WH_D) 
    ),
    [3] = LAYOUT(
        KC_ESC,  JP_1,    JP_2,    JP_3,    JP_4,    JP_5,                        JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    JP_MINS,
        KC_TAB,  KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, XXXXXXX,                     CG_LEFT, GUI_TAB, XXXXXXX, CG_RGHT, KC_PGUP, KC_PSCR,
        KC_LCTL, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_BTN3, XXXXXXX,   XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGDN, KC_INS,
        KC_LSFT, QK_BOOT, XXXXXXX, DF(5),   XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,
                          KC_MHEN, KC_LCTL, KC_LSFT, KC_SPC,                      KC_BSPC, KC_ENT,  KC_DEL,  KC_HENK,

                                            KC_WH_U,                                     KC_WH_U, 
                                S(KC_WH_U), KC_WH_D, S(KC_WH_D),             S(KC_WH_U), KC_WH_D, S(KC_WH_D) 
    ),
    [4] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, JP_1,    JP_2,    JP_3,    JP_4,    JP_5,    XXXXXXX,   XXXXXXX,   JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

                                            KC_WH_U,                                     KC_WH_U, 
                                S(KC_WH_U), KC_WH_D, S(KC_WH_D),             S(KC_WH_U), KC_WH_D, S(KC_WH_D) 
    ),
    // for chrome
    [5] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_F5,   RCS(KC_T), C(KC_PGUP), C(KC_PGDN),                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, C(KC_A), C(KC_S), C(KC_W), A(KC_LEFT), A(KC_RGHT),   KC_SPC, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), XXXXXXX,         KC_SPC, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          XXXXXXX, XXXXXXX, KC_SPC,  KC_ENT,                            DF(0),   XXXXXXX, XXXXXXX, XXXXXXX,

                                            KC_WH_U,                                     KC_WH_U, 
                                S(KC_WH_U), KC_WH_D, S(KC_WH_D),             S(KC_WH_U), KC_WH_D, S(KC_WH_D) 
    )
};


bool encoder_update_user(uint8_t index, bool clockwise) {
	{ // via対応
		keypos_t key;
		// 以下の表のようにkeyを設定する
		// index  clockwise     row col     LAYERマクロ内での識別子
		//   0      true    ->  5  0       ENC1U
		//   0      false   ->  5  1       ENC1D
		//   1      true    ->  5  2       ENC2U
		//   1      false   ->  5  3       ENC2D
		//   2      true    ->  11 0       ENC3U
		//   2      false   ->  11 1       ENC3D
		//   3      true    ->  11 2       ENC4U
		//   3      false   ->  11 3       ENC4D
		key.row = index < 2 ? 5 : 6;
		if( index == 0 || index == 2 ){ key.col = clockwise ? 0 : 1; }
		else if( index == 1 || index == 3 ){ key.col = clockwise ? 2 : 3; }
		else {
			// エンコーダのindexがおかしいとき (indexはエンコーダの数しかないはず)
			key.row = 4; // NOP
		}

		//bool     encoder_layer_locked = false;
		//if (get_highest_layer(layer_state) < _FN) {
		//	layer_on(encoder_lock_layer);
		//	encoder_layer_locked = true;
		//}
		action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
		action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});
		//if (encoder_layer_locked) {
		//	layer_off(encoder_lock_layer);
		//}

		return false;
	}
}

