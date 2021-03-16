/*
  ?© 2021 Microchip Technology Inc. and its subsidiaries

  Subject to your compliance with these terms, you may use Microchip software
  and any derivatives exclusively with Microchip products. You're responsible
  for complying with 3rd party license terms applicable to your use of 3rd party
  software (including open source software) that may accompany Microchip software.
  SOFTWARE IS "AS IS." NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
  APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,
  MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP
  BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS,
  DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER
  CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
  FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY
  ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT EXCEED AMOUNT OF FEES, IF ANY,
  YOU PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*/


#ifndef _MCP9808_H
#define _MCP9808_H

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

// MCP9808 Library Version
#define MCP9808_LIBVER "2.0.0"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*
 * I2C driver support
 */

#define I2C_FSERV_ENABLED

#ifdef I2C_FSERV_ENABLED
#include "../drivers/i2c_simple_master.h"
#define MCP9808_BUS_ID 0
#endif

#define CONCAT(X, Y)    X ## Y

#if defined(I2C_CLASSIC_ENABLED) || defined(I2C1_CLASSIC_ENABLED) || defined(I2C2_CLASSIC_ENABLED) || defined(I2C3_CLASSIC_ENABLED) || defined(I2C4_CLASSIC_ENABLED)
#define I2C_MESSAGE_STATUS(PREF)          CONCAT(PREF, _MESSAGE_STATUS)
#define I2C_MESSAGE_COMPLETE(PREF)        CONCAT(PREF,_MESSAGE_COMPLETE)
#define I2C_MESSAGE_FAIL(PREF)            CONCAT(PREF,_MESSAGE_FAIL)
#define I2C_MESSAGE_PENDING(PREF)         CONCAT(PREF,_MESSAGE_PENDING)
#define I2C_STUCK_START(PREF)             CONCAT(PREF,_STUCK_START)
#define I2C_MESSAGE_ADDRESS_NO_ACK(PREF)  CONCAT(PREF,_MESSAGE_ADDRESS_NO_ACK)
#define I2C_DATA_NO_ACK(PREF)             CONCAT(PREF,_DATA_NO_ACK)
#define I2C_LOST_STATE(PREF)              CONCAT(PREF,_LOST_STATE)
#elif !defined(I2C_FSERV_ENABLED)
#error "No I2C bus has been enabled in the platform!"
#endif

/**
 Section: Constants
*/

#define MCP9808_CLIENT_ADDRESS                      0x1A
    
#define MCP9808_CONFIG_ADDR                         0x01 
#define MCP9808_ALERT_TEMP_UPPER_LIMIT_ADDR         0x02
#define MCP9808_ALERT_TEMP_LOWER_LIMIT_ADDR         0x03
#define MCP9808_ALERT_TEMP_CRIT_LIMIT_ADDR          0x04
#define MCP9808_TEMPERATURE_ADDR                    0x05
#define MCP9808_MANUFACTURER_ID_ADDR                0x06
#define MCP9808_DEVICE_ID_ADDR                      0x07
#define MCP9808_DEVICE_REVISION_ADDR                0x07
#define MCP9808_RESOLUTION_ADDR                     0x08
    
#define MCP9808_REGISTER_PTR_SIZE            		0x01
#define MCP9808_CONFIG_SIZE                  		0x02
#define MCP9808_LIMIT_SIZE                   		0x02
#define MCP9808_TEMPERATURE_SIZE             		0x02
#define MCP9808_MANUFACTURER_SIZE            		0x02
#define MCP9808_DEVICE_ID_REV_SIZE           		0x02
#define MCP9808_RESOLUTION_SIZE              		0x01

#define MCP9808_RESOLUTION_0P5           			0x00
#define MCP9808_RESOLUTION_0P25          			0x01
#define MCP9808_RESOLUTION_0P125         			0x02
#define MCP9808_RESOLUTION_0P0625        			0x03

#define MCP9808_HYSTERESIS_0             			0x00
#define MCP9808_HYSTERESIS_1P5           			0x01
#define MCP9808_HYSTERESIS_3             			0x02
#define MCP9808_HYSTERESIS_6             			0x03    

