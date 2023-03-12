#ifndef DIO_REGISTERS_h 
#define DIO_REGISTERS_h

/*Group A REGISTERs*/
#define DDRA_REGISTER *((volatile u8*) 0x3A)
#define PORTA_REGISTER *((volatile u8*) 0x3B)
#define PINA_REGISTER *((volatile u8*) 0x39)

/*Group B REGISTERs*/
#define DDRB_REGISTER *((volatile u8*) 0x37)
#define PORTB_REGISTER *((volatile u8*) 0x38)
#define PINB_REGISTER *((volatile u8*) 0x36)

/*Group C REGISTERs*/
#define DDRC_REGISTER *((volatile u8*) 0x34)
#define PORTC_REGISTER *((volatile u8*) 0x35)
#define PINC_REGISTER *((volatile u8*) 0x33)

/*group D REGISTERs*/
#define DDRD_REGISTER *((volatile u8*) 0x31)
#define PORTD_REGISTER *((volatile u8*) 0x32)
#define PIND_REGISTER *((volatile u8*) 0x30)

#endif