#include <msp430.h> 
#include "header.h"

unsigned int i = 0;

int main(void) {
	//Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    //Set P1.0 to output
    P1DIR |= 0x01;

    //Loop forever
    while(1){
    P1OUT ^= 0x01;
    //Delay on the blink
    for(i=0; i<20000; i++);
    }
}
