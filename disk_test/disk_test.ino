#include <Adafruit_NeoPixel.h>

#define LED_PIN    3        // データ出力ピン
#define NUM_LEDS   40       // LED数（リングに応じて変更）
#define BRIGHTNESS 100      // 明るさ（0〜255）

Adafruit_NeoPixel ring(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(BRIGHTNESS);
  ring.show();  // すべて消灯状態で初期化

  // RGBで白をセット（R=255, G=255, B=255）
  for (int i = 0; i < NUM_LEDS; i++) {
    ring.setPixelColor(i, ring.Color(255, 255, 255)); // 白（RGB）
  }
  ring.show();  // LEDに反映
}

void loop() {
  // 処理なし（常時白点灯）
}