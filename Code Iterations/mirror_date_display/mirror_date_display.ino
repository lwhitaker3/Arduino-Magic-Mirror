// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
bool blinkColon = false;

//int hours;
//int mins;

float currentMonth;
float currentDay;


RTC_DS3231 rtc;
Adafruit_7segment matrix = Adafruit_7segment();
Adafruit_7segment matrix2 = Adafruit_7segment();

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif

  

  Serial.begin(9600);

  matrix.begin(0x70);
  matrix.setBrightness(1);

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
    
//    Serial.print(now.year(), DEC);
//    Serial.print('/');
    
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(" (");
//    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    Serial.print(") ");
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.println(now.minute(), DEC);

//    hours = now.hour();
//    mins = now.minute();
//    int displayValue = hours*100 + mins;
//    matrix.print(displayValue, DEC);
//    matrix.drawColon(true);
//    matrix.writeDisplay();

    currentMonth = now.month();
    currentDay = now.day();
    float displayValue = currentMonth + (currentDay/100);
    Serial.println(displayValue);
    matrix.print(displayValue);
    matrix.writeDisplay();
    
    



    delay(1000);
}
