
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

// MCP9808 Library Version
// #define MCP9808_LIBVER "2.0.0"

#include "MCP9808.h"

int8_t MCP9808_MODULE_Initialize(MCP9808_i2c_params i2cParams) {
    //Initial settings
    int8_t errorCode = MCP9808_SUCCESS;    
    
    errorCode = MCP9808_SetResolutionRegister(i2cParams, MCP9808_RESOLUTION_0P5);  
    if(errorCode != MCP9808_SUCCESS) goto initialize_exit;

	
	

    errorCode = MCP9808_SetConfigurationRegister(i2cParams, 0);  
    if(errorCode != MCP9808_SUCCESS) goto initialize_exit;

    // The same settings for the Configuration Register can be made individually 
    // using the following functions:

    //errorCode = MCP9808_SetTempHysteresis(i2cParams, MCP9808_HYSTERESIS_0);
    //if(errorCode != MCP9808_SUCCESS) goto initialize_exit;
	
    //errorCode = MCP9808_EnableContinuousConversionMode(i2cParams);  
    //if(errorCode != MCP9808_SUCCESS) goto initialize_exit;
	
	
	
	
    //errorCode = MCP9808_SetAlertControl(i2cParams, MCP9808_DISABLE_ALERT_CONTROL);  
    //if(errorCode != MCP9808_SUCCESS) goto initialize_exit;
	
    //errorCode = MCP9808_SetAlertSelect(i2cParams, MCP9808_DISABLE_ALERT_SELECT);  
    //if(errorCode != MCP9808_SUCCESS) goto initialize_exit;
	
    //errorCode = MCP9808_SetAlertPolarity(i2cParams, MCP9808_ALERT_ACTIVE_LOW);  
    //if(errorCode != MCP9808_SUCCESS) goto initialize_exit;
	
    //errorCode = MCP9808_SetAlertMode(i2cParams, MCP9808_COMPARATOR_OUTPUT);    
    //if(errorCode != MCP9808_SUCCESS) goto initialize_exit; 
    
initialize_exit:
    return errorCode;
}


#if defined(I2C_FSERV_ENABLED)
int8_t MCP9808_Write(MCP9808_i2c_params i2cParams, uint8_t* pdata, uint8_t length) {
    int8_t errorCode = MCP9808_SUCCESS;
    //    //validate the parameters
    //    if( (pdata == NULL) ||
    //        (length == 0) ){
    //        return MCP9808_INVALID_PARAMETER;
    //    }    
    i2c_writeNBytes(i2cParams.i2cAddress, pdata, length);
    return errorCode;
}

int8_t MCP9808_Read(MCP9808_i2c_params i2cParams, uint8_t* pdata, uint8_t length) {
    int8_t errorCode = MCP9808_SUCCESS;
    //    //validate the parameters
    //    if( (pdata == NULL) ||
    //        (length == 0) ){
    //        return MCP9808_INVALID_PARAMETER;
    //    }            

        //read the register value
    i2c_readNBytes(i2cParams.i2cAddress, pdata, length);
    return errorCode;
}
#endif // defined(I2C_FSERV_ENABLED)


#if defined(I2C_CLASSIC_ENABLED)
	
int8_t MCP9808_Write(MCP9808_i2c_params i2cParams, uint8_t* pdata, uint8_t length) {
    volatile I2C_MESSAGE_STATUS(I2CPREF) status; //volatile

//    //validate parameters
//    if( (pdata == NULL) ||
//        (length == 0) ){
//        return MCP9808_INVALID_PARAMETER;
//    }

    switch (i2cParams.i2cBusID) {
#ifdef I2C_CLASSIC_ENABLED
        case 1: 
            I2C_MasterWrite(pdata, length, i2cParams.i2cAddress, (I2C_MESSAGE_STATUS(I2CPREF)*) & status);
            break;
#endif
        default:
            /* i2cBusID is not valid */
            return MCP9808_INVALID_I2C_BUSID;
    }

    //wait for the message to be sent or has changed
    while (status == I2C_MESSAGE_PENDING(I2CPREF));

    if (status != I2C_MESSAGE_COMPLETE(I2CPREF)) {
        return MCP9808_I2C_ERRCLASS | status;
    }
    else {
        return MCP9808_SUCCESS;
    }
}

