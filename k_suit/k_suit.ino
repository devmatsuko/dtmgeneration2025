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
#define BRIGHTNESS 255

// LED個数
#define ARM_LEFT_LED 36
#define BODY_LEFT_LED 27
#define BODY_RIGHT_LED 27
#define ARM_RIGHT_LED 36
#define LEG_RIGHT_LED 21
#define LEG_LEFT_LED 21

// ピン番号
#define PIN_ARM_LEFT 3
#define PIN_BODY_LEFT 4
#define PIN_BODY_RIGHT 6
#define PIN_ARM_RIGHT 7
#define PIN_LEG_RIGHT 8
#define PIN_LEG_LEFT 9

// モード設定 (1:本番モード 2:開発モード)
#define MODE 1

// ==================== タイミング設定 ====================
// じわじわ光る（消える）
#define PULSE_WHITE_WAIT 7500   // 開始待ち時間
#define PULSE_WHITE_WAIT2 1500  // 部位間待ち時間
#define PULSE_WHITE_TIME 1      // 点滅回数
#define PULSE_WHITE_SPACE 5     // 点滅間隔
#define PULSE_WHITE_SPEED 1     // 点灯速度

// ランダム点灯
#define RANDOM_ALL_WAIT 1000  // 1回目の待ち時間
#define RANDOM_ALL_TIME 25    // 点灯回数
#define RANDOM_ALL_SPACE 50   // 点灯間隔
#define RANDOM_ALL_NUM 5      // 同時点灯個数

// 上から下　下から上
#define WAVE_FOOT_WAIT 500    // 開始待ち時間
#define WAVE_TIME 10          // 点灯間隔　下から上への点灯　確認用
#define WAVE_TIME2 1          // 点灯間隔　上から下への点灯　ロックマン
#define WAVE_FOOT_WAIT2 1000  // 開始待ち時間

// 白点灯 
#define WHITE_ON_WAIT 16000  // 点灯時間　上から下　ロックマン待ち時間

// 消灯
#define WHITE_OFF_WAIT 6100  // 消灯時間

// 衣装切り替え
#define SUITS_CHANGE_WAIT     2300   // 開始待ち時間 この数字はいじっちゃだめ
#define SUITS_CHANGE_TIME     1      // 切替回数
#define SUITS_CHANGE_SPACE    2000   // 切替間隔

// じわじわ光る（消えない）
#define PULSE_HOLD_WAIT 0      // 開始待ち時間
#define PULSE_HOLD_WAIT2 7100  // 部位間待ち時間
#define PULSE_HOLD_TIME 1      // 点滅回数
#define PULSE_HOLD_SPACE 5     // 点滅間隔
#define PULSE_HOLD_SPEED 3     // 点灯速度

// 中央への集光　アーム
#define LED_CENTER_WAIT 1500   // 開始待ち時間
#define LED_CENTER_SPEED 20    // 点灯速度
#define LED_CENTER_NUM_MOVE 5  // 移動個数
#define LED_CENTER_TIME 3      // 繰り返し回数
#define LED_CENTER_OFFSET 2    // 位置調整

//LED の移動
#define LEDMOVE_WAIT 18700                          //待ち時間
#define LED_MOVE_NUM 5                              // 移動個数
#define LED_MOVE_COLOR armLeft.Color(0, 0, 0, 255)  //色
#define LED_MOVE_SPEED 10                           // 点灯速度 20
#define LEDMOVE_RIGHT_START 17                      //右腕スタート地点
#define LEDMOVE_RIGHT_END 0                         //右腕地点エンド地点
#define LEDMOVE_LEFT_START 0                        //左腕スタート地点
#define LEDMOVE_LEFT_END 17                         //左腕地点エンド地点

//飛行パート　
  // 小松さん白パート（時間調整はしてないです。エフェクトを並べただけ）
  // 2枚分裂で半身ずつ上下に光が移動（終端で消える）1:40
#define DISK_MOVE_WAIT0 4000                         //待ち時間

#define DISK_MOVE_SPACE1 15                         // 点灯間隔
#define DISK_MOVE_WAIT 10000                         //待ち時間

 // 右手1枚出現時に右足点灯 1:44
#define DISK_MOVE_WAIT2 1000                        // 次の光の待ち時間

  // 1から5枚にするところで下から光が充填されていく1:52
