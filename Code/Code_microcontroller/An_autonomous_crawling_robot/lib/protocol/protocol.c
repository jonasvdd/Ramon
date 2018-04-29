/*
 * protocol.c
 *
 *  Created on: May 08, 2017
 *      Author: Jonas Van Der Donckt
 */


 /****************************************************
 LIBRARIES
 ****************************************************/
#include "protocol.h"
#include <avr/delay.h>
#include <avr/io.h>



/****************************************************
FUNCTIONS
****************************************************/
void transmit_data(struct Dataobj *dObj)
{
    /* transmit start character */
    transmit_USART(START_TYPE);
    _delay_ms(1);

    /* transmits data type */
    transmit_USART(dObj->type);
    _delay_ms(1);

    /* transmit data */
    for (unsigned char i = 0; i < (dObj->dataSize); i++) {
        transmit_USART((unsigned char)(dObj->data >> 8*i));
        _delay_ms(1);
    }

    /* transmit end character */
    transmit_USART(END_TYPE);
}


void init_QvalProtocol(int QVal, struct Dataobj *Q_Data){
    /* initialize the type */
    Q_Data->type =  Q_VALUE_TYPE;

    /* initialize the size */
    Q_Data->dataSize = sizeof(int*);

    /* put the data in an integer */
    Q_Data->data = QVal;
}


void init_PositionProtocol(unsigned char position[2], struct Dataobj *posObj){
    /* initialize the type */
    posObj->type =  POSITION_TYPE;

    /* initialize the data size */
    posObj->dataSize = sizeof(position);

    /* put the data in an integer */
    int posData = (int)position[0];
    posData |= (int)(position[1] << 8);
    posObj->data = posData;
}


void init_SizeProtocol(unsigned char size[2], struct Dataobj *sizeObj){
    /* initialize the type */
    sizeObj->type = TABLE_TYPE;

    /* initialize the data size */
    sizeObj->dataSize = sizeof(size);

    /* put the data in an integer */
    int sizeData = (int)size[0];
    sizeData |= (int)(size[1] << 8);
    sizeObj->data = sizeData;
}
