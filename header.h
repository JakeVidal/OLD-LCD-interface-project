#ifndef _HEADER_H_
#define _HEADER_H_
#include <stdint.h>

//Function prototypes and type definitions
void serial_com(uint8_t data_pin, uint8_t clk_pin, uint8_t value);
void LCD_init(void);
void send_data(void);
void send_cmd(void);

#endif
