/**
 * @file
 * @authors
 * Matt "MateoConLechuga" Waltz\n
 * Jacob "jacobly" Young
 * @brief TI CE OS flags
 */

#ifndef _TI_OS_FLAGS_H
#define _TI_OS_FLAGS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Set a particular OS flag
 *
 * @param offset Offset to particular flag in list
 * @param set Bitmask of flag to set
 */
void os_SetFlagByte(int offset, uint8_t set);

/**
 * Get a particular OS flag
 *
 * @param offset Offset to particular flag in list
 * @returns Bitmask of flag
 */
uint8_t os_GetFlagByte(int offset);

/**
 * High 8 is unsigned offset, low 8 is bits to test
 */
int os_TestFlagBits(uint16_t offset_pattern);
bool os_TestFlagBitsFast(uint16_t offset_pattern); /* Warning: has a bug if bits and flags are all set! */
void os_SetFlagBits(int16_t offset_pattern);
void os_ResetFlagBits(int16_t offset_pattern);

/**
 * Converts a flag group name and member ID to a literal.
 * The `flag_` prefix is automatically taken care of.
 * 
 * For example, `FLAG_ID(indic, enable)` 
 * 
 * @param GROUP Flag group name without the `flag_` prefix
 * @param MEMBER Flag item name without the `flag_GROUP_` prefix
 */
#define FLAG_ID(GROUP, MEMBER) (((flags_ ## GROUP) << 8) | (1 << (flags_ ## GROUP ## _ ## MEMBER)))

/**
 * Sets an OS flag to 1.  The `flags_` prefix and group prefix are added automatically for you.
 * 
 * For example, instead of:
 * 
 * @code
 * os_SetFlagByte(flags_indic, flags_indic_enable);
 * @endcode
 * 
 * you can do:
 * 
 * @code
 * os_SetFlag(indic, enable);
 * @endcode
 * 
 */
#define os_SetFlag(GROUP, MEMBER) os_SetFlagBits(FLAG_ID(GROUP, MEMBER))

/**
 * Clears an OS flag to 0.
 * 
 * @see os_SetFlag
 */
#define os_ResetFlag(GROUP, MEMBER) os_ResetFlagBits(FLAG_ID(GROUP, MEMBER))

/**
 * Checks if an OS flag is set.
 * 
 * @see os_SetFlag
 */
#define os_TestFlag(GROUP, MEMBER) (0 < os_TestFlagBits(FLAG_ID(GROUP, MEMBER)))

#define flags_trig                      0 /**< GROUP: Trig-related */
#define flags_trig_degrees              2 /**< Set for degrees, reset for radians */
#define flags_kbd                       0 /**< GROUP: Keyboard scan control */
#define flags_kbd_SCR                   3 /**< Scan Code Read */
#define flags_kbd_keyPress              4 /**< Set if a key press is in the key press buffer. @see `os_KbdScanCode` in  `<ti/getcsc.h>` */
#define flags_done                      0 /**< GROUP: "Done" */
#define flags_done_prgm                 5 /**< Show "Done" after program exits */
#define flags_edit                      1 /**< GROUP: OS edit buffer */
#define flags_edit_open                 2 /**< Set if an edit buffer is open */
#define flags_Ans                       1 /**< GROUP: Ans variable flags */
#define flags_Ans_scroll                3 /**< Set if viewing Ans can scroll, must be reset to move cursor in edit buffer */
/**
 * GROUP: System monitor.
 * You generally should not mess with the system monitor unless you're writing a flash application that
 * integrates with the OS.
 * And we can't sign flash applications.
 */
