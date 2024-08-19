#include "main.h"
#include "button_event.h"
#include "CLCD.h"
#include "easyMacros.h"

extern Button button1;
extern CLCD clcd;

void button1_start() {
	button1.hold_milisecond = 0;
	button1.valuecycle_milisecond = 0;
	button1.state = MEASURE_HOLD;
	button1.value++;
}

void button1_show_press_time() {
	sprintf(clcd.str1, "%4d%4d %4d%3d",
			button1.hold_milisecond,
			SHORT_MID_BOUNDARY_TIME,
			MID_LONG_BOUNDARY_TIME,
			button1.value);

	CLCD_Puts(0, 0, clcd.str1);
}

void button1_measure_hold() {
	if(button1.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)       button1.state = SHORT_HOLD;
	else if(button1.hold_milisecond <= MID_LONG_BOUNDARY_TIME)   button1.state = MID_HOLD;
	else                                                         button1.state = LONG_HOLD;

	button1_increase_value_by_hold_state();
}

void button1_increase_value_by_hold_state() {
	if(button1.state == SHORT_HOLD) {
		;
	}
	else if(button1.state == MID_HOLD) {
		button1.valuecycle_milisecond++;
		if(button1.valuecycle_milisecond == MID_HOLD_CYCLE_TIME) {
			button1.valuecycle_milisecond = 0;
			button1.value++;
		}
	}
	else {
		button1.valuecycle_milisecond++;
		if(button1.valuecycle_milisecond == LONG_HOLD_CYCLE_TIME) {
			button1.valuecycle_milisecond = 0;
			button1.value++;
		}
	}
}

void button1_short_hold() {
	button1_show_press_time();

	sprintf(clcd.str2, "SHORT HOLD      ");
	CLCD_Puts(0, 1, clcd.str2);
}

void button1_mid_hold() {
	button1_show_press_time();

	sprintf(clcd.str2, "MID HOLD        ");
	CLCD_Puts(0, 1, clcd.str2);
}

void button1_long_hold() {
	button1_show_press_time();

	sprintf(clcd.str2, "LONG HOLD       ");
	CLCD_Puts(0, 1, clcd.str2);
}

void button1_measure_release() {
	if(button1.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)       button1.state = SHORT_RELEASE;
	else if(button1.hold_milisecond <= MID_LONG_BOUNDARY_TIME)   button1.state = MID_RELEASE;
	else                                                         button1.state = LONG_RELEASE;
}

void button1_short_release() {
	button1_show_press_time();

	sprintf(clcd.str2, "SHORT RELEASE   ");
	CLCD_Puts(0, 1, clcd.str2);

	R_RED_LED_TOGGLE();

	button1.state = NONE;
}

void button1_mid_release() {
	button1_show_press_time();

	sprintf(clcd.str2, "MID RELEASE     ");
	CLCD_Puts(0, 1, clcd.str2);

	R_GREEN_LED_TOGGLE();

	button1.state = NONE;
}

void button1_long_release() {
	button1_show_press_time();

	sprintf(clcd.str2, "LONG RELEASE    ");
	CLCD_Puts(0, 1, clcd.str2);

	R_BLUE_LED_TOGGLE();

	button1.state = NONE;
}
