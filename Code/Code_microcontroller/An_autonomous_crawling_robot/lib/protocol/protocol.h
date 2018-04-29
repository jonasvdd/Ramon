/**
 * @file protocol.h
 * @brief This library contains the custom protocol used to send data
 * to a peripheral device which uses the same protocol to receive them.
 * @author Jonas Van Der Donckt
 * @date 14/05/2017
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_


/****************************************************
LIBRARIES
****************************************************/
#include "USART.h"
#include "tools.h"



/****************************************************
CONSTANTS
****************************************************/
#define Q_VALUE_TYPE        'q'
#define POSITION_TYPE       'p'
#define TABLE_TYPE          't'

#define START_TYPE          's'
#define END_TYPE            'e'



/****************************************************
MACROS & STRUCTS
****************************************************/
#define UCHAR_SIZE          (sizeof(unsigned char))
#define CHAR_SIZE           (sizeof(char))
#define INT_SIZE            (sizeof(int))
#define FLOAT_SIZE          (sizeof(float))

/**
* @brief  This struct contains the parameters of the data object that can
* be used to transmit data
* @param type this parameter contains the representation of the data
* @param DataSize contains the amount of bytes of the data
*/
struct Dataobj{
    unsigned char type;
    unsigned char dataSize;
    int data;
};



/****************************************************
FUNCTIONS
****************************************************/
/**
* @brief Transmits the datastruct
* @param dObj passes a reference to the Dataobj that needs to be transmitted
*/
void transmit_data(struct Dataobj *dObj);


/**
* @brief Initializes a Q_value data object
* @param Qval the Q value
* @param Q_Data passes a reference to the Dataobj that needs to be initialized
*/
void init_QvalProtocol(int QVal, struct Dataobj *Q_Data);


/**
* @brief Initializes a position data object
* @param position the indices of the position (row, column)
* @param dataObj1 passes areference to the Dataobj that needs to be initialized
*/
void init_PositionProtocol(unsigned char position[2], struct Dataobj *posObj);


/**
* @brief Initializes a size data object
* @param size the indices of the Q_table's size (row, column)
* @param sizeObj passes a reference to the Dataobj that needs to be initialized
*/
void init_SizeProtocol(unsigned char size[2], struct Dataobj *sizeObj);
#endif
