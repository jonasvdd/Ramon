/**
* @file movementDecoder.h
* @author Jonas Van Der Donckt
* @date 13/05/2017
* @brief This library contains functions to determine the direction by using 2 optosensores.
* Before using the movementDecoder's methods, call the initMovementDecoder() function.
*/

#ifndef MOVEMENTDECODER_H_
#define MOVEMENTDECODER_H_


/****************************************************
LIBRARIES
****************************************************/
#include "tools.h"



/****************************************************
CONSTANTS
****************************************************/
/* adjustable optosensor ports */
#define DECODER1_PORT   PORTD
#define DECODER1_DIR    DDRD
#define DECODER1_DATA   PIND
#define DECODER1        PORTD0          //!< connect the DO pin of optosensor 1 to this port
#define DECODER1_INT    INT0_vect       //!< the interrupt used by optosensor 1

#define DECODER2_PORT   PORTD
#define DECODER2_DIR    DDRD
#define DECODER2_DATA   PIND
#define DECODER2        PORTD1          //!< connect the DO pin of optosensor 1 to this port
#define DECODER2_INT    INT1_vect       //!< the interrupt used by optosensor2



/****************************************************
MACROS
****************************************************/
/* converting gray bits to binary, only works for 2 bits */
#define GRAY_TO_BIN(GRAY)   (GRAY & (1 << 1)) ? (TOGGLE_BIT(GRAY, 0)) : (0)



/****************************************************
FUNCTIONS
****************************************************/
/**
* @brief Initializes the optosensor.
* This function sets up the optosensores to generate interrupts and using
* other functions implemented in this library to retrieve the movement of the agent.
*/
void initMovementDecoder();


/**
* @brief Determines the movement direction of the agent.
* This function uses the current and previous state of the optosensors to
* determine the direction.
*/
inline void checkMovementDir();


/**
* @brief Returns the dirCount value
*/
int getMovementDirCount();


/**
* @brief Clears the dirCount value
*/
void clearDirCount();
#endif
