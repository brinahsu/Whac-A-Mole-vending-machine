/*
 * File:   led.c
 * Author: sabrina
 *
 * Created on January 11, 2021, 5:05 PM
 */


#include <xc.h>
#include <pic18f4520.h>
#define _XTAL_FREQ 20000000
#pragma config OSC = INTIO67 // Oscillator Selection bits
#pragma config WDT = OFF     // Watchdog Timer Enable bit 
#pragma config PWRT = ON    // Power-up Enable bit
#pragma config BOREN = ON   // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF     // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF     // Data EEPROM　Memory Code Protection bit (Data EEPROM code protection off)  
#define seg_port LATD
#define speed 1 // Speed Range 10 to 1  10 = lowest , 1 = highest
#define steps 1000 // how much step it will take
#define clockwise 0 // clockwise direction macro
#define anti_clockwise 1 // anti clockwise direction macro
int score;
int mouse_number;
int is_fail;
void ms_delay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<50;j++);
}
/*void __interrupt(high_priority) Hi_ISR(void)
{
    INTCON3bits.INT1IF=0;
    initial();
    
    

}*/
void Afull_drive (char direction){
    if (direction == anti_clockwise){
        PORTA = 0b00000011;
        ms_delay(speed);
        PORTA = 0b00000110;
        ms_delay(speed);
        PORTA = 0b00001100;
        ms_delay(speed);
        PORTA = 0b00001001;
        ms_delay(speed);
        PORTA = 0b00000011;
        ms_delay(speed);
    }
    if (direction == clockwise){
        PORTA = 0b00001001;
        ms_delay(speed);
        PORTA = 0b00001100;
        ms_delay(speed);
        PORTA = 0b00000110;
        ms_delay(speed);
        PORTA = 0b00000011;
        ms_delay(speed);
        PORTA = 0b00001001;
        ms_delay(speed);
    }       
}
void Bfull_drive (char direction){
    if (direction == anti_clockwise){
        PORTB = 0b00001100;
        ms_delay(speed);
        PORTB = 0b00011000;
        ms_delay(speed);
        PORTB = 0b00110000;
        ms_delay(speed);
        PORTB = 0b00100100;
        ms_delay(speed);
        PORTB = 0b00001100;
        ms_delay(speed);
    }
    if (direction == clockwise){
        PORTB = 0b00100100;
        ms_delay(speed);
        PORTB = 0b00110000;
        ms_delay(speed);
        PORTB = 0b00011000;
        ms_delay(speed);
        PORTB = 0b00001100;
        ms_delay(speed);
        PORTB = 0b00100100;
        ms_delay(speed);
    }       
}
void Cfull_drive (char direction){
    if (direction == anti_clockwise){
        PORTC = 0b00110000;
        ms_delay(speed);
        PORTC = 0b01100000;
        ms_delay(speed);
        PORTC = 0b11000000;
        ms_delay(speed);
        PORTC = 0b10010000;
        ms_delay(speed);
        PORTC = 0b00110000;
        ms_delay(speed);
    }
    if (direction == clockwise){
        PORTC = 0b10010000;
        ms_delay(speed);
        PORTC = 0b11000000;
        ms_delay(speed);
        PORTC = 0b01100000;
        ms_delay(speed);
        PORTC = 0b00110000;
        ms_delay(speed);
        PORTC = 0b10010000;
        ms_delay(speed);
    }       
}
int choose_candy(){
    int which = 1;
    while(1){
        LATD = which;
        __delay_ms(10);
        if(PORTBbits.RB0 == 1){
            return which/2;
            //break;
        }
        which *= 2;
        if(which == 8){
            which = 1;
        } 
    }
    
}
void breathing(){
    
    return;
}
void initial(){
    ADCON1bits.PCFG=0b1111;
    TRISA = 0xF0;     // RA0~RA3: stepper motor ,RA4 RA6 RA7 Infrared Sensor  
    PORTA = 0x0F;
    TRISB = 0x01;     // PORT B0 as choose button ,PORTB1 as reset button
    PORTB = 0x3C;
    TRISC = 0x00;     // PORT B as output port
    PORTC = 0xF0;
    //LATC=0;
    TRISD = 0x80;
    TRISBbits.TRISB0=1;
    PORTBbits.RB0 = 0;
    LATD = 0x00;
    PORTDbits.RD7 = 0;
    //period = (PR2+1)*4*Tosc*(TMR2 prescaler) = (0xFA + 1) * 4 * 1µs * 16 = 16000µs ~= 16ms
    /*T2CONbits.TMR2ON=1;
    T2CONbits.T2CKPS=0b10;
    PR2=0xFA;
    CCP1CONbits.CCP1M=0b1100;*/
}

