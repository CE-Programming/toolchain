/**
 * @file
 * @brief Contains text-wrapping and text input routines for FontLibC.
 *
 * TextIOC is a wrapper for the FontLibC library created by DrDnar. It offers several useful
 * routines for text wrapping and various kinds of text input.
 *
 * The library's text input is based on the Input Data Structure (IDS) which holds the input
 * data and configuration data for the two input routines, textio_Input and textio_TimedInput.
 * Each IDS is at least 26 bytes plus the sum of the number of characters it is to hold and
 * three times the number of keymaps it uses. Each IDS can use up to 255 keymaps.
 *
 * TextIOC offers four built-in keymaps for uppercase and lowercase characters, one for numerals,
 * and one for program/appvar names. It also supports custom keymaps created by the programmer.
 *
 * Each keymap is 57 bytes long. The first character of the keymap acts as the "keymap indicator,"
 * a special character that represents the keymap. The keymap data format is identical to the one
 * used as an example for os_GetCSC in the tice.h documentation.
 *
 * The first keymap in an IDS has an index of zero. The next one has an index of one, and so on.
 * Thus, the number of keymaps in the IDS is the actual number of keymaps minus one. This is
 * important to remember when changing keymaps.
 *
 * Both input routines automatically exit after each keypress, so in order to get more than one
 * character of input, it is necessary to put them inside of a while(){...} or do {...} while loop.
 * The textio_TimedInput function automatically exits after each second as well which allows the
 * programmer to print the timer or whatever else he wishes to do with the timer.
 *
 * The general outline of an textio_Input call resembles the following:
 * @code
 * uint24_t *ids;
 * char *keymap;
 * sk_key_t key;
 *
 * ids = textio_CreateIDS(10, 50, 50, 50, 1);    // Create an IDS
 *
 * // Create a custom keymap and assign it to an IDS (optional)
 * keymap = textio_CreateKeymap('A', \0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0);
 * textio_SetKeymaps(ids, 1, keymap);
 *
 * textio_SetCursorDimensions(ids, 1, 9);    // Set the cursor dimensions
 *
 * // Do additional configuration for the cursor or IDS (optional)
 *
 * // An input loop
 * do {
 *	 key = textio_Input(ids);
 * } while (key != escape_key);
 *
 * // Do something with the input
 *
 * // Free each IDS created
 * textio_DeleteIDS(ids);
 *
 * // Free any keymaps created
 * textio_DeleteKeymap(keymap);
 * @endcode
 *
 * @authors "Captain Calc"
 *
 * Many thanks to DrDnar, jacobly, Adriweb, and the other members of the CE Programming team for their
 * help and support!
 */


#ifndef H_TEXTIOC
#define H_TEXTIOC

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allocates memory for a \c Input \c Data \c Structure \c (IDS).
 *
 * @note
 * Unless a different memory allocation routine other than \c malloc()
 * needs to be used, textio_CreateIDS should be used.
 *
 * @note
 * \c num_keymaps should be at least 1, otherwise undefined behavior will result.
 *
 * @param xPos Starting x-position of the cursor
 * @param yPos y-position of the cursor
 * @param visible_width Width of visible input (in pixels)
 * @param num_keymaps Number of keymaps
 * @param malloc_routine Malloc implementation to use
 * @return Pointer to IDS, if successful; \c NULL, otherwise
 */
uint24_t *textio_AllocIDS(size_t size, uint24_t xPos, uint8_t yPos, uint24_t visible_buffer_width, uint8_t num_keymaps, void *(malloc_routine)(size_t));

/**
 * Allocates memory for a \i Input \i Data \i Structure \i (IDS).
 *
 * @warning
 * If used outside of a function body, the memory will be allocated in the
 * global unitialized data segment (BSS). If used inside a function body, the
 * memory will be allocated on the stack. If the sprite is sufficiently large,
 * usage inside a function body will overflow the stack, so it is recommended
 * that this normally be used outside of a function body.
 *
 * @note
 * \c num_keymaps should be at least 1, otherwise undefined behavior will result.
 *
 * @param xPos Starting x-position of the cursor
 * @param yPos y-position of the cursor
 * @param visible_width Width of visible input (in pixels)
 * @param num_keymaps Number of keymaps
 * @return Pointer to IDS, if successful; \c NULL, otherwise
 */
#define textio_CreateIDS(size, xPos, yPos, visible_buffer_width, num_keymaps) \
textio_AllocIDS(size, xPos, yPos, visible_buffer_width, num_keymaps, malloc)

