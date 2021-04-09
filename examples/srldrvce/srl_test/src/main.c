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
bool ring_buf_update_read_(ring_buf_ctrl_t *rbuf, size_t size, uint8_t region);
void ring_buf_update_write_(ring_buf_ctrl_t *rbuf, size_t size);

void print_ring_buf(const ring_buf_ctrl_t *rbuf) {
    dbg_printf("  buf_start: %p\n", rbuf->buf_start);
    dbg_printf("  buf_end: %p\n", rbuf->buf_end);
    dbg_printf("  data_start: %p\n", rbuf->data_start);
    dbg_printf("  data_break: %p\n", rbuf->data_break);
    dbg_printf("  data_end: %p\n", rbuf->data_end);
    dbg_printf("  dma_active: %i\n", rbuf->dma_active);
}

void print_srl_dev(const srl_device_t *srl) {
    dbg_printf("dev: %p\n", srl->dev);
    dbg_printf("rx_addr: %x\n", srl->rx_addr);
    dbg_printf("tx_addr: %x\n", srl->tx_addr);
    dbg_printf("type: %i\n", srl->type);
    dbg_printf("subtype: %i\n", srl->subtype);
    dbg_printf("tx_buf:\n");
    print_ring_buf(&srl->tx_buf);
    dbg_printf("rx_buf:\n");
    print_ring_buf(&srl->rx_buf);
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

size_t ring_buf_avail(ring_buf_ctrl_t *rbuf) {
    if(rbuf->data_break) {
        return rbuf->data_break - rbuf->data_start +
               rbuf->data_end - rbuf->buf_start;
    } else {
        return rbuf->data_end - rbuf->data_start;
    }
}

size_t ring_buf_contig_avail(ring_buf_ctrl_t *rbuf) {
    if(rbuf->data_break) {
        return rbuf->data_break - rbuf->data_start;
    } else {
        return rbuf->data_end - rbuf->data_start;
    }
}

bool ring_buf_has_consecutive_region(ring_buf_ctrl_t *rbuf, uint8_t size) {
    if(rbuf->data_break) {
        return size < rbuf->data_start - rbuf->data_end;
    } else {
        return size < rbuf->buf_end - rbuf->data_end;
    }
}

size_t ring_buf_push(ring_buf_ctrl_t *rbuf, void *data, size_t size) {
    if(rbuf->data_break) {
        size_t len = rbuf->data_start - rbuf->data_end;
        if(len > size) len = size;
        memcpy(rbuf->data_end, data, len);
        rbuf->data_end += len;
        return len;
    } else {
        if(rbuf->data_end + size > rbuf->buf_end) {
            size_t len = rbuf->buf_end - rbuf->data_end;
            memcpy(rbuf->data_end, data, len);
            rbuf->data_break = rbuf->buf_end;
            rbuf->data_end = rbuf->buf_start;
            return len + ring_buf_push(rbuf, data + len, size - len);
        } else {
            memcpy(rbuf->data_end, data, size);
            rbuf->data_end += size;
            return size;
        }
    }
}

size_t ring_buf_pop(ring_buf_ctrl_t *rbuf, void *data, size_t size) {
    if(rbuf->data_break) {
        if(rbuf->data_start + size > rbuf->data_break) {
            size_t len = rbuf->data_break - rbuf->data_start;
            memcpy(data, rbuf->data_start, len);
            rbuf->data_start = rbuf->buf_start;
            rbuf->data_break = NULL;
            return len + ring_buf_pop(rbuf, data + len, size - len);
        } else {
            memcpy(data, rbuf->data_start, size);
            rbuf->data_start += size;
            return size;
        }
    } else {
        size_t len = rbuf->data_end - rbuf->data_start;
        if(len > size) len = size;
        memcpy(data, rbuf->data_start, len);
        rbuf->data_start += len;
        return len;
    }
}

bool ring_buf_update_read(ring_buf_ctrl_t *rbuf, size_t size, uint8_t region) {
    rbuf->data_end += size;
    if(!rbuf->data_break && rbuf->buf_end - rbuf->data_end < region) {
        rbuf->data_break = rbuf->data_end;
        rbuf->data_end = rbuf->buf_start;
    }
    return !rbuf->data_break || rbuf->data_start - rbuf->data_end <= region;
}

void ring_buf_update_write(ring_buf_ctrl_t *rbuf, size_t size) {
    rbuf->data_start += size;
    if(rbuf->data_start == rbuf->data_break) {
        rbuf->data_start = rbuf->buf_start;
        rbuf->data_break = NULL;
    }
}

void test_rbuf(void) {
    char buffer[500];
    ring_buf_ctrl_t ctrl = {
        buffer,
        &buffer[sizeof buffer],
        buffer,
        NULL,
        buffer,
        false
    };
}

int main(void) {
    test_rbuf();
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
