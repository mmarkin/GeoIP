/**************************************************************************
 *
 * GeoIP.h - Library for getting geographic information from IP address.
 * Using ESP8266  or ESP32 device.
 * v 1.3.2
 * Created by Mitch Markin, May 18, 2018.
 *         revised          July 16, 2018. 
 *         revised          December 1, 2021.
 *         revised          August 28, 2024.
 *  Released into the public domain.       
 * 
 **************************************************************************/

#ifndef GeoIP_h
#define GeoIP_h

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

typedef struct {
    float latitude;             
    float longitude;     
    char  country[24];                
    char  region[24];
    char  city[24];
    char  timezone[24];  
    int   offset;              // UTC offset in hours and minutes (eg. -1130 means -11 hours, 30 minutes)
    long  offsetSeconds;
    bool  status;       
} location_t; 

class GeoIP
{
  public:
    GeoIP();                                  // constructor   
    location_t getGeoFromWiFi(const bool showResults = false);
    location_t getGeoFromWiFi(const char *apiKey, const bool showResults = false);                            
    
  protected: 
    location_t location;     
    JsonDocument doc;  
    const char *key;
    location_t getInfo(bool hasKey);   
    void results();
    void setStruct();                   
};

#endif

/**************************************************************************
 *  
 * End
 *  
 **************************************************************************/
