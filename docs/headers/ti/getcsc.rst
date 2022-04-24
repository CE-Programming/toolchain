.. _getcsc:

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
For convenience, there are duplicate equates for the five keys with different functions;
in the table below, they are **emphasized.**

+---------------+-------------------+-----------------------+-------------------------+
| TI-84 Plus CE | Equate            | TI-83 Premium CE      | Equate                  |
+===============+===================+=======================+=========================+
| Y=            | :code:`sk_Yequ`   | f(x)                  | :code:`sk_Yequ`         |
+---------------+-------------------+-----------------------+-------------------------+
| Window        | :code:`sk_Window` | Fenetre               | :code:`sk_Window`       |
+---------------+-------------------+-----------------------+-------------------------+
| Del           | :code:`sk_Del`    | Suppr                 | :code:`sk_Del`          |
+---------------+-------------------+-----------------------+-------------------------+
| **Apps**      | :code:`sk_Apps`   | **Matrice**           | :code:`sk_Matrix`       |
+---------------+-------------------+-----------------------+-------------------------+
| Clear         | :code:`sk_Clear`  | Annul                 | :code:`sk_Clear`        |
+---------------+-------------------+-----------------------+-------------------------+
| **x^-1**      | :code:`sk_Recip`  | **<>**                | :code:`sk_AnsFrac`      |
+---------------+-------------------+-----------------------+-------------------------+
| **Sin**       | :code:`sk_Sin`    | **Trig**              | :code:`sk_Trig`         |
+---------------+-------------------+-----------------------+-------------------------+
| **Cos**       | :code:`sk_Cos`    | **Resol**             | :code:`sk_Solver`       |
+---------------+-------------------+-----------------------+-------------------------+
| **Tan**       | :code:`sk_Tan`    | **Fraction template** | :code:`sk_Frac`         |
+---------------+-------------------+-----------------------+-------------------------+

.. contents:: :local:
   :depth: 3

API Documentation
-----------------

.. doxygenfile:: ti/getcsc.h
   :project: CE C/C++ Toolchain
