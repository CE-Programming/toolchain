.. _hardware:

Calculator Hardware Overview
===============================

This is a low-level overview of the TI-84 Plus CE's hardware from a programmer's perspective.

Note: In France, the TI-84 Plus CE is called the TI-83 Premium CE.
It also has a slightly different OS with additional functionality, but the hardware is the same.

A Brief History of TI Graphing Calculator Hardware
--------------------------------------------------

While the TI-84 Plus CE's hardware is very different from previous models,
its software is directly derived from the software of previous models.
Understanding the history of the TI-8x line gives some context to why the TI-84 Plus CE is the way it is.

TI's first graphing calculator was the TI-81, released in 1990.
It took the then-popular idea of a "pocket computer" and turned it into an educational tool for students:
not only did it handle scientific computations, but it could also graph equations, do some matrix operations, and was programmable in BASIC, which was a popular language at the time.
At the time, most homes did not have any kind of computer (or tablet or smartphone), and computers costs thousands of dollars;
the TI-81 cost just $110 and students could learn programming on a portable, personal device.

Since 1990, TI has continued to improve their offerings incrementally, adding more functionality to the TI-81's original software.
The TI-83 (non-Plus), introduced in 1996, has nearly all of the mathematical functionality of the TI-84 Plus CE.
The TI-83 Plus, introduced in 1999, added flash memory, allowing more data to be stored in the calculator's "archive," as well as installing "Flash (TM)" applications.
The TI-84 Plus, introduced in 2004, adds a USB port and more RAM (but hidden from the user).
The TI-84 Plus C SE, introduced in 2013, was TI's first attempt to add color to the TI-81's lineage.
Unfortunately, there were too many pixels for too slow a CPU, and it was discontinued soon after.
Thus came the TI-84 Plus CE.

Up until the TI-84 Plus CE, the hardware of the TI-8x series was improved only incrementally.
The TI-84 Plus C SE made it clear that no further incremental improvements were possible, and thus for the TI-84 Plus CE TI radically redesigned the entirety of the calculator's hardware.
However, TI made sure to choose a CPU that was compatible with the TI-84 Plus's so that they could avoid completely rewriting the calculator's software.
Thus, while the TI-84 Plus CE hardware is completely unlike previous models, the software is still very similar.

The Z80 CPU
^^^^^^^^^^^

The TI-81 used a Zilog Z80 8-bit CPU, which had been popular in early PCs from the late 70s and early 80s.
Newer, faster CPUs made the Z80 obsolete in PCs, but it remained adequate for a student's calculator.
With the TI-83 Plus and TI-84 Plus, TI kept the same Z80 CPU, but they increased its speed, from 2 MHz on the TI-81 to 15 MHz on the TI-84 Plus.
Unfortunately, the Z80 is just not fast enough for a full color screen (at least not without a graphics accelerator of some kind),
so the TI-84 Plus CE switched to the Z80's most modern successor, the eZ80.

Running From ROM
^^^^^^^^^^^^^^^^

Unlike modern computers (and indeed the TI Nspire series), the TI-81's CPU did not copy code from a storage device (hard drive or internal flash) before executing it.
Instead the CPU is slow enough and the ROM fast enough that the CPU can fetch each byte from the ROM the moment it's needed, without any waiting.
Today, flash memory has replaced ROMs in nearly all applications, including in the TI-83 Plus and its successors.
Running code directly from a flash memory instead of copying it to RAM first is known as XIP (execute-in-place) flash.

The TI-84 Plus CE continues to use an XIP design like the TI-83 Plus before it.
XIP designs are actually common in microcontrollers like the Arduino.
Usually, the microcontroller has the flash memory built-in, but some, like the Raspberry Pi Pico, do use external flash.

The original Z80 could only directly access 64 K of memory, making accessing additional memory awkward and slow.
The TI-81 has just 64 K of ROM and 8 K of RAM, while the TI-84 Plus C SE had 4 MB of flash and 128 K of RAM, and getting access to everything was complicated!

The TI-84 Plus CE
-----------------

As mentioned, the TI-84 Plus CE's hardware is radically different from its predecessors.

Versions
^^^^^^^^

From time to time, TI revises their calculator hardware.

- Starting with revision code I, TI removed the CPU's interrupt vectoring feature.
- In 2019, the TI-84 Plus CE went through a major revision that significantly improved performance by adding a cache in front of the XIP flash.
- At the same time, TI added a serial link to allow communication with an optional Python co-processor.
  This was originally limited to the French market, but TI has since made Python available in all markets.

The 24-bit eZ80 CPU
^^^^^^^^^^^^^^^^^^^

The TI-84 Plus CE's eZ80 is much faster than the Z80 even when running at the same speed, in some cases up to ten times as fast,
and on the TI-84 Plus CE, the CPU is clocked at 48 MHz, instead of the TI-84 Plus's 15 MHz.
This makes running C code much more practical than it was on previous models, and TI takes advantage of that on the CE.
At the same time, the eZ80 can easily run old Z80 software with only minor changes,
allowing TI to add new functionality written in C to their old Z80 assembly code.

