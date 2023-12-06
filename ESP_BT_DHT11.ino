#include "BluetoothSerial.h"
#include "DHTesp.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

#define DHT_PIN 15

DHTesp dhtSensor;      //khoi tao bien nhan gia tri
TempAndHumidity data;  //khoi tao bien xuat gia tri
void setup() {
  Serial.begin(115200);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
  SerialBT.begin("ESP32_TT");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}
void loop() {
  data = dhtSensor.getTempAndHumidity();
  if (isnan(data.humidity)) {
    SerialBT.println("Error when reading the humidity from the sensor DHT11");
    SerialBT.println("Hum = " + String(data.humidity));
  } else {
    SerialBT.println("Temp = " + String(data.temperature));
    SerialBT.println("Hum = " + String(data.humidity));
  }
  delay(1000);
}