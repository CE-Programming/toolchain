/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS flags
 */

#ifndef TI_FLAGS_H
#define TI_FLAGS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set a particular OS flag
 *
 * @param[in] offset Offset to particular flag in list
 * @param[in] set Bitmask of flag to set
 */
void os_SetFlagByte(int offset, uint8_t set);

/**
 * Get a particular OS flag
 *
 * @param[in] offset Offset to particular flag in list
 * @returns Bitmask of flag
 */
uint8_t os_GetFlagByte(int offset);

/**
 * Check OS flag bits
 *
 * @param offset_pattern High 8 is unsigned offset, low 8 is bits to test
 * @returns 1 if set, 0 if not set
 */
int os_TestFlagBits(uint16_t offset_pattern);

/**
 * Set OS flag bits
 *
 * @param offset_pattern High 8 is unsigned offset, low 8 is bits to test
 */
void os_SetFlagBits(int16_t offset_pattern);

/**
 * Clear OS flag bits
 *
 * @param offset_pattern High 8 is unsigned offset, low 8 is bits to test
 */
void os_ResetFlagBits(int16_t offset_pattern);

/**
 * Faster (and worse) test of OS flag bits
 *
 * @param offset_pattern High 8 is unsigned offset, low 8 is bits to test
 * @warning Has a bug if bits and flags are all set!
 * @note This function is only available on OS 5.3.6 or later.
 */
bool os_TestFlagBitsFast(uint16_t offset_pattern);

/**
 * Converts a flag group name and member ID to a literal.
 * The `flag_` prefix is automatically taken care of.
 * 
 * For example, `OS_FLAG_ID(INDIC, ENABLE)` 
 * 
 * @param[in] GROUP Flag group name without the `OS_FLAG_` prefix
 * @param[in] MEMBER Flag item name without the `OS_FLAG_GROUP_` prefix
 */
#define OS_FLAG_ID(GROUP, MEMBER) (((OS_FLAGS_ ## GROUP) << 8) | (1 << (OS_FLAGS_ ## GROUP ## _ ## MEMBER)))

/**
 * Sets an OS flag to 1.  The `OS_FLAGS_` prefix and group prefix are added automatically for you.
 * 
 * For example, instead of:
 * 
 * @code{.cpp}
 * os_SetFlagByte(OS_FLAGS_INDIC, OS_FLAGS_INDIC_ENABLE);
 * @endcode
 * 
 * you can do:
 * 
 * @code{.cpp}
 * os_SetFlag(INDIC, ENABLE);
 * @endcode
 * 
 */
#define os_SetFlag(GROUP, MEMBER) os_SetFlagBits(OS_FLAG_ID(GROUP, MEMBER))

/**
 * Clears an OS flag to 0.
 * 
 * @see os_SetFlag
 */
#define os_ResetFlag(GROUP, MEMBER) os_ResetFlagBits(OS_FLAG_ID(GROUP, MEMBER))

/**
 * Checks if an OS flag is set.
 * 
 * @see os_SetFlag
 */
#define os_TestFlag(GROUP, MEMBER) (0 < os_TestFlagBits(OS_FLAG_ID(GROUP, MEMBER)))

#define OS_FLAGS_TRIG                      0 /**< GROUP: Trig-related */
#define OS_FLAGS_TRIG_DEGREES              2 /**< Set for degrees, reset for radians */
#define OS_FLAGS_KBD                       0 /**< GROUP: Keyboard scan control */
#define OS_FLAGS_KBD_SCR                   3 /**< Scan Code Read */
#define OS_FLAGS_KBD_KEYPRESS              4 /**< Set if a key press is in the key press buffer. @see `os_KbdScanCode` in  `<ti/getcsc.h>` */
#define OS_FLAGS_DONE                      0 /**< GROUP: "Done" */
#define OS_FLAGS_DONE_PRGM                 5 /**< Show "Done" after program exits */
#define OS_FLAGS_EDIT                      1 /**< GROUP: OS edit buffer */
#define OS_FLAGS_EDIT_OPEN                 2 /**< Set if an edit buffer is open */
#define OS_FLAGS_ANS                       1 /**< GROUP: Ans variable flags */
#define OS_FLAGS_ANS_SCROLL                3 /**< Set if viewing Ans can scroll, must be reset to move cursor in edit buffer */
/**
 * GROUP: System monitor.
 * You generally should not mess with the system monitor unless you're writing a flash application that
 * integrates with the OS.
 * And we can't sign flash applications.
 */
