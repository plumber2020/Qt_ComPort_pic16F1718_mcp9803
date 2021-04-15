/* 
 * File:   MCP9803_init.h
 * Author: abram
 *
 * Created on March 13, 2021, 6:28 PM
 */

#ifndef MCP9803_INIT_H
#define	MCP9803_INIT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/*
 * MCP9803 Connections :
 * PORT  | PIN  | Direction |  PullUP  | Operation              | Interrupt
 * --------------------------------------------------------------------------
 * PORTB |  B4  |   in      | external | Operational_Mode       | -
 * PORTC |  C3  |           | external | I2C SCL                | I2C
 * PORTC |  C4  |           | external | I2C SDA                | I2C
 * PORTC |  C5  |   input   | external | ALERT                  | IOC (any)
 * PORTC |  C6  |   output  |   none   | USART Tx               | USART
 * PORTC |  C7  |   input   |   none   | USART Rx               | USART
 
 */ 
   
#define TEMPLATE_OUTPUT_COMMENT         "#%s%s\r\n"   
#define TEMPLATE_OUTPUT_DEVICE_NAME     "%s:%u; "    //%s:%u = name:address
#define TEMPLATE_OUTPUT_DEVICE_VALUE    "%s "      //value
#define TEMPLATE_OUTPUT_ENDLINE         "\r\n"      //\r\n
      
void MCP9803_Initialize();
void MCP9803_CheckTemperature();

#ifdef	__cplusplus
}
#endif

#endif	/* MCP9803_INIT_H */

