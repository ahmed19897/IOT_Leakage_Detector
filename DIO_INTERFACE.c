#include"STD_Types.h"
#include"DIO_INTERFACE.h"
#include"DIO_REGISTERS.h"
#include"BIT_MATH.h"
u8 loc_pin_value;
u8 LOC_u8Return = 0x00;
/*..................................................................................................................................................................................*/
/*Discription:  set_pin_direction writes the state of an indivisiual pin either input or output                                                                                     */
/*Input:  port_choice: PORTA,PORTB,PORTC or PORTD-----pin_number: PIN0,PIN1,PIN2......PIN7-----direction_value: output or input                                                     */
/*return:  NULL                                                                                                                                                                     */
/*..................................................................................................................................................................................*/
void set_pin_direction(u8 u8port_choice,u8 u8pin_number,u8 u8direction_value)
{
	switch(u8port_choice)
	{
		case PORTA:
		if(u8direction_value==output)
		 {
			set_bit(DDRA_REGISTER,u8pin_number);
		 } 
		else if (u8direction_value==input)
		 {
			clear_bit(DDRA_REGISTER,u8pin_number);
		 }
		 break;
        case PORTB:
		if(u8direction_value==output)
		 {
			set_bit(DDRB_REGISTER,u8pin_number);
		 } 
		else if (u8direction_value==input)
		 {
			clear_bit(DDRB_REGISTER,u8pin_number);
		 }
         break;		 
        case PORTC:
		if(u8direction_value==output)
		 {
			set_bit(DDRC_REGISTER,u8pin_number);
		 } 
		else if (u8direction_value==input)
		 {
			clear_bit(DDRC_REGISTER,u8pin_number);
		 }
 		 break;
		case PORTD:
		if(u8direction_value==output)
		 {
			set_bit(DDRD_REGISTER,u8pin_number);
		 } 
		else if (u8direction_value==input)
		 {
			clear_bit(DDRD_REGISTER,u8pin_number);
		 }
         break;    		 
	}
}
/*..................................................................................................................................................................................*/
/*Discription: set_pin_value writes the value of an indivisiual pin either 0 or 5 volts                                                                                             */
/*Input: port_choice: PORTA,PORTB,PORTC or PORTD-----pin_number: PIN0,PIN1,PIN2......PIN7-----value: HIGH or LOW                                                                    */
/*return: NULL                                                                                                                                                                      */
/*..................................................................................................................................................................................*/
void set_pin_value (u8 u8port_choice,u8 u8pin_number,u8 u8value)
{
	switch(u8port_choice)
	{
	case PORTA:
		if(u8value==HIGH)
		{
			set_bit(PORTA_REGISTER,u8pin_number);
		}
		else if(u8value==LOW)
		{
			clear_bit(PORTA_REGISTER,u8pin_number);
		}
		break;
	case PORTB:
		if(u8value==HIGH)
		{
			set_bit(PORTB_REGISTER,u8pin_number);
		}
		else if(u8value==LOW)
		{
			clear_bit(PORTB_REGISTER,u8pin_number);
		}
		break;
	case PORTC:
		if(u8value==HIGH)
		{
	    	set_bit(PORTC_REGISTER,u8pin_number);
		}
		else if(u8value==LOW)
		{
			clear_bit(PORTC_REGISTER,u8pin_number);
		}
		break;
	case PORTD:
		if(u8value==HIGH)
		{
	      	set_bit(PORTD_REGISTER,u8pin_number);
		}
		else if(u8value==LOW)
		{
			clear_bit(PORTD_REGISTER,u8pin_number);
		}
		break;
	}
}
/*..................................................................................................................................................................................*/
/*Discription: set_port_direction writes the port direction either 0->inout or 255->output                                                                                          */
/*Input: port_choice: PORTA,PORTB,PORTC or PORTD-----port_direction: Output or input                                                                                                */
/*return: NULL                                                                                                                                                                      */
/*..................................................................................................................................................................................*/
void set_port_direction(u8 u8port_choice,u8 u8port_direction)
{
	switch(u8port_choice)
	{
		case PORTA:
		if(u8port_direction==output)
		{
		DDRA_REGISTER=0xff;
		}
		else if (u8port_direction==input)
		{
		DDRA_REGISTER=0x00;
		}
		
		break;
		
		case PORTB:
		if(u8port_direction==output)
		{
		DDRB_REGISTER=0xff;
		}
		else if (u8port_direction==input)
		{
		DDRB_REGISTER=0x00;
		}
		
		break;
		
		case PORTC:
		if(u8port_direction==output)
		{
		DDRC_REGISTER=0xff;
		}
		else if (u8port_direction==input)
		{
		DDRC_REGISTER=0x00;
		}
		break;
		
		case PORTD:
		
		if(u8port_direction==output)
		{
		DDRD_REGISTER=0xff;
		}
		else if (u8port_direction==input)
		{
		DDRD_REGISTER=0x00;
		}
		
		break;
	}
}
/*..................................................................................................................................................................................*/
/*Discription: set_port_value writes the value of the port=port_value                                                                                                                  */
/*Input: port_choice: PORTA,PORTB,PORTC or PORTD-----port_value=0x00,0x01,0x02....0xff                                                                                         */
/*return:  value of the pin either 5 volt or 0 volt                                                                                                                                 */
/*..................................................................................................................................................................................*/
void set_port_value(u8 u8port_choice,u8 u8port_value)
{
	switch(u8port_choice)
	{
		case PORTA:
		
		PORTA_REGISTER=u8port_value;
		
		break;
		
		case PORTB:
		
		PORTB_REGISTER=u8port_value;
		
		break;
		
		case PORTC:
		
		PORTC_REGISTER=u8port_value;
		
		break;
		
		case PORTD:
		
		PORTD_REGISTER=u8port_value;
		
		break;
	}
}

/*..................................................................................................................................................................................*/
/*Discription: get_pin_value reads the value of an indivisiual pin                                                                                                                  */
/*Input: port_choice: PORTA,PORTB,PORTC or PORTD-----pin_number: PIN0,PIN1,PIN2......PIN7                                                                                           */
/*return:  value of the pin either 5 volt or 0 volt                                                                                                                                 */
/*..................................................................................................................................................................................*/
u8 get_pin_value(u8 u8port_choice,u8 u8pin_number)
{
	
	switch(u8port_choice)
	{
		case PORTA:
		loc_pin_value=get_bit(PINA_REGISTER,u8pin_number);
		break;
		case PORTB:
		loc_pin_value=get_bit(PINB_REGISTER,u8pin_number);
		break;
		case PORTC:
		loc_pin_value=get_bit(PINC_REGISTER,u8pin_number);
		break;
		case PORTD:
		loc_pin_value=get_bit(PIND_REGISTER,u8pin_number);
		break;
	}
	return (loc_pin_value);
}
/*..................................................................................................................................................................................*/
/*Discription: get_port_value reads the value of the port                                                                                                                           */
/*Input: port_choice: PORTA,PORTB,PORTC or PORTD                                                                                                                                    */
/*return: the value of the PIN(X) register                                                                                                                                          */
/*..................................................................................................................................................................................*/
u8 get_port_value(u8 u8port_choice)
{


  switch (u8port_choice)
  {

case PORTA:
  LOC_u8Return = PINA_REGISTER;
  break;

case PORTB:
  LOC_u8Return = PINB_REGISTER;
  break;

case PORTC:
  LOC_u8Return = PINC_REGISTER;
  break;

case PORTD:
  LOC_u8Return = PIND_REGISTER;
  break;

default:
  break;

  }
  return (LOC_u8Return);
}
