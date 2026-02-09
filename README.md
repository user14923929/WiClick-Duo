# WiClick Duo

A project demonstrating communication between **Arduino Uno + ESP-01** and **ESP32** for remote LED control via Wi‑Fi.

## Project Description

WiClick Duo is a simple example of network interaction between two microcontrollers:

- Arduino Uno with ESP‑01 module acts as a server  
- ESP32 works as a client  
- A button connected to Arduino controls an LED on the ESP32  
- Data transmission is performed over HTTP inside a local network

## How It Works

1. The user presses a button on the Arduino  
2. Arduino changes its internal state (ON / OFF)  
3. ESP32 periodically requests the Arduino server at:

   http://192.168.0.111

4. After receiving the response, ESP32 turns the LED on GPIO2 ON or OFF

## Hardware Setup

### Arduino Uno

- ESP‑01 connected via adapter  
- Button connected to pin D7 using INPUT_PULLUP mode

### ESP32

- Built‑in LED on GPIO2  
  or external LED with a 220Ω resistor

## Technologies Used

- ESP‑01 AT commands  
- HTTP server on Arduino  
- Wi‑Fi client on ESP32  
- Simple text-based data exchange

## Requirements

- Arduino IDE  
- WiFi and HTTPClient libraries for ESP32  
- ESP‑01 module with adapter  
- All devices connected to the same Wi‑Fi network

## Project Structure

- `./firmware/server/server.ino` — firmware for Arduino Uno / Nano / Mega 
- `./firmware/client/client.ino` — firmware for ESP32 / S2 / S3 / C2 / C6 / H2
- README.md — project documentation

## Possible Improvements

- Support for multiple buttons  
- JSON-based communication  
- Web interface for control  
- Connection loss handling  
- Support for relays and other devices

## Author

Created as an educational example of Arduino and ESP32 interaction over Wi‑Fi.

---

Happy hacking! 😄

## License

MIT License - See LICENSE file for details