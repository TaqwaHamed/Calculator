/*
 * LCD_program.c
 *
 *  Created on: Oct 29, 2021
 *      Author: taqwa
 */
#include"../../Services/STD_TYPES.h"
#include"../../Services/BIT_MATH.h"
#include"../../MCAL/DIO/DIO_interface.h"
#include"LCD_interface.h"
#include"LCD_private.h"
#include"LCD_config.h"
#include"util/delay.h"

DIO_ErrorStatus LCD_enuInit(void)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;

	DIO_SetPinDirection(RS_PORT	, RS_PIN , OUTPUT);
	DIO_SetPinDirection(RW_PORT	, RW_PIN , OUTPUT);
	DIO_SetPinDirection(EN_PORT	, EN_PIN , OUTPUT);

	DIO_SetPinDirection(D7_PORT, D7_PIN, OUTPUT);
	DIO_SetPinDirection(D6_PORT, D6_PIN, OUTPUT);
	DIO_SetPinDirection(D5_PORT, D5_PIN, OUTPUT);
	DIO_SetPinDirection(D4_PORT, D4_PIN, OUTPUT);

	_delay_ms(50);

#if LCD_MODE == EIGHT_BIT
	DIO_SetPinDirection(D3_PORT, D3_PIN, OUTPUT);
	DIO_SetPinDirection(D2_PORT, D2_PIN, OUTPUT);
	DIO_SetPinDirection(D1_PORT, D1_PIN, OUTPUT);
	DIO_SetPinDirection(D0_PORT, D0_PIN, OUTPUT);

	// function set
	LCD_invidSendCommend(0x38);

#elif  LCD_MODE ==FOUR_BIT
	// function set
	LCD_invidSendCommend(0x28);
#endif

	_delay_ms(1);
	//Display on off
	LCD_invidSendCommend(0x0C);
	_delay_ms(1);
	//clear display
	LCD_invidSendCommend(0x01);
	_delay_ms(2);
	//entry mode
	LCD_invidSendCommend(0x06);

	return LOC_enumState;
}


DIO_ErrorStatus LCD_enuDisplayChar(u8 Copy_u8Data)
{

	DIO_ErrorStatus LOC_enumState=DIO_OK;
	//set RS as Data
	DIO_SetPinValue(RS_PORT ,RS_PIN ,HIGH);
	LCD_voidLatch( Copy_u8Data);

	return LOC_enumState;
}


DIO_ErrorStatus LCD_enuSendCommand(u8 Copy_u8Command)
{
	DIO_ErrorStatus LOC_enumState=DIO_OK;
	//set RS as command
	DIO_SetPinValue(RS_PORT ,RS_PIN ,LOW);
	LCD_voidLatch( Copy_u8Command);

	return LOC_enumState;
}

void LCD_voidSendString  ( u8 * Copy_u8ptrString )
{

	u8 LOC_u8Iterator=0;

	while(Copy_u8ptrString[LOC_u8Iterator]!= '\0')
	{
		LCD_enuDisplayChar(Copy_u8ptrString[LOC_u8Iterator]);
		LOC_u8Iterator++;

	}

}


void LCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col )
{

	if(Copy_u8Row==LCD_ROW_1)
	{
		LCD_invidSendCommend((0x80) + ( Copy_u8Col - 1 ));
	}

	else if(Copy_u8Row==LCD_ROW_2)
	{
		LCD_invidSendCommend((0x80)+64 + ( Copy_u8Col - 1 ));

	}

}


void LCD_voidSendINTNum(u32 copy_u32Num)
{


	u32 LOC_u32Reversed = 1 ;

	if( copy_u32Num == 0 ){ LCD_enuDisplayChar('0'); }

	else{

		while ( copy_u32Num != 0 ){

			LOC_u32Reversed = ( LOC_u32Reversed * 10 ) + ( copy_u32Num % 10 );
			copy_u32Num /= 10 ;

		}

		while ( LOC_u32Reversed != 1 ){
			DIO_SetPinValue(RS_PORT,RS_PIN,HIGH);
			LCD_voidLatch( ( LOC_u32Reversed % 10 ) + 48 );
			LOC_u32Reversed /= 10 ;

		}

	}




}
void LCD_voidClearScreen(void)
{
	LCD_invidSendCommend(LCD_DISPLAY_CLEAR);
		_delay_ms(2);

}


