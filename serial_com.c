#include <stdint.h>
#include <msp430.h>
#include "header.h"

//Function to allow serial communication with shift register
void serial_com(uint8_t data_pin, uint8_t clk_pin, uint8_t value){
	// Definitions of variables
	uint8_t bytemask = 0b0001, k;
	// Loop that iterates through value to send it 
	for(k = 8; k > 0; k--){
		// Set data_pin to output current 1/8th of value
		P1OUT &= !data_pin;
		P1OUT |= (value & bytemask);
		// Set clk_pin to high
		P1OUT ^= clk_pin;
		// Set clk_pin to low (default)
		P1OUT ^= clk_pin;
		// Increment output to next 1/8th of value
		bytemask <<= 1;
	}
}

