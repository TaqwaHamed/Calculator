/*
 * LCD_interface.h
 *
 *  Created on: Oct 29, 2021
 *      Author: taqwa
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

DIO_ErrorStatus LCD_enuInit(void);

DIO_ErrorStatus LCD_enuDisplayChar(u8 Copy_u8Data);

DIO_ErrorStatus LCD_enuSendCommand(u8 Copy_u8Command);

void LCD_voidSendString  ( u8 * Copy_u8ptrString );
void LCD_voidSetPosition ( u8 Copy_u8Row , u8 Copy_u8Col );

void LCD_voidSendINTNum(u32 copy_u32Num);
void LCD_voidSendExtraChar(u8 *copy_u8Parr,u8 copy_u8CharNum,u8 copy_u8position,u8 copy_u8EntryMode);
void LCD_voidSendFloatNumber(f64 Copy_f32Number);
void LCD_voidClearScreen(void);

#endif /* LCD_INTERFACE_H_ */