#define flags_mon                       1
#define flags_mon_abandon               4 /**< Don't start any long process in put away routine */
#define flags_plot                      2 /**< GROUP: Plot screen */
#define flags_plot_loc                  1 /**< 0=bkup and display, 1=display only.  By default, this memory is part of the C heap. */
#define flags_plot_disp                 2 /**< 1=plot is in display, 0=text in display, this also indicates whether graph is being shown or not */
#define flags_grfMode                   2 /**< GROUP: Graph mode */
#define flags_grfMode_func              4 /**< Standard function graph Y=f(x) */
#define flags_grfMode_polar             5 /**< Polar graph mode */
#define flags_grfMode_param             6 /**< Parametric graph mode */
#define flags_grfMode_recur             7 /**< Sequence graph mode */
#define flags_graph                     3 /**< GROUP: Graph screen */
#define flags_graph_draw                0 /**< Redraw graph screen.  On exit, this is automatically set by the C runtime. */
#define flags_graph_cursor              2
#define flags_grf                       4 /**< GROUP: Graph screen format */
#define flags_grf_dot                   0 /**< Draw dots instead of connecting points */
#define flags_grf_simul                 1 /**< Draw all graphs simultaneously */
#define flags_grf_grid                  2 /**< Display grid */
#define flags_grf_polar                 3 /**< Display polar coordinates */
#define flags_grf_noCoord               4 /**< Hide coordinates */
#define flags_grf_noAxis                5 /**< Hide X and Y axes */
#define flags_grf_label                 6 /**< Show axis labels */
#define flags_text                      5 /**< GROUP: Text display */
#define flags_text_eraseBelow           1 /**< Erase line below small char */
#define flags_text_scrolled             2 /**< Screen has scrolled */
#define flags_text_inverse              3 /**< Text in inverse color */
#define flags_text_insMode              4 /**< Insert mode */
#define flags_parser                    6 /**< GROUP: Parser (for BASIC and equations).  No useful equates for C programs. */
#define flags_parser2                   7 /**< GROUP: Parser */
#define flags_parser2_numOP1            0 /**< Signals a result in OP1 */
#define flags_newDispF                  8 /**< GROUP: Derivative mode */
#define flags_newDispF_preClrForMode    0 /**< 1=HELP BLINK ON MODE SCREEN */
#define flags_newDispF_allowProgTokens  1 /**< 1=allow programming tokens to be parsed in BASIC programs */
#define flags_apd                       8 /**< GROUP: Automatic Power-Down */
#define flags_apd_able                  2 /**< Enable APD */
#define flags_apd_running               3 /**< APD timer active */
#define flags_apd_warmStart             4 /**< 1=calculator is turning on from APD or power loss */
#define flags_on                        9 /**< GROUP: On key */
#define flags_on_parseInput             1 /**< 1=parse input when done */
#define flags_on_running                3 /**< "1=calculator is running" is literally all TI wrote */
/**
 * On key has been pressed at some point.
 * If this is set, ERR:BREAK will be displayed when the program exits.
 * This is automatically cleared by the C runtime on exit.
 */
