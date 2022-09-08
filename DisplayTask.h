#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define MAX_TEXT_LEN 100

class DisplayTask {
public:
  DisplayTask(Adafruit_NeoPixel& strip);
  void displayText(uint8_t* text);
  void update();
private:
  void showChar(uint8_t c);
  Adafruit_NeoPixel& strip;
  uint32_t color;
  uint8_t text[MAX_TEXT_LEN + 1] = {0};
  int len = 0;
  unsigned long showTime = 0;
  uint8_t currentChar;

  char charmap[26] = {
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
};