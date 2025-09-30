/**
 * Komatsu LED Controller
 * 
 * 接続:
 * - 左腕: Pin 3 (36個)
 * - 左胴: Pin 4 (27個)
 * - 右胴: Pin 6 (27個)
 * - 右腕: Pin 7 (36個)
 * - 右足: Pin 8 (21個)
 * - 左足: Pin 9 (21個)
 */

#include <Adafruit_NeoPixel.h>

// ==================== LED設定 ====================
#define BRIGHTNESS 100

// LED個数
#define ARM_LEFT_LED   36
#define BODY_LEFT_LED  27
#define BODY_RIGHT_LED 27
#define ARM_RIGHT_LED  36
#define LEG_RIGHT_LED  21
#define LEG_LEFT_LED   21

// ピン番号
#define PIN_ARM_LEFT   3
#define PIN_BODY_LEFT  4
#define PIN_BODY_RIGHT 6
#define PIN_ARM_RIGHT  7
#define PIN_LEG_RIGHT  8
#define PIN_LEG_LEFT   9

// モード設定 (1:本番モード 2:開発モード)
#define MODE 1

// ==================== タイミング設定 ====================
// 下から上への点灯
#define WAVE_FOOT_WAIT        25000   // 開始待ち時間
#define WAVE_TIME             10    // 点灯間隔
#define WAVE_FOOT_WAIT2       1000   // 開始待ち時間

// 白点灯
#define WHITE_ON_WAIT         15000  // 点灯時間

// 消灯
#define WHITE_OFF_WAIT        7300   // 消灯時間

// 衣装切り替え
#define SUITS_CHANGE_WAIT     2300   // 開始待ち時間
#define SUITS_CHANGE_TIME     1      // 切替回数
#define SUITS_CHANGE_SPACE    2000   // 切替間隔

// じわじわ光る（消えない）
#define PULSE_HOLD_WAIT       0     // 開始待ち時間
#define PULSE_HOLD_WAIT2      7250  // 部位間待ち時間
#define PULSE_HOLD_TIME       1     // 点滅回数
#define PULSE_HOLD_SPACE      5     // 点滅間隔
#define PULSE_HOLD_SPEED      3     // 点灯速度

// 中央への集光　アーム
#define LED_CENTER_WAIT       1500  // 開始待ち時間
#define LED_CENTER_SPEED      20    // 点灯速度 
#define LED_CENTER_NUM_MOVE   5     // 移動個数
#define LED_CENTER_TIME       3     // 繰り返し回数
#define LED_CENTER_OFFSET     2     // 位置調整

//LED の移動
#define LEDMOVE_WAIT 18700//待ち時間
#define LED_MOVE_NUM 5    // 移動個数
#define LED_MOVE_COLOR armLeft.Color(0, 0, 0, 255)//色
#define LED_MOVE_SPEED  10 // 点灯速度 20
#define LEDMOVE_RIGHT_START 17//右腕スタート地点
#define LEDMOVE_RIGHT_END 0//右腕地点エンド地点
#define LEDMOVE_LEFT_START 0//左腕スタート地点
#define LEDMOVE_LEFT_END 17//左腕地点エンド地点

