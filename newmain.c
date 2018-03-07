// PIC18F4525 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled and controlled by software (SBOREN is enabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 10000000


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define lcd_clear() lcd_command(1)
#define lcd_origin() lcd_command(2)
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 40000000 // ii?aaaeaiea oaeoiaie ?anoiou  40 IAo  aey ooieoee __delay_ms
#endif
#define E_pulse_with 50 //aeeoaeuiinou oaeoiauo eiioeunia LCD a ien
#define LCD_E PORTDbits.RD3
#define LCD_RS PORTDbits.RD2
#define LCD_Data4 LATD // eieoeaeecaoey ii?oia D4-D7 LCD

void lcd_clk(void) /*aaia?aoey eiioeuna ia aoia EN*/
{
  LCD_E = 1;
  __delay_us(E_pulse_with);
  LCD_E = 0;
  __delay_us(E_pulse_with);
}
void lcd_command(unsigned char outbyte) /*ioi?aaeou eiiaiao (4-aeoiue ?a-?ei ?aaiou) */
{
  LCD_RS=0; //?a?ei ia?aaa?e eiiaiau
  LCD_Data4=(LCD_Data4&0x0f)|(outbyte&0xf0); // ioi?aaea noa?oeo ?aou?ao aeo
  lcd_clk();
  LCD_Data4=(LCD_Data4&0x0f)|((outbyte<<4)&0xf0); // ioi?aaea ieaaoeo ?a-ou?ao aeo
  lcd_clk();
  __delay_ms(1);
}
void lcd_putc(char outbyte) /* ioi?aaeou aaiiua (4-aeoiay iia?aoey) */
{
  LCD_RS=1; //?a?ei ia?aaa?e aaiiuo
  LCD_Data4=(LCD_Data4&0x0f)|(outbyte&0xf0);
  lcd_clk();
  LCD_Data4=(LCD_Data4&0x0f)|((outbyte<<4)&0xf0);
  lcd_clk();
}
void lcd_puts(unsigned char line,const char *p) // *auaia no?iee ia ye?ai*
{
	lcd_origin();         // ia?aoia e ioeaaiio aa?ano LCD
	lcd_command(line);			// onoaiiaeou aa?an LCD 00H
	while(*p)                  // i?iaa?eou, ?aaai ee oeacaoaeu 0
	{
	 lcd_putc(*p);             // ioi?aaeou aaiiua ia LCD
	 p++;                      // oaaee?eou aa?an ia 1
	}
}
void inttolcd(unsigned char posi, long value) //auaia ia ye?ai cia?aiee ia?a-iaiiuo
{
	char buff[16];
	ltoa(buff,value,10);
	lcd_puts(posi,buff);
}
void lcd_init() // eieoeaeecaoey LCD-aenieay
{
  TRISD &= 0x03;// ia?aaia auaiaia RD4-RD7a ?a?ei auoiaia
  LCD_Data4 &= 0b00001111;//onoaiiaea ioeae ia eeiee ia?aaa?e aaiiuo
  LCD_E=0;
  LCD_RS=0;
  __delay_ms(1);
/*eieoeaeecaoey aenieay*/
  LCD_Data4=(LCD_Data4&0x0f)|0x30;
  lcd_clk();
 __delay_ms(1);
  LCD_Data4=(LCD_Data4&0x0f)|0x30;
 lcd_clk();
__delay_ms(1);
  LCD_Data4=(LCD_Data4&0x0f)|0x30;
  lcd_clk();
  __delay_ms(1);
/*---------------------------------*/
  LCD_Data4=(LCD_Data4&0x0f)|0x20;	// ia?aee??eou ia 4-aeoiue ?a?ei ia-?a-aa?e
  lcd_clk();
  __delay_ms(1);
  lcd_command(0x28);//onoaiiaeou N=1, F=0 (aaa no?iee, ?acia? neiaiea 5*8 oi?ae
  lcd_command(0x01);	// i?enoeou an?
  lcd_command(0x06);	// aaoiiaoe?anee ia?aaaeioou eo?ni? iinea aaeoa
  lcd_command(0x0C);	// aenieae aee???i, eo?ni?a iao, ia ii?aaao
  lcd_command(0x02);	// ia?aeuiay iiceoey
  lcd_command(0x01);	// i?enoeou an? niiaa
}

