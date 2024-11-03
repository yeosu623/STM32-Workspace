#include "button3_event.h"
#include "main.h"
#include "buzzer.h"
#include "CLCD.h"
#include "easyMacros.h"

extern System_Mode system_mode;
extern Clock clock;
extern Button button3;
extern CLCD clcd;

// Start
void button3_start()
{
	button3.hold_milisecond = 0;
	button3.state = MEASURE_HOLD;
	button3_measure_hold();
}

void button3_measure_hold()
{
	// measure
	if(button3.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)
	{
		                                    button3.state = SHORT_HOLD;
	}
	else if(button3.hold_milisecond <= MID_LONG_BOUNDARY_TIME)
	{
		if(button3.state == SHORT_HOLD)     button3.state = SHORT_MID_THRESHOLD;
		else if(button3.state == MID_HOLD)  button3.state = MID_HOLD;
	}
	else
	{
		if(button3.state == MID_HOLD)       button3.state = MID_LONG_THRESHOLD;
		else if(button3.state == LONG_HOLD) button3.state = LONG_HOLD;
	}

	// acting
	switch(button3.state)
	{
	case SHORT_HOLD:          button3_short_hold(); break;
	case SHORT_MID_THRESHOLD: button3_short_mid_threshold(); break;
	case MID_HOLD:            button3_mid_hold(); break;
	case MID_LONG_THRESHOLD:  button3_mid_long_threshold(); break;
	case LONG_HOLD:           button3_long_hold(); break;
	}
}

void button3_short_hold()
{

}

void button3_short_mid_threshold()
{
	button3.state = MID_HOLD;
}

void button3_mid_hold()
{

}

void button3_mid_long_threshold()
{
	button3.state = LONG_HOLD;
}

void button3_long_hold()
{

}

// Finish
void button3_finish()
{
	button3_measure_release();
}

void button3_measure_release()
{
	// measure
	if(button3.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)       button3.state = SHORT_RELEASE;
	else if(button3.hold_milisecond <= MID_LONG_BOUNDARY_TIME)   button3.state = MID_RELEASE;
	else                                                         button3.state = LONG_RELEASE;

	// acting
	switch(button3.state)
	{
	case SHORT_RELEASE: button3_short_release(); break;
	case MID_RELEASE:   button3_mid_release();   break;
	case LONG_RELEASE:  button3_long_release();  break;
	}
}

void button3_short_release()
{
	switch(system_mode)
	{
	case CLOCK:
		clock.mode_24h = !clock.mode_24h;
	}
}

void button3_mid_release()
{

}

void button3_long_release()
{

}
