#include "KeypadVA.h"
#include "allocateMem.h"
#include "commandmessenger.h"
#include <Keypad.h>

/* **********************************************************************************
    This is just the basic code to set up your custom device.
    Change/add your code as needed.
********************************************************************************** */



const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
//byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
//byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//Keypad *keypad = NULL;
Keypad *ptrkeypad;


KeypadVA::KeypadVA(uint8_t Pin1, uint8_t Pin2)
{
    _pin1 = Pin1;
    _pin2 = Pin2;
}

void KeypadVA::begin()
{

    byte rowPins[ROWS] = {14, 21, 20, 18}; //connect to the row pinouts of the kpd
    byte colPins[COLS] = {15, 16, 19}; //connect to the column pinouts of the kpd
    //byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
    //byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
    Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
    ptrkeypad = &keypad;
}

void KeypadVA::attach(uint16_t Pin3, char *init)
{
    _pin3 = Pin3;
}

void KeypadVA::detach()
{
    if (!_initialised)
        return;
    _initialised = false;
}

void KeypadVA::set(int16_t messageID, char *setPoint)
{
    /* **********************************************************************************
        Each messageID has it's own value
        check for the messageID and define what to do.
        Important Remark!
        MessageID == -2 will be send from the board when PowerSavingMode is set
            Message will be "0" for leaving and "1" for entering PowerSavingMode
        MessageID == -1 will be send from the connector when Connector stops running
        Put in your code to enter this mode (e.g. clear a display)

    ********************************************************************************** */
    int32_t  data = atoi(setPoint);
    uint16_t output;

    // do something according your messageID
    switch (messageID) {
    case -1:
        // tbd., get's called when Mobiflight shuts down
    case -2:
        // tbd., get's called when PowerSavingMode is entered
    case 0:
        output = (uint16_t)data;
        data   = output;
        break;
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    default:
        break;
    }
}

void KeypadVA::update()
{
    char key = ptrkeypad->getKey();
  
    if (key){
        cmdMessenger.sendCmd(kDebug, F("Button Pressed"));
        cmdMessenger.sendCmd(kDebug, key);
    }
}
