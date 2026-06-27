.. _fontlibc_h:

fontlibc.h
==========

.. code-block:: c

    #include <fontlibc.h>

fontlibc was designed under a "mechanism not policy" sort of philosophy.
Rather than attempt to provide as many fancy features as a programmer could want, fontlibc tries to provide fast, basic routines that can be used to build the additional functionality you want.
For example, word-wrap is not directly provided, but can be implemented using :code:`fontlib_SetAlternateStopCode` and :code:`fontlib_GetStringWidth`.
fontlib hopes to provide enough performance to be usable in games, while providing powerful enough basic features for fancy GUIs and document editors.

.. contents:: :local:
   :depth: 3

Text Windowing
--------------

To assist in text layout, fontlibc provides for a text window, which automatically confines text to appear in a specific rectangular area of the screen.
This feature may be useful for dialogs and scrolling large blocks of text.
Use :code:`fontlib_SetWindow` to set the current window bounds.
Use :code:`fontlib_SetNewlineOptions` to control how :code:`fontlib_DrawString` behaves when it reaches the right edge of the text window.

Aligning Text
-------------

Implementing centered text, right-aligned text, and word wrap requires being able to compute the width of a word or string of text.
The routine :code:`fontlib_GetStringWidth` provides this functionality.

If you call :code:`fontlib_SetAlternateStopCode(' ')`, :code:`fontlib_GetStringWidth` and :code:`fontlib_DrawString` will stop drawing on spaces, giving you a chance to check if the next word will fit on screen.
You can use :code:`fontlib_GetLastCharacterRead()` to find out where :code:`fontlib_GetStringWidth` or :code:`fontlib_DrawString` stopped, and, after handling the space, then pass that address (plus one) again to :code:`fontlib_GetStringWidth` or :code:`fontlib_DrawString` to resume processing at where it left off before.

Text Control Codes
------------------

Embedded control codes are a popular way of managing style and formatting information in string.
fontlibc only natively recognizes two types of control codes: NULL (0) as a stop code and a user-specified alternate stop code, and a user-specified newline code (defaults to 0x0A---ASCII LF and standard Linux style).
However, you can add your own control codes with :code:`fontlib_SetFirstPrintableCodePoint`.
When any code point less than the first printable code point is encountered, fontlibc stops string processing and returns to allow you to handle the control code yourself using :code:`fontlib_GetLastCharacterRead`.

Transparent Text
----------------

Part of providing high-performance is not painting a single pixel more than once.
To assist with this goal, fontlibc provides for both transparent and opaque text backgrounds.
Use :code:`fontlib_SetTransparency(true)` if you need to paint text over a background other than a solid color.
If you turn transparency off, however, fontlibc will paint both background and foreground pixels for you, eliminating the time needed to erase those pixels before painting over that area.

Line Spacing
------------

Since a block of text may not always be the same size, fontlibc provides :code:`fontlib_ClearEOL` for erasing the remainder of a line of text without needing to pad it with spaces.
This action can also be performed automatically after embedded newlines in text and on normal wrapping with :code:`fontlib_SetNewlineOptions`.

Additional blank vertical space around text can improve readability in large blocks of text.
:code:`fontlib_SetLineSpacing` allows you to set this behavior.
Fonts may specify default additional spacing that is automatically applied when calling :code:`fontlib_SetFont`.
In GUIs and games where the benefits of legibility are outweighed by more aggressive use of vertical space, you can force the default spacing to zero after using :code:`fontlib_SetFont` with :code:`fontlib_SetLineSpacing`.

API Documentation
-----------------

.. doxygenfile:: fontlibc.h
   :project: CE C Toolchain
