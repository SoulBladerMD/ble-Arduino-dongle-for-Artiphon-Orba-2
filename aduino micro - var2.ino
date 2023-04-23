#include <MIDIUSB.h>

// Define the MIDI message buffer
unsigned char midiMessage[3] = {0, 0, 0};

void setup() {
  Serial.begin(9600);

  // Initialize the MIDIUSB library
  MIDIUSB.begin();
}

void loop() {
  // Read MIDI messages from the ESP32
  while (Serial.available() >= 3) {
    Serial.readBytes(midiMessage, 3);

    // Send the MIDI message to the computer
    midiEventPacket_t midiPacket = {0x09, midiMessage[0], midiMessage[1], midiMessage[2]};
    MIDIUSB.sendMIDI(midiPacket);
  }
}
