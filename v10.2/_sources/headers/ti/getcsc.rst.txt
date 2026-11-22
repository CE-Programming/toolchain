.. _getcsc_h:

ti/getcsc.h
===========

.. code-block:: c

    #include <ti/getcsc.h>

Naturally, TI's operating system also has its own keyboard driver.
You can easily use it instead of the :code:`keypadc` library, and is particularly suited to non-game programs.

The OS's interrupt handler handles the keyboard driver and caches a scancode when it detects a key press.
You can use this scancode directly without any translation of 2nd and alpha through the :code:`os_GetCSC` function.

TI-83 Premium CE
----------------

Some keys on the TI-83 Premium CE are labeled differently, and some have completely different functions.
For convenience, there are additional equates for the TI-83 Premium CE names.
In the table below, the five keys with different functions are **emphasized.**

+---------------+-------------------+-----------------------+-------------------------+
| TI-84 Plus CE | Equate            | TI-83 Premium CE      | Equate                  |
+===============+===================+=======================+=========================+
| Y=            | :code:`sk_Yequ`   | f(x)                  | :code:`sk_Fx`           |
+---------------+-------------------+-----------------------+-------------------------+
| Window        | :code:`sk_Window` | Fenetre               | :code:`sk_Fenetre`      |
+---------------+-------------------+-----------------------+-------------------------+
| Del           | :code:`sk_Del`    | Suppr                 | :code:`sk_Suppr`        |
+---------------+-------------------+-----------------------+-------------------------+
| **Apps**      | :code:`sk_Apps`   | **Matrice**           | :code:`sk_Matrice`      |
+---------------+-------------------+-----------------------+-------------------------+
| Clear         | :code:`sk_Clear`  | Annul                 | :code:`sk_Annul`        |
+---------------+-------------------+-----------------------+-------------------------+
| **x^-1**      | :code:`sk_Recip`  | **<>**                | :code:`sk_TglExact`     |
+---------------+-------------------+-----------------------+-------------------------+
| **Sin**       | :code:`sk_Sin`    | **Trig**              | :code:`sk_Trig`         |
+---------------+-------------------+-----------------------+-------------------------+
| **Cos**       | :code:`sk_Cos`    | **Resol**             | :code:`sk_Resol`        |
+---------------+-------------------+-----------------------+-------------------------+
| **Tan**       | :code:`sk_Tan`    | **Fraction template** | :code:`sk_Frac`         |
+---------------+-------------------+-----------------------+-------------------------+

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/getcsc.h
   :project: CE C/C++ Toolchain
