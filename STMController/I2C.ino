#include "TouchController.h"
#include "LedController.h"

#include <Wire_slave.h>
#include "commands.h"


#define ADDRESS 8

static Command currentCommand = NONE;
static TouchController* tc;
static LedController* lc;

static int tr;
static int c = 0;

void I2Csetup(TouchController* touchController, LedController* ledController, int touchResistance)
{
  Wire.begin(ADDRESS);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent);

  tc = touchController;
  lc = ledController;
  tr = touchResistance;
}

void requestEvent()
{
  Serial.println("Request");
  switch (currentCommand) {
    case GET_INPUTS: 
      unsigned char data[8] = {0, 0, 0, 0, 0, 0, 0, 0};
      int** states = touchController->getStates();
      for (int i = 0; i < 8; i++) {
        data[i] = states[i][0] >= tr ? 1 : 0;
        for (int j = 1; j < 8; j++) {
          data[i] = (data[i] << 1) + (states[i][j] >= tr ? 1 : 0);
        }
        Serial.println((unsigned int)data[i]);
      }
      Wire.write(data, 8);
      currentCommand = NONE;
      break;
  }
  
}

void receiveEvent(int howMany){
  Serial.print("Receive: ");
  Serial.println(howMany);
  Serial.println(currentCommand);
  switch(currentCommand) {
    case SET_BOARD:
      for (int i = 0; i < howMany; i++) {
        // board[c+i] = Wire.read();
        int x = Wire.read();
        lc->setColor(c + i, x * 255, 0, 0);
      }
      c += howMany;
      if (c >= 64) {
        currentCommand = NONE;
        c = 0;
        lc->show();
      }
      break;
    default:
      currentCommand = static_cast<Command>(Wire.read());
      
  }
}