int8_t MCP9808_Read(MCP9808_i2c_params i2cParams, uint8_t* pdata, uint8_t length) {
    volatile I2C_MESSAGE_STATUS(I2CPREF) status; //volatile

//    //validate the parameters
//    if( (pdata == NULL) ||
//        (length == 0) ){
//        return MCP9808_INVALID_PARAMETER;
//    }

    //read the register value 
    switch (i2cParams.i2cBusID) {
#ifdef I2C_CLASSIC_ENABLED
        case 1: 
            I2C_MasterRead(pdata, length, i2cParams.i2cAddress, (I2C_MESSAGE_STATUS(I2CPREF)*) & status);
            break;
#endif
        default:
            /* i2cBusID is not valid */
            return MCP9808_INVALID_I2C_BUSID;
    }

    //wait for the message to be sent or has changed
    while (status == I2C_MESSAGE_PENDING(I2CPREF));

    if (status != I2C_MESSAGE_COMPLETE(I2CPREF)) {
        return MCP9808_I2C_ERRCLASS | status;
    }
    else {
        return MCP9808_SUCCESS;
    }
}
#endif // defined(I2C_CLASSIC_ENABLED) || defined(I2C1_CLASSIC_ENABLED) || defined(I2C2_CLASSIC_ENABLED) || defined(I2C3_CLASSIC_ENABLED) || defined(I2C4_CLASSIC_ENABLED)


//==================== RESOLUTION ===============================//
int8_t MCP9808_SetResolutionRegister(MCP9808_i2c_params i2cParams, uint8_t registerVal){
    int8_t errorCode = MCP9808_SUCCESS;
    uint8_t writeBuffer[MCP9808_RESOLUTION_SIZE + 1];
    
    //validate the value which should be written in register (0|1|2|3)
    if(registerVal > MCP9808_RESOLUTION_0P0625) return MCP9808_INVALID_RESOLUTION_VALUE;
    
    writeBuffer[0] = MCP9808_RESOLUTION_ADDR;
    writeBuffer[1] = registerVal;
    
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
    return errorCode;
}


int8_t MCP9808_GetResolutionRegister(MCP9808_i2c_params i2cParams, uint8_t* resolutionReg){
    uint8_t rxData[MCP9808_RESOLUTION_SIZE];
    uint8_t registerPointer;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write the register pointer
    registerPointer = MCP9808_RESOLUTION_ADDR;
        
    errorCode =  MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof(registerPointer));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof(rxData));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    *resolutionReg = rxData[0];

    if (*resolutionReg > MCP9808_RESOLUTION_0P0625) {
        return MCP9808_INVALID_RESOLUTION_VALUE;
    } else {
        return MCP9808_SUCCESS;
    }
}


int8_t MCP9808_SetResolutionValue(MCP9808_i2c_params i2cParams, float resolutionVal){
    uint8_t writeBuffer;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //validate the value which should be written in register(0.5|0.25|0.125|0.0625 C)
    if(resolutionVal == (float)0.5){
        writeBuffer = MCP9808_RESOLUTION_0P5;
    }else if(resolutionVal == (float)0.25){
        writeBuffer = MCP9808_RESOLUTION_0P25;
    }else if(resolutionVal == (float)0.125){
        writeBuffer = MCP9808_RESOLUTION_0P125;
    }else if(resolutionVal == (float)0.0625){
        writeBuffer = MCP9808_RESOLUTION_0P0625;
    }else{
        return MCP9808_INVALID_RESOLUTION_VALUE;
    }
    
    errorCode = MCP9808_SetResolutionRegister(i2cParams, writeBuffer);        
    return errorCode;
}