// ==================== グローバル変数 ====================
// LEDストリップオブジェクト
Adafruit_NeoPixel armLeft(ARM_LEFT_LED, PIN_ARM_LEFT, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel bodyLeft(BODY_LEFT_LED, PIN_BODY_LEFT, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel bodyRight(BODY_RIGHT_LED, PIN_BODY_RIGHT, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel armRight(ARM_RIGHT_LED, PIN_ARM_RIGHT, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel legRight(LEG_RIGHT_LED, PIN_LEG_RIGHT, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel legLeft(LEG_LEFT_LED, PIN_LEG_LEFT, NEO_GRBW + NEO_KHZ800);

// ガンマ補正テーブル（メモリ節約のためPROGMEMに格納）
const byte neopix_gamma[] PROGMEM = {
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
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};

// ==================== 初期設定 ====================
void setup() {
  // 全LEDストリップの初期化
  initializeLED(&armLeft);
  initializeLED(&bodyLeft);
  initializeLED(&bodyRight);
  initializeLED(&armRight);
  initializeLED(&legRight);
  initializeLED(&legLeft);
}

// LED初期化補助関数
void initializeLED(Adafruit_NeoPixel* strip) {
  strip->begin();
  strip->setBrightness(BRIGHTNESS);
  strip->show();
}

// ==================== メインループ ====================
void loop() {
  if (MODE == 1) {
    performMainSequence();
  } else if (MODE == 2) {
    performDebugSequence();
  }
}

// ==================== シーケンス制御 ====================
// メインシーケンス
void performMainSequence() {
      // 3. 下から上への点灯
  delay(WAVE_FOOT_WAIT);
  colorWipeRange_wave_foot(getWhiteColor(), WAVE_TIME);
  colorWipeRange_wave_bodyarm(getWhiteColor(), WAVE_TIME);
   delay(WAVE_FOOT_WAIT2);
  setAllColor(0);

  // 1. 白色で全点灯
  delay(WHITE_ON_WAIT);
  setAllColor(getWhiteColor());
 
  
  // 2. 消灯
  delay(WHITE_OFF_WAIT);
  setAllColor(0);
  
  // 3. 衣装切り替えエフェクト
  delay(SUITS_CHANGE_WAIT);
  suitsLedChange(getWhiteColor(), 0, SUITS_CHANGE_TIME, SUITS_CHANGE_SPACE);
  
  // 6. じわじわ光る（脛→もも→腰→アーム）消えない
   delay(PULSE_HOLD_WAIT2);
   pulseWhite_arm_hold(PULSE_HOLD_TIME, PULSE_HOLD_SPACE, PULSE_HOLD_SPEED);

      // 4. 中央への集光　アーム
   delay(LED_CENTER_WAIT);
   setAllColor(0);
   LEDtoCenter_arm(getWhiteColor(), LED_CENTER_SPEED, ARM_LEFT_LED, 
              LED_CENTER_NUM_MOVE, LED_CENTER_TIME, LED_CENTER_OFFSET);
   setAllColor(0);

   //LEDの移動
   delay(LEDMOVE_WAIT);
   LEDMOVE(LED_MOVE_COLOR, LED_MOVE_SPEED,LEDMOVE_RIGHT_START,LEDMOVE_RIGHT_END,LEDMOVE_LEFT_END,LEDMOVE_LEFT_START,LEDMOVE_LEFT_END,LED_MOVE_NUM) ;
    

  // 終了（無限待機）
  delay(10000000);
}

// デバッグシーケンス
void performDebugSequence() {
  // デバッグ用の処理をここに記述
 delay(LEDMOVE_WAIT);
 LEDMOVE(LED_MOVE_COLOR, LED_MOVE_SPEED,LEDMOVE_RIGHT_START,LEDMOVE_RIGHT_END,LEDMOVE_LEFT_END,LEDMOVE_LEFT_START,LEDMOVE_LEFT_END,LED_MOVE_NUM) ;
    
  delay(10000000);
}

// ==================== 色制御関数 ====================
// 白色を取得
uint32_t getWhiteColor() {
  return armLeft.Color(0, 0, 0, 255);
}

void set_body_left_Color(uint32_t color) {
  setStripColor_body(&bodyLeft, color, 0, 13);
}

void set_body_right_Color(uint32_t color) {
  setStripColor_body(&bodyRight, color, 0, 13);
}

void set_leftarm_Color(uint32_t color) {
  setStripColor_left_arm(&armLeft, color, 8, 18);
}

void set_rightleg_Color(uint32_t color) {
  setStripColor_right_leg(&legRight, color, 11, 21);
}



// 全LED一括設定
void setAllColor(uint32_t color) {
  setStripColor(&armLeft, color, 0, armLeft.numPixels());
  setStripColor(&bodyLeft, color, 0, bodyLeft.numPixels());
  setStripColor(&bodyRight, color, 0, bodyRight.numPixels());
  setStripColor(&armRight, color, 0, armRight.numPixels());
  setStripColor(&legRight, color, 0, legRight.numPixels());
  setStripColor(&legLeft, color, 0, legLeft.numPixels());
}

// ストリップ色設定
void setStripColor(Adafruit_NeoPixel* strip, uint32_t color, uint16_t start, uint16_t end) {
  for (uint16_t i = start; i < end; i++) {
    strip->setPixelColor(i, color);
  }
  strip->show();
}

void setStripColor_body(Adafruit_NeoPixel* strip, uint32_t color, uint16_t start, uint16_t end) {
  for (uint16_t i = start; i < end; i++) {
    strip->setPixelColor(i, color);
  }
  strip->show();
}

void setStripColor_left_arm(Adafruit_NeoPixel* strip, uint32_t color, uint16_t start, uint16_t end) {
  for (uint16_t i = start; i < end; i++) {
    strip->setPixelColor(i, color);
  }
  strip->show();
}

void setStripColor_right_leg(Adafruit_NeoPixel* strip, uint32_t color, uint16_t start, uint16_t end) {
  for (uint16_t i = start; i < end; i++) {
    strip->setPixelColor(i, color);
  }
  strip->show();
}

// ==================== 個別部位制御 ====================
// 左腕
void setArmLeftColor(uint32_t color) {
  setStripColor(&armLeft, color, 0, armLeft.numPixels());
}

// 右腕
void setArmRightColor(uint32_t color) {
  setStripColor(&armRight, color, 0, armRight.numPixels());
}

// 左胴
void setBodyLeftColor(uint32_t color) {
  setStripColor(&bodyLeft, color, 0, bodyLeft.numPixels());
}

// 右胴
void setBodyRightColor(uint32_t color) {
  setStripColor(&bodyRight, color, 0, bodyRight.numPixels());
}

// 右太もも
void setLegRightThigh(uint32_t color) {
  setStripColor(&legRight, color, 0, legRight.numPixels() - 10);
}

// 左太もも
void setLegLeftThigh(uint32_t color) {
  setStripColor(&legLeft, color, 0, legLeft.numPixels() - 10);
}

// 右脛
void setLegRightShin(uint32_t color) {
  setStripColor(&legRight, color, 11, legRight.numPixels());
}

// 左脛
void setLegLeftShin(uint32_t color) {
  setStripColor(&legLeft, color, 11, legLeft.numPixels());
}


void setarmLeftColor(uint32_t color) {
  setStripColor(&armLeft, color, 0, armLeft.numPixels());
}

void setarmRightColor(uint32_t color) {
  setStripColor(&armRight, color, 0, armRight.numPixels());
}

void setbodyLeftColor(uint32_t color) {
  setStripColor(&bodyLeft, color, 0, bodyLeft.numPixels());
}

void setbodyRightColor(uint32_t color) {
  setStripColor(&bodyRight, color, 0, bodyRight.numPixels());
}

void setlegRightColor(uint32_t color) {
  setStripColor(&legRight, color, 0, legRight.numPixels() - 10);
}

void setlegLeftColor(uint32_t color) {
  setStripColor(&legLeft, color, 0, legLeft.numPixels() - 10);
}

void setlegRightColor_sune(uint32_t color) {
  setStripColor(&legRight, color, 11, legRight.numPixels());
}

void setlegLeftColor_sune(uint32_t color) {
  setStripColor(&legLeft, color, 11, legLeft.numPixels());
}

// ==================== エフェクト関数 ====================
// 衣装切り替えエフェクト
void suitsLedChange(uint32_t colorOn, uint32_t colorOff, uint32_t time, uint32_t wait) {
  for (uint16_t k = 0; k < time; k++) {
    // 点灯
    setAllColor(colorOn);
    delay(wait);
    
    // 消灯
    setAllColor(colorOff);
    delay(wait);
  }
}

// ==================== パルスエフェクト（未使用だが利用可能） ====================
// 全体パルス
void pulseWhiteAll(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    // フェードイン
    for (int j = 0; j < 256; j += speed) {
      uint8_t val = pgm_read_byte(&neopix_gamma[j]);
      setAllColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    // フェードアウト
    for (int j = 255; j >= 0; j -= 4) {
      uint8_t val = pgm_read_byte(&neopix_gamma[j]);
      setAllColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    delay(100);
  }
}

// パルスエフェクト共通処理
void pulseEffect(void (*setColorFunc1)(uint32_t), void (*setColorFunc2)(uint32_t), 
                 uint16_t time, uint8_t wait, uint8_t speed, bool fadeOut) {
  for (uint16_t k = 0; k < time; k++) {
    // フェードイン
    for (int j = 0; j < 256; j += speed) {
      uint8_t val = pgm_read_byte(&neopix_gamma[j]);
      uint32_t color = armLeft.Color(0, 0, 0, val);
      setColorFunc1(color);
      if (setColorFunc2 != NULL) setColorFunc2(color);
      delay(wait);
    }
    // フェードアウト（オプション）
    if (fadeOut) {
      for (int j = 255; j >= 0; j -= 4) {
        uint8_t val = pgm_read_byte(&neopix_gamma[j]);
        uint32_t color = armLeft.Color(0, 0, 0, val);
        setColorFunc1(color);
        if (setColorFunc2 != NULL) setColorFunc2(color);
        delay(wait);
      }
    }
    delay(100);
  }
}

// 脛パルス
void pulseWhiteShinWithFade(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setLegRightShin, setLegLeftShin, time, wait, speed, true);
}

void pulseWhiteShinHold(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setLegRightShin, setLegLeftShin, time, wait, speed, false);
}

// 太ももパルス
void pulseWhiteThighWithFade(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setLegRightThigh, setLegLeftThigh, time, wait, speed, true);
}

void pulseWhiteThighHold(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setLegRightThigh, setLegLeftThigh, time, wait, speed, false);
}

// 胴体パルス
void pulseWhiteBodyWithFade(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setBodyLeftColor, setBodyRightColor, time, wait, speed, true);
}

void pulseWhiteBodyHold(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setBodyLeftColor, setBodyRightColor, time, wait, speed, false);
}

