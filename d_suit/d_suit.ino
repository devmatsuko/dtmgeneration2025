#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS 100

Adafruit_NeoPixel armLeft(36, 3, NEO_GRBW + NEO_KHZ800);  // 左腕
Adafruit_NeoPixel bodyLeft(27, 4, NEO_GRBW + NEO_KHZ800); // 左胴
Adafruit_NeoPixel bodyRight(27, 6, NEO_GRBW + NEO_KHZ800);// 右胴
Adafruit_NeoPixel armRight(36, 7, NEO_GRBW + NEO_KHZ800); // 右腕
Adafruit_NeoPixel legRight(21, 8, NEO_GRBW + NEO_KHZ800); // 右足
Adafruit_NeoPixel legLeft(21, 9, NEO_GRBW + NEO_KHZ800);  // 左足

/** 全部位 */
Adafruit_NeoPixel* ALL_PARTS[] = { &armLeft, &armRight, &bodyLeft, &bodyRight, &legLeft, &legRight};
/** 左半身 */
Adafruit_NeoPixel* LEFT_SIDE[] = { &armLeft, &bodyLeft, &legLeft};
/** 右半身 */
Adafruit_NeoPixel* RIGHT_SIDE[] = { &armRight, &bodyRight, &legRight};
/** 腕だけ */
Adafruit_NeoPixel* ARMS[] = { &armLeft, &armRight};
/** 体だけ */
Adafruit_NeoPixel* BODIES[] = { &bodyLeft, &bodyRight};
/** 脚だけ */
Adafruit_NeoPixel* LEGS[] = { &legLeft, &legRight};

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
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

void setup() {
  armLeft.begin();     armLeft.setBrightness(BRIGHTNESS);     armLeft.show();
  bodyLeft.begin();    bodyLeft.setBrightness(BRIGHTNESS);    bodyLeft.show();
  bodyRight.begin();   bodyRight.setBrightness(BRIGHTNESS);   bodyRight.show();
  armRight.begin();    armRight.setBrightness(BRIGHTNESS);    armRight.show();
  legRight.begin();    legRight.setBrightness(BRIGHTNESS);    legRight.show();
  legLeft.begin();     legLeft.setBrightness(BRIGHTNESS);     legLeft.show();
}

