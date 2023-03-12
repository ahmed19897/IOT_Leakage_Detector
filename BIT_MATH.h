#ifndef _BIT_MATH_h
#define _BIT_MATH_h
/*guard file to prevent super loop of text replacment*/




#define set_bit(value,bit_num) value|=(1<<bit_num)
/*set_bit will write 1 into the Bit_NUM in value Port*/

#define toggle_bit(value,bit_num) value^=(1<<bit_num) 
/*toggle_bit will toggle the Bit_NUM in  Port value*/

#define clear_bit(value,bit_num) value&=(1<<bit_num) 
/*clear_bit will write 0 into Bit_NUM in value port*/

#define get_bit(value,bit_num) (((value) >> (bit_num)) & 0x01)
/*get_bit will return the value of the corrosponding bit*/


/*end of guard file */
#endif