#define MCP9808_POWER_MODE      					0x00
#define MCP9808_SHUTDOWN_MODE   					0x01

#define MCP9808_CRITICAL_LOCK_BIT      				0x80
#define MCP9808_WINDOW_LOCK_BIT        				0x40


#define MCP9808_INTERRUPT_CLEAR_BIT  				0x20

#define MCP9808_ALERT_OUTPUT_NOT_ASSERTED   		0x00
#define MCP9808_ALERT_OUTPUT_ASSERTED       		0x01

#define MCP9808_DISABLE_ALERT_CONTROL   			0x00
#define MCP9808_ENABLE_ALERT_CONTROL    			0x01

#define MCP9808_DISABLE_ALERT_SELECT    			0x00
#define MCP9808_ENABLE_ALERT_SELECT     			0x01

#define MCP9808_ALERT_ACTIVE_LOW    				0x00
#define MCP9808_ALERT_ACTIVE_HIGH   				0x01

#define MCP9808_COMPARATOR_OUTPUT   				0x00
#define MCP9808_INTERRUPT_OUTPUT    				0x01

#define BIT_0       0x01
#define BIT_1       0x02
#define BIT_2       0x04
#define BIT_3       0x08
#define BIT_4       0x10
#define BIT_5       0x20
#define BIT_6       0x40
#define BIT_7       0x80
#define BIT_8       0x100
#define BIT_9       0x200
#define BIT_10      0x400
#define BIT_11      0x800
#define BIT_12      0x1000
#define BIT_13      0x2000
#define BIT_14      0X4000
#define BIT_15      0x8000



//error code
#define MCP9808_NO_ERR                                0
#define MCP9808_SUCCESS                               0
#define MCP9808_INVALID_I2C_BUSID                     1
#define MCP9808_I2C_ERRCLASS                        128
#define MCP9808_INVALID_PARAMETER                  -115

#define MCP9808_INVALID_RESOLUTION_VALUE            -100
#define MCP9808_INVALID_HYSTERESIS_VALUE            -101
#define MCP9808_INVALID_TEMP_CONV_STS_BIT           -102
#define MCP9808_INVALID_CRITICAL_LOCK_BIT           -103
#define MCP9808_INVALID_WINDOW_LOCK_BIT             -104
#define MCP9808_INVALID_ALERT_STATUS_BIT            -105
#define MCP9808_INVALID_ALERT_CONTROL_BIT           -106
#define MCP9808_INVALID_ALERT_SELECT_BIT            -107
#define MCP9808_INVALID_ALERT_POLARITY_BIT          -108
#define MCP9808_INVALID_ALERT_MODE_BIT              -109
#define MCP9808_INVALID_UPPER_LIMIT_VALUE           -110
#define MCP9808_INVALID_LOWER_LIMIT_VALUE           -111
#define MCP9808_INVALID_CRITICAL_LIMIT_VALUE        -112
#define MCP9808_INVALID_CONFIGURATION_VALUE         -113
#define MCP9808_INVALID_LIMIT_VALUE                 -114


 typedef struct _MCP9808_i2c_params {
    uint8_t i2cAddress;
    uint8_t i2cBusID;   // parameter used only by "i2c classic lib"
} MCP9808_i2c_params;

 typedef struct _MCP9808_alert_flags {
    uint8_t tCrit;  
    uint8_t tUpper;
    uint8_t tLower;
} MCP9600_alert_flags;

 typedef enum _MCP9808_alertID{
    ALERT_UPPER = 1,
    ALERT_LOWER = 2,
    ALERT_CRIT = 3
} MCP9808_alertID;  

/**
    @Summary
        Initializes the MCP9808 instance:

    @Description
        This routine initializes the MCP9808 device based on user configuration
        in the MCC gui

    @Preconditions
        None

    @Param        
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params param = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_MODULE_Initialize(param);	
        </code>

*/
int8_t MCP9808_MODULE_Initialize(MCP9808_i2c_params i2cParams);

//==================== RESOLUTION ===============================//

