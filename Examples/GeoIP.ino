/*******************************************************************************************************
 *
 *  Example for GeoIP Library - geographic information from IP address.
 *  Using ESP8266 device.
 *
 *  April 20, 2024
 *  
 *******************************************************************************************************/
 
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <GeoIP.h>

GeoIP geoip;                                  // create GeoIP object 'geoip'
ESP8266WiFiMulti wifiMulti;                   // create WiFiMulti object 'wifiMulti' 

location_t loc;                               // data structure to hold results 

void setup()
{
  Serial.begin(115200);
  delay(100);  

  wifiMulti.addAP("SSID", "Password");              // first SSID to try
  wifiMulti.addAP("SSID", "Password");              // second SSID to try, etc.

  Serial.println("\nConnecting ...");
  
  while (wifiMulti.run() != WL_CONNECTED) 
  { 
    Serial.print('.');
    delay(100);
  } 

  Serial.print("\nConnected to ");   Serial.println(WiFi.SSID());
  Serial.print("IP address: ");      Serial.println(WiFi.localIP());
  Serial.print("Gateway: ");         Serial.println(WiFi.gatewayIP());  

  loc.status = false;
  uint8_t count = 0;

  while (!loc.status && count < 21)     // Try 20 times to connect to geoip server.
                                        // Usually it happens on the first try.
  {
    count++;
    Serial.printf("Attempt %u of 20 to get Geo info.\r\n", count);    
    loc = geoip.getGeoFromWiFi(true);      // true to show results on serial monitor
    //loc = geoip.getGeoFromWiFi(false);     // false to not show results on serial monitor
    //loc = geoip.getGeoFromWiFi();          // no parameter to not show results on serial monitor                                        
  } 

  if (loc.status)                          // Check to see if the data came in from the server.
  {
    // Display information from GeoIP. The library can do this too if called with the parameter set to true.   
  
    Serial.print("\nLatitude: ");               Serial.println(loc.latitude);      // float
    Serial.print("Longitude: ");                Serial.println(loc.longitude);     // float
    Serial.print("City: ");                     Serial.println(loc.city);          // char[24]
    Serial.print("Region: ");                   Serial.println(loc.region);        // char[24]
    Serial.print("Country: ");                  Serial.println(loc.country);       // char[24]    
    Serial.print("Timezone: ");                 Serial.println(loc.timezone);      // char[24]
    Serial.print("UTC Offset: ");               Serial.println(loc.offset);        // int  (eg. -1000 means -10 hours, 0 minutes)
    Serial.print("Offset Seconds: ");           Serial.println(loc.offsetSeconds); // long
      
    delay(2000);
  } 
  else
  {
    Serial.println("Data received was not valid.");
  }  
}

void loop()
{
}
