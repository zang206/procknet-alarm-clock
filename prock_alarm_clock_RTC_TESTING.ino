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
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

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
  bool parse = false;
  bool config = false;
  
   // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

// initialize the display library:
  myDisplay.begin();
  delay(100);
  myDisplay.clear();
  myDisplay.setBrightness(brightness);
  delay(100);

  //while (!Serial) ; // wait for Arduino Serial Monitor
  //delay(200);
//  Serial.print("type in anything: ");
}  


void loop() {
  //myDisplay.clear();
  myDisplay.home();
  if (RTC.read(tm))
  {
    DOW();
    //print2digits(tm.Hour);
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
/*
bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}
*/

/*
  Serial Event example
 
 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and 
 clears it.
 
 A good test for this is to try it with a GPS receiver 
 that sends out NMEA 0183 sentences. 
 
 Created 9 May 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/SerialEvent
 
 */


/*
void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString); 
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}


  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
/* 
void serialEvent() 
{
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') 
    {
      stringComplete = true;
    } 
  }
}


void print2digits(int number) {
  if (number >= 0 && number < 10) {
    myDisplay.print('0');
  }
  myDisplay.print(number);
}
*/
/*
void readRTC() {
  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);

  
}
*/