/**
    @Summary
        Sets the resolution for MCP9808.

    @Description
        This function allows the user to set the resolution register value given the raw value. 
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        registerVal (in) - The resolution register value to be set. Valid options are:
                            MCP9808_RESOLUTION_0P5      = 0x00      (0.5 C)
                            MCP9808_RESOLUTION_0P25     = 0x01      (0.25 C)
                            MCP9808_RESOLUTION_0P125    = 0x02      (0.125 C)
                            MCP9808_RESOLUTION_0P0625   = 0x03      (0.0625 C)
    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params param = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetResolutionRegister(param, MCP9808_RESOLUTION_0P125);	
        </code>

*/
int8_t MCP9808_SetResolutionRegister(MCP9808_i2c_params i2cParams, uint8_t registerVal);


/**
    @Summary
        Gets the resolution for MCP9808.
    @Description
        This function returns the currently set resolution register value. The result is represented by the raw value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *resolutionReg (out) - pointer to variable that will store the resolution register value:
                    MCP9808_RESOLUTION_0P5               = 0x00          (0.5 C)
                    MCP9808_RESOLUTION_0P25              = 0x01          (0.25 C)
                    MCP9808_RESOLUTION_0P125             = 0x02          (0.125 C)
                    MCP9808_RESOLUTION_0P0625            = 0x03          (0.0625 C)

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t resReg;
            int8_t errorCode = MCP9808_GetResolutionRegister(i2cParams, &resReg);	
        </code>

*/
int8_t MCP9808_GetResolutionRegister(MCP9808_i2c_params i2cParams, uint8_t* resolutionReg);


 /**
    @Summary
        Sets the resolution for MCP9808.

    @Description
        This function allows the user to set the resolution value given the real values. 
 
    @Preconditions
        None
 
    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        resolutionVal (in) - The resolution value to be set. Valid options are:
                                0.5 C | 0.25 C | 0.125 C | 0.0625 C

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetResolutionValue(i2cParams, 0.0625);	
        </code>

*/
int8_t MCP9808_SetResolutionValue(MCP9808_i2c_params i2cParams, float resolutionVal);              



/**
    @Summary
        Gets the resolution for MCP9808.

    @Description
        This function returns the currently set resolution value. The result is represented by the real value.
 
    @Preconditions
        None
 
    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *resolutionVal (out) - pointer to variable that will store the currently resolution value (0.5|0.25|0.125|0.0625)

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            float resVal;
            int8_t errorCode = MCP9808_GetResolutionValue(i2cParams, &resVal);
        </code>

*/
int8_t MCP9808_GetResolutionValue(MCP9808_i2c_params i2cParams, float* resolutionVal);

//==================== ALERT LIMITs  =============================//

/**
    @Summary
        Sets the alert temperature upper, lower or critical limit for MCP9808.

    @Description
        This function allows the user to select which alert temperature register to configure 
        and to set the raw value for the selected alert.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        alertId (in) - alert type that will be set. Valid options are:
                     - ALERT_UPPER = 1
                     - ALERT_LOWER = 2
                     - ALERT_CRIT  = 3
    @Param
        registerVal (in) - The value to set in the selected alert temperature limit register.
                        Range: [-4092; 4092]. Register contains 11-bit data in
                        two's complement format (0.25 C):
                                Bits 15-13: Unimplemented
                                Bit  12:    Sign bit
                                Bits 11-2:  Temperature limit bits
                                Bits 1-0:   Unimplemented

    @Returns
        0 for success or error code.

    @Note
        If the 'Window Lock' bit is set, temperature limit registers cannot be written.

    @Example
        <code>
            // Set 0x64 to Alert Temperature Upper register 
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint16_t registerVal = 0x64;
            int8_t errorCode = MCP9808_SetLimitRegister(i2cParams, 1, registerVal);
        </code>

*/
int8_t MCP9808_SetLimitRegister(MCP9808_i2c_params i2cParams, uint8_t alertId, uint16_t registerVal);