#define DISK_MOVE_SPACE2 50                          // 点灯間隔 // 点灯間隔
#define DISK_MOVE_WAIT3 2000                        // 次の光の待ち時間

  // アピール！きらきら〜☆1:54
#define DISK_MOVE_NUM 50                          // 点灯個数
#define DISK_MOVE_FLASH 100                        // 光
#define DISK_MOVE_SPACE3 40                        // 点灯間隔

//全身ピンク
#define DISK_MOVE_PINK_WAIT 31300//ピンクディスクの移動

//小松マルチカラーパート
#define DISK_MOVE_BLUE_WAIT 1900//緑点灯待ち
#define DISK_MOVE_GREEN_WAIT 1800//緑点灯待ち
#define DISK_MOVE_YELLOW_WAIT 1800//黄色点灯待ち
#define DISK_MOVE_MULTICOLOR_WAIT 4000//マルチカラー点灯待ち
#define DISK_MOVE_MULTICOLOR_WAIT2 3000//マルチカラー消灯待ち


// 8. パチ屋
#define DARK_DANCE_WAIT    4800  // 開始待ち時間
#define DARK_DANCE_SPEED   20    // 点灯速度
#define DARK_DANCE_TIME    37    // 繰り返し回数

// 衣装切り替え高速点滅
#define DARK_DANCE_WAIT2     0  // 開始待ち時間
#define DARK_DANCE_TIME2     22     // 切替回数
#define DARK_DANCE_SPACE2    35  // 切替間隔

// //白光固定
// #define DARK_DANCE_WAIT3     4000  // 開始待ち時間

//カイリキーラストカラー
#define KAIRIKI_COLOR_WAIT     18900  // 開始待ち時間 点灯
#define KAIRIKI_COLOR_WAIT2     4250  // 開始待ち時間 消灯

//カラーパート
#define LED_PART_PINK_COLOR armLeft.Color(255, 0, 55, 0)//ピンク色
#define LED_PART_WHITE_COLOR armLeft.Color(0, 0, 0, 255)//白色
#define LED_PART_BLUE_COLOR armLeft.Color(0, 155, 255, 0)//水色
#define LED_PART_GREEN_COLOR armLeft.Color(0, 255, 50, 0)//緑
#define LED_PART_YELLOW_COLOR armLeft.Color(255, 255, 0, 0)//黄色
#define LED_WHITE_COLOR armLeft.Color(0, 0, 0, 255)//白色


//ドクター惨状
#define PULSE_HOLD_WAIT_DOCTOR       0     // 点灯待ち時間
#define PULSE_WHITE_TIME_DOCTOR      2     // 点滅回数
#define PULSE_WHITE_SPACE_DOCTOR     15     // 点滅間隔
#define PULSE_WHITE_SPEED_DOCTOR     3     // 点灯 カウント数
#define PULSE_HOLD_WAIT_DOCTOR2      550     // 点灯待ち時間
#define PULSE_HOLD_WAIT_DOCTOR_OFF   52700     // 点灯待ち時間 きらきら
#define PULSE_WHITE_SPACE_DOCTOR_OFF     60     // 点滅間隔
#define PULSE_WHITE_SPEED_DOCTOR_OFF     1     // 点灯 カウント数
#define WAVE_TIME_DOCTOR             1    // 点灯間隔　下から上の消灯
#define WAVE_NUM_DOCTOR            3    // 点灯間隔
#define WAVE_WAIT_DOCOR2     500 // 2回目の待ち時間  

  // ポイ後の諭吉、小松の惨状
#define YUKICHI_KOMATSU_APP_NUM 50                          // 点灯個数
#define YUKICHI_KOMATSU_APP_FLASH 129                        // 光
#define YUKICHI_KOMATSU_APP_SPACE3 40                        // 点灯間隔
#define YUKICHI_KOMATSU_APP_WAIT  0                       //白固定までも待ち時間
#define YUKICHI_KOMATSU_APP_WAIT0  8100                       //消灯までも待ち時間
#define YUKICHI_KOMATSU_APP_WAIT2  8200                       //水色点灯までも待ち時間
#define YUKICHI_KOMATSU_APP_WAIT3  6900                       //水色消灯までも待ち時間

