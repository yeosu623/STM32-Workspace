#include "button2_event.h"
#include "main.h"
#include "buzzer.h"
#include "CLCD.h"
#include "easyMacros.h"
#include "clock_config.h"

extern System_Mode system_mode;
extern Clock_Config clock_config;
extern Buzzer buzzer;
extern Button button2;
extern CLCD clcd;

// Start
void button2_start()
{
	button2.hold_milisecond = 0;
	button2.state = MEASURE_HOLD;
	button2_measure_hold();

	switch(system_mode)
	{
	case CLOCK_CONFIG:
		next_item();
		break;
	}
}

void button2_measure_hold()
{
	// measure
	if(button2.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)
	{
		                                               button2.state = SHORT_HOLD;
	}
	else if(button2.hold_milisecond <= MID_LONG_BOUNDARY_TIME)
	{
		if(button2.state == SHORT_HOLD)                button2.state = SHORT_MID_THRESHOLD;
		else if(button2.state == SHORT_MID_THRESHOLD)  button2.state = MID_HOLD;
	}
	else
	{
		if(button2.state == MID_HOLD)                  button2.state = MID_LONG_THRESHOLD;
		else if(button2.state == MID_LONG_THRESHOLD)   button2.state = LONG_HOLD;
	}

	// acting
	switch(system_mode)
	{
	case CLOCK_CONFIG:
		clock_config.wait_milisecond = 0;
		break;
	}

	switch(button2.state)
	{
	case SHORT_HOLD:          button2_short_hold();          break;
	case SHORT_MID_THRESHOLD: button2_short_mid_threshold(); break;
	case MID_HOLD:            button2_mid_hold();            break;
	case MID_LONG_THRESHOLD:  button2_mid_long_threshold();  break;
	case LONG_HOLD:           button2_long_hold();           break;
	}
}

void button2_short_hold()
{

}

void button2_short_mid_threshold()
{
	beep_buzzer(30, MID);
}

void button2_mid_hold()
{

}

void button2_mid_long_threshold()
{
	beep_buzzer(30, HIGH);
}

void button2_long_hold()
{

}

// Finish
void button2_finish()
{
	button2_measure_release();
}

void button2_measure_release()
{
	// measure
	if(button2.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)       button2.state = SHORT_RELEASE;
	else if(button2.hold_milisecond <= MID_LONG_BOUNDARY_TIME)   button2.state = MID_RELEASE;
	else                                                         button2.state = LONG_RELEASE;

	// acting
	switch(button2.state)
	{
	case SHORT_RELEASE: button2_short_release(); break;
	case MID_RELEASE:   button2_mid_release();   break;
	case LONG_RELEASE:  button2_long_release();  break;
	}
}

void button2_short_release()
{
	switch(system_mode)
	{
	case CLOCK: buzzer.config = !buzzer.config; break;
	}
}

void button2_mid_release()
{

}

void button2_long_release()
{

}
