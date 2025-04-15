#include <stdbool.h>
#include <stdint.h>

// From <ti/error.h>
int os_PushErrorHandler(void) __attribute__((returns_twice));
void os_PopErrorHandler(void);
// From <ti/vars.h>
#define os_OP1   ((uint8_t*)0xD005F8)
#define os_Flags ((uint8_t*)0xD00080)

void os_DelVarArc(void *entry, void *data)
{
    int clobber_hl, clobber_de;
    asm volatile (
        "call 021434h\n"    // DelVarArc
        : "=l" (clobber_hl),
          "=e" (clobber_de)
        : [hl] "l" (entry),
          [de] "e" (data),
          [flags] "iyl" (os_Flags)
        : "cc", "a", "bc", "ix", "iy"
    );
}

bool arcUnarcVariable(uint8_t varType, uint8_t nameLen, const char *name)
{
    const int err = os_PushErrorHandler();
    if (err) {
        // dbg_printf("[ERROR caught] [arcUnarcVariable] errno = %d\n", err);
        return false;
    }
    *(os_OP1) = varType;
    __builtin_memcpy((char*)(os_OP1+1), name, nameLen);
    *(os_OP1+1+nameLen) = '\0';
    asm volatile (
        "call 021448h\n"    // Arc_Unarc
        :
        : [flags] "iyl" (os_Flags)
        : "cc", "a", "bc", "de", "hl", "ix", "iy"
    );
    os_PopErrorHandler();
    return true;
}
