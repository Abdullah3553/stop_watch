#include<avr/io.h>
#include<avr/interrupt.h>
#include"types.h"
#include"clock.h"
uint8 TIMER1_t = 0;
extern time g_clock;

void TIMER1_ctc_config(void)
{
	TCNT1 = 0; /*intial value */
	OCR1A = 977; /*compare value for 1 second */
	TIMSK |= (1 << OCIE1A); /*interrupt enable bit for compare with OCR1A */
	SREG |= (1 << SREG_I );/*Enable i-bit for global interrupt enable */

	/*
	 * 1Mhz F_CPU
	 * prescaler -> 1024
	 * WGM10 and WGM11 = 0 -> ctc mode
	 * FOC1A =1, FOC1B= 0 -> force ctc mode with OCR1A
	 *
	 * */
	TCCR1A = (1 << FOC1A);
	/*
	 * CS11 = 1 -> prescaler = 1024
	 * CS10 = 1 -> prescaler = 1024
	 * WGM12 = 1 -> ctc mode
	 * WGM13 = 0 -> ctc mode
	 * */
	TCCR1B = ( 1 << CS12 ) | (1 << CS10) | ( 1 << WGM12);
	/*
	 * with this setup, each increment will be 1.024 ms.
	 *  so to get 1 second, you need to count to 977
	 * */
}

void TIMER1_resume(void)
{
	TIMSK |= (1 << OCIE1A); /*TIMER1 Interrupt enable bit*/

	SREG |= (1 << SREG_I );/*Enable i-bit for global interrupt enable */

	/*This set the clock to the timer so the timer will start*/
	TCCR1B = ( 1 << CS12 ) | (1 << CS10) | ( 1 << WGM12);
}

void TIMER1_pause(void)
{
	TIMSK &= ~(1 << OCIE1A); /*TIMER1 Interrupt enable bit*/
	TCCR1B = 0; /*No clock input*/
}

void TIMER1_reset(void)
{
	/*We can do more stuff here like changing the compare value for the timer*/
	TCNT1 = 0; /*reset value */
}


ISR(TIMER1_COMPA_vect)
{
	TIMER1_t++;
	if(TIMER1_t == 1)
	{
		/*A second passed*/
		TIMER1_t = 0;
		advance_second(&g_clock);
	}
}