/**
    @Summary
        Gets the alert temperature upper, lower or critical limit for MCP9808.

    @Description
        This function allows the user to select for which alert temperature register to read the raw value. 
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        alertId (in) - alert type that will be set. Valid options are:
                     - ALERT_UPPER = 1
                     - ALERT_LOWER = 2
                     - ALERT_CRIT  = 3
    @Param
        *registerVal (out) - pointer to variable that will store the raw value of the selected limit register.  
                             Register contains 11-bit data in two's complement format(0.25 C):
                                Bits 15-13: Unimplemented
                                Bit  12:    Sign bit
                                Bits 11-2:  Temperature limit bits
                                Bits 1-0:   Unimplemented

    @Returns
        0 for success or error code.

    @Example
        <code>
            // Get value for Alert Temperature Upper register 
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint16_t registerVal;
            int8_t errorCode = MCP9808_GetLimitRegister(i2cParams, 1, &registerVal);
        </code>

*/
int8_t MCP9808_GetLimitRegister(MCP9808_i2c_params i2cParams, uint8_t alertId, uint16_t* registerVal);

/**
    @Summary
        Sets the alert temperature upper, lower or critical limit for MCP9808.

    @Description
        This function allows the user to select which alert temperature register to configure
        and to set the real value in Celsius degrees for the selected alert.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        alertId (in) - alert type that will be set. Valid options are:
                     - ALERT_UPPER = 1
                     - ALERT_LOWER = 2
                     - ALERT_CRIT  = 3
    @Param
        tempVal (in) - The alert temperature upper limit value to be set.
                       Range: [-255.75; 255.75].

    @Returns
        0 for success or error code.
        
    @Note
        If the 'Window Lock' bit is set, temperature limit registers cannot be written.

    @Example
        <code>
            // Set 90(C) to Alert Temperature Upper register 
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, 1, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetLimitValue(i2cParams, 1, 90);
        </code>

*/
int8_t MCP9808_SetLimitValue(MCP9808_i2c_params i2cParams, uint8_t alertId, float tempVal);

/**
    @Summary
        Gets the alert temperature upper, lower or critical limit for MCP9808.

    @Description
        This function allows the user to select for which alert temperature register to read the real value in Celsius degrees.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        alertId (in) - alert type that will be set. Valid options are:
                     - ALERT_UPPER = 1
                     - ALERT_LOWER = 2
                     - ALERT_CRIT  = 3
    @Param
        *tempVal (out) - pointer to variable that will store the real value of the register.
                             Register contains values from [-255.75; 255.75] range

    @Returns
        0 for success or error code.

    @Example
        <code>
            // Get value for Alert Temperature Upper register
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            float tempVal;
            int8_t errorCode = MCP9808_GetLimitValue(i2cParams, 1, &tempVal);
        </code>

*/
int8_t MCP9808_GetLimitValue(MCP9808_i2c_params i2cParams, uint8_t alertId, float* tempVal);


//==================== TEMPERATURE ===============================//

/**
    @Summary
        Gets the temperature register raw value from MCP9808.

    @Description
        This function returns the raw value from the temperature register.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *registerVal (out)- pointer to variable that will store the raw value of the register.  
                            Register contains 11-bit data in two's complement format(0.25 C):
                               Bit  15:    Tcrit Alert
                               Bit  14:    Tupper Alert
                               Bit  13:    Tlower Alert
                               Bit  12:    Sign bit
                               Bits 11-0:  Temperature bits

    @Returns
        0 for success or error code.

     @Example
        <code>
            // Get temperature register raw value
            uint16_t registerVal;
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_GetTemperatureRegister(i2cParams, &registerVal);
        </code>

*/
int8_t MCP9808_GetTemperatureRegister(MCP9808_i2c_params i2cParams, uint16_t* registerVal);


/**
    @Summary
        Gets the alert flags and the ambient temperature read from MCP9808.

    @Description
        This function returns the alert flags for Tcrit, Tupper and Tlower along with the ambient temperature value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        alertFlags (out) - pointer to the structure that will store the alerts individually 
                         - see MCP9600_alert_flags structure.
    @Param
        *tempVal (out) - pointer to variable that will store the ambient temperature value

    @Returns
        0 for success or error code.

     @Example
        <code>            
            // Get the alert flags and the ambient temperature 
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            MCP9600_alert_flags alertFlags;
            float tempVal;
            int8_t errorCode = MCP9808_GetTemperatureValue(i2cParams, &alertFlags &tempVal);			
        </code>

*/
int8_t MCP9808_GetTemperatureValue(MCP9808_i2c_params i2cParams, MCP9600_alert_flags* alertFlags, float* tempVal);


