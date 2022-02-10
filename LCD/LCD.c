/*********************************************************************/
/*************************** Header Files  ***************************/
/*********************************************************************/

#include "LCD.h"
#include "util/delay.h"

/*********************************************************************/
/*************************** Functions *******************************/
/*********************************************************************/

/***************************************************************************************/
/* Description! Apply initialization sequence for LCD module                           */
/* Input      ! LCD Name                                                               */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_Init(LCD_t LCD )
{
	/* Number Of Data Bit Used */
	switch(LCD.NumberDataBit)
	{
		case 8:
			DIO_SetPortDir(LCD.PortData,0xff); break;
		case 4:
			DIO_SetPortDir(LCD.PortData,0xf0); break;  //in case 4 data bit should use the Last 4 bits in port
		default: break;
	}
	DIO_SetPinDir (LCD.LCD_Control.PortControl,LCD.LCD_Control.RS,OUTPUT);
  //DIO_SetPinDir (LCD.LCD_Control.PortControl,LCD.LCD_Control.RW,OUTPUT);
    DIO_SetPinDir (LCD.LCD_Control.PortControl,LCD.LCD_Control.E ,OUTPUT);

	/* Delay 30ms to ensure the initialization of the LCD driver */
	_delay_ms (30);

	/* Number Of Data Bit Used */
	switch(LCD.NumberDataBit)
	{
		/* In Case 8 Bit Used For Data */
		case 8:
			/* Return Home  */
			LCD_WriteCommand(LCD , LCD_Home);
			_delay_ms (15);

			/* Function Set  */
			LCD_WriteCommand(LCD , LCD_FunctionSet8bit);
			_delay_ms (1);

			/* Display ON OFF Control */
			LCD_WriteCommand(LCD , LCD_DisplayOn);
			_delay_ms (1);

			/* Clear Display */
			LCD_WriteCommand(LCD , LCD_Clear);
			_delay_ms(15);

			/* Entry Mode Set  */
			LCD_WriteCommand(LCD , LCD_EntryMode);
			_delay_ms(2);

			break;

		/* In Case 4 Bit Used For Data */
		case 4:
			/* Return Home  */

			LCD_WriteCommand(LCD , LCD_Home);
			_delay_ms (15);

			/* Function Set  */
			LCD_WriteCommand(LCD , 0x02);
			LCD_WriteCommand(LCD , LCD_FunctionSet4bit);
			_delay_ms (1);

			/* Display ON OFF Control */
			LCD_WriteCommand(LCD , LCD_DisplayOn);
			_delay_ms (1);

			/* Clear Display */
			LCD_WriteCommand(LCD , LCD_Clear);
			_delay_ms(15);

			/* Entry Mode Set  */
			LCD_WriteCommand(LCD , LCD_EntryMode);
			_delay_ms(2);

			break;
	}

}

/***************************************************************************************/
/* Description! Interface to send the configuration commands to the LCD Driver         */
/* Input      ! LCD Name , Command number                                              */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteCommand(LCD_t LCD,u8 Command)
{
	/* Number Of Data Bit Used  */
	switch (LCD.NumberDataBit)
		{
		    /* In Case 8 Bit Used For Data */
			case 8:

				/* Set RS to LOW */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.RS,LOW);

				/* Set E to HIGH  */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

				/* Load Command on Data bus */
				DIO_SetPortValue(LCD.PortData,Command);

				/* Set E to LOW */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,LOW);

				/* Wait for E to settle */
				_delay_ms(5);

				/* Set E to HIGH */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

				/* Delay for 10ms to let the LCD execute command */
				_delay_ms (10);

				break;

			/* In Case 4 Bit Used For Data */
			case 4:

				for(s8 i=1;i>=0;i--)
				{
					/* Set RS to LOW */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.RS,LOW);

					/* Set E to HIGH  */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

					/* Load Command on Data bus */
					if (i)
					{
						u8 CommandFirst = (Command >>4);
						DIO_SetPortValue(LCD.PortData,(CommandFirst));

						/*
						DIO_SetPinValue(LCD.PortData,PIN4,(Command & 0x10));
						DIO_SetPinValue(LCD.PortData,PIN5,(Command & 0x20));
						DIO_SetPinValue(LCD.PortData,PIN6,(Command & 0x40));
						DIO_SetPinValue(LCD.PortData,PIN7,(Command & 0x80));
						 */
					}else
					{
						DIO_SetPortValue(LCD.PortData,(Command));
						/*
						DIO_SetPinValue(LCD.PortData,PIN4,(Command & 0x01));
						DIO_SetPinValue(LCD.PortData,PIN5,(Command & 0x02));
						DIO_SetPinValue(LCD.PortData,PIN6,(Command & 0x04));
						DIO_SetPinValue(LCD.PortData,PIN7,(Command & 0x08));
						 */
					}

					/* Set E to LOW */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,LOW);

					/* Wait for E to settle */
					_delay_ms(5);

					/* Set E to HIGH */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

					/* Delay for 10ms to let the LCD execute command */
					_delay_ms (10);

				}

				break;
			default: break;
		}
}

