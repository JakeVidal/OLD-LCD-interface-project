#ifndef _HEADER_H_
#define _HEADER_H_
#include <stdint.h>

//Pin definitions
static const uint8_t clk_pin 		= 0x1;		//P1.1
static const uint8_t data_pin 		= 0x2;		//P1.2
static const uint8_t latch_pin 		= 0x4;		//P1.3
static const uint8_t switch_pin 	= 0x8;		//P1.4
static const uint8_t reg_sel_pin 	= 0x10;		//P1.5
static const uint8_t rw_sel_pin 	= 0x20;		//P1.6
static const uint8_t enable_pin 	= 0x40;		//P1.7
static const uint8_t busy_check_pin = 0x0;		//P1.0

//Function prototypes and type definitions
void serial_com(uint8_t value);
void shift_out(uint8_t data);

void delay(uint8_t t);
void LCD_init(void);
void send_data(uint8_t cmd);
void send_cmd(uint8_t cmd);
void poll_busy(void);
void write_string(char *str);

#endif
