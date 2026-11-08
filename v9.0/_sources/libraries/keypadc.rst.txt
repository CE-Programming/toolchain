.. _keypadc_h:

keypadc.h
=========

.. code-block:: c

    #include <keypadc.h>

The keypadc library is used for quickly polling the status of the keys in the keypad.
It supports multi-key presses, and can be used for extremely responsive input compared to OS routines such as :code:`os_GetCSC()`.

.. contents:: :local:
   :depth: 3

Helpful key dection
-------------------

Handling key detection properly is a major requirement for a lot of programs.
Detecting a hold can be rather straightforward, but things like a press, release, can sometimes be rather confusing at first.

Detecting a single press
^^^^^^^^^^^^^^^^^^^^^^^^

When a key is first pressed, we only want to trigger on that event.
The following code sets up a simple rising edge detector to catch this.

.. code-block:: c

    bool key, prevkey;
    key = kb_Data[1] == kb_2nd;

    if (key && !prevkey) {
        // ...
    }
    prevkey = key;

Detecting a single release
^^^^^^^^^^^^^^^^^^^^^^^^^^

When a key is released we only want to trigger on that event.
The following code sets up a simple falling edge detector to catch this.

.. code-block:: c

    bool key, prevkey;
    key = kb_Data[1] == kb_2nd;

    if (!key && prevkey) {
        // ...
    }
    prevkey = key;

API Documentation
-----------------

.. doxygenfile:: keypadc.h
   :project: CE C Toolchain