//========================== CONFIGURATION REGISTER ==========================//

/**
    @Summary
        Sets the configuration register for MCP9808.

    @Description
        This function allows the user to set the current configuration register value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        registerVal (in) - The configuration register value to be set.

    @Returns
        0 for success or error code.

    @Example
        <code>
            // writing 0 (default value)
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint16_t registerVal = 0;
            int8_t errorCode = MCP9808_SetConfigurationRegister(i2cParams, registerVal);			
        </code>

*/
int8_t MCP9808_SetConfigurationRegister(MCP9808_i2c_params i2cParams, uint16_t registerVal);



/**
    @Summary
        Gets the configuration register for MCP9808.

    @Description
        This function returns the currently set configuration register value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *registerVal (out) - pointer to variable that will store the current configuration register value.

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint16_t registerVal;
            int8_t errorCode = MCP9808_GetConfigurationRegister(i2cParams, &registerVal);			
        </code>

*/
int8_t MCP9808_GetConfigurationRegister(MCP9808_i2c_params i2cParams, uint16_t* registerVal);


//====================== HYSTERESIS TEMPERATURE ==============================//

/**
    @Summary
        Sets the hysteresis temperature for MCP9808.

    @Description
        This function allows the user to set the temperature limit hysteresis raw value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        hystBitVal (in) - the hysteresis bit value to be set. Valid option are:
                            MCP9808_HYSTERESIS_0   = 0   (0 C)
                            MCP9808_HYSTERESIS_1P5 = 1   (1.5 C)
                            MCP9808_HYSTERESIS_3   = 2   (3.0 C)
                            MCP9808_HYSTERESIS_6   = 3   (6.0 C)

    @Returns
        0 for success or error code.

    @Example
        <code>
            // Set hysteresis raw value to 0x3
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetTempHysteresis(i2cParams, MCP9808_HYSTERESIS_3);			
        </code>

*/
int8_t MCP9808_SetTempHysteresis(MCP9808_i2c_params i2cParams, uint8_t hystBitVal);


/**
    @Summary
        Gets the hysteresis temperature for MCP9808.

    @Description
        This function returns the raw temperature limit hysteresis bit value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *hystBitVal (out) - pointer to variable that will store the hysteresis raw value (0|1|2|3):
                            MCP9808_HYSTERESIS_0             = 0  (0 C)
                            MCP9808_HYSTERESIS_1P5           = 1  (1.5 C)
                            MCP9808_HYSTERESIS_3             = 2  (3.0 C)
                            MCP9808_HYSTERESIS_6             = 3  (6.0 C)

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t hystBitVal;
            int8_t errorCode = MCP9808_GetTempHysteresis(i2cParams, &hystBitVal);			
        </code>

*/
int8_t MCP9808_GetTempHysteresis(MCP9808_i2c_params i2cParams, uint8_t* hystBitVal);


/**
    @Summary
        Sets the hysteresis temperature for MCP9808.

    @Description
        This function allows the user to set the temperature limit hysteresis real value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        hystValue (in) - the temperature hysteresis value to be set.
                        Valid option: 0 C | 1.5 C | 3.0 C | 6.0 C

    @Returns
        0 for success or error code.
        
    @Example
        <code>
            // Set hysteresis real value to1.5
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetTempHysteresisValue(i2cParams, 1.5);			
        </code>

*/
int8_t MCP9808_SetTempHysteresisValue(MCP9808_i2c_params i2cParams, float hystValue);


/**
    @Summary
        Gets the hysteresis temperature for MCP9808.

    @Description
        This function returns the currently set temperature limit hysteresis value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *hystValue (out) - pointer to variable that will store the hysteresis real value 

    @Returns
        0 for success or error code.
        
    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            float hystValue;
            int8_t errorCode = float hystValue = MCP9808_GetTempHysteresisValue(i2cParams, &hystValue); 			
        </code>

*/
int8_t MCP9808_GetTempHysteresisValue(MCP9808_i2c_params i2cParams, float* hystValue);


//========================= SHUTDOWN MODE ====================================//

