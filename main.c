/*
 * simple game.c
 *
 * Created: 5/27/2023 2:54:35 AM
 * Author : kamar salah
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "LCD driver.h"
#include "Keybad driver.h"
#define F_CPU 8000000UL
#include <util/delay.h>

volatile int flag1=0,flag2=0;

int main(void)
{
	 int x;
	 Keybad_vinit ();
	 LCD_vinit ();
	 timer_CTC_vinit_interrupt();
	 
	 LCD_vsend_sring ("3+?=8");
    
	 do
	 {
		 if (flag1>1000)
		 {
			 flag2=1; 
		 }
		 x=Keybad_u8check_press ();
	 }while (x==NOTBRESSED && flag2==0);
	 
	 if (x==NOTBRESSED)                        // not enter any number and throuhg 10sec
	 {
		 
	    LCD_vclear_screen ();
		LCD_vmove_cursor (2,4);
		LCD_vsend_sring ("Time over");
	 }
	 else if (x=='5')
	 {
		LCD_vclear_screen ();
		LCD_vmove_cursor (2,4);
		LCD_vsend_sring ("Well done");
	 }
	 else
	 {
		LCD_vclear_screen ();
		LCD_vmove_cursor (2,3);
		LCD_vsend_sring ("Wrong Answer");
	 }
		 
    
}

ISR (TIMER0_COMP_vect)
{
	flag1++;
}

