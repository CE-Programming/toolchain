#include <usbdrvce.h>

#include <tice.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

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
    usb_RepeatTimerMs(usbTimer, myTimer->interval);
    return USB_SUCCESS;
}

#define NUM_TIMERS 4

int main() {
    int i;
    bool done;
    my_timer_t myTimers[NUM_TIMERS];

    os_ClrHomeFull();
    if (usb_Init(NULL, NULL, NULL, USB_DEFAULT_INIT_FLAGS) != USB_SUCCESS) {
        return 1;
    }

    for (i = 0; i != NUM_TIMERS; i++) {
        myTimers[i].usbTimer.handler = my_timer_handler;
        myTimers[i].interval = 1000u >> i;
        myTimers[i].counter = 10u << i;
        usb_StartTimerMs(&myTimers[i].usbTimer, myTimers[i].interval);
    }

    do {
        done = true;
        for (i = 0; i != NUM_TIMERS; i++) {
            char string[3];
            os_SetCursorPos(i, 0);
            sprintf(string, "%2u", myTimers[i].counter);
            os_PutStrFull(string);
            if (myTimers[i].counter != 0) {
                done = false;
            }
        }
    } while (usb_WaitForEvents() == USB_SUCCESS && !done);

    usb_Cleanup();
}