/**
    @Summary
        Enable the Shutdown mode for MCP9808.

    @Description
        This function allows the user to set the 'Shutdown Mode' bit from
        configuration register.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_EnableShutdownMode(i2cParams);			
        </code>

*/
int8_t MCP9808_EnableShutdownMode(MCP9808_i2c_params i2cParams);


/**
    @Summary
        Enables continuous conversion mode for MCP9808.

    @Description
        This function allows the user to clear the 'Shutdown Mode' bit from
        configuration register.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Returns
        0 for success or error code.

    @Example
        <code> 
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_EnableContinuousConversionMode(i2cParams);	
        </code>

*/
int8_t MCP9808_EnableContinuousConversionMode(MCP9808_i2c_params i2cParams);


/**
    @Summary
        Gets the 'Shutdown Mode' bit for MCP9808.

    @Description
        This function returns the currently set 'Shutdown Mode' bit value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *convStatus (out) - pointer to variable that will store the 'Shutdown Mode' bit value (0|1) 

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t convStatus;
            int8_t errorCode = MCP9808_GetTemperatureConversionStatus(i2cParams, *convStatus);
        </code>

*/
int8_t MCP9808_GetTemperatureConversionStatus(MCP9808_i2c_params i2cParams, uint8_t* convStatus);


//========================= CRITICAL LOCK BIT ================================//


/**
    @Summary
        Sets the 'Critical Lock' bit for MCP9808.

    @Description
        This function allows the user to set the 'Critical Lock' bit from 
        configuration register. In this case, the critical temperature limit
        register cannot be written.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Returns
        0 for success or error code.

    @Note
        When enabled, this bit remains '1'(locked) until cleared by an internal Reset.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetCriticalLock(i2cParams);
        </code>

*/
int8_t MCP9808_SetCriticalLock(MCP9808_i2c_params i2cParams);


/**
    @Summary
        Gets the 'Critical Lock' bit value for MCP9808.

    @Description
        This function returns the currently set 'Critical Temperature Lock' bit value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *critLock (out) - pointer to variable that will store the 'Critical Lock' bit value

    @Returns
        0 for success or error code.
        
    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t critLock;
            int8_t errorCode = MCP9808_GetCriticalLockBit(i2cParams, &critLock);
        </code>

*/
int8_t MCP9808_GetCriticalLock(MCP9808_i2c_params i2cParams, uint8_t* critLock);


//========================= WINDOW LOCK BIT ==================================//

/**
    @Summary
        Sets the 'Window Lock' bit for MCP9808.

    @Description
        This function allows the user to set the 'Window Lock' bit from 
        configuration register. In this case, the upper and lower temperature
        limit registers cannot be written.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Returns
        0 for success or error code.
        
    @Note
        When enabled, this bit remains set to '1' (locked) until cleared by a Power-on Reset.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetWindowLock(i2cParams);
        </code>

*/
int8_t MCP9808_SetWindowLock(MCP9808_i2c_params i2cParams);


/**
    @Summary
        Gets the 'Window Lock' bit value for MCP9808.

    @Description
        This function returns the currently set 'Window Lock' bit value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *windowLock (out) - pointer to variable that will store the 'Window Lock' bit value

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t windowLock;
            int8_t errorCode =  MCP9808_GetWindowLockBit(i2cParams, *windowLock);
        </code>

*/
int8_t MCP9808_GetWindowLock(MCP9808_i2c_params i2cParams, uint8_t* windowLock);


//========================= INTERRUPT CLEAR BIT ==============================//

/**
    @Summary
        Sets the 'Interrupt Clear' bit for MCP9808.

    @Description
        This function allows user to set the 'Interrupt Clear' bit from 
        configuration register.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Returns
        0 for success or error code.

    @Note
        This bit cannot be set to '1' in Shoutdown Mode, but it can be cleared after the 
        device enters Shutdown mode

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_ClearInterrupt(i2cParams);
        </code>

*/
int8_t MCP9808_ClearInterrupt(MCP9808_i2c_params i2cParams);


//========================== ALERT STATUS BIT ================================//

