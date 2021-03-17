#include "MCP9803.h"

/*
 * example:
 MCP9803_Type mcp9803 = MCP9803_Init(
            MCP9803_ADDRESS_BYTE(0x0),
            ( // CONFIG
                 MCP9803_ONE_SHOT_DISABLED
              |  MCP9803_ADC_RESOLUTION_11_BIT
              |  MCP9803_FAULT_QUEUE_1
              |  MCP9803_ALERT_POLARITY_ACTIVE_HIGH
              |  MCP9803_COMPARATOR_MODE
              |  MCP9803_SHUTDOWN_DISABLE 
            ),
            &I2C_ReadDataBlock,
            &I2C_WriteDataBlock,
 );
 */

MCP9803_Type MCP9803_Init(uint8_t address,
                          uint8_t config, 
                          i2c_readMCP9803_Type read_handler,
                          i2c_writeMCP9803_Type write_handler )
{
    MCP9803_Type mcp9803;
    mcp9803.m_address = address;
    mcp9803.m_config = config;
    mcp9803.m_data = 0;
    mcp9803.m_flag.full = 0;

    mcp9803.i2c_read_handler = read_handler;
    mcp9803.i2c_write_handler = write_handler;
    return mcp9803;
}

void MCP9803_SetOperationMode(MCP9803_Type* mcp9803, MCP9803_PWR_MODE mode)
{
    mcp9803->m_config &= ~((uint8_t)ONE_SHOT);
    if (mode == ONE_SHOT) {
        mcp9803->m_config |= MCP9803_SHUTDOWN_ENABLE;
    }
    MCP9803_SetConfiguration(mcp9803);
    mcp9803->m_config |= (uint8_t)mode;
}
void MCP9803_SetConfiguration(MCP9803_Type* mcp9803)
{
    mcp9803->i2c_write_handler(
        mcp9803->m_address, MCP9803_CONFIG_REGISTER,&mcp9803->m_config, 1);     
}
void MCP9803_GetConfiguration(MCP9803_Type* mcp9803)
{
    mcp9803->i2c_read_handler(
        mcp9803->m_address, MCP9803_CONFIG_REGISTER, &mcp9803->m_config, 1); 
}

void MCP9803_SetTemperature(MCP9803_Type* mcp9803, uint8_t reg, uint16_t data)
{
    uint8_t raw_data[2] = {(uint8_t)(data>>8), (uint8_t)(data)};
    mcp9803->i2c_write_handler(mcp9803->m_address, reg, raw_data, 2);     
}

uint16_t MCP9803_GetTemperature(MCP9803_Type* mcp9803, uint8_t reg)
{  
    uint8_t raw_data[2];
    mcp9803->i2c_read_handler(mcp9803->m_address, reg, raw_data, 2);
    return ((uint16_t)raw_data[0] << 8) | (raw_data[1]);
}

bool MCP9803_IsAlert(MCP9803_Type* mcp9803)
{
    return mcp9803->m_flag.alert;
}

void MCP9803_SetAlert(MCP9803_Type* mcp9803, bool alert)
{
    mcp9803->m_flag.alert = 
        (mcp9803->m_config & MCP9803_ALERT_POLARITY_ACTIVE_HIGH) == alert;
}


