/* 
 * File:   MCP9803_i2c.h
 * Author: abram
 *
 * Created on March 15, 2021, 11:17 AM
 */

#ifndef MCP9803_INTERFACE_H
#define	MCP9803_INTERFACE_H

#ifdef	__cplusplus
extern "C" {
#endif

// MCP9803 I2C interface /////////////////////////////////////////////////////

void i2cMCP9803_readDataBlock (uint8_t address, uint8_t reg, void* data, size_t len);
void i2cMCP9803_writeDataBlock(uint8_t address, uint8_t reg, void* data, size_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* MCP9803_INTERFACE_H */

