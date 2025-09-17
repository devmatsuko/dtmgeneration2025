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
  //setAllColor(armLeft.Color(255, 0, 0, 0)); // 赤
  //delay(1000);
//  setAllColor(armLeft.Color(0, 255, 0, 0)); // 緑
//  delay(1000);
//  setAllColor(armLeft.Color(0, 0, 255, 0)); // 青
//  delay(1000);
  //setAllColor(armLeft.Color(0, 0, 0, 255)); // 白
  //delay(1000);

  // 2. じわじわpulse
  //pulseWhiteAll(1, 100, 1);

  // 3. rainbow
  //rainbowCycleAll(1000);

  //setPartColor(armLeft.Color(255, 0, 0, 0), &armRight);


  // 右腕だけランダムに5個のLEDを点滅、10ms間隔で1000回繰り返し
  blinkRandomByPart(armLeft.Color(0, 0, 0, 255), &armRight, 10, 100, 5);
  delay(1000);

  // 全身ランダムに5個のLEDを点滅、10ms間隔で1000回繰り返し
  blinkRandomWholeBody(armLeft.Color(0, 0, 0, 255), 10, 100, 10);
  
  delay(1000);
}

/**
 * 指定した部位を指定した色で光らせる
 * 
 * @param color 色情報
 * @param part  部位 
 */
void setPartColor(uint32_t color, Adafruit_NeoPixel* part) {
  Adafruit_NeoPixel* strips[] = { part };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}




/**
 * 全身のLEDを引数のcolorで点灯
 */
void setAllColor(uint32_t color) {
  Adafruit_NeoPixel* strips[] = { &armLeft, &bodyLeft, &bodyRight, &armRight, &legRight, &legLeft };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

/**
 * 白点滅
 * 
 * @param time 
 * @param wait 
 * @param speed
 */
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

/**
 * 全身レインボー。引数に応じて色の変化速度が変わるよ
 * 
 * @param wait  数値が低いと色の変化早くなるよ
 */
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










/**
 * 部位指定ランダムキラキラ
 * 指定した部位で、指定したnumLEDsの数だけランダムな位置で同時に光らせる
 * 
 * @param color   色 
 * @param part    光らせる部位
 * @param wait    点滅間隔
 * @param times   点滅回数
 * @param numLEDs 同時に光らせるLED個数
 */
void blinkRandomByPart(uint32_t color, Adafruit_NeoPixel* part, uint16_t wait, uint16_t times, uint8_t numLEDs) {
  uint16_t n = part->numPixels();

  if (numLEDs > n) numLEDs = n; // LED数が多すぎたら調整

  for (uint16_t t = 0; t < times; t++) {
    // まず全消灯
    for (uint16_t i = 0; i < n; i++) {
      part->setPixelColor(i, 0);
    }

    // numLEDs 個のランダムで異なる位置を選ぶ
    uint16_t selected[numLEDs];
    uint8_t count = 0;

    while (count < numLEDs) {
      uint16_t idx = random(n);
      bool duplicate = false;
      for (uint8_t j = 0; j < count; j++) {
        if (selected[j] == idx) {
          duplicate = true;
          break;
        }
      }
      if (!duplicate) {
        selected[count++] = idx;
      }
    }

    // 選ばれたLEDを点灯
    for (uint8_t i = 0; i < numLEDs; i++) {
      part->setPixelColor(selected[i], color);
    }

    // 点灯して少し待つ
    part->show();
    delay(wait);

    // 消灯
    for (uint8_t i = 0; i < numLEDs; i++) {
      part->setPixelColor(selected[i], 0);
    }
    part->show();
    delay(wait);
  }
}

/**
 * 全身ランダムキラキラ
 * 指定したnumLEDsの数だけランダムな位置で同時に光らせる
 * 
 * @param color   色 
 * @param wait    点滅間隔
 * @param times   点滅回数
 * @param numLEDs 同時に光らせるLED個数
 */
void blinkRandomWholeBody(uint32_t color, uint16_t wait, uint16_t times, uint8_t numLEDs) {
  const uint8_t totalParts = 6; // strips 配列の要素数
  Adafruit_NeoPixel* strips[] = { &armLeft, &bodyLeft, &bodyRight, &armRight, &legRight, &legLeft };

  // 各部位の LED 総数を計算
  uint16_t partSizes[totalParts];
  uint16_t totalLEDs = 0;
  for (uint8_t i = 0; i < totalParts; i++) {
    partSizes[i] = strips[i]->numPixels();
    totalLEDs += partSizes[i];
  }

  for (uint16_t t = 0; t < times; t++) {
    // まず全消灯
    for (uint8_t i = 0; i < totalParts; i++) {
      strips[i]->clear();
    }

    // numLEDs 個のランダムで異なるLEDを全身から選ぶ
    uint16_t selected[numLEDs];
    uint8_t count = 0;

    while (count < numLEDs) {
      uint16_t idx = random(totalLEDs); // 0～totalLEDs-1 の範囲
      bool duplicate = false;
      for (uint8_t j = 0; j < count; j++) {
        if (selected[j] == idx) {
          duplicate = true;
          break;
        }
      }
      if (!duplicate) {
        selected[count++] = idx;
      }
    }

    // 選ばれた全身LEDを点灯
    for (uint8_t i = 0; i < numLEDs; i++) {
      uint16_t idx = selected[i];
      // idx がどの部位か判定
      for (uint8_t p = 0; p < totalParts; p++) {
        if (idx < partSizes[p]) {
          strips[p]->setPixelColor(idx, color);
          break;
        } else {
          idx -= partSizes[p];
        }
      }
    }

    // 点灯
    for (uint8_t i = 0; i < totalParts; i++) {
      strips[i]->show();
    }

    delay(wait);

    // 消灯
    for (uint8_t i = 0; i < totalParts; i++) {
      strips[i]->clear();
      strips[i]->show();
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



/**
 * 使わないかもだけど面白い光り方する（ランダムじわじわ）
 */
void lightAllRandom(uint32_t color, Adafruit_NeoPixel* part, uint16_t wait) {
  uint16_t n = part->numPixels();

  // インデックス配列を作成
  uint16_t indices[n];
  for (uint16_t i = 0; i < n; i++) {
    indices[i] = i;
  }

  // フィッシャー–イェーツ法でシャッフル
  for (uint16_t i = n - 1; i > 0; i--) {
    uint16_t j = random(i + 1);
    uint16_t tmp = indices[i];
    indices[i] = indices[j];
    indices[j] = tmp;
  }

  // ランダム順で1つずつ点灯
  for (uint16_t k = 0; k < n; k++) {
    part->setPixelColor(indices[k], color);
    part->show();
    delay(wait);  // 点灯間隔
  }
}
