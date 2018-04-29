/**
 * @file q_learning.h
 * @brief This library contains the Q-learning algorithm.
 * before you can use the learn method function you should call the initQ_Learning() function.
 * Afterwards you can call the learn() function.
 * @author Jonas Van Der Donckt, Jules Noppe
 * @date 6/05/2017
 */

#ifndef Q_LEARNING_H
#define Q_LEARNING_H

/****************************************************
LIBRARIES
****************************************************/
#include "tools.h"
#include "servo.h"
#include "movementDecoder.h"
#include "protocol.h"




/****************************************************
CONSTANTS
****************************************************/
#define NUMB_ACTIONS    (2*NUMB_SERVOS)
#define OPT_PER_SERVO   2                       //!< options of actions per servo
#define NUMB_STATES     ((unsigned char)pow(NUMB_SERVO_STATES,NUMB_SERVOS))
#define RAND_INITQ_B    1                       //!< bool; 1 if Q table needs to get randomly initialized
                                                //!< 0 if the Q table doesn't need a random initialisation
#define EXP_ENABLED       1                     //!< bool; 1 if the

/* THE PARAMETERS */
#define EULER                   (double)2.71828
#define NUMB_PARAMETERS         3
#define RADIX                   100             //!< fixed point notation
#define MAX_FACTOR              100             //!< fixed point notation is used --> this is maximum
#define EXP_REWARD_FACTOR       (double)0.1     //!< the exponential reward factor
#define MAX_COUNT               80

// alpha
#define LEARNING_RATE_INDEX     0
#define INIT_LEARNING_RATE      90              //!< alpha 0.5
#define EXP_FACTOR_LEARNING     (float)1
#define FINAL_LEARING_RATE      40

// epsillon
#define GREEDY_FACTOR_INDEX     1
#define INIT_GREEDY_FACTOR      90             //!< epsillon 0.1
#define EXP_GREEDY_FACTOR       (float)1
#define FINAL_GREEDY_FACTOR     0

// gamma
#define DISCOUNT_FACTOR_INDEX   2
#define INIT_DISCOUNT_FACTOR    99              //!< gamma  0.99
#define EXP_FACTOR_DISCOUNT     (float)1
#define FINAL_DISCOUNT_FACTOR   50

#define STARTSTATES1            0           //!< this value should be < than NUMB_STATES
#define STARTSTATES2            3           //i< this value should be < than NUMB_STATES
#define STARTSTATES3            0
#define TRESHMOVFW              2           //!< threshold value for moving forward
#define DELAYVAL                700         //!< value in ms that is used to wait until the robot stopped moving



#define BTN_S                   PORTE5
#define BTN_S_PORT              PORTE
#define BTN_S_DIR               DDRE
#define BTN_S_INT               INT5

/* indices from data byte */
#define PREVACTION_INDEX_NIBBLE 0
#define BTNPRESSED_INDEX        7



/****************************************************
MACROS & STRUCTS
****************************************************/
#define CALC_STATE_INDEX(STATES1, STATES2) (STATES1*4 + STATES2)
#define GETSIZE(QTABLE)     (sizeof(QTABLE[0])/ sizeof(QTABLE[0][0]))
#define ENABLE_BTN          (SET_BIT_HIGH(EIMSK, BTN_S_INT))


/**
 * @brief This struct contains the parameters of the Q-learning formula.
 *  Some other functions are specificly designed to change those parameters
 *  by using an exponential function.
 */
struct Formula_Parameters_t{
    unsigned char initialVal;
    unsigned char finalVal;
    float exp_Factor;
    float current;
};


/****************************************************
FUNCTIONS
****************************************************/
/**
 * @brief Initializes the Q-learning algorithm.
 * This function sets up the pins and the interrupt for the button.
 * It also initialzes the needed components for the Q-learning algorithm
 * (servo.h, movementDecoder.h)
 */
void initQ_Learning();


/**
 * @brief Initializes the Q_Table with random values.
 */
void initQ_Table();


/**
 * @brief The Q-learning algorithm itself.
 * This function executes the Q_learning algorithm itself
 */
void learn();


/**
 * @brief This function calculates the Q-value.
 * It should be only called by the learn() method
 */
int calcQVal();


/**
 * @brief This function calculates the next action.
 * It should be only called by the learn() method
 */
unsigned char calcNextAction();


/**
 * @brief Calculates the state index.
 * @param stateArr[] this array contains the stateval of each servo
 */
unsigned char CalcStateIndex(unsigned char  stateArr[]);


/**
 * @brief This function calculates the maximum Q-value for a certain state.
 * It should be only called by the learn() method.
 * @param state this is the state of the robot
 */
int calcMaxQval(unsigned char state);


/**
 * @brief This function calculates the maximum state index.
 * It should be only called by the learn() method.
 * @param state this is the state of the robot
 */
unsigned char calcMaxActionIndex(unsigned char state);


/**
 * @brief This function waits until button south is pressed.
 */
unsigned char wait_BTN_S();


/**
 * @brief Adjusts the parameters in the Q-learning formule.
 */
void adjustParameters();

/**
 * @brief Calculates the new value of the parameters used in the Q-learning formula.
 * @param *paramVal this is the parameter that will be updated
 */
void calcParameter(struct Formula_Parameters_t *paramVal);
#endif
