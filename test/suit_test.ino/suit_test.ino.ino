#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS 100

Adafruit_NeoPixel armLeft(36, 3, NEO_GRBW + NEO_KHZ800);  // 左腕
Adafruit_NeoPixel bodyLeft(27, 4, NEO_GRBW + NEO_KHZ800); // 左胴
Adafruit_NeoPixel bodyRight(27, 6, NEO_GRBW + NEO_KHZ800);// 右胴
Adafruit_NeoPixel armRight(36, 7, NEO_GRBW + NEO_KHZ800); // 右腕
Adafruit_NeoPixel legRight(21, 8, NEO_GRBW + NEO_KHZ800); // 右足
Adafruit_NeoPixel legLeft(21, 9, NEO_GRBW + NEO_KHZ800);  // 左足

byte neopix_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void setup() {
  armLeft.begin();     armLeft.setBrightness(BRIGHTNESS);     armLeft.show();
  bodyLeft.begin();    bodyLeft.setBrightness(BRIGHTNESS);    bodyLeft.show();
  bodyRight.begin();   bodyRight.setBrightness(BRIGHTNESS);   bodyRight.show();
  armRight.begin();    armRight.setBrightness(BRIGHTNESS);    armRight.show();
  legRight.begin();    legRight.setBrightness(BRIGHTNESS);    legRight.show();
  legLeft.begin();     legLeft.setBrightness(BRIGHTNESS);     legLeft.show();
}

void loop() {
  // 1. 全身に単色
  setAllColor(armLeft.Color(255, 0, 0, 0)); // 赤
  delay(1000);
  setAllColor(armLeft.Color(0, 255, 0, 0)); // 緑
  delay(1000);
  setAllColor(armLeft.Color(0, 0, 255, 0)); // 青
  delay(1000);
  setAllColor(armLeft.Color(0, 0, 0, 255)); // 白
  delay(1000);

  // 2. じわじわpulse
  pulseWhiteAll(2, 5, 2);

  // 3. rainbow
  rainbowCycleAll(10);
  delay(10000);
}

void setAllColor(uint32_t color) {
  Adafruit_NeoPixel* strips[] = { &armLeft, &bodyLeft, &bodyRight, &armRight, &legRight, &legLeft };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

void pulseWhiteAll(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) {
      uint8_t val = neopix_gamma[j];
      setAllColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    for (int j = 255; j >= 0; j -= 4) {
      uint8_t val = neopix_gamma[j];
      setAllColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    delay(100);
  }
}

void rainbowCycleAll(uint8_t wait) {
  uint16_t maxPixels = 0;
  Adafruit_NeoPixel* strips[] = { &armLeft, &bodyLeft, &bodyRight, &armRight, &legRight, &legLeft };
  for (auto strip : strips) {
    if (strip->numPixels() > maxPixels) maxPixels = strip->numPixels();
  }

  for (uint16_t j = 0; j < 256 * 5; j++) {
    for (auto strip : strips) {
      for (uint16_t i = 0; i < strip->numPixels(); i++) {
        strip->setPixelColor(i, Wheel(((i * 256 / maxPixels) + j) & 255));
      }
      strip->show();
    }
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return armLeft.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return armLeft.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  WheelPos -= 170;
  return armLeft.Color(WheelPos * 3, 255 - WheelPos * 3, 0, 0);
}