/**
 * servo.c
 *
 *  Created on: Mar 16, 2017
 *      Author: Jonas Van Der Donckt
 */

 /****************************************************
 LIBRARIES
 ****************************************************/
 #include "servo.h"
 #include <avr/interrupt.h>



 /****************************************************
 VARIABLES
 ****************************************************/
 BYTE dataB;                                    //!< this dataByte contains data of multiple parameters
                                                //!< BIT7: Bool isMoving (true if servos are moving
                                                //!< BIT4: stateIndex(of switch state)
                                                //!< BIT0-3: Nibble servoIndex (max amount of servos is 1)

struct servo_t servos[NUMB_SERVOS];             //!< Contains all the data of the servos

unsigned char stateAngles[NUMB_SERVO_STATES];   //!< Contains the angles of the predefined states
unsigned int CurrentTicks[NUMB_SERVOS];         //!< Contains the amount of ticks that the servo is high
int interpollateTime =  0;                      //!< Contains the amount of ticks before we interpollate the servo



/****************************************************
FUNCTIONS
****************************************************/
void initServo(unsigned char restStateArr[NUMB_SERVOS])
{
    /* arrays containing the data of each servo */
    unsigned char servoPinArr[8] = {SERVO1, SERVO2, SERVO3, SERVO4, SERVO5,
         SERVO6, SERVO7, SERVO8};
    volatile unsigned char *servoDirArr[8] = {&SERVO1_DIR, &SERVO2_DIR, &SERVO3_DIR,
         &SERVO4_DIR, &SERVO5_DIR, &SERVO6_DIR, &SERVO7_DIR, &SERVO8_DIR};
    volatile unsigned char *servoPortArr[8] = {&SERVO1_PORT, &SERVO2_PORT, &SERVO3_PORT,
        &SERVO4_PORT, &SERVO5_PORT, &SERVO6_PORT, &SERVO7_PORT, &SERVO8_PORT};


    /****************************************************
    TIMER 1
    ****************************************************/
    /* configuring waveform generation mode to CTC */
    SET_BIT_LOW(TCCR1B, WGM13);
    SET_BIT_HIGH(TCCR1B, WGM12);
    SET_BIT_LOW(TCCR1A, WGM11);
    SET_BIT_LOW(TCCR1A, WGM10);

    /* configuring the prescaler to 8 */
    SET_BIT_LOW(TCCR1B, CS12);
    SET_BIT_HIGH(TCCR1B, CS11);
    SET_BIT_LOW(TCCR1B, CS10);

   /* disable output compares mode */
    SET_BIT_LOW(TCCR1A, COM1B1);
    SET_BIT_LOW(TCCR1A, COM1B0);
    SET_BIT_LOW(TCCR1A, COM1A1);
    SET_BIT_LOW(TCCR1A, COM1A0);

    /* enable the interrupts for the timer */
    SET_BIT_HIGH(TIMSK1, OCIE1A);
    OCR1A = US_TO_TICKS(BASE_TIME_WIDTH);


    /* configuring the state angles */
    for (unsigned char i = 0; i < NUMB_SERVO_STATES; i++) {
        stateAngles[i] = MIN_STATE_ANGLE + i*STATE_ANGLE_WIDTH;
    }

    /* configuring the servo pins */
    for (unsigned char i = 0; i < NUMB_SERVOS; i++) {
        servos[i].pin = servoPinArr[i];
        servos[i].port = servoPortArr[i];
        servos[i].ticks = CurrentTicks[i];
        SET_PIN_OUTPUT(*(servoDirArr[i]), servos[i].pin);
        CurrentTicks[i] =  ANGLE_TO_TICKS(stateAngles[restStateArr[i]]);
    }
}


void servoWriteStates(unsigned char stateArr[])
{
    /* converting the stateArr to an array with the corresponding angles */
    unsigned char posArr[NUMB_SERVOS];
    for (unsigned char i = 0; i < NUMB_SERVOS; i++) {
        posArr[i] = stateAngles[stateArr[i]];
    }
    servoWriteAngles(posArr);
}


