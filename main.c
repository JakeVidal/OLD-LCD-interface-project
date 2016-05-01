#include <stdint.h>
#include <msp430.h>
#include "header.h"

static const uint8_t clk_pin = 0b00000001;
static const uint8_t data_pin = 0b00000010;
static const uint8_t latch_pin = 0b00000100;
static const uint8_t switch_pin = 0b00001000;

// Main program function
int main(void) {

    // Stop watchdog timer to prevent timeout reset
    WDTCTL = WDTPW | WDTHOLD;

    // Initialize P1.0, P1.1 and P1.2 to output as clk_pin, data_pin and latch_pin then enable pullup resistors
    P1DIR |= (data_pin | clk_pin | latch_pin);
    P1REN |= (data_pin | clk_pin | latch_pin);

    // set P1.3 as input, enable pullup resistors, enable interrupt, set to trigger on high/low edge (for button to work) and clear interrupt flags
    P1DIR &= ~switch_pin;
    P1REN |= switch_pin;
    P1IE |= switch_pin;
    P1IES |= switch_pin;
    P1IFG = 0b00000000;


    // Loop forever with Interrupts enabled
    __enable_interrupt();
    while(1){}
}

// Port 1 Interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){

	// Set latch pin to low
	P1OUT &= ~latch_pin;

	// Outputs an 8-bit value in serial through P1.1
	serial_com(data_pin, clk_pin, 0b10101100);

	// Set latch pin to high
	P1OUT |= latch_pin;
    
	// Clear interrupt flag for P1.3
	P1IFG &= ~switch_pin;
}
