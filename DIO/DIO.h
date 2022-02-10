
#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

/*****************************************************************/
/*************************** DIO REG *****************************/
/*****************************************************************/
#define DDRA_REG    *((volatile u8 *) 0x3B)
#define PORTA_REG   *((volatile u8 *) 0x3A)
#define PINA_REG    *((volatile u8 *) 0x39)

#define DDRB_REG    *((volatile u8 *) 0x37)
#define PORTB_REG   *((volatile u8 *) 0x38)
#define PINB_REG    *((volatile u8 *) 0x36)

#define DDRC_REG    *((volatile u8 *) 0x34)
#define PORTC_REG   *((volatile u8 *) 0x35)
#define PINC_REG    *((volatile u8 *) 0x33)

#define DDRD_REG    *((volatile u8 *) 0x31)
#define PORTD_REG   *((volatile u8 *) 0x32)
#define PIND_REG    *((volatile u8 *) 0x30)

/*********************************************************************/
/*************************** Header Files  ***************************/
/*********************************************************************/
#include "STD_TYPES.h"

//// PIN Direction ////
typedef enum
{
	INPUT  = 0,
	OUTPUT	  ,
}PinDir_t;

//// PIN OUTPUT ////
typedef enum
{
	LOW = 0,
	HIGH   ,
}PinLevel_t;

//// PIN INPUT PULL ////
typedef enum
{
	PULLDOWN = 0,
	PULLUP		,
}PinPull_t;

//// Port Defines ////
typedef enum{
	PORTA = 0,
	PORTB	 ,
	PORTC	 ,
	PORTD 	 ,
}Port_t;

//// PIN Defines ////
typedef enum{
	PIN0 =  0,
	PIN1	 ,
	PIN2	 ,
	PIN3	 ,
	PIN4	 ,
	PIN5	 ,
	PIN6	 ,
	PIN7	 ,
}PinNumber_t;

/*********************************************************************/
/*************************** Functions *******************************/
/*********************************************************************/

void DIO_SetPinDir	 (Port_t PortID, PinNumber_t PinNum , PinDir_t PinDir);

void DIO_SetPinValue 	 (Port_t PortID, PinNumber_t PinNum , PinLevel_t PinLevel);

u8   DIO_GetPinValue 	 (Port_t PortID, PinNumber_t PinNum);

void DIO_SetPortDir	 (Port_t PortID, u8 PortDir);

void DIO_SetPortValue    (Port_t PortID, u8 PortValue);

u8   DIO_GetPortValue    (Port_t PortID);

#endif /* MCAL_DIO_DIO_H_ */
