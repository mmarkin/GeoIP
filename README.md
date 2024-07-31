# GeoIP
A library for ESP8266 or ESP32 to pull timezone and location information based on the WiFi network's IP address. 
It does this by accessing an online server called ipapi.co.
No user account or access key is needed to use ipapi.co's free plan. Just add the library to your code, call its method, 
and read the results from the struct it returns.

The library is available in the library managers for PlatformIO and the Arduino IDE. Just search for geoip.
For PlatformIO it can be installed automatically by adding this line to the project's platformio.ini file:       
lib_deps = mmarkin/GeoIP@^1.2.6    

ipapi.co's free plan allows a client 30,000 lookups per month. If you need more they have paid subscriptions starting 
at $12US per month. 

To use the library in your code:
```c
#include <GeoIP.h>                 // add the GeoIP class, creates a new data type called location_t
location_t loc;                    // declare a location_t variable 
GeoIP geoip;                       // create an instance of the GeoIP class
loc = geoip.getGeoFromWiFi(true);  // get the results
```
The parameter in the function call sets whether or not the library prints the results to the serial monitor.    
Setting it to true prints the results, setting it to false or leaving it blank doesn't.

The library returns the results in a struct with the following members:    
latitude - a float value            
longitude - a float value             
country - a character array up to 24 bytes long                      
region - a character array up to 24 bytes long       
city - a character array up to 24 bytes long         
timezone - a character array up to 24 bytes long   
offset - an integer value with the local time zone's UTC offset in hours and minutes (eg. -1130 means -11 hours, 30 minutes or 800 means 8 hours, 0 minutes)        
offsetSeconds - a long integer with the time zone's UTC offset in seconds    
status - a boolean value, true if the library successfully received the information, false if it didn't    

For example, you could say:
```c
Serial.print(loc.timezone);    
time_t localTime = now() + loc.offsetSeconds;    // assuming the now() function returns UTC time
```

(The now() function mentioned is part of the TimeLib library. It usually gets set to UTC time in code for ESP devices that sync to Network Time Protocol servers.)

See the simple sketch in the examples directory for more details.

