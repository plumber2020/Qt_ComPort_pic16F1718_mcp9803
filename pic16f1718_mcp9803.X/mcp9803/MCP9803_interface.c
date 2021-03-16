#include "../mcc_generated_files/i2c_master.h"
#include "MCP9803_interface.h"

// MCP9803 I2C interface /////////////////////////////////////////////////////

typedef struct
{
    size_t len;
    uint8_t *data;
} i2c_buffer_t;

static i2c_operations_t rd_BlkRegCompleteHandler(void *p)
{
    I2C_SetBuffer(((i2c_buffer_t *)p)->data,((i2c_buffer_t*)p)->len);
    I2C_SetDataCompleteCallback(NULL,NULL);
    return I2C_RESTART_READ;
}
static i2c_operations_t wr_BlkRegCompleteHandler(void *p)
{
    I2C_SetBuffer(((i2c_buffer_t *)p)->data,((i2c_buffer_t*)p)->len);
    I2C_SetDataCompleteCallback(NULL,NULL);
    return I2C_CONTINUE;
}

void i2cMCP9803_readDataBlock(uint8_t address, uint8_t reg, void* data, size_t len)
{
    i2c_buffer_t d;
    d.data = data;
    d.len = len;

    while(!I2C_Open(address)); // sit here until we get the bus..
    I2C_SetDataCompleteCallback(rd_BlkRegCompleteHandler,&d);
    I2C_SetBuffer(&reg,1);
    I2C_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C_MasterWrite();
    while(I2C_BUSY == I2C_Close()); // sit here until finished.
}
void i2cMCP9803_writeDataBlock(uint8_t address, uint8_t reg, void* data, size_t len)
{
    i2c_buffer_t d;
    d.data = data;
    d.len = len;

    while(!I2C_Open(address)); // sit here until we get the bus..
    I2C_SetDataCompleteCallback(wr_BlkRegCompleteHandler,&d);
    I2C_SetBuffer(&reg,1);
    I2C_SetAddressNackCallback(NULL,NULL); //NACK polling?
    I2C_MasterWrite();
    while(I2C_BUSY == I2C_Close()); // sit here until finished.
}