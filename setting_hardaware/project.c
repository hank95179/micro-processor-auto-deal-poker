#include "setting_hardaware/uart.h"
#include "setting_hardaware/interrupt_manager.h"
#include <xc.h>
#include <pic18f4520.h>
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include"setting_hardaware/adc.h"
#define _XTAL_FREQ 500000
// using namespace std;

char str[20];
int degree=-90;
int step_size=0;
int poker_time = 13;
int time;
void Delay(int num)
{
    int i = 0;
    while(i<num)
        i++;
    return;
}

void __interrupt(high_priority) Hi_ISR(void)
{
    
////    UART_Write_Text("1<=n<=9:\r\n");
//    LATDbits.LATD0 ^= 1;
//    INTCONbits.INT0IF = 0;
}

void run(){
    ClearBuffer();
    char word[20];
    int n_step = 1;
    int now_state = 1;
    LATDbits.LD4 = 1;
    UART_Write_Text("  ");
    while(time > 0){
        int cur = PORTBbits.RB5;
        if(cur == 0){
            if(now_state == 1){
                time--;
            }
            LATDbits.LD4 = 0;
        }
        
        else{
            LATDbits.LD4 = 1;
             
        }
        if(RCIF){
            unsigned char c = RCREG;            
            if(c == 'e')
            {
                UART_Write(c);
                UART_Write_Text("return from run\r\n");
                LATDbits.LD4 = 0;
                return;
            }
        }
        now_state = cur;
        sprintf(word,"\b\b%2d",time);
        UART_Write_Text(word);
        
    }
     LATDbits.LD4 = 0;
}

void Mode_run(){
    char word[20];
    ClearBuffer();
    UART_Write_Text("  ");
    while(1){
        if(RCIF){
            unsigned char c = RCREG;            
            if(c == 'r')
            {
                UART_Write(c);
                break;
            }
        }
        sprintf(word, "\b\b%2d", time = (ADC_Read(7) * 15 / 1023));
        LATD = ADC_Read(7) * 15 / 1023;
        __delay_us(10000);
        UART_Write_Text(word);
    }
    run();
}

void Mode_run2(){
    char word[20];
    ClearBuffer();
    strcpy(word, GetString());
    time = atoi(word);
    run();
}

void Mode_detect(){
    ClearBuffer();
    UART_Write_Text("1<=n<=9:\r\n");
    char word[20];
    int n_step = 1;
    // LATAbits.LA3 = 1;
    while(1){
        strcpy(word , "");
        // strcpy(word, GetString());
        
        
        int digital;
        
        if (PORTAbits.RA3 == 0){
            LATDbits.LD0 = 1;
            UART_Write_Text("on");
        }
        
        else{
            // UART_Write_Text("w");
            LATDbits.LD0 = 0;
        }
        //else{
            // LATDbits.LD0 = 0;
        //}
        
        if(word[0] == 'e'){
            LATDbits.LD0 = 0;
            return;
        }
    }
}


void Mode_degree()
{
    return;
//    ClearBuffer();
//    UART_Write_Text("1<=n<=9:\r\n");
//    char word[20];
//    int n_step = 1;
//    while(1){
//        strcpy(word , "");
//        strcpy(word, GetString());
//        if(word[0] == 'e')
//            return;
//            
//        // CCPR1L = (char) 18;
//        
//        //sscanf(word , "%d" , &degree);
//        sscanf(word , "%d" , &n_step);
//    //    
//        step_size = (int) (180 / n_step);
//        
//        // CCPR1L = (unsigned char)(duty / 4);
//        // CCP1CONbits.DC1B = (unsigned char)(duty % 4);
//        
//        degree += step_size;
//        
//        if( degree > 90 ){
//            degree = 90;
//        }
//        unsigned char num = degree+90;
//        
//        num = num*14/180;
//        num = num + 4;
//        if(num<4)
//            num=4;
//        if(num > 18)
//                num=18;
//        
//        CCPR1L = num;
//    }
}
void Mode_turn(void){
    LATDbits.LD5 = 1;
    __delay_ms(4000);
    LATDbits.LD5 = 0;
    UART_Write_Text("return from turn\r\n");
    
}
void main(void) 
{    
    UART_Initialize();
    ADC_Initialize();
//    INTERRUPT_Initialize();
//    BSF		INTCON2 , RBPU
    INTCON2bits.RBPU = 1;
    TRISCbits.RC2 = 0;
    CCP1CON = 0b00001100;
    T2CON = 0b00000111;
    PR2 = 0x9b;
    //CCPR1L = 14;
    CCPR1L = 5;
    INTCONbits.INT0IF = 0;
    TRISB = 0b00111111;
    TRISD = 0;
    LATD = 0;
    
     TRISAbits.RA0 = 1;
//    TRISAbits.RA3 = 1;
//    TRISA = 1;
    
    // ADCON1bits.PCFG = 0b1011;
    
    //INTCONbits.GIE = 1;
    //RCONbits.IPEN = 1;
    //INTCONbits.INT0IE = 1;
    //INTCONbits.INT0IF = 0;
    //INTCON2bits.RBPU = 1;
    while(1) 
    {
        strcpy(str, GetString());
        if(strcmp(str , "motor")==0){ // Mode2
               // TODO     
//            Mode_motor();
        }
        else if (strcmp(str , "degree")==0)
            Mode_degree();
        else if (strcmp(str , "turn")==0)
            Mode_turn();
        else if (strcmp(str , "run")==0)
            Mode_run();
        else if (strcmp(str , "run2")==0)
            Mode_run2();
//        else if (strcmp(str , "detect")==0)
//            Mode_detect();
        else
            ClearBuffer();
    }
    return;
}