/**
 * Frees the memory allocated for the specified \p IDS.
 *
 * @note
 * Unless a different free-ing routine other than \c free()
 * needs to be used, textio_DeleteIDS should be used.
 *
 * @param IDS Pointer to IDS
 * @param free_routine Free implementation to use
 */
void textio_FreeIDS(uint24_t *IDS, void (free_routine)(void *));

/**
 * Frees the memory allocated for the specified \p IDS.
 *
 * @param IDS Pointer to IDS
 */
#define textio_DeleteIDS(IDS) \
textio_FreeIDS(IDS, free)

/**
 * Gets the size of the data buffer in the specified \p IDS.
 *
 * @param IDS Pointer to IDS
 * @return Size of data buffer
 */
uint24_t textio_GetDataBufferSize(uint24_t *IDS);

/**
 * Gets a pointer to the data buffer in the specified \p IDS.
 *
 * @param IDS Pointer to IDS
 * @return Pointer to data buffer
 */
char *textio_GetDataBufferPtr(uint24_t *IDS);

/**
 * Gets a pointer to the last character textio_Input processed in
 * the specified \p IDS.
 * @see textio_Input
 *
 * @param IDS Pointer to IDS
 * @return Pointer to last character processed
 */
uint24_t textio_GetCurrCharPtr(uint24_t *IDS);

/**
 * Gets the x-position for the specified \p IDS
 *
 * @param IDS Pointer to IDS
 * @return IDS x-position
 */
uint24_t textio_GetIDSX(uint24_t *IDS);

/**
 * Gets the y-position for the specified \p IDS
 *
 * @param IDS Pointer to IDS
 * @return IDS y-position
 */
uint8_t textio_GetIDSY(uint24_t *IDS);

/**
 * Sets the cursor color for the specified \p IDS
 *
 * @param IDS Pointer to IDS
 * @param color 8bpp color
 */
void textio_SetCursorColor(uint24_t *IDS, uint8_t color);

/**
 * Gets the cursor color for the specified \p IDS
 *
 * @param IDS Pointer to IDS
 * @return Cursor color
 */
uint8_t textio_GetCursorColor(uint24_t *IDS);

/**
 * Gets the background color of the cursor.
 *
 * @note The color returned is the background color of the cursor from the last IDS used in
 * textio_Input or textio_TimedInput.
 *
 * @param IDS Pointer to IDS
 * @return Cursor's background color
*/
uint8_t textio_GetCursorBGColor(void);

/**
 * Sets the cursor blink rate. Defaults to 16.
 *
 * @note The greater the number's magnitude the slower the cursor will blink.
 * However, a blink rate of 0 will turn off cursor blinking.
 *
 * @note This function is not IDS-specific. The cursor blink rate will be the same for all IDSes
 * until it is changed by the programmer.
 *
 * @param rate A number from 0 to 255
*/
void textio_SetCursorBlinkRate(uint8_t rate);

/**
 * Gets the current cursor x-position.
 *
 * @return Current cursor x-position
*/
uint24_t textio_GetCurrCursorX(void);

/**
 * Sets the cursor width and height.
 *
 * @param IDS Pointer to IDS
 * @param width Width of cursor
 * @param height Height of cursor
 * @return True if dimensions set; False, otherwise
 */
bool textio_SetCursorDimensions(uint24_t *IDS, uint8_t width, uint8_t height);

/**
 * Gets cursor's width.
 *
 * @param IDS Pointer to IDS
 * @return Cursor width
 */
uint8_t textio_GetCursorWidth(uint24_t *IDS);

/**
 * Gets cursor's height.
 *
 * @param IDS Pointer to IDS
 * @return Cursor height
 */
uint8_t textio_GetCursorHeight(uint24_t *IDS);

/**
 * Sets the amount of time in which textio_TimedInput will accept input.
 *
 * @param IDS Pointer to IDS
 * @param seconds Number of seconds
*/
void textio_SetIDSTimer(uint24_t *IDS, uint24_t seconds);

/**
 * Gets the timer value for the specified IDS.
 *
 * @note You can determine if the timer for the textio_TimedInput function
 * has expired by checking the value that this function returns.
 *
 * @param IDS Pointer to IDS
 * @return Amount of time left
*/
uint24_t textio_GetIDSTimer(uint24_t *IDS);

/**
 * Sets the state of the \c PRGM_NAME flag.
 *
 * @note
 * This flag determines if the textio_Input will accept a number as
 * a the first character of input.
 *
 * @param IDS Pointer to IDS
 * @param state State of flag
*/
void textio_SetPrgmNameFlag(uint24_t *IDS, bool state);

