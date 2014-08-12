/*****************************************************
Chip type               : ATmega32
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

#include <mega32.h>
#include <sleep.h>

int i=0;

// Timer 0 output compare interrupt service routine
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{
   i++;
   if(i==61)             
   {
      OCR0=0x09;                 
   }
   if(i==62)
   {
      PORTB.0 = ~PORTB.0;       //toggel pin 0 state.
      OCR0=0xFF;
      i=0;
   }
}

void main(void)
{

PORTB=0x00;     //set value of pin(0) to 0.
DDRB=0x01;      //pin(0)(led number D9) defined for output.

TCCR0=0x0C;     //initiate timer(0) for 31.250kHz clock frecuncy and CTC mode.
TCNT0=0x00;     //set timer(0) value register to 0x00.
OCR0=0xFF;      //set compare register to 0xFF.

TIMSK=0x02;     //enable timer(0) comper match interrupt. 

#asm("sei")     //enable  Golobal interrupts
sleep_enable();         //initiate sleep in power management unit.

while (1)
      {
        idle();     //disable cpu clock (first sleep mode).
      }
}
