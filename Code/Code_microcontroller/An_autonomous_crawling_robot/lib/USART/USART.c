/**
 * USART.c
 *
 *  Created on: May 14, 2017
 *      Author: Jonas Van Der Donckt
 */


 /****************************************************
 LIBRARIES
 ****************************************************/
#include "USART.h"
#include <avr/interrupt.h>



/****************************************************
FUNCTIONS
****************************************************/
void initUSART()
{
    /* configuring the baud rate */
    UBRR1H = (BYTE)(UBBRVAL >> 8);
    UBRR1L = (BYTE)(UBBRVAL);

    /*enable the reciever and transmitter */
    SET_BIT_HIGH(UCSR1B, RXEN1);
    SET_BIT_HIGH(UCSR1B, TXEN1);

    /****************************************************
    frame format
    ****************************************************/
    /* 8 data bits */
    SET_BIT_LOW(UCSR1B, UCSZ12);
    SET_BIT_HIGH(UCSR1C, UCSZ11);
    SET_BIT_HIGH(UCSR1C, UCSZ10);

    /* disable parity */
    SET_BIT_LOW(UCSR1C, UPM11);
    SET_BIT_LOW(UCSR1C, UPM10);

    /* 2 stop bits */
    SET_BIT_HIGH(UCSR1C, USBS1);
}


void transmit_USART(BYTE data)
{
    /* wait for empty transmit buffer */
    while (! (UCSR1A & (1 << UDRE1))) {}

    /* place data into the trasmitter buffer*/
    UDR1 = data;
}


unsigned char Receive_USART ()
{
    /* wait for the data to be recieved */
    while (! (UCSR1A & (1 << RXC1))) {}

    /* get and return received data from buffer*/
    return UDR1;
}