void candy(){
//void main(void) {
    initial();
    /*RCONbits.IPEN=1;
    INTCONbits.GIE=1;
    INTCON2bits.INTEDG1=1;
    INTCON3bits.INT1IP=1;
    INTCON3bits.INT1IE=1;
    INTCON3bits.INT1IF=0;*/
    int which = 1;
    /*while(1){
        if(PORTDbits.RD7==0){
            break;
        }
    }*/
    int a = choose_candy();
    
    if (a==0){
        while(PORTAbits.RA5==1){
        //while(1){
            Afull_drive(anti_clockwise);
        }
    }
    else if (a==1){
        while(PORTAbits.RA7==1){
        //while(1){
            Bfull_drive(anti_clockwise);
        }
    }
    else if (a==2){
        for(int i=0;i<steps;i++){
            Cfull_drive(anti_clockwise);
        }
    }
    //CCPR1L=50;
    //while(1){
        //breathing();
        /*if(PORTAbits.RA7==0){
            LATDbits.LATD3=1;
        }else{
            LATDbits.LATD3=0;
        }*/
        //duty cycle = (CCPR1L:CCP1CON<5:4>)*Tosc*(TMR2 prescaler) = (50*4 + 0b00) * 1µs * 16 ~=3200µs
        //CCPR1L+=10;
        //if (CCPR1L==300){
            //CCPR1L=50;
        //}
        //__delay_ms(5);
        
        
    //}
    return;
}
int seven_display(int n){
    switch(n){
        case 0:
            return 0xC0;
            break;
        case 1:
            return 0xF9;
            break;    
        case 2:
            return 0xA4;
            break;    
        case 3:
            return 0xB0;
            break;    
        case 4:
            return 0x99;
            break;    
        case 5:
            return 0x92;
            break;
        case 6:
            return 0x82;
            break;
        case 7:
            return 0xF8;
            break;
        case 8:
            return 0x80;
            break;
        case 9:
            return 0x90;
            break;
        case 10:  //F
            return 0x8E;
            break;
        case 11:  //A
            return 0x88;
            break;
        case 12:  //L
            return 0xC7;
            break;
        case 13:
            return 0x40; //0.
            break;
        case 14:
            return 0xff; //null
            break;
    }
}
int print(int t1, int t2, int s1, int s2, int mouse_number){  //將秒數和分數print到七段顯示器上
    PORTAbits.RA3 = 0;
    PORTAbits.RA4 = 0;
    PORTAbits.RA5 = 0;
    PORTAbits.RA6 = 0;
    LATB = 0x00;
    LATC = 0x00;
    seg_port = 0x00;
    if(mouse_number==1){  //上地鼠
        LATB = 0b00001011;
        LATC = 0b01000001;
        seg_port=seven_display(t1);
        PORTAbits.RA6 = 1;
        for(int i=0;i<50;i++);
        LATB = 0b00010000;
        LATC = 0b01100011;
        seg_port=seven_display(t2);
        PORTAbits.RA5 = 1;  
        PORTAbits.RA6 = 0;
        for(int i=0;i<50;i++);
        LATB = 0b00000100;
        LATC = 0b01010101;
        seg_port=seven_display(s1);
        PORTAbits.RA4 = 1;
        PORTAbits.RA5 = 0;
        for(int i=0;i<50;i++);
        seg_port=seven_display(s2);
        PORTAbits.RA3 = 1;
        PORTAbits.RA4 = 0;
        for(int i=0;i<50;i++){}
    }
    else if(mouse_number==2){  //下地鼠  
        LATB = 0b00101000;
        LATC = 0b11000001;
        seg_port=seven_display(t1);
        PORTAbits.RA6 = 1;
        for(int i=0;i<50;i++);
        LATB = 0b00000100;
        LATC = 0b01100011;
        seg_port=seven_display(t2);
        PORTAbits.RA5 = 1; 
        PORTAbits.RA6 = 0;
        for(int i=0;i<50;i++);
        LATB = 0b00010000;
        LATC = 0b01010101;
        seg_port=seven_display(s1);
        PORTAbits.RA4 = 1;
        PORTAbits.RA5 = 0;
        for(int i=0;i<50;i++);
        seg_port=seven_display(s2);
        PORTAbits.RA3 = 1;
        PORTAbits.RA4 = 0;
        for(int i=0;i<50;i++){}
    }
    else if(mouse_number==3){  //左地鼠
        LATB = 0b00111110;
        LATC = 0b01110100;
        seg_port=seven_display(t1);
        PORTAbits.RA6 = 1;
        for(int i=0;i<50;i++);
        LATB = 0b00011100;
        LATC = 0b01101111;
        seg_port=seven_display(t2);
        PORTAbits.RA5 = 1; 
        PORTAbits.RA6 = 0;
        for(int i=0;i<50;i++);
        LATB = 0b00101010;
        LATC = 0b01111011;
        seg_port=seven_display(s1);
        PORTAbits.RA4 = 1;
        PORTAbits.RA5 = 0;
        for(int i=0;i<50;i++);
        seg_port=seven_display(s2);
        PORTAbits.RA3 = 1;
        PORTAbits.RA4 = 0;
        for(int i=0;i<50;i++){}
    }
    else if(mouse_number==4){  //右地鼠
        LATB = 0b00111110;
        LATC = 0b00010111;
        seg_port=seven_display(t1);
        PORTAbits.RA6 = 1;
        for(int i=0;i<50;i++);
        LATB = 0b00011100;
        LATC = 0b01111011;
        seg_port=seven_display(t2);
        PORTAbits.RA5 = 1; 
        PORTAbits.RA6 = 0;
        for(int i=0;i<50;i++);
        LATB = 0b00101010;
        LATC = 0b01101111;
        seg_port=seven_display(s1);
        PORTAbits.RA4 = 1;
        PORTAbits.RA5 = 0;
        for(int i=0;i<50;i++);
        seg_port=seven_display(s2);
        PORTAbits.RA3 = 1;
        PORTAbits.RA4 = 0;
        for(int i=0;i<50;i++){}
    }   
    else if(mouse_number==0){  //沒地鼠
        seg_port=seven_display(t1);
        PORTAbits.RA6 = 1;
        for(int i=0;i<50;i++);
        seg_port=seven_display(t2);
        PORTAbits.RA5 = 1; 
        PORTAbits.RA6 = 0;
        for(int i=0;i<50;i++);
        seg_port=seven_display(s1);
        PORTAbits.RA4 = 1;
        PORTAbits.RA5 = 0;
        for(int i=0;i<50;i++);
        seg_port=seven_display(s2);
        PORTAbits.RA3 = 1;
        PORTAbits.RA4 = 0;
        for(int i=0;i<50;i++){}
    } 
}

