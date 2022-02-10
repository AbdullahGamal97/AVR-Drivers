/*********************************************************************/
/*************************** Header Files  ***************************/
/*********************************************************************/

#include "BIT_MATH.h"
#include "DIO.h"


/*********************************************************************/
/*************************** Functions *******************************/
/*********************************************************************/


/******************** Set Pin Direction Function *********************/

void DIO_SetPinDir(Port_t PortID, PinNumber_t PinNum, PinDir_t PinDir)
{
	if (PinDir == OUTPUT)
	{
		switch (PortID)
		{
			case PORTA:	SET_BIT(DDRA_REG, PinNum); break;

			case PORTB:	SET_BIT(DDRB_REG, PinNum); break;

			case PORTC:	SET_BIT(DDRC_REG, PinNum); break;

			case PORTD:	SET_BIT(DDRD_REG, PinNum); break;
		}
	} else if (PinDir == INPUT)
	{
		switch (PortID)
		{
			case PORTA:	CLR_BIT(DDRA_REG, PinNum); break;

			case PORTB:	CLR_BIT(DDRB_REG, PinNum); break;

			case PORTC:	CLR_BIT(DDRC_REG, PinNum); break;

			case PORTD:	CLR_BIT(DDRD_REG, PinNum); break;
		}
	} else
	{
		// error in Pin Direction input
	}
}

/******************** Set Pin Value Function ***********************/

void DIO_SetPinValue(Port_t PortID,PinNumber_t PinNum, PinLevel_t PinLevel)
{
	if (PinLevel == HIGH)
	{
		switch (PortID)
		{
			case PORTA:	SET_BIT(PORTA_REG, PinNum);	break;

			case PORTB:	SET_BIT(PORTB_REG, PinNum);	break;

			case PORTC:	SET_BIT(PORTC_REG, PinNum);	break;

			case PORTD:	SET_BIT(PORTD_REG, PinNum);	break;
		}
	} else if (PinLevel == LOW)
	{
		switch (PortID)
		{
			case PORTA:	CLR_BIT(PORTA_REG, PinNum);	break;

			case PORTB:	CLR_BIT(PORTB_REG, PinNum);	break;

			case PORTC:	CLR_BIT(PORTC_REG, PinNum);	break;

			case PORTD:	CLR_BIT(PORTD_REG, PinNum);	break;
		}
	} else
	{
		// error in Pin Value input
	}
}

/******************** Get Pin Value Function ***********************/

u8 DIO_GetPinValue(Port_t PortID,PinNumber_t PinNum)
{
	u8 Bit_return_val = 0;

	switch (PortID)
	{
		case PORTA:	Bit_return_val = GET_BIT(PINA_REG, PinNum);	break;

		case PORTB:	Bit_return_val = GET_BIT(PINB_REG, PinNum);	break;

		case PORTC:	Bit_return_val = GET_BIT(PINC_REG, PinNum);	break;

		case PORTD:	Bit_return_val = GET_BIT(PIND_REG, PinNum);	break;
	}
	return Bit_return_val;
}

/******************** Set Port Direction Function ***********************/

void DIO_SetPortDir(Port_t PortID, u8 PortDir)
{
	switch (PortID)
	{
		case PORTA:	DDRA_REG = PortDir;	break;

		case PORTB:	DDRB_REG = PortDir;	break;

		case PORTC:	DDRC_REG = PortDir;	break;

		case PORTD:	DDRD_REG = PortDir;	break;
	}
}

/******************** Set Port Value Function ***********************/

void DIO_SetPortValue(Port_t PortID, u8 PortValue)
{
	switch (PortID)
	{
		case PORTA:	PORTA_REG = PortValue;	break;

		case PORTB:	PORTB_REG = PortValue;	break;

		case PORTC:	PORTC_REG = PortValue;	break;

		case PORTD:	PORTD_REG = PortValue;	break;
	}
}

/******************** Get Port Value Function ***********************/

u8 DIO_GetPortValue(Port_t PortID)
{
	u8 val_return = 0;

	switch (PortID)
	{
		case PORTA:	val_return = PINA_REG;	break;

		case PORTB:	val_return = PINB_REG;	break;

		case PORTC:	val_return = PINC_REG;	break;

		case PORTD:	val_return = PIND_REG;	break;
	}

	return val_return;
}
