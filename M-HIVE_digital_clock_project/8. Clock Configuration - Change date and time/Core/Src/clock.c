#include "main.h"
#include "buzzer.h"
#include "7SEG.h"
#include "CLCD.h"

extern Clock clock;
extern Buzzer buzzer;
extern CLCD clcd;

void init_clock()
{
	clock_convert_time_format();
	check_leap_year();
}

void show_clock()
{
	// control flashing points.
	if(clock.time.milisecond < 500) clock.point = ON;
	else clock.point = OFF;

	// display on CLCD
	sprintf(clcd.str1, "%s  %4d.%02d.%02d",
			clock.leap_year ? "LEAP" : "    ",
			clock.time.year,
			clock.time.month,
			clock.time.day);
	sprintf(clcd.str2, "BZ %s  %s %02d%c%02d",
			buzzer.config ? "ON " : "OFF",
			clock.mode_24h ? "  " : (clock.time.hour < 12 ? "AM" : "PM"),
			clock.mode_24h ? clock.time.hour : clock.time.hour % 12,
			clock.point ? ':' : ' ',
			clock.time.minute);

	CLCD_Puts(0, 0, clcd.str1);
	CLCD_Puts(0, 1, clcd.str2);

	// display on 7-SEG
	_7SEG_SetNumber(DGT1, clock.time.second / 10, OFF);
	_7SEG_SetNumber(DGT2, clock.time.second % 10, clock.point);
}

void clock_convert_time_format()
{
	if(clock.time.milisecond == 1000)
	{
		clock.time.milisecond = 0;
		clock.time.second++;
	}
	if(clock.time.second == 60)
	{
		clock.time.second = 0;
		clock.time.minute++;
	}
	if(clock.time.minute == 60)
	{
		clock.time.minute = 0;
		clock.time.hour++;

		beep_buzzer(30, MID);
	}
	if(clock.time.hour == 24)
	{
		clock.time.hour = 0;
		clock.time.day++;

		beep_buzzer(30, HIGH);
	}
	if(check_day_reach_end())
	{
		clock.time.day = 1;
		clock.time.month++;
	}
	if(clock.time.month == 13)
	{
		clock.time.month = 1;
		clock.time.year++;

		check_leap_year();
	}
}

int check_day_reach_end()
{
	switch(clock.time.month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if(clock.time.day > 31) return TRUE;
		else return FALSE;

	case 4: case 6: case 9: case 11:
		if(clock.time.day > 30) return TRUE;
		else return FALSE;

	case 2:
		if(clock.time.day > 28 && !clock.leap_year) return TRUE;
		else if(clock.time.day > 29 && clock.leap_year) return TRUE;
		else return FALSE;

	default:
		return FALSE;
	}
}

void check_leap_year() {
	     if(!(clock.time.year % 4) && !(clock.time.year % 100) && !(clock.time.year % 400)) clock.leap_year = TRUE;
	else if(!(clock.time.year % 4) && !(clock.time.year % 100))                             clock.leap_year = FALSE;
	else if(!(clock.time.year % 4))                                                         clock.leap_year = TRUE;
	else                                                                                    clock.leap_year = FALSE;
}

void set_max_day() {
	switch(clock.time.month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		clock.time.day = 31;
		break;

	case 4: case 6: case 9: case 11:
		clock.time.day = 30;
		break;

	case 2:
		if(clock.leap_year) clock.time.day = 29;
		else                clock.time.day = 28;
		break;
	}
}