void LCD_voidSendExtraChar(u8 *copy_u8Parr,u8 copy_u8CharNum,u8 copy_u8position,u8 copy_u8EntryMode)
{
	u8 LOC_u8Iterator = 0 ;
	//Go To CGRAM
	LCD_invidSendCommend(0b01000000);
	// set RS as data
	DIO_SetPinValue(RS_PORT, RS_PIN,HIGH);
	//Draw Character
	for(LOC_u8Iterator=0;LOC_u8Iterator<(copy_u8CharNum*8);LOC_u8Iterator++)
	{
		LCD_voidLatch(copy_u8Parr[LOC_u8Iterator]);
	}
	if(copy_u8EntryMode==0x04)
	{
		//return to DDRAM
		LCD_invidSendCommend(copy_u8position);
		LCD_invidSendCommend(copy_u8EntryMode);


	}
	//send address
	for(LOC_u8Iterator=0;LOC_u8Iterator<copy_u8CharNum;LOC_u8Iterator++)
	{
		DIO_SetPinValue(RS_PORT, RS_PIN,HIGH);
		LCD_voidLatch(LOC_u8Iterator);


	}

}


void LCD_voidSendFloatNumber(f64 Copy_f64Number)
{


	// send int num
	LCD_voidSendINTNum((u64)Copy_f64Number );
	// Send decimal point
	LCD_enuDisplayChar('.');

	// Multiply the Float Number by 10^6 so the decimal number becomes part number
	u64 Local_u64tempNumber = Copy_f64Number*1000000;

	if( Local_u64tempNumber%10 >=5 )
	{

		LCD_voidSendINTNum((u64)((( Local_u64tempNumber/10)+1) % 100000));
	}
	else
	{

		// Display the number
		LCD_voidSendINTNum((u64)(( Local_u64tempNumber/10) % 100000));

	}


}

static inline void LCD_invidSendCommend(u8 Copy_u8Command)
{
	//set RS as command
	DIO_SetPinValue(RS_PORT ,RS_PIN ,LOW);

	// set RW as  write operation,EN LOW
	DIO_SetPinValue(RW_PORT, RW_PIN,LOW);
	DIO_SetPinValue(EN_PORT, EN_PIN,LOW);

	//write data
	DIO_SetPinValue(D7_PORT, D7_PIN,GET_BIT(Copy_u8Command,7) );
	DIO_SetPinValue(D6_PORT, D6_PIN, GET_BIT(Copy_u8Command,6) );
	DIO_SetPinValue(D5_PORT, D5_PIN, GET_BIT(Copy_u8Command,5)  );
	DIO_SetPinValue(D4_PORT, D4_PIN, GET_BIT(Copy_u8Command,4)  );

#if LCD_MODE==EIGHT_BIT

	DIO_SetPinValue(D3_PORT, D3_PIN,GET_BIT(Copy_u8Command,3) );
	DIO_SetPinValue(D2_PORT, D2_PIN, GET_BIT(Copy_u8Command,2) );
	DIO_SetPinValue(D1_PORT, D1_PIN, GET_BIT(Copy_u8Command,1) );
	DIO_SetPinValue(D0_PORT, D0_PIN, GET_BIT(Copy_u8Command,0) );

#elif LCD_MODE == FOUR_BIT
	if(Copy_u8Command=0x28)
	{
		// falling edge
		DIO_SetPinValue(EN_PORT, EN_PIN,HIGH);
		_delay_ms(10);
		DIO_SetPinValue(EN_PORT, EN_PIN,LOW);
		_delay_ms(10);
		DIO_SetPinValue(D7_PORT, D7_PIN,GET_BIT(Copy_u8Command,7) );
		DIO_SetPinValue(D6_PORT, D6_PIN, GET_BIT(Copy_u8Command,6) );
		DIO_SetPinValue(D5_PORT, D5_PIN, GET_BIT(Copy_u8Command,5)  );
		DIO_SetPinValue(D4_PORT, D4_PIN, GET_BIT(Copy_u8Command,4)  );
	}


	// falling edge
	DIO_SetPinValue(EN_PORT, EN_PIN,HIGH);
	_delay_ms(10);
	DIO_SetPinValue(EN_PORT, EN_PIN,LOW);
	_delay_ms(10);

	DIO_SetPinValue(D3_PORT, D3_PIN,GET_BIT(Copy_u8Command,3) );
	DIO_SetPinValue(D2_PORT, D2_PIN, GET_BIT(Copy_u8Command,2) );
	DIO_SetPinValue(D1_PORT, D1_PIN, GET_BIT(Copy_u8Command,1) );
	DIO_SetPinValue(D0_PORT, D0_PIN, GET_BIT(Copy_u8Command,0) );


#else
#error Wrong Selection


#endif

	// falling edge
	DIO_SetPinValue(EN_PORT, EN_PIN,HIGH);
	_delay_ms(10);
	DIO_SetPinValue(EN_PORT, EN_PIN,LOW);
	_delay_ms(10);

}