The eZ80 expands the memory space from 64 K to 16 MB, allowing easy access to all of the calculator's memory.
Unfortunately, while the Z80 has perfectly-sensible 16-bit addresses, with an address being two bytes in size,
the eZ80 uses 24-bit addresses, meaning each address is three bytes long.
This is an unusual size, and it also results in the toolchain having 24-bit-size :code:`int` .

Consequently, the eZ80 can natively access variables that are either one byte (8 bits, :code:`char`) or three bytes (24 bits, :code:`int`) in size,
but two-byte (16 bits, :code:`short`) and four-byte (32 bits, :code:`long`) variables are actually a little slower for the CPU to access.
The :code:`<stdint.h>` header contains declarations for the standard 8-, 16-, and 32-bit types, 
Furthermore, the eZ80 is a little slower at signed arithmetic, so you should use :code:`unsigned` when possible.

The :code:`<stdint.h>` header contains declarations for the standard 8-, 16-, and 32-bit types, as well as the eZ80's 24-bit type.
Here's a table:

==================   ====================================   =======    ========   ===========   ==========================   ==========================
C Type               :code:`<stdint.h>` Names               CE Bits    CE Bytes   Common Size   CE :code:`unsigned` Range    CE :code:`signed` Range
==================   ====================================   =======    ========   ===========   ==========================   ==========================
:code:`char`         :code:`uint8_t`, :code:`int8_t`        8          1          8/1           0 to 255                     -128 to 127
:code:`short`        :code:`uint16_t`, :code:`int16_t`      16         2          16/2          0 to 65535                   -32768 to 32767
:code:`int`          :code:`uint24_t`, :code:`int24_t`      24         3          32/4          0 to 16777215                -8388608 to 8388607
:code:`long`         :code:`uint32_t`, :code:`int32_t`      32         4          32/4          0 to 4294967295              -2147483648 to 2147483647
:code:`long long`    :code:`uint64_t`, :code:`int64_t`      64         8          64/8          0 to a lot                   -negative lot to a lot
:code:`void*`        :code:`uintptr_t`, :code:`ptrdiff_t`   24         3          64/8          All of RAM and the archive   N/A
==================   ====================================   =======    ========   ===========   ==========================   ==========================

"Common Size" is the size in bit/bytes of the type that Windows uses, as well as many other platforms;
on some platforms, the types are larger than in this toolchain.

Floating-Point Numbers
^^^^^^^^^^^^^^^^^^^^^^

Perhaps surprisingly, even though the Z80 is used in a calculator, the CPU itself does not have any concept of :code:`float` or :code:`double`.
The circuits that modern CPUs use to handle such types is large and complicated, and simply wasn't feasible in the 70s when the Z80 was designed.
Therefore, software has to implement that functionality.

Like the Z80, the eZ80 also lacks native support for float-point arithmetic, so :code:`float` is slower than :code:`int`.
Furthermore, in the toolchain, :code:`float` and :code:`double` are actually treated the same (this is allowed by the C standard).

In the toolchain, :code:`float` is the standard IEEE 32-bit float.
However, IEEE floats have limited precision and have unintuitive rouding behavior.
So when TI designed the TI-81, they wrote their own special floating-point number format, which is much more suitable for precision scientific calculations.
Unfortunately, it also much slower.

This, however, has nothing to do with the calculator's hardware, and is instead covered on a different page.

The Memory Map
^^^^^^^^^^^^^^

Both flash and RAM are mapped into the eZ80's address space.
This means that a pointer may point to RAM or flash (or something else!) depending on its value.

====================================    ====================
Pointer Value                           Memory Accessed [1]_
====================================    ====================
:code:`0x000000` to :code:`0x3FFFFF`    Flash
:code:`0x400000` to :code:`0xCFFFFF`    Nothing
:code:`0xD00000` to :code:`0xD3FFFF`    RAM
:code:`0xD40000` to :code:`0xD657FF`    VRAM
:code:`0xD65800` to :code:`0xFFFFFF`    I/O
====================================    ====================

.. [1] WikiTI has more details at https://wikiti.brandonw.net/index.php?title=84PCE:Wait_States

How does a CPU tell a USB port to send data to a device?
Today, most CPUs use something called memory-mapped I/O.
This means that reading from or writing to special address (pointers) won't actually access memory, but instead sends a command or query to a hardware device.

For example, there is no RAM or flash at the address :code:`0xF60024`,
but if you write to that address, the LCD backlight controller will know you're trying to talk it and change the LCD's brightness.
Similarly, if you read from that address, the backlight controller will respond with the current backlight value.
The toolchain exposes these special addresses as variables you can read and write.

.. code-block:: c

    #include <sys/lcd.h> // Gets access to the LCD's special memory addresses
    
    // Later in your program
    // Show the current backlight level by reading it directly from hardware:
    printf("Current backlight level: 0x%2X\n", lcd_BacklightLevel);

Flash Memory
^^^^^^^^^^^^

