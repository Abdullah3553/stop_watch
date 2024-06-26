#define F_CPU 1000000UL

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include"types.h"
#include"clock.h"
#include"timer.h"
#include"interrupts.h"

extern time g_clock; /*Global clock*/

int main(void)
{
	init_time(&g_clock); 	/*Set the clock to zero */

	DDRA |= 0x3f; 	/*Enable Pins for all 6 7-segments */
	PORTA &= 0xc0;	/*All enable Pins are OFF*/

	DDRC |= 0x0f; 	/*4 pins for 7-segment decoder digit */
	PORTC &= 0xf0; 	/*Set the decoder digit to 0*/

	INT0_config();
	INT1_config();
	INT2_config();

	TIMER1_ctc_config(); /*Compare mode with TIMER1 that counts seconds*/

	while(1)
	{
		display_clock(&g_clock);
	}/*While(1) end*/


}
