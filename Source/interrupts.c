#include"types.h"
#include"timer.h"
#include"interrupts.h"
#include"clock.h"
#include<avr/io.h>
#include<avr/interrupt.h>


extern time g_clock;

void INT0_config(void)
{
	DDRD &= ~(1 << RESET);	/*RESET button pin*/
	PORTD |= (1 << RESET);	/*internal pull-up resistor for RESET button*/

	MCUCR &= ~(1 << ISC00);	/*INT0 on falling edge */
	MCUCR |= (1 << 	ISC01); /*INT0 on falling edge */
	GICR |= (1 << INT0); 	/*Enable INT0*/

	SREG |= (1 << SREG_I );/*Enable i-bit for global interrupt enable */

}

void INT1_config(void)
{
	DDRD &= ~(1 << PAUSE);	/*PAUSE button pin*/
							/*External pull-down resistor for PAUSE button*/

	MCUCR |= (1 << 	ISC10) 	/*INT1 on raising edge */
			| (1 << ISC11); /*INT1 on raising edge */
	GICR |= (1 << INT1); 	/*Enable INT1*/

	SREG |= (1 << SREG_I );/*Enable i-bit for global interrupt enable */

}

void INT2_config(void)
{
	DDRB &= ~(1 << RESUME) ;/*resume button*/
	PORTB |= (1 << RESUME); /*internal pull-up resistor for RESUME button*/

	MCUCSR &= ~(1 <<ISC2); 	/*INT2 on falling edge */
	GICR |= (1 << INT2); 	/*Enable INT2*/

	SREG |= (1 << SREG_I );/*Enable i-bit for global interrupt enable */

}


ISR(INT0_vect)
{
	/*Should reset the clock*/
	init_time(&g_clock); /*Reset the 7-segments*/

	TIMER1_reset();
}

ISR(INT1_vect)
{
	TIMER1_pause();
}

ISR(INT2_vect)
{
	TIMER1_resume();
}
