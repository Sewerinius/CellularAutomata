#include<SPI.h>
#include <Wire.h>
#include <TTP229.h>
volatile boolean Resend1, Resend2;
volatile byte SlaveReceived;
TTP229 ttp229 = TTP229();
void setup(){
  Wire.begin();
//  Serial.begin(9600);
  pinMode(MISO,OUTPUT);
  SPCR |= _BV(SPE);
  Resend1=false;
  Resend2=false;
  SPI.attachInterrupt();
}

ISR (SPI_STC_vect){
  if(SPDR==1)
    Resend1 = true;
  else if(SPDR==2)
    Resend2 = true;
}

void loop(){
  if(Resend1){
    ttp229.readKeys();
    byte data1 = 0;
//    Serial.print("Key states0-7: ");
    for (int i = 0; i < 8; ++i) {
        if (ttp229.isKeyPress(i)) {
//            Serial.print("1 ");
            data1++;
        } else
//            Serial.print("0 ");
        if(i<7)
          data1 *= 2;
    }
    SPDR = data1;
//    Serial.println();
    Resend1=false;
  }
  if(Resend2){
    byte data2 = 0;
//    Serial.print("Key states8-15:  ");
    for (int i = 8; i < 16; ++i) {
        if (ttp229.isKeyPress(i)) {
//            Serial.print("1 ");
            data2++;
        } else
//            Serial.print("0 ");
        if(i<15)
          data2 *= 2;
    }
    SPDR = data2;
//    Serial.println();
    Resend2=false;
  }
}
