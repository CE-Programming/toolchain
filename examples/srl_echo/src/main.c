#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>

#include <usbdrvce.h>
#include <srldrvce.h>

/* Serial device struct */
srl_device_t srl;

bool has_device = false;

/* A buffer for internal use by the serial library */
uint8_t srl_buf[512];

/* Handle USB events */
static usb_error_t handle_usb_event(usb_event_t event, void *event_data,
                                    usb_callback_data_t *callback_data __attribute__((unused))) {
    /* Enable newly connected devices */
    if(event == USB_DEVICE_CONNECTED_EVENT && !(usb_GetRole() & USB_ROLE_DEVICE)) {
        usb_device_t device = event_data;
        usb_ResetDevice(device);
    }
    /* When a device is connected, or when connected to a computer */
    if((event == USB_DEVICE_ENABLED_EVENT && !(usb_GetRole() & USB_ROLE_DEVICE)) || event == USB_HOST_CONFIGURE_EVENT) {
        if(!has_device) {
            usb_device_t device = event_data;

            /* Initialize the serial library with the newly attached device */
            srl_error_t error = srl_Init(&srl, device, srl_buf, sizeof srl_buf, SRL_INTERFACE_ANY);

            if(error) {
                /* Print the error code to the homescreen */
                char buf[64];
                sprintf(buf, "Error %u initting serial", error);

                os_ClrHome();
                os_PutStrFull(buf);
            } else {
                has_device = true;
            }
        }
    }
    if(event == USB_DEVICE_DISCONNECTED_EVENT) {
        has_device = false;
    }

    return USB_SUCCESS;
}

int main(void) {
    /* Initialize the USB driver with our event handler and the serial device descriptors */
    usb_error_t usb_error = usb_Init(handle_usb_event, NULL, srl_GetCDCStandardDescriptors(), USB_DEFAULT_INIT_FLAGS);
    if(usb_error) {
        usb_Cleanup();
        return 1;
    }

    do {
        kb_Scan();
        
        /* Call the USB event handler frequently to ensure that no data gets missed */
        usb_HandleEvents();

        if(has_device) {
            /* A buffer to store bytes read by the serial library */
            char in_buf[64];

            /* Read up to 64 bytes from serial */
            size_t bytes_read = srl_Read(&srl, in_buf, sizeof in_buf);

            /* Only write when bytes were received */
            if(bytes_read) {
                /* Write the same bytes back to the other device */
                srl_Write(&srl, in_buf, bytes_read);
            }
        }

    } while(!kb_IsDown(kb_KeyClear));

    usb_Cleanup();
    return 0;
}
