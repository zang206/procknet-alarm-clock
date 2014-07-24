/*Alarm clock code for to be used on a Pro Mini 5v 16mhz and a DS1307 RTC.  Using example code from 
TimeAlarmExample.pde and DS1307RTC from www.pjrc.com.  Making this project for my wife for which
normal alarm clocks are effective any more.  Currently we have three and she still gets up late if
at all every morning.

When completed the sketch will retreve the time from the RTC every cycle of the loop function.
Will display date and time on 5x7, 16 character dot matrix display.  Have a snooze button. 
Alarm on/off switch. A very loud siren to wake the dead, or my wife.
*/

/*
There will be a few iterations of this program as I add in and test additional code for 
the different hardware pieces.
*/

/*
This sketch  triggers daily alarms at 8:30 am and 17:45 pm.
A Timer is triggered every 15 seconds, another timer triggers once only after 10 seconds.
A weekly alarm is triggered every Sunday at 8:30:30
*/
#include <DS1307RTC.h>
#include <Wire.h>
#include <Time.h>
#include <TimeAlarms.h>


void setup()
{
  Serial.begin(9600);
  setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011
  // create the alarms 
  Alarm.alarmRepeat(8,30,0, MorningAlarm);  // 8:30am every day
  Alarm.alarmRepeat(17,45,0,EveningAlarm);  // 5:45pm every day 
  Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 

 
  Alarm.timerRepeat(15, Repeats);            // timer for every 15 seconds    
  Alarm.timerOnce(10, OnceOnly);             // called once after 10 seconds 
}

void  loop(){  
  digitalClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}

// functions to be called when an alarm triggers:
void MorningAlarm(){
  Serial.println("Alarm: - turn lights off");    
}

void EveningAlarm(){
  Serial.println("Alarm: - turn lights on");           
}

void WeeklyAlarm(){
  Serial.println("Alarm: - its Monday Morning");      
}

void ExplicitAlarm(){
  Serial.println("Alarm: - this triggers only at the given date and time");       
}

void Repeats(){
  Serial.println("15 second timer");         
}

void OnceOnly(){
  Serial.println("This timer only triggers once");  
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
