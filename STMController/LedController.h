#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include <WS2812B.h>

class LedController{
  private:
    int pixelQuantity;
    int correctionLvl;
    WS2812B *pixels;
  public:
    LedController(int pixelQuantity, int correctionLvl){
      this->pixelQuantity = pixelQuantity;
      this->correctionLvl = correctionLvl;
      this->pixels = new WS2812B(this->pixelQuantity);
      this->pixels->begin();
      this->pixels->clear();
    }
    void clearAndShow(){
      this->pixels->clear();
      this->show();
    }
    void show(){
      this->pixels->show();
    }
    void ledsShowStages(int** tab){
      for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
          if(tab[i][j]>=this->correctionLvl)
            this->setColor(i*8+j,255,0,0);
          else
            this->setColor(i*8+j,0,0,0);
      this->show();
    }
    void setColor(int i, int r, int g, int b){
      int reIndex = i-(2*(i%8)-7)*((i/8)%2);
      pixels->setPixelColor(reIndex, pixels->Color(r, g, b));
    }
    void test(){
      for(int i=0;i<64;i++){
        pixels->setPixelColor(i, pixels->Color(255, 0, 255));
        Serial.println(i);
        pixels->show();
        delay(100);
      }
      for(int i=0;i<64;i++){
        pixels->setPixelColor(i, pixels->Color(0, 0, 0));
      }
      Serial.println("clear");
        delay(1000);
      pixels->show();
        delay(1000);
    }
};

#endif