/*
 * clock.h
 *
 *  Created on: May 10, 2024
 *      Author: Abdullah
 */

#ifndef CLOCK_H_
#define CLOCK_H_


#define RIGHT_DIGIT 0
#define LEFT_DIGIT  1
#define DIGIT_ERROR -1

typedef struct {
	uint8 hours, minutes, seconds;
}time;

uint8 init_time(time*);
static sint8 get_digit(uint8 number,uint8 digit );
uint8 display_clock(time*);
static uint8 advance_hour(time*);
static uint8 advance_minute(time*);
uint8 advance_second(time*);

#endif /* CLOCK_H_ */
