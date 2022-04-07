#include <p18f4455.h>
#include <adc.h>
#include <delays.h>
#include <stdio.h>
#include <stdlib.h>


#define cooler LATCbits.LATC2
#define heater PORTCbits.RC5

void adc_init(void)
{
  ADCON0=0x01;
  ADCON1=0x0B;
  ADCON2=0x01;
}



unsigned int adc_amostra(unsigned char canal)
{


    switch(canal)
    {
      case 0: 
        ADCON0=0x01;
        break;
      case 1: 
        ADCON0=0x05;
        break;
      case 2: 
        ADCON0=0x09;
        break;
    }
   

    ADCON0bits.GO=1;
    while(ADCON0bits.GO == 1);

   return ((((unsigned int)ADRESH)<<2)|(ADRESL>>6));
}



#define ldata PORTD      
#define rs PORTEbits.RE2                //conectarea pinului rs la pinul RE0
#define rw PORTEbits.RE0 				//conectarea pinului rw la pinul RE1 (unused)
#define en PORTEbits.RE1 				//conectarea pinului e la pinul RE2
unsigned float a,b,c,d;
int counter = 0;
int multi=0;
int flag=0;
int Rez=0;
int n=1000;
int temp=0;
float tens;
int itens;
int i=0;
int status=0;
char buffer[30];
int numere[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int numerepct[]={0b10111111,0b10000110,0b11011011,0b11001111,0b11100110,0x6D,0x7D,0x07,0x7F,0x6F};
int j=0;
unsigned char msg1[ ]=" APLICATIE";
unsigned char msg2[ ]=" OC PLACA ";
unsigned char msg3[]="APASA RB3";
unsigned char msg4[]="PENTRU A INCEPE!";
unsigned char msg5[]="INSERATI TIMP";
unsigned char msg6[]="|OC TEST|";
unsigned char msg7[]="RB3";
unsigned char msg8[]="----------------";
unsigned char msg9[]="PLS WAIT! RB4 AB";
unsigned char msg10[]="Done! RB3 redo";
unsigned char celsius="TEMP C";
unsigned char timp[]="";
unsigned char temps[]="";


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
TRISC = 0;
//ADCON1=0X0E; 
T0CON=0b00000011;
TMR0H=0x6D;
TMR0L=0x83;

ADCON1=0x0E;


//configurare sistem intreruperi

  //activare intr timer0



LCD_command(0x38);   // 2 lines and 5×7 matrix
LCD_command(0x0F);  //	Display on, cursor blinking on
LCD_write_string(msg1);
LCD_command(0XC0);
LCD_write_string(msg2);
msdelay(35000);
LCD_command(0x01); //clear
LCD_command(0X80); //Force cursor to beginning (1st line)
LCD_write_string(msg3);
LCD_command(0XC0);
LCD_write_string(msg4);
while(PORTBbits.RB3==1);
INTCONbits.TMR0IF=0;
RCONbits.IPEN=0;				//timer0 high
T0CONbits.TMR0ON=1;
INTCONbits.TMR0IE=1; 
INTCONbits.GIE=1;
TRISAbits.TRISA0=1;

ADCON0bits.CHS3=0;
ADCON0bits.CHS2=0;
ADCON0bits.CHS1=0;
ADCON0bits.CHS0=0;
ADCON2=0x15;
ADCON0bits.ADON=1;


while(1)
{
	while(itens>=0 && status==1){
	LATD=numere[(int)a];
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

}
void rutina_intrerupere () //definitia functiei de tratare a intreruperii
{	
			TRISA=0x07;
			adc_init();
			;
			Rez=(adc_amostra(0)*10)/2;
					tens=(float)(Rez*5)/512;
		tens=(tens*1000)/83.33;


	
	
	if(status==0){
			itens=(int)tens/10;
			itoa(itens,timp);
			LCD_command(0x01);//clear
			LCD_command(0X80);//Force cursor to beginning (1st line)
			LCD_write_string(msg5);
			LCD_command(0XC0); //Force cursor to beginning (2nd line)
			LCD_write_string(msg7);
			LCD_command(0X14); //Increment cursor (shift cursor to right)
			LCD_write_string(msg6);
				LCD_command(0X14); //Increment cursor (shift cursor to right)
			LCD_write_string(timp);
		
			if(PORTBbits.RB3==0)
					{
				
				status=1;
			
		}
	}
	
	if(status==1){
	
	heater=1;
	if(flag==0)
	cooler=0;
	
	temp=(adc_amostra(2)*10)/2;
	temp=temp/10;
	itoa(temp,temps);
	
		
	if(PORTBbits.RB5==0)
		cooler=1;
		if(temp>50)
			{
				flag=1;
			}
		if(flag==1)
{
	cooler=1;
		if(temp<40)
			flag=0;
}
			
		
		LCD_command(0x01);//clear
	LCD_command(0X80);//Force cursor to beginning (1st line)
LCD_write_string(celsius);
	LCD_command(0X14); //Increment cursor (shift cursor to right)
	LCD_command(0X14); //Increment cursor (shift cursor to right)
	LCD_write_string(temps);
	
	LCD_command(0XC0); //Force cursor to beginning (2nd line)
	LCD_write_string(msg9);
			a = itens/ 1000;   //mii
        	b = ((itens/100)%10); //sute
        	c = ((itens/10)%10);  //zeci
        	d = (itens%10);  //unitati
			itens--;
			if(itens==0 || PORTBbits.RB4==0)
			{
				status=2;	
}
}

		if(status==2)
{
	if(PORTBbits.RB3==0)
					status=0;
		heater=0;
		cooler=1;
			LATD=0xff;
				LATAbits.LATA2=1;
					LATAbits.LATA3=1;
						LATAbits.LATA4=1;
							LATAbits.LATA5=1;
			msdelay(5000);
			LATAbits.LATA2=0;
					LATAbits.LATA3=0;
						LATAbits.LATA4=0;
							LATAbits.LATA5=0;
									LCD_command(0x01);//clear
			LCD_command(0X80);//Force cursor to beginning (1st line)
			LCD_write_string(msg10);
				if(PORTBbits.RB3==0)
					status=0;
		
}	
				//end
			
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
msdelay(1);
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