// アームパルス
void pulseWhiteArmWithFade(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setArmRightColor, setArmLeftColor, time, wait, speed, true);
}

void pulseWhiteArmHold(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setArmRightColor, setArmLeftColor, time, wait, speed, false);
}

// ==================== レインボーエフェクト ====================
void rainbowCycleAll(uint8_t wait) {
  uint16_t maxPixels = max(max(max(ARM_LEFT_LED, BODY_LEFT_LED), ARM_RIGHT_LED), LEG_RIGHT_LED);
  
  for (uint16_t j = 0; j < 256 * 5; j++) {
    setRainbowStrip(&armLeft, j, maxPixels);
    setRainbowStrip(&bodyLeft, j, maxPixels);
    setRainbowStrip(&bodyRight, j, maxPixels);
    setRainbowStrip(&armRight, j, maxPixels);
    setRainbowStrip(&legRight, j, maxPixels);
    setRainbowStrip(&legLeft, j, maxPixels);
    showAllStrips();
    delay(wait);
  }
}

void setRainbowStrip(Adafruit_NeoPixel* strip, uint16_t j, uint16_t maxPixels) {
  for (uint16_t i = 0; i < strip->numPixels(); i++) {
    strip->setPixelColor(i, Wheel(((i * 256 / maxPixels) + j) & 255));
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

// ==================== ユーティリティ関数 ====================
// 全ストリップを更新
void showAllStrips() {
  armLeft.show();
  bodyLeft.show();
  bodyRight.show();
  armRight.show();
  legRight.show();
  legLeft.show();
}

// ==================== 中央への集光 ====================
void LEDtoCenter_arm(uint32_t c, uint8_t wait, uint8_t num, uint8_t numMove, 
                 uint8_t time, uint8_t offset) {
  for (uint16_t t = 0; t < time; t++) {
    uint8_t i = 0;
    uint8_t g = 0;
    uint8_t u = LEG_RIGHT_LED;
    
    for (uint16_t k = num; k > 0; k--) {
      // // ボディー上から下
      // if (i < (BODY_LEFT_LED / 2) - numMove - offset) {
      //   bodyLeft.setPixelColor(i, c);
      //   bodyRight.setPixelColor(i, c);
      //   bodyLeft.show();
      //   bodyRight.show();
      //   i++;
      // }
      
      // // ボディー下から上
      // if (k >= (BODY_LEFT_LED / 2) - numMove - offset) {
      //   bodyLeft.setPixelColor(k, c);
      //   bodyRight.setPixelColor(k, c);
      //   bodyLeft.show();
      //   bodyRight.show();
      // }
      
      // アーム下から上
      if (k >= ARM_LEFT_LED / 2) {
        uint16_t armPos = k - (ARM_LEFT_LED + 2) / 2;
        armLeft.setPixelColor(armPos, c);
        armRight.setPixelColor(armPos, c);
        armLeft.show();
        armRight.show();
      }
      
      // // 足下から上
      // if (u <= k) {
      //   legRight.setPixelColor(u, c);
      //   legLeft.setPixelColor(u, c);
      //   legRight.show();
      //   legLeft.show();
      //   u--;
      // }
      
      // 前のLEDを消灯
      clearPreviousLEDs(k, g, numMove);
      delay(wait);
      g++;
    }
  }
}

void clearPreviousLEDs(uint16_t k, uint8_t g, uint8_t numMove) {
  bodyLeft.setPixelColor(g - numMove, 0);
  bodyRight.setPixelColor(g - numMove, 0);
  bodyLeft.setPixelColor(k + numMove, 0);
  bodyRight.setPixelColor(k + numMove, 0);
  armLeft.setPixelColor(k - numMove - (19 - numMove * 2), 0);
  armRight.setPixelColor(k - numMove - (19 - numMove * 2), 0);
  legRight.setPixelColor(k - numMove - (15 - numMove * 2), 0);
  legLeft.setPixelColor(k - numMove - (15 - numMove * 2), 0);
  
  armLeft.show();
  bodyLeft.show();
  bodyRight.show();
  armRight.show();
  legRight.show();
  legLeft.show();
}

// ==================== ウェーブ効果 ====================
void colorWipeRange_wave_foot(uint32_t c, uint32_t wait) {
  for (uint16_t i = LEG_RIGHT_LED; i > 0; i--) {
    legRight.setPixelColor(i, c);
    legLeft.setPixelColor(i, c);
    legRight.show();
    legLeft.show();
    delay(wait);
  }
}

void colorWipeRange_wave_bodyarm(uint32_t c, uint32_t wait) {
  uint32_t g = ARM_LEFT_LED / 2;
  
  for (uint16_t i = ARM_LEFT_LED; i > 0; i--) {
    // ボディー部分
    bodyLeft.setPixelColor(i, c);
    bodyRight.setPixelColor(i, c);
    bodyLeft.show();
    bodyRight.show();
    delay(wait);
    
    // アーム部分
    if (i >= ARM_LEFT_LED / 2) {
      uint16_t armPos = i - (ARM_LEFT_LED / 2 + 1);
      armLeft.setPixelColor(armPos, c);
      armRight.setPixelColor(armPos, c);
      armLeft.setPixelColor(g, c);
      armRight.setPixelColor(g, c);
      armLeft.show();
      armRight.show();
      g++;
      delay(wait);
    }
  }
}


// 脛光る（ホールド）
void pulseWhite_series_sune_hold(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setlegRightColor_sune, setlegLeftColor_sune, time, wait, speed, false);
}

// 太もも光る（ホールド）
void pulseWhite_series_momo_hold(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setlegRightColor, setlegLeftColor, time, wait, speed, false);
}

