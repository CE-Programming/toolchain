.. _coding_guidelines:

General Coding Guidelines
=========================

If you are new to the C language and are looking for some pointers to improve your coding style, this page is for you!
These suggestions should help you avoid common pitfalls, and make your code easier to manage.

Style Consistency
-----------------

This is a big one.
When programming, it is important to choose a coding style that you prefer and **stick with it**.
For instance, if you prefer using 4 spaces to indent your code, use that everywhere -- don't mix tabs and spaces!
If your variables are :code:`snake_case` or :code:`camelCase` -- use the same format everywhere.
This goes for function naming too.

Some additional style guidelines:

- Try to keep lines 80 characters or less. This will promote less indentation and better coding design, as well as avoid insanely long variable names. If you have more than 3 levels of indentation, it's probably time to rethink your code.
- Use consistent bracing formats; if your braces all start on a new line, don't mix them. It is especially helpful to always use braces even on single-line conditional statements as it will avoid spurious bugs from popping up.
- Try to keep functions at 100 lines or less. Any more and the function should be broken out, as this will increase readability and make it easier for you 6 months later to understand what you wrote.
- It doesn't really matter *what* your style is as long as it is consistent! People will be more inclined to help and contribute to your code if you keep it neat.

Use Descriptive Naming
^^^^^^^^^^^^^^^^^^^^^^

This is a relatively minor one, but try to give functions and variables useful and unique names.
For example, :code:`int player_x` is more descriptive than :code:`int x`, and :code:`void handle_user_input(void)` is more useful than :code:`void do_things(void)`.
The name should tell you why it exists, what it does, and how it is used.
If a name requires a comment, then the name is useless.

Some helpful tips:

- Use pronounceable names.
- Beware of using names which vary in small ways. (e.g. "player_x" and "player_xx").
- Use intention revealing names.

Avoid Using Comments
--------------------

Code should have a minimal number of comments in it.
Comments aren't code; they are for a human to convey what a particular portion of code is for to another human.
Using comments leads to issues where **a)** the comments don't match the code, **b)** they are either superfluous or useless, **c)** they are flat out incorrect or outdated, or **d)** they add noise to the code itself and make it more difficult to read.

It is much easier to read code without having to also read comments that don't convey any helpful information.
Comments should be used in cases where it is difficult for someone reading the code to understand exactly what is happening.
They should ideally describe the "what" of the code, not the "how" or the "why", or the "who".

Comments should ideally be kept fairly short and to the point.
This is an example of a bad comment:

.. code-block:: c

    //functions
    void optix_InitializeGUIState(void) {

    }

The "functions" comment adds no value here.
The name of the function provides more information than the comment does, which is how it should be.

Avoid Commenting Unused Code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A lot of people when they program will change a few lines, or try many different iterations of code in an attempt to get something working.
The code that doesn't make it is usually commented out like below:

.. code-block:: c

    y = 10 + y ^ 7;
    // y = 10 + y ^ 6;
    // y = 10;
    // y = x + 76;

This hinders readability and makes the whole codebase reek.
Unused code should be purged from the source file; and revision control (e.g. git) should be used to keep track of these modifications instead.
If you really need sections of code that can be enabled/disabled, then consider using a define that is passed via the compiler to toggle the option.
Or in a pinch, use :code:`#if 0 \ code \ #endif`.

Include File Recommendations
----------------------------

Include files can be one of the most hated aspects of C -- so it is important to use them correctly to prevent losing your mind.
When working with multiple files, there is the concept of a "source" file and a "header" file.
The source file includes all the code/variables that the program needs to work.
The header file exposes an interface that allows other source files to use functions and/or variables defined in the corresponding source file.
The below example shows the proper and recommended implementation of the source and header files.

**source.c**:

.. code-block:: c

    #include "source.h"

    #include <stdio.h>
    #include <stdlib.h>

    static void my_internal_source_function(void) {
        // do some stuff in here
    }

    void my_external_source_function(void) {
        my_internal_source_function();
        // do some other stuff in here
    }

**source.h**:

.. code-block:: c

    #ifndef SOURCE_H
    #define SOURCE_H

    #include "some_other_header.h"

    #ifdef __cplusplus
    extern "C" {
    #endif

    void my_external_source_function(void);

    #ifdef __cplusplus
    }
    #endif

    #endif

Here are the important takeaways from the above example:

