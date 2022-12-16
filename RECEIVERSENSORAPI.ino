#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzzer = 7;

void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(buzzer, OUTPUT);
  Mirf.cePin = 8;
  Mirf.csnPin = 9;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.channel = 1;
  Mirf.payload = sizeof(float);
  Mirf.config();
  Mirf.setTADDR((byte *) "nrf01");
  Mirf.setRADDR((byte *) "nrf02");
  Serial.println("Reception of the value :");
}
void loop() {
  int sensorValue;
  if (Mirf.dataReady()) {
    Mirf.getData((byte *) & sensorValue);
    Serial.println(sensorValue);
    lcd.setCursor(0, 0);
    lcd.print("LEVEL API:");
    lcd.setCursor(10, 0);
    lcd.print(sensorValue);
    if (sensorValue <100)
    {
      lcd.setCursor(0, 1);
      lcd.print("BAHAYA!!!");
      tone(buzzer, 1000, 10000);
      digitalWrite(3, HIGH);
    }
    else
    {
      lcd.setCursor(0, 1);
      lcd.print("NORMAL!!!");
      noTone(buzzer);
      digitalWrite(3,LOW);
    }
    delay(500);}
}
