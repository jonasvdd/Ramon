/**
 * @file servo.h
 * @author Jonas Van Der Donckt
 * @date 16/03/2017
 * @brief This library contains functions whom help to control multiple servos.
 * Before using any of the the servo methods, call the initServo() function.
 */

 #ifndef SERVO_H_
 #define SERVO_H_


 /****************************************************
 LIBRARIES
 ****************************************************/
 #include "tools.h"



/****************************************************
CONSTANTS
****************************************************/
#define CLK_TICKS_US        16      //!< the unprescaled clock uses 16 ticks per µs
#define PRESCALER           8       //!< the prescaler of the clock

/* semi-adjustable parameters */
#define MAXANGLE            180     //!< just informative
#define MIN_STATE_ANGLE     10      //!< must be smaller than MAX_STATE_ANGLE
#define MAX_STATE_ANGLE     110     //!< must be smaller than MAXANGLE
#define MAX_NUMB_SERVOS     8       //!< this is the maximum amount of servos

#define MIN_PULSE_WIDTH     600     //!< the shortest pulse sent to a servo in µs
#define MAX_PULSE_WIDTH     2400    //!< the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH 1500    //!< default pulse width when servo is attached
#define PERIOD              20000   //!< this is the refresh interval

/* ADJUSTABLE PARAMETERS FOR Q_LEARNING */
#define NUMB_SERVOS         2       //<! adapt this to change the amount of servo's
#define NUMB_SERVO_STATES   4       //<! adapt this to change the amount of states
#define INTERPOLLATEINT     1500    //!< refresh inte rval for interpollation
#define INTERPOLLATEVAL     1       //!< angle change wich each interpollation

/* for switch state */
#define NUMB_SWITCH_STATES  2
#define PULSE               0
#define WAIT                1

/* positions of indices from the data within the dataByte */
#define ISMOVING_INDEX          7           //!< index of the bool isMoving in the data byte
#define SERVO_INDEX_NIBBLE      0           //!< start index of the nibble that contains the servo index
#define STATE_INDEX_POS         4           //!< single bit value that contains the switch state index

/* adjustable servo ports */
#define SERVO1              PORTC0
#define SERVO1_PORT         PORTC       //!< will be used as a pointer
#define SERVO1_DIR          DDRC        //!< will be used as a pointer

#define SERVO2              PORTC1
#define SERVO2_PORT         PORTC       //!< will be used as a pointer
#define SERVO2_DIR          DDRC        //!< will be used as a pointer

#define SERVO3              PORTB1
#define SERVO3_PORT         PORTB       //!< will be used as a pointer
#define SERVO3_DIR          DDRB        //!< will be used as a pointer

#define SERVO4              0
#define SERVO4_PORT         PORTC       //!< will be used as a pointer
#define SERVO4_DIR          DDRC        //!< will be used as a pointer

#define SERVO5              0
#define SERVO5_PORT         PORTC       //!< will be used as a pointer
#define SERVO5_DIR          DDRC        //!< will be used as a pointer

#define SERVO6              0
#define SERVO6_PORT         PORTC       //!< will be used as a pointer
#define SERVO6_DIR          DDRC        //!< will be used as a pointer

#define SERVO7              0
#define SERVO7_PORT         PORTC       //!< will be used as a pointer
#define SERVO7_DIR          DDRC        //!< will be used as a pointer

#define SERVO8              0
#define SERVO8_PORT         PORTC       //!< will be used as a pointer
#define SERVO8_DIR          DDRC        //!< will be used as a pointer



/****************************************************
MACROS
****************************************************/
#define STATE_ANGLE_WIDTH   ((MAX_STATE_ANGLE - MIN_STATE_ANGLE)/(NUMB_SERVO_STATES - 1))
#define BASE_TIME_WIDTH     (PERIOD/NUMB_SERVOS)   //!< val in µs

#define ANGLE_TO_TICKS_INTERP(ANG)(((US_TO_TICKS(MAX_PULSE_WIDTH - MIN_PULSE_WIDTH)/180)*ANG))

#define US_TO_TICKS(US)     (US*(CLK_TICKS_US/PRESCALER))
#define ANGLE_TO_US(ANG)    (MIN_PULSE_WIDTH + ((MAX_PULSE_WIDTH - MIN_PULSE_WIDTH)/180)*ANG)
#define ANGLE_TO_TICKS(ANG) (US_TO_TICKS(ANGLE_TO_US(ANG)))
#define TICKS_TO_ANGLE(TCK) ((TCK - US_TO_TICKS(MIN_PULSE_WIDTH))/(US_TO_TICKS((MAX_PULSE_WIDTH - MIN_PULSE_WIDTH)/180)))


/**
 * @brief This struct contains the parameters of a servo.
 *  Some other functions are specificly designed to change those parameters.
 */
struct servo_t
{
    unsigned char pin;              //!< pointer to the pin
    volatile unsigned char *port;   //!< pointer to the port
    unsigned int ticks;             //!< contains amount of prescaled ticks
    unsigned char isActive;         //!< 0 = inactive
};



/****************************************************
FUNCTIONS
****************************************************/
/**
 * @brief Initializes the servo motors.
 * This function sets up the pins and interrupts for the servos.
 * It should be called before you want to use the servos.
 * @param restStateArr these are the restStates of the servos
 */
 void initServo(unsigned char restStateArr[NUMB_SERVOS]);


/**
 * @brief This function makes the servos go to a given state.
 * @param stateArr[] this contains the state index corresponding servo
 */
void servoWriteStates(unsigned char stateArr[]);


/**
 * @brief This function makes the servo's go to a given angle.
 * @param posArr[] this contains the angle values of the servo's
 */
void servoWriteAngles(unsigned char posArr[]);


/**
 * @brief This function makes a specific servo go to a given state.
 * @param state this contains the state index corresponding servo
 * @param servoIndex this contains the index of the servo
 */
void servoWriteState(unsigned char state, BYTE servoIndex);


/**
 * @brief This function makes the servo's go to a given angle.
 * @param angle this contains the angle the servo needs to go to
 * @param servoIndex this contains the index of the servo
 */
void servoWriteAngle(unsigned char angle, BYTE servoIndex);


/**
 * @brief Interpollates the movement of the servo's.
 * This function should only be used within this library.
 */
 inline void interpollate();


/**
 * @brief This function helps to generate a PWM-signal.
 * This function should only be used by servo timer interrupt (TIMER1_COMPA_vect)
 */
inline void setServoState();


/**
 * @brief This function enables the servo.
 * It should be called before writing a position to the servos.
 * @param index the index of the servo that should be enabled
 */
void enableServo(int index);


/**
 * @brief This function disables the servo.
 * Writing a position to the servo will have no effect.
 * When you enable the servo, it will go to the last written position.
 * @param index the index of the servo that should be disabled
 */
void disableServo(int index);


/**
 *@brief This function waits until the servo reached the goal position.
 */
void waitServoMovement();
#endif