/**
    @Summary
        Gets the 'Alert Status' bit for MCP9808.

    @Description
        This function returns the currently alert output status bit value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *alertSts (out) - pointer to variable that will store the 'Alert Status' bit value.
                            MCP9808_ALERT_OUTPUT_NOT_ASSERTED        = 0
                            MCP9808_ALERT_OUTPUT_ASSERTED            = 1

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t alertSts;
            int8_t errorCode =  MCP9808_GetAlertStatus(i2cParams, &alertSts);			
        </code>

*/
int8_t MCP9808_GetAlertStatus(MCP9808_i2c_params i2cParams, uint8_t* alertSts);


//=========================== ALERT CONTROL BIT ==============================//

/**
    @Summary
        Sets the 'Alert Control' bit value for MCP9808.

    @Description
        This function allows the user to set the alert output control bit value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        bitValue (in) - The 'Alert Control' bit value to be set. Valid options:
                        MCP9808_DISABLE_ALERT_CONTROL    (0) - disabled
                        MCP9808_ENABLE_ALERT_CONTROL     (1) - enabled

    @Returns
        0 for success or error code.

    @Note
        This bit can't be set when either of the Lock bits are set. This can be
        set in Shutdown mode, but the Alert output will not assert or deassert.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetAlertControl(MCP9808_ENABLE_ALERT_CONTROL);			
        </code>

*/
int8_t MCP9808_SetAlertControl(MCP9808_i2c_params i2cParams, uint8_t bitValue);


/**
    @Summary
        Gets the 'Alert Control' bit value for MCP9808.

    @Description
        This function returns the currently set alert output control bit value.
 
    @Preconditions
        None
 
    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *alertCtrl (out) - pointer to variable that will store the 'Alert Control' bit value:
                            MCP9808_DISABLE_ALERT_CONTROL            = 0
                            MCP9808_ENABLE_ALERT_CONTROL             = 1

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t alertCtrl;
            int8_t errorCode = MCP9808_GetAlertControl(i2cParams, &alertCtrl);			
        </code>

*/
int8_t MCP9808_GetAlertControl(MCP9808_i2c_params i2cParams, uint8_t* alertCtrl);


//=========================== ALERT SELECT BIT ===============================//

/**
    @Summary
        Sets the 'Alert Select' bit for MCP9808.

    @Description
        This function allows the user to set the alert output select bit value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        bitValue (in) -  The 'Alert Select' bit value to be set. Valid options:
                            MCP9808_DISABLE_ALERT_SELECT    (0) - alert output for upper, lower and critical limits
                            MCP9808_ENABLE_ALERT_SELECT     (1) - alert output only for critical limit

    @Returns
        0 for success or error code.

    @Note
        This bit cannot be written when the Alarm Window Lock bit is set.
        This bit can be configured in Shutdown mode, but the alert output 
        will not assert or deassert.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetAlertSelect(i2cParams, MCP9808_ENABLE_ALERT_SELECT);			
        </code>

*/
int8_t MCP9808_SetAlertSelect(MCP9808_i2c_params i2cParams, uint8_t bitValue);


/**
    @Summary
        Gets the 'Alert Select' bit value for MCP9808.

    @Description
        This function returns the currently set alert output select bit value.
 
    @Preconditions
        None
 
    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *alertSel (out) - pointer to variable that will store the 'Alert Select' bit value:
                            MCP9808_DISABLE_ALERT_SELECT         = 0
                            MCP9808_ENABLE_ALERT_SELECT          = 1

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t alertSel;
            int8_t errorCode = MCP9808_GetAlertSelect(i2cParams, &alertSel);			
        </code>

*/
int8_t MCP9808_GetAlertSelect(MCP9808_i2c_params i2cParams, uint8_t* alertSel);


//========================== ALERT POLARITY BIT ==============================//  


/**
    @Summary
        Sets the 'Alert Polarity' bit for MCP9808.

    @Description
        This function allows the user to set the alert output polarity bit value. 
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        bitValue  (in) - The 'Alert Polarity' bit value to be set. Valid options:
                            MCP9808_ALERT_ACTIVE_LOW     (0) - active low
                            MCP9808_ALERT_ACTIVE_HIGH    (1) - active high

    @Returns
        0 for success or error code.

    @Note
        This bit cannot be written when either of the Lock bits are set.
        This bit can be written in Shutdown mode, but the alert output will not
        assert or deassert.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetAlertPolarity(i2cParams, MCP9808_ALERT_ACTIVE_LOW);
        </code>

*/
int8_t MCP9808_SetAlertPolarity(MCP9808_i2c_params i2cParams, uint8_t bitValue);


