#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <assert.h>
#include <debug.h>

/*
 * Even though debug.h has prototypes for Debugger, SetWriteWatchpoint, SetWatchpoint, RemoveWatchpoint, RemoveAllWatchpoints, RemoveAllBreakpoints...
 * you have to use the dbg_ prefix as shown here:
 */

void main(void) {
    /* Set the intial value of some variables */
    int dbg_test_var_1 = 10;
    uint8_t dbg_test_var_2 = 3;

    /* Print a simple debugging string */
    dbg_sprintf(dbgout, "This is the start of a CEmu debugging test\n");

    /* You can enter the debugger manually */
    dbg_Debugger();

    /* Set a watchpoint that will break anytime we write/change this varaible */
    dbg_SetWriteWatchpoint(&dbg_test_var_1, sizeof dbg_test_var_1);

    /* Set a non breaking watchpoint just so we can see what is in this variable at any given time */
    dbg_SetWatchpoint(&dbg_test_var_2, sizeof dbg_test_var_2);

    /* Now, let's write to the varaible to see what happens (Go to the 'Watchpoints' tab in CEmu to view the status) */
    dbg_test_var_1 = 5;

    /* Remove the watchpoint that we had set */
    dbg_RemoveWatchpoint(&dbg_test_var_1);
    dbg_RemoveWatchpoint(&dbg_test_var_2);

    /* We can also use those */
    dbg_RemoveAllWatchpoints();
    dbg_RemoveAllBreakpoints();

    /* Set this value to zero */
    dbg_test_var_2 = 0;

    /* Fail this assertion */
    assert(dbg_test_var_2);
}
