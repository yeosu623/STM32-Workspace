#include "button3_event.h"
#include "main.h"
#include "buzzer.h"
#include "CLCD.h"
#include "easyMacros.h"
#include "clock_config.h"
#include "alarm_config.h"
#include "alarm.h"
#include "stopwatch.h"

extern System system;
extern System_Mode previous_system_mode;
extern Clock clock;
extern Clock_Config clock_config;
extern Alarm_Config alarm_config;
extern Button button3;
extern CLCD clcd;
extern Alarm alarm;
extern Stopwatch stopwatch;
extern Lap lap;
extern void change_system_mode(System_Mode);

// Start
void button3_start()
{
	beep_buzzer(30, LOW);

	button3.hold_milisecond = 0;
	button3.state = MEASURE_HOLD;
	button3_measure_hold();

	switch(system.mode)
	{
	case CLOCK_CONFIG:
		clock_config_increase_once();
		break;
	case ALARM_CONFIG:
		alarm_config_increase_once();
		break;
	case ALARM_TRIGGER:
		change_system_mode(previous_system_mode);
		break;
	case STOPWATCH:
		if(stopwatch.state == PAUSED)
		{
			clear_stopwatch();
			lap.state = CLEAR;
			stopwatch.state = STOPPED;
		}
		else if(stopwatch.state == RUNNING)
			lap.state = SAVE;

		break;
	}
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
		if(button3.state == SHORT_HOLD)                button3.state = SHORT_MID_THRESHOLD;
		else if(button3.state == SHORT_MID_THRESHOLD)  button3.state = MID_HOLD;
	}
	else
	{
		if(button3.state == MID_HOLD)                  button3.state = MID_LONG_THRESHOLD;
		else if(button3.state == MID_LONG_THRESHOLD)   button3.state = LONG_HOLD;
	}

	// acting
	system.wait_milisecond = 0;

	switch(button3.state)
	{
	case SHORT_HOLD:          button3_short_hold();          break;
	case SHORT_MID_THRESHOLD: button3_short_mid_threshold(); break;
	case MID_HOLD:            button3_mid_hold();            break;
	case MID_LONG_THRESHOLD:  button3_mid_long_threshold();  break;
	case LONG_HOLD:           button3_long_hold();           break;
	}
}

void button3_short_hold()
{

}

void button3_short_mid_threshold()
{
	beep_buzzer(30, MID);
}

void button3_mid_hold()
{
	button3.repeating_milisecond++;

	switch(system.mode)
	{
	case CLOCK_CONFIG: clock_config_increase_continuous_150ms(); break;
	case ALARM_CONFIG: alarm_config_increase_continuous_150ms(); break;
	}
}

void button3_mid_long_threshold()
{
	beep_buzzer(30, HIGH);
}

void button3_long_hold()
{
	button3.repeating_milisecond++;

	switch(system.mode)
	{
	case CLOCK_CONFIG: clock_config_increase_continuous_20ms(); break;
	case ALARM_CONFIG: alarm_config_increase_continuous_20ms(); break;
	}
}

// Finish
void button3_finish()
{
	if(alarm.closing) alarm.closing = FALSE;
	else button3_measure_release();
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
	switch(system.mode)
	{
	case CLOCK:
		clock.mode_24h = !clock.mode_24h;
		break;
	case ALARM:
		alarm_enable_disable();
		break;
	}
}

void button3_mid_release()
{

}

void button3_long_release()
{

}
