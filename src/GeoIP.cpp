/*******************************************************************************************************
 *
 *  GeoIP.cpp - Library for getting geographic information from IP address.
 *  Using ESP8266 or ESP32 device.
 *  Created by Mitch Markin, May 18, 2018.
 *             revised       July 16, 2018. 
 *             revised       December 1, 2021.
 *             revised       July 14, 2022 to add status.
 *             revised       March 15, 2024 to use ArduinoJson 7.
 *                           Adapted from Benoit Blanchon's HTTP example from the ArduinoJson library.
 *                           April 24, 2024
 *                           Added information returned if things went wrong.
 *  Released into the public domain.    
 * 
 *******************************************************************************************************/

#include "GeoIP.h"  

GeoIP::GeoIP()    // constructor
{ }

location_t GeoIP::getGeoFromWiFi()
{
  location_t temp = getInfo();
  return temp;
}

location_t GeoIP::getGeoFromWiFi(const bool showResults)
{
  location_t temp = getInfo();

  if (showResults)
  {  
    Serial.println(F("Json parsing results from GeoIP:"));
    Serial.print(F("  City:           "));      Serial.println(temp.city);
    Serial.print(F("  Region:         "));      Serial.println(temp.region);    
    Serial.print(F("  Country:        "));      Serial.println(temp.country);     
    Serial.print(F("  Latitude:       "));      Serial.println(temp.latitude, 3);
    Serial.print(F("  Longitude:      "));      Serial.println(temp.longitude, 3);
    Serial.print(F("  Time Zone:      "));      Serial.println(temp.timezone);    
    Serial.print(F("  UTC Offset:     "));      Serial.println(temp.offset);
    Serial.print(F("  Offset Seconds: "));      Serial.println(temp.offsetSeconds);
  }
  return temp;
}

// Use WiFiClientSecure class to create TLS connection

location_t GeoIP::getInfo()
{
  const char* host = "ipapi.co";
  const int httpsPort = 443; 
  WiFiClientSecure client;
  location_t location;
  
  client.setInsecure();
  
  location.offsetSeconds = 0;    
  location.offset = 0;  
  strncpy(location.region, "Not set", 8);
  strncpy(location.country, "Not set", 8);
  strncpy(location.timezone, "Not set", 8);
  location.latitude = 0.0;
  location.longitude = 0.0;
  location.status = false;
 
  Serial.print(F("Starting connection to Geo IP server "));   
  Serial.println(host);

  if (!client.connect(host, httpsPort))  
  {
    Serial.println(F("Connection to Geo IP server failed"));
    strncpy(location.city, "Connection failed",18);
    return location;
  }

  Serial.println(F("Connected!"));

  // Send HTTP request
  client.println(F("GET /json/ HTTP/1.1"));
  // If you have an API key provied by ipapi.co use this line instead of the one above and insert your key
  //client.println(F("GET /json/?key=<api key provided by ipapi> HTTP/1.1"));
  client.print(F("Host: "));   
  client.println(host);
  client.println(F("User-Agent: esp-idf/1.0 esp32"));
  client.println(F("Connection: close"));

  if (client.println() == 0) 
  {
    Serial.println(F("Failed to send request"));
    client.stop();
    strncpy(location.city, "Request not sent", 17);
    return location;
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));

  // It should be "HTTP/1.0 200 OK" or "HTTP/1.1 200 OK"
  if (strcmp(status + 9, "200 OK") != 0) 
  {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    client.stop();
    strncpy(location.city, "Unexpected response", 20);
    return location;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";

  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
    client.stop();
    strncpy(location.city, "Invalid response", 17);
    return location;
  }

  // Parse JSON object
  JsonDocument doc;  
  DeserializationError error = deserializeJson(doc, client);

  if (error) 
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    client.stop();
    strncpy(location.city, "Json parsing failed", 20);
    return location;
  }

  // Set the geo info struct. 
  // There is other information about the location in the JSON document 
  // such as country code, continent, country capital, languages, calling code, currency, 
  // and the network's IP address and ISP.
  
  strncpy(location.city, (doc["city"].as<const char*>()), sizeof(location.city)-1);
  strncpy(location.region, (doc["region"].as<const char*>()), sizeof(location.region)-1);
  strncpy(location.country, (doc["country_name"].as<const char*>()), sizeof(location.country)-1);
  location.latitude = (doc["latitude"].as<float>());
  location.longitude = (doc["longitude"].as<float>());
  strncpy(location.timezone, (doc["timezone"].as<const char*>()), sizeof(location.timezone)-1); 
  // UTC offset is in hours and minutes (eg. -1130 means -11 hours, 30 minutes or 800 means 8 hours, 0 minutes)
  location.offset = (doc["utc_offset"].as<int>());         
  location.offsetSeconds = (location.offset / 100) * 3600 + (location.offset % 100) * 60;             
  location.status = true; 

  // Make sure the character arrays are terminated 

  location.city[sizeof(location.city)-1] = '\0';
  location.region[sizeof(location.region)-1] = '\0';
  location.country[sizeof(location.country)-1] = '\0';
  location.timezone[sizeof(location.timezone)-1] = '\0';
  
  client.stop();     
  return location;   
}  

/*******************************************************************************************************
 * 
 *    End
 *    
 *******************************************************************************************************/    
