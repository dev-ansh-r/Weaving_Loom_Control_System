#include <xc.h>
#include "config.h"
#include "lcd.h"
#include "eeprom.h"

#include<stdio.h>
#include<math.h>

char arr[4][16] = {"WELCOME","1.LOOM SETTINGS","2.DHOTI SETTINGS","3.RESET SETTINGS"};
int loom_s, loom_w, loom_p, option;
int dhoti_steps;
int dhoti_values[60][4];

//unsigned char value1 = 100;
//unsigned char address = 0xF0;

#define _XTAL_FREQ 20000000

#define RS PORTDbits.RD2
#define EN PORTDbits.RD3
#define DATA_4 PORTDbits.RD4
#define DATA_5 PORTDbits.RD5
#define DATA_6 PORTDbits.RD6
#define DATA_7 PORTDbits.RD7

#define CURSOR PORTBbits.RB7
#define ENTER PORTBbits.RB0
#define BACK PORTCbits.RC0
#define INC PORTBbits.RB6

int main_menu();
int increment(int fixed, int count, unsigned char line ,unsigned char pos);
int increment_two(int fixed, int count, unsigned char line ,unsigned char pos);
int increment_one(int fixed, int count, unsigned char line ,unsigned char pos);
void enterdhoti_values(int steps);

void Loom_settings();
void Dothi_settings();
void Reset_settings();


void main(){ 
    LcdInit();
    int opt = main_menu();
    LcdClearDisplay();
    switch(opt+1){
        case 1:
                LcdDisplayString(1,0,"INVALID OPTION");
            break;
        case 2:
            Loom_settings();
            break;
        case 3:
            Dothi_settings();
            break;
        case 4:
            Reset_settings();
            break;
        default:
            LcdDisplayString(1,0,"INVALID OPTION");
            break;
        }
}

int main_menu(){
    while(1){
        LcdDisplayString(1,0,arr[option]);
        while(CURSOR == 0 ){
            if(ENTER == 1)
                return option;
        }   
        if(option < 3)    
            ++option;
        else
            option = 0;
        LcdClearDisplay();
    }
}

int increment(int fixed, int count, unsigned char line ,unsigned char pos){
   int dynamic ,displayy , i = 0;
   while(1){
        displayy = fixed + dynamic;
        LcdDisplayNumber(line,pos,displayy);
        while(INC == 0){
            if(CURSOR == 1){
                return fixed + dynamic;
            }
        }
        __delay_ms(10);
        if(i<9)
            i++;            
        else
            i=0;
        dynamic = (i * pow(10,count));
    }   
}

int increment_two(int fixed, int count, unsigned char line ,unsigned char pos){
   int dynamic ,displayy , i = 0;
   while(1){
        displayy = fixed + dynamic;
        LcdDisplaytwo(line,pos,displayy);
        while(INC == 0){
            if(CURSOR == 1){
                return fixed + dynamic;
            }
        }
        __delay_ms(10);
        if(i<9)
            i++;            
        else
            i=0;
        dynamic = (i * pow(10,count));
    }   
}

int increment_one(int fixed, int count, unsigned char line ,unsigned char pos){
   int dynamic ,displayy , i = 0;
   while(1){
        displayy = fixed + dynamic;
        LcdDisplaytwo(line, pos, displayy);
        while(INC == 0){
            if(CURSOR == 1){
                return fixed + dynamic;
            }
        }
        __delay_ms(10);
        if(i<9)
            i++;            
        else
            i=0;
        dynamic = (i * pow(10,count));
    }   
}

void Loom_settings(){
    LcdClearDisplay();
    int count = 3;
    LcdDisplayString(1, 0, "W:");
    LcdDisplayNumber(1,2,loom_w);
    LcdDisplayString(1,8,"S:");
    LcdDisplayNumber(1,10, loom_s);
    LcdDisplayString(2,0,"P:");
    LcdDisplayNumber(2,2,loom_p);
    for(int i=count;i>=0;--i){
        loom_w=ReadEEPROM16b(0x10);
        loom_w = increment(loom_w, i, 1,2);
    }
    for(int i=count;i>=0;--i){
        loom_s=ReadEEPROM16b(0x13);
        loom_s = increment(loom_s, i, 1,10);
    }
    for(int i=count;i>=0;--i){
        loom_p=ReadEEPROM16b(0x16);
        loom_p = increment(loom_p, i, 2,2);
    }
    while(BACK == 0){
        if(BACK == 1){
            WriteEeprom16B(0x10,loom_w);
            WriteEeprom16B(0x13,loom_s);
            WriteEeprom16B(0x16,loom_p);   
            main_menu();
        }
    }
    main_menu();
}





void Dothi_settings(){
    LcdDisplayString(1,0,"NO OF STEPS:");
    for(int k=1;k>=0;--k){
        dhoti_steps = increment_two(dhoti_steps, k, 1, 12);
        __delay_ms(10);
    }   
    LcdClearDisplay();
    if(dhoti_steps<=60)
        enterdhoti_values(dhoti_steps);
    else
        LcdDisplayString(1,0,"INVALID OPTION");
}


void Reset_settings(){
    /*int dhoti_f = 0;
    dhoti_f = increment_one(dhoti_f,0,1,9);
    while(BACK == 0){        
    }*/
}

void enterdhoti_values(int steps){
    for(int i=1;i<=steps;){
        LcdDisplaytwo(1,0,i);
        LcdDisplayString(1,2,":");
        LcdDisplayNumber(1,3,0);
        LcdDisplayString(1,7,"F:0N:0P:0");
        ++i;
        LcdDisplaytwo(2,0,i);
        LcdDisplayString(2,2,":");
        LcdDisplayNumber(2,3,0);
        LcdDisplayString(2,7,"F:0N:0P:0");
        for(int k=3;k>=0;--k)
            dhoti_values[i][0] = increment(dhoti_values[i][0],k,1,3);
        LcdDisplayString(1,7,"F:0N:0P:0");
        for(int k=3;k>=0;--k)
            dhoti_values[i][0] = increment(dhoti_values[i][0],k,2,3);
        
        while(BACK==0){
        if(BACK==1){
            WriteEEPROM(0x20,dhoti_values[i][0]);
        }
    }
    }
    
}
