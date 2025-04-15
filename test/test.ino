#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


#define PIN 6 //Arduino6ピンから出力
#define NUM_LED 59 // 1m60LED
#define BRIGHTNESS 100 //明るさ
#define Start 0 //スタート
#define End 59 //エンド

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LED, PIN, NEO_GRBW + NEO_KHZ800);
 

//じわじわの値
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
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip1.setBrightness(BRIGHTNESS);
  strip1.begin();
  strip1.show();
}

void loop() {
  fullColor(strip1.Color(0, 0, 0, 255),2000);
  fullColor(strip1.Color(0, 155, 255,0),2000);
  fullColor(strip1.Color(255, 155, 0, 0),2000);
  fullColor(strip1.Color(0, 255, 155, 0),2000);
  fullColor(strip1.Color(155, 255, 0, 0),2000);
  fullColor(strip1.Color(0, 0, 0, 255),2000);
  rhythm1(strip1.Color(0, 0, 0, 255), strip1.Color(0, 0, 0, 1), 20, 1);
  rainbowCycle(10);
  delay(10000000);//ループ防止
}

void fullColor(uint32_t c, uint32_t wait) {
  for(uint16_t i=Start; i<=End; i++) {
    strip1.setPixelColor(i, c);
  }
    strip1.show();
    delay(wait);
}

// 任意に範囲を光らせる
void colorWipeRange(uint32_t c, uint32_t wait, uint32_t startLED1, uint32_t endLED1) {
  for(uint16_t i=startLED1; i<=endLED1; i++) {
    strip1.setPixelColor(i, c);
  }
    strip1.show();
    delay(wait);
}

//基本リズム1 高さは全て同じ
void rhythm1(uint32_t c1, uint32_t c2, uint16_t time, uint8_t wait) {
  for(uint16_t i=0; i<=time; i++){
    // 下から上
    for(uint16_t j=strip1.numPixels() - 1; j>=2; j=j-2) {
      strip1.setPixelColor(j, c1);
      strip1.setPixelColor(j-1, c1);
      strip1.show();
      delay(wait);
    }
    // 上から下。基本黒
    for(uint16_t k=1; k<strip1.numPixels(); k=k+2) {
      strip1.setPixelColor(k, c2);
      strip1.setPixelColor(k+1, c2);
      strip1.show();
      delay(wait);
    }
    delay(50);
  }
}

// 流れながら点滅(単色)
void theaterChase(uint32_t c, uint8_t wait,uint8_t cycle ) {
  for (int j=0; j<cycle; j++) {
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, c);
      }
      strip1.show();
      delay(wait);

      for (uint16_t i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, 0);
      }
    }
  }
}


//じわじわホワイト(はやめ)
void pulseWhite(uint16_t time,uint8_t wait,uint8_t speed,uint32_t c, uint32_t startLed1, uint32_t endLed1) {
   for(uint16_t k=0; k<=time-1; k++){ 
    for(int j = 0; j < 256 ; j = j+speed){
        for(uint16_t i=startLed1; i<endLed1; i++) {
            strip1.setPixelColor(i, strip1.Color(0,0,0, neopix_gamma[j] ) );
        }
          delay(wait);
          strip1.show();
        }
  
    for(int j = 255; j >= 0 ; j = j-4){
       for(uint16_t i=startLed1; i<endLed1; i++) {
            strip1.setPixelColor(i, strip1.Color(0,0,0, neopix_gamma[j] ) );
        }
          delay(wait);
          strip1.show();
        }
        delay(100);
   }
}

//じわじわホワイト(はやめ)
void pulseBlueIn(uint16_t time,uint8_t wait,uint8_t speed,uint32_t c, uint32_t startLed1, uint32_t endLed1) {
   for(uint16_t k=0; k<=time-1; k++){ 
    for(int j = 0; j < 256 ; j = j+speed){
      for(uint16_t i=startLed1; i<endLed1; i++) {
        strip1.setPixelColor(i, strip1.Color(0,0,neopix_gamma[j] ) );
      }
      delay(wait);
      strip1.show();
    }
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel(((i * 256 / strip1.numPixels()) + j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}


void rainbow(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip1.numPixels(); i++) {
      strip1.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip1.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip1.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip1.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip1.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}


uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
