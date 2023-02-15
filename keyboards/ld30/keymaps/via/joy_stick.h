
#include "joystick.h"
#include "analog.h"
#include "print.h"
#include <math.h>

#undef MIN
#undef MAX
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

////joystick config
//joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
//    [0] = JOYSTICK_AXIS_IN(F7, 900, 575, 285),
//    [1] = JOYSTICK_AXIS_IN(F6, 900, 575, 285)
//};

/* Joystick + Encoder fix */
/*
void keyboard_post_init_kb(void) {
	if (is_keyboard_master()) {
		writePinLow(JOYSTICK_X_PIN);
		writePinLow(JOYSTICK_Y_PIN);
	}
}
*/

/* Joystick axes settings */
///*
joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
	[0] = JOYSTICK_AXIS_IN(JOYSTICK_X_PIN, 268, 514, 813),
	//[0] = JOYSTICK_AXIS_IN(JOYSTICK_X_PIN, 813, 514, 268),
	//[1] = JOYSTICK_AXIS_IN(JOYSTICK_Y_PIN, 865, 519, 260)
	[1] = JOYSTICK_AXIS_IN(JOYSTICK_Y_PIN, 260, 519, 865)
	//[0] = JOYSTICK_AXIS_IN(JOYSTICK_X_PIN, 813, 514, 268),
	//[1] = JOYSTICK_AXIS_IN(JOYSTICK_Y_PIN, 260, 519, 865)
	//[0] = JOYSTICK_AXIS_IN(JOYSTICK_Y_PIN, 260, 519, 865),
	//[1] = JOYSTICK_AXIS_IN(JOYSTICK_X_PIN, 813, 514, 268)
};
//*/

/*
void joystick_task(){
	const long _xc = 488 - 10;
	const long _yc = 484 + 9;
	const long _xm = _xc - 130, _xM = 800 - _xc;
	const long _ym = _yc - 180, _yM = 860 - _yc;
	long x = analogReadPin(F7);
	long y = analogReadPin(F6);
	x = x - _xc;
	y = y - _yc;

	// 軸毎の調整
	if( x > 0 ) x = x * 200 / _xM;
	else        x = x * 200 / _xm;
	if( y > 0 ) y = y * 200 / _yM;
	else        y = y * 200 / _ym;
	x = x < -127 ? -127 : x > 127 ? 127 : x;
	y = y < -127 ? -127 : y > 127 ? 127 : y;

	joystick_status.axes[0] = -1 * x;
	joystick_status.axes[1] = -1 * y;

	//dprintf( "(%d, %d)\n", joystick_status.axes[0], joystick_status.axes[1] );

	//joystick_axes[0] = JOYSTICK_AXIS_IN(F7, 900, 575, 285);
	//joystick_axes[1] = JOYSTICK_AXIS_IN(F6, 900, 575, 285);

	joystick_status.status |= JS_UPDATED;
	//send_joystick_packet(&joystick_status);
}
*/
