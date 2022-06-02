#include "Nintendo.h"
#include <Servo.h>
// Define a Gamecube Console
//デジタル5,6番ピンを使う
CGamecubeConsole GamecubeConsole1(5);
Servo myservo;
const int SV_PIN = 6;
Gamecube_Data_t d = defaultGamecubeData;

void setup()
{
  //SG90用初期セットアップ
  myservo.attach(SV_PIN, 500, 2400);
  delay(500);
  myservo.detach();

  d.report.a = 0;
  d.report.b = 0;
  d.report.x = 0;
  d.report.y = 0;
  d.report.start = 0;
  d.report.dleft = 0;
  d.report.dright = 0;
  d.report.ddown = 0;
  d.report.dup = 0;
  d.report.z = 0;
  d.report.r = 0;
  d.report.l = 0;
  d.report.xAxis = 128;
  d.report.yAxis = 128;
  d.report.cxAxis = 128;
  d.report.cyAxis = 128;
  d.report.left = 0;
  d.report.right = 0;

  //コントローラーを認識させるおまじない
  d.report.start = 1;
  GamecubeConsole1.write(d);  //press start

  d.report.start = 0;
  GamecubeConsole1.write(d);  //release start
  // Start debug serial
  //4800にしてるけど9600とかでも良いかも
  Serial.begin(9600);
}

void press_gc_reset(){
  //角度は各々要調整
  Serial.println("Reset");
  myservo.attach(SV_PIN, 500, 2400);
  myservo.write(65);
  delay(500);
  myservo.write(90);
  delay(500);
  myservo.detach();
}

void update_data(){
  if(!Serial.available()) return;

  uint8_t head = Serial.read();
  //@が送られてきたらサーボでリセットボタンを押す
  if(head == 0x40) {
      press_gc_reset();
      return;
  }

  uint8_t buttons_state_1;
  uint8_t buttons_state_2;

  // 2byte分送信される.
  while((buttons_state_1 = Serial.read()) == 0xFF) {}
  while((buttons_state_2 = Serial.read()) == 0xFF) {}

  if(buttons_state_1 & 0x40){
    d.report.xAxis = Serial.read();
    d.report.yAxis = Serial.read();
  }

  if(buttons_state_2 & 0x40){
    d.report.cxAxis = Serial.read();
    d.report.cyAxis = Serial.read();
  }

  if(buttons_state_1 & 0x80){
    d.report.a = 0;
    d.report.b = 0;
    d.report.x = 0;
    d.report.y = 0;
    d.report.l = 0;
    d.report.r = 0;
  } else {
    d.report.a =  buttons_state_1       & 1;
    d.report.b = (buttons_state_1 >> 1) & 1;
    d.report.x = (buttons_state_1 >> 2) & 1;
    d.report.y = (buttons_state_1 >> 3) & 1;
    d.report.l = (buttons_state_1 >> 4) & 1;
    d.report.r = (buttons_state_1 >> 5) & 1;
  }

  if(buttons_state_2 & 0x80){
    d.report.z      = 0;
    d.report.start  = 0;
    d.report.dleft  = 0;
    d.report.dright = 0;
    d.report.dup    = 0;
    d.report.ddown  = 0;
  } else {
    d.report.z      =  buttons_state_2       & 1;
    d.report.start  = (buttons_state_2 >> 1) & 1;
    d.report.dleft  = (buttons_state_2 >> 2) & 1;
    d.report.dright = (buttons_state_2 >> 3) & 1;
    d.report.dup    = (buttons_state_2 >> 4) & 1;
    d.report.ddown  = (buttons_state_2 >> 5) & 1;
  }
}

void loop()
{
  update_data();
  if(!GamecubeConsole1.write(d)) {
    Serial.println("GCが起動していないか、接続されていません。");
  } else {
    Serial.write(d.report.raw8, sizeof(d.report.raw8));
  }
}
