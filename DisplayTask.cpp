#include "DisplayTask.h"
#include <string.h>

DisplayTask::DisplayTask(Adafruit_NeoPixel& strip) : strip(strip)
{
  color = strip.Color(255, 255, 200);
}

void DisplayTask::displayText(uint8_t* text)
{
  memset(this->text, 0, sizeof(this->text));
  strncpy((char*) this->text, (char*) text, MAX_TEXT_LEN);
  len = strlen((char*) this->text);
  showTime = millis();
  update();
  Serial.printf("len: %i\n", len);
}

void DisplayTask::update()
{
  unsigned int diff = millis() - showTime;
  unsigned int idx = diff / 500;
  if (idx >= len || diff % 500 > 400)
  {
    strip.clear();
    strip.show();
    currentChar = 0;

    // wait one more sec (2 ticks)
    if (idx > len + 2)
    {
      // show text again
      showTime = millis();
    }
  }
  else if (currentChar != text[idx]) {
    showChar(text[idx]);
  }
}

void DisplayTask::showChar(uint8_t c)
{
  currentChar = c;

  int idx = -1;
  if (c >= 'A' && c <= 'Z')
    idx = c - 'A';
  else if (c >= 'a' && c <= 'z')
    idx = c - 'a';
  else
  {
    strip.clear();
    strip.show();
    return;
  }

  strip.clear();
  strip.setPixelColor(charmap[idx], color);
  strip.show();

  Serial.print("[show]: ");
  Serial.println(c);
}
