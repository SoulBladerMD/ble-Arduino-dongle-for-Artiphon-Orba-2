#include <usbhid.h>
#include <hidboot.h>
#include <usbhub.h>

USB     Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

void setup() {
  Usb.Init();
  HidKeyboard.SetReportParser(0, ParseHIDReport);
}

void loop() {
  Usb.Task();
  // вашият код тук
}

void ParseHIDReport(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {
  // вашият код тук
}
