#include "button4_event.h"
#include "main.h"
#include "buzzer.h"
#include "CLCD.h"
#include "easyMacros.h"
#include "clock_config.h"

extern System system;
extern System_Mode previous_system_mode;
extern Clock_Config clock_config;
extern Button button4;
extern CLCD clcd;
extern Alarm alarm;
extern void change_system_mode(System_Mode);

// Start
void button4_start()
{
	beep_buzzer(30, LOW);

	button4.hold_milisecond = 0;
	button4.state = MEASURE_HOLD;
	button4_measure_hold();

	switch(system.mode)
	{
	case CLOCK_CONFIG:
		decrease_once();
		break;
	case ALARM_TRIGGER:
		change_system_mode(previous_system_mode);
		break;
	}
}

void button4_measure_hold()
{
	// measure
	if(button4.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)
	{
		                                               button4.state = SHORT_HOLD;
	}
	else if(button4.hold_milisecond <= MID_LONG_BOUNDARY_TIME)
	{
		if(button4.state == SHORT_HOLD)                button4.state = SHORT_MID_THRESHOLD;
		else if(button4.state == SHORT_MID_THRESHOLD)  button4.state = MID_HOLD;
	}
	else
	{
		if(button4.state == MID_HOLD)                  button4.state = MID_LONG_THRESHOLD;
		else if(button4.state == MID_LONG_THRESHOLD)   button4.state = LONG_HOLD;
	}

	// acting
	system.wait_milisecond = 0;

	switch(button4.state)
	{
	case SHORT_HOLD:          button4_short_hold();          break;
	case SHORT_MID_THRESHOLD: button4_short_mid_threshold(); break;
	case MID_HOLD:            button4_mid_hold();            break;
	case MID_LONG_THRESHOLD:  button4_mid_long_threshold();  break;
	case LONG_HOLD:           button4_long_hold();           break;
	}
}

void button4_short_hold()
{

}

void button4_short_mid_threshold()
{
	beep_buzzer(30, MID);
}

void button4_mid_hold()
{
	button4.repeating_milisecond++;

	switch(system.mode)
	{
	case CLOCK_CONFIG: decrease_continuous_150ms(); break;
	}
}

void button4_mid_long_threshold()
{
	beep_buzzer(30, HIGH);
}

void button4_long_hold()
{
	button4.repeating_milisecond++;

	switch(system.mode)
	{
	case CLOCK_CONFIG: decrease_continuous_20ms(); break;
	}
}

// Finish
void button4_finish()
{
	if(alarm.closing) alarm.closing = FALSE;
	else button4_measure_release();
}

void button4_measure_release()
{
	// measure
	if(button4.hold_milisecond <= SHORT_MID_BOUNDARY_TIME)       button4.state = SHORT_RELEASE;
	else if(button4.hold_milisecond <= MID_LONG_BOUNDARY_TIME)   button4.state = MID_RELEASE;
	else                                                         button4.state = LONG_RELEASE;

	// acting
	switch(button4.state)
	{
	case SHORT_RELEASE: button4_short_release(); break;
	case MID_RELEASE:   button4_mid_release();   break;
	case LONG_RELEASE:  button4_long_release();  break;
	}
}

void button4_short_release()
{

}

void button4_mid_release()
{

}

void button4_long_release()
{

}
