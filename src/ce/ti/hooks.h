/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS hooks.
 * The API for using hooks isn't fleshed out here, so this isn't really useful.
 */

#ifndef _TI_OS_HOOKS_H
#define _TI_OS_HOOKS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define os_CursorHookPtr     (*(uint24_t*)0xD025D5)
#define os_LibraryHookPtr    (*(uint24_t*)0xD025D8)
#define os_RawKeyHookPtr     (*(uint24_t*)0xD025DB)
#define os_GetKeyHookPtr     (*(uint24_t*)0xD025DE)
#define os_HomescreenHookPtr (*(uint24_t*)0xD025E1)
#define os_WindowHookPtr     (*(uint24_t*)0xD025E4)
#define os_GraphHookPtr      (*(uint24_t*)0xD025E7)
#define os_YEqualsHookPtr    (*(uint24_t*)0xD025EA)
#define os_FontHookPtr       (*(uint24_t*)0xD025ED)
#define os_RegraphHookPtr    (*(uint24_t*)0xD025F0)
#define os_GraphicsHookPtr   (*(uint24_t*)0xD025F3)
#define os_TraceHookPtr      (*(uint24_t*)0xD025F6)
#define os_ParserHookPtr     (*(uint24_t*)0xD025F9)
#define os_AppChangeHookPtr  (*(uint24_t*)0xD025FC)
#define os_Catalog1HookPtr   (*(uint24_t*)0xD025FF)
#define os_HelpHookPtr       (*(uint24_t*)0xD02602)
#define os_CxRedispHookPtr   (*(uint24_t*)0xD02605)
#define os_MenuHookPtr       (*(uint24_t*)0xD02608)
#define os_Catalog2HookPtr   (*(uint24_t*)0xD0260B)
#define os_TokenHookPtr      (*(uint24_t*)0xD0260E)
#define os_LocalizeHookPtr   (*(uint24_t*)0xD02611)
#define os_SilentLinkHookPtr (*(uint24_t*)0xD02614)
#define os_ActiveUSBHookPtr  (*(uint24_t*)0xD0261A)

#ifdef __cplusplus
}
#endif

#endif
