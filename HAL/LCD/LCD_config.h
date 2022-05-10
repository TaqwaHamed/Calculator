/*
 * LCD_config.h
 *
 *  Created on: Oct 29, 2021
 *      Author: taqwa
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/*			LCD_MODE		*/
#define LCD_MODE		EIGHT_BIT

/*			Control Pins	*/
#define RS_PORT		PORTD
#define RS_PIN		PIN0

#define RW_PORT		PORTD
#define RW_PIN		PIN1

#define EN_PORT		PORTD
#define EN_PIN		PIN2

/*			Data Pins		*/
#define D7_PORT		PORTC
#define D7_PIN		PIN7

#define D6_PORT		PORTC
#define D6_PIN		PIN6

#define D5_PORT		PORTC
#define D5_PIN		PIN5

#define D4_PORT		PORTC
#define D4_PIN		PIN4

#define D3_PORT		PORTC
#define D3_PIN		PIN3

#define D2_PORT		PORTC
#define D2_PIN		PIN2

#define D1_PORT		PORTC
#define D1_PIN		PIN1

#define D0_PORT		PORTC
#define D0_PIN		PIN0

#define LCD_DISPLAY_CLEAR				0b00000001
#define LCD_SHIFT_DISABEL				0b00000110
#define LCD_SHIFT_LEFT					0b00000111
#define LCD_SHIFT_RIGHT				0b00000101

#endif /* LCD_CONFIG_H_ */
