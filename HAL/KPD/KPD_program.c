/*
 * KPD_program.c
 *
 *  Created on: Nov 2, 2021
 *      Author: taqwa
 */

#include"../../Services/STD_TYPES.h"
#include"../../Services/BIT_MATH.h"
#include"../../MCAL/DIO/DIO_interface.h"
#include"KPD_interface.h"
#include"KPD_config.h"
#include"KPD_private.h"
#include "util/delay.h"



DIO_ErrorStatus KeyPadInt(void)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;

	DIO_SetPinDirection(KeyPad_ROW_1port , KeyPad_ROW_1pin ,INPUT);
	DIO_SetPinDirection(KeyPad_ROW_2port , KeyPad_ROW_2pin ,INPUT);
	DIO_SetPinDirection(KeyPad_ROW_3port , KeyPad_ROW_3pin ,INPUT);
	DIO_SetPinDirection(KeyPad_ROW_4port , KeyPad_ROW_4pin ,INPUT);

	DIO_SetPinValue(KeyPad_ROW_1port , KeyPad_ROW_1pin ,HIGH);
	DIO_SetPinValue(KeyPad_ROW_2port , KeyPad_ROW_2pin ,HIGH);
	DIO_SetPinValue(KeyPad_ROW_3port , KeyPad_ROW_3pin ,HIGH);
	DIO_SetPinValue(KeyPad_ROW_4port , KeyPad_ROW_4pin ,HIGH);


	DIO_SetPinDirection(KeyPad_COL_1port , KeyPad_COL_1pin ,OUTPUT);
	DIO_SetPinDirection(KeyPad_COL_2port , KeyPad_COL_2pin ,OUTPUT);
	DIO_SetPinDirection(KeyPad_COL_3port , KeyPad_COL_3pin ,OUTPUT);
	DIO_SetPinDirection(KeyPad_COL_4port , KeyPad_COL_4pin ,OUTPUT);

	DIO_SetPinValue(KeyPad_COL_1port , KeyPad_COL_1pin ,HIGH);
	DIO_SetPinValue(KeyPad_COL_2port , KeyPad_COL_2pin ,HIGH);
	DIO_SetPinValue(KeyPad_COL_3port , KeyPad_COL_3pin ,HIGH);
	DIO_SetPinValue(KeyPad_COL_4port , KeyPad_COL_4pin ,HIGH);


	return LOC_enumState;
}


DIO_ErrorStatus KeyPadGetPressed(u8 *copy_pu8KeyValue )
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;

	u8 rowpin[]=  {KeyPad_ROW_1pin,KeyPad_ROW_2pin,KeyPad_ROW_3pin,KeyPad_ROW_4pin};
	u8 rowport[]= {KeyPad_ROW_1port,KeyPad_ROW_2port,KeyPad_ROW_3port,KeyPad_ROW_4port};

	u8 colpin[]=  {KeyPad_COL_1pin,KeyPad_COL_2pin,KeyPad_COL_3pin,KeyPad_COL_4pin};
	u8 colport[]= {KeyPad_COL_1port,KeyPad_COL_2port,KeyPad_COL_3port,KeyPad_COL_4port};

	u8 col,row,pinval;


	for(col=0;col<4;col++)
	{
		DIO_SetPinValue(colport[col], colpin[col], LOW);

		for(row=0;row<4;row++)
		{
			DIO_GetPinValue(rowport[row] , rowpin[row] ,&pinval);

			if(pinval==0) //FOR BOUNCING
			{
				_delay_ms(30);
				DIO_GetPinValue(rowport[row],rowpin[row],&pinval);
				if(pinval==0)
				{
					*copy_pu8KeyValue = arr[row][col];
				}
				DIO_GetPinValue(rowport[row],rowpin[row],&pinval);
				while(pinval==0)
				{
					DIO_GetPinValue(rowport[row],rowpin[row],&pinval);
				}
				break;
			}

		}

		DIO_SetPinValue(colport[col], colpin[col], HIGH);
	}


	return LOC_enumState;
}