// 腰光る（ホールド）
void pulseWhite_series_body_hold(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setbodyLeftColor, setbodyRightColor, time, wait, speed, false);
}

// アーム光る（ホールド）
void pulseWhite_arm_hold(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setarmRightColor, setarmLeftColor, time, wait, speed, false);
}

// ==================== LED移動用 ====================

void LEDMOVE(uint32_t c, uint8_t wait,uint32_t right_start,uint32_t right_end,uint32_t num,uint32_t left_start,uint32_t left_end,int32_t ledmovenum) {
uint32_t komatsu_move_Led;
komatsu_move_Led=ARM_LEFT_LED;
  for(int16_t k=num; k>= -ledmovenum; k--) {//右から左
    
         armRight.setPixelColor(k, c);
         armRight.show();
         armRight.setPixelColor(k+ledmovenum, armRight.Color(0,0,0));
         armRight.show();

    delay(wait);
  }

  //ボディーの光る
   set_body_right_Color(getWhiteColor());
   delay(wait+50);
   setAllColor(0);
   set_body_left_Color(getWhiteColor());
   delay(wait+50);
   setAllColor(0);

  for(int16_t k=0; k <= num+ledmovenum; k++) {//左から右
       if (k <= num) {
        komatsu_move_Led=komatsu_move_Led-1;
        armLeft.setPixelColor(k, c);
        armLeft.setPixelColor(komatsu_move_Led, c);
        armLeft.show();
        armLeft.setPixelColor(k-ledmovenum, armLeft.Color(0,0,0));
        armLeft.setPixelColor(komatsu_move_Led+ledmovenum, armLeft.Color(0,0,0));
        armLeft.show();
         delay(wait);
       }
        

       if (k > num) { //移動LED個数を最後消灯させる
             for(int16_t i=ledmovenum; i>=0 ; i--) {
              armLeft.setPixelColor(k-i, armLeft.Color(0,0,0));
              armLeft.setPixelColor(komatsu_move_Led+i, armLeft.Color(0,0,0));
              armLeft.show();
              delay(wait);
             }
        }
   
  }
}