Archived variables, the operating system, and applications, are all stored in flash.
While you can freely read any and all of flash, the calculator's hardware prevents you from writing to flash, and in fact, attempting to do so will cause a crash.
The calculator's operating system works with special hardware to enforce this restriction in order to prevent students from patching the OS to let them cheat.
Consequently, the only way to store data in flash is to create a variable in RAM and then archive it.
The :ref:`fileioc library <fileioc_h>` makes this easy.

Because teachers (and therefore TI's management) get very worked up by cheating, the toolchain does not (and will not) provide any means of bypassing this restriction.

The LCD
^^^^^^^

The TI-84 Plus CE's display is an LCD with 320 by 240 pixels.
The LCD technically supports 18-bit color, but it has fairly mediocre color.
The LCD is actually a portrait display, rotated 90 degrees;
software configures the LCD controller to present the illusion of a landscape display.
This, however, does result in the diagonal line that plagues :code:`graphx`.

The LCD Controller
^^^^^^^^^^^^^^^^^^

The LCD controller is a logic block that sends pixels from VRAM to the physical display.
TI's operating system uses VRAM in a 16-bits-per-pixel format, but the LCD controller also supports other formats:

- 24-bit color, which uses way too much RAM;
- other 16- and 15-bit color formats;
- 8-bit palettized color, using one byte per pixel and allowing double bufferiing;
- 4-bit palettized color, using even less RAM and packing in two pixels per byte;
- 2-bit and 1-bit palettized color modes, packing in four or eight pixels per byte.

The :code:`graphx` library puts the controller in 8-bit mode, which is faster (half as much data),
and allows double buffering.
There are currently no libraries for using other graphics modes.
You'll even have to write your own routines if you want use 16-bit color mode.

Direct access to the LCD controller's control registers is provided in the :code:`sys/lcd.h` header.

The LCD Driver
^^^^^^^^^^^^^^

Internal to the LCD panel is a chip-on-glass LCD driver.
It translates digital color values into analog voltages that drive the physical pixels.
The LCD driver also has an internal graphics RAM (GRAM) of its own.
It is possible to disable the LCD controller and send pixels directly to the LCD driver,
but there is no toolchain support for that.

The Keyboard
^^^^^^^^^^^^

The calculator's keypad is organized as a generic key matrix.
You can directly read the key matrix using the :code:`keypadc` library.
However, for simple programs, it is often easier to let the operating system handle the keypad.
This can be done using the :code:`ti/getcsc` or :code:`ti/getkey` headers.

Real-Time Clock
^^^^^^^^^^^^^^^

The calculator has a dedicated real-time clock (RTC) circuit that keeps track of the time and date.
Most digital devices that track real time use a 32768 Hz crystal, and the calculator is no different.

The :code:`sys/rtc.h` header provides direct access to the clock hardware.
While you can easily directly read the clock's time, the header also gives you access to OS
routines that also process the time and date into more a human-readable form.

Timers
^^^^^^

The RTC only tracks time to the nearest second.
If you want sub-second timing, there are also hardware timers that provide more precision.
The :code:`sys/timers.h` header provides access to the timers.

USB
^^^^^^

The calculator has a USB port, of course, but the toolchain does not yet support it.
Work on a USB driver is ongoing in the :code:`usbdrvce` branch on the toolchain.

The :code:`sys/basicusb.h` allows you to check if the battery is currently being charged, and that's about it.

Protected Hardware
^^^^^^^^^^^^^^^^^^

Some of the calculator's hardware is protected, meaning normal programs cannot access it.
The protection is linked to the protection on the flash chip (mentioned above), and the intention is that only the calculator's operating system can access protected hardware.

- The calculator has an SHA accelerator block.
  For some reason it is protected, so there isn't much useful to say about it.
- System configuration and power control are protected.
- In some markets, the CE comes with an additional LED on the front that blinks when the calculator is in exam mode.
  Naturally, user programs cannot activate this LED to prevent programs from faking exam mode.

Wait States
^^^^^^^^^^^

When TI designed the TI-84 Plus CE, they wanted to save money by using standard logic blocks they could just buy pre-designed.
These logic blocks were designed for use with ARM CPUs.
Unfortunately, TI did an abysmal, atrocious, awful job of integrating the eZ80 CPU with the ARM-oriented logic blocks.

Fundamentally, the issue is that the eZ80, as a successor to the Z80, is designed to be used with low-speed, zero-lantency memory.
However, ARM CPUs are optimized for high-speed, high-latency memory.
TI failed to take this into account, so the eZ80 is unable to take advantage of the extra speed, while getting the full brunt of the high latency.
For the version of the TI-84 Plus CE released in 2015, this results in the eZ80 CPU spending some 85 % of its time stalled, unable to do anything useful.
Yes, the CPU litterally runs as though it's only clocked at around 6 MHz (equivalent to a Z80 at around 50 MHz).
In 2019, TI released a new version of the TI-84 Plus CE that improves this significantly: now the CPU only spends about two-thirds of its time stalled.

This isn't really important for toolchain users; there's nothing you can do about it.
I just feel the need to tell everyone about TI Education's bad engineering in the hope that they'll one day feel enough shame to do better.
Because TI *does* have good engineers; they just apparently weren't employed when designing the TI-84 Plus CE.