- The first line in the source file should be the corresponding header file for the source interface. Other headers can then be included after; with system/toolchain headers last. This ensures that the header includes all the things necessary to compile it.
- The source file uses the **static** keyword in front of a function to indicate that it can only be used in the *source.c* file. This prevents other source files from attempting to use it. It is a good idea to get into the habit of labeling functions  in this way if they are not used anywhere except for the file they are in.
- The header includes so-called "header guards" (the :code"`#ifdef SOURCE_H` / :code:`#define SOURCE_H` lines), which are used to prevent the header from being included multiple times in the same source file.
- The :code:`ifdef __cplusplus` lines are used to prevent a C++ compiler from mangling the names of the header functions. It is a good idea to add this, even if you are working on a C-only project as it will save you any headache if a C++ compiler tries to compile the header.
- The external source function is represented as a "prototype" inside the header. This prototype tells the rest of the source files the arguments and return of the function, but does not define the implementation. It is the responsibility of the linker to take all the compiled source files and find the corresponding functions.

Proper Prototyping
^^^^^^^^^^^^^^^^^^

In C, if a function takes no arguments it should be represented as :code:`foo(void);` in the prototype, not :code:`foo();`.
Contrary to what it might seem, :code:`foo();` indicates that the function can take *any number* of arguments.
Note that this is the opposite in C++.

What not to put in header files
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here are the following things that should not be put in header files in C:

- Function implementations. Only function prototypes should be put in header files.
- Variable declarations. If you need to have a "global variable" (you don't), then the global variable should be declared in a *source* file and then included in the header using the *extern* keyword (e.g. :code:`extern global_variable[100];`).

The reason you shouldn't do the above is that the :code:`#include` preprocessor command literally performs a copy/paste of one file into another.
If a header is used in two different source files, then the function or variable will be duplicated *twice* (include guards cannot prevent this, they only prevent inclusion in a single source file!).
Even worse is making the function/variable "static" in the header, which makes each file has its own implementation -- it will still compile, but it most certainly is not what you intended!
If you ever see code or variables that are defined in a header, run far away.

Avoid Global Variables
----------------------

Global variables are **bad**.
These are variables which are defined outside of a function.

Here's why you shouldn't use them:

- Global variables can be modified by any section of code, making it difficult to remember every possible use.
- A global variable can have no access control. It can not be limited to some parts of the program.
- Using global variables causes namespace pollution. This may lead to unnecessarily reassigning a global value.

There are better alternatives to using global variables, described below:

Proper Scoping
^^^^^^^^^^^^^^

"Scope" is an important part of C programming.
Every opening brace :code:`{` is the start of a new scope, and every ending brace :code:`}` the end of the previous scope.
You want to make sure that the variables you use only need to be in the scope they are in.
For example, in the below code snippet a global variable is used

Using the static keyword
^^^^^^^^^^^^^^^^^^^^^^^^

The static keyword is helpful when trying to avoid dynamic allocation and avoiding global variables.
The below example shows an array that is globally allocated by :code:`malloc`, which is not recommended.

.. code-block:: c

    char big_text_array[16000];

    char *alloc_array(void) {
        big_text_array = malloc(16000);
        return big_text_array;
    }

Alternatively, the :code:`static` keyword can be used to allocate the buffer.
The :code:`static` keyword changes the storage space for the variable, and allows it to persist as if it were a global variable.
The variable maintains the contents it previously held when the function was last called.
Rather than using dynamic allocation to create the array, static allocation can be used instead as shown below:

.. code-block:: c

    char *return_array(void) {
        static char big_text_array[16000];
        return big_text_array;
    }

Using structures
^^^^^^^^^^^^^^^^

Structures are a helpful way to encapsulate particular objects used in a program.
For example, you might have different objects for a player, enemies, and props when creating a game.
A structure allows you to put all the relevant information into a single object that can then be passed around to different functions.

For example, the following code snippet creates a player structure:

.. code-block:: c

    struct player {
        int x;
        int y;
    };

    void set_player_position(struct player *player) {
        player->x = 20;
        player->y = 10;
    }

It is recommended to avoid "typedef" on structures.
This is because it is hiding the underlying type, and makes it harder on readability.

Avoid Dynamic Allocation
------------------------

Dynamic allocation (e.g. *malloc*, *calloc*, *realloc*) should be avoided as much as possible.
This is because it is an expensive operation and uses a few kilobytes of space for the function itself.

On the CE, the heap (the region of memory that the above functions allocate from) is stored in the same region of memory that uninitialized data is stored in (referred to as the "bss" section).
This means that any uninitialized variables not on the stack will automatically use the same region of memory.
Since this region is a fixed known size, there is next to zero usefulness in using malloc to perform memory allocation.

Dynamic allocation can also lead to fragmentation of the heap when running, making programs be extremely unstable and prone to leaks and crashes.
You also aren't guaranteed that you will get a valid memory pointer -- and thus have no way to recover other than to quit your program!

Use Static Analysis Tools
^^^^^^^^^^^^^^^^^^^^^^^^^

Static Analysis examines the code without executing the program in order to find common programming issues and flaw/bugs that may not be intended.
It is a great way to improve the reliability and ensure that you are following the best programming practices.
There are many static analysis tools available, some better than others.
Some common ones include:

- Cppcheck
- Clang Static Analyzer (scan-build)
- Coverity

Cppcheck is the easiest one to use with the CE C toolchain, but it is also fairly limited.