#define YUKICHI_KOMATSU_APP_WAIT4  5485                       //レインボーまでも待
#define RANDOM_ALL_WAIT3 2000 //この葉前のランダム点灯ち時間

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
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
  2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
  5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
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
  // 1. じわじわ光る（脛→もも→腰→アーム）消える
  delay(PULSE_WHITE_WAIT);
  pulseWhite_series_sune(PULSE_WHITE_TIME, PULSE_WHITE_SPACE, PULSE_WHITE_SPEED);
  delay(PULSE_WHITE_WAIT2);
  pulseWhite_series_momo(PULSE_WHITE_TIME, PULSE_WHITE_SPACE, PULSE_WHITE_SPEED);
  delay(PULSE_WHITE_WAIT2);
  pulseWhite_series_body(PULSE_WHITE_TIME, PULSE_WHITE_SPACE, PULSE_WHITE_SPEED);
  delay(PULSE_WHITE_WAIT2);
  pulseWhite_arm(PULSE_WHITE_TIME, PULSE_WHITE_SPACE, PULSE_WHITE_SPEED);

  // 2. ランダム点灯（1回目）
  delay(RANDOM_ALL_WAIT);
  random_all(getWhiteColor(), RANDOM_ALL_TIME, RANDOM_ALL_SPACE, RANDOM_ALL_NUM);

  // 3. 下から上への点灯
  delay(WAVE_FOOT_WAIT);
  colorWipeRange_wave_foot(getWhiteColor(), WAVE_TIME);
  colorWipeRange_wave_bodyarm(getWhiteColor(), WAVE_TIME);
  delay(WAVE_FOOT_WAIT2);
  setAllColor(0);

  // 1. 上から下の点灯出現 六万
  delay(WHITE_ON_WAIT);
  colorWipeRange_wave_bodyarm2(getWhiteColor(), WAVE_TIME2);
  colorWipeRange_wave_foot2(getWhiteColor(), WAVE_TIME2);

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
  LEDMOVE(LED_MOVE_COLOR, LED_MOVE_SPEED, LEDMOVE_RIGHT_START, LEDMOVE_RIGHT_END, LEDMOVE_LEFT_END, LEDMOVE_LEFT_START, LEDMOVE_LEFT_END, LED_MOVE_NUM);

 //小松飛行パート
  delay(DISK_MOVE_WAIT0);

  // 小松さん白パート（時間調整はしてないです。エフェクトを並べただけ）
  // 2枚分裂で半身ずつ上下に光が移動（終端で消える）
  relayFromBodyCenterBoth(getWhiteColor(), DISK_MOVE_SPACE1); // 第二引数小さいほど早くなる DISK_MOVE_SPACE1 15
  delay(DISK_MOVE_WAIT);//DISK_MOVE_WAIT 2000

  // // 右手1枚出現時に右足点灯
  // setLegRightThigh(getWhiteColor());
  // delay(DISK_MOVE_WAIT2);//DISK_MOVE_WAIT2 1000
  // setAllColor(0);

  // // 1から5枚にするところで下から光が充填されていく
  // fillFromLegsToArms(getWhiteColor(), DISK_MOVE_SPACE2);//DISK_MOVE_SPACE2 50
  // delay(DISK_MOVE_WAIT3);//DISK_MOVE_WAIT3 2000
  // setAllColor(0);

  // アピール！きらきら〜☆
  sparkleFullBody(DISK_MOVE_NUM, getWhiteColor(), DISK_MOVE_FLASH, DISK_MOVE_SPACE3);  // 全身から<第一引数>個ランダムに選んで光らせる、を<第三引数>回やる）

    delay(DISK_MOVE_PINK_WAIT);
    setAllColor(LED_PART_PINK_COLOR);
    delay(DISK_MOVE_BLUE_WAIT);
    setAllColor(LED_PART_BLUE_COLOR);
    delay(DISK_MOVE_GREEN_WAIT);
    setAllColor(LED_PART_GREEN_COLOR);
    delay(DISK_MOVE_YELLOW_WAIT);
    setAllColor(LED_PART_YELLOW_COLOR);
    delay(DISK_MOVE_MULTICOLOR_WAIT);
    set_armleft_Color(LED_PART_YELLOW_COLOR);//水色
    set_armright_Color(LED_PART_GREEN_COLOR);//緑
    set_bodyLeft_Color(LED_PART_PINK_COLOR);//ピンク
    set_bodyRight_Color(LED_PART_BLUE_COLOR);//水色
    set_legRight_Color(LED_PART_BLUE_COLOR);//緑
    set_legLeft_Color(LED_PART_PINK_COLOR);//ピンク
    delay(DISK_MOVE_MULTICOLOR_WAIT2);
    setAllColor(0);

    // 8. パチ屋
    delay(DARK_DANCE_WAIT);
    theaterChase(getWhiteColor(), DARK_DANCE_SPEED, DARK_DANCE_TIME);

    // 5. 衣装切り替え
   delay(DARK_DANCE_WAIT2);
  //  suitsLedChange(getWhiteColor(), 0, DARK_DANCE_TIME2, DARK_DANCE_SPACE2);
  //  setAllColor(LED_PART_WHITE_COLOR);   
  // delay(DARK_DANCE_WAIT3);
  //  setAllColor(0);

   delay(KAIRIKI_COLOR_WAIT); 
   set_armleft_Color(LED_PART_BLUE_COLOR);//水色
   set_armright_Color(LED_PART_GREEN_COLOR);//緑
   //  set_bodyLeft_Color(LED_PART_YELLOW_COLOR);//黄色
   //  set_bodyRight_Color(LED_PART_PINK_COLOR);//ピンク
   //  set_legRight_Color(LED_PART_GREEN_COLOR);//緑
   //  set_legLeft_Color(LED_PART_BLUE_COLOR);//青色
   delay(KAIRIKI_COLOR_WAIT2); 
   setAllColor(0);

   //２曲目ドクター登場
   delay(PULSE_HOLD_WAIT_DOCTOR);
 pulseWhiteAll(PULSE_WHITE_TIME_DOCTOR, PULSE_WHITE_SPACE_DOCTOR, PULSE_WHITE_SPEED_DOCTOR); 
   delay(PULSE_HOLD_WAIT_DOCTOR2);//無音のところ
   pulseWhiteAll(PULSE_WHITE_TIME_DOCTOR, PULSE_WHITE_SPACE_DOCTOR, PULSE_WHITE_SPEED_DOCTOR); 
   setAllColor(LED_WHITE_COLOR);     
   pulseWhiteAll_off(1, PULSE_WHITE_SPACE_DOCTOR_OFF, PULSE_WHITE_SPEED_DOCTOR_OFF); 
   delay(PULSE_HOLD_WAIT_DOCTOR_OFF);//48秒徐々にフェードアウト～次の登場まで
   sparkleFullBody(YUKICHI_KOMATSU_APP_NUM, getWhiteColor(), YUKICHI_KOMATSU_APP_FLASH, YUKICHI_KOMATSU_APP_SPACE3);  // きらきら　全身から<第一引数>個ランダムに選んで光らせる、を<第三引数>回やる）
   delay(YUKICHI_KOMATSU_APP_WAIT);//7秒白固定待ち時間
   setAllColor(LED_WHITE_COLOR); 
   delay(YUKICHI_KOMATSU_APP_WAIT0);//消灯
   setAllColor(0); 
   delay(YUKICHI_KOMATSU_APP_WAIT2);//7秒諭吉ピンク点灯待ち
   setAllColor(LED_PART_BLUE_COLOR);// 
   delay(YUKICHI_KOMATSU_APP_WAIT3);//7諭吉ピンク消灯待ち
   setAllColor(0);//
   delay(YUKICHI_KOMATSU_APP_WAIT4);//15諭吉レインボー待ち
   random_all(LED_PART_BLUE_COLOR, RANDOM_ALL_TIME, RANDOM_ALL_SPACE, RANDOM_ALL_NUM);
   delay(RANDOM_ALL_WAIT3);
   rainbowCycleAll(10);



  // 終了（無限待機）
  delay(10000000);
}