int8_t MCP9808_GetResolutionValue(MCP9808_i2c_params i2cParams, float* resolutionVal){
    uint8_t rxData;
    int8_t errorCode = MCP9808_SUCCESS;
    
    // Get register value
    errorCode = MCP9808_GetResolutionRegister(i2cParams, &rxData);
    if (errorCode != MCP9808_SUCCESS){
        return errorCode;
    }
    
    // Check which value is set
    switch (rxData) {
        case 0x0:
            *resolutionVal = (float) 0.5;
            break;
        case 0x01:
            *resolutionVal = (float) 0.25;
            break;
        case 0x02:
            *resolutionVal = (float) 0.125;
            break;
        case 0x03:
            *resolutionVal = (float) 0.0625;
            break;
    }
    
    return MCP9808_SUCCESS;      
}


//==================== ALERT LIMITS ===============================//
int8_t MCP9808_SetLimitRegister(MCP9808_i2c_params i2cParams, uint8_t alertId, uint16_t registerVal){
    uint8_t writeBuffer[MCP9808_LIMIT_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;

    //validate the value which should be written in register
    if (registerVal > 0x1FFC) { //8188
        return MCP9808_INVALID_LIMIT_VALUE;
    } else {
        switch (alertId) {
            case ALERT_UPPER:
                writeBuffer[0] = MCP9808_ALERT_TEMP_UPPER_LIMIT_ADDR;
                break;
            case ALERT_LOWER:
                writeBuffer[0] = MCP9808_ALERT_TEMP_LOWER_LIMIT_ADDR;
                break;
            case ALERT_CRIT:
                writeBuffer[0] = MCP9808_ALERT_TEMP_CRIT_LIMIT_ADDR;
                break;
            default:
                errorCode = MCP9808_INVALID_PARAMETER;
                return errorCode;
        }
        writeBuffer[1] = registerVal >> 8;
        writeBuffer[2] = registerVal & 0xFC;

        errorCode = MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof (writeBuffer));
        return errorCode;        
    }
}


int8_t MCP9808_GetLimitRegister(MCP9808_i2c_params i2cParams, uint8_t alertId, uint16_t* registerVal){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_LIMIT_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;

    // write the register pointer
    switch (alertId) {
        case ALERT_UPPER:
            registerPointer = MCP9808_ALERT_TEMP_UPPER_LIMIT_ADDR;
            break;
        case ALERT_LOWER:
            registerPointer = MCP9808_ALERT_TEMP_LOWER_LIMIT_ADDR;
            break;
        case ALERT_CRIT:
            registerPointer = MCP9808_ALERT_TEMP_CRIT_LIMIT_ADDR;
            break;
        default:
            errorCode = MCP9808_INVALID_PARAMETER;
            return errorCode;
    }
        
    errorCode =  MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof(registerPointer));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    // read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof(rxData));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    *registerVal = ((uint16_t)rxData[0] << 8) | (uint16_t)rxData[1];
    return MCP9808_SUCCESS;
}


int8_t MCP9808_SetLimitValue(MCP9808_i2c_params i2cParams, uint8_t alertId, float tempVal){
    int16_t writeValue;
    uint16_t regValue;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //validate the value which should be written in register
    if(tempVal < -255.75 || tempVal > 255.75){
        return MCP9808_INVALID_LIMIT_VALUE;
    }else{
        writeValue = (int16_t)((float)tempVal * 16);
        regValue = (uint16_t)writeValue & 0x1FFC; //clear the three MSB and the two LSB
        errorCode = MCP9808_SetLimitRegister(i2cParams, alertId, regValue);
        return errorCode;       
    }
}


int8_t MCP9808_GetLimitValue(MCP9808_i2c_params i2cParams, uint8_t alertId, float* tempVal){
    float temperature;
    int8_t errorCode = MCP9808_SUCCESS;
    uint16_t regVal;
    int16_t signedVal;
    
    errorCode = MCP9808_GetLimitRegister(i2cParams, alertId, &regVal);
    if(errorCode != MCP9808_SUCCESS) return errorCode;   
    
    // sign-extend the bit #12 of the register value
    if ((regVal & BIT_12) == BIT_12){
        regVal = regVal | 0xE000;
    }
    
    signedVal = (int16_t)regVal;
    temperature = (float)signedVal;
    *tempVal = temperature / 16;
    
    return MCP9808_SUCCESS;
}


