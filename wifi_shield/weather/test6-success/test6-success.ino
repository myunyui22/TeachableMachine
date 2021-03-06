#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <JsonListener.h>
#include <time.h>
#include "OpenWeatherMapCurrent.h"

OpenWeatherMapCurrent client;

// See https://docs.thingpulse.com/how-tos/openweathermap-key/
String OPEN_WEATHER_MAP_APP_ID = "39a0ff4bc161a5cfb71be4079e4c9f47";

String OPEN_WEATHER_MAP_LOCATION_ID = "1846326";

String OPEN_WEATHER_MAP_LANGUAGE = "kr";
boolean IS_METRIC = true;


/* WiFi Settings*/
 
const char* ESP_HOST_NAME = "esp-" + ESP.getFlashChipId();
const char* WIFI_SSID     = "ACSLab2.4G";
const char* WIFI_PASSWORD = "acsl0103";

WiFiClient wifiClient;

void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  delay(500);
  connectWifi();

//  // "lon": 8.54, float lon;
//  Serial.printf("lon: %f\n", data.lon);
//  // "lat": 47.37 float lat;
//  Serial.printf("lat: %f\n", data.lat);
//  // "id": 521, weatherId weatherId;
//  Serial.printf("weatherId: %d\n", data.weatherId);
//  // "main": "Rain", String main;
//  Serial.printf("main: %s\n", data.main.c_str());
//  // "description": "shower rain", String description;
//  Serial.printf("description: %s\n", data.description.c_str());
//  // "icon": "09d" String icon; String iconMeteoCon;
//  Serial.printf("icon: %s\n", data.icon.c_str());
//  Serial.printf("iconMeteoCon: %s\n", data.iconMeteoCon.c_str());
//  // "temp": 290.56, float temp;
//  Serial.printf("temp: %f\n", data.temp);
//  // "pressure": 1013, uint16_t pressure;
//  Serial.printf("pressure: %d\n", data.pressure);
//  // "humidity": 87, uint8_t humidity;
//  Serial.printf("humidity: %d\n", data.humidity);
//  // "temp_min": 289.15, float tempMin;
//  Serial.printf("tempMin: %f\n", data.tempMin);
//  // "temp_max": 292.15 float tempMax;
//  Serial.printf("tempMax: %f\n", data.tempMax);
//  // "wind": {"speed": 1.5}, float windSpeed;
//  Serial.printf("windSpeed: %f\n", data.windSpeed);
//  // "wind": {"deg": 1.5}, float windDeg;
//  Serial.printf("windDeg: %f\n", data.windDeg);
//  // "clouds": {"all": 90}, uint8_t clouds;
//  Serial.printf("clouds: %d\n", data.clouds);
//  // "dt": 1527015000, uint64_t observationTime;
//  time_t time = data.observationTime;
//  Serial.printf("observationTime: %d, full date: %s", data.observationTime, ctime(&time));
//  // "country": "CH", String country;
//  Serial.printf("country: %s\n", data.country.c_str());
//  // "sunrise": 1526960448, uint32_t sunrise;
//  time = data.sunrise;
//  Serial.printf("sunrise: %d, full date: %s", data.sunrise, ctime(&time));
//  // "sunset": 1527015901 uint32_t sunset;
//  time = data.sunset;
//  Serial.printf("sunset: %d, full date: %s", data.sunset, ctime(&time));
//
//  // "name": "Zurich", String cityName;
//  Serial.printf("cityName: %s\n", data.cityName.c_str());
//  Serial.println();
//  Serial.println("---------------------------------------------------/\n");

}

void loop() {
  OpenWeatherMapCurrentData data;
  client.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  client.setMetric(IS_METRIC);
  client.updateCurrentById(&data, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION_ID);
  Serial.printf("%.2f %d\n",data.temp, data.humidity);

  delay(3000);
  
}