/**
 * Sets the state of the \c IDS_Lock flag. When this flag is on, \c textio_Input(),
 * will not accept input for the specified IDS.
 *
 * @param IDS Pointer to IDS
 * @param state State of flag
 */
void textio_LockIDS(uint24_t *IDS, bool state);

/**
 * Gets the state of the \c IDS_Lock flag.
 *
 * @param IDS Pointer to IDS
 * @return State of flag
 */
bool textio_GetIDSLock(uint24_t *IDS);

/**
 * Gets the state of the buffer_full flag. This flag is set if the data buffer of the specified IDS
 * is full. The flag is reset, otherwise.
 *
 * @param IDS Pointer to IDS
 * @return State of buffer_full flag
*/
bool textio_GetBufferFullFlag(uint24_t *IDS);

/**
 * Clears the data buffer of the specified IDS (sets contents to \c NULL).
 *
 * @param IDS Pointer to IDS
*/
void textio_ClearDataBuffer(uint24_t *IDS);

/**
 * Allocates memory for a new keymap.
 *
 * @note
 * Unless a different memory allocation routine other than \c malloc()
 * needs to be used, textio_CreateKeymap should be used.
 *
 * @param indicator Symbol that indicating the keymap's type
 * @param keymap_data 50-byte character array
 * @param malloc_routine Malloc implementation to use
 * @return Pointer to keymap, if successful; \c NULL, otherwise
 */
char *textio_AllocKeymap(uint8_t indicator, const char *keymap_data, void *(malloc_routine)(size_t));

/**
 * Allocates memory for a new keymap.
 *
 * @note The \p keymap_data is the same string format used in the GraphX os_GetCSC example.
 * E.G. \0\0\0\0\0\0\0\0\0\0\"WRMH\0\0?[VQLG\0\0:ZUPKFC\0 YTOJEB\0\0XSNIDA\0\0\0\0\0\0\0\0
 *
 * @param indicator Symbol that indicating the keymap's type
 * @param keymap_data 50-byte character array
 * @return Pointer to keymap, if successful; \c NULL, otherwise
 */
#define textio_CreateKeymap(indicator, keymap_data) \
textio_AllocKeymap(indicator, keymap_data, malloc)

/**
 * Frees the memory allocated for the specified keymap.
 *
 * @note
 * Unless a different free-ing routine other than \c free()
 * needs to be used, textio_DeleteKeymap should be used.
 *
 * @param IDS Pointer to IDS
 * @param free_routine Free implementation to use
 */
void textio_FreeKeymap(uint24_t *IDS, void (free_routine)(void *));

/**
 * Frees the memory allocated for the specified keymap.
 *
 * @param IDS Pointer to IDS
*/
#define textio_DeleteKeymap(IDS) \
textio_FreeKeymap(IDS, free)

/**
 * Sets the keymaps for the specified IDS. These keymaps determine what kind of data the
 * data buffer will hold.
 *
 * @param IDS Pointer to IDS
 * @param num_keymaps Number of keymaps
 * @param keymap0 Pointer to first keymap
 */
void textio_SetKeymaps(uint24_t *IDS, uint8_t num_keymaps, char *keymap0, ...);

/**
 * Gets the number of available keymaps for the specified IDS.
 *
 * @note The number returned will be one less than the actual number of keymaps
 * in the IDS. There is no need to compensate for this (see introductory documentation).
 *
 * @param IDS Pointer to IDS
 * @return Number of keymaps
*/
uint8_t textio_GetNumKeymaps(uint24_t *IDS);

/**
 * Sets the initial keymap for textio_Input. The first keymap stored to the IDS
 * with textio_SetKeymaps has an index of 0; the second has an index of 1, and so on.
 *
 * @param IDS Pointer to IDS
 * @param keymap_num Number of keymap
 */
void textio_SetCurrKeymapNum(uint24_t *IDS, uint8_t number);

/**
 * Gets the current keymap number for the specified IDS.
 *
 * @param IDS Pointer to IDS
 * @return Current keymap number
*/
uint8_t textio_GetCurrKeymapNum(uint24_t *IDS);

/**
 * Gets the current keymap for the specified IDS.
 *
 * @param IDS Pointer to IDS
 */
uint24_t *textio_GetCurrKeymapPtr(uint24_t *IDS);

/**
 * Gets the codepoint that acts as the current keymap's indicator.
 *
 * @param IDS Pointer to IDS
 * @return Current keymap indicator
*/
char textio_GetCurrKeymapIndicator(uint24_t *IDS);

/**
 * Gets a pointer to the built-in TextIOC uppercase letters keymap.
 *
 * @return Pointer to keymap
*/
char *textio_GetUppercaseLettersKeymap(void);