//==================== TEMPERATURE ===============================//
int8_t MCP9808_GetTemperatureRegister(MCP9808_i2c_params i2cParams, uint16_t* registerVal){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_TEMPERATURE_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_TEMPERATURE_ADDR;
    
    errorCode =  MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof(registerPointer));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    // read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof(rxData));
    if(errorCode != MCP9808_SUCCESS) return errorCode;  
    
    *registerVal = ((uint16_t)rxData[0] << 8) | (uint16_t)rxData[1];

    return MCP9808_SUCCESS;
}


int8_t MCP9808_GetTemperatureValue(MCP9808_i2c_params i2cParams, MCP9600_alert_flags* alertFlags, float* tempVal){
    uint16_t regVal;
    int16_t signedVal;
    float temperature;
    int8_t errorCode = MCP9808_SUCCESS;   
    
    errorCode = MCP9808_GetTemperatureRegister(i2cParams, &regVal);
    if(errorCode != MCP9808_SUCCESS) return errorCode;   
    
    //first check flag bits
    //alert output temperature critical limit
    if ((regVal & BIT_15) == BIT_15) {
        alertFlags->tCrit = MCP9808_ALERT_OUTPUT_ASSERTED;
    }else{
        alertFlags->tCrit = MCP9808_ALERT_OUTPUT_NOT_ASSERTED;
    }
    
    //alert output temperature upper limit
    if ((regVal & BIT_14) == BIT_14) {
        alertFlags->tUpper = MCP9808_ALERT_OUTPUT_ASSERTED;
    }else{
        alertFlags->tUpper = MCP9808_ALERT_OUTPUT_NOT_ASSERTED;
    }
    
    //alert output temperature lower limit
    if ((regVal & BIT_13) == BIT_13) {
        alertFlags->tLower = MCP9808_ALERT_OUTPUT_ASSERTED;
    }else{
        alertFlags->tLower = MCP9808_ALERT_OUTPUT_NOT_ASSERTED;
    }

    // temp value sign extension over the flag bits
    if ((regVal & BIT_12) == BIT_12) {
        //temperature < 0
        regVal = regVal | 0xE000;
    } else {
        //temperature > 0
        regVal = regVal & 0x1FFF; //clear the flags
    }
    
    signedVal = (int16_t)regVal;
    temperature = (float)signedVal;
    *tempVal = temperature / 16;
    
    return MCP9808_SUCCESS;
}


//=================== CONFIGURATION REGISTER =======================//
int8_t MCP9808_SetConfigurationRegister(MCP9808_i2c_params i2cParams, uint16_t registerVal){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    writeBuffer[0] = MCP9808_CONFIG_ADDR;
    writeBuffer[1] = (registerVal & 0xff00) >> 8;
    writeBuffer[2] = registerVal & 0xff;
    
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
    return errorCode;
}


int8_t MCP9808_GetConfigurationRegister(MCP9808_i2c_params i2cParams, uint16_t* registerVal){
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    uint8_t registerPointer;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    
    errorCode =  MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof(registerPointer));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof(rxData));
    if(errorCode != MCP9808_SUCCESS) return errorCode;

    *registerVal = ((uint16_t)rxData[0] << 8) | (uint16_t)rxData[1];

    return MCP9808_SUCCESS;  
}


//====================== HYSTERESIS TEMPERATURE ==============================//
int8_t MCP9808_SetTempHysteresis(MCP9808_i2c_params i2cParams, uint8_t hystBitVal){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //validate the value which should be written in register
    if( hystBitVal > MCP9808_HYSTERESIS_6) return MCP9808_INVALID_HYSTERESIS_VALUE;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

    errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value at &writeBuffer[1]
    errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //change the hysteresis bits 
    writeBuffer[1] = (uint8_t)((writeBuffer[1] & 0xf9) | (hystBitVal << 1));

    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
    return errorCode;
}