#define OS_FLAGS_MON                       1
#define OS_FLAGS_MON_ABANDON               4 /**< Don't start any long process in put away routine */
#define OS_FLAGS_PLOT                      2 /**< GROUP: Plot screen */
#define OS_FLAGS_PLOT_LOC                  1 /**< 0=bkup and display, 1=display only.  By default, this memory is part of the C heap. */
#define OS_FLAGS_PLOT_DISP                 2 /**< 1=plot is in display, 0=text in display, this also indicates whether graph is being shown or not */
#define OS_FLAGS_GRFMODE                   2 /**< GROUP: Graph mode */
#define OS_FLAGS_GRFMODE_FUNC              4 /**< Standard function graph Y=f(x) */
#define OS_FLAGS_GRFMODE_POLAR             5 /**< Polar graph mode */
#define OS_FLAGS_GRFMODE_PARAM             6 /**< Parametric graph mode */
#define OS_FLAGS_GRFMODE_RECUR             7 /**< Sequence graph mode */
#define OS_FLAGS_GRAPH                     3 /**< GROUP: Graph screen */
#define OS_FLAGS_GRAPH_DRAW                0 /**< Redraw graph screen.  On exit, this is automatically set by the C runtime. */
#define OS_FLAGS_GRAPH_CURSOR              2
#define OS_FLAGS_GRF                       4 /**< GROUP: Graph screen format */
#define OS_FLAGS_GRF_DOT                   0 /**< Draw dots instead of connecting points */
#define OS_FLAGS_GRF_SIMUL                 1 /**< Draw all graphs simultaneously */
#define OS_FLAGS_GRF_GRID                  2 /**< Display grid */
#define OS_FLAGS_GRF_POLAR                 3 /**< Display polar coordinates */
#define OS_FLAGS_GRF_NOCOORD               4 /**< Hide coordinates */
#define OS_FLAGS_GRF_NOAXIS                5 /**< Hide X and Y axes */
#define OS_FLAGS_GRF_LABEL                 6 /**< Show axis labels */
#define OS_FLAGS_TEXT                      5 /**< GROUP: Text display */
#define OS_FLAGS_TEXT_ERASEBELOW           1 /**< Erase line below small char */
#define OS_FLAGS_TEXT_SCROLLED             2 /**< Screen has scrolled */
#define OS_FLAGS_TEXT_INVERSE              3 /**< Text in inverse color */
#define OS_FLAGS_TEXT_INSMODE              4 /**< Insert mode */
#define OS_FLAGS_PARSER                    6 /**< GROUP: Parser (for BASIC and equations).  No useful equates for C programs. */
#define OS_FLAGS_PARSER2                   7 /**< GROUP: Parser */
#define OS_FLAGS_PARSER2_NUMOP1            0 /**< Signals a result in OP1 */
#define OS_FLAGS_NEWDISPF                  8 /**< GROUP: Derivative mode */
#define OS_FLAGS_NEWDISPF_PRECLRFORMODE    0 /**< 1=HELP BLINK ON MODE SCREEN */
#define OS_FLAGS_NEWDISPF_ALLOWPROGTOKENS  1 /**< 1=allow programming tokens to be parsed in BASIC programs */
#define OS_FLAGS_APD                       8 /**< GROUP: Automatic Power-Down */
#define OS_FLAGS_APD_ABLE                  2 /**< Enable APD */
#define OS_FLAGS_APD_RUNNING               3 /**< APD timer active */
#define OS_FLAGS_APD_WARMSTART             4 /**< 1=calculator is turning on from APD or power loss */
#define OS_FLAGS_ON                        9 /**< GROUP: On key */
#define OS_FLAGS_ON_PARSEINPUT             1 /**< 1=parse input when done */
#define OS_FLAGS_ON_RUNNING                3 /**< "1=calculator is running" is literally all TI wrote */
/**
 * On key has been pressed at some point.
 * If this is set, ERR:BREAK will be displayed when the program exits.
 * This is automatically cleared by the C runtime on exit.
 */
