#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int sensorPin = A0;
int sensorValue = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("Library initialization; EC/CSN pin and channel definition and moduletransmission and reception address definition");
  delay(1000);
  Mirf.cePin = 8;
  Mirf.csnPin = 9;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.channel = 1;
  Mirf.payload = sizeof(float);
  Mirf.config();
  Mirf.setTADDR((byte *) "nrf02");
  Mirf.setRADDR((byte *) "nrf01");
}
void loop() {
  delay(500);
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  if (sensorValue <100) {
  }
  Mirf.send((byte *) & sensorValue);
  while (Mirf.isSending());
}