/***************************************************************************************/
/* Description! Interface to write character on LCD screen                             */
/* Input      ! LCD Name , Character Data                                              */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteData(LCD_t LCD,u8 Data)
{
	   /* Number Of Data Bit Used  */
		switch (LCD.NumberDataBit)
			{
			    /* In Case 8 Bit Used For Data */
				case 8:

					/* Set RS to High */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.RS,HIGH);

					/* Set E to HIGH  */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

					/* Load Command on Data bus */
					DIO_SetPortValue(LCD.PortData,Data);

					/* Set E to LOW */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,LOW);

					/* Wait for E to settle */
					_delay_ms(5);

					/* Set E to HIGH */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

					/* Delay for 10ms to let the LCD execute command */
					_delay_ms (10);

					break;

				/* In Case 4 Bit Used For Data */
				case 4:

					for(s8 i=1;i>=0;i--)
					{
						/* Set RS to High */
						DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.RS,HIGH);

						/* Set E to HIGH  */
						DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

						/* Load Command on Data bus */
						if (i)
						{
							u8 DataFirst = (Data >>4);
							DIO_SetPortValue(LCD.PortData,(DataFirst));
							/*
							DIO_SetPinValue(LCD.PortData,PIN4,(Data & 0x10));
							DIO_SetPinValue(LCD.PortData,PIN5,(Data & 0x20));
							DIO_SetPinValue(LCD.PortData,PIN6,(Data & 0x40));
							DIO_SetPinValue(LCD.PortData,PIN7,(Data & 0x80));
							*/
						}else
						{
							DIO_SetPortValue(LCD.PortData,(Data));
							/*
							DIO_SetPinValue(LCD.PortData,PIN4,(Data & 0x01));
							DIO_SetPinValue(LCD.PortData,PIN5,(Data & 0x02));
							DIO_SetPinValue(LCD.PortData,PIN6,(Data & 0x04));
							DIO_SetPinValue(LCD.PortData,PIN7,(Data & 0x08));
							 */
						}

						/* Set E to LOW */
						DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,LOW);

						/* Wait for E to settle */
						_delay_ms(5);

						/* Set E to HIGH */
						DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

						/* Delay for 10ms to let the LCD execute command */
						_delay_ms (10);

					}

					break;
				default: break;
			}


}

/***************************************************************************************/
/* Description! Interface to write string on LCD screen                                */
/* Input      ! LCD Name , Pointer to the string                                       */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteString(LCD_t LCD,u8* Astring)
{
	u8 index=0;
	while(Astring[index] != '\0')
	{
		/* Send one one Character to finish string */
		LCD_WriteData(LCD,Astring[index]);

		/* Increment index */
		index++;

		/* Delay for 5ms to let the LCD execute command */
		_delay_ms(5);
	}
}

/***************************************************************************************/
/* Description! Interface to Locate to write on LCD screen                             */
/* Input      ! LCD Name , Position of Row , Position of Column                        */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void Goto_X_Y (LCD_t LCD,u8 Row,u8 Column)
{
	if (Column <=16 && Column >0)
	{
		switch (Row)
		{
			case 1: LCD_WriteCommand(LCD,(Column | 0x80)); break;
			case 2: LCD_WriteCommand(LCD,((Column + 0x40) | 0x80)); break;
			default: break;
		}

	}
}