int8_t MCP9808_GetTempHysteresis(MCP9808_i2c_params i2cParams, uint8_t* hystBitVal){
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    uint8_t registerPointer;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer for Configuration register
    registerPointer = MCP9808_CONFIG_ADDR;
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;
    
    *hystBitVal = (rxData[0] & 0x06) >> 1;
    return MCP9808_SUCCESS;
}


int8_t MCP9808_SetTempHysteresisValue(MCP9808_i2c_params i2cParams, float hystValue){
    uint8_t bitValue;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //validate the value which should be written in register
    if(hystValue == 0){
        bitValue = MCP9808_HYSTERESIS_0;
    }else if(hystValue == 1.5){
        bitValue = MCP9808_HYSTERESIS_1P5;
    }else if(hystValue == 3){
        bitValue = MCP9808_HYSTERESIS_3;
    }else if(hystValue == 6){
        bitValue = MCP9808_HYSTERESIS_6;
    }else{
        return MCP9808_INVALID_HYSTERESIS_VALUE;
    }
    
    errorCode = MCP9808_SetTempHysteresis(i2cParams, bitValue);
    return errorCode;
}


int8_t MCP9808_GetTempHysteresisValue(MCP9808_i2c_params i2cParams, float* hystValue){
    uint8_t bitValue;
    int8_t errorCode = MCP9808_SUCCESS;
    
    errorCode = MCP9808_GetTempHysteresis(i2cParams, &bitValue);
    if (errorCode != MCP9808_SUCCESS) return errorCode;
    
    switch (bitValue) {
        case MCP9808_HYSTERESIS_0:
            *hystValue = 0;
            return MCP9808_SUCCESS;
        case MCP9808_HYSTERESIS_1P5:
            *hystValue = 1.5;
            return MCP9808_SUCCESS;
        case MCP9808_HYSTERESIS_3:
            *hystValue = 3.0;
            return MCP9808_SUCCESS;
        case MCP9808_HYSTERESIS_6:
            *hystValue = 6.0;
            return MCP9808_SUCCESS;
    }
    return MCP9808_INVALID_HYSTERESIS_VALUE;
}


//========================= SHUTDOWN MODE ====================================//
int8_t MCP9808_EnableShutdownMode(MCP9808_i2c_params i2cParams){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

    errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value at &writeBuffer[1]
    errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //set the SHDN bit
    writeBuffer[1] = writeBuffer[1] | MCP9808_SHUTDOWN_MODE;
    
    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));
    return errorCode;
}


int8_t MCP9808_EnableContinuousConversionMode(MCP9808_i2c_params i2cParams){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

    errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value at &writeBuffer[1]
    errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //clear the SHDN bit
    writeBuffer[1] = writeBuffer[1] & 0xfe; // (MCP9808_POWER_MODE)
    
    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
    return errorCode;
}


int8_t MCP9808_GetTemperatureConversionStatus(MCP9808_i2c_params i2cParams, uint8_t* convStatus){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    *convStatus = rxData[0] & BIT_0;
    return MCP9808_SUCCESS;
}


//========================= CRITICAL LOCK BIT ================================//
int8_t MCP9808_SetCriticalLock(MCP9808_i2c_params i2cParams){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;

    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

    errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value at &writeBuffer[1]
    errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;
    
    //set the Crit. Lock bit
    writeBuffer[2] = writeBuffer[2] | MCP9808_CRITICAL_LOCK_BIT;
    
    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
    return errorCode;
}


int8_t MCP9808_GetCriticalLock(MCP9808_i2c_params i2cParams, uint8_t* critLock){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    *critLock = (rxData[1] & BIT_7) >> 7;
    return MCP9808_SUCCESS;
}


