#include <Adafruit_NeoPixel.h>

#define LED_PIN    3
#define NUM_LEDS   40       // LED数：リングの個数に応じて変更
#define BRIGHTNESS 100

Adafruit_NeoPixel ring(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastUpdate = 0;
int currentIndex = 0;
bool animationFinished = false;

void setup() {
  ring.begin();
  ring.setBrightness(BRIGHTNESS);
  ring.show();  // 初期状態：全消灯
}

void loop() {
  // アニメーションが終わっていないなら実行
  if (!animationFinished && millis() - lastUpdate >= 200) {
    ring.setPixelColor(currentIndex, ring.Color(255, 255, 255)); // 白に点灯
    ring.show();
    currentIndex++;
    lastUpdate = millis();

    if (currentIndex >= NUM_LEDS) {
      animationFinished = true;
    }
  }
}