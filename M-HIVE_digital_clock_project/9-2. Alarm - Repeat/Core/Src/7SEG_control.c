#include "main.h"
#include "7SEG.h"

extern Clock clock;

void show_7seg()
{
	// control flashing points.
	if(clock.time.milisecond < 500) clock.point = ON;
	else clock.point = OFF;

	// display on 7-SEG
	_7SEG_SetNumber(DGT1, clock.time.second / 10, OFF);
	_7SEG_SetNumber(DGT2, clock.time.second % 10, clock.point);
}