int mouse(){  //地鼠
    mouse_number =(rand()%4+1);  //隨機產生某隻地鼠1-4
    return mouse_number;
}

int get_adc(int channel){ //x->channel=0 y->channel=1
    if(channel == 0){
        ADCON0 = 0b00000001;
    }
    else
        ADCON0 = 0b00000101;
    
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO_nDONE == 1);
    return ADRESH*256+ADRESL;
}

int joystick(){  //搖桿
    int x = get_adc(0);
    int y = get_adc(1);
    if(x < 300){ //左
        return 3;
    }
    else if(x > 600){ //右
        return 4;
    }
    else if(y < 300){  //上
        return 1;
    }
    else if(y > 600){ //下
        return 2;
    }
}

void game(){  //倒數計時15秒
    //if(PORTAbits.RA2 == 1){  //start
        score = 0;
        T0CON = 0x07;
        for(int j = 15; j > 0; j--){
            TMR0H = 0xfc;
            TMR0L = 0x3f;
            INTCONbits.TMR0IF = 0;
            T0CONbits.TMR0ON = 1;
            while(INTCONbits.TMR0IF != 1){
                int mo=mouse();
                print(j/10,j%10,score/10,score%10,mo);
                int add=0;
                int appear = (rand()%1500+500); 
                for(int i=0;i< appear ;i++){
                    //display_mouse(mo);
                    print(j/10,j%10,score/10,score%10,mo);
                    if(mo == joystick()){
                        print(j/10,j%10,score/10,score%10,mo);
                        add=1;
                        break;
                    }
                    if(INTCONbits.TMR0IF == 1)
                        break;
                } 
                LATB=0;
                LATC=0;
                score+=add;
                print(j/10,j%10,score/10,score%10,0);
                int space = rand()%3;
                for(int i=0; i<=space*100; i++){
                    if(INTCONbits.TMR0IF == 1){
                        space = 0;
                        break;
                    }
                    print(j/10,j%10,score/10,score%10,0);
                }   
            }; 
        }
        T0CONbits.TMR0ON = 0;    
        if(score>=10){
            is_fail = 0;
            PORTBbits.RB4=1;
            for(int i=0;i<300;i++)
                print(14,13,0,14,0);
           
        }
        else{
            for(int i=0;i<300;i++)
                print(10,11,1,12,0);
        }
        return;
    //}    
}

void main(void) {
//void test(){
    TRISA = 0b00000111;  //RA0-1 analog input, RA2 button, RA3-RA6 為7段顯示器0-3
    PORTA = 0x00;
    TRISB = 0;  //LED matrix
    LATB = 0b00000000;
    LATC = 0b01111111;  //LED matrix
    TRISC = 0;
    TRISD = 0x00; //RD0-RD7為七段顯示器a-g
    LATD = 0x00;
    ADRESH = 0b00000000;
    ADCON1 = 0b00001101;
    ADCON2 = 0b10010000;
    is_fail = 1;
    while(is_fail==1){
        if(PORTAbits.RA2 == 1){
            game();
        }
    }
    LATB = 0xff;
    LATC = 0x00;
    __delay_ms(50);
    candy();
    return;
}

