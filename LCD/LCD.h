
#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "DIO.h"

/*********************************************************************/
/*************************** Definition *******************************/
/*********************************************************************/

#define LCD_Clear           0x01          // replace all characters with ASCII 'space'
#define LCD_Home            0x02          // return cursor to first position on first line
#define LCD_EntryMode       0x06          // shift cursor from left to right on read/write
#define LCD_DisplayOff      0x08          // turn display off
#define LCD_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define LCD_FunctionReset   0x30          // reset the LCD
#define LCD_FunctionSet8bit 0x3C          // 8-bit data, 2-line display, 5 x 7 font
#define LCD_FunctionSet4bit 0x2C          // 4-bit data, 2-line display, 5 x 7 font
#define LCD_SetCursor       0x80          // set cursor position

/*********************************************************************/
/*************************** Structures ******************************/
/*********************************************************************/

typedef struct {
	Port_t 		PortControl;
	PinNumber_t RS         ;
  //PinNumber_t RW         ;
    PinNumber_t E          ;
}LCD_Control_t;

typedef struct {
	Port_t 		  PortData   ;
	LCD_Control_t LCD_Control;
	u8 			  NumberDataBit;
}LCD_t;

/*********************************************************************/
/*************************** Functions *******************************/
/*********************************************************************/

void LCD_Init		 (LCD_t LCD 		   );
void LCD_WriteCommand(LCD_t LCD,u8  Command);
void LCD_WriteData   (LCD_t LCD,u8  Data   );
void LCD_WriteString (LCD_t LCD,u8* Astring);
void Goto_X_Y		 (LCD_t LCD,u8 Row,u8 Colume);

#endif /* HAL_LCD_LCD_H_ */