/**
 * Gets a pointer to the built-in TextIOC lowercase letters keymap.
 *
 * @return Pointer to keymap
*/
char *textio_GetLowercaseLettersKeymap(void);

/**
 * Gets a pointer to the built-in TextIOC program_name letters keymap.
 *
 * @return Pointer to keymap
*/
char *textio_GetPrgmNameLettersKeymap(void);

/**
 * Gets a pointer to the built-in TextIOC numerical keymap.
 *
 * @return Pointer to keymap
*/
char *textio_GetNumericalKeymap(void);

/**
 * Creates an IDS and sets it up to use the TextIOC uppercase and lowercase letters keymaps.
 *
 * @note If the IDS memory allocation fails, \p name will be equal to \c NULL.
 *
 * @param name Name of the new IDS
 * @param xPos Starting x-position of the cursor
 * @param yPos y-position of the cursor
 * @param visible_width Width of visible input (in pixels)
*/
#define textio_CreateAlphaIDS(name, size, xPos, yPos, visible_buffer_width) \
do { name = textio_CreateIDS(size, xPos, yPos, visible_buffer_width, 2); \
if (name != NULL) { \
textio_SetKeymaps(name, 2, textio_GetUppercaseLettersKeymap(), textio_GetLowercaseLettersKeymap()); \
}; } while (0)

/**
 * Creates an IDS and sets it up to use the TextIOC numericl keymap.
 *
 * @note If the IDS memory allocation fails, \p name will be equal to \c NULL.
 *
 * @param name Name of the new IDS
 * @param xPos Starting x-position of the cursor
 * @param yPos y-position of the cursor
 * @param visible_width Width of visible input (in pixels)
*/
#define textio_CreateNumericalIDS(name, size, xPos, yPos, visible_buffer_width) \
do { name = textio_CreateIDS(size, xPos, yPos, visible_buffer_width, 1); \
if (name != NULL) { \
textio_SetKeymaps(name, 1, textio_GetNumericalKeymap()); \
}; } while (0)

/**
 * Creates an IDS and sets it up to use the TextIOC uppercase and lowercase letters keymaps as well
 * as the TextIOC numerical keymap.
 *
 * @note If the IDS memory allocation fails, \p name will be equal to \c NULL.
 *
 * @param name Name of the new IDS
 * @param xPos Starting x-position of the cursor
 * @param yPos y-position of the cursor
 * @param visible_width Width of visible input (in pixels)
*/
#define textio_CreateAlphaNumericalIDS(name, size, xPos, yPos, visible_buffer_width) \
do { name = textio_CreateIDS(size, xPos, yPos, visible_buffer_width, 3); \
if (name != NULL) { \
textio_SetKeymaps(name, 3, textio_GetUppercaseLettersKeymap(), textio_GetLowercaseLettersKeymap(), textio_GetNumericalKeymap()); \
}; } while (0)

/**
 * Creates an IDS and sets it up to use the TextIOC program_name letters keymap as well
 * as the TextIOC numerical keymap.
 *
 * @note If the IDS memory allocation fails, \p name will be equal to \c NULL.
 *
 * @param name Name of the new IDS
 * @param xPos Starting x-position of the cursor
 * @param yPos y-position of the cursor
 * @param visible_width Width of visible input (in pixels)
*/
#define textio_CreatePrgmNameIDS(name, size, xPos, yPos, visible_buffer_width) \
do { name = textio_CreateIDS(size, xPos, yPos, visible_buffer_width, 2); \
if (name != NULL) { \
textio_SetKeymaps(name, 2, textio_GetPrgmNameLettersKeymap(), textio_GetNumericalKeymap()); \
textio_SetPrgmNameFlag(ids, true); \
}; } while (0)

/**
 * Sets the key that activates textio_Input()'s clear action. Defaults to [clear].
 *
 * @note This function is not IDS-specific. The action will remain linked to the given key for all IDSes
 * until it is changed by the programmer.
 *
 * @param key Key
*/
void textio_SetClearKey(sk_key_t key);

/**
 * Sets the key that activates textio_Input()'s backspace action. Defaults to [del].
 *
 * @note This function is not IDS-specific. The action will remain linked to the given key for all IDSes
 * until it is changed by the programmer.
 *
 * @param key Key
*/
void textio_SetBackspaceKey(sk_key_t key);

/**
 * Sets the key that moves the cursor left. Defaults to the left arrow key.
 *
 * @note This function is not IDS-specific. The action will remain linked to the given key for all IDSes
 * until it is changed by the programmer.
 *
 * @param key Key
*/
void textio_SetCursorLeftKey(sk_key_t key);

