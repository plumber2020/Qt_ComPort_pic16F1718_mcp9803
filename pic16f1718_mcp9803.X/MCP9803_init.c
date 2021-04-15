#include "MCP9803_init.h"

#include "mcc_generated_files/mcc.h"
#include "mcp9803/MCP9803.h"
#include "mcp9803/MCP9803_conversion.h"
#include "mcp9803/MCP9803_interface.h"

//FLAG DEBUG for view on pin
#define DUBUG_1                         0   //view change FLAG before GetTempr
#define DUBUG_2                         1   //view change FLAG after  GetTempr
#define FLAG_SET(VALUE)                 LATBbits.LATB7 = VALUE
#define FLAG(DUBUG,VALUE)               do {if (DUBUG) FLAG_SET(VALUE);} while(0)


#define ACTUAL_ADC_RESOLUTION           MCP9803_ADC_RESOLUTION_10_BIT
#define ACTUAL_ADC_CONVERSION_DELAYms   80
#define MCP9803_GetTmprPeriod_ms        2000    // desirable period of checking
// also setup (check this)
#define TMR_Period_ms                   ACTUAL_ADC_CONVERSION_DELAYms
#define WDT_Period_s                    16

#define TMRCallback_Counter_MAX         (MCP9803_GetTmprPeriod_ms/TMR_Period_ms)
static 
volatile uint16_t TMRCallback_Counter = 0; 

void MCP9803_Alert_IOC_InterruptHandler();
void MCP9803_GetTempr_TMR_InterruptHandler();

#define DEBUG_wakeUpINFORM
inline void wakeUp_Status();

//////////////////////////////////////////////////////////////////////////////

MCP9803_Type mcp9803;
static MCP9803_PWR_MODE Operational_Mode;

void MCP9803_Initialize() {
    
    IOCCF5_SetInterruptHandler(MCP9803_Alert_IOC_InterruptHandler);
    TMR6_SetInterruptHandler(MCP9803_GetTempr_TMR_InterruptHandler);
    
    uint8_t address = ( MCP9803_A0_GetValue() 
                        | MCP9803_A1_GetValue()<<1
                        | MCP9803_A2_GetValue()<<2 ) & 0xFF;
    
    mcp9803 = MCP9803_Init(
                MCP9803_ADDRESS_BYTE(address),
                ( MCP9803_DEFAULT_CONFIG | ACTUAL_ADC_RESOLUTION ),
                &i2cMCP9803_readDataBlock,
                &i2cMCP9803_writeDataBlock
    );
    uint8_t operationMode = (MCP9803_OneShot_GetValue()) ? 
                            MCP9803_SHUTDOWN_ENABLE : MCP9803_SHUTDOWN_DISABLE;
    printf(TEMPLATE_OUTPUT_COMMENT, 
            "START Temperature SENSOR: ",
            MCP9803_NAME);
    printf(TEMPLATE_OUTPUT_COMMENT,
            MCP9803_NAME,
            (operationMode)
            ?" Mode=ONE_SHOT after SLEEP"
            :" Mode=CONTINUOUS ALERTnoSLEEP");

    MCP9803_SetOperationMode(&mcp9803,operationMode);
    MCP9803_Alert_IOC_InterruptHandler();   //check ALERT right now
}

void MCP9803_CheckTemperature()
{
    //check pre-last step for ONE_SHOT MODE ////////////////////////////
    if ( mcp9803.m_flag.readySendCfg )
        if (mcp9803.m_config & (uint8_t)ONE_SHOT)
        {
            MCP9803_SetConfiguration(&mcp9803);
            mcp9803.m_flag.readySendCfg = false;
            TMR6 = 0x00; //restart current count for setup actual delay
            FLAG(DUBUG_1,0);
            return;
        }
    
    //check ready data from sensor ////////////////////////////////////
    if (!mcp9803.m_flag.readyGetData)
        return;
     
    //getting temperature value and print /////////////////////////////
    mcp9803.m_data = MCP9803_GetTemperature(
                        &mcp9803, MCP9803_AMBIENT_TEMPERATURE_REGISTER);
    
    //output in UART
    printf(TEMPLATE_OUTPUT_DEVICE_NAME, 
            MCP9803_NAME, mcp9803.m_address&0x7);
    
    FLAG(DUBUG_2,0);
    char value_str[8]="";
    MCP9803_STRING_fromRAW2complement(value_str, mcp9803.m_data);
    printf(TEMPLATE_OUTPUT_DEVICE_VALUE, value_str);
    
    FLAG(DUBUG_2,1);
    if ((mcp9803.m_config&MCP9803_SHUTDOWN_ENABLE) != (MCP9803_SHUTDOWN_ENABLE))
        printf(TEMPLATE_OUTPUT_DEVICE_VALUE, 
                (MCP9803_IsAlert(&mcp9803))?"ALERT":"NORMAL");
    
    //reset ///////////////////////////////////////////////////////////
    mcp9803.m_flag.readyGetData = false;
    FLAG(DUBUG_2,0);
    CLRWDT();
    
    //sleep ///////////////////////////////////////////////////////////
    if (MCP9803_IsAlert(&mcp9803)) {
        printf(TEMPLATE_OUTPUT_ENDLINE);
    }
    else
    {
        printf(TEMPLATE_OUTPUT_COMMENT,"SLEEP","...");
        FLAG(DUBUG_2,1);
        while(!EUSART_is_tx_done()){}
        FLAG(DUBUG_2,0);
        
        //go sleep ........
        SLEEP(); 
        //wakeup   ........
        FLAG(DUBUG_1,1);
        TMR6 = 0x00; //restart current count for setup actual delay
        TMRCallback_Counter = 0;  //reset
        wakeUp_Status();
        FLAG(DUBUG_1,0);
    }
}

#include <stdio.h>
void wakeUp_Status()
{
#ifdef DEBUG_wakeUpINFORM
    char sbuf[40];
    sprintf(sbuf, "[%s, %s]", 
            ((STATUSbits.nTO)
            ?"ALERT interrupt"              //1 = After power-up, CLRWDT instruction or SLEEP instruction
            :"WDT Time-out"),               //0 = A WDT Time-out occurred
            ((STATUSbits.nPD)
            ?"PowerUp | CLRWDT"             //1 = After power-up or by the CLRWDT instruction
            :"after SLEEP")                 //0 = By execution of the SLEEP instruction  
            );
    printf(TEMPLATE_OUTPUT_COMMENT, 
            "...WAKEUP STATUS=", 
            sbuf);
#endif
}

// INTERRUPT HANDLERS ///////////////////////////////////////////////////////

void MCP9803_Alert_IOC_InterruptHandler() 
{
    MCP9803_SetAlert(&mcp9803,MCP9803_Alert_GetValue()); 
}

void MCP9803_GetTempr_TMR_InterruptHandler()
{
    FLAG(DUBUG_1,~FLAG_GetValue());
    ++TMRCallback_Counter;
    if(TMRCallback_Counter == TMRCallback_Counter_MAX-1) {
        mcp9803.m_flag.readySendCfg = true;
        FLAG(DUBUG_1,1); 
    }
    else
        if(TMRCallback_Counter >= TMRCallback_Counter_MAX) {
            mcp9803.m_flag.readyGetData = true;
            TMRCallback_Counter = 0; //reset
            FLAG(DUBUG_2,1);
        }
}


