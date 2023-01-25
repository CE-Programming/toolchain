_CallFontHook              equ 0020130h
_CallLocalizeHook          equ 0020134h
_RunCursorHook             equ 00213B8h
_RunLibraryHook            equ 00213BCh
_RunRawKeyHook             equ 00213C0h
_SetCursorHook             equ 00213C4h
_SetLibraryHook            equ 00213C8h
_SetGetKeyHook             equ 00213CCh
_ClrCursorHook             equ 00213D0h
_ClrLibraryHook            equ 00213D4h
_ClrRawKeyHook             equ 00213D8h
_GetKeyHook                equ 00213DCh
_SetGetCSCHook             equ 00213E0h
_ClrGetKeyHook             equ 00213E4h
_SetCatalog2Hook           equ 00213E8h
_ClrCatalog2Hook           equ 00213ECh
_SetLocalizeHook           equ 00213F0h
_ClrLocalizeHook           equ 00213F4h
_SetTokenHook              equ 00213F8h
_ClrTokenHook              equ 00213FCh
_SetHomescreenHook         equ 0021410h
_ClrHomescreenHook         equ 0021414h
_SetWindowHook             equ 0021418h
_ClrWindowHook             equ 002141Ch
_SetGraphModeHook          equ 0021420h
_ClrGraphModeHook          equ 0021424h
_SetYeditHook              equ 0021440h
_ClrYeditHook              equ 0021444h
_SetFontHook               equ 0021454h
_ClrFontHook               equ 0021458h
_SetRegraphHook            equ 002145Ch
_ClrRegraphHook            equ 0021460h
_RunGraphingHook           equ 0021464h
_SetTraceHook              equ 0021468h
_ClrTraceHook              equ 002146Ch
_RunTraceHook              equ 0021470h
_SetParserHook             equ 002149Ch
_ClrParserHook             equ 00214A0h
_SetAppChangeHook          equ 00214A4h
_ClrAppChangeHook          equ 00214A8h
_SetGraphicsHook           equ 00214ACh
_ClrGraphicsHook           equ 00214B0h
_SetCatalog1Hook           equ 00214C4h
_ClrCatalog1Hook           equ 00214C8h
_SetHelpHook               equ 00214CCh
_ClrHelpHook               equ 00214D0h
_RunCatalog2Hook           equ 00214E0h
_RunCatalog1Hook           equ 00214E4h
_SetCxReDispHook           equ 00214F8h
_ClrCxReDispHook           equ 00214FCh
_SetMenuHook               equ 0021518h
_ClrMenuHook               equ 002151Ch
_SetSilentLinkHook         equ 0021544h
_ClrSilentLinkHook         equ 0021548h
_ChkHelpHookVer            equ 0021654h
_SetUSBActivityHook        equ 002171Ch
_ClrUSBActivityHook        equ 0021720h
_RunLocalizeHook           equ 0022098h

hookExecTemp		equ 0D025D2h
cursorHookPtr		equ 0D025D5h
libraryHookPtr		equ 0D025D8h
rawKeyHookPtr		equ 0D025DBh
getKeyHookPtr		equ 0D025DEh
homescreenHookPtr	equ 0D025E1h
windowHookPtr		equ 0D025E4h
graphHookPtr		equ 0D025E7h
yEqualsHookPtr		equ 0D025EAh
fontHookPtr		equ 0D025EDh
regraphHookPtr		equ 0D025F0h
graphicsHookPtr		equ 0D025F3h
traceHookPtr		equ 0D025F6h
parserHookPtr		equ 0D025F9h
appChangeHookPtr	equ 0D025FCh
catalog1HookPtr		equ 0D025FFh
helpHookPtr		equ 0D02602h
cxRedispHookPtr		equ 0D02605h
menuHookPtr		equ 0D02608h
catalog2HookPtr		equ 0D0260Bh
tokenHookPtr		equ 0D0260Eh
localizeHookPtr		equ 0D02611h
silentLinkHookPtr	equ 0D02614h
USBActivityHookPtr	equ 0D0261Ah

;----------------------------------------------------------------------
hookflags2		equ 34h		;also sysHookFlg
getCSCHookActive	equ 0		;1 = GetCSC hook active
libraryHookActive	equ 1		;1 = library hook active
noHookActive		equ 2		;1 = same as 0; never used by OS
homescreenHookActive	equ 4		;1 = homescreen hook active
rawKeyHookActive	equ 5		;1 = raw key hook active
catalog2HookActive	equ 6		;1 = catalog 2 hook active
cursorHookActive	equ 7		;1 = cursor hook active
;----------------------------------------------------------------------
hookflags3		equ 35h		;also sysHookFlg1
tokenHookActive		equ 0		;1 = token hook active
localizeHookActive	equ 1		;1 = localize hook active
windowHookActive	equ 2		;1 = window hook active
graphHookActive		equ 3		;1 = graph hook active
yEquHookActive		equ 4		;1 = Y= hook active
fontHookActive		equ 5		;1 = font hook active
regraphHookActive	equ 6		;1 = regraph hook active
drawingHookActive	equ 7		;1 = drawing hook active
;----------------------------------------------------------------------
hookflags4		equ 36h		;also sysHookFlag2
traceHookActive		equ 0		;1 = trace hook active
parserHookActive	equ 1		;1 = parser hook active
appChangeHookActive	equ 2		;1 = app change hook active
catalog1HookActive	equ 3		;1 = catalog 1 hook active
helpHookActive		equ 4		;1 = help hook active
cxRedispHookActive	equ 5		;1 = cxRedisp hook active
menuHookActive		equ 6		;1 = menu hook active
silentLinkHookActive	equ 7		;1 = silent link hook active
;----------------------------------------------------------------------
;hookflags2Override	equ 37h		;set corresponding bit to kill iy+35h hook when executing app
;----------------------------------------------------------------------
;hookflags3Override	equ 38h		;set corresponding bit to kill iy+36h hook when executing app
;----------------------------------------------------------------------
;hookflags4Override	equ 39h		;set corresponding bit to kill iy+37h hook when executing app
;----------------------------------------------------------------------
hookflags5		equ 3Ah
usbActivityHookActive	equ 0		;1 = USB activity hook active
;----------------------------------------------------------------------
extraHookFlags		equ 3Eh
checkCatalog2HookVer	equ 3		;1 = check catalog 2 hook's version before executing it (and error or take other action if so)
openLibActive		equ 4		;1 = OpenLib( was successfully called on a Flash application (ExecLib will error if zero)