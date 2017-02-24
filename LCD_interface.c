#include <stdint.h>
#include <msp430.h>
#include "header.h"

#define SET_ENABLE_LOW  P1OUT &= ~enable_pin
#define SET_ENABLE_HIGH P1OUT |= enable_pin 
#define SET_WRITE       P1OUT &= ~rw_sel_pin
#define SET_READ        P1OUT |= rw_sel_pin
#define SET_CMD_REG     P1OUT &= ~reg_sel_pin
#define SET_DATA_REG    P1OUT |= reg_sel_pin

//Delay function
void delay(uint8_t t){
    for(j = 0; j <= t; j++){
        for(i = 0; i < 100; i++);
    }
}

//Function to initialize the LCD
void LCD_init(void){

    //Set LCD into 8-bit mode
    send_cmd(0x38); 

    //Turn the LCD display on and hide the cursor
    send_cmd(0xc);

    //Clear the LCD display
    send_cmd(0x1); 

    //Place the cursor at the beginning of the first line
    send_cmd(0x80);
}

//Function to send data to the LCD data register
void send_data(uint8_t cmd){

    //Check if LCD is busy
    poll_busy(void); 

    //Set R/W LCD pin to write
    SET_WRITE;

    //Select data register on LCD
    SET_DATA_REG;

    //Send command to shift register
    shift_out(cmd);

    //Set enable LCD pin high to low (write)
    SET_ENABLE_HIGH;
    delay(2);
    SET_ENABLE_LOW;
}

//Function to send data to the LCD command register
void send_cmd(uint8_t cmd){

    //Check if LCD is busy
    poll_busy(void); 

    //Set R/W LCD pin to write
    SET_WRITE;

    //Select command register on LCD
    SET_CMD_REG;

    //Send command to shift register
    shift_out(cmd); 

    //Set enable LCD pin high to low (write)
    SET_ENABLE_HIGH;
    delay(2);
    SET_ENABLE_LOW;
}

//Function to check whether the LCD is busy
void poll_busy(void){

    //Poll the busy bit on the LCD
    while((P1IN & busy_check_pin) == 1){

        //Set enable LCD pin low to high (read)
        SET_ENABLE_LOW;
        delay(2);
        SET_ENABLE_HIGH;
    }
}

void write_string(char *str){

    //Loop to increment through string via pointer
    while(*str){

        //Send each character to the LCD display
        send_data(*str)
        str++;
    }
}