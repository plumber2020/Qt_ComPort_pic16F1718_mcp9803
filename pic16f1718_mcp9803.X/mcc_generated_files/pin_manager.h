/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16LF1718
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set MCP9803_OneShot aliases
#define MCP9803_OneShot_TRIS                 TRISBbits.TRISB4
#define MCP9803_OneShot_LAT                  LATBbits.LATB4
#define MCP9803_OneShot_PORT                 PORTBbits.RB4
#define MCP9803_OneShot_WPU                  WPUBbits.WPUB4
#define MCP9803_OneShot_OD                   ODCONBbits.ODB4
#define MCP9803_OneShot_ANS                  ANSELBbits.ANSB4
#define MCP9803_OneShot_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define MCP9803_OneShot_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define MCP9803_OneShot_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define MCP9803_OneShot_GetValue()           PORTBbits.RB4
#define MCP9803_OneShot_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define MCP9803_OneShot_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define MCP9803_OneShot_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define MCP9803_OneShot_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define MCP9803_OneShot_SetPushPull()        do { ODCONBbits.ODB4 = 0; } while(0)
#define MCP9803_OneShot_SetOpenDrain()       do { ODCONBbits.ODB4 = 1; } while(0)
#define MCP9803_OneShot_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define MCP9803_OneShot_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set FLAG aliases
#define FLAG_TRIS                 TRISBbits.TRISB7
#define FLAG_LAT                  LATBbits.LATB7
#define FLAG_PORT                 PORTBbits.RB7
#define FLAG_WPU                  WPUBbits.WPUB7
#define FLAG_OD                   ODCONBbits.ODB7
#define FLAG_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define FLAG_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define FLAG_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define FLAG_GetValue()           PORTBbits.RB7
#define FLAG_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define FLAG_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define FLAG_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define FLAG_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define FLAG_SetPushPull()        do { ODCONBbits.ODB7 = 0; } while(0)
#define FLAG_SetOpenDrain()       do { ODCONBbits.ODB7 = 1; } while(0)

// get/set MCP9803_A0 aliases
#define MCP9803_A0_TRIS                 TRISCbits.TRISC0
#define MCP9803_A0_LAT                  LATCbits.LATC0
#define MCP9803_A0_PORT                 PORTCbits.RC0
#define MCP9803_A0_WPU                  WPUCbits.WPUC0
#define MCP9803_A0_OD                   ODCONCbits.ODC0
#define MCP9803_A0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define MCP9803_A0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define MCP9803_A0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define MCP9803_A0_GetValue()           PORTCbits.RC0
#define MCP9803_A0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define MCP9803_A0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define MCP9803_A0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define MCP9803_A0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define MCP9803_A0_SetPushPull()        do { ODCONCbits.ODC0 = 0; } while(0)
#define MCP9803_A0_SetOpenDrain()       do { ODCONCbits.ODC0 = 1; } while(0)

// get/set MCP9803_A1 aliases
#define MCP9803_A1_TRIS                 TRISCbits.TRISC1
#define MCP9803_A1_LAT                  LATCbits.LATC1
#define MCP9803_A1_PORT                 PORTCbits.RC1
#define MCP9803_A1_WPU                  WPUCbits.WPUC1
#define MCP9803_A1_OD                   ODCONCbits.ODC1
#define MCP9803_A1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define MCP9803_A1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define MCP9803_A1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define MCP9803_A1_GetValue()           PORTCbits.RC1
#define MCP9803_A1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define MCP9803_A1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define MCP9803_A1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define MCP9803_A1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define MCP9803_A1_SetPushPull()        do { ODCONCbits.ODC1 = 0; } while(0)
#define MCP9803_A1_SetOpenDrain()       do { ODCONCbits.ODC1 = 1; } while(0)

// get/set MCP9803_A2 aliases
#define MCP9803_A2_TRIS                 TRISCbits.TRISC2
#define MCP9803_A2_LAT                  LATCbits.LATC2
#define MCP9803_A2_PORT                 PORTCbits.RC2
#define MCP9803_A2_WPU                  WPUCbits.WPUC2
#define MCP9803_A2_OD                   ODCONCbits.ODC2
#define MCP9803_A2_ANS                  ANSELCbits.ANSC2
#define MCP9803_A2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define MCP9803_A2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define MCP9803_A2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define MCP9803_A2_GetValue()           PORTCbits.RC2
#define MCP9803_A2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define MCP9803_A2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define MCP9803_A2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define MCP9803_A2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define MCP9803_A2_SetPushPull()        do { ODCONCbits.ODC2 = 0; } while(0)
#define MCP9803_A2_SetOpenDrain()       do { ODCONCbits.ODC2 = 1; } while(0)
#define MCP9803_A2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define MCP9803_A2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set MCP9803_Alert aliases
#define MCP9803_Alert_TRIS                 TRISCbits.TRISC5
#define MCP9803_Alert_LAT                  LATCbits.LATC5
#define MCP9803_Alert_PORT                 PORTCbits.RC5
#define MCP9803_Alert_WPU                  WPUCbits.WPUC5
#define MCP9803_Alert_OD                   ODCONCbits.ODC5
#define MCP9803_Alert_ANS                  ANSELCbits.ANSC5
#define MCP9803_Alert_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define MCP9803_Alert_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define MCP9803_Alert_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define MCP9803_Alert_GetValue()           PORTCbits.RC5
#define MCP9803_Alert_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define MCP9803_Alert_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define MCP9803_Alert_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define MCP9803_Alert_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define MCP9803_Alert_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define MCP9803_Alert_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)
#define MCP9803_Alert_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define MCP9803_Alert_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSC6 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF5 pin functionality
 * @Example
    IOCCF5_ISR();
 */
void IOCCF5_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF5 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF5 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF5_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF5_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF5 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF5_SetInterruptHandler() method.
    This handler is called every time the IOCCF5 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF5_SetInterruptHandler(IOCCF5_InterruptHandler);

*/
extern void (*IOCCF5_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF5 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF5_SetInterruptHandler() method.
    This handler is called every time the IOCCF5 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF5_SetInterruptHandler(IOCCF5_DefaultInterruptHandler);

*/
void IOCCF5_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/