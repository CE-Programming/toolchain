#include <usbdrvce.h>

#include <tice.h>

#include <stddef.h>

static void putChar(char c) {
  static char str[2];
  str[0] = c;
  os_PutStrFull(str);
}
static void putNibHex(unsigned char x) {
  x &= 0xF;
  putChar(x < 10 ? '0' + x : 'A' + x - 10);
}
static void putByteHex(unsigned char x) {
  putNibHex(x >> 4);
  putNibHex(x >> 0);
}
static void putIntHex(unsigned int x) {
  putByteHex(x >> 16);
  putByteHex(x >>  8);
  putByteHex(x >>  0);
}

static usb_error_t handle_usb_event(usb_event_t event, void *event_data,
				    usb_callback_data_t *callback_data) {
  static const char *usb_event_names[] = {
    "USB_DEVICE_DISCONNECTED_EVENT",
    "USB_DEVICE_CONNECTED_EVENT",
    "USB_DEVICE_DISABLED_EVENT",
    "USB_DEVICE_ENABLED_EVENT",
    "USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT",
    "USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT",
    "USB_DEFAULT_SETUP_EVENT",
    // Temp debug events:
    "USB_DEVICE_INT",
    "USB_DEVICE_CONTEXT_INT",
    "USB_DEVICE_FIFO_INT",
    "USB_DEVICE_DEVICE_INT",
    "USB_OTG_INT",
    "USB_HOST_INT",
    "USB_CONTEXT_SETUP_INT",
    "USB_CONTEXT_INPUT_INT",
    "USB_CONTEXT_OUTPUT_INT",
    "USB_CONTEXT_END_INT",
    "USB_CONTEXT_ERROR_INT",
    "USB_CONTEXT_ABORT_INT",
    "USB_FIFO0_INPUT_INT",
    "USB_FIFO0_OUTPUT_INT",
    "USB_FIFO0_SHORT_PACKET_INT",
    "USB_FIFO1_INPUT_INT",
    "USB_FIFO1_OUTPUT_INT",
    "USB_FIFO1_SHORT_PACKET_INT",
    "USB_FIFO2_INPUT_INT",
    "USB_FIFO2_OUTPUT_INT",
    "USB_FIFO2_SHORT_PACKET_INT",
    "USB_FIFO3_INPUT_INT",
    "USB_FIFO3_OUTPUT_INT",
    "USB_FIFO3_SHORT_PACKET_INT",
    "USB_DEVICE_RESET_INT",
    "USB_DEVICE_SUSPEND_INT",
    "USB_DEVICE_RESUME_INT",
    "USB_DEVICE_ISOCHRONOUS_ERROR_INT",
    "USB_DEVICE_ISOCHRONOUS_ABORT_INT",
    "USB_DEVICE_ZERO_LENGTH_PACKET_TRANSMIT_INT",
    "USB_DEVICE_ZERO_LENGTH_PACKET_RECEIVE_INT",
    "USB_DEVICE_DMA_FINISH_INT",
    "USB_DEVICE_DMA_ERROR_INT",
    "USB_DEVICE_IDLE_INT",
    "USB_DEVICE_WAKEUP_INT",
    "USB_B_SRP_COMPLETE_INT",
    "USB_B_SRP_DETECT_INT",
    "USB_A_VBUS_ERROR_INT",
    "USB_B_SESSION_END_INT",
    "USB_ROLE_CHANGED_INT",
    "USB_ID_CHANGED_INT",
    "USB_OVERCURRENT_INT",
    "USB_B_PLUG_REMOVED_INT",
    "USB_A_PLUG_REMOVED_INT",
    "USB_INT",
    "USB_HOST_ERROR_INT",
    "USB_HOST_PORT_CHANGE_DETECT_INT",
    "USB_HOST_FRAME_LIST_ROLLOVER_INT",
    "USB_HOST_SYSTEM_ERROR_INT",
    "USB_HOST_ASYNC_ADVANCE_INT",
  };
  os_PutStrFull(usb_event_names[event]);
  os_NewLine();
  return USB_SUCCESS;
}

void main(void) {
  usb_Init(handle_usb_event, NULL, NULL, USB_DEFAULT_INIT_FLAGS);
  os_SetCursorPos(0, 0);
  while (!os_GetCSC()) {
    usb_WaitForInterrupt();
  }
  usb_Cleanup();
}
