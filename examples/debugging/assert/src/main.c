/* static_assert and assert are both included from assert.h */
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <ti/screen.h>
#include <ti/getkey.h>

/* static_assert is a compile time assert that can appear outside a function body ... */
static_assert(sizeof(int) == 3, "Expecting int to be 24 bits.");

int main(void)
{
    typedef struct some_struct {
        char a;
        int b, c;
    } some_struct_t;
    /* ... or inside one! */
    static_assert(offsetof(some_struct_t, c) == 4, "Expecting member c of some_struct_t to be at offset 4.");

    uint16_t key;
    char str[13];

    os_ClrHome();
    os_SetCursorPos(0, 0);
    os_PutStrFull("Please don't quit me! :(");

    /* Wait for the enter key to quit */
    do
    {
        key = os_GetKey();

        /* assert does nothing and compiles to no code when you make normally.
           However when you make debug, it logs an error to the CEmu console and
           quits the program if passed a false condition. Adding a string after
           the condition with && is a standard hack to allow printing arbitrary
           text to the console, along with the condition, if the assert fails. */
        assert((key != k_Quit) && "Not expecting quit to be pressed.");

        sprintf(str, "key = 0x%04hX", key);
        os_SetCursorPos(1, 0);
        os_PutStrFull(str);
    }
    while (key != k_Clear);

    return 0;
}
