// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
// Default is to set RTC time to time sketch is compiled
// Check results here : https://www.timeanddate.com/worldclock/converted.html
// Added UTC offset calculations

#include <Wire.h>
#include "RTClib.h"

// Uncomment to set RTC to UCT Time

// #define UTC_ON

RTC_PCF8523 rtc;
float UTCOffset = -4.0; // Your timezone relative to UTC

void setup()
{

  Serial.begin(115200);
  if (!rtc.begin())
  {
    // If the RTC is not present complain and bail
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

#ifdef UTC_ON
  // Set RTC to date/time sketch is compiled
  rtc.adjust(DateTime(__DATE__, __TIME__));
  delay(1000);
  DateTime now = rtc.now();
  // Adjust the time from local to UTC
  DateTime UTCTime(now.unixtime() - 3600 * UTCOffset);
  // Reset RTC to adjusted time (Local +/- UTC)
  rtc.adjust(UTCTime);
#else
  // Set RTC to date/time sketch is compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Sets RTC
#endif
}

void loop()
{

  DateTime now = rtc.now();

  // Define character buffer to hold date/time

  char tbuffer[25] = ""; //Time buffer

  // Stuff date/time from RTC "now" into our buffer, note we are picking the bits
  // we want from the "rtc.now" function
  // Print it out so we can check.

  sprintf(tbuffer, "%04d/%02d/%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());

  Serial.println(tbuffer);
  delay(5000);
}
