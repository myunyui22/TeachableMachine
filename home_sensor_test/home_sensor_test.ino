#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#define led1 12;
#define led2 13;

LiquidCrystal_I2C lcd1(0x27, 16, 2);  //현재 시간 표시 lcd
LiquidCrystal_I2C lcd2(0x25, 16, 2);  //날씨 표시 lcd
Servo window1, window2, window3, front_door, curtain; //window2는 window1과 같은 디지털핀 공유

void setup() {
  Serial.begin(115200);
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
  window1.attach(6);
  window2.attach(7);
  window3.attach(8);
  front_door.attach(11);
  curtain.attach(5);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);

  //motor test
  window1.write(90);
  window2.write(90);
  window3.write(90);
  delay(1000);
  window1.write(0);
  window2.write(0);
  window3.write(0);
}

void loop() {
  while (Serial.available() > 0) {
    char msg = Serial.read();
    if (msg == 'f') { //open_the_front_door
      front_door.write(180);
    }
    if (msg == 'b') { //close_the_front_door
      front_door.write(0);
    }
    if (msg == 'o') { //open_the_window
      window1.write(90);
      window2.write(90);
      window3.write(90);
    }
    if (msg == 'c') { //close_the_window
      window1.write(0);
      window2.write(0);
      window3.write(0);
    }
    if (msg == 't') { //curent_time
      /*Serial.println("time");
      if (!Serial.available()) {  //받은 데이터가 없을 때
        delay(100);
      }
      else{
        String str = Serial.readString();
        timeDateSeperate(str);
      }*/
    }
    if (msg == 'w') { //weather
      /*Serial.println("weather");
      if (!Serial.available()) {  //받은 데이터가 없을 때
        delay(100);
      }
      else{
        String str = Serial.readString();
        tempHumSeperate(str);
      }*/
    }
    if (msg == 'n') { //led_on
      digitalWrite(12, HIGH);
      digitalWrite(9, HIGH);
    }
    if (msg == 'l') { //led_off
      digitalWrite(12, LOW);
      digitalWrite(9, LOW);
    }
    if (msg == 'u') { //curtain_open
      curtain.write(180);
    }
    if (msg == 'd') { //curtain_close
      curtain.write(0);
    }
  }
}

void timeDateSeperate(String str) {
  int sep = str.indexOf(" ");
  String currentTime = str.substring(0, sep+1); //시간
  String currentDate = str.substring(sep + 1); //날짜

  //개행문자 제거
  currentTime.trim();
  currentDate.trim();

  //lcd 클리어
  lcd1.clear();
  
  //출력
  lcd1.setCursor(0, 0);
  lcd1.print("time : " + currentTime);
  lcd1.setCursor(0, 1);
  lcd1.print("date:" + currentDate);
}

void tempHumSeperate(String str) {
  int sep = str.indexOf(" ");
  String temp = str.substring(0, sep + 1); //온도
  String hum = str.substring(sep + 1); //습도

  //개행문자 제거
  temp.trim();
  hum.trim();

  //lcd 클리어
  lcd2.clear();
  //출력
  lcd2.setCursor(0,0);
  lcd2.print("temp : " + temp); //온도
  lcd2.setCursor(0,1);
  lcd2.print("hum : " + hum); //습도
}
