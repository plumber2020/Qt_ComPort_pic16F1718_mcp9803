/* 
 * File:   MCP9803_conversion.h
 * Author: abram
 *
 * Created on March 15, 2021, 11:59 AM
 */

#ifndef MCP9803_CONVERSION_H
#define	MCP9803_CONVERSION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
// FLOAT CONVERSION FROM/TO RAW DATA /////////////////////////////////////////
    
float    MCP9803_FLOAT_fromRAW2complement(uint16_t);
uint16_t MCP9803_FLOAT_toRAW2complement(float);

// STRING[8] CONVERSION FROM/TO RAW DATA /////////////////////////////////////

int MCP9803_STRING_fromRAW2complement(char* str, uint16_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* MCP9803_CONVERSION_H */

