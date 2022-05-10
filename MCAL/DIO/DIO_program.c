


#include"../../Services/STD_TYPES.h"
#include"../../Services/BIT_MATH.h"
#include"DIO_interface.h"
#include"DIO_private.h"



DIO_ErrorStatus DIO_SetPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
	{
		if (u8PinValCopy == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
			case PORTA: SET_BIT(PORTA_REG,u8PinIdCopy); break;
			case PORTB: SET_BIT(PORTB_REG,u8PinIdCopy); break;
			case PORTC: SET_BIT(PORTC_REG,u8PinIdCopy); break;
			case PORTD: SET_BIT(PORTD_REG,u8PinIdCopy); break;
			}

		}

		else if (u8PinValCopy == LOW)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
			case PORTA: CLR_BIT(PORTA_REG,u8PinIdCopy); break;
			case PORTB: CLR_BIT(PORTB_REG,u8PinIdCopy); break;
			case PORTC: CLR_BIT(PORTC_REG,u8PinIdCopy); break;
			case PORTD: CLR_BIT(PORTD_REG,u8PinIdCopy); break;
			}
		}

		else
		{
			LOC_enumState = DIO_NOK ;
		}
	}

	else
	{
		LOC_enumState = DIO_NOK ;
	}
	return LOC_enumState;
}

DIO_ErrorStatus DIO_TOGPinValue(u8 u8PortIdCopy , u8 u8PinIdCopy, u8 u8PinValCopy)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
	{
		if (u8PinValCopy == HIGH)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
			case PORTA: CLR_BIT(PORTA_REG,u8PinIdCopy); break;
			case PORTB: CLR_BIT(PORTB_REG,u8PinIdCopy); break;
			case PORTC: CLR_BIT(PORTC_REG,u8PinIdCopy); break;
			case PORTD: CLR_BIT(PORTD_REG,u8PinIdCopy); break;
			}

		}

		else if (u8PinValCopy == LOW)
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
			case PORTA: SET_BIT(PORTA_REG,u8PinIdCopy); break;
			case PORTB: SET_BIT(PORTB_REG,u8PinIdCopy); break;
			case PORTC: SET_BIT(PORTC_REG,u8PinIdCopy); break;
			case PORTD: SET_BIT(PORTD_REG,u8PinIdCopy); break;
			}
		}

		else
		{
			LOC_enumState = DIO_NOK ;
		}
	}

	else
	{
		LOC_enumState = DIO_NOK ;
	}
	return LOC_enumState;
}

DIO_ErrorStatus DIO_GetPinValue(u8 u8PortIdCopy, u8 u8PinIdCopy,  u8 *u8PinVal)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;

	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
	{

		/* Check on the Required PORT Number */
		switch (u8PortIdCopy)
		{
		case PORTA:*u8PinVal= GET_BIT(PINA_REG,u8PinIdCopy); break;
		case PORTB:*u8PinVal= GET_BIT(PINB_REG,u8PinIdCopy); break;
		case PORTC:*u8PinVal= GET_BIT(PINC_REG,u8PinIdCopy); break;
		case PORTD:*u8PinVal= GET_BIT(PIND_REG,u8PinIdCopy); break;
		}

	}

	else
	{
		LOC_enumState = DIO_NOK ;
	}

	return LOC_enumState;

}

DIO_ErrorStatus DIO_SetPinDirection (u8 u8PortIdCopy, u8 u8PinIdCopy, u8 u8PinDirCopy)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;
	/* Make sure that the Port ID and Pin ID are in the valid range */
	if ((u8PortIdCopy <= PORTD) && (u8PinIdCopy <= PIN7))
	{
		if ( u8PinDirCopy == OUTPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
			case PORTA: SET_BIT(DDRA_REG,u8PinIdCopy); break;
			case PORTB: SET_BIT(DDRB_REG,u8PinIdCopy); break;
			case PORTC: SET_BIT(DDRC_REG,u8PinIdCopy); break;
			case PORTD: SET_BIT(DDRD_REG,u8PinIdCopy); break;
			}
		}

		else if ( u8PinDirCopy == INPUT )
		{
			/* Check on the Required PORT Number */
			switch (u8PortIdCopy)
			{
			case PORTA: CLR_BIT(DDRA_REG,u8PinIdCopy); break;
			case PORTB: CLR_BIT(DDRB_REG,u8PinIdCopy); break;
			case PORTC: CLR_BIT(DDRC_REG,u8PinIdCopy); break;
			case PORTD: CLR_BIT(DDRD_REG,u8PinIdCopy); break;
			}
		}

		else
		{
			LOC_enumState = DIO_OK ;
		}
	}

	else
	{
		LOC_enumState = DIO_NOK ;
	}
	return LOC_enumState;
}

DIO_ErrorStatus DIO_SetPortDirection (u8 u8PortId, u8 u8PortDir)
{

	DIO_ErrorStatus LOC_enumState = DIO_OK ;
	if (( u8PortId <= PORTD) )
	{
		/* Check on the Required PORT Number */
		switch (u8PortId)
		{
		case     PORTA: PORTA_REG = u8PortDir; break;
		case     PORTB: PORTB_REG = u8PortDir; break;
		case     PORTC: PORTC_REG = u8PortDir; break;
		case     PORTD: PORTD_REG = u8PortDir; break;
		default: /* Wrong Port ID */  LOC_enumState = DIO_NOK ;      break;
		}
	}
	else
	{
		LOC_enumState = DIO_NOK ;
	}

	return LOC_enumState ;
}

DIO_ErrorStatus DIO_SetPortValue     (u8 u8PortId, u8 u8PortVal)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;
	if (( u8PortId <= PORTD) )
	{
		/* Check on the Required PORT Number */
		switch (u8PortId)
		{
		case     PORTA: PORTA_REG = u8PortVal; break;
		case     PORTB: PORTB_REG = u8PortVal; break;
		case     PORTC: PORTC_REG = u8PortVal; break;
		case     PORTD: PORTD_REG = u8PortVal; break;
		default: LOC_enumState = DIO_NOK ;       break;
		}
	}
	else
	{
		LOC_enumState = DIO_NOK ;
	}
	return LOC_enumState ;

}
DIO_ErrorStatus DIO_TOGPortValue     (u8 u8PortId, u8 u8PortVal)
{
	DIO_ErrorStatus LOC_enumState = DIO_OK ;
	if (( u8PortId <= PORTD) )
	{
		/* Check on the Required PORT Number */
		switch (u8PortId)
		{
		case     PORTA: PORTA_REG =~u8PortVal; break;
		case     PORTB: PORTB_REG =~u8PortVal; break;
		case     PORTC: PORTC_REG =~u8PortVal; break;
		case     PORTD: PORTD_REG =~u8PortVal; break;
		default: LOC_enumState = DIO_NOK ;       break;
		}
	}
	else
	{
		LOC_enumState = DIO_NOK ;
	}
	return LOC_enumState ;

}
