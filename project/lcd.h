//lcd.h

unsigned char LCD_rCommand(void);
char LCD_BusyCheck(unsigned char temp);
void LCD_wCommand(char cmd);
void LCD_wBCommand(char cmd);
void LCD_Init(void);
void LCD_wData(char dat);
void LCD_wString(char *str);
