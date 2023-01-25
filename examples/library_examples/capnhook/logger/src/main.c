#include <capnhook.h>
#include <string.h>

#include <debug.h>

extern hook_t hook;
extern size_t hook_size;
extern char type_name_buffer[16];

char *type_names[] = {
    "CURSOR",
    "LIBRARY",
    "RAW_KEY",
    "GET_CSC",
    "HOMESCREEN",
    "WINDOW",
    "GRAPH",
    "Y_EQUALS",
    "FONT",
    "REGRAPH",
    "GRAPHICS",
    "TRACE",
    "PARSER",
    "APP_CHANGE",
    "CATALOG1",
    "HELP",
    "CX_REDISP",
    "MENU",
    "CATALOG2",
    "TOKEN",
    "LOCALIZE",
    "SILENT_LINK",
    "USB_ACTIVITY",
};

void main() {
    for(hook_type_t type = 0; type < HOOK_NUM_TYPES; type++) {
        if(type == HOOK_TYPE_LOCALIZE) continue;
        if(type == HOOK_TYPE_FONT) continue;
        if(type == HOOK_TYPE_RAW_KEY) continue;
        if(type == HOOK_TYPE_GET_CSC) continue;
        if(type == HOOK_TYPE_CURSOR) continue;
        if(type == HOOK_TYPE_MENU) continue;
        strcpy(type_name_buffer, type_names[type]);
        hook_error_t err = hook_Install(0xFF0000 + type, &hook, hook_size, type, 5, "Hook call logger");
        dbg_sprintf(dbgout, "Err %u\n", err);
    }
    hook_Sync();
}
