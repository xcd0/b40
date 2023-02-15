#include QMK_KEYBOARD_H

#include "keymap_japanese.h"
#include "lm36.h"


// tap dance{{{{
enum custom_keycodes {
  MACRO1= SAFE_RANGE,
  MACRO2,
  MACRO3,
  MACRO4,
};

// 必要な数のタップダンス状態のタイプを定義します
typedef enum {
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
} td_state_t;

typedef struct { bool is_press_action; td_state_t state; } td_tap_t;

 // カスタムタップダンスキー。他のタップダンスキーはこの列挙型に追加します
enum {
	HOME_LALT_MHEN_L3, // . HOME _ LALT .. 無変換 .._ L3
	END_LGUI_HENK_L3, // . END _ LGUI .. 変換 .._ L3
	ESC_SFT__L1,   // . ESC _ LSFT .. ESCx2 ._ L ... L1固定
	TAB_CTL__L2,   // . TAB _ LCTL .. TABx2 ._ L ... L2固定
};

// 現在のタップダンスの状態を決定します
td_state_t cur_dance(qk_tap_dance_state_t *state) { // {{{
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
} // }}}

// 個々のタップダンスキーごとにtd_tap_t構造体のインスタンス生成 {{{
static td_tap_t haml3_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t eghl3_state  = { .is_press_action = true, .state = TD_NONE };
static td_tap_t esl1_state = { .is_press_action = true, .state = TD_NONE };
static td_tap_t tcl2_state = { .is_press_action = true, .state = TD_NONE };
// }}}


// haml3 HOME_LALT_MHEN_L3, // . HOME _ LALT .. 無変換 ._ L3 ... L3 {{{
void haml3_finished(qk_tap_dance_state_t *state, void *user_data) {
	haml3_state.state = cur_dance(state);
	switch (haml3_state.state) {
		case TD_TAP1:  register_code(KC_HOME); break;
		case TD_HOLD1: register_code(KC_LALT); break;
		case TD_TAP2:  register_code(KC_MHEN); break;
		case TD_TAP2_: tap_code(KC_MHEN); register_code(KC_MHEN); break;
		//case TD_TAP3: // ... でレイヤー固定
		case TD_HOLD2:
			if( layer_state_is(3) ) { // ... でレイヤー固定した時の解除
				// レイヤー固定うまく解除できない
				//layer_off(3); break;
			}else{ // ._の時ホールドしている間はレイヤーを維持する
				layer_on(3); break;
			}
		default: break;
	}
}
void haml3_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (haml3_state.state) {
		case TD_TAP1:  unregister_code(KC_HOME); break;
		case TD_HOLD1:  unregister_code(KC_LALT); break;
		case TD_TAP2:  unregister_code(KC_MHEN); break;
		case TD_TAP2_: unregister_code(KC_HENK); break;
		case TD_TAP3:  break; // 解除しない
		// レイヤー固定うまく解除できない
		//case TD_HOLD2: layer_off(3); break;
		default: break;
	}
	haml3_state.state = TD_NONE;
}
// }}}

// eghl3 END_LGUI_HENK_L3, // . END _ LGUI .. 変換 ._ L3 ... L3 {{{
void eghl3_finished(qk_tap_dance_state_t *state, void *user_data) {
	eghl3_state.state = cur_dance(state);
	switch (eghl3_state.state) {
		case TD_TAP1:  register_code(KC_END); break;
		case TD_HOLD1: register_code(KC_LGUI); break;
		case TD_TAP2:  register_code(KC_HENK); break;
		case TD_TAP2_: tap_code(KC_HENK); register_code(KC_HENK); break;
		//case TD_TAP3: // ... でレイヤー固定
		case TD_HOLD2:
			if( layer_state_is(3) ) { // ... でレイヤー固定した時の解除
				// レイヤー固定うまく解除できない
				// layer_off(3); break;
			}else{ // ._の時ホールドしている間はレイヤーを維持する
				layer_on(3); break;
			}
		default: break;
	}
}
void eghl3_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (eghl3_state.state) {
		case TD_TAP1:  unregister_code(KC_END); break;
		case TD_HOLD1: unregister_code(KC_LGUI); break;
		case TD_TAP2:  unregister_code(KC_HENK); break;
		case TD_TAP2_: unregister_code(KC_HENK); break;
		case TD_HOLD2: layer_off(3); break;
		// レイヤー固定うまく解除できない
		//case TD_TAP3:  break; // 解除しない 
		default: break;
	}
	eghl3_state.state = TD_NONE;
}
// }}}

// esl1 ESC_SFT__L2,   // . ESC _ LSFT .. ESCx2 ._ L2 ... L3固定 {{{
void esl1_finished(qk_tap_dance_state_t *state, void *user_data) {
	esl1_state.state = cur_dance(state);
	switch (esl1_state.state) {
		case TD_TAP1:  register_code(KC_ESC); break;
		case TD_HOLD1: register_code(KC_LSFT); break;
		case TD_TAP2:  tap_code(KC_ESC); register_code(KC_ESC); break;
		case TD_TAP2_: tap_code(KC_ESC); register_code(KC_ESC); break;
		case TD_TAP3: // ... でレイヤー固定
		case TD_HOLD2:
			if( layer_state_is(1) ) { // ... でレイヤー固定した時の解除
				layer_off(1); break;
			}else{ // ._の時ホールドしている間はレイヤーを維持する
				layer_on(1); break;
			}
		default: break;
	}
}
void esl1_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (esl1_state.state) {
		case TD_TAP1:  unregister_code(KC_ESC); break;
		case TD_HOLD1: unregister_code(KC_LSFT); break;
		case TD_TAP2:  unregister_code(KC_ESC); break;
		case TD_TAP2_: unregister_code(KC_ESC); break;
		case TD_TAP3:  layer_off(1); break;
		case TD_HOLD2: break; // 解除しない 
		default: break;
	}
	esl1_state.state = TD_NONE;
}
// }}}

