# GeoIP
A library for ESP8266 or ESP32 to pull timezone and location information based on the WiFi network's IP address. 
It does this by accessing an online server called ipapi.co.
No user keys are needed. Just add the library, call its method, and read the results from the struct it returns. 
See the simple sketch in the Examples directory.    
ipapi.co's free plan allows a client 30,000 lookups per month. If you need more they have paid subscriptions starting 
at $12US per month. 

Use the library in your code:
```c
include <GeoIP.h>                  // add the library, creates a new data type  called location_t
location_t loc;                    // declare a location_t variable
GeoIP geoip;                       // create an instance of GeoIP class
loc = geoip.getGeoFromWiFi(true);  // get the results
```
The parameter sets whether or not the library prints the results to the serial monitor.    
Setting it to true prints the results, setting it to false or leaving it blank doesn't.

The library returns the results in a struct with the following members:    
latitude - a float value            
longitude - a float value             
country - a character array up to 24 bytes long                      
region - a character array up to 24 bytes long       
city - a character array up to 24 bytes long         
timezone - a character array up to 24 bytes long   
offset - an integer value with the local time zone's UTC offset in hours and minutes (eg. -1130 means -11 hours, 30 minutes)<br>
offsetSeconds - a long integer with the time zone's UTC offset in seconds    
status - a boolean value, true if the library successfully received the information, false if it didn't    

For example, you could say:
```c
Serial.print(loc.timezone);    
time_t localTime = now() + loc.offsetSeconds;    // the now() function returns UTC time
```

