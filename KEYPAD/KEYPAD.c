/*********************************************************************/
/*************************** Header Files  ***************************/
/*********************************************************************/
#include "KEYPAD.h"
#include "util/delay.h"
/*********************************************************************/
/*************************** Functions *******************************/
/*********************************************************************/

/*********************************************************************/
/*************************** Keypad Keys *****************************/
/*********************************************************************/
u8 ArrayKeypad[4][4]={
							{'1','2','3','+'},
							{'4','5','6','-'},
							{'7','8','9','*'},
							{'=','0','.','/'},
					 };


/*********************************************************************/
/* Description! Apply initialization sequence for Keypad module      */
/* Input      ! Keypad Name                                          */
/* Output     ! Nothing                                              */
/*********************************************************************/
void Keypad_Init(Keypad_t Keypad)
{
	/*	set upper 4 pins as output
	 * 	set lower 4 pin as input
     */
	DIO_SetPortDir(Keypad.PortControl,0x0F);

	/*	set upper 4 pins as HIGH
	 * 	set lower 4 pin as Internal Pullup
	 */
	DIO_SetPortValue(Keypad.PortControl,0xFF);
}

/*********************************************************************/
/* Description! Get Press Key for Keypad module                      */
/* Input      ! Keypad Name                                          */
/* Output     ! value of Press Key                                   */
/*********************************************************************/
u8 Keypad_GetPressKey (Keypad_t Keypad)
{
	for (u8 row =0; row < Keypad.Row_N; row++)
	{
		DIO_SetPortValue(Keypad.PortControl,(~(0x01<<row)));
		
		for (u8 column =0; column < Keypad.Column_N; column++)
		{
			if (DIO_GetPinValue(Keypad.PortControl,(column+4))==0)
			{
				return ArrayKeypad[row][column];
			}
			_delay_ms(2);
		}
	}
	return 0;
}