#define OS_FLAGS_ON_INTERRUPT              4
#define OS_FLAGS_STATS                     9 /**< GROUP: Statistics */
#define OS_FLAGS_STATS_VALID               6 /**< Reset to recompute stat vars */
#define OS_FLAGS_FMT                       0x0A /**< GROUP: Numeric format */
#define OS_FLAGS_FMT_EXPONENT              0 /**< 1=show exponent, 0=no exponent */
#define OS_FLAGS_FMT_ENG                   1 /**< Engineering notation instead of scientific */
#define OS_FLAGS_NUMMODE                   0x0A /**< GROUP: numMode */
#define OS_FLAGS_FMT_REAL                  5
#define OS_FLAGS_FMT_RECT                  6
#define OS_FLAGS_FMT_POLAR                 7
#define OS_FLAGS_FMTOVERRIDE               0x0B /**< GROUP: copy of fmtFlags with conversion override */
//#define OS_FLAGS_FMTEDIT                   0x0C /**< GROUP: Numeric editing flags */
//#define OS_FLAGS_FMTEDIT_FLAG              0 /**< 1=format number for editing */
#define OS_FLAGS_CURSOR                    0x0C /**< GROUP: Homescreen cursor */
#define OS_FLAGS_CURSOR_ABLE               2 /**< Cursor blinking enabled */
#define OS_FLAGS_CURSOR_ON                 3 /**< Cursor is actually being shown this moment */
#define OS_FLAGS_CURSOR_LOCK               4 /**< 1=cursor is locked off */
#define OS_FLAGS_CMD                       0x0C /**< GROUP: Command editor */
#define OS_FLAGS_CMD_VIRGIN                5 /**< Nothing has been typed so far. */
#define OS_FLAGS_CMD_EXEC                  6 /**< Need to execute a command */
#define OS_FLAGS_APP                       0x0D /**< GROUP: Application stuff */
#define OS_FLAGS_APP_WANTINTERRUPT         0 /**< Want ON key interrupts */
#define OS_FLAGS_APP_TEXTSAVE              1 /**< 1=save characters in textShadow */
#define OS_FLAGS_APP_AUTOSCROLL            2 /**< 1=auto-scroll text on last line */
#define OS_FLAGS_APP_MENUS                 3 /**< 1=process keys that bring up menus, 0=check Lock menu flag */
#define OS_FLAGS_APP_LOCKMENUS             4 /**< 1=ignore menu keys, 0=switch to home screen and bring up menu */
#define OS_FLAGS_APP_CURGRAPHIC            5 /**< 1=graphic cursor */
#define OS_FLAGS_APP_CURWORD               6 /**< 1=text cursor covers entire word */
#define OS_FLAGS_APP_EXIT                  7 /**< 1=application handles [EXIT] key itself */
#define OS_FLAGS_RCL                       0x0D /**< GROUP: Recall queue */
#define OS_FLAGS_RCL_ENABLEQUEUE           7 /**< Enable recall queue */
#define OS_FLAGS_SEQ                       0x0F /**< GROUP: Sequential graph */
#define OS_FLAGS_SEQ_WEBMODE               0 /**< 0 = NORMAL SEQ MODE, 1 = WEB MODE */
#define OS_FLAGS_SEQ_WEBVERT               1
#define OS_FLAGS_SEQ_UV                    2 /**< U vs. V */
#define OS_FLAGS_SEQ_VW                    3 /**< V vs. W */
#define OS_FLAGS_SEQ_UW                    4 /**< U vs. W */
#define OS_FLAGS_PROMPT                    0x11 /**< GROUP: Prompt line */
#define OS_FLAGS_PROMPT_EDIT               1 /**< Editing in prompt buffer */
#define OS_FLAGS_INDIC                     0x12 /**< GROUP: Run indicator. */
#define OS_FLAGS_INDIC_ENABLE              0 /**< Set to enable run indicator.  The C runtime resets this automatically. */
/**
 * indicator save area in use=1, free=0
 * 
 * resetting will disable 2nd while in _getkey
 */
#define OS_FLAGS_INDIC_INUSE               1
/**
 * GROUP: [2nd] and [ALPHA]
 * 
 * @see os_GetKey
 * @see sys/getkey.h
 */