// tcl2 TAB_CTL__L3,   // . TAB _ LCTL .. TABx2 ._ L3 ... L3固定 {{{
void tcl2_finished(qk_tap_dance_state_t *state, void *user_data) {
	tcl2_state.state = cur_dance(state);
	switch (tcl2_state.state) {
		case TD_TAP1:  register_code(KC_TAB); break;
		case TD_HOLD1: register_code(KC_LCTL); break;
		case TD_TAP2:  tap_code(KC_TAB); register_code(KC_TAB); break;
		case TD_TAP2_: tap_code(KC_TAB); register_code(KC_TAB); break;
		case TD_TAP3: // ... でレイヤー固定
		case TD_HOLD2:
			if( layer_state_is(2) ) { // ... でレイヤー固定した時の解除
				layer_off(2); break;
			}else{ // ._の時ホールドしている間はレイヤーを維持する
				layer_on(2); break;
			}
		default: break;
	}
}
void tcl2_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (tcl2_state.state) {
		case TD_TAP1:  unregister_code(KC_TAB); break;
		case TD_HOLD1: unregister_code(KC_LCTL); break;
		case TD_TAP2:  unregister_code(KC_TAB); break;
		case TD_TAP2_: unregister_code(KC_TAB); break;
		case TD_TAP3:  layer_off(2); break;
		case TD_HOLD2: break; // 解除しない 
		default: break;
	}
	tcl2_state.state = TD_NONE;
}
// }}}

// タップダンスキーを機能に関連付けます
qk_tap_dance_action_t tap_dance_actions[] = {
	[HOME_LALT_MHEN_L3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, haml3_finished, haml3_reset),
	[END_LGUI_HENK_L3]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, eghl3_finished, eghl3_reset),
	[ESC_SFT__L1]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esl1_finished, esl1_reset),
	[TAB_CTL__L2]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tcl2_finished, tcl2_reset)
};
// //}}}


// マクロ{{{
#define L1_G   LT(1,JP_G)
#define L1_H   LT(1,JP_H)
#define L2_B   LT(2,JP_B)
#define L3_V   LT(3,JP_V)
#define C_TAB  CTL_T(KC_TAB) // tab -> ctrl
#define S_ESC  SFT_T(KC_ESC) // esc -> shift
#define A_MHEN ALT_T(JP_MHEN)
#define G_HENK GUI_T(JP_HENK)
// MT(MOD_LALT,JP_MHEN)
// MT(MOD_LSFT,JP_BSPC)
// MT(MOD_LGUI,JP_HENK)
#define C_INS C(KC_INS)
#define S_INS S(KC_INS)
#define CG_LEFT C(G(KC_LEFT))
#define CG_RGHT C(G(KC_RGHT))
#define GUI_TAB G(KC_TAB)

//#define MT(KC_ESC)
//#define MT(KC_TAB)

#define T_HAML3 TD(HOME_LALT_MHEN_L3)
#define T_EGHL3 TD(END_LGUI_HENK_L3)
#define T_ESL1 TD(ESC_SFT__L1)
#define T_TCL2 TD(TAB_CTL__L2)

// }}}

// キーマップ {{{
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,    JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,
        JP_A,    JP_S,    JP_D,    JP_F,    L1_G,    L1_H,    JP_J,    JP_K,    JP_L,    JP_SCLN,
        JP_Z,    JP_X,    JP_C,    L3_V,    L2_B,    JP_N,    JP_M,    JP_COMM, JP_DOT,  JP_SLSH,
                 T_HAML3, T_TCL2,  T_ESL1,  KC_SPC,  KC_BSPC, KC_ENT,  KC_DEL,  T_EGHL3
    ),
    [1] = LAYOUT(
        JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC, JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_AT,
        JP_COLN, JP_PLUS, JP_MINS, JP_ASTR, _______, _______, JP_DQUO, JP_LBRC, JP_RBRC, JP_COLN,
        JP_TILD, JP_UNDS, JP_EQL,  JP_PIPE, KC_LSFT, XXXXXXX, JP_GRV,  JP_LABK, JP_RABK, JP_BSLS,
                 KC_HOME, KC_TAB,  _______,  KC_SPC,  KC_BSPC, KC_ENT, KC_DEL,  KC_END
    ),
    [2] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_PSLS, KC_P7,   KC_P8,   KC_P9,  KC_PMNS,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PAST, KC_P4,   KC_P5,   KC_P5,  KC_PPLS,
        KC_F11,  KC_F12,  C_INS,   S_INS,   _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,  KC_PENT,
                 KC_HOME, _______, KC_ESC,  _______, _______, _______, _______, KC_PDOT
    ),
    [3] = LAYOUT(
        KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, XXXXXXX, CG_LEFT, GUI_TAB, XXXXXXX, CG_RGHT, XXXXXXX, 
        KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_BTN3, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
                 XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

// }}}

