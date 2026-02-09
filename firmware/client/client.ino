#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "SSID_WIFI";
const char* password = "PASSWORD_WIFI";

const char* serverUrl = "http://192.168.0.111/";

const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(serverUrl);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();

      if (payload.indexOf("ON") >= 0) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }

    http.end();
  }

  delay(1000);
}
