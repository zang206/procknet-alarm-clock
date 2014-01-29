#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>
#include <LedDisplay.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;
String dayofweek = "";

// Define pins for the LED display. 
// You can change these, just re-wire your board:
#define dataPin 2              // connects to the display's data in
#define registerSelect 3       // the display's register select pin 
#define clockPin 4             // the display's clock pin
#define enable 5               // the display's chip enable pin
#define reset 6               // the display's reset pin

#define displayLength 16        // total number of characters in all three displays


// create am instance of the LED display:
LedDisplay myDisplay = LedDisplay(dataPin, registerSelect, clockPin, 
enable, reset, displayLength);

int brightness = 15;           // screen brightness
int myDirection = 1;           // direction of scrolling.  -1 = left, 1 = right.


void setup() {
   // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:


// initialize the display library:
  myDisplay.begin();
  delay(100);
  myDisplay.clear();
  myDisplay.setBrightness(brightness);
  delay(100);
}  


void loop() {
  myDisplay.home();
  if (RTC.read(tm))
  {
    DOW();
    if (tm.Hour >= 0 && tm.Hour < 10) {
      myDisplay.setCursor(0);
      myDisplay.print("0");
      myDisplay.print(tm.Hour);
    }
    else {
      myDisplay.setCursor(0);
      myDisplay.print(tm.Hour);
    }
    myDisplay.setCursor(2);
    myDisplay.print(":");
    if (tm.Minute >= 0 && tm.Minute < 10) {
      myDisplay.setCursor(3);
      myDisplay.print("0");
      myDisplay.print(tm.Minute);
    }
    else {
      myDisplay.setCursor(3);
      myDisplay.print(tm.Minute);
    }
    myDisplay.setCursor(2);
    //print2digits(tm.Month);
    if (tm.Month >= 0 && tm.Month < 10) {
      myDisplay.setCursor(6);
      myDisplay.print("0");
      myDisplay.print(tm.Month);
    }
    else {
      myDisplay.setCursor(6);
      myDisplay.print(tm.Month);
    }
    myDisplay.setCursor(8);
    myDisplay.print("/");
    if (tm.Day >= 0 && tm.Day < 10) {
      myDisplay.setCursor(9);
      myDisplay.print("0");
      myDisplay.print(tm.Day);
    }
    else {
      myDisplay.setCursor(9);
      myDisplay.print(tm.Day);
    }
    //myDisplay.setCursor(11);
    //myDisplay.print("/");
    myDisplay.setCursor(13);
    myDisplay.print(dayofweek);
    //myDisplay.print(tmYearToCalendar(tm.Year));
    delay(1000);
  }
  else
  {
    if (RTC.chipPresent)
    {
      myDisplay.print("RTC Not Setup");
      delay(1000);
    }
    else {
      myDisplay.print("RTCNotConnected");
      delay(1000);
    }
  }  
}

void DOW() {
  switch (tm.Wday) {
    case 1:
      dayofweek = ("Tue");
      break;
    case 2:
      dayofweek = ("Wed");
      break;
    case 3:
      dayofweek = ("Thu");
      break;
    case 4:
      dayofweek = ("Fri");
      break;
    case 5:
      dayofweek = ("Sat");
      break;
    case 6:
      dayofweek = ("Sun");
      break;
    case 7:
      dayofweek = ("Mon");
      break;
    //default: 
      // if nothing else matches, do the default
      // default is optional
  }
}

