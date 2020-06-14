#include "LedController.h"
#include "TouchController.h"


int states[8][8];
LedController *ledController;
TouchController *touchController;

void setup (void){
  Serial.begin(9600);
  ledController = new LedController(64, 3);
  touchController = new TouchController(SPI_CLOCK_DIV64, 8);
    I2Csetup(touchController, ledController, 3);
}

void loop(void){ 
  touchController->getButtons(0);
  touchController->getButtons(1);
  touchController->getButtons(2);
  touchController->getButtons(3);
//  touchController->serialWriteStages();
  // ledController->ledsShowStages(touchController->getStates());
  delay(8);
}
