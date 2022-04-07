#include "p18f4455.h"
#include "delays.h"
#include "pwm.h"
 
void do_jos()
{
	OpenPWM1(238);
	SetDCPWM1(477);
	PORTB=0b00000001;
}
void re()
{
	OpenPWM1(211);
	SetDCPWM1(425);
	PORTB=0b00000010;
}
void mi()
{
	OpenPWM1(191);
	SetDCPWM1(379);
	PORTB=0b00000100;
}
void fa()
{
	OpenPWM1(179);
	SetDCPWM1(358);
	PORTB=0b00001000;
}
void sol()
{
	OpenPWM1(160);
	SetDCPWM1(319);
	PORTB=0b00010000;	
}
void la()
{
	OpenPWM1(142);
	SetDCPWM1(284);
	PORTB=0b00100000;
}
void si()
{
	OpenPWM1(127);
	SetDCPWM1(253);
	PORTB=0b01000000;
}
void do_sus()
{
	OpenPWM1(120);
	SetDCPWM1(239);
	PORTB=0b10000000;
}



void melodie(){
ClosePWM1();
	mi();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
	fa();
	Delay10KTCYx(30);
	sol();
	Delay10KTCYx(30);
	sol();
	Delay10KTCYx(30);
	fa();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
	re();
	Delay10KTCYx(30);
	do_jos();
	Delay10KTCYx(30);
	do_jos();
	Delay10KTCYx(30);
	re();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
	re();
	Delay10KTCYx(30);
	re();
	Delay10KTCYx(60);
	mi();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
	fa();
	Delay10KTCYx(30);
	sol();
	Delay10KTCYx(30);
	fa();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
		re();
	Delay10KTCYx(30);
	do_jos();
	Delay10KTCYx(30);
		do_jos();
	Delay10KTCYx(30);
	re();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
		re();
	Delay10KTCYx(30);
	do_jos();
	Delay10KTCYx(30);
		do_jos();
	Delay10KTCYx(60);
	ClosePWM1();



}

void melodie2()
{
	ClosePWM1();
	mi();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
	mi();
	Delay10KTCYx(30);
	do_jos();
	Delay10KTCYx(15);
	fa();
	Delay10KTCYx(15);
	
	mi();
	Delay10KTCYx(30);
	do_jos();
	Delay10KTCYx(15);
	fa();
	Delay10KTCYx(15);
	mi();
	Delay10KTCYx(60);

	la();
	Delay10KTCYx(30);
	la();
	Delay10KTCYx(30);
	la();
	Delay10KTCYx(30);
		si();
	Delay10KTCYx(15);
	fa();
	Delay10KTCYx(15);
	
	mi();
	Delay10KTCYx(30);
	do_jos();
	Delay10KTCYx(15);
	fa();
	Delay10KTCYx(15);
	mi();
	Delay10KTCYx(60);
	ClosePWM1();


}
 void main()
 {
	 PORTD=0;
	 LATD=0;
	 TRISD=0b00000011;
	 
	 PORTB=0;
	 LATB=0;
	 TRISB=0b00000000;
	 
	 PORTC=0;
	 LATC=0;
	 TRISC=0b00000101;
	 
	 	INTCON = 0X90 ;
CMCON = 0X07 ;
ADCON1=0x0F;
		


	 TRISCbits.TRISC2=0;
	 T2CONbits.TMR2ON=0;
	 T2CONbits.T2CKPS0=1;
	 T2CONbits.TMR2ON=1;
	 
	 OSCCONbits.IRCF2=1;
	 OSCCONbits.IRCF1=1;
	 OSCCONbits.IRCF0=0;
	 OSCCONbits.SCS1=1;
	 
	 LATCbits.LATC1=1;

	 while(1)
		  {
		
		if(PORTDbits.RD0==0){
	ClosePWM1();
	melodie();}
	if(PORTDbits.RD1==0){
	ClosePWM1();
	melodie2();
;}

if(PORTDbits.RD0==0 && PORTDbits.RD1==0){
ClosePWM1();
	mi();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	fa();
	Delay10KTCYx(50);
	sol();
	Delay10KTCYx(50);
	sol();
	Delay10KTCYx(50);
	fa();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(50);
	do_jos();
	Delay10KTCYx(50);
	do_jos();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(100);
	mi();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	fa();
	Delay10KTCYx(50);
	sol();
	Delay10KTCYx(50);
	fa();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
		re();
	Delay10KTCYx(50);
	do_jos();
	Delay10KTCYx(50);
		do_jos();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
		re();
	Delay10KTCYx(50);
	do_jos();
	Delay10KTCYx(50);
		do_jos();
	Delay10KTCYx(100);
	ClosePWM1();



}


if(PORTDbits.RD0==1 && PORTDbits.RD1==1){
	ClosePWM1();
	mi();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	fa();
	Delay10KTCYx(50);
	sol();
	Delay10KTCYx(50);
	sol();
	Delay10KTCYx(50);
	fa();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(50);
	do_jos();
	Delay10KTCYx(50);
	do_jos();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(100);
	mi();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
	fa();
	Delay10KTCYx(50);
	sol();
	Delay10KTCYx(50);
	fa();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
		re();
	Delay10KTCYx(50);
	do_jos();
	Delay10KTCYx(50);
		do_jos();
	Delay10KTCYx(50);
	re();
	Delay10KTCYx(50);
	mi();
	Delay10KTCYx(50);
		re();
	Delay10KTCYx(50);
	do_jos();
	Delay10KTCYx(50);
		do_jos();
	Delay10KTCYx(100);
	ClosePWM1();
}

		
}


	}
		 
		 
	 
 