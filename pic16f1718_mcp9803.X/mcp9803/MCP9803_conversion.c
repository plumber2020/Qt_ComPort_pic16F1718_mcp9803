#include "MCP9803_conversion.h"
#include <stdio.h>

// CONVERSION FROM/TO RAW DATA ///////////////////////////////////////////////

float MCP9803_FLOAT_fromRAW2complement(uint16_t data)
{    
    uint16_t sign = data & 0x8000;
    if (sign) {                     // = negative value
        data = (~data) + (1<<4);    // = conversion from 2's complement
    }
    return ((sign)?-1:1)/16.f * (data >> 4); 
}

uint16_t MCP9803_FLOAT_toRAW2complement(float value)
{
    uint8_t sign = (value < 0)?1:0;
    uint16_t data = (uint16_t)(value * 16);
    
    if (sign) {                 // = negative value
        data = (~data) + 1;     // = conversion from 2's complement 
    }
    return (data<<4) | ((sign)?0x8000:0x0);
}

//////////////////////////////////////////////////////////////////////////////

#define ACCURACY_2digits    100 // ~ accuracy 0.01

int MCP9803_STRING_fromRAW2complement(char* str, uint16_t data)
{
    char sign = {' '};
    if (data & 0x8000) {  // for negative sign do conversion from 2's complement
        sign = '-';
        data = ((~data) + 0x0010);
    } 
    return sprintf (str, "%c%u.%u", 
            sign,
            (data>>8)&0xFF, 
            ((data&0xF0)>>4)*ACCURACY_2digits/16 );
}