/**
    @Summary
        Gets the 'Alert Polarity' bit value for MCP9808.

    @Description
        This function returns the currently set alert output polarity bit value.
 
    @Preconditions
        None
 
    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *alertPol (out) - pointer to variable that will store the 'Alert Polarity' bit value:
                            MCP9808_ALERT_ACTIVE_LOW             = 0
                            MCP9808_ALERT_ACTIVE_HIGH            = 1

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t alertPol;
            int8_t errorCode = MCP9808_GetAlertPolarity(i2cParams, &alertPol);
        </code>

*/
int8_t MCP9808_GetAlertPolarity(MCP9808_i2c_params i2cParams, uint8_t* alertPol);


//============================ ALERT MODE BIT ================================//


/**
    @Summary
        Sets the 'Alert Mode' bit for MCP9808.

    @Description
        This function allows to set the alert output mode bit value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        bitValue - The 'Alert Mode' bit value to be set. Valid options:
                        MCP9808_COMPARATOR_OUTPUT    (0) - comparator output
                        MCP9808_INTERRUPT_OUTPUT     (1) - interrupt output

    @Returns
        0 for success or error code.

    @Note
        This bit cannot be written when either of the Lock bits are set.
        This bit can be written in Shutdown mode, but the alert output will not
        assert or deassert.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            int8_t errorCode = MCP9808_SetAlertMode(i2cParams, MCP9808_COMPARATOR_OUTPUT);
        </code>

*/
int8_t MCP9808_SetAlertMode(MCP9808_i2c_params i2cParams, uint8_t bitValue);


/**
    @Summary
        Gets the 'Alert Mode' bit value for MCP9808.

    @Description
        This function returns the currently set alert output mode bit value.
 
    @Preconditions
        None
 
    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.

    @Param
        *alertMode (out) - pointer to variable that will store the 'Alert Mode' bit value:
                    MCP9808_COMPARATOR_OUTPUT        = 0
                    MCP9808_INTERRUPT_OUTPUT         = 1

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t alertMode;
            int8_t errorCode =  MCP9808_GetAlertMode(i2cParams, &alertMode);			
        </code>

*/
int8_t MCP9808_GetAlertMode(MCP9808_i2c_params i2cParams, uint8_t* alertMode);

/**
    @Summary
        Gets the Manufacturer ID register value for MCP9808.

    @Description
        This function provides the Manufacturer ID register value.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.
        
    @Param
        *manufacturerId (out)- pointer to variable that will store the manufacturer ID.

    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint16_t manufacturerId;
            int8_t errorCode = MCP9808_GetManufacturerID(i2cParams, &manufacturerId);
        </code>

*/
int8_t MCP9808_GetManufacturerID(MCP9808_i2c_params i2cParams, uint16_t* manufacturerId);


/**
    @Summary
        Gets the Device ID and the Device Revision values for MCP9808.

    @Description
        This function provides Device ID and the Device Revision values.
 
    @Preconditions
        None

    @Param
        i2cParams (in) - device's I2C address and bus index - see MCP9808_i2c_params structure.
        
    @Param
        *deviceId (out)- pointer to variable that will store the device ID.
        
    @Param
        *deviceRevision (out)- pointer to variable that will store the revision ID.
        
    @Returns
        0 for success or error code.

    @Example
        <code>
            MCP9808_i2c_params i2cParams = {MCP9808_CLIENT_ADDRESS, MCP9808_BUS_ID};
            uint8_t deviceId;
            uint8_t deviceRevision;
            int8_t errorCode = MCP9808_GetDeviceID(i2cParams, &deviceId, &deviceRevision);
        </code>

*/
int8_t MCP9808_GetDeviceID(MCP9808_i2c_params i2cParams, uint8_t* deviceId, uint8_t* deviceRevision);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	// _MCP9808_H

/**
  End of File
*/












