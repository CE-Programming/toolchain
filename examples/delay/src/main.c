#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void) {
    /* Clear the homescreen */
    os_ClrHome();

    /* Print the delay notice */
	os_PutStrFull("Waiting for 5s...");

	/* Delay for 5s */
	delay(5000);

    /* Print the done notice */
	os_PutStrFull("Done.");
}
