#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3); // RX, TX for communication with ESP-01

const char* ssid = "SSID_WIFI";
const char* password = "PASSWORD_WIFI";

const int buttonPin = 7;

bool ledState = false;
bool lastButtonState = HIGH;

void sendCommand(String cmd, int delayTime = 1000) {
  esp.println(cmd);
  delay(delayTime);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  esp.begin(9600);

  delay(2000);

  sendCommand("AT");
  sendCommand("AT+CWMODE=2"); // access point + server mode
  sendCommand("AT+CIPMUX=1");
  sendCommand("AT+CIPSERVER=1,80");

  // Assign IP 192.168.0.111
  sendCommand("AT+CIPAP=\"192.168.0.111\"");
}

void loop() {

  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    ledState = !ledState;
    delay(200);
  }

  lastButtonState = buttonState;

  if (esp.available()) {
    String data = esp.readString();

    if (data.indexOf("+IPD") >= 0) {

      String response = ledState ? "ON" : "OFF";

      String http =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Connection: close\r\n\r\n" +
        response;

      int id = data.charAt(data.indexOf("+IPD,") + 5) - '0';

      String sendCmd = "AT+CIPSEND=";
      sendCmd += id;
      sendCmd += ",";
      sendCmd += http.length();

      sendCommand(sendCmd, 500);
      sendCommand(http, 500);

      String closeCmd = "AT+CIPCLOSE=" + String(id);
      sendCommand(closeCmd, 500);
    }
  }
}
