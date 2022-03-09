#ifndef _UART_H
#define _UART_H
      
#define _XTAL_FREQ 8000000

void UART_Initialize(void);
char * GetString();
void UART_Write(unsigned char data);
void UART_Check(unsigned char data);
void UART_Write_Text(char* text);
void ClearBuffer();
void MyusartRead();
void show_adc();

#endif