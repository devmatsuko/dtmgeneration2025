#include <Adafruit_NeoPixel.h>

#define LED_PIN    3
#define NUM_LEDS   45
#define BRIGHTNESS 100

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRBW + NEO_KHZ800);

unsigned long startMillis;

bool blackedOutBeforeSequence = false;


void runOnce(bool& flag, void (*fn)()) {
  if (!flag) {
    fn();
    flag = true;
  }
}

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();

  // 実際の「0:35」からスタートしたように見せる
  startMillis = millis() - 35000;
  // 練習用は「1:06」からスタートする
  // startMillis = millis() - 65500;
}

void loop() {
  unsigned long activeTime = (millis() - startMillis);

  if (activeTime >= 86000) { // 1:26
    runOnce(blackedOutBeforeSequence, fullBlack); // 一度だけ消灯
    sequentialWhite();
  } else if (activeTime >= 78500) { // 1:18
    stripedBlink();
  } else if (activeTime >= 73000) { // 1:13
    fullWhite();
  }
}

// 全LED白
void fullWhite() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0, 255));
  }
  strip.show();
}

// 全LED消灯
void fullBlack() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

// 縞々点滅（0.5秒周期）
void stripedBlink() {
  static bool state = false;
  static unsigned long lastToggle = millis;

  if (millis() - lastToggle >= 50) {
    state = !state;
    lastToggle = millis();

    for (int i = 0; i < NUM_LEDS; i++) {
      if ((i % 2 == 0) == state) {
        strip.setPixelColor(i, strip.Color(0, 0, 0, 255));
      } else {
        strip.setPixelColor(i, 0);
      }
    }
    strip.show();
  }
}

// 流れる白点灯（100msずつ）
void sequentialWhite() {
  static int index = 0;
  static unsigned long lastUpdate = 0;

  if (index >= NUM_LEDS) return;

  if (millis() - lastUpdate > 20) {
    strip.setPixelColor(index, strip.Color(0, 0, 0, 255));
    strip.show();
    index++;
    lastUpdate = millis();
  }
}