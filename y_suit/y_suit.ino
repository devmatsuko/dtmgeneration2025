#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS 100
#define armLeft_LED 36
#define bodyLeft_LED 27
#define bodyRight_LED 27
#define armRight_LED 36
#define legRight_LED 21
#define legLeft_LED 21

Adafruit_NeoPixel armLeft(armLeft_LED, 3, NEO_GRBW + NEO_KHZ800);  // 左腕 LED個数 36
Adafruit_NeoPixel bodyLeft(bodyLeft_LED, 4, NEO_GRBW + NEO_KHZ800); // 左胴 LED個数 27
Adafruit_NeoPixel bodyRight(bodyRight_LED, 6, NEO_GRBW + NEO_KHZ800);// 右胴 LED個数 27
Adafruit_NeoPixel armRight(armRight_LED, 7, NEO_GRBW + NEO_KHZ800); // 右腕 LED個数 36
Adafruit_NeoPixel legRight(legRight_LED, 8, NEO_GRBW + NEO_KHZ800); // 右足 LED個数 21
Adafruit_NeoPixel legLeft(legLeft_LED, 9, NEO_GRBW + NEO_KHZ800);  // 左足 LED個数 21

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

//じわじわ光る 脛⇒もも⇒腰⇒アーム　消える
#define pulseWhite_wait 1000//じわじわの光までの時間
#define pulseWhite_wait2 1000 //じわじわ光　脛⇒モモ⇒腰⇒腕の待ち時間
#define pulseWhite_time 1 //じわじわ光回数
#define pulseWhite_space 5 //じわじわ光間隔
#define pulseWhite_speed 1 //じわじわ光点灯速度

//じわじわ光る 脛⇒もも⇒腰⇒アーム　消えない
#define pulseWhite_hold_wait 1000//じわじわの光までの時間
#define pulseWhite_hold_wait2 1000 //じわじわ光　脛⇒モモ⇒腰⇒腕の待ち時間
#define pulseWhite_hold_time 1 //じわじわ光回数
#define pulseWhite_hold_space 5 //じわじわ光間隔
#define pulseWhite_hold_speed 3 //じわじわ光点灯速度

#define colorWipeRange_wave_foot_wait 1000//下⇒上点灯までの時間
#define colorWipeRange_wave_time 10//下⇒上点灯の点灯間隔時間

#define random_all_wait 1000//ランダム点灯までの時間
#define random_all_wait2 10000//ランダム点灯までの時間
#define random_all_time 25//ランダム点灯までの回数
#define random_all_space 50//ランダム点灯までの間隔
#define random_all_num 5//ランダム点灯までの間隔

#define suits_led_change_wait 7000//諭吉衣装　小松衣装に入れ替わりの待ち時間
#define suits_led_change_time 5//諭吉衣装　小松衣装に入れ替わりの回数
#define suits_led_change_space 1000//諭吉衣装　小松衣装に入れ替わりの感覚

#define pulseWhite_series_hold 3000//じわじわ光⇒全身

////LEDディスクに光が集まっていく
#define LEDtoCenter_up_speed 20 //点灯スピード
#define LEDtoCenter_up_num_move 5//移動個数( 移動個数＝(総数/2)ー変数値)
#define LEDtoCenter_up_time 5//点灯回数

 

