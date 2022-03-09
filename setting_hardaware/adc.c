#include <xc.h>

void ADC_Initialize(void) {
    TRISA = 0xff;		// Set as input port
    ADCON1 = 0x0e;  	// Ref vtg is VDD & Configure pin as analog pin 
    // ADCON2 = 0x92;  	
    ADFM = 1 ;          // Right Justifie
//    ADCON2bits.ADCS = 7; // 
    ADCON2bits.ADCS = 0b000;    // A/D conversion clock 查表後設100(4MHZ < 5.71MHz)
    ADCON2bits.ACQT = 0b001;    // Tad = 1 微秒 Acquisition time 設4tad = 4 >2.4
//    ADCON0bits.ADON = 1;
//    ADCON2bits.ADFM = 1;        // right justfied
//    PIE1bits.ADIE = 1;          // Enable A/D Converter Interrupt Enable bit
//    PIR1bits.ADIF = 0;          // clear A/D Converter Interrupt Flag bit
//    INTCONbits.PEIE = 1;        // Enable peripheral interrupt
//    INTCONbits.GIE = 1;         // set GIE bit  (global interrupt enable bit)
    
    ADRESH=0;  			// Flush ADC output Register
    ADRESL=0;  
}

int ADC_Read(int channel)
{
    int digital;
    INTCONbits.GIE = 1;   
    ADCON0bits.CHS =  0x07; // Select Channe7
    ADCON0bits.GO = 1;
    ADCON0bits.ADON = 1;
    
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH*256) | (ADRESL);
    INTCONbits.GIE = 0;   
    return(digital);
}