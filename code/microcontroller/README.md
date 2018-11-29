# Microcontroller Code
## Table of contents

* [Interrupts and timers used by libraries:](#interrupts-and-timers-used-by-libraries)
* [Libraries](#libraries)
    + [MovementDecoder](#movementdecoder)
    + [Servo](#servo)
    + [Q-learning](#q-learning)
    + [Protocol](#protocol)
* [Notes](#notes)
    + [Future work](#future-work)
* [Personal opinion](#personal-opinion)
* [Taakverdeling](#taakverdeling)

## Interrupts and timers used by libraries:

```
movementDecoder:
        -   INT0
        -   INT1
servo:
        -   TIMER1
q_learning:
        -   INT5
RGB_led:
        -   TIMER0
USART:
            NONE
protocol:
            NONE
```

## Libraries 
### MovementDecoder

Before using this library, make sure that that the optoswitches are connected to the corresponding pins. If not so, adapt the parameters in the header file.

### Servo
Before using this library, make sure that that the servos are connected to the corresponding pins. If not so, adapt the parameters in the header file.

### Q-learning
There are options to chose if the Q_Table gets randomly initialized. You can also let the parameters change exponentially.

### Protocol
* **sending an integer**:      Little endian (LSB first, then MSB)
* **sending an position**:     row first, then column


## Notes
### Future work
*  Make the Q_Table's data type chars (saves 50% space)
* Optimalize the transmission protocol (join start and datatype in 1 byte)
* Make functions to load in the Q_Table/ store it in ROM.
* Let the agent interact with other agents
* Share a Q-table between different robots


The main goal of the code was to make it as much generic as possible. This means
that by changing the NUMB_SERVOS macro in the servo.h library, the Q-table would
automaticly adapt. I (Jonas) wanted to avoid having libraries connected to the
dwenguinoBoard and dwenguinoLCD libraries. Hereby would the code be more
micrcocontroller-independent.

## Personal opinion
_(deze tekst doe ik heel even in het Nederlands)_  

We waren een groepje van drie, dus er werd logischerwijze meer van ons verwacht. Jammer genoeg was niet iedereen even gemotiveerd/werklustig. Doorheen het semester spraken we altijd op dinsdag-  of woensdagmiddag af om samen aan het project
te werken. De eerste paar weken deed iedereen mee, maar na de vierde week kwam Arne niet meer af. Dit had als gevolg dat ik in de vrijdagles altijd de progressie die (Jules en ik) hadden gemaakt moest uitleggen aan Arne.

Uiteindelijk besefte hij dat door hem de vooruitgang van het project belemmerd werd. Hierdoor wou Arne de uitbreiding (visualisatie) op zich nemen. Na de paasvakantie, wanneer we aan de uitbreiding begonnen, bleek dat het USART protocol voor de bluetooth module nog steeds niet geïmplementeerd was. Het was zelf zo erg dat ik rond week 10 hem nog geholpen heb om atom op zijn computer te installeren. De uitbreiding heb ik (Jonas) zelf
nog mogen uitzoeken, want Jules was druk bezig met het verslag te schrijven en de C# applicatie.

Het is niet dat Arne helemaal niets deed, in de les wou hij wel werken, maar daar bleef het meestal bij.

Deze tekst heb ik geschreven omdat ik redelijk veel stress bij dit project had. Niet door het niveau van de opdracht, maar door de druk die op mijn (Jonas) schouders lag om eigenlijk voor 2 te werken.

Desalniettemin heb ik veel bijgeleerd van dit project en vind ik dat we het einddoel succesvol bereikt hebben bereikt hebben.

## Taakverdeling
Taak | persoon
|:--|--:|
Maken van de robot | Arne
Schrijven verslag | Jules
Maken van de C# code | Jules/ Jonas (Arne)
C code + documentatie | Jonas (Jules)
maken van de powerpoint | Jules / Arne / Jonas
Nalezen van het verslag |  Jonas
Nalezen van de code | Jules