static void LCD_voidLatch(u8 copy_u8Data)
{

	// set RW as  write operation,EN LOW
	DIO_SetPinValue(RW_PORT, RW_PIN,LOW);
	DIO_SetPinValue(EN_PORT, EN_PIN,LOW);

	//write data
	DIO_SetPinValue(D7_PORT, D7_PIN,GET_BIT (copy_u8Data,7) );
	DIO_SetPinValue(D6_PORT, D6_PIN, GET_BIT(copy_u8Data,6) );
	DIO_SetPinValue(D5_PORT, D5_PIN, GET_BIT(copy_u8Data,5)  );
	DIO_SetPinValue(D4_PORT, D4_PIN, GET_BIT(copy_u8Data,4)  );

#if LCD_MODE==EIGHT_BIT

	DIO_SetPinValue(D3_PORT, D3_PIN,GET_BIT (copy_u8Data,3) );
	DIO_SetPinValue(D2_PORT, D2_PIN, GET_BIT(copy_u8Data,2) );
	DIO_SetPinValue(D1_PORT, D1_PIN, GET_BIT(copy_u8Data,1) );
	DIO_SetPinValue(D0_PORT, D0_PIN, GET_BIT(copy_u8Data,0) );

#elif LCD_MODE == FOUR_BIT
	if(Copy_u8Command=0x28)
	{
		// falling edge
		DIO_SetPinValue(EN_PORT, EN_PIN,HIGH);
		_delay_ms(10);
		DIO_SetPinValue(EN_PORT, EN_PIN,LOW);
		_delay_ms(10);
		DIO_SetPinValue(D7_PORT, D7_PIN,GET_BIT( copy_u8Data,7) );
		DIO_SetPinValue(D6_PORT, D6_PIN, GET_BIT(copy_u8Data,6) );
		DIO_SetPinValue(D5_PORT, D5_PIN, GET_BIT(copy_u8Data,5)  );
		DIO_SetPinValue(D4_PORT, D4_PIN, GET_BIT(copy_u8Data,4)  );
	}


	// falling edge
	DIO_SetPinValue(EN_PORT, EN_PIN,HIGH);
	_delay_ms(10);
	DIO_SetPinValue(EN_PORT, EN_PIN,LOW);
	_delay_ms(10);

	DIO_SetPinValue(D3_PORT, D3_PIN,GET_BIT (copy_u8Data,3) );
	DIO_SetPinValue(D2_PORT, D2_PIN, GET_BIT(copy_u8Data,2) );
	DIO_SetPinValue(D1_PORT, D1_PIN, GET_BIT(copy_u8Data,1) );
	DIO_SetPinValue(D0_PORT, D0_PIN, GET_BIT(copy_u8Data,0) );


#else
#error "Wrong Selection"


#endif

	// falling edge
	DIO_SetPinValue(EN_PORT, EN_PIN,HIGH);
	_delay_ms(10);
	DIO_SetPinValue(EN_PORT, EN_PIN,LOW);
	_delay_ms(10);



}
















