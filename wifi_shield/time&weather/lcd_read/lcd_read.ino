#include <SimpleTimer.h>
#include <LiquidCrystal_I2C.h>

//lcd1은 방lcd, lcd2는 거실lcd
LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x25, 16, 2);

SimpleTimer timer;  

void setup() {
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
  // Initialize Serial Monitor
  Serial.begin(115200);

  timer.setInterval(5000,sendData);
}

void loop() {
  timer.run();
}

void sendData() {
  Serial.println("time"); //  //현재시간 요청
  if (!Serial.available()) {  //받은 데이터가 없을 때
    delay(100);
  }
  else{
    String str = Serial.readString();
    timeDateSeperate(str);
  }
  
  delay(2000);
  
  Serial.println("weather");  //날씨 요청
  if (!Serial.available()) {  //받은 데이터가 없을 때
    delay(100);
  }
  else{
    String str = Serial.readString();
    tempHumSeperate(str);
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
