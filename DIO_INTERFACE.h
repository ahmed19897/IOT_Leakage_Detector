#ifndef _DIO_interface_h
#define _DIO_interface_h
#include"STD_Types.h"
/*port macros*/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

/*pin macros*/
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

/*output/input macros*/
#define output 1

#define input 0


/*high/low macros*/
#define HIGH 1

#define LOW 0

/*individiual pin functions*/
void set_pin_direction(u8 u8port_choice,u8 u8pin_number,u8 u8direction_value);


void set_pin_value (u8 u8port_choice,u8 u8pin_number,u8 u8value);


u8 get_pin_value(u8 u8port_choice,u8 u8pin_number);

/*port functions*/
void set_port_direction(u8 u8port_choice,u8 u8port_direction);


void set_port_value(u8 u8port_choice,u8 u8port_value);


u8 get_port_value(u8 u8port_choice);
/*end of guard file*/



#endif
