# GeoIP
A library for ESP8266 or ESP32 to pull timezone and location information based on the WiFi network's IP address. 
It does this by accessing an online server called ipapi.co.
No user account or access key is needed to use ipapi.co's free plan. Just add the library to your code, call its method, 
and read the results from the struct it returns.

ipapi.co's free plan allows a client 30,000 lookups per month. If you need more they have paid subscriptions starting 
at $12US per month. In that case, your API key can be added when the library's method is called as shown below. 

The library is available in the library managers for PlatformIO and the Arduino IDE. Just search for geoip.
For PlatformIO it can be installed automatically by adding this line to the project's platformio.ini file:       
lib_deps = mmarkin/GeoIP@^1.3.1 

Here is a quick summary on how to use the library in your code. See the simple sketch in the examples directory for details.  
First include the library, declare a location_t variable, and create an instance of the GeoIP class.  
```c
#include <GeoIP.h>                 // add the GeoIP class, creates a new data type called location_t
location_t loc;                    // declare a location_t variable to hold the results
GeoIP geoip;                       // create an instance of the GeoIP class
```
Then get the results by using one of these function calls depending on whether or not you have an API key and you want the results 
shown on the serial monitor. If supplying an API key it must be inside double quotation marks.  
```c
loc = geoip.getGeoFromWiFi();                        // no key, results not shown on serial monitor
loc = geoip.getGeoFromWiFi(false);                   // no key, results not shown on serial monitor
loc = geoip.getGeoFromWiFi(true);                    // no key, show results on on serial monitor
loc = geoip.getGeoFromWiFi("Your API Key");          // use API key, results not shown on serial monitor
loc = geoip.getGeoFromWiFi("Your API Key", false)  ; // use API key, results not shown on serial monitor
loc = geoip.getGeoFromWiFi("Your API Key", true);    // use API key, show results on on serial monitor
```

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

The now() function mentioned above is part of the TimeLib library. It's frequently used in code for ESP devices that sync to Network Time Protocol (NTP) servers.
The now() function keeps track of time and date in seconds. NTP servers send a timestamp that combines the time and date in one long integer as the number of seconds
that have elapsed since midnight, January 1, 1970, UTC. Therefore to show local time the timestamp has to be adjusted by the number of seconds local time differs from UTC. 
