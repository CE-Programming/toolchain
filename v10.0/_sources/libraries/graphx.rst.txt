.. _graphx_h:

graphx.h
========

.. code-block:: c

    #include <graphx.h>

The :code:`graphx` library implements efficient graphics routines from everything to drawing sprites, shapes, and tilemaps.
This allows a programmer to easily add quality graphics to their program without needing to worry about the low-level implementation details.

.. contents:: :local:
   :depth: 3

Default Palette
---------------

This is the default palette used by graphx.
This palette can be modified at any time with different colors.

.. image:: images/graphx_palette.png
   :align: center

Coordinate System
-----------------

The graphx library coordinate system consists of the horizontal (:code:`x`) and vertical (:code:`y`) components of the screen.
Pixel coordinates are generally expressed as an :code:`x` and :code:`y` pair, such as (:code:`x`, :code:`y`).
The graphx library uses the top left of the screen as pixel coordinate (0, 0), while the bottom right of the screen is pixel coordinate (319, 239).
The defines :code:`GFX_LCD_WIDTH` and :code:`GFX_LCD_HEIGHT` can be used to get the LCD screen width and height respectively.

Clipped vs. Unclipped
---------------------

The graphx library contains many similar functions, e.g. :code:`gfx_Sprite` and :code:`gfx_Sprite_NoClip`.

As the name suggests, the **_NoClip** variant of a routine performs no clipping.
Clipping is the process of checking if parts (or all) of an object to be drawn are outside the window bounds and skipping drawing these out of bounds parts.
This checking process takes time.
If you can be sure that an object to be drawn is fully within the bounds of the screen, the clipping process can be safely skipped by using the **_NoClip** variant of the routine.

**Do not use the _NoClip variant of a routine if you can not be sure that the object to be drawn is fully within the bounds of the screen. Doing so may result in corrupted graphics or memory.
This is because the screen itself is represented as a region of memory. If you draw outside the bounds of that region, you risk overwriting other, possibly important data. This can cause corruption, and can cause crashes.**

Partial Redraw
--------------

Partial redraw applies when you are moving a sprite against a static background.
Sometimes, it can be too slow to redraw the entire screen just to move a small portion of it.
Partial redraw saves a copy of what is behind the sprite, and draws it when the sprite moves again.
For example, in a simple Pong game, if a white ball is drawn on a black background, instead of redrawing the entire screen each frame, you can redraw a small region around the ball to erase it.

Sample Implementation
^^^^^^^^^^^^^^^^^^^^^

A brief summation of the partial redraw using graphx is:

* Allocate space for a temporary sprite.
* When the background is drawn, a small copy of it is saved to the temporary sprite.
* After the background is drawn, the sprite is drawn as normal.
* Upon movement, the sprite is erased using the temporary sprite and the coordinates are updated.
* The section of background with the updated coordinates is stored to the temporary sprite and the process repeated.

This is implemented using somewhat pseudo code:

.. code-block:: c

    int x = 0;
    int y = 0;
    gfx_sprite_t *behind_sprite = gfx_MallocSprite(SPRITE_WIDTH, SPRITE_HEIGHT);

    // ...draw the background code  here...

    // set initial sprite state
    gfx_GetSprite(behind_sprite, x, y);
    gfx_TransparentSprite(sprite, x, y);

    do {
        // if we don't need to move, loop
        if (no_move) continue;

        // clear out the old sprite
        gfx_Sprite(behind_sprite, x, y);

        // ...movement code here...
        // updates x and y

        // get the new background and draw the moved sprite
        gfx_GetSprite(behind_sprite, x, y);
        gfx_TransparentSprite(sprite, x, y);
    } while (moving);

Buffering Graphics
------------------

Buffering is a fancy method in order to prevent graphics from being displayed as they are being drawn.
It is used primarily to eliminate visible draws which can make an application look amateurish, sluggish, or appear to flicker.

When graphics routines are buffered, they draw offscreen (non-visible) portion of memory, so the user doesn't see the partial drawing.
This is accomplished in one line with the following routine, usually placed directly after calling `gfx_Begin()`:

