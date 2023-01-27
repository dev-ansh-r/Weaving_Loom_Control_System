#ifndef XC_HEADER_CONFIG_H
#define	XC_HEADER_CONFIG_H

#include <xc.h> 

// PIC18F46K22 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config FOSC = HSHP      // Oscillator Selection bits (HS oscillator (high power > 16 MHz))
#pragma config PLLCFG = OFF     // 4X PLL Enable (Oscillator used directly)
#pragma config PRICLKEN = ON    // Primary clock enable bit (Primary clock is always enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal/External Oscillator Switchover bit (Oscillator Switchover mode enabled)

// CONFIG2L
#pragma config PWRTEN = ON      // Power-up Timer Enable bit (Power up timer enabled)
#pragma config BOREN = OFF       // Brown-out Reset Enable bits (Brown-out Reset enabled and controlled by software (SBOREN is enabled))
#pragma config BORV = 150       // Brown Out Reset Voltage bits (VBOR set to 1.5 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits (Watch dog timer is always disabled. SWDTEN has no effect.)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = OFF     // HFINTOSC Fast Start-up (HFINTOSC output and ready status are delayed by the oscillator stable status)
#pragma config T3CMX = PORTB5   // Timer3 Clock input mux bit (T3CKI is on RB5)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

#define PULSE_SECTOR                        2  // 2 byte
#define DHOTI_SETTING_TOTAL_COUNT_SECTOR    4  // 1 byte
#define DHOTI_SETTING_CURRENT_COUNT_SECTOR  5  // 1 byte
#define SINGLE_PICK_SECTOR                  6  // 2 byte
#define WEFT_TIMING_SECTOR                  8  // 2 byte
#define ANTI_WEFT_TIMING_SECTOR             10  // 2 byte
#define RELAY_1_TIMING_SECTOR               12  // 2 byte
#define RELAY_2_TIMING_SECTOR               14  // 2 byte
#define METER_SETTING_SECTOR                16  // 2 byte
#define METER_PULSE_SECTOR                  18  // 2 byte
#define PNEUMATIC_SENSOR_SECTOR             20  // 1 byte
#define METER_COUNT_SECTOR                  21  // 2 byte
#define WEFT_HIGH_LOW_TIMEOUT               23  // 1 byte
#define SINGLE_PICK_NO_SENSE_TIMEOUT        24  // 1 byte
#define COIL_SENSEOR_SECTOR                 25  // 1 byte
#define DHOTI_SEETING_SECTOR                26  // 

#define MAX_SETTING_COUNT                   99

typedef enum
{
    SYSTEM_HALTED,
    SYSTEM_RUNNING,
    SYSTEM_PRE_BREAK,
    SYSTEM_BREAK,
    SYSTEM_FORWARD_PICK,
    SYSTEM_REVERSE_PICK,
    SYSTEM_SINGLE_PICK,
    SYSTEM_SETTING      
}eSystemState_t;

typedef enum
{
    NO_DELAY = 0X00,
    BREAK_DELAY = 0X01,
    FORWARD_DELAY = 0X02,
    REVERSE_DELAY = 0X04
}eDelayType_t;

typedef enum
{
    LCD_REFRESH = 0,        
    LCD_RUNNING,
    LCD_STOPPED,
    LCD_PULSE_COUNT,        
    LCD_NO_PULSE,
    LCD_NO_WEFT,
    LCD_ANTI_WEFT,     
    LCD_DATA_SAVED,
    LCD_DATA_FORWARD,
    LCD_DATA_REVERSE,
    LCD_DATA_WARP,
    LCD_DATA_SINGLE_PICK,
    LCD_DATA_SETTINGS,
    LCD_DATA_PNEUMATIC,
}eLcdScreenState;

typedef struct
{
    unsigned short PulseCount;
    unsigned char OffCount;
    unsigned char OnCount;
    unsigned char SelectedReleay;
    unsigned char StopOrRun;
}DhotiSetting_t;

DhotiSetting_t __DhotiSetting_t[MAX_SETTING_COUNT];
unsigned char __TotalDhotiSettingCount = 0;
unsigned char __DhotiStepArrayIndex = 0;
volatile unsigned char  __PulseCount;
volatile unsigned char __PrevPulseState = 0;
volatile unsigned char __ms10TickPulse;

unsigned char __LoomStopped;
unsigned short __WeftTiming;
unsigned char __WeftHighOrLow;
unsigned short __SinglePickTiming;
unsigned char __SinglePickNoSensorTiming;
unsigned char __CoilSensor;
unsigned short __Relay1Timing;
unsigned short __Relay2Timing;
unsigned char __AntiWeftCount;
unsigned char __PneumaticSensor;
unsigned char __ProtectMultipleWrite;

volatile eSystemState_t __SystemState;
volatile unsigned short __DispPulseCount;
volatile unsigned short __StopPulseCount;

unsigned short __PulseTimeOut;
unsigned short __MeterPulseSettings;
volatile unsigned short __MeterPulseCount;
unsigned short  __MeterCount;
volatile unsigned short __RelayOnOffDelay;

eLcdScreenState __LcdScreenState;
eLcdScreenState __PrevLcdScreenState;
unsigned short __LcdDelay;
unsigned char __SubMenuState;
unsigned char __PneumaticIndex;

void DelayMs(unsigned short Delay);

void LcdMenuRefreshHandler( void );

void LcdMenuHandler( void );

void MenuHandleMainScreen( void );

void MenuEnterButtonHanling( void );

void MenuIncDhotiSetting( void );

void MenuDecDhotiSetting( void );

void MenuCursorPosHandling( void );

void MenuExitHandling( void );

void MenuUpdateIncDecScreen( void );

void MenuIncrementChar(void);
#endif	/* XC_HEADER_TEMPLATE_H */