void servoWriteAngles(unsigned char posArr[])
{
    /* writing the angles to the corresponding servo struct */
    for (unsigned char i = 0; i < NUMB_SERVOS; i++) {
        servos[i].ticks = ANGLE_TO_TICKS(posArr[i]);
    }
    /* the servos are moving */
    SET_BIT_HIGH(dataB, ISMOVING_INDEX);
}


void servoWriteState(unsigned char state, BYTE servoIndex)
{
    servoWriteAngle(stateAngles[state], servoIndex);
}


void servoWriteAngle(unsigned char angle, BYTE servoIndex)
{
    servos[servoIndex].ticks = ANGLE_TO_TICKS(angle);
    /* the servo is moving */
    SET_BIT_HIGH(dataB, ISMOVING_INDEX);
}

inline void interpollate()
{
    /* checking if the servo has reached its goalposition ( = servos[i].ticks) */
    SET_BIT_LOW(dataB, ISMOVING_INDEX);
    for (unsigned char  i = 0; i < NUMB_SERVOS; i++) {
        if(TICKS_TO_ANGLE(servos[i].ticks) != TICKS_TO_ANGLE(CurrentTicks[i]) &&
                servos[i].isActive ) {
                    SET_BIT_HIGH(dataB, ISMOVING_INDEX);
        }
    }

    /* interpollate if the servo still hasn't reached its goalposition */
    if (GET_BIT(dataB, ISMOVING_INDEX)) {
        for (unsigned char i = 0; i < NUMB_SERVOS; i++) {
           if(TICKS_TO_ANGLE(servos[i].ticks) > TICKS_TO_ANGLE(CurrentTicks[i])) {
               CurrentTicks[i]+= ANGLE_TO_TICKS_INTERP(INTERPOLLATEVAL);
           }
           else if(TICKS_TO_ANGLE(servos[i].ticks) < TICKS_TO_ANGLE(CurrentTicks[i])) {
               CurrentTicks[i]-= ANGLE_TO_TICKS_INTERP(INTERPOLLATEVAL);
           }
       }
   }
}


inline void setServoState()
{
    /* Reducing the interpollateTime */
    interpollateTime -= OCR1A;

    /* retrieving the servo index */
    BYTE servoIndex = 0;
    GET_NIBBLE(dataB, SERVO_INDEX_NIBBLE, servoIndex);

    /* generating PWM signal */
    switch (GET_BIT(dataB, STATE_INDEX_POS)) {
        case PULSE:
        if (servos[servoIndex].isActive) {
            SET_PIN_HIGH(*(servos[servoIndex].port), servos[servoIndex].pin);
        }
        OCR1A = CurrentTicks[servoIndex];
        SET_BIT_HIGH(dataB, STATE_INDEX_POS);   // equivalent to stateIndex++
        break;

        case WAIT:
        SET_PIN_LOW(*(servos[servoIndex].port), servos[servoIndex].pin);
        OCR1A = US_TO_TICKS(BASE_TIME_WIDTH) - CurrentTicks[servoIndex];
        SET_BIT_LOW(dataB, STATE_INDEX_POS);

		/* avoiding modulo operation */
        if( servoIndex == (NUMB_SERVOS - 1)) {
            servoIndex = 0;
        }
        else {
            servoIndex++;
        }
        break;
    }
    dataB &= ~(0x0F << 4*SERVO_INDEX_NIBBLE);
    dataB |= (servoIndex << 4*SERVO_INDEX_NIBBLE);

    /* checking if interpollation is needed */
    if (interpollateTime < 0) {
        interpollate();
        interpollateTime = US_TO_TICKS(INTERPOLLATEINT);
    }
}


void enableServo(int index)
{
    servos[index].isActive = 1;
}


void disableServo(int index)
{
    servos[index].isActive = 0;
}


void waitServoMovement()
{
    while(GET_BIT(dataB, ISMOVING_INDEX)) {
        TOGGLE_BIT(PORTA, PORTA0);
    }
}


/****************************************************
INTERRUPTS
****************************************************/
 ISR(TIMER1_COMPA_vect)
 {
     /*  disable interrupt from TIMER1 */
     SET_PIN_LOW(TIMSK1,OCIE1A);
     setServoState();
     /* enable interrupt from TIMER1 */
     SET_PIN_HIGH(TIMSK1, OCIE1A);
 }
