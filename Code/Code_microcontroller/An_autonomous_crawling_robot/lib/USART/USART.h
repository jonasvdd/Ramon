/**
* @file USART.h
* @brief This library contains functions to transmit data with the USART protocol.
* Before using the USART's methods, call the initUSART() function.
* @author Jonas Van Der Donckt
* @date 14/05/2017
*/

#ifndef USART_H_
#define USART_H_


/****************************************************
LIBRARIES
****************************************************/
#include "tools.h"



/****************************************************
CONSTANTS
****************************************************/
#define BAUDRATE        (long)9600      //!< adapt to change BAUDRATE
#define UBBRVAL         (F_CPU/(16*BAUDRATE) - 1)



/****************************************************
FUNCTIONS
****************************************************/
/**
* @brief Initializes the USART protocol and configures the frame format.
* This function should be called before using any of the other methods within
* this library.
*/
void initUSART();


/**
* @brief Transmits data with the USART protocol.
* @param data this is the data that will be transmitted.
*/
void transmit_USART(BYTE data);


/**
* @brief Receives data with the USART protocol.
*/
unsigned char Receive_USART();
#endif