//========================= WINDOW LOCK BIT ==================================//
int8_t MCP9808_SetWindowLock(MCP9808_i2c_params i2cParams){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

    errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value at &writeBuffer[1]
    errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;
    
    //set the Win. Lock bit
    writeBuffer[2] = writeBuffer[2] | MCP9808_WINDOW_LOCK_BIT;
    
    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
    return errorCode;
}


int8_t MCP9808_GetWindowLock(MCP9808_i2c_params i2cParams, uint8_t* windowLock){
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    uint8_t registerPointer;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    *windowLock = (rxData[1] & BIT_6) >> 6;
    return MCP9808_SUCCESS;
}


//========================= INTERRUPT CLEAR BIT ==============================//
int8_t MCP9808_ClearInterrupt(MCP9808_i2c_params i2cParams){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //read current configuration register
    writeBuffer[0] = MCP9808_CONFIG_ADDR;

    errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value at &writeBuffer[1]
    errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
    if (errorCode != MCP9808_SUCCESS) return errorCode;
    
    //set the Int. clear bit
    writeBuffer[2] = writeBuffer[2] | MCP9808_INTERRUPT_CLEAR_BIT;
    
    //write back the register
    errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
    return errorCode;
}


//========================== ALERT STATUS BIT ================================//
int8_t MCP9808_GetAlertStatus(MCP9808_i2c_params i2cParams, uint8_t* alertStat){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    *alertStat = (rxData[1] & BIT_4) >> 4;
    return MCP9808_SUCCESS;
}


//=========================== ALERT CONTROL BIT ==============================//
int8_t MCP9808_SetAlertControl(MCP9808_i2c_params i2cParams, uint8_t bitValue){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;

    //validate the value which should be written in register
    if (bitValue < 0x02) {
        //read current configuration register
        writeBuffer[0] = MCP9808_CONFIG_ADDR;

        errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
        if (errorCode != MCP9808_SUCCESS) return errorCode;

        //read the register value at &writeBuffer[1]
        errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
        if (errorCode != MCP9808_SUCCESS) return errorCode;
        
        // change the Alert Cnt. bit
        writeBuffer[2] = (uint8_t)((writeBuffer[2] & 0xf7) | (bitValue << 3)); 
        
        //write back the register
        errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
        return errorCode;
    }else{
        return MCP9808_INVALID_ALERT_CONTROL_BIT;
    }
}


int8_t MCP9808_GetAlertControl(MCP9808_i2c_params i2cParams, uint8_t* alertCtrl){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    *alertCtrl = (rxData[1] & BIT_3) >> 3;
    return MCP9808_SUCCESS;
}


//=========================== ALERT SELECT BIT ===============================//
int8_t MCP9808_SetAlertSelect(MCP9808_i2c_params i2cParams, uint8_t bitValue){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //validate the value which should be written in register
    if(bitValue < 0x02){
        //read current configuration register
        writeBuffer[0] = MCP9808_CONFIG_ADDR;

        errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
        if (errorCode != MCP9808_SUCCESS) return errorCode;

        //read the register value at &writeBuffer[1]
        errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
        if (errorCode != MCP9808_SUCCESS) return errorCode;
        
        //change the Alert Sel. bit
        writeBuffer[2] = (uint8_t)((writeBuffer[2] & 0xFB) | (bitValue << 2));
        
        //write back the register
        errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
        return errorCode;            
    }else{
        return MCP9808_INVALID_ALERT_SELECT_BIT;
    }
}


int8_t MCP9808_GetAlertSelect(MCP9808_i2c_params i2cParams, uint8_t* alertSel){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    *alertSel = (rxData[1] & BIT_2) >> 2;
    return MCP9808_SUCCESS;
}


