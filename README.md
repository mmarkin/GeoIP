# GeoIP
A library for an ESP8266 or an ESP32 to pull timezone information using ipapi.co based on the WiFi network's IP address.

Add it to your code: #include <GeoIP><br>
Create an instance of the class: GeoIP geoip;<br>  
Add a struct to hold the results: location_t loc;<br>
Get the results: loc = geoip.getGeoFromWiFi(true);<br>
The parameter sets whether or not the library prints the results to the serial monitor. Setting it to true prints the results. 
Setting it to false or leaving it blank will not print the results.<br><br>
The results struct has the following members:<br>
latitude - a float value            
longitude - a float value             
country - a 24-byte character array                       
region - a 24-byte character array       
city - a 24-byte character array        ;
timezone - a 24-byte character array   
offset - an integer value with the local time zone's UTC offset in hours and minutes (eg. -1130 means -11 hours, 30 minutes)<br>
offsetSeconds - a long integer with the time zone's UTC offset in seconds<br>
status - a boolean value, true if the library successfully received the information, false if it didn't<br><br>
See the simple sketch in the Examples directory.
