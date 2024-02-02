#include <BlynkSimpleEsp32.h>
#include <WiFi.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define moisture 33    //PIN
#define ph 34

#define BLYNK_TEMPLATE_ID "TMPL6J18G4TtL"               //FIRMWARE CONFIGURATION BLYNK
#define BLYNK_TEMPLATE_NAME "ALPAT"
#define BLYNK_AUTH_TOKEN "7PXv3bUuOs_MLEPssP-vbILm7v-1SHNP"

#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, "admin", "12345678", "blynk.cloud", 80);  //username & pass

  lcd.init();
  lcd.backlight();
  
  pinMode(moisture, INPUT);
  pinMode(ph, INPUT);
}

void loop() {
  Blynk.run();

  int mValue = analogRead(moisture);      //membaca nilai sensor moisture

  int phValue = analogRead(ph);           //membaca nilai sensor pH
  int nilaiPH = (0.0139*phValue)+7.7851;  //rumus pembacaan sensor pH
  int mapM = map(mValue, 4095, 0, 0, 100);
  
  Serial.print(mapM);
  Serial.print(" || ");
  Serial.println(nilaiPH);

  Blynk.virtualWrite(V0, mapM);
  Blynk.virtualWrite(V1, nilaiPH);

  lcd.setCursor(0, 0);
  lcd.print("Moisture : ");
  lcd.setCursor(11, 0);
  lcd.print(mapM);
  lcd.setCursor(14, 0);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("----- pH : ");
  lcd.setCursor(11, 1);
  lcd.print(nilaiPH);

  delay(1000);
  lcd.setCursor(11, 1);
  lcd.print("  ");


}
