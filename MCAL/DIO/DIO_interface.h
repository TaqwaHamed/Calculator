
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

typedef enum{

	DIO_NOK,
	DIO_OK

}DIO_ErrorStatus;




/* Port Defines */
#define PORTA    0
#define PORTB    1
#define PORTC    2
#define PORTD    3

/* PIN Defines */
#define PIN0   0
#define PIN1   1
#define PIN2   2
#define PIN3   3
#define PIN4   4
#define PIN5   5
#define PIN6   6
#define PIN7   7

/* PIN Directions */
#define INPUT  0
#define OUTPUT 1

/* PIN Value Options */
#define HIGH   1
#define LOW    0

/* IO Pins */
DIO_ErrorStatus DIO_SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy);
DIO_ErrorStatus DIO_TOGPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy);
DIO_ErrorStatus DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy, u8 *u8PinVal);

DIO_ErrorStatus DIO_SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy);

/* IO Ports */
DIO_ErrorStatus DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir);

DIO_ErrorStatus DIO_SetPortValue     (u8 u8PortId, u8 u8PortVal);
DIO_ErrorStatus DIO_TOGPortValue     (u8 u8PortId, u8 u8PortVal);
#endif
