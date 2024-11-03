#include "button1_event.h"
#include "main.h"
#include "buzzer.h"
#include "CLCD.h"
#include "easyMacros.h"

extern System_Mode system_mode;
extern Clock_Config clock_config;
extern Button button1;
extern CLCD clcd;

// Start
void button1_start()
{
	button1.hold_milisecond = 0;
	button1.state = MEASURE_HOLD;
	button1_measure_hold();
}

void button1_measure_hold()
{
	// measure
	if(button1.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)
	{
		                                               button1.state = SHORT_HOLD;
	}
	else if(button1.hold_milisecond <= MID_LONG_BOUNDARY_TIME)
	{
		if(button1.state == SHORT_HOLD)                button1.state = SHORT_MID_THRESHOLD;
		else if(button1.state == SHORT_MID_THRESHOLD)  button1.state = MID_HOLD;
	}
	else
	{
		if(button1.state == MID_HOLD)                  button1.state = MID_LONG_THRESHOLD;
		else if(button1.state == MID_LONG_THRESHOLD)   button1.state = LONG_HOLD;
	}

	// acting
	switch(system_mode)
	{
	case CLOCK_CONFIG:
		clock_config.wait_milisecond = 0;
		break;
	}

	switch(button1.state)
	{
	case SHORT_HOLD:          button1_short_hold();          break;
	case SHORT_MID_THRESHOLD: button1_short_mid_threshold(); break;
	case MID_HOLD:            button1_mid_hold();            break;
	case MID_LONG_THRESHOLD:  button1_mid_long_threshold();  break;
	case LONG_HOLD:           button1_long_hold();           break;
	}
}

void button1_short_hold()
{

}

void button1_short_mid_threshold()
{
	beep_buzzer(30, MID);

	switch(system_mode)
	{
	case CLOCK:
		system_mode = CLOCK_CONFIG;
		init_clock_config();
		break;

	case CLOCK_CONFIG:
		system_mode = CLOCK;
		break;
	}
}

void button1_mid_hold()
{

}

void button1_mid_long_threshold()
{
	beep_buzzer(30, HIGH);
}

void button1_long_hold()
{

}

// Finish
void button1_finish()
{
	button1_measure_release();
}

void button1_measure_release()
{
	// measure
	if(button1.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)       button1.state = SHORT_RELEASE;
	else if(button1.hold_milisecond <= MID_LONG_BOUNDARY_TIME)   button1.state = MID_RELEASE;
	else                                                         button1.state = LONG_RELEASE;

	// acting
	switch(button1.state)
	{
	case SHORT_RELEASE: button1_short_release(); break;
	case MID_RELEASE:   button1_mid_release();   break;
	case LONG_RELEASE:  button1_long_release();  break;
	}
}

void button1_short_release()
{
	switch(system_mode)
	{
	case CLOCK: break;
	}
}

void button1_mid_release()
{

}

void button1_long_release()
{

}
