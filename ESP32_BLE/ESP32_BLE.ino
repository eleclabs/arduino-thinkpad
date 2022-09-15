// Coding By IOXhop : www.ioxhop.com
// This version 0.2

#include "BLE.h"

#define LED_PIN LED_BUILTIN
#define SERVICE_UUID 0xFF
#define CHAR_UUID_LED 0xFF01

BLE ble("easyBLE LED");

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  ble.begin();
  
  ble.on(READ, [](int service_uuid, int char_uuid) {
    Serial.println("Event: READ");
    Serial.print("Service UUID: 0x");
    Serial.println(service_uuid, HEX);
    Serial.print("Characteristic UUID: 0x");
    Serial.println(char_uuid, HEX);

    ble.reply(digitalRead(LED_PIN));
  });
  
  ble.on(WRITE, [](int service_uuid, int char_uuid) {
    Serial.println("Event: WRITE");
    Serial.print("Service UUID: 0x");
    Serial.println(service_uuid, HEX);
    Serial.print("Characteristic UUID: 0x");
    Serial.println(char_uuid, HEX);
    Serial.print("Data: ");
    char *data = ble.data();
    for (int i=0;data[i]!=0;i++) {
        Serial.print("0x");
        if (data[i] < 0x10) Serial.print("0");
        Serial.print(data[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    if (service_uuid == SERVICE_UUID && char_uuid == CHAR_UUID_LED) {
      digitalWrite(LED_PIN, data[0] - '0');
    }
  });
  
  BLEService *service = new BLEService(SERVICE_UUID);
  service->addCharacteristic(CHAR_UUID_LED);
  ble.addService(service);
}

void loop() {
  
}
