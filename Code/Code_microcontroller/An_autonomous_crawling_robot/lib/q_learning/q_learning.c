/*
 * q_learning.c
 *
 *  Created on: May 15, 2017
 *      Author: Jonas Van Der Donckt, Jules Noppe
 */


/****************************************************
LIBRARIES§
****************************************************/
#include "q_learning.h"
#include <avr/delay.h>
#include <time.h>
#include <avr/interrupt.h>


/****************************************************
VARIABLES
****************************************************/
unsigned char dataByte;         //!< this dataByte contains data of multiple parameters
                                //!<  BIT 7:  Bool btnPressed (true when the button is pressed)
                                //!<  BIT 0-3:    Nibble prevAction (max omount of servos is 8  -->
                                //!<        2 actions per servo = 16 = 2^4 = NIbble)
int **Q_Table;                  //!< dynamically allocated Q_Table
int *temp;                      //!< pointer used to allocate Q_Table

unsigned char prevServoStateArr[NUMB_SERVOS] = {STARTSTATES1,STARTSTATES2};
unsigned char nextServoStateArr[NUMB_SERVOS] = {STARTSTATES1,STARTSTATES2};

/* for exponentially adjusting the parameters of the Q_Table*/
int  numbIterations = 0;        //!< the amount of iterations the agent has done through the learn method
struct Formula_Parameters_t parameters[NUMB_PARAMETERS];



/****************************************************
FUNCTIONS
****************************************************/
void initQ_Learning() {
    /* Q_Table: dynamicly allocated 2 dimensional array */
    Q_Table = malloc(NUMB_STATES * sizeof(int*));
    temp = malloc(NUMB_STATES * NUMB_ACTIONS * sizeof(int*));

    for (int i = 0; i < NUMB_STATES; i ++) {
        Q_Table[i] =  temp + (i* NUMB_ACTIONS);
    }

    /* initializing the parameter struct */
    unsigned char initialVals[] = {INIT_LEARNING_RATE, INIT_GREEDY_FACTOR, INIT_DISCOUNT_FACTOR};
    float factor[] = {EXP_FACTOR_LEARNING, EXP_GREEDY_FACTOR, EXP_FACTOR_DISCOUNT};
    unsigned char finalVals[] = {FINAL_LEARING_RATE, FINAL_GREEDY_FACTOR, FINAL_DISCOUNT_FACTOR };

    for (unsigned char i = 0; i < NUMB_PARAMETERS; i++){
        parameters[i].initialVal = initialVals[i];
        parameters[i].finalVal = finalVals[i];
        parameters[i].exp_Factor = factor[i];
        parameters[i].current = initialVals[i];
    }

    /* should be only called once */
    srand((unsigned int)time(NULL));

    /* initializing other libraries */
    initUSART();
    initMovementDecoder();
    initServo(prevServoStateArr);


    /****************************************************
    INT7
    ****************************************************/
    /* configuring the pin to input and enable pullup */
    SET_PIN_INPUT(BTN_S_DIR, BTN_S);
    SET_BIT_HIGH(BTN_S_PORT, BTN_S);

    /* configuring the interrupt on trailing edge */
    SET_BIT_HIGH(EICRB, ISC51);
    SET_BIT_LOW(EICRB, ISC50);

    /* enable interrupts */
    SET_BIT_HIGH(SREG, 7);                  // enable interrupts

    /* enabling the servos */
    for (unsigned char i = 0; i < NUMB_SERVOS; i++){
        enableServo(i);
    }

    /* moves the servos to the startstate */
    servoWriteStates(nextServoStateArr);
    waitServoMovement();
}


void initQ_Table(){
    struct Dataobj dataobj1;

    /* transmitting size to the pc */
    unsigned char size[2] = {NUMB_STATES, NUMB_ACTIONS};
    init_SizeProtocol(size, &dataobj1);
    transmit_data(&dataobj1);

    /* initializing the Q_Table with random values */
    for(unsigned char i = 0; i < NUMB_STATES; i++) {
        for(unsigned char j = 0; j < NUMB_ACTIONS; j++) {
            unsigned char q = rand();
            q %= (unsigned char)NUMB_STATES;
            Q_Table[i][j] = q;

            /* transmitting data*/
            unsigned char pos[2] = {i, j};
            init_PositionProtocol(pos, &dataobj1 );
            transmit_data(&dataobj1);
            init_QvalProtocol((int)q, &dataobj1);
            transmit_data(&dataobj1);
        }
    }
}


