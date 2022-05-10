/*
 * LCD_private.h
 *
 *  Created on: Oct 29, 2021
 *      Author: taqwa
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define EIGHT_BIT	24
#define FOUR_BIT	9

static inline void LCD_invidSendCommend(u8 Copy_u8Command);

static void LCD_voidLatch(u8 copy_u8Data);

#define LCD_ROW_1     111
#define LCD_ROW_2     222

#define LCD_COL_1      1
#define LCD_COL_2      2
#define LCD_COL_3      3
#define LCD_COL_4      4
#define LCD_COL_5      5
#define LCD_COL_6      6
#define LCD_COL_7      7
#define LCD_COL_8      8
#define LCD_COL_9      9
#define LCD_COL_10     10
#define LCD_COL_11     11
#define LCD_COL_12     12
#define LCD_COL_13     13
#define LCD_COL_14     14
#define LCD_COL_15     15
#define LCD_COL_16     16





#endif /* LCD_PRIVATE_H_ */
