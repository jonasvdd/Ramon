#include "dwenguinoLCD.h"
#include "q_learning.h"



void waitforButton();

int main()
{
    initLCD();
    backlightOn();
    initQ_Learning();
    waitforButton();        //!< waits until the user has pressed BTN_S
    clearLCD();
    Learn();
    return 0;
 }

/* waiting for the south button */
void waitforButton(){
    clearLCD();
    appendStringToLCD("Resting Mode ...");
    setCursorLCD(1,0);
    appendStringToLCD("Press btn south");
    waitBTN();
    clearLCD();
    appendStringToLCD("Activation");
    setCursorLCD(1,0);
    appendStringToLCD("complete");
    _delay_ms(2000);
    clearDirCount();
}
