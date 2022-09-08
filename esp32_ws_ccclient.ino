#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>
#include <Adafruit_NeoPixel.h>

#include "wifi_credentials.h"

#define PIN 15
#define LED_COUNT 100

WebSocketsClient webSocket;

const char *ssid = _SSID;
const char *password = _PASSWORD;

unsigned long messageInterval = 5000;
bool connected = false;

char charmap[] = {
  0,   // a
  1,   // b
  2,   // c
  3,   // d
  4,   // e
  5,   // f
  6,   // g
  7,   // h
  8,   // i
  9,   // j
  10,  // k
  11,  // l
  12,  // m
  13,  // n
  14,  // o
  15,  // p
  16,  // q
  17,  // r
  18,  // s
  19,  // t
  20,  // u
  21,  // v
  22,  // w
  23,  // x
  24,  // y
  25   // z
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
uint32_t color = strip.Color(255, 255, 200);

#define DEBUG_SERIAL Serial

void showChar(uint8_t c) {
  int idx = -1;
  if (c > 'A' && c < 'Z')
    idx = c - 'A';
  if (c > 'a' && c < 'z')
    idx = c - 'a';

  strip.clear();
  strip.setPixelColor(charmap[idx], color);
  strip.show();
}

void showText(uint8_t *text) {
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      DEBUG_SERIAL.printf("[WSc] Disconnected!\n");
      connected = false;
      break;
    case WStype_CONNECTED:
      {
        DEBUG_SERIAL.printf("[WSc] Connected to url: %s\n", payload);
        connected = true;

        // send message to server when Connected
        DEBUG_SERIAL.println("[WSc] SENT: Connected");
        webSocket.sendTXT("Connected");
      }
      break;
    case WStype_TEXT:
      DEBUG_SERIAL.printf("[WSc] RECEIVED: %s\n", payload);
      showText(payload);
      break;
    case WStype_BIN:
    case WStype_PING:
    case WStype_PONG:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
  }
}

void setup() {
  DEBUG_SERIAL.begin(115200);

  DEBUG_SERIAL.println();
  DEBUG_SERIAL.println();
  DEBUG_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    DEBUG_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
    DEBUG_SERIAL.flush();
    delay(1000);
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    DEBUG_SERIAL.print(".");
  }
  DEBUG_SERIAL.print("Local IP: ");
  DEBUG_SERIAL.println(WiFi.localIP());
  // server address, port and URL
  webSocket.begin("192.168.178.44", 8080, "/ws/0001");

  // event handler
  webSocket.onEvent(webSocketEvent);
}


void loop() {
  webSocket.loop();
}