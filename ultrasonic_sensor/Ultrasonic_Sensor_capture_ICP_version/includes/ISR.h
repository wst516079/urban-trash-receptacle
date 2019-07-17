/*
 * ISR.h
 *
 * Created: 2019/7/15 13:24:24
 *  Author: 93441
 */ 


#ifndef ISR_H_
#define ISR_H_

#define ICP1 (PIND & 0x40)                    //ICP1 on atmega1284 is D6
unsigned char ov_counter;
unsigned int rising_edge,falling_edge;
unsigned long pulse_clocks;
double distance;

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b){
    return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}

void init(){
	TCCR1B=0x42; //init timer1, prescale 1/8, set the positive edge as trigger
    
    TIMSK1=0x21; //allow timer1 overflow interrupt and capture interrupt
}
void trigger(){
		PORTA = 0x00;    // trigger the sensor
        _delay_us(2);
        PORTA = 0x01;
        _delay_us(10);
        PORTA = 0x00;
}


ISR(_VECTOR(15))               //overflow interrupt
{
    ov_counter++; 

}


ISR(_VECTOR(12))                 // Input Capture Interrupt
{
    if (ICP1)
    { 
        rising_edge = ICR1;                                     //save the positive Edge         
        TCCR1B = SetBit(TCCR1B,6,0);                            //set the negative edge as trigger
        ov_counter = 0;                                   //set overflow counter to 0
        
    }
    else
    { 
        falling_edge = ICR1;                         //save the negative Edge
        TCCR1B = SetBit(TCCR1B,6,1);                           //set the positive edge as trigger
        pulse_clocks = (unsigned long)falling_edge - (unsigned long)rising_edge + (unsigned long)ov_counter * 16 / 1000; //calculate the pulse width [number of pulse between positive and negative edge, plus number of overflow multiplied by bit wide then divided by the number of pulse in one millisecond]
		distance = pulse_clocks * 0.017;
	}

}




#endif /* ISR_H_ */