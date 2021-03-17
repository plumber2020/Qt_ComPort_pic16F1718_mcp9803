/* 
 * File:   myMCP9803.h
 * Author: abram
 *
 * Created on March 10, 2021, 10:52 PM
 */
 
// The MCP9800/1/2/3 has four registers that are user-accessible. 
/* These registers are specified as 
 * the Ambient Temperature (TA) register            /read-only/
 * the Temperature Limit-set (TSET) register        /read/write/
 * the Temperature Hysteresis (THYST) register      /read/write/
 * device Configuration (CONFIG) register.
 * 
 * ----------------------------------------------------------------------------
 * REG
 * Pointer|      |   7   |   6   |   5   |   4   |   3   |   2   |   1   |  0  
 * ----------------------------------------------------------------------------
 * Ambient Temperature Register (TA)
 *  00    | MSB  | Sign  | 2^6°C | 2^5°C | 2^4°C | 2^3°C | 2^2°C | 2^1°C | 2^0°C
 *        | LSB  | 2^-1°C| 2^-2°C| 2^-3°C| 2^-4°C| 0     | 0     | 0     | 0
 * ----------------------------------------------------------------------------
 * Sensor Configuration Register (CONFIG)
 *  01    | LSB  |OneShot|  Resolution   |  Fault Queue  | ALERT |COMP/INT| Shutdown

 * ----------------------------------------------------------------------------
 * Temperature Hysteresis Register (THYST)
 *  10    | MSB  | Sign  | 2^6°C | 2^5°C | 2^4°C | 2^3°C | 2^2°C | 2^1°C | 2^0°C
 *        | LSB  | 2^-1°C|   0   |   0   |   0   |   0   |   0   |   0   |  0
 * ----------------------------------------------------------------------------
 * Temperature Limit-Set Register (TSET)
 *  11    | MSB  | Sign  | 2^6°C | 2^5°C | 2^4°C | 2^3°C | 2^2°C | 2^1°C | 2^0°C
 *        | LSB  | 2^-1°C|   0   |   0   |   0   |   0   |   0   |   0   |  0
 * ----------------------------------------------------------------------------
 * 
 */

// AMBIENT TEMPERATURE REGISTER (TA)- ADDRESS <0000 0000>
/*
 * The MCP9800/1/2/3 has a 16-bit read-only Ambient Temperature register 
 * that contains 9-bit to 12-bit temperature data. 
 * (0.5°C to 0.0625°C resolutions, respectively). This data is formatted 
 * in two's complement. The bit assignments, as well as the corresponding
 * resolution, is shown in the register assignment below.
 * 
 * The refresh rate of this register: It takes 30 ms (typical) for 9-bit
 * data and 240 ms (typical) for 12-bit data. Since this register is 
 * double-buffered, the user can read the register while the 
 * MCP9800/1/2/3 performs Analog-to-Digital conversion in the background.
 */

// SENSOR CONFIGURATION REGISTER (CONFIG) ADDRESS <0000 0001>
/* bit 7 ONE-SHOT bit
        1 = Enabled
        0 = Disabled (Power-up default)
 * bit 5-6 ADC RESOLUTION bits
        00 = 9 bit or 0.5°C (Power-up default)
        01 = 10 bit or 0.25°C
        10 = 11 bit or 0.125°C
        11 = 12 bit or 0.0625°C
 * bit 3-4 FAULT QUEUE bits
        00 = 1 (Power-up default)
        01 = 2
        10 = 4
        11 = 6
 * bit 2 ALERT POLARITY bit
        1 = Active-high
        0 = Active-low (Power-up default)
 * bit 1 COMP/INT bit
        1 = Interrupt mode
        0 = Comparator mode (Power-up default)
 * bit 0 SHUTDOWN bit
        1 = Enable
        0 = Disable (Power-up default)
 */
    
// TEMPERATURE HYSTERESIS REGISTER (THYST) ADDRESS <0000 0010>
/* The power-up default value of THYST register is 75°C,
 * or <0100 1011 0> in binary.
 */

// TEMPERATURE LIMIT-SET REGISTER (TSET) ADDRESS <0000 0011>
/* The power-up default value of the TSET register is 80°C,
 * or <0101 0000 0> in binary.
 */

// Other parameters
/*
 * Shutdown mode
 * The Shutdown mode disables all power-consuming activities
 * In Shutdown mode, the CONFIG, TA, TSET and THYST registers can be read or written to
 * 
 * One-Shot Mode
 * The One-shot mode performs a single temperature measurement and returns to Shutdown mode.
 * For example, a 9-bit TA in One-shot mode consumes 200 uA (typical) for 30 ms
 * and 0.1 uA (typical) during shutdown.
 * 
 * ALERT Output Configuration
 * The ALERT output can be configured as either a comparator output or
 * as Interrupt Output mode using bit 1 of CONFIG.
 * 
 * Comparator Mode
 * In Comparator mode, the ALERT output is asserted when TA is greater than TSET. 
 * The pin remains active until TA is lower than THYST.
 * 
 * Interrupt Mode
 * In Interrupt mode, the ALERT output is asserted when TA is greater than TSET. 
 * However, the output is deasserted when the user performs a read from any register.
 * When TA drifts below THYST, the MCP9800/1/2/3 outputs another interrupt and the
 * controller needs to read a register to deassert the ALERT output.
 * 
 * Fault Queue
 * The fault queue feature can be used as a filter to lessen the probability 
 * of spurious activation of the ALERT pin.
 * 
 * RESOLUTION AND CONVERSION TIME
 *   Bits   Resolution   tCONV (typical)
        9   0.5          30 ms
        10  0.25         60 ms
        11  0.125        120 ms
        12  0.0625       240 ms
 * 
 * POWER-UP DEFAULTS
 * Register     Data(Hex)   Power-up Defaults
    TA          0000        0°C
    TSET        A000        80°C
    THYST       9600        75°C
    Pointer     00          Temperature register
    CONFIG      00          Continuous Conversion
                            Comparator mode
                            Active-low Output
                            Fault Queue 1
                            9-bit Resolution 
 */
   
