#include <msp430.h> 

unsigned int i = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	//Stop watchdog timer

    P1DIR |= 0x01; //Set P1.0 to output

    while(1){ //Loop forever.
    P1OUT ^= 0x01;
    for(i=0; i<20000; i++);//Delay on the blink
    }
}
