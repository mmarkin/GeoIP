# GeoIP
A library for an ESP8266 or an ESP32 to pull timezone information based on the WiFi network's IP address using an online server called ipapi.co.
No user keys are needed. Just add the library, call it, and read the results from a struct. See the simple sketch in the Examples directory.

Add it to your code:&nbsp;&nbsp;#include &#60;GeoIP&#62;<br>
Create an instance of the class called geoip (or whatever you want to call it)&nbsp;&nbsp;GeoIP geoip;  
Add a struct called loc (or whatever you want to call it) to hold the results:&nbsp;&nbsp;location_t loc;
Get the results:&nbsp;&nbsp;loc = geoip.getGeoFromWiFi(true);<br>
The parameter sets whether or not the library prints the results to the serial monitor.<br> 
 Setting it to true prints the results. Setting it to false or leaving it blank will not print the results.<br><br>
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