// デバッグシーケンス
void performDebugSequence() {

   pulseWhiteAll(PULSE_WHITE_TIME_DOCTOR, PULSE_WHITE_SPACE_DOCTOR, PULSE_WHITE_SPEED_DOCTOR); 
   delay(PULSE_HOLD_WAIT_DOCTOR2);//無音のところ
   pulseWhiteAll(PULSE_WHITE_TIME_DOCTOR, PULSE_WHITE_SPACE_DOCTOR, PULSE_WHITE_SPEED_DOCTOR); 
   setAllColor(LED_WHITE_COLOR);     
   pulseWhiteAll_off(1, PULSE_WHITE_SPACE_DOCTOR_OFF, PULSE_WHITE_SPEED_DOCTOR_OFF); 
   delay(PULSE_HOLD_WAIT_DOCTOR_OFF);//48秒徐々にフェードアウト～次の登場まで
   sparkleFullBody(YUKICHI_KOMATSU_APP_NUM, getWhiteColor(), YUKICHI_KOMATSU_APP_FLASH, YUKICHI_KOMATSU_APP_SPACE3);  // きらきら　全身から<第一引数>個ランダムに選んで光らせる、を<第三引数>回やる）
   delay(YUKICHI_KOMATSU_APP_WAIT);//7秒白固定待ち時間
   setAllColor(LED_WHITE_COLOR); 
   delay(YUKICHI_KOMATSU_APP_WAIT0);//消灯
   setAllColor(0); 
   delay(YUKICHI_KOMATSU_APP_WAIT2);//7秒諭吉ピンク点灯待ち
   setAllColor(LED_PART_BLUE_COLOR);// 
   delay(YUKICHI_KOMATSU_APP_WAIT3);//7諭吉ピンク消灯待ち
   setAllColor(0);//
   delay(YUKICHI_KOMATSU_APP_WAIT4);//15諭吉レインボー待ち
   random_all(getWhiteColor(), RANDOM_ALL_TIME, RANDOM_ALL_SPACE, RANDOM_ALL_NUM);
   delay(RANDOM_ALL_WAIT3);
   rainbowCycleAll(10);


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


// 脛（すね）光る
void pulseWhite_series_sune(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setlegRightColor_sune, setlegLeftColor_sune, time, wait, speed, true);
}

