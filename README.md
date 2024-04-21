# GeoIP
A library for an ESP8266 or an ESP32 to pull timezone information using ipapi.co based on the WiFi network's IP address.

Add it to your code: #include <GeoIP>
Create an instance of the class: GeoIP geoip;  
Add a struct to hold the results: location_t loc;
Get the results: loc = geoip.getGeoFromWiFi(true);  



struct IPGeo {
  String tz;
  int offset;
  String city;
  String country;
  String country_code;
  bool is_dst;
  double latitude;
  double longitude;
};
