#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <keypadc.h>

#define usb_callback_data_t usb_device_t

#include <usbdrvce.h>
#include <srldrvce.h>

/* Handle USB events */
static usb_error_t handle_usb_event(usb_event_t event, void *event_data,
								  usb_callback_data_t *callback_data) {
	/* When a device is connected, or when connected to a computer */
	if(event == USB_DEVICE_CONNECTED_EVENT || event == USB_HOST_CONFIGURE_EVENT) {
		if(!*callback_data) {
			/* Set the USB device */
			*callback_data = event_data;
		}
	}

	/* When a device is disconnected */
	if(event == USB_DEVICE_DISCONNECTED_EVENT) {
		*callback_data = NULL;
	}

	return USB_SUCCESS;
}

void main(void) {
	usb_error_t usb_error;
	srl_error_t srl_error;

	usb_device_t usb_device = NULL;
	srl_device_t srl;

	/* A buffer for internal use by the serial library */
	uint8_t srl_buf[512];

	/* Initialize the USB driver with our event handler and the serial device descriptors */
	usb_error = usb_Init(handle_usb_event, &usb_device, srl_GetCDCStandardDescriptors(), USB_DEFAULT_INIT_FLAGS);
	if(usb_error) goto exit;

	/* Wait for a USB device to be connected */
	while(!usb_device) {
		kb_Scan();

		/* Exit if clear is pressed */
		if(kb_IsDown(kb_KeyClear)) {
			goto exit;
		}
		/* Handle any USB events that have occured */
		usb_HandleEvents();
	}

	/* Initialize the serial library with the USB device */
	srl_error = srl_Init(&srl, usb_device, srl_buf, sizeof(srl_buf), SRL_INTERFACE_ANY);
	if(srl_error) goto exit;

	do {
		/* A buffer to store bytes read by the serial library */
		char in_buf[64];
		size_t bytes_read;

		kb_Scan();
		usb_HandleEvents();

		/* If the device was disconnected, exit */
		if(!usb_device) break;

		/* Read up to 64 bytes from serial */
		bytes_read = srl_Read(&srl, in_buf, sizeof(in_buf));

		/* Only write when bytes were received */
		if(bytes_read) {
			/* Write the same bytes back to the other device */
			srl_Write(&srl, in_buf, bytes_read);
		}

	} while(!kb_IsDown(kb_KeyClear));

	exit:
    usb_Cleanup();
}