volatile int h=0;
volatile long k=0;
volatile unsigned char u=0;

void motor_init() 
{ 
    TRISDbits.RD0=0; 
    TRISDbits.RD1=0; 
    TRISBbits.RB1=0; 
    TRISBbits.RB2=0; 
    TRISCbits.TRISC1=0; 
    TRISCbits.TRISC2=0; 
    CCP1CONbits.CCP1M=0b1100; //задаём режим работы модуля CCP1 (ШИМ) CCP1CONbits.P1M=0b00; //задействован только один вывод P1A 
    CCP2CONbits.CCP2M=0b1111; // задаём режим работы модуля CCP2(ШИМ) 
    CCPR1L=0; // задаём нулевую скважность CCPR2L=0; // задаём нулевую скважность 
    PR2=124;// задаём период ШИМ 
    T2CONbits.T2CKPS=0b00; //задаём предделитель модуля Timer2 равным 1 
    T2CONbits.TMR2ON=1;// включение модуля Timer2 
} 


void motor_a_change_Speed_A (signed char speed) 
 { 
    if (speed>0) // движение вперёд 
    { 
        CCPR1L=speed; 
        PORTDbits.RD0=0; 
        PORTDbits.RD1=1; 
    } 
    else if (speed<0) // движение назад 
    { 
        CCPR1L =speed; 
        PORTDbits.RD0=1; 
        PORTDbits.RD1=0; 
    } 
    else //остановка 
    { 
        CCPR1L=0; 
        PORTDbits.RD0=0;         
        PORTDbits.RD1=0; 
    }
} 
void motor_a_change_Speed_B (signed char speed) 
 { 
    if (speed>0) // движение вперёд 
    { 
        CCPR2L=speed; 
        PORTBbits.RB1=0; 
        PORTBbits.RB2=1; 
    } 
    else if (speed<0) // движение назад 
    { 
        CCPR2L =speed; 
        PORTBbits.RB1=1; 
        PORTBbits.RB2=0;  
    } 
    else //остановка 
    { 
        CCPR2L=0; 
        PORTBbits.RB1=0; 
        PORTBbits.RB2=0;  
    }
}

void Adc_init() 
    { 
    TRISA|=0b00101111; //перевод выводов RA0, RA1, RA2, RA3, RA5 в режим входов 
    TRISE|=0b00000111; //перевод выводов RE0, RE1, RE2 в режим входов 
    ADCON1bits.PCFG=0b0111; // конфигурация аналого-цифровых портов 
    ADCON1bits.VCFG=0b00; // опорное напряжение Vss Vdd 
    ADCON2bits.ACQT=0b111;// время преобразования 20 Tad 
    ADCON2bits.ADCS=0b110;// частота преобразования Fosc/64     
    ADCON2bits.ADFM=0;//левое смещение 
    ADCON0bits.ADON=1;   // модуль АЦП включен 
     } 
int read_Adc() 
{ 
    ADCON0bits.CHS=3; // выбор аналогового канала     
    ADCON0bits.GO_DONE=1; // запуск преобразования 
    while(ADCON0bits.GO_DONE==1);       
    return (ADRESH<<2)+(ADRESL>>6);//запись результата преобразования 
} 


void main(void) { 
    lcd_init();
    Adc_init();
    motor_init();
    motor_a_change_Speed_A(-100);
    motor_a_change_Speed_B(-100);
    while(1)
    {
        inttolcd(0x80,read_Adc());
        if(read_Adc() >300)
        {
            motor_a_change_Speed_A(0);
        }
        else
        {
            motor_a_change_Speed_A(-100);
        }
    } 
}    