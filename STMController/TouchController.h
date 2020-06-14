#ifndef TOUCH_CONTROLLER_H
#define TOUCH_CONTROLLER_H

#include<SPI.h>

#define SS0 PA0
#define SS1 PA1
#define SS2 PA2
#define SS3 PA3


class TouchController{
  private:
    int delayBeetweenMsg;
    SPIClass *SPI_2;
    int *mapperData;
    int **states;
  public:
    TouchController(int clockDivider, int delayBeetweenMsg){
      this->delayBeetweenMsg = delayBeetweenMsg;
      this->SPI_2 = new SPIClass(2);
      this->mapperData = new int[4];
      this->mapperData[0] = 0;
      this->mapperData[1] = 4;
      this->mapperData[2] = 32;
      this->mapperData[3] = 36;
      this->states = new int*[8];
      for(int i=0;i<8;i++){
        this->states[i] = new int[8];
        for(int j=0;j<8;j++)
          states[i][j]=0;
      }
      pinMode(SS0,OUTPUT);
      pinMode(SS1,OUTPUT);
      pinMode(SS2,OUTPUT);
      pinMode(SS3,OUTPUT);
      this->SPI_2->begin();
      this->SPI_2->setClockDivider(clockDivider);
      digitalWrite(SS0,HIGH);
      digitalWrite(SS1,HIGH);
      digitalWrite(SS2,HIGH);
      digitalWrite(SS3,HIGH);
    }
    void decodeDatas(byte data1, byte data2, byte sector){
      unsigned long bitChecker = 32768;
      unsigned long data = data2;
      data<<=8;
      data+=data1;
      String answer = "";
      for (int i = 0; i < 16; i++){
        int no = i+i/4*4+this->mapperData[sector];
        if(data & bitChecker){
          if(this->states[no/8][no%8]<1000)
            this->states[no/8][no%8] += 1;
        }else
          this->states[no/8][no%8] = 0;
        bitChecker>>=1;
      }
    }
    void getButtons(byte sector){
      byte receive1,receive2;
      switch(sector){
        case 0:
          digitalWrite(SS0, LOW);
          break;
        case 1:
          digitalWrite(SS1, LOW);
          break;
        case 2:
          digitalWrite(SS2, LOW);
          break;
        case 3:
          digitalWrite(SS3, LOW);
          break;
      }
      receive1=this->SPI_2->transfer(1);
      delay(this->delayBeetweenMsg);
      receive2=this->SPI_2->transfer(2);
      this->decodeDatas(receive1, receive2, sector);
      delay(this->delayBeetweenMsg);
      switch(sector){
        case 0:
          digitalWrite(SS0, HIGH);
          break;
        case 1:
          digitalWrite(SS1, HIGH);
          break;
        case 2:
          digitalWrite(SS2, HIGH);
          break;
        case 3:
          digitalWrite(SS3, HIGH);
          break;
      }
    }
    void serialWriteStages(){
      for(int i=0;i<8;i++){
        for(int j=0;j<8;j++)
          Serial.print(String (this->states[j][i])+" ");
        Serial.println();
      }
      Serial.println();
    }
    int** getStates(){
      return states;
    }
};

#endif