#define OS_FLAGS_SHIFT                     0x12
#define OS_FLAGS_SHIFT_2ND                 3 /**< [2nd] has been pressed */
#define OS_FLAGS_SHIFT_ALPHA               4 /**< [ALPHA] has been pressed */
#define OS_FLAGS_SHIFT_LOWERCASE           5 /**< Little-a mode */
#define OS_FLAGS_SHIFT_ALPHALOCK           6 /**< [2nd]+[ALPHA] */
#define OS_FLAGS_SHIFT_KEEPALPHA           7 /**< 1=cannot cancel alpha shift */
#define OS_FLAGS_TABLE                     0x13 /**< GROUP: Graph table screen */
#define OS_FLAGS_TABLE_AUTOFILL            4 /**< 1=prompt, 0=fillAuto */
#define OS_FLAGS_TABLE_AUTOCALC            5 /**< 1=prompt, 0=CalcAuto */
#define OS_FLAGS_TABLE_RETABLE             6 /**< 0=table is okay, 1=must recompute table. */
#define OS_FLAGS_TRACE                     0x18 /**< GROUP: Trace */
#define OS_FLAGS_TRACE_EXPRESSION          0 /**< set to hide expression while tracing */
#define OS_FLAGS_STATS2                    0x1A /**< GROUP: More stats */
#define OS_FLAGS_STATS2_DIAGNOSTICS        0 /**< 1 = stat diagnostics on */
#define OS_FLAGS_STATS2_NODEL              2 /**< 1 = don't delete stats */
//#define OS_FLAGS_APD2              0x1B /**< GROUP: APD part 2 */
//#define OS_FLAGS_APD2_WARMSTARTINT       6 /**< 1 = a warm start is occurning before the next interrupt */
#define OS_FLAGS_GRAPH2                    0x1F /**< GROUP: Graph screen */
#define OS_FLAGS_GRAPH2_SPLITOVERRIDE      3 /**< 0 = force full screen with ParseInp, or something */
#define OS_FLAGS_ASM1                      0x21 /**< GROUP: Intentionally unused by TI, available for programs! */
#define OS_FLAGS_ASM2                      0x22 /**< GROUP: Intentionally unused by TI, available for programs! */
#define OS_FLAGS_ARCHIVE                   0x24 /**< GROUP: Archive stuff */
#define OS_FLAGS_ARCHIVE_CHECKBATTERY	    0 /**< 1 = check battery levels in Arc_Unarc first and throw error if low */
#define OS_FLAGS_GETSEND                   0x24 /**< FLAGS */
#define OS_FLAGS_GETSEND_COMFAILED         1 /**< 1 = Get/Send Communication Failed */
#define OS_FLAGS_SELFTEST                  0x24 /**< GROUP: Self-test screen */
#define OS_FLAGS_SELFTEST_RESETONPOWERON   2 /**< 1 = Force RAM reset when APD disabled on next power on */
#define OS_FLAGS_LOWERCASE                 0x24 /**< GROUP: Enable lowercase flag */
#define OS_FLAGS_LOWERCASE_ENABLE          3 /**< Enable lowercase flag */
#define OS_FLAGS_CONTEXT                   0x25 /**< GROUP: Context vectors */
#define OS_FLAGS_CONTEXT_NOCXPUTAWAY       5 /**< 1 = do not call cxPutAway routine */
#define OS_FLAGS_STATUSBAR                 0x27 /**< FLAGS */
#define OS_FLAGS_STATUSBAR_NOBARMODE       7 /**< 1 = abort drawing of statusbar mode, like "TEST MODE ENABLED */
#define OS_FLAGS_API1                      0x28 /**< FLAGS */
#define OS_FLAGS_API1_APPALLOWCONTEXT      0 /**< app wants context changes to happen */
#define OS_FLAGS_API1_APPRUNNING           4 /**< app is currently running */
#define OS_FLAGS_API1_APPRETKEYOFF         7 /**< 1 = GetKey returns kOff when [2nd]+[ON] pressed */
#define OS_FLAGS_API2                      0x29 /**< FLAGS */
#define OS_FLAGS_API3                      0x2A /**< FLAGS */
#define OS_FLAGS_API4                      0x2B /**< FLAGS */
#define OS_FLAGS_API4_CELLOVERRIDE         1 /**< use cell override */
#define OS_FLAGS_API4_FULLSCRNDRAW         2 /**< DRAW INTO LAST ROW/COL OF SCREEN */
#define OS_FLAGS_XAP0                      0x2E /**< GROUP: External apps */
#define OS_FLAGS_XAP0_MOUSE                0 /**< Used by mouse cursor routines */
#define OS_FLAGS_XAP1                      0x2F /**< GROUP: External apps */
#define OS_FLAGS_XAP2                      0x30 /**< GROUP: External apps */
#define OS_FLAGS_XAP3                      0x31 /**< GROUP: External apps */
#define OS_FLAGS_FONT                      0x32 /**< FLAGS */
#define OS_FLAGS_FONT_FRACDRAWLFONT        2
#define OS_FLAGS_FONT_FRACTALLLFONT        3
#define OS_FLAGS_FONT_CUSTOMFONT           7
/**
 * GROUP: OS hooks, also scriptFlag, rclFlag2, backGroundLink
 * 
 * You should generally not touch these.
 * The SDK does not have any explicit OS hook support.
 */
