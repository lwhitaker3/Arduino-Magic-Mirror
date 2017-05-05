// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
bool blinkColon = false;
int hours;
int mins;
float currentMonth;
float currentDay;

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
  alpha4.setBrightness(10);

  matrix.begin(0x71);
  matrix.setBrightness(10);

  matrix2.begin(0x72);
  matrix2.setBrightness(10);


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


    DateTime now = rtc.now();
    alpha4.clear();
    
//    Serial.print(now.year(), DEC);
//    Serial.print('/');
    
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(" (");
//    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//      Serial.print(sizeof(daysOfTheWeek[now.dayOfTheWeek()]));
      for( int i = 0 ; i < 5 ; ++i ){
        today[ i ] = daysOfTheWeek[now.dayOfTheWeek()][ i ];
      }
      for( int j = 0 ; j < 4 ; ++j){
        Serial.println((int) today[j]);
        if (today[j] == '\0'){
          break;
        }
        alpha4.writeDigitAscii(j, today[j]);
      }
      
//    Serial.print(") ");
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.println(now.minute(), DEC);
//      alpha4.writeDigitAscii(0, days[0]);
//      alpha4.writeDigitAscii(1, days[1]);
//      alpha4.writeDigitAscii(2, days[2]);
      alpha4.writeDisplay();
//    
//    Serial.println(today);

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
      Serial.println(displayValue2);
      matrix2.print(displayValue2);
      matrix2.writeDisplay();

      


      

    delay(1000);
}
