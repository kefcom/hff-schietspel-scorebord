#include "FastLED.h"

#define LED_COUNT 14
#define LED_PIN1 12
#define LED_PIN2 13
#define SCOREPIN 14
#define RESETPIN 4
#define BTNDEBOUNCE 1000

CRGB outputColor = CRGB::Red;

unsigned long lastResetTime;

int theScore = 0;


CRGB leds1[LED_COUNT];
CRGB leds2[LED_COUNT];

bool number0[14] = {1,1,1,1,1,1,1,1,1,1,1,1,0,0};
bool number1[14] = {0,0,1,1,1,1,0,0,0,0,0,0,0,0};
bool number2[14] = {1,1,1,1,0,0,1,1,1,1,0,0,1,1};
bool number3[14] = {1,1,1,1,1,1,1,1,0,0,0,0,1,1};
bool number4[14] = {0,0,1,1,1,1,0,0,0,0,1,1,1,1};
bool number5[14] = {1,1,0,0,1,1,1,1,0,0,1,1,1,1};
bool number6[14] = {1,1,0,0,1,1,1,1,1,1,1,1,1,1};
bool number7[14] = {1,1,1,1,1,1,0,0,0,0,0,0,0,0};
bool number8[14] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};
bool number9[14] = {1,1,1,1,1,1,1,1,0,0,1,1,1,1};

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN1>(leds1, LED_COUNT);
  FastLED.addLeds<NEOPIXEL, LED_PIN2>(leds2, LED_COUNT);

  pinMode(SCOREPIN, INPUT_PULLUP);
  pinMode(RESETPIN, INPUT_PULLUP);
  lastResetTime = millis();  
}

void showNumber(int theNr)
{
  if(theNr > 9)
  {
    setNumber(2, theNr %10);
    setNumber(1, theNr /10);    
  }else{
    setNumber(1, 0);
    setNumber(2, theNr);
  }

}

void setNumber(int dgit, int numbr)
{
  int currNr[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
  for(int i = 0; i<LED_COUNT; i++)
  {
    switch(numbr)
    {
      case 0:
        currNr[i] = number0[i];
        break;
      case 1:
        currNr[i] = number1[i];
        break;
      case 2:
        currNr[i] = number2[i];
        break;
      case 3:
        currNr[i] = number3[i];
        break;
      case 4:
        currNr[i] = number4[i];
        break;
      case 5:
        currNr[i] = number5[i];
        break;
      case 6:
        currNr[i] = number6[i];
        break;
      case 7:
        currNr[i] = number7[i];
        break;
      case 8:
        currNr[i] = number8[i];
        break;
      case 9:
        currNr[i] = number9[i];
        break;                                                        
    }
  }
  for(int i = 0; i<LED_COUNT; i++)
  {
    if(currNr[i] == 1)
    {
      if(dgit == 1)
      {
        leds1[i] = outputColor;
      }else{
        leds2[i] = outputColor;
      }
    }else{
      if(dgit == 1)
      {
        leds1[i] = CRGB::Black;
      }else{
        leds2[i] = CRGB::Black;
      }
    }
  } 
}

void loop() {
  showNumber(theScore);
  
  if(digitalRead(SCOREPIN) == 0 && ( millis() - lastResetTime) > BTNDEBOUNCE)
  {
    //score up
    Serial.println("SCORE UP!");
    theScore++;
    lastResetTime = millis();

  }
  if(digitalRead(RESETPIN) == 0 && (millis() - lastResetTime) > BTNDEBOUNCE)
  {
    //RESET
    theScore = 0;
    lastResetTime = millis();
  }  

  FastLED.show();

}
