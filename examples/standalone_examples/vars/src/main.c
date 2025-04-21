#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <ti/getcsc.h>
#include <ti/screen.h>
#include <ti/vars.h>
#include <debug.h>

#define MY_LIST_NAME "\x5DTESTL"

struct Counters
{
    unsigned int ram;
    unsigned int flash;
};

// Those can't be deleted.
static bool isInternalVar(uint8_t varType, const char* name)
{
    return !strcmp(name, "#")
        || (varType == OS_TYPE_EQU  && !strcmp(name, "."))
        || (varType == OS_TYPE_PRGM && !strcmp(name, "!"));
}

// Walk through the VAT, debug-prints some info about the entries, and returns the number of entries seen
static struct Counters walkVAT(void)
{
    void* vatStart = os_GetSymTablePtr();
    void* nextEntry = NULL;
    void* entry = vatStart;
    uint24_t varType = 0, nameLen = 0;
    char name[9] = {0};
    void* data = NULL;
    struct Counters counters = { 0, 0 };

    while (entry)
    {
        nextEntry = os_NextSymEntry(entry, &varType, &nameLen, name, &data);

        const bool isArchived = (uintptr_t)data < (uintptr_t)os_RamStart;
        const bool isNamed = entry <= *(void**)0xD0259D; // progPtr
        const bool isInternal = isInternalVar(varType, name);
        const uint8_t* actualDataAddr = isArchived ? (data + 9 + isNamed + nameLen) : data;

        if (isArchived) {
            counters.flash++;
        } else {
            counters.ram++;
        }

        dbg_printf("%s%s entry %p (data @ %06X ; actual data @ %06X) : [type %02X] [namelen %d] \"%s\"\n",
                    isArchived ? "Archived" : "RAM", isInternal ? " internal" : "", entry, (uintptr_t)data,
                    (uintptr_t)actualDataAddr, varType, nameLen, name);

        entry = nextEntry;
    }

    return counters;
}

int main(void)
{
    static char buf[31] = {0};

    os_ClrHome();

    struct Counters countersBefore = walkVAT();
    dbg_printf("before: %d R / %d F", countersBefore.ram, countersBefore.flash);
    os_PutStrFull("Before creating list");
    os_NewLine();
    os_NewLine();
    while (!os_GetCSC());

    int ret = 0;
    ret = os_SetListDim(MY_LIST_NAME, 10);
    dbg_printf("os_SetListDim ret = %d\n", ret);
    assert(ret == 0);
    os_PutStrFull("Created. ");

    void *entry, *data;
    ret = os_ChkFindSym(OS_TYPE_REAL_LIST, MY_LIST_NAME, &entry, &data);
    dbg_printf("os_ChkFindSym ret = %d. entry = %p, data = %p\n", ret, entry, data);
    assert(ret == 1);

    struct Counters countersAfter = walkVAT();
    dbg_printf("created: %d R / %d F", countersAfter.ram, countersAfter.flash);
    snprintf(buf, 30, "Diff %dR %dF", countersAfter.ram - countersBefore.ram, countersAfter.flash - countersBefore.flash);
    os_PutStrFull(buf);
    os_NewLine();
    while (!os_GetCSC());

    bool archived = arcUnarcVariable(OS_TYPE_REAL_LIST, sizeof(MY_LIST_NAME)-1, MY_LIST_NAME);
    assert(archived);
    os_PutStrFull("Archived. ");

    struct Counters countersArchived = walkVAT();
    dbg_printf("archived: %d R / %d F", countersArchived.ram, countersArchived.flash);
    snprintf(buf, 30, "Diff %dR %dF", countersArchived.ram - countersAfter.ram, countersArchived.flash - countersAfter.flash);
    os_PutStrFull(buf);
    os_NewLine();
    while (!os_GetCSC());

    ret = os_ChkFindSym(OS_TYPE_REAL_LIST, MY_LIST_NAME, &entry, &data);
    dbg_printf("os_ChkFindSym ret = %d. entry = %p, data = %p\n", ret, entry, data);
    assert(ret == 1);

    os_DelVar(entry);

    ret = os_ChkFindSym(OS_TYPE_REAL_LIST, MY_LIST_NAME, &entry, &data);
    dbg_printf("os_ChkFindSym ret = %d. entry = %p, data = %p\n", ret, entry, data);
    assert(ret == 0);
    os_PutStrFull("Deleted. ");

    struct Counters countersDeleted = walkVAT();
    dbg_printf("deleted: %d R / %d F", countersDeleted.ram, countersDeleted.flash);
    snprintf(buf, 30, "Diff %dR %dF", countersDeleted.ram - countersArchived.ram, countersDeleted.flash - countersArchived.flash);
    os_PutStrFull(buf);

    while (!os_GetCSC());
    return 0;
}