//========================== ALERT POLARITY BIT ==============================//  
int8_t MCP9808_SetAlertPolarity(MCP9808_i2c_params i2cParams, uint8_t bitValue){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //validate the value which should be written in register
    if(bitValue < 0x02){
        //read current configuration register
        writeBuffer[0] = MCP9808_CONFIG_ADDR;

        errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
        if (errorCode != MCP9808_SUCCESS) return errorCode;

        //read the register value at &writeBuffer[1]
        errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
        if (errorCode != MCP9808_SUCCESS) return errorCode;
        
        //change the Alert Pol. bit
        writeBuffer[2] = (uint8_t)((writeBuffer[2] & 0xfd) | (bitValue << 1));
        
        //write back the register
        errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
        return errorCode;   
    }else{
        return MCP9808_INVALID_ALERT_POLARITY_BIT;
    }
}


int8_t MCP9808_GetAlertPolarity(MCP9808_i2c_params i2cParams, uint8_t* alertPol){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    *alertPol = (rxData[1] & BIT_1) >> 1;
    return MCP9808_SUCCESS;
}


//============================ ALERT MODE BIT ================================//
int8_t MCP9808_SetAlertMode(MCP9808_i2c_params i2cParams, uint8_t bitValue){
    uint8_t writeBuffer[MCP9808_CONFIG_SIZE + 1];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //validate the value which should be written in register
    if(bitValue < 0x02){
        //read current configuration register
        writeBuffer[0] = MCP9808_CONFIG_ADDR;

        errorCode = MCP9808_Write(i2cParams, writeBuffer, MCP9808_REGISTER_PTR_SIZE);
        if (errorCode != MCP9808_SUCCESS) return errorCode;

        //read the register value at &writeBuffer[1]
        errorCode = MCP9808_Read(i2cParams, writeBuffer + 1, MCP9808_CONFIG_SIZE);
        if (errorCode != MCP9808_SUCCESS) return errorCode;
        
        //change the Alert Mod. bit
        writeBuffer[2] = (writeBuffer[2] & 0xfe) | bitValue;
        
        //write back the register
        errorCode =  MCP9808_Write(i2cParams, writeBuffer, (uint8_t)sizeof(writeBuffer));        
        return errorCode;  
    }else{
        return MCP9808_INVALID_ALERT_MODE_BIT;
    }
}


int8_t MCP9808_GetAlertMode(MCP9808_i2c_params i2cParams, uint8_t* alertMode){
    uint8_t registerPointer;
    uint8_t rxData[MCP9808_CONFIG_SIZE];
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write register pointer
    registerPointer = MCP9808_CONFIG_ADDR;
    
    errorCode = MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof (registerPointer));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof (rxData));
    if (errorCode != MCP9808_SUCCESS) return errorCode;

    *alertMode = rxData[1] & BIT_0;
    return MCP9808_SUCCESS;
}


//============================ DEVICE INFORMATION ================================//
int8_t MCP9808_GetManufacturerID(MCP9808_i2c_params i2cParams, uint16_t* manufacturerId){
    uint8_t rxData[MCP9808_MANUFACTURER_SIZE];
    uint8_t registerPointer;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write the register pointer
    registerPointer = MCP9808_MANUFACTURER_ID_ADDR;
        
    errorCode =  MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof(registerPointer));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof(rxData));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    *manufacturerId = ((uint16_t)rxData[0] << 8) | (uint16_t)rxData[1];

    return MCP9808_SUCCESS;
}


int8_t MCP9808_GetDeviceID(MCP9808_i2c_params i2cParams, uint8_t* deviceId, uint8_t* deviceRevision){
    uint8_t rxData[MCP9808_DEVICE_ID_REV_SIZE];
    uint8_t registerPointer;
    int8_t errorCode = MCP9808_SUCCESS;
    
    //write the register pointer
    registerPointer = MCP9808_DEVICE_ID_ADDR;
        
    errorCode =  MCP9808_Write(i2cParams, &registerPointer, (uint8_t)sizeof(registerPointer));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    //read the register value
    errorCode = MCP9808_Read(i2cParams, rxData, (uint8_t)sizeof(rxData));
    if(errorCode != MCP9808_SUCCESS) return errorCode;
    
    *deviceId       = rxData[0];
    *deviceRevision = rxData[1];

    return MCP9808_SUCCESS;
}


