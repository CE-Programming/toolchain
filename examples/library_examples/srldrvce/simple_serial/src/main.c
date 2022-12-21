/*
 *--------------------------------------
 * Program Name:
 * Author:
 * License:
 * Description:
 *--------------------------------------
*/

#include <keypadc.h>
#include <sys/timers.h>
#include <string.h>
#include <stdio.h>

#include "simple_serial.h"

int main(void)
{
    int counter = 0;
    serial_Begin(9600);

    do {
        kb_Scan();
        if (kb_IsDown(kb_KeyEnter)) {
            const char *hello = "Hello world\n";
            serial_Write(hello, strlen(hello));

            counter++;
            serial_printf("The enter key has been pressed %i times.\n", counter);
            delay(100);
        }

        char buf[50];
        int bytes_read = serial_Read(buf, sizeof buf);
        printf("%*.s", bytes_read, buf);
    } while (!kb_IsDown(kb_KeyClear));

    serial_End();
    return 0;
}
