/*
 * sos-msg.c
 *
 * Created: 7/7/2024 9:44:38 AM
 * Author : kolke
 */ 
#define F_CPU 8000000L
#define __DELAY_BACKWARD_COMPATIBLE__ /*This Macro makes the delay function accept variables as inputs*/
#include <avr/io.h>
#include <util/delay.h>

//should have used global variables instead of the #defines, this is terrible coding
//TODO : Fix the two macros and make them variables
//Macros fixed, const unsigned ints created

const unsigned int MSG_END = 2000;
const unsigned int CHAR_END = 1000;

void showmsg(int array[5]);
void onled(int time);
void offled(int time);

int main(void)
{
	int S_char[5] = {100, 100, 100, 100, 100};
	int O_char[5] = {250, 100, 250, 100, 250};
		
	DDRB = 0xFF;
    /* Replace with your application code */
    while (1) 
    {
		showmsg(S_char);
		_delay_ms(CHAR_END);
		showmsg(O_char);
		_delay_ms(CHAR_END);
		showmsg(S_char);
		_delay_ms(MSG_END);	
    }
}

void onled(int time){
	PORTB = 0xFF;
	_delay_ms(time); /*accepts the time input because of the __DELAY_BACKWARD_COMPATIBLE__ macro*/
}


void offled(int time){
	PORTB = 0x00;
	_delay_ms(time); /*accepts the time input because of the __DELAY_BACKWARD_COMPATIBLE__ macro*/
}

void showmsg(int array[5]){
	for (int i = 0; i < 6; i++)
	{
		if (i%2==0)
		{
			onled(array[i]);
		}
		else if (i%2!=0)
		{
			offled(array[i]);
		}
	}
}

