# GeoIP
A library for ESP8266 or ESP32 to pull timezone and location information based on the WiFi network's IP address. 
It does this by accessing an online server called ipapi.co.
No user keys are needed. Just add the library, call its method, and read the results from the struct it returns. See the simple sketch in the Examples directory.

Add the library to your code:<br>
<p style="color green"><b>#include &#60;GeoIP&#62;</b></p>
This adds a new datatype called <b>location_t</b>.<br>
Add a struct of <b>location_t</b> type called <b>loc</b> (or whatever you want to call it) to hold the results:<br>
<b>location_t loc;</b><br>
Create an instance of the class called <b>geoip</b> (or whatever you want to call it)<br>
<b>GeoIP geoip;</b><br>
Get the results:<br>
<b>loc = geoip.getGeoFromWiFi(true);</b><br>
The parameter sets whether or not the library prints the results to the serial monitor.<br> 
Setting it to true prints the results, setting it to false or leaving it blank doesn't.

The results struct has the following members:<br>
latitude - a float value            
longitude - a float value             
country - a character array up to 24 bytes long                      
region - a character array up to 24 bytes long       
city - a character array up to 24 bytes long         
timezone - a character array up to 24 bytes long   
offset - an integer value with the local time zone's UTC offset in hours and minutes (eg. -1130 means -11 hours, 30 minutes)<br>
offsetSeconds - a long integer with the time zone's UTC offset in seconds<br>
status - a boolean value, true if the library successfully received the information, false if it didn't<br><br>
For example, you could say:<br>
<b>Serial.print(loc.timezone);</b><br>
<b>time_t localTime = now() + loc.offsetSeconds;</b>&nbsp;&nbsp;(Assuming the now() function returns UTC time)