void loop() {

  //03:19.340でスーツ点灯
  setAllColor(armLeft.Color(0, 0, 255, 0)); // 緑（動作確認用：開始）
  delay(7477);

  // ----- ドクターパート start -----
  // 3:26.817 幕開いて登場：ランダムキラキラ
  // 全身ランダムチカチカ（色、間隔、回数、同時に点灯させるLED数）
  blinkRandomWholeBody(armLeft.Color(0, 0, 0, 255), 40, 78, 30);

  // 3:34.830 3人で前に歩く：ゆっくりF.I.&F.O.で明滅（5回）
  // フェードイン点滅（点滅回数、変化の速さ、変化幅）←変化幅を大きくすると明滅が速くなるよ
  pulseWhiteAll(5, 1, 5);
  delay(500);

  // 二人ハケる直前のｼﾞｬﾝｼﾞｬﾝｼﾞｬﾝｼﾞｬﾝ！:前半ｼﾞｬﾝｼﾞｬﾝで左点灯右点灯、後半ｼﾞｬﾝｼﾞｬﾝ！で内から外、上から下
  // ｼﾞｬﾝ(左半身だけ点灯)
  setPartsColor(armLeft.Color(0, 0, 0, 255), LEFT_SIDE, 3);
  delay(500);
  setAllColor(armLeft.Color(0, 0, 0, 0)); // 消灯
  // ｼﾞｬﾝ（右半身だけ点灯）
  setPartsColor(armLeft.Color(0, 0, 0, 255), RIGHT_SIDE, 3);
  delay(500);
  // 全身白（一瞬）
  setAllColor(armLeft.Color(0, 0, 0, 255)); 
  
  // ｼﾞｬﾝ（下から上へ消える）
  fadeInAllPartsOrder(armLeft.Color(0, 0, 0, 0), true, 3);
  // ｼﾞｬﾝ（上から下へ点灯）
  fadeInAllPartsOrder(armLeft.Color(0, 0, 0, 255), false, 3);
  setAllColor(armLeft.Color(0, 0, 0, 255)); 
  delay(500);

  // 3:41.953ちょっとスーツ暗転
  setAllColor(armLeft.Color(0, 0, 0, 0));
  delay(1809);

  // 3:43.762ポイの光がスーツに吸い込まれる：体の中央から全身に光がチャージ
  fadeInColorAllPartsRandom(armLeft.Color(0, 0, 0, 255), ALL_PARTS, 3, 50, 3);
  setAllColor(armLeft.Color(0, 0, 0, 255)); 
  delay(1500);
  setAllColor(armLeft.Color(0, 0, 0, 0)); 

  // サビ前（ポイでカウントダウン予定のとこ）：左右で違う部位がランダム点滅（部位単位で光る）
  lightRandomPartBothSides(armLeft.Color(0, 0, 0, 255));
  delay(400);
  setAllColor(armLeft.Color(0, 0, 0, 0)); 
  lightRandomPartBothSides(armLeft.Color(0, 0, 0, 255));
  delay(400);
  setAllColor(armLeft.Color(0, 0, 0, 0)); 
  lightRandomPartBothSides(armLeft.Color(0, 0, 0, 255));
  delay(400);
  setAllColor(armLeft.Color(0, 0, 0, 0)); 
  lightRandomPartBothSides(armLeft.Color(0, 0, 0, 255));
  delay(400);
  
  setAllColor(armLeft.Color(0, 0, 0, 0)); 
  delay(1400);

  // サビ入りのテテテン！のとこ：テテテン！に合わせて全身に光が灯る（↑の「左右で違う部位がランダム点滅の応用でできないかなぁ）
  lightAllPartsRandomSequence(armLeft.Color(0, 0, 0, 255), 250);
  setAllColor(armLeft.Color(0, 0, 0, 255)); 
  
  // サビ？スウィングパート：全身白のままor8拍ずつで色変えたり何かしら変化させる？（ポイ振ってる時横向いてるし、３人の時色変えるかもだから白のままでもいい気もする）
  delay(5000);

  // スウィングパート終わりのジャンジャンジャンジャーン：ポイに合わせて半身ずつ白点灯、一瞬点灯してF.O.
  setAllColor(armLeft.Color(0, 0, 0, 0)); 
  delay(1000);
  // ｼﾞｬﾝ(左半身だけ点灯)
  setPartsColor(armLeft.Color(0, 0, 0, 255), LEFT_SIDE, 3);
  delay(500);
  setAllColor(armLeft.Color(0, 0, 0, 0)); // 消灯
  // ｼﾞｬﾝ（右半身だけ点灯）
  setPartsColor(armLeft.Color(0, 0, 0, 255), RIGHT_SIDE, 3);
  delay(500);
  // ｼﾞｬﾝ（全身白）
  setAllColor(armLeft.Color(0, 0, 0, 255)); 
  delay(500);
  // ジャーン（キラキラ）
  blinkRandomWholeBody(armLeft.Color(0, 0, 0, 255), 40, 60, 30);
  setAllColor(armLeft.Color(0, 0, 0, 0)); 
  delay(2000);
   
  // ----- ドクターパート end -----

  // ----- ポイパート終了後〜二人に光渡すまで start -----
  fadeInBrightness(5, 1);
  setAllColor(armLeft.Color(0, 0, 0, 255)); 
  delay(5000);

  // 後ろ指差す&Yk登場時のテテテン！に合わせて下から部位ごと消灯
  // 両足
  turnOffPair(&legLeft, &legRight);
  delay(200);
  // 体
  turnOffPair(&bodyLeft, &bodyRight);
  delay(200);
  // 両腕
  turnOffPair(&armLeft, &armRight);

  // 二人が舞台上がるまで暗転
  delay(5000);

  // 二人が舞台に上がり始めるあたりでF.I.
  fadeInBrightness(7, 1);
  setAllColor(armLeft.Color(0, 0, 0, 255)); 
  delay(5000);

  // 二人に光渡して以降レインボー(仮)
  rainbowCycleAll(5);
  // ----- ポイパート終了後〜二人に光渡すまで end -----

  // ----- 3人パート start -----
  // 一旦仮でエンドパート〜終わりまでレインボー
  delay(5000);
  // ----- 3人パート end -----

  setAllColor(armLeft.Color(255, 0, 0, 0)); // 赤（動作確認用：終了）
  delay(3000);

}