#define OS_FLAGS_HOOKS1                    0x33
#define OS_FLAGS_HOOKS1_ALT_ON             0 /**< run ONSCRPT at startup */
#define OS_FLAGS_HOOKS1_ALT_OFF            1 /**< run OFFSCRPT at shutdown */
#define OS_FLAGS_HOOKS1_USERCLQUEUEEND     2 /**< 1 = external mode */
#define OS_FLAGS_HOOKS1_IGNOREBPLINK       3 /**< 1 = override flag for link activity hook */
#define OS_FLAGS_HOOKS1_BPLINKON           4 /**< 1 = link activity hook active */
#define OS_FLAGS_HOOKS1_ENABLEKEYECHO      5 /**< 1 = sends keypresses back to connected calc as remote control packets (with GetCSC vs. GetKey codes...really dumb, TI) */
#define OS_FLAGS_HOOKS1_NOTEMPDELETE       6 /**< 1 = do not delete temporary programs at homescreen */
#define OS_FLAGS_HOOKS2                    0x34 /**< FLAGS; also sysHookFlg */
#define OS_FLAGS_HOOKS2_GETCSC             0 /**< 1 = GetCSC hook active */
#define OS_FLAGS_HOOKS2_LIBRARY            1 /**< 1 = library hook active */
//#define OS_FLAGS_HOOKS2_NO                 2 /**< 1 = same as 0; never used by OS */
#define OS_FLAGS_HOOKS2_HOMESCREEN         4 /**< 1 = homescreen hook active */
#define OS_FLAGS_HOOKS2_RAWKEY             5 /**< 1 = raw key hook active */
#define OS_FLAGS_HOOKS2_CATALOG2           6 /**< 1 = catalog 2 hook active */
#define OS_FLAGS_HOOKS2_CURSOR             7 /**< 1 = cursor hook active */
#define OS_FLAGS_HOOKS3                    0x35 /**< FLAGS; also sysHookFlg1 */
#define OS_FLAGS_HOOKS3_TOKEN              0 /**< 1 = token hook active */
#define OS_FLAGS_HOOKS3_LOCALIZE           1 /**< 1 = localize hook active */
#define OS_FLAGS_HOOKS3_WINDOW             2 /**< 1 = window hook active */
#define OS_FLAGS_HOOKS3_GRAPH              3 /**< 1 = graph hook active */
#define OS_FLAGS_HOOKS3_YEQU               4 /**< 1 = Y= hook active */
#define OS_FLAGS_HOOKS3_FONT               5 /**< 1 = font hook active */
#define OS_FLAGS_HOOKS3_REGRAPH            6 /**< 1 = regraph hook active */
#define OS_FLAGS_HOOKS3_DRAWING            7 /**< 1 = drawing hook active */
#define OS_FLAGS_HOOKS4                    0x36 /**< FLAGS; also sysHookFlag2 */
#define OS_FLAGS_HOOKS4_TRACE              0 /**< 1 = trace hook active */
#define OS_FLAGS_HOOKS4_PARSER             1 /**< 1 = parser hook active */
#define OS_FLAGS_HOOKS4_APPCHANGE          2 /**< 1 = app change hook active */
#define OS_FLAGS_HOOKS4_CATALOG1           3 /**< 1 = catalog 1 hook active */
#define OS_FLAGS_HOOKS4_HELP               4 /**< 1 = help hook active */
#define OS_FLAGS_HOOKS4_CXREDISP           5 /**< 1 = cxRedisp hook active */
#define OS_FLAGS_HOOKS4_MENU               6 /**< 1 = menu hook active */
#define OS_FLAGS_HOOKS4_SILENTLINK         7 /**< 1 = silent link hook active */
#define OS_FLAGS_HOOKS5                    0x3A /**< FLAGS */
#define OS_FLAGS_HOOKS5_USBACTIVITY        0 /**< 1 = USB activity hook active */
#define OS_FLAGS_PLOT3                     0x3C /**< GROUP: Plot screen */
#define OS_FLAGS_PLOT3_BUFFERONLY          0 /**< Draw commands only draw to buffer, not screen.  Will corrupt heap in default configuration. */
#define OS_FLAGS_PLOT3_USEFASTCIRC         4 /**< Use fast circle routine, which does not pay attention to the aspect ratio of X/Y min/max */
#define OS_FLAGS_KEYBOARD                  0x3D /**< GROUP: Originally TI-Keyboard accessory, probably now USB keyboards */
#define OS_FLAGS_KEYBOARD_DEFAULTS         6 /**< 1 = GetKey returns extended keycodes with TI-Keyboard */
#define OS_FLAGS_SILENTLINK                0x3E /**< FLAGS */
#define OS_FLAGS_SILENTLINK_ACTIVE         0 /**< SE/84+ silent link is active */
#define OS_FLAGS_EXTRAHOOKS                0x3E /**< GROUP: Even more hooks */
#define OS_FLAGS_EXTRAHOOKS_CHECKCAT2VER   3 /**< 1 = check catalog 2 hook's version before executing it (and error or take other action if so) */
#define OS_FLAGS_EXTRAHOOKS_OPENLIBACTIVE  4 /**< 1 = OpenLib( was successfully called on a Flash application (ExecLib will error if zero) */
#define OS_FLAGS_CLOCK                     0x3F /**< GROUP: Clock */
#define OS_FLAGS_CLOCK_NOTMDYMODE          0 /**< 0 = M/D/Y format */
#define OS_FLAGS_CLOCK_ISYMDMODE           1 /**< 1 = Y/M/D format */
#define OS_FLAGS_CLOCK_IS24HOUR            2 /**< 1 = clock in 24 hour mode */
#define OS_FLAGS_CLOCK_INAFTERNOON         3 /**< 1 = current time is in afternoon (PM) (I think) */
#define OS_FLAGS_CLOCK_USETOKENSINSTRING   4 /**< 1 = use tokens instead of characters when displaying clock as string (for getTmStr and getDtStr vs. MODE screen) (keep this reset) */
#define OS_FLAGS_CLOCK_DISPLAYCLOCK        5 /**< 1 = display clock (this is set every second, reset otherwise) */
#define OS_FLAGS_CLOCK_CLOCKON             6 /**< 1 = clock on */
#define OS_FLAGS_MATHPRINT                 0x44 /**< GROUP: MathPrint */
#define OS_FLAGS_MATHPRINT_ENABLED         5 /**< 1 = use mathprint styling */
#define OS_FLAGS_BOOTMENU                  0x45 /**< FLAGS */
#define OS_FLAGS_BOOTMENU_DISPINITIALMENU  4 /**< 1 = don't display the initial boot menu */
#define OS_FLAGS_BACKLIGHT                 0x46 /**< FLAGS */
#define OS_FLAGS_BACKLIGHT_RESTORE         0 /**< 1 = restore lcd brightness when needed */
#define OS_FLAGS_GRAPH3                    0x4A /**< FLAGS */
#define OS_FLAGS_GRAPH3_DRAWLABELS         0 /**< 1 = don't draw Graph Labels (this is usually reset anyway) */
#define OS_FLAGS_PUTMAP                    0x4A /**< GROUP: putMap */
#define OS_FLAGS_PUTMAP_USEPIXELSHADOW2    3 /**< 1 = use pixelshadow2, not pixelshadow */
#define OS_FLAGS_PUTMAP_USECOLOR           4 /**< 1 = use custom color */
#define OS_FLAGS_GRAPHDISP                 0x4B /**< FLAGS */
#define OS_FLAGS_GRAPHDISP_BACKGROUNDVALID 4 /**< 1 = items in graph background are still valid */

#define os_Flags ((uint8_t*)0xD00080)

#ifdef __cplusplus
}
#endif

#endif
