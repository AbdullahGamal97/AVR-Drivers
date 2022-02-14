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
		case Eight_Bit:
			DIO_SetPortDir(LCD.PortData,0xff); break;

		case Four_Bit:
			DIO_SetPinDir(LCD.PortData,LCD.Pin1,OUTPUT);
			DIO_SetPinDir(LCD.PortData,LCD.Pin2,OUTPUT);
			DIO_SetPinDir(LCD.PortData,LCD.Pin3,OUTPUT);
			DIO_SetPinDir(LCD.PortData,LCD.Pin4,OUTPUT);
			break;

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
		case Eight_Bit:
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
		case Four_Bit:

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



	switch (LCD.NumberDataBit)
	{
		/* In Case 8 Bit Used For Data */
		case Eight_Bit:
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
		case Four_Bit:

				/* Set RS to LOW */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.RS,LOW);

				/* Set E to HIGH */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

				/* Load Second Half Command on Data bus */
				DIO_SetPinValue(LCD.PortData,LCD.Pin1,((Command >>4) & 1));
				DIO_SetPinValue(LCD.PortData,LCD.Pin2,((Command >>5) & 1));
				DIO_SetPinValue(LCD.PortData,LCD.Pin3,((Command >>6) & 1));
				DIO_SetPinValue(LCD.PortData,LCD.Pin4,((Command >>7) & 1));

				/* Set E to LOW */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,LOW);

				/* Wait for E to settle */
				_delay_ms(2);

				/* Set E to HIGH */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);
				/* Wait for E to settle */
				_delay_ms(5);

				/* Set E to HIGH
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);*/

				/* Load First Half Command on Data bus */
				DIO_SetPinValue(LCD.PortData,LCD.Pin1,((Command >>0) & 1));
				DIO_SetPinValue(LCD.PortData,LCD.Pin2,((Command >>1) & 1));
				DIO_SetPinValue(LCD.PortData,LCD.Pin3,((Command >>2) & 1));
				DIO_SetPinValue(LCD.PortData,LCD.Pin4,((Command >>3) & 1));

				/* Set E to LOW */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,LOW);

				/* Wait for E to settle */
				_delay_ms(2);

				/* Set E to HIGH */
				DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

				/* Delay for 10ms to let the LCD execute command */
				_delay_ms (5);
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


	switch (LCD.NumberDataBit)
	{
		/* In Case 8 Bit Used For Data */
		case Eight_Bit:

					/* Set RS to HIGH */
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
					_delay_ms(5);
					break;

		/* In Case 4 Bit Used For Data */
		case Four_Bit:

					/* Set RS to HIGH */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.RS,HIGH);

					/* Set E to HIGH */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

					/* Load Second Half Data on Data bus */
					DIO_SetPinValue(LCD.PortData,LCD.Pin1,((Data >>4) & 1));
					DIO_SetPinValue(LCD.PortData,LCD.Pin2,((Data >>5) & 1));
					DIO_SetPinValue(LCD.PortData,LCD.Pin3,((Data >>6) & 1));
					DIO_SetPinValue(LCD.PortData,LCD.Pin4,((Data >>7) & 1));

					/* Set E to LOW */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,LOW);

					/* Wait for E to settle */
					_delay_ms(2);

					/* Set E to HIGH */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

					/* Wait for E to settle */
					_delay_ms(5);

					/* Set E to HIGH *
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);*/

					/* Load First Half Data on Data bus */
					DIO_SetPinValue(LCD.PortData,LCD.Pin1,((Data >>0) & 1));
					DIO_SetPinValue(LCD.PortData,LCD.Pin2,((Data >>1) & 1));
					DIO_SetPinValue(LCD.PortData,LCD.Pin3,((Data >>2) & 1));
					DIO_SetPinValue(LCD.PortData,LCD.Pin4,((Data >>3) & 1));

					/* Set E to LOW */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,LOW);

					/* Wait for E to settle */
					_delay_ms(2);

					/* Set E to HIGH */
					DIO_SetPinValue(LCD.LCD_Control.PortControl,LCD.LCD_Control.E,HIGH);

					/* Delay for 10ms to let the LCD execute command */
					_delay_ms (5);
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
/* Description! Interface to write character on LCD screen                             */
/* Input      ! LCD Name , Character Data                                              */
/* Output     ! Nothing                                                                */
/***************************************************************************************/
void LCD_WriteNumber(LCD_t LCD,u32 Number)
{
	u8 DigitalValue[10];
	u8 DigitalCounter = 9;

	if(Number == 0)
	{
		LCD_WriteData(LCD,'0');
	}

	while(Number != 0)
	{
		DigitalValue[ DigitalCounter ]= Number % 10;
		Number /=10;
		DigitalCounter--;
	}

	DigitalCounter++;

	for(; DigitalCounter <10 ; DigitalCounter++)
	{
		switch( DigitalValue[ DigitalCounter ] )
		{

			case 0: LCD_WriteData(LCD,'0'); break;
			case 1: LCD_WriteData(LCD,'1'); break;
			case 2: LCD_WriteData(LCD,'2'); break;
			case 3: LCD_WriteData(LCD,'3'); break;
			case 4: LCD_WriteData(LCD,'4'); break;
			case 5: LCD_WriteData(LCD,'5'); break;
			case 6: LCD_WriteData(LCD,'6'); break;
			case 7: LCD_WriteData(LCD,'7'); break;
			case 8: LCD_WriteData(LCD,'8'); break;
			case 9: LCD_WriteData(LCD,'9'); break;

		}
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

