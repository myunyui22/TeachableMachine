#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  // Initialize Serial Monitor
  Serial.begin(115200);
}

void loop() {
  if (Serial.available()) {
    lcd.setCursor(0,0);
    String str = Serial.readString();
    timeAndDateSeperate(str);
  }
  //delay(3000);
}

void timeAndDateSeperate(String str){
    Serial.println("trim 하기 전 str : "+str);
    //str.trim();
    int sep = str.indexOf("\n");
    Serial.println("sep : "+sep);
    String current_time = str.substring(0,sep+1);
    current_time.trim();
    String date = str.substring(sep+2);
    date.trim();
    lcd.setCursor(0,0);
    lcd.print(current_time);
    lcd.setCursor(0,1);
    lcd.print(date);
    Serial.println(str);
    Serial.println(current_time);
    Serial.println(date);
}
