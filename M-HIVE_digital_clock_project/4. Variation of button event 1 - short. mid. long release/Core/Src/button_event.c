#include "main.h"
#include "button_event.h"
#include "CLCD.h"
#include "easyMacros.h"

extern Button button1;
extern CLCD clcd;

void button1_start() {
	button1.milisecond = 0;
	button1.state = PRESS;
}

void button1_show_press_time() {
	sprintf(clcd.str1, "%4d  %4d  %4d",
			button1.milisecond,
			SHORT_MID_BOUNDARY_TIME,
			MID_LONG_BOUNDARY_TIME);

	CLCD_Puts(0, 0, clcd.str1);
}

void button1_measure_release() {
	if(button1.milisecond <= SHORT_MID_BOUNDARY_TIME)       button1.state = SHORT_RELEASE;
	else if(button1.milisecond <= MID_LONG_BOUNDARY_TIME)   button1.state = MID_RELEASE;
	else                                                    button1.state = LONG_RELEASE;
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
