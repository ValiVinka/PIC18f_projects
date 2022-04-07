#include <p18f4455.h>
#include <adc.h>
#include <delays.h>
#include <stdio.h>
#include <stdlib.h>
#include <usart.h>
#include <ctype.h>


#define ldata PORTD      
#define rs PORTEbits.RE2                //conectarea pinului rs la pinul RE0
#define rw PORTEbits.RE0 				//conectarea pinului rw la pinul RE1 (unused)
#define en PORTEbits.RE1 				//conectarea pinului e la pinul RE2
unsigned int a,b,c,d;
int counter = 0;
int multi=0;
int Rez=0;
char data='a';
char action[20];
char msg[2];
int n=1000;
int i=0;
char buffer;
int numere[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int numerepct[]={0b10111111,0b10000110,0b11011011,0b11001111,0b11100110,0x6D,0x7D,0x07,0x7F,0x6F};
int j=0;
unsigned char msg1[ ]="Numarator";
unsigned char msg2[ ]="RB3 apasat";
unsigned char msgv[]="Hello";
unsigned char msg3[]="RB3 apasat";
unsigned char msg4[]="RB4 apasat";
unsigned char msgs[]="Becuri stinse";
unsigned char msga[]="Becuri aprinse";
unsigned char msgunu[]="Numaru 1";


void LCD_command(unsigned char value);   //trimiterea comenzilor la LCD
void lcddata(unsigned char value);       //trimiterea datelor afisate pe LCD
void msdelay(unsigned int itime);        //creearea intarzierii in milisecunde
void LCD_write_string(static char *str); //scrierea mesajelor pe LCD

void config_serial(){
TXSTAbits.BRGH = 1;
BAUDCONbits.BRG16 = 0;
SPBRG=129;
TXSTA=0x22;
RCSTA=0x90;
BAUDCON=0x08;
}



void main ()
{
PORTD=0;
LATD=0;
TRISD=0x00;
TRISB=0xFF;
TRISA=0x00;
LATA=0x00;
CMCON = 0X07 ;
ADCON1=0x0F;
TRISE=0X00;    






baudUSART (BAUD_IDLE_TX_PIN_STATE_LOW &
 BAUD_8_BIT_RATE &
 BAUD_WAKEUP_OFF &
 BAUD_AUTO_OFF); 
OpenUSART (USART_TX_INT_OFF & 
USART_RX_INT_OFF & 
USART_ASYNCH_MODE & 
USART_EIGHT_BIT & 
USART_BRGH_HIGH, 
129); 

OpenUSART (USART_TX_INT_OFF & 
USART_RX_INT_OFF & 
USART_ASYNCH_MODE & 
USART_EIGHT_BIT & 
USART_BRGH_HIGH, 
129);
//RCONbits.IPEN=0;
//INTCONbits.TMR0IE=1;
//INTCONbits.GIE=1;
//INTCONbits.TMR0IF=0;
//T0CONbits.TMR0ON=1;
//PIE1bits.RCIE=1;
//PIE1bits.TXIE=1;

LCD_command(0x38);   // 2 lines and 5×7 matrix
LCD_command(0x0E);  //	Display on, cursor blinking off
LATAbits.LATA5=1;
LATD=0x00;
while(1){

//LCD_command(0x01);  //Clear display screen
//LCD_write_string(buffer);
//
//



if(TXSTAbits.TRMT==1){

	if(PORTBbits.RB3==0)
		printf("RB3 apasat");
		//Delay100TCYx(50);
			
	if(PORTBbits.RB4==0)
		printf("RB4 apasat");
}

	if(PIR1bits.RCIF==1){
    PIR1bits.RCIF=0;
	buffer = RCREG;



if(buffer=='clear'){
LCD_command(0x01);  //Clear display screen
   PIR1bits.RCIF=0;
}

if(buffer=='1'){
LCD_command(0x01);
LCD_write_string(msgunu);
LATD=numere[1];

//LCD_write_string(buffer);
}


if(buffer=='aprinde'){
LCD_command(0x01);
LCD_write_string(msga);
LATD=0xff;
}

if(buffer=='stinge'){
LCD_command(0x01);
LCD_write_string(msgs);
LATD=0x00;
}

if(buffer=='Hello'){
LCD_command(0x01);
LCD_write_string(msgv);
}

if(buffer=='numara')
{	LCD_command(0x01);
	LCD_write_string(msg1);
	for(i=0;i<10;i++){
	LATD=numere[i];
	Delay10KTCYx(50);
	}
	
}


}



//Delay10KTCYx(10);







}
}



void rutina_intrerupere () //definitia functiei de tratare a intreruperii
{

			
		
	
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
	Delay100TCYx(1);
}