void Learn(){
    /* initialize the Q-table with random values */
    if (RAND_INITQ_B){
        initQ_Table();
    }

    /* making sure that the agents previous movements are neglected */
    clearDirCount();

    while (1){
        unsigned char state = CalcStateIndex(prevServoStateArr);
        /* calculating next action --> next state */
        unsigned char action = calcNextAction();
        unsigned char servo = (NUMB_SERVOS - 1) - action/OPT_PER_SERVO;
        char option = -1 + 2* (action % 2);
        if (nextServoStateArr[servo] == 0 && option < 0) {
            nextServoStateArr[servo] = (NUMB_ACTIONS - 1);
        }
        else{
            nextServoStateArr[servo] = (nextServoStateArr[servo] + option)%4;
        }
        CLEAR_NIBBLE(dataByte, PREVACTION_INDEX_NIBBLE);
        SET_NIBBLE(dataByte, PREVACTION_INDEX_NIBBLE, action);

        /* servo executes the action */
        servoWriteStates(nextServoStateArr);

        /* calculating Qval and placing it in the Q_Table */
        int Qval = calcQVal();

        BYTE prevAction =  0;
        GET_NIBBLE(dataByte, PREVACTION_INDEX_NIBBLE, prevAction);
        Q_Table[CalcStateIndex(prevServoStateArr)][prevAction] = Qval;

        /* transmitting the data */
        struct Dataobj q_valObj;
        BYTE SerialState[2] = {CalcStateIndex(prevServoStateArr),prevAction};
        init_PositionProtocol(SerialState, &q_valObj);
        transmit_data(&q_valObj);
        init_QvalProtocol(Qval, &q_valObj);
        transmit_data(&q_valObj);
        for (unsigned char i = 0; i < NUMB_SERVOS; i++) {
            prevServoStateArr[i] = nextServoStateArr[i];
        }
        if (EXP_ENABLED){
            adjustParameters();
        }
    }
}


int calcQVal(){
    /* calculate the reward of maxQvalue of the state where the servo is moving towards */
    int state = (int)CalcStateIndex(nextServoStateArr);
    int futureRW = (parameters[LEARNING_RATE_INDEX].current *
        parameters[DISCOUNT_FACTOR_INDEX].current)/100;
    futureRW = (futureRW * calcMaxQval(state)) / 100;

    /* calculate previous reward of the chosen state,action pair */
    BYTE prevAction =  0;
    GET_NIBBLE(dataByte, PREVACTION_INDEX_NIBBLE, prevAction);
    state = CalcStateIndex(prevServoStateArr);
    int prevRW = ((MAX_FACTOR - parameters[LEARNING_RATE_INDEX].current)*
                    Q_Table[state][prevAction])/100;

    /* wait until the servo has reached goalposition */
    waitServoMovement();

    /* delay for when the agent is still moving after servo reached position
          -->  so we retrieve the correct angleDecoder val*/
    _delay_ms(DELAYVAL);

    /* calculate the reward of the angleDecoder */
    int reward = parameters[LEARNING_RATE_INDEX].current;

    int count = getMovementDirCount();
    clearDirCount();

    if (count > TRESHMOVFW) {
        reward = (reward*count)/7.2*count/100;
    }
    else {
        reward = (reward*count/7.2*abs(count))/100 - 20;
    }

    /* calculates total reward */
    reward += ( futureRW + prevRW);
    return reward;
}


unsigned char calcNextAction(){
    /* calculate the maxQvale of the actions from the current servo state */
    unsigned char state = CalcStateIndex(prevServoStateArr);
    unsigned char index = calcMaxActionIndex(state);

    /* random factor */
    int r = rand();
    r %= RADIX;
    if (r < parameters[GREEDY_FACTOR_INDEX].current) {
        int a = rand();
        a %=NUMB_ACTIONS;
        /* random action who is not the optimal action atm */
        while (a == index){
            a = rand()%NUMB_ACTIONS;
        }
        index = a;
    }
    return index;
}


unsigned char CalcStateIndex(unsigned char  stateArr[]){
    unsigned char stateIndex = 0;
    for (unsigned char i = 0; i < NUMB_SERVOS; i++){
        stateIndex += stateArr[i]*(pow(NUMB_SERVO_STATES, i));
    }
    return stateIndex;
}


int calcMaxQval(unsigned char state) {
    int maxVal = Q_Table[state][0];
    for (unsigned char i  = 1; i < NUMB_ACTIONS; i++) {
        if (Q_Table[state][i] > maxVal) {
            maxVal = Q_Table[state][i];
       }
   }
   return maxVal;
}


unsigned char calcMaxActionIndex(unsigned char state) {
    unsigned char maxStateIndex = 0;
    int maxVal = Q_Table[state][maxStateIndex];
    for (unsigned char i = 1; i < NUMB_ACTIONS; i++) {
        if (Q_Table[state][i] > maxVal) {
            maxVal = Q_Table[state][i];
            maxStateIndex = i;
       }
   }
   return maxStateIndex;
}


void waitBTN(){
    SET_BIT_HIGH(EIMSK, BTN_S_INT);
    while(!(GET_BIT(dataByte, BTNPRESSED_INDEX))){
        rand();
    }
    SET_BIT_LOW(dataByte, BTNPRESSED_INDEX);
}


void adjustParameters() {
    for(unsigned char i = 0; i < NUMB_PARAMETERS; i++) {
        calcParameter(&parameters[i]);
    }
    numbIterations++;
}


void calcParameter(struct Formula_Parameters_t *paramVal){
    if ((unsigned char)paramVal->current != paramVal->finalVal){
        float temp = pow(EULER, ((-1)*numbIterations *
                paramVal->exp_Factor/100));
        if ((paramVal->initialVal) > (paramVal->finalVal)){
            /* trailing exponential */
            paramVal->current = (paramVal->initialVal - paramVal->finalVal)*temp +
                paramVal->finalVal;
        }
        else {
            /* rising exponential */
            paramVal->current = paramVal->finalVal - (paramVal->finalVal -
                paramVal->initialVal)*temp;
        }
    }
}



/****************************************************
INTERRUPTS
****************************************************/
ISR(INT5_vect){
    /*  disable interrupt  */
    SET_BIT_LOW(EIMSK, BTN_S_INT);
    SET_BIT_HIGH(dataByte, BTNPRESSED_INDEX);
}
