// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"


bool blinkColon = false;
int hours;
int mins;
float currentMonth;
float currentDay;

int pirInputPin = 12;               
int pirState = LOW;             
int pirVal = 0; 

int currentPhrase = 0;

unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)

Adafruit_NeoPixel butterfly1 = Adafruit_NeoPixel(1,9, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel butterfly2 = Adafruit_NeoPixel(1,10, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel butterfly3 = Adafruit_NeoPixel(1,11, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel cherryTree = Adafruit_NeoPixel(8,8, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel phrase1 = Adafruit_NeoPixel(6,6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel phrase2 = Adafruit_NeoPixel(6,7, NEO_GRB + NEO_KHZ800);


//int hours;
//int mins;



RTC_DS3231 rtc;
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
Adafruit_7segment matrix = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();

char daysOfTheWeek[7][5] = {"SUN", "MON", "TUES", "WED", "THUR", "FRI", "SAT"};

char today[5];

void setup () {


  Serial.begin(9600);
  alpha4.begin(0x70);  // pass in the address
  alpha4.setBrightness(7);

  matrix.begin(0x71);
  matrix.setBrightness(7);

  matrix2.begin(0x72);
  matrix2.setBrightness(7);

  pinMode(pirInputPin, INPUT);     

  butterfly1.begin();
  butterfly1.show(); // Initialize all pixels to 'off'
  butterflyLights1(butterfly1.Color(255,0,100), 50);

  
  butterfly2.begin();
  butterfly2.show(); // Initialize all pixels to 'off'
  butterflyLights2(butterfly2.Color(88,2,163), 50);

  butterfly3.begin();
  butterfly3.show(); // Initialize all pixels to 'off'
  butterflyLights3(butterfly3.Color(230,80,0), 50);

  cherryTree.begin();
  cherryTree.show();

  phrase1.begin();
  phrase1.show();

  phrase2.begin();
  phrase2.show();



  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {

     unsigned long currentMillis = millis();

     if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        DateTime now = rtc.now();
        alpha4.clear();
        for( int i = 0 ; i < 5 ; ++i ){
          today[ i ] = daysOfTheWeek[now.dayOfTheWeek()][ i ];
        }
        for( int j = 0 ; j < 4 ; ++j){
//          Serial.println((int) today[j]);
          if (today[j] == '\0'){
            break;
          }
          alpha4.writeDigitAscii(j, today[j]);
        }
        
        alpha4.writeDisplay();    
        
        hours = now.hour();
        mins = now.minute();
        int displayValue = hours*100 + mins;
        matrix.print(displayValue, DEC);
        matrix.drawColon(blinkColon);
        matrix.writeDisplay();

        if (!blinkColon){
          blinkColon = true;    
        }else{
          blinkColon = false;
        }


      
        currentMonth = now.month();
        currentDay = now.day();
        float displayValue2 = currentMonth + (currentDay/100);
//        Serial.println(displayValue2);
        matrix2.print(displayValue2);
        matrix2.writeDisplay();
        
     }


      pirVal = digitalRead(pirInputPin);  // read input value
      if (pirVal == HIGH) {
        
        // check if the input is HIGH
        if (pirState == LOW) {
          // we have just turned on
          Serial.println("Motion detected!");

          if (currentPhrase==0){
            phrase1Lights(phrase1.Color(255,0,100), 50);
            currentPhrase = 1;
          } else if (currentPhrase==1){
            phrase2Lights(phrase2.Color(255,0,100), 50);
            currentPhrase = 0;
          }
          
          // We only want to print on the output change, not state
          pirState = HIGH;
        }
      } else {
        
        if (pirState == HIGH){
          phrase1Lights(phrase1.Color(0,0,0), 50);
          phrase2Lights(phrase1.Color(0,0,0), 50);
          // we have just turned of
          Serial.println("Motion ended!");
          // We only want to print on the output change, not state
          pirState = LOW;
        }
      }


     
      
      if(hours>=6 && hours<7){
        cherryTreeLights(cherryTree.Color(255,0,100), 50); //pink
      }
      else if(hours>=7 && hours<8){
        cherryTreeLights(cherryTree.Color(255,0,0), 50); //red
      }
      else if(hours>=8 && hours<9){
        cherryTreeLights(cherryTree.Color(230,80,0), 50); //orange
      }
      else if(hours>=9 && hours<12){
        cherryTreeLights(cherryTree.Color(255,255,0), 50); //yellow
      }
      else if(hours>=12 && hours<15){
        cherryTreeLights(cherryTree.Color(0,255,0), 50); //green
      }
      else if(hours>=15 && hours<17){
        cherryTreeLights(cherryTree.Color(255,255,0), 50); //yellow
      }
      else if(hours>=17 && hours<18){
        cherryTreeLights(cherryTree.Color(230,80,0), 50); //orange
      }
      else if(hours>=18 && hours<19){
        cherryTreeLights(cherryTree.Color(255,0,0), 50); //red
      }
      else if(hours>=19 && hours<20){
        cherryTreeLights(cherryTree.Color(255,0,100), 50); //pink
      }
      else{
        cherryTreeLights(cherryTree.Color(32,178,170), 50);
      }
            
      delay(1000);
}

void butterflyLights1(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<butterfly1.numPixels(); i++) {
    butterfly1.setPixelColor(i, c);
    butterfly1.show();
    delay(wait);
  }
}

void butterflyLights2(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<butterfly2.numPixels(); i++) {
    butterfly2.setPixelColor(i, c);
    butterfly2.show();
    delay(wait);
  }
}

void butterflyLights3(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<butterfly3.numPixels(); i++) {
    butterfly3.setPixelColor(i, c);
    butterfly3.show();
    delay(wait);
  }
}

void cherryTreeLights(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<cherryTree.numPixels(); i++) {
    cherryTree.setPixelColor(i, c);
    cherryTree.show();
    delay(wait);
  }
}

void phrase1Lights(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<phrase1.numPixels(); i++) {
    phrase1.setPixelColor(i, c);
    phrase1.show();
    delay(wait);
  }
}

void phrase2Lights(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<phrase2.numPixels(); i++) {
    phrase2.setPixelColor(i, c);
    phrase2.show();
    delay(wait);
  }
}
