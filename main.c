#include <xc.h>
#include "config.h"
#include "lcd.h"

#define _XTAL_FREQ 20000000

//array parameters
#define NUMBER_OF_STRING 4
#define MAX_STRING_SIZE 40

//pin definintions
#define CURSOR PORTBbits.RB7
#define STOP PORTBbits.RB0
#define START PORTCbits.RC0
#define INC PORTBbits.RB6

void loom_settings();
void dhoti_settings();
void reset();

void main(void)
{
    char arr[NUMBER_OF_STRING][MAX_STRING_SIZE] ={ "WELCOME", "1.LOOM SETTINGS", "2.DHOTI SETTINGS", "3.RESET" };
    LcdInit();
   __delay_ms(1000);
    while(1){ 
    int i =0;
    while(i<4){
        LcdDisplayString(1, 0, arr[i]);
        //__delay_ms(1000);
        if(CURSOR == 1){
            LcdClearDisplay();
            i = i+1;
            continue;}
        if(STOP == 1){
        switch(i){
            case 1:
                loom_settings();
                LcdClearDisplay();
                break;
            case 2:
                dhoti_settings();
                LcdClearDisplay();
                break;
            case 3:
                reset();
                LcdClearDisplay();
                break;
            default:
                LcdClearDisplay();
                LcdDisplayString(1,1,"INVALID OPTION");
                    __delay_ms(2000);
                LcdClearDisplay();
                break;
        }
    }
    

   //LcdDisplayString(2, 0, " MENU SETTINGS ");
   __delay_ms(1000);
   }
   //main module
}

}

void loom_settings(){
   LcdClearDisplay();
   while(START != 1){
   LcdDisplayString(1, 0, " W:0000 S:0000 ");
   LcdDisplayString(2, 0, " P:000 ");
   }
    
}

void dhoti_settings(){
   LcdClearDisplay();
   while(START != 1){
   LcdDisplayString(1, 0, "No of STEP : 00 ");
   }    
}

void reset(){
    LcdClearDisplay();
    while(START != 1){
        LcdDisplayString(1,0," WORKING ");
    }
}