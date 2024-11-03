#include "button1_event.h"
#include "main.h"
#include "buzzer.h"
#include "CLCD.h"
#include "clock_config.h"
#include "alarm_config.h"
#include "stopwatch.h"
#include "easyMacros.h"

extern System system;
extern System_Mode previous_system_mode;
extern Clock_Config clock_config;
extern Alarm_Config alarm_config;
extern Button button1;
extern CLCD clcd;
extern Alarm alarm;
extern Stopwatch stopwatch;
extern Lap lap;
extern void change_system_mode(System_Mode);

// Start
void button1_start()
{
	beep_buzzer(30, LOW);

	button1.hold_milisecond = 0;
	button1.state = MEASURE_HOLD;
	button1_measure_hold();

	switch(system.mode)
	{
	case ALARM_TRIGGER:
		change_system_mode(previous_system_mode);
		break;
	}
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
	system.wait_milisecond = 0;

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

	switch(system.mode)
	{
	case CLOCK:
		change_system_mode(CLOCK_CONFIG);
		init_clock_config();
		break;

	case CLOCK_CONFIG:
		change_system_mode(CLOCK);
		break;

	case ALARM:
		change_system_mode(ALARM_CONFIG);
		init_alarm_config();
		break;

	case ALARM_CONFIG:
		change_system_mode(ALARM);
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
	if(alarm.closing) alarm.closing = FALSE;
	else button1_measure_release();
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
	switch(system.mode)
	{
	case CLOCK:
		init_alarm();
		change_system_mode(ALARM);
		break;
	case ALARM:
		init_stopwatch();
		change_system_mode(STOPWATCH);

		lap.state = INIT;
		break;
	case STOPWATCH:
		init_clock();
		change_system_mode(CLOCK);
		break;
	}
}

void button1_mid_release()
{

}

void button1_long_release()
{

}