#define flags_on_interrupt              4
#define flags_stats                     9 /**< GROUP: Statistics */
#define flags_stats_valid               6 /**< Reset to recompute stat vars */
#define flags_fmt                       0x0A /**< GROUP: Numeric format */
#define flags_fmt_exponent              0 /**< 1=show exponent, 0=no exponent */
#define flags_fmt_eng                   1 /**< Engineering notation instead of scientific */
#define flags_numMode                   0x0A /**< GROUP: numMode */
#define flags_fmt_real                  5
#define flags_fmt_rect                  6
#define flags_fmt_polar                 7
#define flags_fmtOverride               0x0B /**< GROUP: copy of fmtFlags with conversion override */
//#define flags_fmtEdit                   0x0C /**< GROUP: Numeric editing flags */
//#define flags_fmtEdit_flag              0 /**< 1=format number for editing */
#define flags_cursor                    0x0C /**< GROUP: Homescreen cursor */
#define flags_cursor_able               2 /**< Cursor blinking enabled */
#define flags_cursor_on                 3 /**< Cursor is actually being shown this moment */
#define flags_cursor_lock               4 /**< 1=cursor is locked off */
#define flags_cmd                       0x0C /**< GROUP: Command editor */
#define flags_cmd_virgin                5 /**< Nothing has been typed so far. */
#define flags_cmd_exec                  6 /**< Need to execute a command */
#define flags_app                       0x0D /**< GROUP: Application stuff */
#define flags_app_wantInterrupt         0 /**< Want ON key interrupts */
#define flags_app_textSave              1 /**< 1=save characters in textShadow */
#define flags_app_autoScroll            2 /**< 1=auto-scroll text on last line */
#define flags_app_menus                 3 /**< 1=process keys that bring up menus, 0=check Lock menu flag */
#define flags_app_lockMenus             4 /**< 1=ignore menu keys, 0=switch to home screen and bring up menu */
#define flags_app_curGraphic            5 /**< 1=graphic cursor */
#define flags_app_curWord               6 /**< 1=text cursor covers entire word */
#define flags_app_exit                  7 /**< 1=application handles [EXIT] key itself */
#define flags_rcl                       0x0D /**< GROUP: Recall queue */
#define flags_rcl_enableQueue           7 /**< Enable recall queue */
#define flags_seq                       0x0F /**< GROUP: Sequential graph */
#define flags_seq_webMode               0 /**< 0 = NORMAL SEQ MODE, 1 = WEB MODE */
#define flags_seq_webVert               1
#define flags_seq_uv                    2 /**< U vs. V */
#define flags_seq_vw                    3 /**< V vs. W */
#define flags_seq_uw                    4 /**< U vs. W */
#define flags_prompt                    0x11 /**< GROUP: Prompt line */
#define flags_prompt_edit               1 /**< Editing in prompt buffer */
#define flags_indic                     0x12 /**< GROUP: Run indicator. */
#define flags_indic_enable              0 /**< Set to enable run indicator.  The C runtime resets this automatically. */
/**
 * indicator save area in use=1, free=0
 * 
 * resetting will disable 2nd while in _getkey
 */
#define flags_indic_inUse               1
/**
 * GROUP: [2nd] and [ALPHA]
 * 
 * @see os_GetKey
 * @see sys/getkey.h
 */
#define flags_shift                     0x12
#define flags_shift_2nd                 3 /**< [2nd] has been pressed */
#define flags_shift_alpha               4 /**< [ALPHA] has been pressed */
#define flags_shift_lowercase           5 /**< Little-a mode */
#define flags_shift_alphaLock           6 /**< [2nd]+[ALPHA] */
#define flags_shift_keepAlpha           7 /**< 1=cannot cancel alpha shift */
#define flags_table                     0x13 /**< GROUP: Graph table screen */
#define flags_table_autoFill            4 /**< 1=prompt, 0=fillAuto */
#define flags_table_autoCalc            5 /**< 1=prompt, 0=CalcAuto */
#define flags_table_reTable             6 /**< 0=table is okay, 1=must recompute table. */
#define flags_trace                     0x18 /**< GROUP: Trace */
#define flags_trace_expression          0 /**< set to hide expression while tracing */
#define flags_stats2                    0x1A /**< GROUP: More stats */
#define flags_stats2_diagnostics        0 /**< 1 = stat diagnostics on */
#define flags_stats2_noDel              2 /**< 1 = don't delete stats */
//#define flags_apd2              0x1B /**< GROUP: APD part 2 */
//#define flags_apd2_warmStartInt       6 /**< 1 = a warm start is occurning before the next interrupt */
#define flags_graph2                    0x1F /**< GROUP: Graph screen */
#define flags_graph2_splitOverride      3 /**< 0 = force full screen with ParseInp, or something */
#define flags_asm1                      0x21 /**< GROUP: Intentionally unused by TI, available for programs! */
#define flags_asm2                      0x22 /**< GROUP: Intentionally unused by TI, available for programs! */
#define flags_archive                   0x24 /**< GROUP: Archive stuff */
#define flags_archive_checkBattery	    0 /**< 1 = check battery levels in Arc_Unarc first and throw error if low */
#define flags_getSend                   0x24 /**< FLAGS */
#define flags_getSend_comFailed         1 /**< 1 = Get/Send Communication Failed */
#define flags_selfTest                  0x24 /**< GROUP: Self-test screen */
#define flags_selfTest_resetOnPowerOn   2 /**< 1 = Force RAM reset when APD disabled on next power on */
#define flags_lowercase                 0x24 /**< GROUP: Enable lowercase flag */
#define flags_lowercase_enable          3 /**< Enable lowercase flag */
#define flags_context                   0x25 /**< GROUP: Context vectors */
#define flags_context_nocxPutAway       5 /**< 1 = do not call cxPutAway routine */
#define flags_statusBar                 0x27 /**< FLAGS */
#define flags_statusBar_noBarMode       7 /**< 1 = abort drawing of statusbar mode, like "TEST MODE ENABLED */
#define flags_api1                      0x28 /**< FLAGS */
#define flags_api1_appAllowContext      0 /**< app wants context changes to happen */
#define flags_api1_appRunning           4 /**< app is currently running */
#define flags_api1_appRetKeyOff         7 /**< 1 = GetKey returns kOff when [2nd]+[ON] pressed */
#define flags_api2                      0x29 /**< FLAGS */
#define flags_api3                      0x2A /**< FLAGS */
#define flags_api4                      0x2B /**< FLAGS */
#define flags_api4_cellOverride         1 /**< use cell override */
#define flags_api4_fullScrnDraw         2 /**< DRAW INTO LAST ROW/COL OF SCREEN */
#define flags_xap0                      0x2E /**< GROUP: External apps */
#define flags_xap0_mouse                0 /**< Used by mouse cursor routines */
#define flags_xap1                      0x2F /**< GROUP: External apps */
#define flags_xap2                      0x30 /**< GROUP: External apps */
#define flags_xap3                      0x31 /**< GROUP: External apps */
#define flags_font                      0x32 /**< FLAGS */
#define flags_font_fracDrawLFont        2
#define flags_font_fracTallLFont        3
#define flags_font_customFont           7
/**
 * GROUP: OS hooks, also scriptFlag, rclFlag2, backGroundLink
 * 
 * You should generally not touch these.
 * The SDK does not have any explicit OS hook support.
 */
