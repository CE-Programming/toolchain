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

Getting GetCSC codes with keypadc 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This code returns the same keycodes that `os_GetCSC()` produces.

.. code-block:: c

   // code by jacobly
   uint8_t get_single_key_pressed(void) {
       static uint8_t last_key;
       uint8_t only_key = 0;
       kb_Scan();
       for (uint8_t key = 1, group = 7; group; --group) {
           for (uint8_t mask = 1; mask; mask <<= 1, ++key) {
               if (kb_Data[group] & mask) {
                   if (only_key) {
                       last_key = 0;
                       return 0;
                   } else {
                       only_key = key;
                   }
               }
           }
       }
       if (only_key == last_key) {
           return 0;
       }
       last_key = only_key;
       return only_key;
   }


API Documentation
-----------------

.. doxygenfile:: keypadc.h
   :project: CE C/C++ Toolchain
