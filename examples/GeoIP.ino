/*******************************************************************************************************
 *
 *  Example for GeoIP Library - geographic information from IP address.
 *  Using ESP8266 or ESP32 device.
 *
 *  April 20, 2024
 *  
 *******************************************************************************************************/

// For ESP8266
#include <ESP8266WiFi.h>         
#include <ESP8266WiFiMulti.h>

// For ESP32 
//#include <WiFi.h>                             
//#include <WiFiMulti.h>

#include <GeoIP.h>

GeoIP geoip;                                  // create GeoIP object 'geoip'
ESP8266WiFiMulti wifiMulti;                   // create WiFiMulti object 'wifiMulti' 

location_t loc;                               // data structure to hold results 

void setup()
{
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_STA);

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

  while (!loc.status && count < 21)     // Try up to 20 times to connect to geoip server.
                                        // Usually it happens on the first try.
  {
    count++;
    Serial.printf("Attempt %u of 20 to get Geo info.\r\n", count); 

    // Use one of the following function calls. If using API key it must be inside double quotation marks.
    
    loc = geoip.getGeoFromWiFi();                        // no key, results not shown on serial monitor
    //loc = geoip.getGeoFromWiFi(false);                   // no key, results not shown on serial monitor
    //loc = geoip.getGeoFromWiFi(true);                    // no key, show results on on serial monitor
    //loc = geoip.getGeoFromWiFi("Your API Key");          // use API key, results not shown on serial monitor
    //loc = geoip.getGeoFromWiFi("Your API Key", false);   // use API key, results not shown on serial monitor
    //loc = geoip.getGeoFromWiFi("Your API Key", true);    // use API key, show results on on serial monitor                                    
  } 

  if (loc.status)                          // Check to see if the data came in from the server.
  {
    // Display information from GeoIP. The library can do this too if true is added to the function call.   
  
    Serial.print("\nLatitude: ");               Serial.println(loc.latitude);      // float
    Serial.print("Longitude: ");                Serial.println(loc.longitude);     // float
    Serial.print("City: ");                     Serial.println(loc.city);          // char[36]
    Serial.print("Region: ");                   Serial.println(loc.region);        // char[36]
    Serial.print("Country: ");                  Serial.println(loc.country);       // char[36]    
    Serial.print("Timezone: ");                 Serial.println(loc.timezone);      // char[36]
    Serial.print("UTC Offset: ");               Serial.println(loc.offset);        // int  (eg. -1000 means -10 hours, 0 minutes)
    Serial.print("Offset Seconds: ");           Serial.println(loc.offsetSeconds); // long    
  } 
  else
  {
    Serial.println("Data received was not valid.");
  }  
}

void loop()
{
}
