#include<avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>
#include "STD_Types.h"
#include <stdlib.h>


#define Element 7
////////////////////////////////////////////////////////////////////////////////////////
void Resposnse_WIFI_GOT_IP(void);
void Usart_Send(char *ptr,int Number_Of_Characters);
void Get_Char(void);
void Safe_Response(int channel);
void Danger_Response(int channel);
void Sensor_Check(void);//checks the sensor reading if within range green light on , if not within range red light on and buzzer on
void turn_on_off_sensor(void);
void Analogee_Value(void);

char *LCDptr[3]={0};
char y[3]={0};
u16 * ADCLptr=0;
u16 * ADCHptr=0;
int counterADC=0;
int counter_tmr=0;
int flag=0;
int Flag_Sensor_Check=0;

char temp[2];
char Analoge_Value[8];
int index_Get_Char=0;//to store the number of received characters in the line form esp8266
int counter=0;
int temp_counter=0;
int index=0;
int send=0;

int counter_timer=0;
u16 time=0;

char Char_String[1][151];
char Esp_Excepected_Response[3 ][Element]={"+IPD,0","+IPD,1","OK\r\n"};
char Esp_Communicate        [16][41     ]=
{
"AT+CIPMUX=1\r\n",
"AT+CIPSERVER=1,255\r\n",
"AT+CIPSENDBUF=0,126\r\n",//140 works
"AT+CIPSENDBUF=0,126\r\n",
"AT+CIPSENDBUF=1,126\r\n",
"AT+CIPSENDBUF=1,126\r\n",
"HTTP/1.1 200 OK\r\n",
"Content-Type: text/html\r\n",
"\r\n",
"<!DOCTYPE HTML>\r\n",
"<html>\r\n",
"<br><br>\r\n",
"THE STATUS OF AIR IS DANGEROUS  <br>\r\n",
"</html>\r\n",
"AT+CIPCLOSE=0\r\n",
"THE STATUS OF AIR IS SAFE.....  <br>\r\n"
};
/////////////////////////////////////////////////////////////////////////////////////
ISR (USART_RXC_vect)
{
	temp[temp_counter]=UDR;
	send=1;
	Get_Char();

}
/////////////////////////////////////////////////////////////////////////////////////
ISR(ADC_vect)
{
	 ADCSRA |=(1<<ADSC);//begin the next ADC conversion

}
/////////////////////////////////////////////////////////////////////////////////////
ISR(TIMER0_OVF_vect)
{

	counter_tmr++;
		if (counter_tmr>=255)
		{
			time++;
			counter_tmr=0;
		}
}
/////////////////////////////////////////////////////////////////////////////////////
void main(void)
{

	UCSRB |=(1<<TXEN)  |(1<<RXEN) |(1<<RXCIE) ;
	UCSRC |=(1<<URSEL) |(1<<UCSZ0)|(1<<UCSZ1) ;
	UBRRL  =51                                ;
	UBRRH  =0                                 ;

	DDRB   =0xFF                              ;
	PORTB  =0x00                              ;
	DDRC   =0xFF                              ;
	PORTC  =0x00                              ;
	DDRA=0b00000000                           ;


	ADCSRA=0x8F;
	ADMUX=0b01000001;
	ADCSRA |=(1<<ADSC);//begin the first conversion when the program has started

	TCCR0=0b00000010;/*Normal with 8 prescale */
	TIMSK=0b00000001;/*timer 0 interrupt over flow enabled*/
	SREG|=0b10000000;

	sei();//enable general interrupts

	for(int i=0;i<151;i++)
	{
		Char_String[0][i]='\0';
	}
	PORTC|=(1<<PC3);
	_delay_ms(2000);
	Resposnse_WIFI_GOT_IP();
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
	while(1)
	{
	if ((strcmp(Char_String[0],"WIFI GOT IP"))==0 && send==1)
	{
			Resposnse_WIFI_GOT_IP();
			send=0;
	}

	if((strcmp(Esp_Excepected_Response[0],Char_String[index]))==0 && send==1 && Flag_Sensor_Check==1)
	{
			Danger_Response(2);//idp==0
			send=0;
	}

		else if((strcmp(Esp_Excepected_Response[1],Char_String[index]))==0 && send==1 && Flag_Sensor_Check==1)
		{
			Danger_Response(4);//ipd==1
			send=0;
		}

	if((strcmp(Esp_Excepected_Response[0],Char_String[index]))==0 && send==1 && Flag_Sensor_Check==0)
		{
				Safe_Response(2);//idp==0
				send=0;
		}

			else if((strcmp(Esp_Excepected_Response[1],Char_String[index]))==0 && send==1 && Flag_Sensor_Check==0)
			{
				Safe_Response(4);//ipd==1
				send=0;
			}

	turn_on_off_sensor();


	if(Char_String[0][index_Get_Char-1]=='\n')
		{
			for(int i=0;i<151;i++)
			{
				Char_String[0][i]='\0';
			}
			index_Get_Char=0;
		}

	}

}
////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void Usart_Send(char *ptr,int Number_Of_Characters)
{
	int index=0;
	for(int i=0;i<Number_Of_Characters;i++)
	{
		UDR=*ptr;
		ptr++;
		_delay_ms(10);
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void Resposnse_WIFI_GOT_IP(void)
{
		_delay_ms(1000);
	Usart_Send(&Esp_Communicate[0][0],15);
		_delay_ms(1000);
	Usart_Send(&Esp_Communicate[1][0],22);
}
////////////////////////////////////////////////////////////////////////////////////////////
void Danger_Response(int channel)
{
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[channel][0],21);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[6][0],17);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[7][0],25);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[8][0],2);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[9][0],17);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[10][0],8);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[11][0],10);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[12][0],38);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[13][0],9);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[14][0],15);

}
////////////////////////////////////////////////////////////////////////////////////////////
void Safe_Response(int channel)
{
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[channel][0],21);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[6][0],17);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[7][0],25);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[8][0],2);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[9][0],17);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[10][0],8);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[11][0],10);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[15][0],38);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[13][0],9);
	_delay_ms(500);
	Usart_Send(&Esp_Communicate[14][0],15);

}
///////////////////////////////////////////////////////////////////////////////////////////
void Get_Char(void)
{
	//else//start storing the data form esp8266

		Char_String[0][index_Get_Char]=temp[temp_counter];
		index_Get_Char ++ ;
		temp_counter++;

		if(temp_counter>1)
		{
			temp_counter=0;
		}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sensor_Check(void)
{

	ADCLptr=&ADCL;//assign the adress of the ADCL(which stores the ADC value after conversion) to the ADCLPTR pointeer
	ADCHptr=&ADCH;

	if(* ADCLptr>260 & time>5750)
	 {
		counterADC++;//to make sure that the high reading is not momentarely

		while(counterADC==3)
		 {
			PORTB=0b00000011;
			counterADC=0;
			Flag_Sensor_Check=1;//this flag will be used to either send a danger messaage to the esp client on browser or not
		 }
	 }

	else if(* ADCLptr<260 & time>5750)
	 {
		PORTB=0b00000100;
		Flag_Sensor_Check=0;//this flag will be used to either send a danger messaage to the esp client on browser or not
	 }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void turn_on_off_sensor(void)
{
	if(time<=5000)
	    {
		PORTC =0b00001010;
	    }
	  if(time>=5000&&time<=6000)//1 mins=1000 and 6 mins=6000
	    {
	    PORTC =0b00001100;
	    Sensor_Check();
	    }
	  else if(time>6000)
	  	  {
		  time=0;
	  	  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Analogee_Value(void)
{
	itoa(*ADCLptr,Analoge_Value,10);

	Usart_Send(&Analoge_Value,3);

	Usart_Send(&Esp_Communicate[8][0],2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

