#include <p18f4455.h>
#include <adc.h>
#include <delays.h>
#include <stdio.h>
#include <stdlib.h>

#define ldata PORTD      
#define rs PORTEbits.RE2                //conectarea pinului rs la pinul RE0
#define rw PORTEbits.RE0 				//conectarea pinului rw la pinul RE1 (unused)
#define en PORTEbits.RE1 				//conectarea pinului e la pinul RE2
unsigned float a,b,c,d;
int counter = 0;
int multi=0;
int Rez=0;
int n=1000;
int i=0;
char buffer[30];
int numere[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int numerepct[]={0b10111111,0b10000110,0b11011011,0b11001111,0b11100110,0x6D,0x7D,0x07,0x7F,0x6F};
int j=0;
unsigned char msg1[ ]="VOLTMETRU mV";
unsigned char msg2[ ]="";
unsigned char msgv[]=".";
unsigned char msg3[]="";
unsigned char msg4[]="MILIVOLTI";


void LCD_command(unsigned char value);   //trimiterea comenzilor la LCD
void lcddata(unsigned char value);       //trimiterea datelor afisate pe LCD
void msdelay(unsigned int itime);        //creearea intarzierii in milisecunde
void LCD_write_string(static char *str); //scrierea mesajelor pe LCD



void rutina_intrerupere(void);

#pragma code my_section = 0x008   //vector intrerupere

void intrerupere (void)
{
	_asm goto rutina_intrerupere _endasm

}
#pragma code

#pragma interrupt rutina_intrerupere

void main ()
{
PORTD=0;
LATD=0;
TRISD=0x00;
TRISB=0xFF;
TRISA=0x00;
LATA=0x00;
CMCON = 0X07 ;
TRISE=0X00;    

T0CON=0b00000011;
TMR0H=0x6D;
TMR0L=0x83;


TRISAbits.TRISA0=1;
ADCON1=0x0E;
ADCON0bits.CHS3=0;
ADCON0bits.CHS2=0;
ADCON0bits.CHS1=0;
ADCON0bits.CHS0=0;
ADCON2=0x15;
ADCON0bits.ADON=1;
LATAbits.LATA1=1;
//configurare sistem intreruperi

  //activare intr timer0
INTCONbits.TMR0IF=0;
RCONbits.IPEN=0;				//timer0 high
T0CONbits.TMR0ON=1;
INTCONbits.TMR0IE=1; 
INTCONbits.GIE=1;


LCD_command(0x38);   // 2 lines and 5×7 matrix
LCD_command(0x0F);  //	Display on, cursor blinking on
while(1)
{


LATD=numerepct[(int)a];
			LATAbits.LATA2=1;
			LATAbits.LATA5=0;
	
		LATD=numere[(int)b];
				LATAbits.LATA3=1;
				LATAbits.LATA2=0;

			LATD=numere[(int)c];	
					LATAbits.LATA4=1;
					LATAbits.LATA3=0;
					
				LATD=numere[(int)d];
					LATAbits.LATA5=1;
					LATAbits.LATA4=0;


}

}
void rutina_intrerupere () //definitia functiei de tratare a intreruperii
{
float tens;
int itens;

	LCD_command(0x01);  //Clear display screen
LCD_write_string(msg1); 
LCD_command(0XC0); //Force cursor to beginning (2nd line)




ADCON0bits.GO=1;
Rez=ReadADC();
Rez=(Rez>>6)&0x3ff;

tens=(float)(Rez*5)/1023;
tens=tens*1000;


itens=(int)tens;
//	if(PIR1bits.ADIF==1){
// PIR1bits.ADIF=0;
		a = itens/ 1000;   //mii
        b = ((itens/100)%10); //sute
        c = ((itens/10)%10);  //zeci
        d = (itens%10);  //unitati
		
itoa(itens,msg2);
LCD_write_string(msg2);

LCD_command(0X14); //Increment cursor (shift cursor to right)
LCD_command(0X14); //Increment cursor (shift cursor to right)


LCD_write_string(msg4);

			INTCONbits.TMR0IF=0;
			T0CONbits.TMR0ON=1;
	
}	



////trimiterea comenzilor la LCD
void LCD_command (unsigned char value)
{
ldata=value;     
rs=0;            
rw=0;
en=1;              
msdelay(1);
en=0;
}

//scrierea mesajelor pe LCD
void LCD_write_string(static char *str)
{
int i = 0;
while (str[i] != 0)
{
lcddata(str[i]);
msdelay(15);
i++;
}
}

//trimiterea datelor afisate pe LCD
void lcddata (unsigned char value)
{
ldata=value;  
rs=1;          
rw=0;
en=1;        
msdelay(1);
en=0;
}

//creearea intarzierii in milisecunde
void msdelay (unsigned int itime)
{
int k;
for(k=0;k<itime;k++)
	Delay100TCYx(2);
}
