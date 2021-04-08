/*
 *--------------------------------------
 * Program Name:
 * Author:
 * License:
 * Description:
 *--------------------------------------
*/

#include <srldrvce.h>

#include <debug.h>
#include <keypadc.h>
#include <stdbool.h>
#include <string.h>
#include <tice.h>

void get_device_type_(srl_device_t *srl);
void get_endpoint_addresses_(srl_device_t *srl);
size_t ring_buf_avail_(ring_buf_ctrl_t *rbuf);
bool ring_buf_has_consecutive_region_(ring_buf_ctrl_t *rbuf, uint8_t size);
size_t ring_buf_push_(ring_buf_ctrl_t *rbuf, void *data, size_t size);
size_t ring_buf_pop_(ring_buf_ctrl_t *rbuf, void *data, size_t size);
void ring_buf_update_(ring_buf_ctrl_t *rbuf, size_t size, uint8_t region);

void print_srl_dev(const srl_device_t *srl) {
   dbg_printf("dev: %p\n", srl->dev);
   dbg_printf("rx_addr: %x\n", srl->rx_addr);
   dbg_printf("tx_addr: %x\n", srl->tx_addr);
   dbg_printf("type: %i\n", srl->type);
   dbg_printf("subtype: %i\n", srl->subtype);
   dbg_printf("tx_buf.buf_start: %p\n", srl->tx_buf.buf_start);
   dbg_printf("tx_buf.buf_size: %i\n", srl->tx_buf.buf_size);
   dbg_printf("tx_buf.data_start: %p\n", srl->tx_buf.data_start);
   dbg_printf("tx_buf.data_break: %p\n", srl->tx_buf.data_break);
   dbg_printf("tx_buf.data_end: %p\n", srl->tx_buf.data_end);
   dbg_printf("tx_buf.dma_active: %i\n", srl->tx_buf.dma_active);
   dbg_printf("rx_buf.buf_start: %p\n", srl->rx_buf.buf_start);
   dbg_printf("rx_buf.buf_size: %i\n", srl->rx_buf.buf_size);
   dbg_printf("rx_buf.data_start: %p\n", srl->rx_buf.data_start);
   dbg_printf("rx_buf.data_break: %p\n", srl->rx_buf.data_break);
   dbg_printf("rx_buf.data_end: %p\n", srl->rx_buf.data_end);
   dbg_printf("rx_buf.dma_active: %i\n", srl->rx_buf.dma_active);
}

srl_device_t srl;

bool has_device = false;

uint8_t srl_buf[512];

static usb_error_t handle_usb_event(usb_event_t event, void *event_data,
                                    usb_callback_data_t *callback_data __attribute__((unused))) {
   /* Enable newly connected devices */
   if(event == USB_DEVICE_CONNECTED_EVENT && !(usb_GetRole() & USB_ROLE_DEVICE)) {
       usb_device_t device = event_data;
       printf("device connected\n");
       usb_ResetDevice(device);
   }
   /* When a device is connected, or when connected to a computer */
   if((event == USB_DEVICE_ENABLED_EVENT && !(usb_GetRole() & USB_ROLE_DEVICE)) || event == USB_HOST_CONFIGURE_EVENT) {
       if(!has_device) {
           usb_device_t device = event_data;
           printf("device enabled\n");

           /* Initialize the serial library with the newly attached device */
           srl_error_t error = srl_Open(&srl, device, srl_buf, sizeof srl_buf, SRL_INTERFACE_ANY, 9600);

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
       srl_Close(&srl);
       has_device = false;
   }

   return USB_SUCCESS;
}

void test_rbuf(void) {
    char buffer[500];
    ring_buf_ctrl_t ctrl = {
        buffer,
        sizeof buffer,
        buffer,
        NULL,
        buffer,
        false
    };
}

int main(void) {
    //os_ClrHome();
    //const usb_standard_descriptors_t *default_desc = (void*)(((struct{char b; void *addr;}*)usb_RepeatTimerCycles)->addr + 16);
    const usb_standard_descriptors_t *desc = srl_GetCDCStandardDescriptors();
    /* Initialize the USB driver with our event handler and the serial device descriptors */
    //usb_error_t usb_error = 
    usb_Init(handle_usb_event, NULL, desc, USB_DEFAULT_INIT_FLAGS);
    //if(usb_error) {
    //    usb_Cleanup();
    //    printf("usb init error %u\n", usb_error);
    //    do kb_Scan(); while(!kb_IsDown(kb_KeyClear));
    //    return 1;
    //}

    do {
        kb_Scan();
        
        usb_HandleEvents();

        // if(has_device) {
        //    char in_buf[64];

        //    size_t bytes_read = srl_Read(&srl, in_buf, sizeof in_buf);

        //    if(bytes_read) {
        //        srl_Write(&srl, in_buf, bytes_read);
        //    }
        // }

    } while(!kb_IsDown(kb_KeyClear));

    usb_Cleanup();
    return 0;
}
