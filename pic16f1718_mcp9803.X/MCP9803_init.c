#include "MCP9803_init.h"

#include "mcc_generated_files/mcc.h"
#include "mcp9803/MCP9803.h"
#include "mcp9803/MCP9803_conversion.h"
#include "mcp9803/MCP9803_interface.h"

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


//////////////////////////////////////////////////////////////////////////////

MCP9803_Type mcp9803;
static MCP9803_PWR_MODE Operational_Mode;

void MCP9803_Initialize() {
    
    IOCCF5_SetInterruptHandler(MCP9803_Alert_IOC_InterruptHandler);
    TMR6_SetInterruptHandler(MCP9803_GetTempr_TMR_InterruptHandler);
    
    mcp9803 = MCP9803_Init(
                MCP9803_ADDRESS_BYTE(0x0),
                ( MCP9803_DEFAULT_CONFIG | ACTUAL_ADC_RESOLUTION ),
                &i2cMCP9803_readDataBlock,
                &i2cMCP9803_writeDataBlock
    );
    uint8_t operationMode = (MCP9803_OneShot_GetValue()) ? 
                            MCP9803_SHUTDOWN_ENABLE : MCP9803_SHUTDOWN_DISABLE;
    printf("START Temperature SENSOR: %s. Mode=%s\n\r",
            (MCP9803_NAME),
            (operationMode)?"ONE_SHOT":"CONTINUOUS");
    MCP9803_SetOperationMode(&mcp9803,operationMode);
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
    printf("%s[id:%u] ", MCP9803_NAME, mcp9803.m_address&0x7);
    char result_str[8]="";
    MCP9803_STRING_fromRAW2complement(result_str, mcp9803.m_data);
    printf("%8s ", result_str);
    
    if ((mcp9803.m_config&MCP9803_SHUTDOWN_ENABLE) != (MCP9803_SHUTDOWN_ENABLE))
        printf("[%6s] ", (MCP9803_IsAlert(&mcp9803))?"ALERT":"NORMAL");
    printf("\n\r");
    
    //reset ///////////////////////////////////////////////////////////
    mcp9803.m_flag.readyGetData = false;
    FLAG(DUBUG_2,0);
    CLRWDT();
    
    //sleep ///////////////////////////////////////////////////////////
    if (!MCP9803_IsAlert(&mcp9803)) {
        printf("SLEEP... ");
        FLAG(DUBUG_2,1);
        while(!EUSART_is_tx_done()){}
        FLAG(DUBUG_2,0);
        
        //go sleep ........
        SLEEP(); 
        //wakeup   ........
        FLAG(DUBUG_1,1);
        TMR6 = 0x00; //restart current count for setup actual delay
        TMRCallback_Counter = 0;  //reset
        printf("...WAKE UP STATUS [nTO|nPD] = %c%c \n\r",
                (STATUSbits.nTO)?'1':'0',
                (STATUSbits.nPD)?'1':'0' 
                );
        FLAG(DUBUG_1,0);
    }

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


