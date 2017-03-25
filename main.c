#include <stdint.h>
#include <msp430.h>
#include "header.h"

//Main program function
int main(void) {

    //Stop watchdog timer to prevent timeout reset
    WDTCTL = WDTPW | WDTHOLD;

    //Initialize P1.1, P1.2, P1.4, P1.5, P1.6 and P1.7 to output then enable pullup resistors
    P1DIR |= (clk_pin | data_pin | latch_pin | reg_sel_pin | rw_sel_pin | enable_pin);
    P1REN |= (clk_pin | data_pin | latch_pin | reg_sel_pin | rw_sel_pin | enable_pin | switch_pin | busy_check_pin);

    //Set P1.0 and P1.3 as input 
    P1DIR &= ~switch_pin;
    P1DIR &= ~busy_check_pin;

    //Enable interrupt, set to trigger on high/low edge (for button to work) and clear interrupt flags
    P1IE |= switch_pin;
    P1IES |= switch_pin;
    P1IFG = 0x0;

    //Initialize the LCD
    LCD_init();
    
    //Loop forever with Interrupts enabled
    __enable_interrupt();
    while(1){}
}

//Port 1 Interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void){

    //Send data to LCD
    write_string("Hello World");

    //Clear interrupt flag for P1.3
    P1IFG &= ~switch_pin;
}