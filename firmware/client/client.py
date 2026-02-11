import network
import urequests as requests
import time
from machine import Pin

# Wi-Fi and server settings
SSID = "SSID_WIFI"
PASSWORD = "PASSWORD_WIFI"
SERVER_URL = "http://192.168.0.111/"

# Setting up a pin for an LED
led = Pin(2, Pin.OUT)

# Connecting to Wi-Fi
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(SSID, PASSWORD)

print("Connecting to Wi-Fi...")
while not wifi.isconnected():
    time.sleep(0.5)

print("Connected! IP:", wifi.ifconfig()[0])

while True:
    if wifi.isconnected():
        try:
            response = requests.get(SERVER_URL)
            payload = response.text
            response.close()
            
            if "ON" in payload:
                led.value(1)  # Turn on the LED
            else:
                led.value(0)  # Turn off the LED

        except Exception as e:
            print("Request error:", e)

    time.sleep(1)

