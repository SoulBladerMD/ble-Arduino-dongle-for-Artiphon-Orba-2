#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Настройки за Bluetooth BLE
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* pServer;
BLECharacteristic* pCharacteristic;

// Настройки за Serial порт
#define BAUD_RATE 9600
HardwareSerial SerialPort(1);

void setup() {
  Serial.begin(115200);

  // Инициализация на Bluetooth BLE
  BLEDevice::init("Orba 2");
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(pService->getUUID());
  pAdvertising->start();

  // Инициализация на Serial порт
  SerialPort.begin(BAUD_RATE, SERIAL_8N1, 16, 17);
}

void loop() {
  // Проверка за свързаност с Bluetooth BLE
  if (pServer->getConnectedCount() > 0) {
    // Четене на данни от Orba 2
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      SerialPort.write(value.c_str(), value.length());
    }
  }
  delay(10);
}