/**
   指定した部位を指定した色で光らせる

   @param color     色情報
   @param parts     部位（複数指定可能）
   @param partCount 部位の個数（引数で指定してあげないといけないらしい）
*/
void setPartsColor(uint32_t color, Adafruit_NeoPixel* parts[], uint8_t partCount) {
  for (uint8_t p = 0; p < partCount; p++) {
    Adafruit_NeoPixel* strip = parts[p];
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

/**
   全身のLEDを引数のcolorで点灯
   @param color 色情報
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
   白点滅

   @param time  点滅ループ回数
   @param wait  明るさの変化の速さ（小さいと速く変化、大きいとゆっくり変化）
   @param speed F.I.とF.Oにかける時間
*/
void pulseWhiteAll(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) {
      uint8_t val = neopix_gamma[j];
      setAllColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    for (int j = 255; j >= 0; j -= speed) {
      uint8_t val = neopix_gamma[j];
      setAllColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    delay(100);
  }
}

/**
   全身レインボー。引数に応じて色の変化速度が変わるよ

   @param wait  数値が低いと色の変化早くなるよ
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
   部位指定ランダムキラキラ
   指定した部位で指定したnumLEDsの数だけランダムな位置で同時に光らせる

   @param color   色
   @param part    光らせる部位
   @param wait    点滅間隔
   @param times   点滅回数
   @param numLEDs 同時に光らせるLED個数
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
   全身ランダムキラキラ
   指定したnumLEDsの数だけランダムな位置で同時に光らせる

   @param color   色
   @param wait    点滅間隔
   @param times   点滅回数
   @param numLEDs 同時に光らせるLED個数
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

void blinkRandomWholeBodyForDuration(uint32_t color, uint16_t wait, uint32_t durationMs, uint8_t numLEDs) {
  const uint8_t totalParts = 6;
  Adafruit_NeoPixel* strips[] = { &armLeft, &bodyLeft, &bodyRight, &armRight, &legRight, &legLeft };

  uint16_t partSizes[totalParts];
  uint16_t totalLEDs = 0;
  for (uint8_t i = 0; i < totalParts; i++) {
    partSizes[i] = strips[i]->numPixels();
    totalLEDs += partSizes[i];
  }

  unsigned long startTime = millis();
  unsigned long now = startTime;
  bool ledOn = false;

  while (now - startTime < durationMs) {
    // ランダム選択と描画は点灯時のみ
    if (!ledOn) {
      // 全消灯
      for (uint8_t i = 0; i < totalParts; i++) {
        strips[i]->clear();
      }

      // numLEDs個のランダムLEDを選択
      uint16_t selected[numLEDs];
      uint8_t count = 0;
      while (count < numLEDs) {
        uint16_t idx = random(totalLEDs);
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
        uint16_t idx = selected[i];
        for (uint8_t p = 0; p < totalParts; p++) {
          if (idx < partSizes[p]) {
            strips[p]->setPixelColor(idx, color);
            break;
          } else {
            idx -= partSizes[p];
          }
        }
      }

      for (uint8_t i = 0; i < totalParts; i++) strips[i]->show();
    } else {
      // 消灯表示
      for (uint8_t i = 0; i < totalParts; i++) {
        strips[i]->clear();
        strips[i]->show();
      }
    }

    ledOn = !ledOn; // 点灯⇔消灯を切り替える

    // ループ開始時刻からwait経過するまで待機
    unsigned long nextTarget = now + wait;
    while (millis() < nextTarget) {
      // ここでCPUは待機。無駄なdelay()誤差を防ぐ。
    }

    now = millis();
  }

  // 最後に全消灯
  for (uint8_t i = 0; i < totalParts; i++) {
    strips[i]->clear();
    strips[i]->show();
  }
}



uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return armLeft.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return armLeft.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  WheelPos -= 170;
  return armLeft.Color(WheelPos * 3, 255 - WheelPos * 3, 0, 0);
}

/**
  脚先/腕先から光リレー

  @param  color     色情報
  @param  isFromLeg 始点が脚か（true：脚先から、false：腕先から）
  @param  wait      リレースピード（小さいほど高速）
*/
void fadeInAllPartsOrder(uint32_t color, bool isFromLeg, uint16_t wait) {
  if(isFromLeg) {
    // 足から腕の先へ
    fadePairFromTail(&legLeft, &legRight, color, wait);
    fadePairFromTail(&bodyLeft, &bodyRight, color, wait);
    fadePairFromHead(&armLeft, &armRight, color, wait);
  } else {
    // 腕からへ脚先へ
    fadePairFromTail(&armLeft, &armRight, color, wait);
    fadePairFromHead(&bodyLeft, &bodyRight, color, wait);
    fadePairFromHead(&legLeft, &legRight, color, wait);
  }
}

/**
  左右同時に末尾からリレーする関数

  @param  left     左の部位
  @param  right    右の部位
  @param  color     色情報
  @param  wait      リレースピード（小さいほど高速）
*/
void fadePairFromTail(Adafruit_NeoPixel* left, Adafruit_NeoPixel* right, uint32_t color, uint16_t wait) {
  int n = left->numPixels();
  if (right->numPixels() < n) n = right->numPixels(); // 左右でLED数が違う場合は短い方に合わせる

  for (int i = n - 1; i >= 0; i--) {
    left->setPixelColor(i, color);
    right->setPixelColor(i, color);
    left->show();
    right->show();
    delay(wait);
  }
}

/**
  左右同時に先頭からリレーする関数

  @param  left     左の部位
  @param  right    右の部位
  @param  color     色情報
  @param  wait      リレースピード（小さいほど高速）
*/
void fadePairFromHead(Adafruit_NeoPixel* left, Adafruit_NeoPixel* right, uint32_t color, uint16_t wait) {
  int n = left->numPixels();
  if (right->numPixels() < n) n = right->numPixels(); // 左右でLED数が違う場合は短い方に合わせる

  for (int i = 0; i < n; i++) {
    left->setPixelColor(i, color);
    right->setPixelColor(i, color);
    left->show();
    right->show();
    delay(wait);
  }
}

/**
 * 全身ランダムじわじわ侵食

   @param color     色情報
   @param parts     じわじわ対象部位配列
   @param wait      じわじわ速度（小さいほど早く侵食）
   @param numAtOnce 一度に点灯させるLED数
 */
void fadeInColorAllPartsRandom(uint32_t color, Adafruit_NeoPixel* parts[], uint8_t partCount, uint16_t wait, uint8_t numAtOnce) {
  // 全LED数をカウント
  uint16_t totalLEDs = 0;
  for (uint8_t p = 0; p < partCount; p++) {
    totalLEDs += parts[p]->numPixels();
  }

  // 全LEDのインデックスと部位を対応付ける配列を作成
  struct LEDIndex {
    Adafruit_NeoPixel* strip;
    uint16_t index;
  };
  LEDIndex allLEDs[totalLEDs];

  uint16_t pos = 0;
  for (uint8_t p = 0; p < partCount; p++) {
    uint16_t n = parts[p]->numPixels();
    for (uint16_t i = 0; i < n; i++) {
      allLEDs[pos].strip = parts[p];
      allLEDs[pos].index = i;
      pos++;
    }
  }

  // フィッシャー–イェーツ法でシャッフル
  for (uint16_t i = totalLEDs - 1; i > 0; i--) {
    uint16_t j = random(i + 1);
    LEDIndex tmp = allLEDs[i];
    allLEDs[i] = allLEDs[j];
    allLEDs[j] = tmp;
  }

  // ランダム順で指定数ずつ点灯
  for (uint16_t k = 0; k < totalLEDs; k += numAtOnce) {
    for (uint8_t m = 0; m < numAtOnce && (k + m) < totalLEDs; m++) {
      allLEDs[k + m].strip->setPixelColor(allLEDs[k + m].index, color);
    }
    // まとめてshow()で同時点灯
    for (uint8_t m = 0; m < numAtOnce && (k + m) < totalLEDs; m++) {
      allLEDs[k + m].strip->show();
    }
    delay(wait);
  }
}

/**
 * 左右でランダムな部位を選んでLEDを全点灯

   @param color     色情報
 */
void lightRandomPartBothSides(uint32_t color) {
  const uint8_t LEFT_COUNT  = sizeof(LEFT_SIDE) / sizeof(LEFT_SIDE[0]);
  const uint8_t RIGHT_COUNT = sizeof(RIGHT_SIDE) / sizeof(RIGHT_SIDE[0]);

  // 左右ランダムに選択
  uint8_t leftIndex  = random(LEFT_COUNT);
  uint8_t rightIndex = random(RIGHT_COUNT);

  Adafruit_NeoPixel* leftPart  = LEFT_SIDE[leftIndex];
  Adafruit_NeoPixel* rightPart = RIGHT_SIDE[rightIndex];

  // 選ばれた部位の全LEDを点灯
  for (uint16_t i = 0; i < leftPart->numPixels(); i++) {
    leftPart->setPixelColor(i, color);
  }
  for (uint16_t i = 0; i < rightPart->numPixels(); i++) {
    rightPart->setPixelColor(i, color);
  }

  // 点灯反映
  leftPart->show();
  rightPart->show();
}

/**
 * 左右でそれぞれ違う部位がランダムな順番で部位全体点灯（最後は全身光る）

   @param color     色情報
   @param wait      点灯速度（小さいほど点灯間隔短い）
 */
void lightAllPartsRandomSequence(uint32_t color, uint16_t wait) {
  const uint8_t LEFT_COUNT  = sizeof(LEFT_SIDE) / sizeof(LEFT_SIDE[0]);
  const uint8_t RIGHT_COUNT = sizeof(RIGHT_SIDE) / sizeof(RIGHT_SIDE[0]);

  // 左右の部位を使ったフラグ配列（選ばれた部位を記録）
  bool leftUsed[LEFT_COUNT]  = { false };
  bool rightUsed[RIGHT_COUNT] = { false };

  uint8_t steps = max(LEFT_COUNT, RIGHT_COUNT); // 点灯ステップ数（左右どちらかの最大数）

  for (uint8_t s = 0; s < steps; s++) {
    // 左側の未選択部位からランダム選択
    uint8_t leftIndex;
    do {
      leftIndex = random(LEFT_COUNT);
    } while (leftUsed[leftIndex]);
    leftUsed[leftIndex] = true;
    Adafruit_NeoPixel* leftPart = LEFT_SIDE[leftIndex];

    // 右側の未選択部位からランダム選択
    uint8_t rightIndex;
    do {
      rightIndex = random(RIGHT_COUNT);
    } while (rightUsed[rightIndex]);
    rightUsed[rightIndex] = true;
    Adafruit_NeoPixel* rightPart = RIGHT_SIDE[rightIndex];

    // 選ばれた部位の全LEDを点灯（既存の点灯は維持）
    for (uint16_t i = 0; i < leftPart->numPixels(); i++) {
      leftPart->setPixelColor(i, color);
    }
    for (uint16_t i = 0; i < rightPart->numPixels(); i++) {
      rightPart->setPixelColor(i, color);
    }

    // show() で反映
    leftPart->show();
    rightPart->show();

    delay(wait); // 次のステップまでの待機
  }
}

/**
 * 白フェードイン

   @param wait  明るさの変化の速さ（小さいと速く変化、大きいとゆっくり変化）
   @param speed F.I.にかける時間
 */
void fadeInBrightness(uint8_t wait, uint8_t speed) {
  for (int j = 0; j < 256; j += speed) {
    uint8_t val = neopix_gamma[j];
    setAllColor(armLeft.Color(0, 0, 0, val));
    delay(wait);
  }
}

/**
 * フェードアウト

   @param wait  明るさの変化の速さ（小さいと速く変化、大きいとゆっくり変化）
   @param speed F.O.にかける時間
 */
void fadeOutBrightness(uint8_t wait, uint8_t speed) {
  for (int j = 255; j >= 0; j -= speed) {
    uint8_t val = neopix_gamma[j];
    setAllColor(armLeft.Color(0, 0, 0, val));
    delay(wait);
  }
}

/**
 * 左右同時に部位全体を消灯する関数

   @param left  左部位
   @param right 右部位
 */
void turnOffPair(Adafruit_NeoPixel* left, Adafruit_NeoPixel* right) {
  for (uint16_t i = 0; i < left->numPixels(); i++) {
    left->setPixelColor(i, 0);
  }
  for (uint16_t i = 0; i < right->numPixels(); i++) {
    right->setPixelColor(i, 0);
  }
  left->show();
  right->show();
}

/**
   使わないかもだけど面白い光り方する（ランダム侵食じわじわ）
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
