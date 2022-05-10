/*
 * calc.c
 *
 *  Created on: Apr 24, 2022
 *      Author: taqwa
 */

#include"../Services/STD_TYPES.h"
#include"calc.h"


u8 AsciTOInt(u8 * Copy_u8String ,  u16 * Copy_u32Value)
{

	u8 LOC_u8ArrayStringCounter = 0;
	u8 LOC_u8ValueArrayIndexCounter = 0;
	u8 LOC_u8Temp = 0;


	while( Copy_u8String[ LOC_u8ArrayStringCounter ] != '\0' )
	{

		switch(Copy_u8String[ LOC_u8ArrayStringCounter ])
		{

		case '+':
		case '-':
		case '*':
		case '/':   LOC_u8ValueArrayIndexCounter++;
		Copy_u32Value[LOC_u8ValueArrayIndexCounter++]  =  ( Copy_u8String[ LOC_u8ArrayStringCounter ] | (1<<15) );

		break;
		default:
			LOC_u8Temp = Copy_u8String[LOC_u8ArrayStringCounter] - '0';
			Copy_u32Value[LOC_u8ValueArrayIndexCounter] = Copy_u32Value[LOC_u8ValueArrayIndexCounter]*10 + LOC_u8Temp;

		}

		LOC_u8ArrayStringCounter++;


	}


	return LOC_u8ValueArrayIndexCounter;

}



void Array_voidClear(void * Copy_vidptrArray , u8 Copy_u8ArrayLength , u8 Copy_u8Type)
{

	for( u8 Local_u8ArrayIterator = 0; Local_u8ArrayIterator <Copy_u8ArrayLength ; Local_u8ArrayIterator++ )
		{
			if( Copy_u8Type == U8_Type )
			{
				*(u8*)(Copy_vidptrArray+Local_u8ArrayIterator) = 0;
			}
			else if( Copy_u8Type == U16_Type )
			{
				*(u16*)(Copy_vidptrArray+Local_u8ArrayIterator) = 0;
			}
		}





}
