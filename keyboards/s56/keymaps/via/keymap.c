#include QMK_KEYBOARD_H

#include "keymap_japanese.h"
#include "s56.h"

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
#define L1_G   LT(1,JP_G)
#define L1_H   LT(1,JP_H)
#define L2_B   LT(2,JP_B)
#define L3_V   LT(3,JP_V)
#define C_TAB  CTL_T(KC_TAB) // tab -> ctrl
#define S_ESC  SFT_T(KC_ESC) // esc -> shift
#define A_MHEN ALT_T(JP_MHEN)
#define G_HENK GUI_T(JP_HENK)
#define L2_HOME LT(2,KC_HOME)
#define L3_END  LT(3,KC_END)
// MT(MOD_LALT,JP_MHEN) MT(MOD_LSFT,JP_BSPC) MT(MOD_LGUI,JP_HENK)
#define C_INS C(KC_INS)
#define S_INS S(KC_INS)
#define CG_LEFT C(G(KC_LEFT))
#define CG_RGHT C(G(KC_RGHT))
#define GUI_TAB G(KC_TAB)

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
/*
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        JP_Q,    JP_W,    JP_E,    JP_R,    JP_T,                      JP_Y,    JP_U,    JP_I,    JP_O,    JP_P,
        JP_A,    JP_S,    JP_D,    JP_F,    L1_G,                      JP_H,    JP_J,    JP_K,    JP_L,    JP_SCLN,
        JP_Z,    JP_X,    JP_C,    L3_V,    L2_B,                      JP_N,    JP_M,    JP_COMM, JP_DOT,  JP_SLSH,
                 L2_HOME, A_MHEN,  C_TAB,   S_ESC,   KC_SPC,  KC_BSPC, KC_ENT,  KC_DEL,  G_HENK, L3_END
    ),
    [1] = LAYOUT(
        JP_EXLM, JP_DQUO, JP_HASH, JP_DLR,  JP_PERC,                   JP_AMPR, JP_QUOT, JP_LPRN, JP_RPRN, JP_AT,
        JP_CIRC, JP_PLUS, JP_MINS, JP_ASTR, XXXXXXX,                   XXXXXXX, JP_DQUO, JP_LBRC, JP_RBRC, JP_COLN,
        JP_TILD, JP_UNDS, JP_EQL,  JP_PIPE, XXXXXXX,                   XXXXXXX, JP_GRV,  JP_LCBR, JP_RCBR, JP_BSLS,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  KC_BSPC, KC_ENT,  KC_DEL,  KC_END,  XXXXXXX
    ),
    [2] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_PSLS, KC_P7,   KC_P8,   KC_P9,  KC_PMNS,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                    KC_PAST, KC_P4,   KC_P5,   KC_P5,  KC_PPLS,
        KC_F11,  KC_F12,  C_INS,   S_INS,   XXXXXXX,                   KC_P0,   KC_P1,   KC_P2,   KC_P3,  KC_PENT,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SPC,  KC_BSPC, KC_ENT,  KC_DEL,  KC_PDOT, XXXXXXX
    ),
    [3] = LAYOUT(
        KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, XXXXXXX,                   CG_LEFT, GUI_TAB, XXXXXXX, CG_RGHT, XXXXXXX, 
        KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_BTN3,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
                 XXXXXXX, XXXXXXX, DB_TOGG, EE_CLR,  QK_BOOT, QK_BOOT, EE_CLR,  DB_TOGG, XXXXXXX, XXXXXXX
    ),
    [4] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
    )
};
*/



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
	KC_ESC  , KC_Q     , KC_W     , KC_E     , KC_R        , KC_T       , SL(KC_EQL)  , KC_EQL      ,   /**/   SL(KC_8)    , SL(KC_9)    , KC_Y     , KC_U       , KC_I       , KC_O      , KC_P       , KC_LBRC    ,
	KC_TAB  , KC_A     , KC_S     , KC_D     , KC_F        , KC_G       , KC_MINS     , SL(KC_MINS) ,   /**/   KC_RBRC     , KC_NUHS     , KC_H     , KC_J       , KC_K       , KC_L      , KC_SCLN    , KC_QUOT    ,
	KC_LALT , KC_Z     , KC_X     , KC_C     , KC_V        , KC_B       , SL(KC_JYEN) , GUI_INS     ,   /**/   SL(KC_RBRC) , SL(KC_NUHS) , KC_N     , KC_M       , KC_COMM    , KC_DOT    , KC_SLSH    , KC_RO      ,
	                                           CT(KC_HOME) , MO(1)      , ST(KC_SPC)  , KC_MHEN     ,   /**/   KC_HENK     , KC_BSPC     , KC_ENT   , L2(KC_END)
	)       ,
	[1] = LAYOUT(
	_______ , KC_1     , KC_2     , KC_3     , KC_4        , KC_5       , _______     , _______     ,   /**/   _______     , _______     , KC_6     , KC_7       , KC_8       , KC_9      , KC_0       , XXXXXXX    ,
	_______ , SL(KC_1) , SL(KC_2) , SL(KC_3) , SL(KC_4)    , SL(KC_5)   , _______     , _______     ,   /**/   _______     , _______     , SL(KC_6) , SL(KC_7)   , SL(KC_8)   , SL(KC_9)  , XXXXXXX    , XXXXXXX    ,
	_______ , XXXXXXX  , XXXXXXX  , XXXXXXX  , SL(KC_INS)  , CL(KC_INS) , _______     , _______     ,   /**/   _______     , _______     , XXXXXXX  , XXXXXXX    , _______    , _______   , _______    , XXXXXXX    ,
	                                           _______     , XXXXXXX    , _______     , _______     ,   /**/   _______     , _______     , _______  , _______
	)       ,
	[2] = LAYOUT(
	_______ , KC_F1    , KC_F2    , KC_F3    , KC_F4       , KC_F5      , DEBUG       , EEP_RST     ,   /**/   XXXXXXX     , XXXXXXX     , XXXXXXX  , XXXXXXX    , XXXXXXX    , XXXXXXX   , XXXXXXX    , XXXXXXX    ,
	_______ , KC_F6    , KC_F7    , KC_F8    , KC_F9       , KC_F10     , XXXXXXX     , XXXXXXX     ,   /**/   XXXXXXX     , XXXXXXX     , KC_LEFT  , KC_DOWN    , KC_UP      , KC_RGHT   , XXXXXXX    , XXXXXXX    ,
	_______ , KC_F11   , KC_F12   , XXXXXXX  , XXXXXXX     , XXXXXXX    , XXXXXXX     , RESET       ,   /**/   XXXXXXX     , XXXXXXX     , XXXXXXX  , XXXXXXX    , _______    , _______   , _______    , XXXXXXX    ,
	                                           XXXXXXX     , XXXXXXX    , _______     , _______     ,   /**/   _______     , _______     , _______  , XXXXXXX
	)       ,
	[3] = LAYOUT(
	_______ , S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)     , S(KC_T)    , _______     , _______     ,   /**/   _______     , _______     , S(KC_Y)  , S(KC_U)    , S(KC_I)    , S(KC_O)   , S(KC_P)    , S(KC_LBRC) ,
	_______ , S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)     , S(KC_G)    , _______     , _______     ,   /**/   _______     , _______     , S(KC_H)  , S(KC_J)    , S(KC_K)    , S(KC_L)   , S(KC_SCLN) , S(KC_QUOT) ,
	_______ , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)     , S(KC_B)    , _______     , _______     ,   /**/   _______     , _______     , S(KC_N)  , S(KC_M)    , S(KC_COMM) , S(KC_DOT) , S(KC_SLSH) , S(KC_RO)   ,
	                                           _______     , _______    , XXXXXXX     , _______     ,   /**/   _______     , KC_DEL      , _______  , _______
	)
};