// 太もも光る
void pulseWhite_series_momo(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setlegRightColor, setlegLeftColor, time, wait, speed, true);
}

// 腰光る
void pulseWhite_series_body(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setbodyLeftColor, setbodyRightColor, time, wait, speed, true);
}

// アーム光る
void pulseWhite_arm(uint16_t time, uint8_t wait, uint8_t speed) {
  pulseEffect(setarmRightColor, setarmLeftColor, time, wait, speed, true);
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

// ==================== ランダム点灯 ====================
void random_all(uint32_t c, uint16_t time, uint8_t wait, uint8_t num) {
  for (uint16_t t = 0; t <= time; t++) {
    // ランダム位置を生成して点灯
    uint32_t positions[6];
    positions[0] = random(0, ARM_LEFT_LED);
    positions[1] = random(0, BODY_LEFT_LED);
    positions[2] = random(0, BODY_RIGHT_LED);
    positions[3] = random(0, ARM_RIGHT_LED);
    positions[4] = random(0, LEG_RIGHT_LED);
    positions[5] = random(0, LEG_LEFT_LED);

    // 点灯
    setRandomPixels(&armLeft, positions[0], num, c);
    setRandomPixels(&bodyLeft, positions[1], num, c);
    setRandomPixels(&bodyRight, positions[2], num, c);
    setRandomPixels(&armRight, positions[3], num, c);
    setRandomPixels(&legRight, positions[4], num, c);
    setRandomPixels(&legLeft, positions[5], num, c);

    delay(wait);

    // 消灯
    setRandomPixels(&armLeft, positions[0], num, 0);
    setRandomPixels(&bodyLeft, positions[1], num, 0);
    setRandomPixels(&bodyRight, positions[2], num, 0);
    setRandomPixels(&armRight, positions[3], num, 0);
    setRandomPixels(&legRight, positions[4], num, 0);
    setRandomPixels(&legLeft, positions[5], num, 0);
  }
}
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

void setRandomPixels(Adafruit_NeoPixel* strip, uint32_t pos, uint8_t num, uint32_t color) {
  uint16_t maxPos = strip->numPixels();
  for (uint16_t i = pos; i < pos + num && i < maxPos; i++) {
    strip->setPixelColor(i, color);
  }
  strip->show();
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
void pulseEffect(void (*setColorFunc1)(uint32_t), void (*setColorFunc2)(uint32_t), uint16_t time, uint8_t wait, uint8_t speed, bool fadeOut) {
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



// ==================== LED移動用 ====================

void LEDMOVE(uint32_t c, uint8_t wait, uint32_t right_start, uint32_t right_end, uint32_t num, uint32_t left_start, uint32_t left_end, int32_t ledmovenum) {
  uint32_t komatsu_move_Led;
  komatsu_move_Led = ARM_LEFT_LED;
  for (int16_t k = num; k >= -ledmovenum; k--) {  //右から左

    armRight.setPixelColor(k, c);
    armRight.show();
    armRight.setPixelColor(k + ledmovenum, armRight.Color(0, 0, 0));
    armRight.show();

    delay(wait);
  }

  //ボディーの光る
  set_body_right_Color(getWhiteColor());
  delay(wait + 50);
  setAllColor(0);
  set_body_left_Color(getWhiteColor());
  delay(wait + 50);
  setAllColor(0);

  for (int16_t k = 0; k <= num + ledmovenum; k++) {  //左から右
    if (k <= num) {
      komatsu_move_Led = komatsu_move_Led - 1;
      armLeft.setPixelColor(k, c);
      armLeft.setPixelColor(komatsu_move_Led, c);
      armLeft.show();
      armLeft.setPixelColor(k - ledmovenum, armLeft.Color(0, 0, 0));
      armLeft.setPixelColor(komatsu_move_Led + ledmovenum, armLeft.Color(0, 0, 0));
      armLeft.show();
      delay(wait);
    }


    if (k > num) {  //移動LED個数を最後消灯させる
      for (int16_t i = ledmovenum; i >= 0; i--) {
        armLeft.setPixelColor(k - i, armLeft.Color(0, 0, 0));
        armLeft.setPixelColor(komatsu_move_Led + i, armLeft.Color(0, 0, 0));
        armLeft.show();
        delay(wait);
      }
    }
  }
}

// ==================== ウェーブ効果 上から下点灯　小松用====================
void colorWipeRange_wave_foot2(uint32_t c, uint32_t wait) {
  for (uint16_t i = 0; i < LEG_RIGHT_LED; i++) {
    legRight.setPixelColor(i, c);
    legLeft.setPixelColor(i, c);
    legRight.show();
    legLeft.show();
    delay(wait);
  }
}

void colorWipeRange_wave_bodyarm2(uint32_t c, uint32_t wait) {
  uint32_t g = ARM_LEFT_LED / 2;

  for (uint16_t i = 0; i < ARM_LEFT_LED; i++) {
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

// ---------- 白パート用関数 ----------
// relayFromBodyCenterBoth()のヘルパー関数：指定位置に「5個の光の塊」を出す
void drawSegment(Adafruit_NeoPixel* strip, int pos, int len, uint32_t color) {
  strip->clear();
  for (int i = 0; i < len; i++) {
    int idx = pos + i;
    if (idx >= 0 && idx < strip->numPixels()) {
      strip->setPixelColor(idx, color);
    }
  }
  strip->show();
}

/**
  2枚出現時のエフェクト（体の中央から腕先、足先に光がリレー）

  color   色情報
  wait    小さい数値ほどリレースピード速くなる
*/
void relayFromBodyCenterBoth(uint32_t color, uint16_t wait) {

  int numBodyL = bodyLeft.numPixels();
  int numBodyR = bodyRight.numPixels();
  int numArmL = armLeft.numPixels();
  int numArmR = armRight.numPixels();
  int numLegL = legLeft.numPixels();
  int numLegR = legRight.numPixels();

  int stepSize = 5;
  int centerL = numBodyL / 2;
  int centerR = numBodyR / 2;

  // 上方向に必要な最大距離（body上半分 + arm）
  int upSteps = (centerL + numArmL);
  // 下方向に必要な最大距離（body下半分 + leg）
  int downSteps = ((numBodyL - centerL) + numLegL);

  int totalSteps = max(upSteps, downSteps) + stepSize;

  // --- 上下同時にリレー ---
  for (int t = 0; t < totalSteps; t++) {
    // 全クリア
    bodyLeft.clear(); bodyRight.clear();
    armLeft.clear(); armRight.clear();
    legLeft.clear(); legRight.clear();

    // ===== 上方向（中央 → arm末端）=====
    int upOffset = t;
    int bodyUpPos = centerL - upOffset;  // body中央→先端へ
    drawSegment(&bodyLeft, bodyUpPos, stepSize, color);
    drawSegment(&bodyRight, centerR - upOffset, stepSize, color);

    int armPos = upOffset - centerL;     // armへ移行
    if (armPos >= 0) {
      drawSegment(&armLeft, armPos, stepSize, color);
      drawSegment(&armRight, armPos, stepSize, color);
    }

    // ===== 下方向（中央 → leg末端）=====
    int downOffset = t;
    int bodyDownPos = centerL + downOffset;  // body中央→末端へ
    drawSegment(&bodyLeft, bodyDownPos, stepSize, color);
    drawSegment(&bodyRight, centerR + downOffset, stepSize, color);

    int legPos = downOffset - (numBodyL - centerL);
    if (legPos >= 0) {
      drawSegment(&legLeft, legPos, stepSize, color);
      drawSegment(&legRight, legPos, stepSize, color);
    }

    // --- すべて同時に更新 ---
    bodyLeft.show(); bodyRight.show();
    armLeft.show(); armRight.show();
    legLeft.show(); legRight.show();

    delay(wait);
  }
}

// --- fillFromLegsToArms()のヘルパー関数：末端から充填する関数 ---
void fillFromEnd(Adafruit_NeoPixel* strip, int litLength, uint32_t color) {
  strip->clear();
  int n = strip->numPixels();
  for (int i = 0; i < litLength && i < n; i++) {
    int idx = n - 1 - i;  // 末端から点灯
    strip->setPixelColor(idx, color);
  }
  strip->show();
}

// --- fillFromLegsToArms()のヘルパー関数：先端から充填する関数（腕専用）---
void fillFromStart(Adafruit_NeoPixel* strip, int litLength, uint32_t color) {
  strip->clear();
  int n = strip->numPixels();
  for (int i = 0; i < litLength && i < n; i++) {
    int idx = i;  // 先端から点灯
    strip->setPixelColor(idx, color);
  }
  strip->show();
}

/**
  1→5枚時のエフェクト。足から上に向かって光が充填される

  color   色情報
  wait    小さい数値ほどリレースピード速くなる
*/
void fillFromLegsToArms(uint32_t color, uint16_t wait) {

  int numLegL = legLeft.numPixels();
  int numLegR = legRight.numPixels();
  int numBodyL = bodyLeft.numPixels();
  int numBodyR = bodyRight.numPixels();
  int numArmL = armLeft.numPixels();
  int numArmR = armRight.numPixels();

  // 各パーツごとの全LED数
  int totalLen = numLegL + numBodyL + numArmL;

  // 充填進行
  for (int step = 0; step <= totalLen; step++) {
    // --- 左右同時に更新 ---
    legLeft.clear(); legRight.clear();
    bodyLeft.clear(); bodyRight.clear();
    armLeft.clear(); armRight.clear();

    if (step <= numLegL) {
      // 足のみ点灯中
      fillFromEnd(&legLeft, step, color);
      fillFromEnd(&legRight, step, color);
    } else if (step <= numLegL + numBodyL) {
      // 足は全点灯、体の下から充填
      fillFromEnd(&legLeft, numLegL, color);
      fillFromEnd(&legRight, numLegR, color);

      int bodyFill = step - numLegL;
      fillFromEnd(&bodyLeft, bodyFill, color);
      fillFromEnd(&bodyRight, bodyFill, color);
    } else {
      // 足・体は全点灯、腕の先端から充填（ここが変更点）
      fillFromEnd(&legLeft, numLegL, color);
      fillFromEnd(&legRight, numLegR, color);
      fillFromEnd(&bodyLeft, numBodyL, color);
      fillFromEnd(&bodyRight, numBodyR, color);

      int armFill = step - (numLegL + numBodyL);
      fillFromStart(&armLeft, armFill, color);  // ← 先端から点灯
      fillFromStart(&armRight, armFill, color); // ← 先端から点灯
    }

    delay(wait);
  }
}

/**
  5枚アピールキラキラ！
  やってることは全身からランダムな個数LEDを選んで点灯！の繰り返し

  numLEDs   1度に光らせるLED個数
  color     色情報
  flashes   光らせる回数
  wait      光らせる感覚（小さい数値ほどキラキラが速くなる）
*/
void sparkleFullBody(int numLEDs, uint32_t color, int flashes, uint16_t wait) {

  Adafruit_NeoPixel* allParts[] = { &armLeft, &armRight, &bodyLeft, &bodyRight, &legLeft, &legRight };

  // LED総数をカウント
  int totalLEDs = 0;
  int offsets[6]; // 各パーツの開始インデックス
  for (int i = 0; i < 6; i++) {
    offsets[i] = totalLEDs;
    totalLEDs += allParts[i]->numPixels();
  }

  // ランダム点灯
  for (int f = 0; f < flashes; f++) {
    // まず全クリア
    for (int i = 0; i < 6; i++) allParts[i]->clear();

    for (int n = 0; n < numLEDs; n++) {
      int r = random(totalLEDs); // 0〜totalLEDs-1
      // どのパーツに属するか判定
      for (int p = 0; p < 6; p++) {
        int start = offsets[p];
        int end = start + allParts[p]->numPixels();
        if (r >= start && r < end) {
          int idx = r - start;
          allParts[p]->setPixelColor(idx, color);
          break;
        }
      }
    }

    // 全パーツ更新
    for (int i = 0; i < 6; i++) allParts[i]->show();
    delay(wait);
  }

  // 最後に全消灯
  for (int i = 0; i < 6; i++) {
    allParts[i]->clear();
    allParts[i]->show();
  }
}

// ==================== パチ屋 ====================
void theaterChase(uint32_t c, uint8_t wait, uint8_t cycle) {
  for (int j = 0; j < cycle; j++) {
    for (int q = 0; q < 3; q++) {
      // 3つおきにLEDを点灯
      for (uint16_t i = 0; i < ARM_RIGHT_LED; i = i + 3) {
        setTheaterPixel(&armLeft, i + q, c);
        setTheaterPixel(&bodyLeft, i + q, c);
        setTheaterPixel(&bodyRight, i + q, c);
        setTheaterPixel(&armRight, i + q, c);
        setTheaterPixel(&legRight, i + q, c);
        setTheaterPixel(&legLeft, i + q, c);
      }
      showAllStrips();
      delay(wait);
      
      // 消灯
      for (uint16_t i = 0; i < ARM_RIGHT_LED; i = i + 3) {
        setTheaterPixel(&armLeft, i + q, 0);
        setTheaterPixel(&bodyLeft, i + q, 0);
        setTheaterPixel(&bodyRight, i + q, 0);
        setTheaterPixel(&armRight, i + q, 0);
        setTheaterPixel(&legRight, i + q, 0);
        setTheaterPixel(&legLeft, i + q, 0);
      }
      showAllStrips();
    }
  }
}


void set_armleft_Color(uint32_t color) {
  setStripColor(&armLeft, color, 0, armLeft.numPixels());
}

void set_armright_Color(uint32_t color) {
  setStripColor(&armRight, color, 0, armRight.numPixels());
}
void set_bodyLeft_Color(uint32_t color) {
   setStripColor(&bodyLeft, color, 0, bodyLeft.numPixels());
}
void set_bodyRight_Color(uint32_t color) {
  setStripColor(&bodyRight, color, 0, bodyRight.numPixels());
}
void set_legRight_Color(uint32_t color) {
    setStripColor(&legRight, color, 0, legRight.numPixels());
}
void set_legLeft_Color(uint32_t color) {
     setStripColor(&legLeft, color, 0, legLeft.numPixels());
}

void setTheaterPixel(Adafruit_NeoPixel* strip, uint16_t pos, uint32_t color) {
  if (pos < strip->numPixels()) {
    strip->setPixelColor(pos, color);
  }
}

// ==================== ウェーブ効果 下から上　消灯====================
void colorWipeRange_wave_foot_off(uint32_t wait,uint32_t off_num) {
  for (int16_t i = LEG_RIGHT_LED; i >= 0; i--) {
    uint32_t c;
    c=armLeft.Color(0, 0, 0, 0);
    legRight.setPixelColor(i, c);
    legLeft.setPixelColor(i, c);
    legRight.show();
    legLeft.show();
    delay(wait);
  }
}

void colorWipeRange_wave_bodyarm_off(uint32_t wait,uint32_t off_num) {
  uint32_t g = ARM_LEFT_LED / 2;
  uint32_t c;
  c=armLeft.Color(0, 0, 0, 0);
  for (int16_t i = ARM_LEFT_LED; i >= 0; i--) {
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

// ==================== パルス効果 ====================
void pulseWhiteAll_off(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {

    for (int j = 255; j >= 0; j -= 4) {
            uint8_t val = pgm_read_byte(&neopix_gamma[j]);
      setAllColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    delay(100);
  }
}

