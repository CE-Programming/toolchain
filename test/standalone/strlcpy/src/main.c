#include <ti/getcsc.h>
#include <ti/screen.h>
#include <stdio.h>
#include <string.h>

void test_strlcpy_impl(size_t size) {
    char string[] = "Hello there, Venus";
    char buffer[20] = "xxxxxxxxxxxxxxxxxxx";
    size_t r = strlcpy(buffer, string, size);
    size_t len = strlen(buffer);

    printf("Source: '%s', size: %d, buffer: '%s', len: %d, result: %d\n",
           string, size, buffer, len, r);
}


void test_strlcpy_impl_empty_src(size_t size) {
    char string[] = "";
    char buffer[20] = "xxxxxxxxxxxxxxxxxxx";
    size_t r = strlcpy(buffer, string, size);
    size_t len = strlen(buffer);

    printf("Source: '%s', size: %d, buffer: '%s', len: %d, result: %d\n",
           string, size, buffer, len, r);
}


/* Main function, called first */
int main(void)
{
    /* Clear the homescreen */
    os_ClrHome();

    /* Print a string */

    printf("Testing strlcpy...\n\n");

    test_strlcpy_impl(19);
    test_strlcpy_impl(10);

    while (!os_GetCSC()) {};

    test_strlcpy_impl(1);
    test_strlcpy_impl(0);

    while (!os_GetCSC()) {};

    test_strlcpy_impl_empty_src(10);
    test_strlcpy_impl_empty_src(1);

    printf("all done!\n");

    /* Waits for a key */
    while (!os_GetCSC());

    /* Return 0 for success */
    return 0;
}