.. code-block:: c

    gfx_SetDrawBuffer();

The next part is deciding how the drawn graphics should be displayed to the user.

Method 1 (Copying/Blitting)
^^^^^^^^^^^^^^^^^^^^^^^^^^^

The first method is to copy (commonly referred to as 'blitting') whatever is in the buffer to the visible screen.
The simplest way is to call:

.. code-block:: c

    gfx_BlitBuffer();

Which will copy/blit the entire buffer to the screen.
Alternatively, `gfx_BlitLines()` and `gfx_BlitRectangle()` and the other variations are used to specify the blitting bounds.
This flickers less than normal drawing because having many small copy operations (like drawing sprites) is slower than one large copy operation (blitting the buffer to the screen). This means that a blit operation is less likely to get caught by a screen refresh than a bunch of sprite operations.

Method 2 (Buffer Swapping)
^^^^^^^^^^^^^^^^^^^^^^^^^^

Buffer swapping swaps the visible screen with an offscreen buffer, leaving the contents on both.
Whatever is currently on the screen will become the graphics buffer, and whatever is in the graphics buffer will be displayed on the screen.
The code to swap the visible screen with non-visibile buffer is:

.. code-block:: c

    gfx_SwapDraw();

What actually happens is shown below, 'graphics' is simply where the graphics routines will draw to.

.. image:: images/graphx_buffer.png
   :align: center

This method is really useful when you are redrawing all of the graphics each frame, and requires more work to handle if you only wish to do a partial redraw.

Pros and Cons
^^^^^^^^^^^^^

Buffering is slower than drawing to the main screen, but greatly improves perceived performance which is extremely important in graphical applications.

**Blitting**: Easy, simply a copy to the screen.

**Swapping**: Requires more programmer management (sometimes), faster than blitting.

Creating Sprites
----------------

Sprites are images that contain pixel data that can be drawn via graphx functions.
The CE C Toolchain includes `convimg <https://github.com/mateoconlechuga/convimg>`_, which is used to convert images in PNG or similar formats into binary data that can be used by graphx.

Getting Started
^^^^^^^^^^^^^^^

We are going to begin by taking a look at an example program to familiarize ourselves with how to run and configure convimg.

Open the `graphx/sprites` example, and navigate to the `src/gfx` folder.

The image :code:`oiram.png` is the sprite that wants to be converted, and :code:`convimg.yaml` is used to configure how the image should be converted.

Open :code:`convimg.yaml` in a text editor, which contains the below lines.
Run the command :code:`convimg --help`. This outputs the readme for convimg, and what each of the various commands do.
You can also find the readme online, available `here <https://github.com/mateoconlechuga/convimg/blob/master/README.md>`_.

.. code-block:: yaml

    palettes:
      - name: global_palette
        fixed-entries:
          - color: {index: 0, r: 255, g: 0, b: 128}
          - color: {index: 1, r: 255, g: 255, b: 255}
        images: automatic

    converts:
      - name: sprites
        palette: global_palette
        transparent-color-index: 0
        images:
          - oiram.png

    outputs:
      - type: c
        include-file: gfx.h
        palettes:
          - global_palette
        converts:
          - sprites

Converting Sprites
^^^^^^^^^^^^^^^^^^

Converting sprites requires you to type :code:`make gfx` instead of :code:`make`.
Any time you change an image or the :code:`convimg.yaml`, you will need to execute this command.

.. image:: images/graphx_sprites.png
   :align: center

You can now :code:`make` the project as you would any of the other examples.

Explanation of output
"""""""""""""""""""""

Sprites used in the graphx library are allowed 8 bits per pixel *(aka 8bpp)*, which allows for a total of :code:`256` colors.
As shown in the previous image, convimg was able to create a suitable palette for :code:`oiram.png` with 15 colors.
Once the palette is generated, convimg outputs C headers and source files that are automatically picked up by the toolchain and compiled into the final program.

API Documentation
-----------------

.. doxygenfile:: graphx.h
   :project: CE C/C++ Toolchain
