#include <MIDIUSB.h>

// Настройки за Serial порт
#define BAUD_RATE 9600
HardwareSerial SerialPort(1);

void setup() {
  Serial.begin(115200);

  // Инициализация на Serial порт
  SerialPort.begin(BAUD_RATE, SERIAL_8N1, 2, 3);

  // Инициализация на MIDIUSB
  MIDIUSB.begin();
}

void loop() {
  // Четене на данни от Serial порт
  while (SerialPort.available() > 0) {
    uint8_t byte = SerialPort.read();
    midiEventPacket_t packet = {0x09, 0x90, byte, 0x7f};
    MIDIUSB.sendMIDI(packet);
  }
}