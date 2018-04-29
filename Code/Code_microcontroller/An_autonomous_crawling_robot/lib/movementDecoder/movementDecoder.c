/*
 * movementDecoder.c
 *
 *  Created on: May 13, 2017
 *      Author: Jonas
 */

/****************************************************
LIBRARIES
****************************************************/
#include "movementDecoder.h"
#include <avr/interrupt.h>



/****************************************************
VARIABLES
****************************************************/
BYTE prevAngleState = 0;        //!< The first time prevAngleState is unknown, represented by the MSB of prevAngleState
                                //!<    BIT 7:    (MSB) bool prevAngleStateKnown
                                //!<    BIT 0-1:  the binary value of prevAngleState
int dirCount = 0;               //!< Value = movement, sign = direction



/****************************************************
FUNCTIONS
****************************************************/
void initMovementDecoder()
{
  /* configuring the optoswitches' pins to input */
  SET_PIN_INPUT(DECODER1_DIR, DECODER1);
  SET_PIN_INPUT(DECODER2_DIR, DECODER2);

  /* enabling the pullups */
  SET_PIN_HIGH(DECODER1_PORT, DECODER1);
  SET_PIN_HIGH(DECODER2_PORT, DECODER2);


  /****************************************************
  INT0, INT1
  ****************************************************/
  /* configure interrupt requests on any edge */
  SET_BIT_LOW(EICRA, ISC01);
  SET_BIT_HIGH(EICRA, ISC00);

  SET_BIT_LOW(EICRA, ISC11);
  SET_BIT_HIGH(EICRA, ISC10);

  /* enable interrupts */
  SET_BIT_HIGH(EIMSK, INT0);
  SET_BIT_HIGH(EIMSK, INT1);
}


inline void checkMovementDir()
{
    /* if the previous state is known */
    /* this condition will be true most of the time so it is put first */
    if (GET_BIT(prevAngleState, 7)) {
        /* to retrieve the values of prevAngleState */
        SET_BIT_LOW(prevAngleState, 7);

        /* getting the gray value from the optoswitches */
        BYTE currentState = GET_BIT(DECODER1_DATA, DECODER1);
        currentState |= (GET_BIT(DECODER2_DATA, DECODER2 ) << 1);

        /* converting the gray value to binary */
        GRAY_TO_BIN(currentState);

        /* determining the movement direction */
        if (prevAngleState != currentState) {
            BYTE nextForward;

            /* avoiding modulo operation */
            if (prevAngleState == 3) {
                nextForward = 0;
            }
            else {
                nextForward = 1 + prevAngleState;
            }

            if (nextForward == currentState) {
                dirCount++;     // forward movement
            }
            else {
                dirCount--;     // backward movement
            }
        }
        prevAngleState = currentState;
    }

    /* the previous state is not known the first time */
    else {
        /* getting the gray value from the optoswitches */
        prevAngleState = GET_BIT(DECODER1_DATA, DECODER1);
        prevAngleState |= ((GET_BIT(DECODER2_DATA, DECODER2) << 1));

        /* configure interrupts to the correct edge */
         SET_BIT_HIGH(EICRA, ISC01);
         SET_BIT_HIGH(EICRA, ISC11);
         (GET_BIT(prevAngleState, 0)) > (0) ? (SET_BIT_LOW(EICRA, ISC00)) :
         (SET_BIT_HIGH(EICRA, ISC00));
         (GET_BIT(prevAngleState, 1)) > (0) ? (SET_BIT_LOW(EICRA, ISC10)) :
         (SET_BIT_HIGH(EICRA, ISC10));

        /* converting the gray value to binary */
        GRAY_TO_BIN(prevAngleState);
    }
    /* setting the prevAngleStateKnown to true */
    SET_BIT_HIGH(prevAngleState, 7);
}


int getMovementDirCount()
{
  return dirCount;
}


void clearDirCount()
{
    dirCount = 0;
}



/****************************************************
INTERRUPTS
****************************************************/
ISR(DECODER1_INT)
{
    /* disable interrupt from INT0 */
    SET_BIT_LOW(EIMSK, INT0);
    /* toggle from trailing to falling and vice versa */
    TOGGLE_BIT(EICRA, ISC00);
    checkMovementDir();
    /* enables the interrupt from INT0 */
    SET_BIT_HIGH(EIMSK, INT0);
}


ISR(DECODER2_INT)
{
    /* disable interrupt from INT1 */
    SET_BIT_LOW(EIMSK, INT1);
    /* toggle from trailing to falling and vice versa */
    TOGGLE_BIT(EICRA, ISC10);
    checkMovementDir();
    /* enables the interrupt from INT0 */
    SET_BIT_HIGH(EIMSK, INT1);
}
