#include <Adafruit_NeoPixel.h>

#define LED_PIN    3
#define NUM_LEDS   40       // LED数：リングの個数に応じて変更
#define BRIGHTNESS 100

Adafruit_NeoPixel ring(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastUpdate = 0;
int currentIndex = 0;
bool animationFinished = false;
#define LED_on_wait  68500
#define LED_disk_speed  20
#define LED_off_wait  4000
int test = 2;//1:本モード,2:開発モード

void setup() {
  ring.begin();
  ring.setBrightness(BRIGHTNESS);
  ring.show();  // 初期状態：全消灯
}

void loop() {
  

         delay(LED_on_wait);
         LEDdisk_on(NUM_LEDS,LED_disk_speed);
         delay(LED_off_wait);
         setAllColor(ring.Color(0, 0, 0));
         delay(10000000);

}

void setAllColor(uint32_t color) {
    for (uint16_t i = 0; i <NUM_LEDS; i++) {
      ring.setPixelColor(i, color);
    }
      ring.show();
  }

void LEDdisk_on(uint32_t num,uint32_t speed){
           for(uint16_t i=0; i<=num; i++) { //armLeft_LED=bodyRigh_LED　かつarmLeft＿LEDが一番個数が多いためarmLeft_LEDを使用
                 ring.setPixelColor(i, ring.Color(255, 255, 255)); // 白に点灯
                 ring.show();
            delay(speed);
               }
}
