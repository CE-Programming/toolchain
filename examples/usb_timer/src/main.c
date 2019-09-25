#include <usbdrvce.h>

#include <tice.h>

#include <stddef.h>

typedef struct my_timer {
    usb_timer_t usbTimer;
    unsigned interval;
    unsigned counter;
} my_timer_t;

usb_error_t my_timer_handler(usb_timer_t *usbTimer) {
    my_timer_t *myTimer = (my_timer_t *)usbTimer;
    if (myTimer->counter != 0) {
        myTimer->counter -= 1;
    }
    usb_RepeatTimer(&myTimer, myTimer->interval);
    return USB_SUCCESS;
}

#define N 4

void main() {
    os_ClrHomeFull();
    if (usb_Init(NULL, NULL, NULL, USB_DEFAULT_INIT_FLAGS) == USB_SUCCESS) {
        my_timer_t myTimers[N];
        int i;
        for (i = 0; i != N; i++) {
            myTimers[i].usbTimer.handler = my_timer_handler;
            myTimers[i].interval = 1000u >> i;
            myTimers[i].counter = 10u << i;
            usb_StartTimer(&myTimers[i], myTimers[i].interval);
        }
        while (usb_WaitForEvents() == USB_SUCCESS) {
            for (i = 0; i != N; i++) {
                char string[3];
                os_SetCursorPos(i, 0);
                sprintf(string, "%2u", myTimers[i].counter);
                os_PutStringFull(string);
            }
            for (i = 0; i != N; i++) {
                if (myTimers[i].counter != 0) {
                    continue;
                }
            }
            break;
        }
        usb_Cleanup();
    }
}