// Diagram for Reading +25.25°C Temperature from the TA Register
/*      | Address Byte   |       | TA Pointer|  
 *  s + | 1001000 + W(0) | +ack+ | 00000000  | +ack
 * 
 *      | Address Byte   |       | MSB Data  |       | LSB Data |   
 *  s + | 1001000 + R(1) | +ack+ | 00011001  | +ack+ | 01000000 | +nak/p     
 */


///////////////////////////////////////////////////////////////////


#ifndef MYMCP9803_H
#define	MYMCP9803_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include  <stdlib.h>
    
#define MCP9803_NAME                            "MCP9803"

// ADDRESS REGISTER ///////////////////////////////////////////////

#define MCP9803_ADDRESS_BYTE(AAA)              (0x48 | AAA)
#define MCP9803_AMBIENT_TEMPERATURE_REGISTER    0x00    //b00000000
#define MCP9803_CONFIG_REGISTER                 0x01    //b00000001
#define MCP9803_HYSTERESIS_REGISTER             0x02    //b00000010
#define MCP9803_LIMIT_SET_REGISTER              0x03    //b00000010

// DEFAULT VALUE of REGISTER //////////////////////////////////////

#define MCP9803_DEFAULT_ADDRESS_BYTE           (0x48 | 0x0)
#define MCP9803_DEFAULT_CONFIG                  0x00   
#define MCP9803_DEFAULT_AMBIENT_TEMPERATURE     0x00    
#define MCP9803_DEFAULT_HYSTERESIS              0x48    //LOWER_ALERT_BOUND    
#define MCP9803_DEFAULT_LIMIT_SET               0x50    //UPPER_ALERT_BOUND

// CONFIG REGISTER ////////////////////////////////////////////////

#define MCP9803_ONE_SHOT_DISABLED               0x0     //DEFAULT
#define MCP9803_ONE_SHOT_ENABLED                0x1<<7

#define MCP9803_ADC_RESOLUTION_9_BIT            0x0     //DEFAULT
#define MCP9803_ADC_RESOLUTION_10_BIT           0x1<<5
#define MCP9803_ADC_RESOLUTION_11_BIT           0x2<<5
#define MCP9803_ADC_RESOLUTION_12_BIT           0x3<<5

#define MCP9803_FAULT_QUEUE_1                   0x0     //DEFAULT
#define MCP9803_FAULT_QUEUE_2                   0x1<<3
#define MCP9803_FAULT_QUEUE_4                   0x2<<3
#define MCP9803_FAULT_QUEUE_6                   0x3<<3
    
#define MCP9803_ALERT_POLARITY_ACTIVE_LOW       0x0     //DEFAULT
#define MCP9803_ALERT_POLARITY_ACTIVE_HIGH      0x1<<2

#define MCP9803_COMPARATOR_MODE                 0x0     //DEFAULT
#define MCP9803_INTERPUT_MODE                   0x1<<1

#define MCP9803_SHUTDOWN_DISABLE                0x0     //DEFAULT
#define MCP9803_SHUTDOWN_ENABLE                 0x1<<0
    
// DELAY //////////////////////////////////////////////////////////
    
#define MCP9803_ADC_RESOLUTION_9_BIT_DELAY      50      //30..75ms
#define MCP9803_ADC_CONVERSATION_DELAY(ADC_RES) MCP9803_ADC_RESOLUTION_9_BIT_DELAY \
                                                * (1 << ADC_RES )
      
///////////////////////////////////////////////////////////////////
  
typedef void(*i2c_readMCP9803_Type) (uint8_t address, uint8_t reg, void* data, size_t len);
typedef void(*i2c_writeMCP9803_Type)(uint8_t address, uint8_t reg, void* data, size_t len);

typedef struct { 
	uint8_t m_address;
	uint8_t m_config;
    uint16_t m_data;
    union {
        struct {
            uint8_t alert           :1;
            uint8_t readySendCfg    :1;
            uint8_t readyGetData    :1; 
            uint8_t unused          :5;
        };
        uint8_t full;
    } m_flag;

    
    //i2c interface
    i2c_readMCP9803_Type i2c_read_handler;
	i2c_writeMCP9803_Type i2c_write_handler;
} MCP9803_Type;

typedef enum MCP9803_POWER_MODE_Type {
    CONTINUOUS  = MCP9803_DEFAULT_CONFIG,
    ONE_SHOT    = MCP9803_ONE_SHOT_ENABLED | MCP9803_SHUTDOWN_ENABLE
} MCP9803_PWR_MODE;

MCP9803_Type MCP9803_Init(uint8_t address,
                          uint8_t config, 
                          i2c_readMCP9803_Type,
                          i2c_writeMCP9803_Type);

void MCP9803_SetOperationMode(MCP9803_Type* device, MCP9803_PWR_MODE mode);
void MCP9803_SetConfiguration(MCP9803_Type* device);
void MCP9803_GetConfiguration(MCP9803_Type* device);

void MCP9803_SetTemperature(MCP9803_Type* device, uint8_t reg, uint16_t data);
uint16_t MCP9803_GetTemperature(MCP9803_Type* device, uint8_t reg);

bool MCP9803_IsAlert(MCP9803_Type* mcp9803);
void MCP9803_SetAlert(MCP9803_Type* mcp9803, bool alert);


#ifdef	__cplusplus
}
#endif

#endif	/* MYMCP9803_H */

