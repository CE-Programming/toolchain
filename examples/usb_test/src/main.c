#include <usbdrvce.h>

#include <stddef.h>

void main(void) {
  usb_Init(NULL, NULL, NULL, NULL, USB_DEFAULT_INIT_FLAGS);
  usb_Cleanup();
}
