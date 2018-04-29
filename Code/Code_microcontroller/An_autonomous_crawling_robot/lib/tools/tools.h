/**
* @file tools.h
* @author Jonas Van Der Donckt
* @date 14/05/2017
* @brief This library contains useful MACROS which can be used in other libraries
*/

#ifndef TOOLS_H_
#define TOOLS_H_

/****************************************************
CONSTANTS
****************************************************/
#define F_CPU 16000000UL        //!< adapt this if the CPU has a different frequency

/* data types */
#define BYTE unsigned char



/****************************************************
MACROS
****************************************************/
/* bit operations */
#define SET_PIN_HIGH(PORT, PIN)	        PORT |= (1 << PIN)
#define SET_PIN_LOW(PORT, PIN)	        PORT &= ~(1 << PIN)

#define SET_BIT_HIGH(REG, BIT)	        REG |= (1 << BIT)
#define SET_BIT_LOW(REG, BIT)	        REG &= ~(1 << BIT)

#define SET_PIN_OUTPUT(DDR, PIN)        SET_PIN_HIGH(DDR, PIN)
#define SET_PIN_INPUT(DDR, PIN)         SET_PIN_LOW(DDR, PIN)

#define TOGGLE_BIT(REG, POS)            (REG ^= (1<< POS))
#define GET_BIT(REG, POS)               ((REG & (1<< POS)) > (0) ? (1) : (0))

/* nibble operations */
#define GET_NIBBLE(REG, LSB_INDEX, D1)  (D1 = (REG & (0x0F << LSB_INDEX)))
#define SET_NIBBLE(REG, LSB_INDEX, D1)  (REG |= (D1 << LSB_INDEX))

#define CLEAR_NIBBLE(REG, LSB_INDEX )   (REG &=~(0x0F << LSB_INDEX) )
#endif
