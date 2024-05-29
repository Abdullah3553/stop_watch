#include"types.h"
#include"clock.h"
#include<util/delay.h>
#include<avr/io.h>

time g_clock;

uint8 init_time(time* clock)
{
	clock->hours = 0;
	clock->minutes = 0;
	clock->seconds = 0;
	return SUCCESS; /*Could be ignored*/
}

static sint8 get_digit(uint8 number,uint8 digit )
{

	if(digit == RIGHT_DIGIT)
	{
        number = number % 10; 	/*Select the Least significant digit only*/
		return (sint8)number;
	}
	else if(digit == LEFT_DIGIT)
	{
		number = number % 100; 	/*To Select the last 2 digits only */
		number = number / 10;	/*To remove the ones digit*/
		return (sint8)number;
	}

	return DIGIT_ERROR;	/*digit was not RIGHT_DIGIT or LEFT_DIGIT*/
}

uint8 display_clock(time* clock)
{
	/*Display the digits on the 6 7-segments */

	/*enable the tens digit in the hours*/
	PORTA = ( PORTA & 0xc0 ) | ( 0b00000001 );
	/*Display the tens digit on the enabled 7-segment*/
	PORTC = ( PORTC & 0xf0 )
			| ( 0x0f & ( (uint8) get_digit(clock->hours, LEFT_DIGIT) ) );
	_delay_ms(1);

	/*enable the ones digit in the hours*/
	PORTA = ( PORTA & 0xc0 ) | ( 0b00000010 );
	/*Display the tens digit on the enabled 7-segment*/
	PORTC = ( PORTC & 0xf0 )
			| ( 0x0f & ( (uint8) get_digit(clock->hours, RIGHT_DIGIT) ) );
	_delay_ms(1);

	/*enable the tens digit in the minutes*/
	PORTA = ( PORTA & 0xc0 ) | ( 0b00000100 );
	/*Display the tens digit on the enabled 7-segment*/
	PORTC = ( PORTC & 0xf0 ) |
			( 0x0f & ( (uint8) get_digit(clock->minutes, LEFT_DIGIT) ) );
	_delay_ms(1);

	/*enable the ones digit in the minutes*/
	PORTA = ( PORTA & 0xc0 ) | ( 0b00001000 );
	/*Display the tens digit on the enabled 7-segment*/
	PORTC = ( PORTC & 0xf0 )
			| ( 0x0f & ( (uint8) get_digit(clock->minutes, RIGHT_DIGIT) ) );
	_delay_ms(1);

	/*enable the tens digit in the seconds*/
	PORTA = ( PORTA & 0xc0 ) | ( 0b00010000 );
	/*Display the tens digit on the enabled 7-segment*/
	PORTC = ( PORTC & 0xf0 )
			| ( 0x0f & ( (uint8) get_digit(clock->seconds, LEFT_DIGIT) ) );
	_delay_ms(1);

	/*enable the ones digit in the seconds*/
	PORTA = ( PORTA & 0xc0 ) | ( 0b00100000 );
	/*Display the tens digit on the enabled 7-segment*/
	PORTC = ( PORTC & 0xf0 )
			| ( 0x0f & ( (uint8) get_digit(clock->seconds, RIGHT_DIGIT) ) );
	_delay_ms(1);

	return SUCCESS;
}

static uint8 advance_hour(time* clock)
{
	/*this function will increment 1 on the clock hours and handle the clock logic*/
	if(clock->hours == 99)
	{
		clock->hours = 0;
	}
	else
	{
		clock->hours++;
	}
	return SUCCESS;
}


static uint8 advance_minute(time* clock)
{
	/*this function will increment 1 on the clock minutes and handle the clock logic*/
	if(clock->minutes == 59)
	{
		clock->minutes = 0;
		advance_hour(clock);
	}
	else
	{
		clock->minutes++;
	}
	return SUCCESS;
}

uint8 advance_second(time* clock)
{
	/*this function will increment 1 on the clock and handle the clock logic*/
	if(clock->seconds == 59)
	{
		clock->seconds = 0;
		advance_minute(clock);
	}
	else
	{
		clock->seconds++;
	}
	return SUCCESS;
}
