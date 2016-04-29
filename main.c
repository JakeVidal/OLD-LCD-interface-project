#include <stdint.h>
#include <msp430.h>
#include "header.h"

// Main program function
int main(void) {
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;
    // Initialize P1.0, P1.1 and P1.2 to ouput as clk_pin, data_pin and latch_pin and P1.3 as input
    P1DIR |= 0b0111;
    // Enable interrupt on P1.3
    P1IE |= ~0b1000;
    // Set interrupt to trigger on high/low edge (for button)
    P1IES |= 0b1000;
    // Clear interrupt flag for P1.3
    P1IFG &= ~0b1000;
    // Loop forever with Interrupts enabled
    __enable_interrupt();
    while(1){}
}

// Port 1 Interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){
	// Set latch pin to low
	P1OUT &= ~0b0100;
	// Outputs an 8-bit value in serial through P1.1
	serial_com(0b0010, 0b0001, 0b10101100);
	// Set latch pin to high
	P1OUT |= 0b0100;
	// Clear interrupt flag for P1.3
	P1IFG &= ~0b1000;
}
