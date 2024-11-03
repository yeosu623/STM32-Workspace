#include "button2_event.h"
#include "main.h"
#include "buzzer.h"
#include "CLCD.h"
#include "easyMacros.h"
#include "clock_config.h"
#include "alarm_config.h"
#include "alarm.h"

extern System system;
extern System_Mode previous_system_mode;
extern Clock_Config clock_config;
extern Alarm_Config alarm_config;
extern Buzzer buzzer;
extern Button button2;
extern CLCD clcd;
extern Alarm alarm;
extern void change_system_mode(System_Mode);

// Start
void button2_start()
{
	beep_buzzer(30, LOW);

	button2.hold_milisecond = 0;
	button2.state = MEASURE_HOLD;
	button2_measure_hold();

	switch(system.mode)
	{
	case CLOCK_CONFIG:
		clock_config_next_item();
		break;
	case ALARM_CONFIG:
		alarm_config_next_item();
		break;
	case ALARM_TRIGGER:
		change_system_mode(previous_system_mode);
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
	system.wait_milisecond = 0;

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
	if(alarm.closing) alarm.closing = FALSE;
	else button2_measure_release();
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
	switch(system.mode)
	{
	case CLOCK:
		buzzer.config = !buzzer.config;
		break;
	case ALARM:
		next_alarm();
		break;
	}
}

void button2_mid_release()
{

}

void button2_long_release()
{

}
