#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
}

void loop() {
  Serial.println("request");
  
  if (Serial.available()) {
    String str = Serial.readString();
    temperateAndHumiditySeperate(str);
  }
  delay(3000);
}

//받아올것 : 온도, 습도, 날씨(표정출력)
void temperateAndHumiditySeperate(String str){
    Serial.println("trim 하기 전 str : "+str);
    //str.trim();
    int sep = str.indexOf(" ");
    Serial.println("sep : " + sep);
    String temp = str.substring(0,sep+1);
    temp.trim();
    String hum = str.substring(sep+1);
    hum.trim();
    lcd.clear();  //맨 처음 연결될 때 나오는 connected 문구가 lcd에 출력되는것을 방지
    lcd.setCursor(0,0);
    lcd.print("temp : " + temp);
    lcd.setCursor(0,1);
    lcd.print("hum : " + hum);
    Serial.println(str);
    Serial.println("temp : " + temp);
    Serial.println("hum : " + hum);
}