/**
 * Sets the key that moves the cursor right. Defaults to the right arrow key.
 *
 * @note This function is not IDS-specific. The action will remain linked to the given key for all IDSes
 * until it is changed by the programmer.
 *
 * @param key Key
*/
void textio_SetCursorRightKey(sk_key_t key);

/**
 * Gets input from user and stores it in the data buffer of the specified IDS. The user is only
 * allowed to give input for the amount of time assigned to the IDS by textio_SetIDSTimer.
 *
 * @param IDS Pointer to IDS
 * @return Code of key pressed
*/
sk_key_t textio_TimedInput(uint24_t *IDS);

/**
 * Gets input from user and stores it in the data buffer of the specified IDS.
 *
 * @param IDS Pointer to IDS
 * @return Code of key pressed
*/
sk_key_t textio_Input(uint24_t *IDS);

/**
 * Sets the codepoint that will stand for the theta character for the current font.
 *
 * @note This codepoint will only be valid for the font that was being used when this function
 * was called.
 *
 * @param codepoint The codepoint for the theta character
*/
void textio_SetThetaCodepoint(uint8_t codepoint);

/**
 * Gets the codepoint for the theta character.
 *
 * @note This codepoint is not IDS-specific. It sets the theta character's codepoint for the
 * font in use.
 *
 * @return Codepoint for theta character
*/
char textio_GetThetaCodepoint(void);

/**
 * Converts any codepoints in \p name that correspond to the codepoint set by
 * textio_SetThetaCodepoint into the TI-OS theta codepoint (0x5B).
 *
 * @param name Pointer to the name of the program/appvar to convert
 * @return Pointer to the converted name
*/
char *textio_ConvertProgramAppvarName_TIOS(char *name);

/**
 * Converts any codepoints in \p name that correspond to the TI-OS theta codepoint into the
 * codepoint set by textio_SetThetaCodepoint.
 *
 * @param name Pointer to the name of the program/appvar to convert
 * @return Pointer to the converted name
*/
char *textio_ConvertProgramAppvarName_TextIOC(char *name);


/**
 * Print formatting options for textio_PrintText.
 *
 * @see textio_SetPrintFormat
*/
typedef enum {

	/**
	 * Enables left-margin-flush printing.
	*/
	TEXTIOC_PRINT_LEFT_MARGIN_FLUSH = 0x01,

	/**
	 * Enables right-margin-flush printing.
	*/
	TEXTIOC_PRINT_RIGHT_MARGIN_FLUSH = 0x02,

	/**
	 * Enables centered printing.
	*/
	TEXTIOC_PRINT_CENTERED = 0x03

} textio_print_format_options_t;

/**
 * Sets the print format for textio_PrintText.
 *
 * @see textio_print_format_options_t
 *
 * @param format Format option code
*/
bool textio_SetPrintFormat(uint8_t format);

/**
 * Gets the current print format.
 *
 * @return Current print format code
*/
uint8_t textio_GetPrintFormat(void);

/**
 * Sets the tab size.
 *
 * @note The tab size will be multiplied by the width of the current font's space to create the
 * actual pixel width of the tab.
 *
 * @param size Size of tab
*/
void textio_SetTabSize(uint8_t size);

/**
 * Gets the current tab size.
 *
 * @note This function returns the tab size, not the tab's actual pixel width.
 *
 * @return Current tab size
*/
uint8_t textio_GetTabSize(void);

/**
 * Prints a tab at the current cursor position.
*/
void textio_PrintTab(void);

/**
 * Prints a character (including tabs) at the current cursor position.
 *
 * @param character Character to print
*/
void textio_PrintChar(char character);

/**
 * Gets the width of the supplied character. This function also works for tabs, and it returns the
 * tab's actual pixel width.
 *
 * @param character Target character
 * @return Width of character
*/
uint8_t textio_GetCharWidth(char character);

/**
 * Gets the width of the supplied line.
 *
 * @param line Pointer to line
 * @param eol Pointer to the End-Of-Line
 * @return Width of line
*/
uint24_t textio_GetLineWidth(char *line, char *eol);

/**
 * Prints the supplied text in the current text window using the print format set by textio_SetPrintFormat.
 *
 * @param text Pointer to text
 * @param yPos y-position at which to start printing
*/
void textio_PrintText(char *text, uint8_t yPos);

/**
 * Returns a pointer to the \p line_num line in \p text.
 *
 * @param text Pointer to text
 * @param line_num Number of line
 * @return Pointer to desired line
*/
char *textio_GetLinePtr(char *text, uint8_t line_num);


#ifdef __cplusplus
}
#endif

#endif