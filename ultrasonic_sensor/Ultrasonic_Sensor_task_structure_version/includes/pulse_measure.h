/*
 * pulse_measure.h
 *
 * Created: 2019/7/17 11:06:17
 *  Author: 93441
 */ 


#ifndef PULSE_MEASURE_H_
#define PULSE_MEASURE_H_

#define echo (PIND & 0x40)
#define trigger (PINB & 0x01)
unsigned long signal_time = 0;
unsigned long output = 0;
char string[10];
unsigned char i = 0x00;
enum SM1_gen_pulse { SM1_gen};
int SMTick1_gen_pulse(int state) {
    switch(state){
        case SM1_gen:
        break;
        default:
        state = SM1_gen;
    }
    switch(state){
        case SM1_gen:
        PORTA = 0x00;
        _delay_us(2);
        PORTA = 0x01;
        _delay_us(10);
        PORTA = 0x00;
        break;
    }
    return state;
}
enum SM2_count_length { SM2_low, SM2_high};
int SMTick2_count_length(int state) {
    switch(state){
        case SM2_low:
        if (!echo)
        {
            state = SM2_low;
        }
        else if (echo)
        {
            state = SM2_high;
        }
        
        break;
        case SM2_high:
        if (!echo)
        {
            state = SM2_low;
        }
        else if (echo)
        {
            state = SM2_high;
        }
        
        break;
        default:
        state = SM2_low;
    }
    switch(state){
        case SM2_low:
        if (signal_time != 0)
        {
            output = signal_time;
            signal_time = 0;
        }
        break;
        case SM2_high:
        signal_time ++;
        break;
    }
    
    return state;
}
enum SM3_LCD { SM3_show, SM3_wait};
int SMTick3_LCD(int state) {
    switch(state){
        case SM3_wait:
        state = SM3_show;
        break;
        case SM3_show:
        break;
        default:
        state = SM3_wait;
    }
    switch(state){
        case SM3_wait:
        break;
        case SM3_show:
        sprintf(string,"%d",output/2);     //distance = output(ms)/1000*340(m/s)*(100)/2
        //sprintf(string,"%d",i);
        //char* string = "3.14";
        if (output != 0)
        {
            LCD_DisplayString(1,string);
        }
        

        break;
    }
    return state;
}




#endif /* PULSE_MEASURE_H_ */