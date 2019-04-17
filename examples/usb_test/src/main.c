#include <usbdrvce.h>

#include <debug.h>
#include <tice.h>

#include <stddef.h>
#include <string.h>

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
static void putIntHex(unsigned x) {
    putByteHex(x >> 16);
    putByteHex(x >>  8);
    putByteHex(x >>  0);
}
static void putBlockHex(void *block, size_t size) {
    while (size--)
        putByteHex(*(*(unsigned char **)&block)++);
}

static usb_error_t got_device_descriptor(usb_endpoint_t endpoint, usb_transfer_status_t status,
                                         size_t transferred, usb_transfer_data_t *data) {
    return USB_SUCCESS;
}

static usb_error_t handle_usb_event(usb_event_t event, void *event_data,
                                    usb_callback_data_t *callback_data) {
    static const char *usb_event_names[] = {
        "USB_ROLE_CHANGED_EVENT",
        "USB_DEVICE_DISCONNECTED_EVENT",
        "USB_DEVICE_CONNECTED_EVENT",
        "USB_DEVICE_DISABLED_EVENT",
        "USB_DEVICE_ENABLED_EVENT",
        "USB_DEVICE_OVERCURRENT_DEACTIVATED_EVENT",
        "USB_DEVICE_OVERCURRENT_ACTIVATED_EVENT",
        "USB_DEFAULT_SETUP_EVENT",
        // Temp debug events:
        "USB_DEVICE_INT",
        "USB_DEVICE_CONTROL_INT",
        "USB_DEVICE_FIFO_INT",
        "USB_DEVICE_DEVICE_INT",
        "USB_OTG_INT",
        "USB_HOST_INT",
        "USB_CONTROL_INPUT_INT",
        "USB_CONTROL_OUTPUT_INT",
        "USB_CONTROL_END_INT",
        "USB_CONTROL_ERROR_INT",
        "USB_CONTROL_ABORT_INT",
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
        "USB_A_SRP_DETECT_INT",
        "USB_A_VBUS_ERROR_INT",
        "USB_B_SESSION_END_INT",
        "USB_OVERCURRENT_INT",
        "USB_B_PLUG_REMOVED_INT",
        "USB_A_PLUG_REMOVED_INT",
        "USB_INT",
        "USB_HOST_ERROR_INT",
        "USB_HOST_PORT_CONNECT_STATUS_CHANGE_INT",
        "USB_HOST_PORT_ENABLE_DISABLE_CHANGE_INT",
        "USB_HOST_PORT_OVERCURRENT_CHANGE_INT",
        "USB_HOST_PORT_FORCE_PORT_RESUME_INT",
        "USB_HOST_FRAME_LIST_ROLLOVER_INT",
        "USB_HOST_SYSTEM_ERROR_INT",
        "USB_HOST_ASYNC_ADVANCE_INT",
    };
    static char device_descriptor[8];
    switch (event) {
        case USB_ROLE_CHANGED_EVENT:
            os_PutStrFull(usb_event_names[event]);
            putChar(':');
            putNibHex(*(usb_role_t *)event_data >> 4);
            _OS(os_NewLine);
            break;
        case USB_DEVICE_DISCONNECTED_EVENT:
        case USB_DEVICE_CONNECTED_EVENT:
            os_PutStrFull(usb_event_names[event]);
            putChar(':');
            putIntHex((unsigned)event_data);
            putIntHex((unsigned)usb_FindDevice(NULL, NULL, USB_SKIP_HUBS));
            _OS(os_NewLine);
            break;
        case USB_DEVICE_DISABLED_EVENT:
            os_PutStrFull(usb_event_names[event]);
            _OS(os_NewLine);
            memset(device_descriptor, 0, sizeof(device_descriptor));
            break;
        case USB_DEVICE_ENABLED_EVENT: {
            static const usb_control_setup_t setup = {
                USB_DEVICE_TO_HOST | USB_STANDARD_REQUEST | USB_RECIPIENT_DEVICE,
                USB_GET_DESCRIPTOR,
                USB_DEVICE_DESCRIPTOR << 8,
                0,
                sizeof(device_descriptor),
            };
            os_PutStrFull(usb_event_names[event]);
            putChar(':');
            putIntHex((unsigned)event_data);
            putIntHex((unsigned)usb_FindDevice(NULL, NULL, USB_SKIP_HUBS));
            _OS(os_NewLine);
            return usb_ScheduleDefaultControlTransfer(event_data, &setup, &device_descriptor,
                                                      got_device_descriptor, &device_descriptor);
        }
        case USB_INTERRUPT:
            os_PutStrFull(usb_event_names[event]);
            putChar(':');
            putIntHex((unsigned)event_data);
            putChar(':');
            putBlockHex(device_descriptor, sizeof(device_descriptor));
            _OS(os_NewLine);
            break;
        case USB_DEFAULT_SETUP_EVENT: {
            unsigned char i;
            for (i = 0; i < 8; i++)
                putByteHex(((unsigned char *)event_data)[i]);
            _OS(os_NewLine);
            return USB_IGNORE;
        }
        case USB_HOST_FRAME_LIST_ROLLOVER_INTERRUPT: {
            static unsigned counter;
            unsigned row, col;
            os_GetCursorPos(&row, &col);
            os_SetCursorPos(0, 8);
            putIntHex(++counter);
            os_SetCursorPos(row, col);
            break;
        }
        case USB_DEVICE_INTERRUPT:
        case USB_DEVICE_DEVICE_INTERRUPT:
        case USB_DEVICE_CONTROL_INTERRUPT:
        case USB_DEVICE_WAKEUP_INTERRUPT:
        case USB_HOST_INTERRUPT:
            break;
        default:
            os_PutStrFull(usb_event_names[event]);
            _OS(os_NewLine);
            break;
    }
    return USB_SUCCESS;
}

void main(void) {
    usb_error_t error;
    os_SetCursorPos(1, 0);
    if ((error = usb_Init(handle_usb_event, NULL, NULL, USB_DEFAULT_INIT_FLAGS)) == USB_SUCCESS) {
        while ((error = usb_WaitForInterrupt()) == USB_SUCCESS && !os_GetCSC()) {
            unsigned row, col;
            os_GetCursorPos(&row, &col);
            os_SetCursorPos(0, 0);
            putIntHex(usb_GetFrameNumber());
            os_SetCursorPos(row, col);
        }
    }
    usb_Cleanup();
    putIntHex(error);
    os_GetKey();
}