#define flags_hooks1                    0x33
#define flags_hooks1_alt_On             0 /**< run ONSCRPT at startup */
#define flags_hooks1_alt_Off            1 /**< run OFFSCRPT at shutdown */
#define flags_hooks1_useRclQueueEnd     2 /**< 1 = external mode */
#define flags_hooks1_ignoreBPLink       3 /**< 1 = override flag for link activity hook */
#define flags_hooks1_bPLinkOn           4 /**< 1 = link activity hook active */
#define flags_hooks1_enableKeyEcho      5 /**< 1 = sends keypresses back to connected calc as remote control packets (with GetCSC vs. GetKey codes...really dumb, TI) */
#define flags_hooks1_noTempDelete       6 /**< 1 = do not delete temporary programs at homescreen */
#define flags_hooks2                    0x34 /**< FLAGS; also sysHookFlg */
#define flags_hooks2_getCSC             0 /**< 1 = GetCSC hook active */
#define flags_hooks2_library            1 /**< 1 = library hook active */
//#define flags_hooks2_no                 2 /**< 1 = same as 0; never used by OS */
#define flags_hooks2_homescreen         4 /**< 1 = homescreen hook active */
#define flags_hooks2_rawKey             5 /**< 1 = raw key hook active */
#define flags_hooks2_catalog2           6 /**< 1 = catalog 2 hook active */
#define flags_hooks2_cursor             7 /**< 1 = cursor hook active */
#define flags_hooks3                    0x35 /**< FLAGS; also sysHookFlg1 */
#define flags_hooks3_token              0 /**< 1 = token hook active */
#define flags_hooks3_localize           1 /**< 1 = localize hook active */
#define flags_hooks3_window             2 /**< 1 = window hook active */
#define flags_hooks3_graph              3 /**< 1 = graph hook active */
#define flags_hooks3_yEqu               4 /**< 1 = Y= hook active */
#define flags_hooks3_font               5 /**< 1 = font hook active */
#define flags_hooks3_regraph            6 /**< 1 = regraph hook active */
#define flags_hooks3_drawing            7 /**< 1 = drawing hook active */
#define flags_hooks4                    0x36 /**< FLAGS; also sysHookFlag2 */
#define flags_hooks4_trace              0 /**< 1 = trace hook active */
#define flags_hooks4_parser             1 /**< 1 = parser hook active */
#define flags_hooks4_appChange          2 /**< 1 = app change hook active */
#define flags_hooks4_catalog1           3 /**< 1 = catalog 1 hook active */
#define flags_hooks4_help               4 /**< 1 = help hook active */
#define flags_hooks4_cxRedisp           5 /**< 1 = cxRedisp hook active */
#define flags_hooks4_menu               6 /**< 1 = menu hook active */
#define flags_hooks4_silentLink         7 /**< 1 = silent link hook active */
#define flags_hooks5                    0x3A /**< FLAGS */
#define flags_hooks5_usbActivity        0 /**< 1 = USB activity hook active */
#define flags_plot3                     0x3C /**< GROUP: Plot screen */
#define flags_plot3_bufferOnly          0 /**< Draw commands only draw to buffer, not screen.  Will corrupt heap in default configuration. */
#define flags_plot3_useFastCirc         4 /**< Use fast circle routine, which does not pay attention to the aspect ratio of X/Y min/max */
#define flags_keyboard                  0x3D /**< GROUP: Originally TI-Keyboard accessory, probably now USB keyboards */
#define flags_keyboard_defaults         6 /**< 1 = GetKey returns extended keycodes with TI-Keyboard */
#define flags_silentLink                0x3E /**< FLAGS */
#define flags_silentLink_active         0 /**< SE/84+ silent link is active */
#define flags_extraHooks                0x3E /**< GROUP: Even more hooks */
#define flags_extraHooks_checkCat2Ver   3 /**< 1 = check catalog 2 hook's version before executing it (and error or take other action if so) */
#define flags_extraHooks_openLibActive  4 /**< 1 = OpenLib( was successfully called on a Flash application (ExecLib will error if zero) */
#define flags_clock                     0x3F /**< GROUP: Clock */
#define flags_clock_notMDYMode          0 /**< 0 = M/D/Y format */
#define flags_clock_isYMDMode           1 /**< 1 = Y/M/D format */
#define flags_clock_is24Hour            2 /**< 1 = clock in 24 hour mode */
#define flags_clock_inAfternoon         3 /**< 1 = current time is in afternoon (PM) (I think) */
#define flags_clock_useTokensInString   4 /**< 1 = use tokens instead of characters when displaying clock as string (for getTmStr and getDtStr vs. MODE screen) (keep this reset) */
#define flags_clock_displayClock        5 /**< 1 = display clock (this is set every second, reset otherwise) */
#define flags_clock_clockOn             6 /**< 1 = clock on */
#define flags_mathprint                 0x44 /**< GROUP: MathPrint */
#define flags_mathprint_enabled         5 /**< 1 = use mathprint styling */
#define flags_bootMenu                  0x45 /**< FLAGS */
#define flags_bootMenu_dispInitialMenu  4 /**< 1 = don't display the initial boot menu */
#define flags_backlight                 0x46 /**< FLAGS */
#define flags_backlight_restore         0 /**< 1 = restore lcd brightness when needed */
#define flags_graph3                    0x4A /**< FLAGS */
#define flags_graph3_drawLabels         0 /**< 1 = don't draw Graph Labels (this is usually reset anyway) */
#define flags_putMap                    0x4A /**< GROUP: putMap */
#define flags_putMap_usePixelShadow2    3 /**< 1 = use pixelshadow2, not pixelshadow */
#define flags_putMap_useColor           4 /**< 1 = use custom color */
#define flags_graphDisp                 0x4B /**< FLAGS */
#define flags_graphDisp_backgroundValid 4 /**< 1 = items in graph background are still valid */

#define os_Flags            ((uint8_t*)0xD00080)

#ifdef __cplusplus
}
#endif

#endif