#define moni 2//じわじわ光⇒全身
void loop() {
  // 1. 全身に単色
if(moni == 1){
  delay(pulseWhite_wait);
//////////////////じわじわ光る 脛⇒もも⇒腰⇒アーム
 pulseWhite_series_sune(pulseWhite_time, pulseWhite_space, pulseWhite_speed); //(time,wait,speed)
  delay(pulseWhite_wait2);
 pulseWhite_series_momo(pulseWhite_time, pulseWhite_space, pulseWhite_speed); //(time,wait,speed)
   delay(pulseWhite_wait2);
 pulseWhite_series_body(pulseWhite_time, pulseWhite_space, pulseWhite_speed); //(time,wait,speed)
   delay(pulseWhite_wait2);
 pulseWhite_arm(pulseWhite_time, pulseWhite_space, pulseWhite_speed); //(time,wait,speed)
   delay(pulseWhite_wait2);
///////////////////////////////
   delay(random_all_wait);
//////////////////ランダム点灯
  random_all(armLeft.Color(0, 0, 0, 255),random_all_time, random_all_space,random_all_num); //左アーム　ランダム点灯 ,関数(色、点灯回数、待ち時間、点灯個数)
//////////////////////////////
   delay(colorWipeRange_wave_foot_wait);
//////////////////下⇒上の点灯
colorWipeRange_wave_foot(armLeft.Color(0, 0, 0, 255), colorWipeRange_wave_time); // 白  
colorWipeRange_wave_bodyarm(armLeft.Color(0, 0, 0, 255), colorWipeRange_wave_time); // 白
//////////////////////////////
  delay(random_all_wait2);
//////////////////ランダム点灯
  setAllColor(armLeft.Color(0, 0, 0, 0)); // 白
  random_all(armLeft.Color(0, 0, 0, 255),random_all_time, random_all_space,random_all_num); //左アーム　ランダム点灯 ,関数(色、点灯回数、間隔、点灯個数)
   setAllColor(armLeft.Color(0, 0, 0, 0)); // off
//////////////////////////////
  delay(suits_led_change_wait);
/////////////////諭吉衣装と小松衣装の光の移動
suits_led_change(armLeft.Color(0, 0, 0, 255),armLeft.Color(0, 0, 0, 0),suits_led_change_time,suits_led_change_space);//関数(点灯する色、消灯、点灯回数、点灯間隔)
//////////////////////////////////////////////
 delay(pulseWhite_series_hold);
//////////////////じわじわ光る 消えない
 pulseWhite_series_sune_hold(pulseWhite_hold_time, pulseWhite_hold_space, pulseWhite_hold_speed); //(time,wait,speed)
  delay(pulseWhite_wait2);
 pulseWhite_series_momo_hold(pulseWhite_hold_time, pulseWhite_hold_space, pulseWhite_hold_speed); //(time,wait,speed)
   delay(pulseWhite_wait2);
 pulseWhite_series_body_hold(pulseWhite_hold_time, pulseWhite_hold_space, pulseWhite_hold_speed); //(time,wait,speed)
   delay(pulseWhite_wait2);
 pulseWhite_arm_hold(pulseWhite_hold_time, pulseWhite_hold_space, pulseWhite_hold_speed); //(time,wait,speed)
   delay(pulseWhite_wait2);
///////////////////////////////

  ///////////////////////////////中央に光が集まっていく
 setAllColor(armLeft.Color(0, 0, 0, 0)); // 白
 LEDtoCenter(armLeft.Color(0, 0, 0, 255), LEDtoCenter_up_speed,armLeft_LED,LEDtoCenter_up_num_move,LEDtoCenter_up_time);//(色、スピード、LED個数、LED幅(総数- 変数、間隔)、回数
 ///////////////////////////////

  
//setAllColor(armLeft.Color(0, 0, 0, 255)); // 白
//
//
//  delay(1000);
//  setAllColor(armLeft.Color(255, 0, 0, 0)); // 赤
//  delay(1000);
//  setAllColor(armLeft.Color(0, 255, 0, 0)); // 緑
//  delay(1000);
//  setAllColor(armLeft.Color(0, 0, 255, 0)); // 青
//  delay(1000);
//  setAllColor(armLeft.Color(0, 0, 0, 255)); // 白
//  delay(1000);
//  setAllColor(armLeft.Color(0, 0, 0, 0)); // 消灯 
//  delay(1000);
  // 3. rainbow
  rainbowCycleAll(10);
  delay(10000000);
}
if(moni == 2){
  ///////////////////////////////中央に光が集まっていく
 setAllColor(armLeft.Color(0, 0, 0, 0)); // 白
 LEDtoCenter(armLeft.Color(0, 0, 0, 255), LEDtoCenter_up_speed,armLeft_LED,LEDtoCenter_up_num_move,LEDtoCenter_up_time);//(色、スピード、LED個数、LED幅(総数- 変数、間隔)、回数
 ///////////////////////////////
  delay(10000000);
}

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

void setarmLeftColor(uint32_t color) {//アーム左
  Adafruit_NeoPixel* strips[] = { &armLeft };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

void setbodyLeftColor(uint32_t color) {//ボディー左
  Adafruit_NeoPixel* strips[] = { &bodyLeft };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

void setbodyRightColor(uint32_t color) {//ボディー右
  Adafruit_NeoPixel* strips[] = { &bodyRight };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

void setarmRightColor(uint32_t color) {//アーム　右
  Adafruit_NeoPixel* strips[] = { &armRight };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

void setlegRightColor(uint32_t color) {//モモ　右
  Adafruit_NeoPixel* strips[] = { &legRight };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels()-10; i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

void setlegLeftColor(uint32_t color) {//モモ　左
  Adafruit_NeoPixel* strips[] = { &legLeft };
  for (auto strip : strips) {
    for (uint16_t i = 0; i < strip->numPixels()-10; i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

void setlegRightColor_sune(uint32_t color) { //脛　左
  Adafruit_NeoPixel* strips[] = { &legRight };
  for (auto strip : strips) {
    for (uint16_t i = 11; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, color);
    }
    strip->show();
  }
}

void setlegLeftColor_sune(uint32_t color) {  // 脛　右
  Adafruit_NeoPixel* strips[] = { &legLeft };
  for (auto strip : strips) {
    for (uint16_t i = 11; i < strip->numPixels(); i++) {
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

//脛（すね）光る
void pulseWhite_series_sune(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) { 
      uint8_t val = neopix_gamma[j];
      setlegRightColor_sune(armLeft.Color(0, 0, 0, val));
      setlegLeftColor_sune(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    for (int j = 255; j >= 0; j -= 4) {
      uint8_t val = neopix_gamma[j];
      setlegRightColor_sune(armLeft.Color(0, 0, 0, val));
      setlegLeftColor_sune(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
  
    delay(100);
  }
}

//太もも光る
void pulseWhite_series_momo(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) { 
      uint8_t val = neopix_gamma[j];
      setlegRightColor(armLeft.Color(0, 0, 0, val));
      setlegLeftColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    for (int j = 255; j >= 0; j -= 4) {
      uint8_t val = neopix_gamma[j];
      setlegRightColor(armLeft.Color(0, 0, 0, val));
      setlegLeftColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
  
    delay(100);
  }
}

//腰　光る
void pulseWhite_series_body(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) { 
      uint8_t val = neopix_gamma[j];
      setbodyLeftColor(armLeft.Color(0, 0, 0, val));
      setbodyRightColor(armLeft.Color(0, 0, 0, val));
     // setlegRightColor(armLeft.Color(0, 0, 0, val));
     // setlegLeftColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    for (int j = 255; j >= 0; j -= 4) {
      uint8_t val = neopix_gamma[j];
      setbodyLeftColor(armLeft.Color(0, 0, 0, val));
      setbodyRightColor(armLeft.Color(0, 0, 0, val));
    //  setlegRightColor(armLeft.Color(0, 0, 0, val));
    //  setlegLeftColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
  
    delay(100);
  }
}

//アーム　光る
void  pulseWhite_arm(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) { 
      uint8_t val = neopix_gamma[j];
     setarmRightColor(armLeft.Color(0, 0, 0, val));
     setarmLeftColor(armLeft.Color(0, 0, 0, val));
     // setlegRightColor(armLeft.Color(0, 0, 0, val));
     // setlegLeftColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    for (int j = 255; j >= 0; j -= 4) {
      uint8_t val = neopix_gamma[j];
     setarmRightColor(armLeft.Color(0, 0, 0, val));
     setarmLeftColor(armLeft.Color(0, 0, 0, val));
    //  setlegRightColor(armLeft.Color(0, 0, 0, val));
    //  setlegLeftColor(armLeft.Color(0, 0, 0, val));
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

void  random_all(uint32_t c, uint16_t time, uint8_t wait,uint8_t num) { /////ランダム点灯
 Adafruit_NeoPixel* strips1[] = { &armLeft};
 Adafruit_NeoPixel* strips2[] = { &bodyLeft};
 Adafruit_NeoPixel* strips3[] = { &bodyRight};
 Adafruit_NeoPixel* strips4[] = { &armRight};
 Adafruit_NeoPixel* strips5[] = { &legRight};
 Adafruit_NeoPixel* strips6[] = { &legLeft};    
  uint32_t ledPosition_armLeft_LED;
  uint32_t ledPosition_bodyLeft_LED;
  uint32_t ledPosition_bodyRight_LED;
  uint32_t ledPosition_armRight_LED;
  uint32_t ledPosition_legRight_LED;
  uint32_t ledPosition_legLeft_LED;
  for (auto strip1 : strips1) {
      for (auto strip2 : strips2) {
          for (auto strip3 : strips3) {
            for (auto strip4 : strips4) {
              for (auto strip5 : strips5) {
                for (auto strip6 : strips6) {
                  for(uint16_t i=0; i<=time; i++){
                   ledPosition_armLeft_LED = random(0, armLeft_LED);
                   ledPosition_bodyLeft_LED=random(0, bodyLeft_LED);
                   ledPosition_bodyRight_LED=random(0, bodyRight_LED);
                   ledPosition_armRight_LED=random(0, armRight_LED);
                   ledPosition_legRight_LED=random(0, legRight_LED);
                   ledPosition_legLeft_LED=random(0, legLeft_LED);
    
                     for(uint16_t i=ledPosition_armLeft_LED; i<ledPosition_armLeft_LED + num; i++) {
                         strip1->setPixelColor(i, c);
                     }
                     for(uint16_t i= ledPosition_bodyLeft_LED; i< ledPosition_bodyLeft_LED + num; i++) {
                         strip2->setPixelColor(i, c);
                     }
                     for(uint16_t i=  ledPosition_bodyRight_LED; i<  ledPosition_bodyRight_LED + num; i++) {
                         strip3->setPixelColor(i, c);
                     }
                     for(uint16_t i=  ledPosition_armRight_LED; i<  ledPosition_armRight_LED + num; i++) {
                         strip4->setPixelColor(i, c);
                     }
                     for(uint16_t i=  ledPosition_legRight_LED; i<   ledPosition_legRight_LED + num; i++) {
                        strip5->setPixelColor(i, c);
                     }
                     for(uint16_t i=   ledPosition_legLeft_LED; i<  ledPosition_legLeft_LED + num; i++) {
                        strip6->setPixelColor(i, c);
                     }
        
                     strip1->show();
                     strip2->show();
                     strip3->show();
                     strip4->show();
                     strip5->show();
                     strip6->show();
                     delay(wait);
         
                     for(uint16_t i=ledPosition_armLeft_LED; i<ledPosition_armLeft_LED + num; i++) {
                        strip1->setPixelColor(i, armLeft.Color(0, 0, 0, 0));
                     }
                    for(uint16_t i= ledPosition_bodyLeft_LED; i< ledPosition_bodyLeft_LED + num; i++) {
                        strip2->setPixelColor(i, armLeft.Color(0, 0, 0, 0));
                    }
                    for(uint16_t i= ledPosition_bodyRight_LED; i< ledPosition_bodyRight_LED + num; i++) {
                        strip3->setPixelColor(i, armLeft.Color(0, 0, 0, 0));
                    }
                   for(uint16_t i=ledPosition_armRight_LED; i< ledPosition_armRight_LED + num; i++) {
                       strip4->setPixelColor(i, armLeft.Color(0, 0, 0, 0));
                    }
                  for(uint16_t i= ledPosition_legRight_LED; i<  ledPosition_legRight_LED + num; i++) {
                       strip5->setPixelColor(i, armLeft.Color(0, 0, 0, 0));
                    }
                 for(uint16_t i=  ledPosition_legLeft_LED; i<   ledPosition_legLeft_LED + num; i++) {
                       strip6->setPixelColor(i, armLeft.Color(0, 0, 0, 0));
                    }
        
                  strip1->show();
                  strip2->show();
                  strip3->show();
                  strip4->show();
                  strip5->show();
                  strip6->show();
  }
}
}
}
}
}
}
}

void colorWipeRange_wave_foot(uint32_t c, uint32_t wait) {  //足部分の下⇒上の点灯
 Adafruit_NeoPixel* strips5[] = { &legRight};
 Adafruit_NeoPixel* strips6[] = { &legLeft};  
   for (auto strip5 : strips5) {
       for (auto strip6 : strips6) {
          for(uint16_t i=legRight_LED; i>0; i--) { //legRight_LED=legleft_LEDのため、legRight_LEDを使用
                strip5->setPixelColor(i, c);
                strip6->setPixelColor(i, c);   
                strip5->show();
                strip6->show();
                delay(wait);
               }

          }
}
}

void colorWipeRange_wave_bodyarm(uint32_t c, uint32_t wait) {  //上半身部分の下⇒上の点灯
 Adafruit_NeoPixel* strips1[] = { &armLeft};
 Adafruit_NeoPixel* strips2[] = { &bodyLeft};
 Adafruit_NeoPixel* strips3[] = { &bodyRight};
 Adafruit_NeoPixel* strips4[] = { &armRight};
 uint32_t g=(armLeft_LED/2);
  for (auto strip1 : strips1) {
   for (auto strip2 : strips2) {
       for (auto strip3 : strips3) {
         for (auto strip4 : strips4) {        
          for(uint16_t i=armLeft_LED; i>0; i--) { //armLeft_LED=bodyRigh_LED　かつarmLeft＿LEDが一番個数が多いためarmLeft_LEDを使用
               
                strip2->setPixelColor(i, c);
                strip3->setPixelColor(i, c);   
                strip2->show();
                strip3->show();
                delay(wait);
                if (i>=(armLeft_LED/2)){
                strip1->setPixelColor(i-(armLeft_LED/2+1), c);
                strip4->setPixelColor(i-(armLeft_LED/2+1), c);   
                strip1->show();               
                strip4->show();   

                strip1->setPixelColor(g, c);
                strip4->setPixelColor(g, c);   
                strip1->show();               
                strip4->show();
                g=g+1;;        
                delay(wait);
               }
               

          }
 }
}
}
}
}


void suits_led_change(uint32_t color_on,uint32_t color_off,uint32_t time,uint32_t wait) {
  Adafruit_NeoPixel* strips[] = { &armLeft, &bodyLeft, &bodyRight, &armRight, &legRight, &legLeft };
 for (uint16_t k = 0; k < time; k++) {
       for (auto strip : strips) {
           for (uint16_t i = 0; i < strip->numPixels(); i++) {
             strip->setPixelColor(i, color_on);
            }
            strip->show();
        }
        
        delay(wait);
        
       for (auto strip : strips) {
           for (uint16_t i = 0; i < strip->numPixels(); i++) {
             strip->setPixelColor(i, color_off);
            }
            strip->show();
        }
         delay(wait);
  }
}  

//脛（すね）光るホールド
void pulseWhite_series_sune_hold(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) { 
      uint8_t val = neopix_gamma[j];
      setlegRightColor_sune(armLeft.Color(0, 0, 0, val));
      setlegLeftColor_sune(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
    delay(100);
  }
}

//太もも光る
void pulseWhite_series_momo_hold(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) { 
      uint8_t val = neopix_gamma[j];
      setlegRightColor(armLeft.Color(0, 0, 0, val));
      setlegLeftColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
  
    delay(100);
  }
}

//腰　光る
void pulseWhite_series_body_hold(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) { 
      uint8_t val = neopix_gamma[j];
      setbodyLeftColor(armLeft.Color(0, 0, 0, val));
      setbodyRightColor(armLeft.Color(0, 0, 0, val));
     // setlegRightColor(armLeft.Color(0, 0, 0, val));
     // setlegLeftColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
  
    delay(100);
  }
}

//アーム　光る
void  pulseWhite_arm_hold(uint16_t time, uint8_t wait, uint8_t speed) {
  for (uint16_t k = 0; k < time; k++) {
    for (int j = 0; j < 256; j += speed) { 
      uint8_t val = neopix_gamma[j];
     setarmRightColor(armLeft.Color(0, 0, 0, val));
     setarmLeftColor(armLeft.Color(0, 0, 0, val));
     // setlegRightColor(armLeft.Color(0, 0, 0, val));
     // setlegLeftColor(armLeft.Color(0, 0, 0, val));
      delay(wait);
    }
  
    delay(100);
  }
}

//両腕腕5個ずつ移動する(腕⇒肩)
void LEDtoCenter(uint32_t c, uint8_t wait, uint8_t num, uint8_t num_move,uint8_t time) {
 Adafruit_NeoPixel* strips[] = { &armLeft, &bodyLeft, &bodyRight, &armRight, &legRight, &legLeft };
  Adafruit_NeoPixel* strips1[] = { &armLeft};//３６個
 Adafruit_NeoPixel* strips2[] = { &bodyLeft};//２７個
 Adafruit_NeoPixel* strips3[] = { &bodyRight};//２７個
 Adafruit_NeoPixel* strips4[] = { &armRight};//３６個
 Adafruit_NeoPixel* strips5[] = { &legRight};
 Adafruit_NeoPixel* strips6[] = { &legLeft};    
 uint8_t i;
 uint8_t g;
 uint8_t u;
 for (auto strip4 : strips4) {
  for (auto strip1 : strips1) {
    for (auto strip2 : strips2) {
       for (auto strip3 : strips3) {
          for (auto strip5 : strips5) {
             for (auto strip6 : strips6) {
            for (uint16_t k = 0; k < time; k++) {
       i=0;
       g=0;
       u=legRight_LED;
      for(uint16_t k=num; k >0 ; k--) {
////////////////////////////////////////// ボディーの上⇒下
         if(i < ((bodyLeft_LED)/2)-num_move){ 
                strip2->setPixelColor(i, c);
                strip3->setPixelColor(i, c);
                strip2->show();
                strip3->show();
                i=i+1;
          }
////////////////////////////////////////
//////////////////////////////////////// ボディーの下⇒上
         if(k >= ((bodyLeft_LED)/2)-num_move){ 
                strip2->setPixelColor(k, c);
                strip3->setPixelColor(k, c);
                strip2->show();
                strip3->show();
          }
//////////////////////////////////////
/////////////////////////////////////　アームの下⇒上         
          if(k >= (armLeft_LED/2)){
            strip1->setPixelColor((k-(armLeft_LED+2)/2), c);
            strip4->setPixelColor((k-(armLeft_LED+2)/2), c);
            strip1->show();
            strip4->show();
          }
////////////////////////////////////
//////////////////////////////////////// 足の下⇒上
         if(u <= ((legRight_LED))){ 
                strip5->setPixelColor(u, c);
                strip6->setPixelColor(u, c);
                strip5->show();
                strip6->show();
                 u=u-1;
          }
//////////////////////////////////////
      
//      if(armLeft_LED-k >= 0){
//        strip->setPixelColor(armLeft_LED-k, c);
//      }


//      if(0+k <= armRight_LED){
//        strip->setPixelColor(0+k, c);
//      }
//      if(armRight_LED-k >= 0){
//        strip->setPixelColor(armRight_LED-k, c); 
//      }
// 

    strip1->setPixelColor(k-num_move, armLeft.Color(0, 0, 0, 0));
    strip2->setPixelColor(g-num_move, armLeft.Color(0, 0, 0, 0));
    strip3->setPixelColor(g-num_move, armLeft.Color(0, 0, 0, 0));
    strip2->setPixelColor(k+num_move, armLeft.Color(0, 0, 0, 0));
    strip3->setPixelColor(k+num_move, armLeft.Color(0, 0, 0, 0));
    strip4->setPixelColor(k-num_move, armLeft.Color(0, 0, 0, 0));
    strip5->setPixelColor(k-num_move, armLeft.Color(0, 0, 0, 0));
    strip6->setPixelColor(k-num_move, armLeft.Color(0, 0, 0, 0));
    //strip1->setPixelColor((armLeft_LED-k)+num_move, armLeft.Color(0, 0, 0, 0));
    strip1->show();
    strip2->show();
    strip3->show();
    strip4->show();
    strip5->show();
    strip6->show();
    delay(wait);
    g=g+1;
  }
  
}
}
}
}
}
}
}
}
