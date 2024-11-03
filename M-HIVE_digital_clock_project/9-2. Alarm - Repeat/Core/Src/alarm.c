#include "main.h"
#include "alarm.h"
#include "buzzer.h"
#include "7SEG.h"
#include "CLCD.h"
#include "easyMacros.h"
#include "7SEG_control.h"

extern System system;
extern Clock clock;
extern Buzzer buzzer;
extern Alarm alarm;
extern CLCD clcd;
extern void change_system_mode(System_Mode);

void init_alarm()
{
	system.wait_milisecond = 0;
	alarm.select = 0;
}

void show_alarm()
{
	// display on CLCD
	sprintf(clcd.str1, "ALARM #%d %s %s",
			alarm.select + 1,
			alarm.activate[alarm.select] ? "ON " : "OFF",
			alarm.repeat[alarm.select] ? "RPT" : "ONC");
	sprintf(clcd.str2, "        %s %02d:%02d",
			clock.mode_24h ? "  " : (alarm.hour[alarm.select] < 12 ? "AM" : "PM"),
			clock.mode_24h ? alarm.hour[alarm.select] : alarm.hour[alarm.select] % 12,
			alarm.minute[alarm.select]);

	CLCD_Puts(0, 0, clcd.str1);
	CLCD_Puts(0, 1, clcd.str2);

	// display on 7-seg
	show_7seg();

	// if idle time over 30 seconds, return to clock mode
	if(system.wait_milisecond > 30000) system.mode = CLOCK;
}

void next_alarm()
{
	if(alarm.select + 1 == 5) alarm.select = 0;
	else alarm.select++;
}

void alarm_enable_disable()
{
	alarm.activate[alarm.select] = !alarm.activate[alarm.select];
}

void check_alarm()
{
	for(int i = 0; i < 5; i++)
		if(alarm.activate[i] &&
		   alarm.hour[i] == clock.time.hour &&
		   alarm.minute[i] == clock.time.minute)
		{
			change_system_mode(ALARM_TRIGGER);

			if(alarm.repeat[i] == OFF) alarm.activate[i] = OFF;
			break;
		}
}

void trigger_alarm()
{
	// toggle buzzer and LED on every 30ms.
	if((system.wait_milisecond / 30) % 2)
	{
		buzzer_start(HIGH);
		ALL_LED_ON();
	}
	else
	{
		buzzer_stop();
		ALL_LED_OFF();
	}

	// toggle CLCD on every 500ms.
	if((clock.time.milisecond / 500) % 2)
	{
		CLCD_Puts(0, 0, "ALARM TRIGGERED!");
	}
	else
	{
		CLCD_Clear();
	}

	// display 7-seg.
	show_7seg();

	// exit when press any button.
	if(CHECK_SW1_PRESSING() ||
	   CHECK_SW2_PRESSING() ||
	   CHECK_SW3_PRESSING() ||
	   CHECK_SW4_PRESSING())
	{
		alarm.closing = TRUE;
		ALL_LED_OFF();
	}
}
