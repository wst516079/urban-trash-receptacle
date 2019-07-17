/*
 * test.c
 *
 * Created: 2019/7/15 12:10:03
 * Author : 93441
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include "io.c"
#include <io.h>
#include "ISR.h"



char string[10];



int main(void)
{
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xBF; PORTD = 0X40;
    LCD_init();
    
    init();         //init timer1, prescale 1/8, set the positive edge as trigger
                    //allow timer1 overflow interrupt and capture interrupt
    
    asm("sei");
    /* Replace with your application code */
    while (1) 
    {
        
        trigger();    // trigger the sensor
        dtostrf(distance,3,2,string);          // change fixed point to string
        LCD_DisplayString(1,string);                       
        _delay_ms(1000);                                

    }
}

