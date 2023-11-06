#include "config.h"
#include "LCD_PORTD.h"
#include <xc.h>
#include "functions.h"


#define RED_pin TRISCbits.RC2 //red
#define GREEN_pin TRISCbits.RC1 //green
#define BLUE_pin TRISCbits.RC0 //blue
#define RED LATCbits.LC2 //red
#define GREEN LATCbits.LC1 //green
#define BLUE LATCbits.LC0 //blue

#define UP_BUTTON PORTBbits.RB0
#define DOWN_BUTTON PORTBbits.RB3
#define LEFT_BUTTON PORTBbits.RB1
#define RIGHT_BUTTON PORTBbits.RB2

#define ON 1
#define OFF 0
#define HI 1
#define LO 0

#define IN 1
#define OUT 0
#define LOW 0

unsigned int analogRead(char canal);
void configADC(char CHANNELS);
void configPWM1 (void);
void configPWM2 (void);
void configPWM3 (void);
void setDC1 (char x);
void setDC2 (char x);
void setDC3 (char x);

void myChars(void);
void delay(int a);
void configPorts(void);
void specialChars(void);
void configInterrupts(void);
void T0_1s(void);
void practicaInfusion(void);
void animateDrop(int speed);
void contar(void);
void programarTiempo(void);
void check4Buttons(void);
void heatingstatus(double temp);


char y = 0;
char contador = 0;
char bandera = OFF;
int speed = 0;
int espera = 100;
int x = 0;
char s_unit = '0';
char s_dec = '0';
char m_unit = '0';
char m_dec = '0';
char SETTING = 1;
char COUNT_END = 0;

char duty3;
char HiLo;
//double multiplier = _XTAL_FREQ/(PWM_FREQ*16.0*100.0);

#define _XTAL_FREQ 8000000      // PIC18F4550 internal oscillator frequency

#define PWM_FREQ 2500            // PWM frequency in Hz
#define DESIRED_TEMP 37     // Default desired temperature
#define SENSOR 0
#define DEGREE 223
int lec1;

void main(void) {
    OSCCON = 0x7F; //8MHz      // Start the oscillator
    iniLCD();
    LCDcommand(DispOn);
    configADC(1);
    
    BLUE_pin = OUT;
    GREEN_pin = OUT;
    RED_pin = OUT;
    unsigned int lect1;
    lec1 = analogRead(0);
    unsigned int lec1;
    double volts;
    double temp;
    LCDprint(11,"Temperature; ", 0); //imprime temperatura
    while(1){
        lec1 = analogRead(SENSOR);
        volts = 5.0*lec1/1023.0;
        temp = volts*10;
        heatingstatus(temp);
        MoveCursor(0,LINE_DOWN); //*
        LCDint(temp);
        LCDchar('.');
        temp = temp-(int)temp;
        temp*=100;
        LCDint(temp);
        LCDchar('.');
        LCDchar(DEGREE);
        LCDchar('C');
        LCDprint(5,"     ",0); //*
        __delay_ms(500);
    }
    return;
}
    

void heatingstatus(double temp) {
    if (temp < DESIRED_TEMP - 3) {
        RED = LOW; //blue
        GREEN = LOW;
        BLUE = HI;
    } else if (temp < DESIRED_TEMP +1) {
        RED = LOW; //green
        GREEN = HI;
        BLUE = LOW;
    } else if (temp < DESIRED_TEMP + 3) {
        RED = HI; // yellow
        GREEN = HI;
        BLUE = LOW;
    } else {
        RED = HI; // red
        GREEN = LOW;
        BLUE = LOW;
    }
}
