/*
 * main.c
 *
 *  Created on: Apr 21, 2022
 *      Author: taqwa
 */
#include"../Services/STD_TYPES.h"
#include"../MCAL/DIO/DIO_interface.h"
#include"../HAL/KPD/KPD_interface.h"
#include"../HAL/KPD/KPD_config.h"
#include"../HAL/LCD/LCD_interface.h"
#include"../HAL/LCD/LCD_private.h"
#include"calc.h"
#include"InfixToPostfix.h"


#define OPERATION			1
#define NUMBER				0

int main(void)
{
	LCD_enuInit();
	KeyPadInt();



	u8 Local_u8LCD_CurrentPosition = LCD_COL_1;
	u8 Local_u8ArrayCurrentIndex = 0;
	u8 Local_u8ArrayEnteredvalues[100] = {0};
	u16 Local_u16ExpressionArray[20] = {0};
	u8 Local_u8LastVal = NUMBER;



	while(1)
	{

		u8 Local_u8KepadPressed = NOT_PRESSED;
		do{
			KeyPadGetPressed(&Local_u8KepadPressed);

		} while(Local_u8KepadPressed == NOT_PRESSED);


		if(Local_u8KepadPressed =='=')
		{

			LCD_enuDisplayChar(Local_u8KepadPressed);
			u8 Local_u8ExpLength =AsciTOInt(Local_u8ArrayEnteredvalues,Local_u16ExpressionArray);
			s32 LOC_u32Result = CALCEquation(Local_u16ExpressionArray,Local_u8ExpLength);
			if( LOC_u32Result < 0 )
			{
				LCD_enuDisplayChar('-');
				LCD_voidSendINTNum(LOC_u32Result*-1);
			}
			else
			{
				LCD_voidSendINTNum(LOC_u32Result);
			}
			Local_u8LastVal = NUMBER;


		}

		else if(Local_u8KepadPressed == 'c')
		{
			LCD_voidClearScreen();
			LCD_voidSetPosition (LCD_ROW_1,LCD_COL_1);
			Array_voidClear(Local_u8ArrayEnteredvalues,100,U8_Type);
			Array_voidClear(Local_u16ExpressionArray,20,U16_Type);

			Local_u8LCD_CurrentPosition =LCD_COL_1;
			Local_u8ArrayCurrentIndex   =0;
			Local_u8LastVal = NUMBER;
		}

		else  //user enter operation
		{

			if( (Local_u8KepadPressed == '+' ) || ( Local_u8KepadPressed == '-' ) ||
					(Local_u8KepadPressed == '*' ) || ( Local_u8KepadPressed == '/') )
			{


				if( Local_u8LastVal == OPERATION )  ////user enter operation and last value was operation
				{
					Local_u8LCD_CurrentPosition -=1;
					Local_u8ArrayCurrentIndex   -=1;
					Local_u8ArrayEnteredvalues[Local_u8ArrayCurrentIndex] = Local_u8KepadPressed;
					LCD_voidSetPosition(LCD_ROW_1 ,Local_u8LCD_CurrentPosition );
					LCD_enuDisplayChar(Local_u8KepadPressed);
					Local_u8LCD_CurrentPosition +=1;
					Local_u8ArrayCurrentIndex   +=1;
					Local_u8LastVal = OPERATION;
				}


				else     ////user enter operation and last value was Number
				{
					Local_u8ArrayEnteredvalues[Local_u8ArrayCurrentIndex] = Local_u8KepadPressed;
					LCD_enuDisplayChar(Local_u8KepadPressed);
					Local_u8LCD_CurrentPosition +=1;
					Local_u8ArrayCurrentIndex   +=1;
					Local_u8LastVal = OPERATION;

				}


			}

			else   //user enter number
			{
				Local_u8ArrayEnteredvalues[Local_u8ArrayCurrentIndex] = Local_u8KepadPressed;
				LCD_enuDisplayChar(Local_u8KepadPressed);
				Local_u8LCD_CurrentPosition +=1;
				Local_u8ArrayCurrentIndex   +=1;
				Local_u8LastVal = NUMBER;



			}



		}


	}






	return 0;
}
