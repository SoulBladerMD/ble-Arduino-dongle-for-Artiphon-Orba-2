#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Define the MIDI service and characteristic UUIDs
static BLEUUID midiServiceUUID("03b80e5a-ede8-4b33-a751-6ce34ec4c700");
static BLEUUID midiCharacteristicUUID("7772e5db-3868-4112-a1a9-f2669d106bf3");

// Define the MIDI service and characteristic objects
BLEServer* pServer = NULL;
BLEService* pService = NULL;
BLECharacteristic* pCharacteristic = NULL;

// Define the MIDI message buffer
unsigned char midiMessage[3] = {0, 0, 0};

void setup() {
  Serial.begin(9600);

  // Create the BLE server
  BLEDevice::init("Orba2");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new BLEServerCallbacks());

  // Create the MIDI service and characteristic
  pService = pServer->createService(midiServiceUUID);
  pCharacteristic = pService->createCharacteristic(midiCharacteristicUUID, BLECharacteristic::PROPERTY_WRITE_NR);
  pCharacteristic->setCallbacks(new BLECharacteristicCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising* pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(midiServiceUUID);
  pAdvertising->start();
}

void loop() {
  // Do nothing
}

// Callbacks for BLE events
class BLEServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    // Do nothing
  }

  void onDisconnect(BLEServer* pServer) {
    // Do nothing
  }
};

class BLECharacteristicCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic) {
    // Read the MIDI message data
    std::string midiData = pCharacteristic->getValue();

    // Check the length of the MIDI message
    if (midiData.length() == 3) {
      // Convert the MIDI message data to unsigned char
      midiMessage[0] = (unsigned char) midiData[0];
      midiMessage[1] = (unsigned char) midiData[1];
      midiMessage[2] = (unsigned char) midiData[2];

      // Send the MIDI message to the Arduino
      Serial.write(midiMessage, 3);
    }
  }
};
