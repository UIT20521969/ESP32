#include <LiquidCrystal_I2C.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd(0x27, 16, 2);
String presentStr, previousStr = " ";
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_TT");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  lcd.init();
  lcd.backlight();
}
void loop() {
  if (Serial.available()) {
    lcd.setCursor(0, 0);
    lcd.print(Serial.read());
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
    lcd.setCursor(0, 1);
    lcd.print(SerialBT.read());
  }
  presentStr = SerialBT.read();
  if (presentStr != previousStr) {
    lcd.clear();
    Serial.println(presentStr);
    lcd.setCursor(0, 0);
    lcd.print(presentStr);
    previousStr = presentStr;
    delay(20);
  }
}