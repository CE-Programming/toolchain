.. _lcddrvce_h:

lcddrvce.h
==========

.. code-block:: c

    #include <lcddrvce.h>

The :code:`lcddrvce` library is used for interacting with the Sitronix ST7789 LCD controller.

.. contents:: :local:
   :depth: 3

Overview
--------

This library exposes interfaces to send any supported command to the LCD (this excludes read commands, which don't work reliably on CE hardware).

Communication with the LCD controller is done over an SPI connection; however, the SPI hardware is also used to communicate with the ARM coprocessor on Python models.
As such, the SPI hardware is not always set up properly to communicate with the LCD controller, and this library exists to provide a reliable and performant interface to the LCD across calculator models.

For additional information about the LCD controller and its commands, check out the documentation on `WikiTI <https://wikiti.brandonw.net/index.php?title=84PCE:LCD_Controller>`__.

Library Initialization
----------------------

The :code:`lcd_Init` and :code:`lcd_Cleanup` functions provide reference-counted initialization and cleanup of the SPI configuration.
That means multiple calls to :code:`lcd_Init()` are allowed, and the SPI hardware is restored to its original settings only after the same number of calls to :code:`lcd_Cleanup()`.
Since the configuration is set differently than the OS's default settings for performance reasons, it's not allowed to power off the calculator without cleaning up the library first.
This means if calling certain functions like :code:`os_GetKey` which can auto-power-down the calculator, either the LCD library should be cleaned up or auto-power-down should be disabled with :code:`os_DisableAPD()`.
When using this library as part of another library's implementation and performance is not critical, it's safest to call both :code:`lcd_Init()` and :code:`lcd_Cleanup()` each time commands need to be sent.
That way, users of the library will be able to cleanup the SPI configuration whenever they need to.

API Documentation
-----------------

.. doxygenfile:: lcddrvce.h
   :project: CE C/C++ Toolchain
