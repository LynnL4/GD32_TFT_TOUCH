#include "SPI.h"
#include "TFT_eSPI.h"
#include "XPT2046.h"
XPT2046 xpt(PE2, PE3, PE0, PD13, PE4);
// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();


void setup(void) {

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_CYAN);
  Serial.begin(115200);
  xpt.begin();
}


void loop() {

  int16_t x, y;
  if(xpt.touchDown()){
  xpt.getXY(&x , &y);
  Serial.print("X:");
  Serial.print(x);
  Serial.print("\t y:");
  Serial.println(y);
  }

}
